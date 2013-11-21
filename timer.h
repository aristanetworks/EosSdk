// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOSSDK_TIMER_H
#define EOSSDK_TIMER_H

namespace eos {

typedef double seconds_t;
static const seconds_t NEVER = NAN;

// Seconds since boot (clock_monotonic).
seconds_t now();

class timer_task {
 public:
   timer_task();
   ~timer_task();
   virtual void run() = 0;
   void wakeup_time_is( seconds_t );
   
};


}

#endif // EOSSDK_TIMER_H
