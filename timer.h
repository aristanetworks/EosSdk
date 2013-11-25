// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TIMER_H
#define EOS_TIMER_H

#include <math.h>

namespace eos {

typedef double seconds_t;

// Seconds since boot (clock_monotonic).
seconds_t now();
static const seconds_t never = INFINITY;

class timeout_handler {
 public:
   timeout_handler();
   ~timeout_handler();
   virtual void on_timeout() = 0;
   void timeout_time_is(seconds_t);
};

}

#endif // EOS_TIMER_H
