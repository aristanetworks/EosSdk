// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/timer.h"

namespace eos {

seconds_t now() {
   return never;  // TODO: No op impl.
}

timeout_handler::timeout_handler() {
}

timeout_handler::~timeout_handler() {
}

void
timeout_handler::timeout_time_is(seconds_t) {
   // TODO: No op impl.
}

}
