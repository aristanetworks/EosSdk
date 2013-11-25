// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <Ark/HTimerWheel.h>
#include <EosSdk/timer.h>
#include <EosSdk/panic.h>
#include <TimerSm.h>
#include <Tac/Tracing.h>
#include <Tac/Time.h>
#include <map>

DEFAULT_TRACE_HANDLE( "eos" );

namespace eos {

static double const TIME_BASE = 1000000.0;

seconds_t now() {
   return Tac::now() + TIME_BASE;
}

Ark::TimerWheel::Ptr
get_timer_wheel() {
   static Ark::TimerWheel::Ptr timer_wheel = Ark::TimerWheel::TimerWheelIs(
         0,
         Tac::activityManager()->clock(),
         1,
         0xffffffff,
         true,
         1024 );
   return timer_wheel;
}

std::map< timeout_handler *, TimerTaskSm::Ptr > taskToTaskSm;
std::map< TimerTaskSm *, timeout_handler * > taskSmToTask;

timeout_handler *get_timeout_handler( const TimerTaskSm::Ptr & taskSm ) {
   return taskSmToTask[ taskSm.ptr() ];
}

timeout_handler::timeout_handler() {
   // Enqueue the new timer task, with no wakeup time
   TimerTaskSm::Ptr taskSm = TimerTaskSm::TimerTaskSmIs( get_timer_wheel() );
   taskSmToTask[ taskSm.ptr() ] = this;
   taskToTaskSm[ this ] = taskSm;
}

timeout_handler::~timeout_handler() {
   // Dequeue ourselves
   TimerTaskSm::Ptr taskSm = taskToTaskSm[ this ];
   taskSmToTask.erase( taskSm.ptr() );
   taskToTaskSm.erase( this );
}

void
timeout_handler::timeout_time_is( seconds_t when ) {
   TRACE9( __PRETTY_FUNCTION__ << " " << when );
   if( when != never && when < TIME_BASE ) {
      panic( "absolute time value %lf too small to be plausible", when );
   }
   if( when == never ){
      when = Tac::endOfTime;
   }
   taskToTaskSm[ this ]->wakeupTimeIs( when - TIME_BASE );
}

//
// TimerTaskSm method implementations
//

void
TimerTaskSm::run() {
   taskSmToTask[ this ]->on_timeout();
}

void
TimerTaskSm::wakeupTimeIs( const Tac::Seconds & when ) {
   wheel_->timeMinIs( when );
}


}
