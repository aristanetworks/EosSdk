// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>

#include <event2/event.h>

#include "libevent.h"

void
libevent_loop::init() {
   loop_->wait_for_initialized();
   loop_->external_loop_is(this);
}

static void cb_read(evutil_socket_t fd, short /*what*/, void *arg) {
   ((libevent_loop*) arg)->on_readable(fd);
}

void
libevent_loop::watch_readable(int fd, bool interested) {
   assert(interested);  // TODO: support unregistering an fd.
   struct event * ev = event_new(eb_, fd, EV_READ|EV_PERSIST, cb_read, this);
   event_add(ev, NULL);
}

static void cb_write(evutil_socket_t fd, short /*what*/, void *arg) {
   ((libevent_loop*) arg)->on_writable(fd);
}

void
libevent_loop::watch_writable(int fd, bool interested) {
   assert(interested);  // TODO: support unregistering an fd.
   struct event * ev = event_new(eb_, fd, EV_WRITE|EV_PERSIST, cb_write, this);
   event_add(ev, NULL);
}

void
libevent_loop::watch_exception(int fd, bool interested) {
   // libevent doesn't allow watching just for "exceptions".  Rather when a
   // connection is closed, we'll be notified the fd is "readable" and we'll
   // read EOF.
   watch_readable(fd, interested);
}

static void cb_timer(evutil_socket_t fd, short /*what*/, void *arg) {
   ((libevent_loop*) arg)->on_timeout();
}

void
libevent_loop::timeout_time_is(struct timeval deadline) {
   struct event * ev = evtimer_new(eb_, cb_timer, this);
   event_add(ev, &deadline);
}
