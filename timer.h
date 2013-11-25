// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TIMER_H
#define EOS_TIMER_H

namespace eos {

typedef double seconds_t;

// Monotonically increasing time. Corresponds to the number of seconds
// since boottime (with some offset).
seconds_t now();
// 'never' represents a time that will we never see
static const seconds_t never = 0;

/* Class to handle timer events. */
class timeout_handler {
 public:
   timeout_handler();
   ~timeout_handler();

   virtual void on_timeout() = 0;
   void timeout_time_is(seconds_t);
};

}

#endif // EOS_TIMER_H
