// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <time.h>

#include <cstdio>

#include "eos/base_mgr.h"
#include "eos/panic.h"
#include "eos/timer.h"
#include "impl.h"

namespace eos {

//static seconds_t const TIME_BASE = 1000000.0;

seconds_t now() {
   struct timespec t;
   int ret = clock_gettime(CLOCK_MONOTONIC, &t);
   if(ret == -1) {
      panic("clock_gettime(CLOCK_MONOTONIC) returned %d", ret);
   }
   return t.tv_sec + 0.000000001 * t.tv_nsec;// + TIME_BASE;
}

timeout_handler::timeout_handler(timeout_mgr * mgr) : base_handler(mgr) {
   impl.register_timeout_handler(this);
}

timeout_handler::~timeout_handler() {
   impl.unregister_timeout_handler(this);
}

void
timeout_handler::timeout_time_is(seconds_t timeout) {
   impl.timeout_is(this, timeout);
}

timeout_mgr::~timeout_mgr() {
}

class timeout_mgr_impl: public timeout_mgr {
 public:
   timeout_mgr_impl() {
   }

   void init_handler(timeout_handler * handler) {
      // TODO: No op impl.
   }
};

}
