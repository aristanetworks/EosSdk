// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

<<= TacModule("Tac::Time");
<<= TacModule("Ark::HTimerWheel");

eos : Tac::Namespace {

TimerTaskSm : Tac::Type(wheel) : Tac::Constrainer {
   tacFwkActivity = 0;

   wheel : in Ark::TimerWheel::PtrConst;
      
   run : extern invasive void();
   wheel::time => run();

   wakeupTimeIs : extern invasive void(when : Tac::Seconds);
}

}

<<= CppBlock("TimerSm.tin");