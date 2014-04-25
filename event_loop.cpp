// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/panic.h"
#include "eos/event_loop.h"
#include "impl.h"

namespace eos {

void
event_loop_handler::on_readable(int) {
   impl.main_loop(0);
}

void
event_loop_handler::on_writable(int) {
   impl.main_loop(0);
}

void
event_loop_handler::on_exception(int) {
   impl.main_loop(0);
}

void
event_loop_handler::on_timeout() {
   impl.main_loop(0);
}

event_loop::event_loop(mount_mgr * mgr) : mount_mgr_(mgr) {
}

event_loop::~event_loop() {
}

void
event_loop::wait_for_initialized() const {
}

void
event_loop::run(seconds_t duration) const {
   if(duration < 0){
      panic("duration must be 0 or greater");
   }
   impl.main_loop(duration);
}

void
event_loop::external_loop_is(event_loop_handler * loop) {
   if(!loop) {
      panic("The event_loop_handler passed in argument was null");
   }
   loop_ = loop;
   // TODO: No-op impl.
}

}
