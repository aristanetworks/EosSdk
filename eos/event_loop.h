// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_EVENT_LOOP_H
#define EOS_EVENT_LOOP_H

#include <eos/base.h>

namespace eos {

class EOS_SDK_PUBLIC event_loop {
 public:
   event_loop();
   ~event_loop();

   // Wait for all managers to be initialized. Generally called right
   // after creating the event_loop, as an alternative to creating an
   // agent_handler and then waiting for on_initialized to be called.
   void wait_for_initialized() const;
   
   // Run the event loop for `duration` seconds. If no duration is
   // specified, all pending events will be executed and control will
   // be returned to the caller.
   void run(seconds_t duration=0) const;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(event_loop);
};

}

#endif // EOS_EVENT_LOOP_H
