// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TIMER_H
#define EOS_TIMER_H

#include <eos/base.h>

namespace eos {

typedef double seconds_t;

// Monotonically increasing time in seconds. Corresponds to the number
// of seconds since boottime plus an arbitrary offset.
seconds_t now() EOS_SDK_PUBLIC;

// 'never' represents a future time that now() can never reach.
static const seconds_t never = 0;

/* The 'timeout_handler' class manages a single instance of a
timer. To schedule a timeout, call 'timeout_time_is()' using an
absolute time greater than now(). When the timeout_time has been
exceeded, 'on_timeout()' is called and the timer is unset. To cancel a
timer, set the timeout to the 'never' constant.

There are no guarantees that 'on_timeout()' will be called exactly at
the configured timeout, though we guarantee this will never be called
*before* the configured timeout.*/
class EOS_SDK_PUBLIC timeout_handler {
 public:
   timeout_handler();
   ~timeout_handler();

   void timeout_time_is(seconds_t);
   virtual void on_timeout() = 0;
};

}

#endif // EOS_TIMER_H
