// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/panic.h"
#include "eos/event_loop.h"
#include "impl.h"

namespace eos {

event_loop::event_loop() {
}

event_loop::~event_loop() {
}

void
event_loop::run(seconds_t duration) const {
   if(duration < 0){
      panic("duration must be 0 or greater");
   }
   impl.main_loop(duration);
}

}
