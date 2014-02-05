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

   // Run the event loop for `duration` seconds. If no duration is
   // specified, all pending events will be executed and control will
   // be returned to the caller.
   void run(seconds_t duration=0) const;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(event_loop);
};

}

#endif // EOS_EVENT_LOOP_H
