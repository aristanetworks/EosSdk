// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>
#include "eos/agent.h"

namespace eos {

agent_handler::agent_handler() {
}

agent_handler::~agent_handler() {
}

void
agent_handler::on_initialized() {
}

void
agent_main_loop(const char * agent_name, int argc, char ** argv) {
   assert(agent_name);   // Must not be NULL.
   assert(*agent_name);  // Must be at least one char long.
}

}
