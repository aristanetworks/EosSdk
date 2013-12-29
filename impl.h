// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_STUBS_IMPL_H
#define EOS_STUBS_IMPL_H

#include <list>
#include <map>
#include <queue>

#include <sys/select.h>  // for fd_set

#include "eos/agent.h"
#include "eos/fd.h"
#include "eos/timer.h"

namespace eos {

/**
 * Handles all the interests of a particular fd_handler.
 *
 * There is one instance of this class per instance of fd_handler.
 * This 1-to-1 association is implemented via a map in the Impl class.
 *
 * This is where we keep track of that the fd_handler we're associated
 * with is interested in.
 */
class fd_handler_sm {
   enum interest_t {
      WANT_READ = 1 << 0,
      WANT_WRITE = 1 << 1,
      WANT_EXCEPT = 1 << 2,
   };
 public:
   /// Returns true if we're interested in this FD at all.
   bool interested_in(int fd) const {
      return fds_.find(fd) != fds_.end();
   }

   /// Sets whether or not we're interested in the given FD being readable.
   void watch_readable(int fd, bool interest) {
      interest_is(fd, interest, WANT_READ);
   }
   /// Returns true iff we're interested in this FD being readable.
   bool want_readable(int fd) const {
      return interested_in(fd) && fds_.at(fd) & WANT_READ;
   }

   /// Sets whether or not we're interested in the given FD being writeable.
   void watch_writable(int fd, bool interest) {
      interest_is(fd, interest, WANT_WRITE);
   }
   /// Returns true iff we're interested in this FD being writeable.
   bool want_writable(int fd) const {
      return interested_in(fd) && fds_.at(fd) & WANT_WRITE;
   }

   /// Sets whether or not we're interested in the given FD being in exception state.
   void watch_exception(int fd, bool interest) {
      interest_is(fd, interest, WANT_EXCEPT);
   }
   /// Returns true iff we're interested in this FD being in exception state.
   bool want_exception(int fd) const {
      return interested_in(fd) && fds_.at(fd) & WANT_EXCEPT;
   }

   /// Prepares the FD sets for select().
   void update_fd_set(int & maxfd,
                      fd_set * readfds,
                      fd_set * writefds,
                      fd_set * exceptfds);
   /// Iterates over the FDs we're interested in.
   std::map<int, uint8_t>::const_iterator fd_set_begin() const {
      return fds_.begin();
   }
   /// End iterator when interating over the FDs we're interested in.
   std::map<int, uint8_t>::const_iterator fd_set_end() const {
      return fds_.end();
   }

 private:
   void interest_is(int fd, bool want, interest_t interest);
   std::map<int, uint8_t> fds_;
};

/**
 * Provides actual storage for `timeout_handler'.
 * Since timeout_handler doesn't store the current timeout, we have to store
 * it here, and associate a `timer' to each `timeout_handler'.
 */
class timer {
 public:
   timer() {
   }
   explicit timer(timeout_handler * handler) : handler_(handler) {
   }
   timeout_handler * handler() {
      return handler_;
   }
   void timeout_is(seconds_t timeout) {
      timeout_ = timeout;
   }
   seconds_t timeout() const {
      return timeout_;
   }
 private:
   seconds_t timeout_;
   timeout_handler * handler_;
   //EOS_SDK_DISALLOW_COPY_CTOR(timer);  // see comment in register_timeout_handler
};

/// Sorts timers such that the ones with the closest deadline come first.
class timer_cmp {
 public:
   bool operator()(const timer* l, const timer* r) {
      return l->timeout() > r->timeout();
   }
};

/**
 * Min-heap of timers, so access to the next timer is O(1).
 * Insertion / deletion is O(log n).  Updating a deadline is O(n).
 * This would be more efficient with a Fibonacci heap, but that
 * doesn't really matter for now.
 */
class timer_queue : public std::priority_queue<timer *,
                                               std::vector<timer *>,
                                               timer_cmp> {
 public:
   timer_queue() {
   }

   /// Re-inserts the given timer in the queue when its deadline is changed.
   void update(timer * timer);
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(timer_queue);
};

/**
 * Provides a basic implementation for various EOS SDK primitives.
 * Keeps track of the state of the stubbed out SDK so we can behave
 * in a compatible way with how the real SDK behaves.
 * This implementation provides no guarantee on ordering of events,
 * meaning notifications don't get delivered to handlers in the same
 * order as with the real SDK.
 */
class Impl {
 public:
   Impl() {
   }
   void register_agent_handler(agent_handler * handler) {
      agent_handlers_.push_back(handler);
   }
   void unregister_agent_handler(agent_handler * handler) {
      agent_handlers_.remove(handler);  // O(N) but the list is tiny.
   }

   void register_fd_handler(fd_handler * handler) {
      fd_handlers_[handler] = fd_handler_sm();
   }
   void unregister_fd_handler(fd_handler * handler) {
      fd_handlers_.erase(handler);
   }
   fd_handler_sm * get_fd_sm(fd_handler * handler) {
      return &fd_handlers_.at(handler);
   }

   void register_timeout_handler(timeout_handler * handler) {
      // We should do this, but our version of GCC is too old and doesn't have
      // 'emplace()' even when compiling in c++0x mode :(
      //timeout_to_timer_.emplace(handler, timer(handler));
      timeout_to_timer_[handler] = timer(handler);
   }
   void unregister_timeout_handler(timeout_handler * handler) {
      timeout_to_timer_.erase(handler);
   }
   void timeout_is(timeout_handler * handler, seconds_t timeout);

   /// Goes into an infinite event loop.
   void main_loop(const char * agent_name);
 private:
   // Min-heap for all outstanding timers.
   timer_queue timers_;

   // Maps a FD handler to the set of FDs it's interested in.
   std::map<fd_handler *, fd_handler_sm> fd_handlers_;

   std::list<agent_handler *> agent_handlers_;

   // Maps a user-created timeout_handler to an outstanding timer.
   std::map<timeout_handler *, timer> timeout_to_timer_;

   EOS_SDK_DISALLOW_COPY_CTOR(Impl);
};

// Like the real SDK, this implementation is not thread safe and only one
// instance of it can be used at a time.
extern Impl impl;

}

#endif // EOS_STUBS_IMPL_H
