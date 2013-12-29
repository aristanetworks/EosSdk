// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <algorithm>
#include <cerrno>
#include <cstdio>
#include <ctime>  // for time_t
#include <sys/select.h>
#include <sys/time.h>  // for struct timeval

#include "impl.h"
#include "eos/panic.h"

namespace eos {

Impl impl;

void
fd_handler_sm::update_fd_set(int & maxfd,
                             fd_set * readfds,
                             fd_set * writefds,
                             fd_set * exceptfds) {
   for(auto i = fds_.begin(); i != fds_.end(); i++) {
      int fd = i->first;
      if(fd > maxfd) {
         maxfd = fd;
      }
      uint8_t flags = i->second;
      if (flags & WANT_READ) {
         FD_SET(fd, readfds);
      }
      if (flags & WANT_WRITE) {
         FD_SET(fd, writefds);
      }
      if (flags & WANT_EXCEPT) {
         FD_SET(fd, exceptfds);
      }
   }
}

void
fd_handler_sm::interest_is(int fd, bool want, interest_t interest) {
   if(want) {
      fds_[fd] = fds_[fd] | interest;
   } else {
      fds_[fd] = fds_[fd] & ~interest;
      if(!fds_[fd]) {
         fds_.erase(fd);
      }
   }
}

void
timer_queue::update(timer * timer) {
   if (timer->timeout() == never) {
      // Remove the timer from the list.  Don't use erase() because it's O(N).
      auto it = std::find(c.begin(), c.end(), timer);
      if (it == c.end()) {
         return;  // We weren't in the list, so nothing to do.
      }
      // Swap the one we want to remove with the last one, and pop back.  O(1)
      std::swap(*it, c.back());
      c.pop_back();
   }
   // Re-sort our vector into a min-heap.  O(3N) = O(N).
   std::make_heap(c.begin(), c.end(), comp);
}

void Impl::timeout_is(timeout_handler * handler, seconds_t timeout) {
   timer& timer = timeout_to_timer_[handler];
   seconds_t previous = timer.timeout();
   timer.timeout_is(timeout);
   if (previous == never) {    // If we weren't previously scheduled...
      timers_.push(&timer);    // ... then add ourself to the min-heap.
   } else {                    // Otherwise, we were already scheduled...
      timers_.update(&timer);  // ... so we need to adjust our position.
   }
}

static struct timeval to_timeval(seconds_t time) {
   struct timeval tv;
   tv.tv_sec = time_t(time);
   tv.tv_usec = suseconds_t((time - tv.tv_sec) * 1000000.0 + 0.5);
   return tv;
}

void Impl::main_loop(const char * agent_name) {
   for(auto i = agent_handlers_.begin(); i != agent_handlers_.end(); ++i) {
      (*i)->on_initialized();
   }

   while(true) {
      int maxfd = 0;
      fd_set readfds;
      FD_ZERO(&readfds);
      fd_set writefds;
      FD_ZERO(&writefds);
      fd_set exceptfds;
      FD_ZERO(&exceptfds);

      for(auto handler = fd_handlers_.begin();
          handler != fd_handlers_.end(); handler++) {
         handler->second.update_fd_set(maxfd, &readfds, &writefds, &exceptfds);
      }
      maxfd++;

      seconds_t next_deadline;  // Absolute point in time of our next deadline.
      seconds_t timeout_seconds;  // How long we're gonna sleep to get there.
      timer * next_timer = 0;
      if(timers_.empty()) {
         next_deadline = never;
         timeout_seconds = 0;
      } else {
         next_timer = timers_.top();
         timers_.pop();
         next_deadline = next_timer->timeout();
         timeout_seconds = next_deadline - now();
      }

      // Consider switching to epoll, but this doesn't matter for now.
      struct timeval timeout = to_timeval(timeout_seconds);
      int rv = select(maxfd, &readfds, &writefds, &exceptfds,
                      next_deadline == never ? 0 : &timeout);

      if(rv < 0) {  // select() failed?
         switch(errno) {
            case EINTR:
               break;  // Go straight to the point where we process timers.
            case EBADF:
               panic("TODO: handle this case");
            case EINVAL:
               panic("Programming bug, should never happen");
            case ENOMEM:
               panic("System out of memory");
         }
         panic("Unhandled errno on select() failure: %d", errno);
      } else {  // select() succeeded.
         // Process notifications: for each handler, check each FD it's
         // interested in, and if the FD was select()ed, notify it.
         for(auto handler_iter = fd_handlers_.begin();
             handler_iter != fd_handlers_.end(); handler_iter++) {
            auto handler = handler_iter->first;
            auto sm = handler_iter->second;
            for(auto fd_iter = sm.fd_set_begin();
                fd_iter != sm.fd_set_end(); fd_iter++) {
               int fd = fd_iter->first;
               if(FD_ISSET(fd, &readfds) && sm.want_readable(fd)) {
                  handler->on_readable(fd);
               }
               if(FD_ISSET(fd, &writefds) && sm.want_writable(fd)) {
                  handler->on_writable(fd);
               }
               if(FD_ISSET(fd, &exceptfds) && sm.want_exception(fd)) {
                  handler->on_exception(fd);
               }
            }
         }
      }

      // Process timers.
      if(next_timer) {  // Do we have at least one outstanding timer?
         if(now() >= next_deadline) {  // Our first timer has passed.
            next_timer->handler()->on_timeout();
            // We may have other timers that have passed too.
            while(!timers_.empty()) {
               next_timer = timers_.top();  // Grab the next timer.
               if(next_timer->timeout() > now()) {  // Should it have fired already?
                  break;  // No: stop here.
               }  // Yes: trigger the callback, and continue.
               timers_.pop();
               next_timer->handler()->on_timeout();
            }
         } else {  // Our first timer needs to be rescheduled.
            timers_.push(next_timer);
         }
      }
   }
}

}
