// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>
#include <cstdlib>  // for abort()
#include "eos/agent.h"
#include "impl.h"

namespace eos {

agent_handler::agent_handler() {
   impl.register_agent_handler(this);
}

agent_handler::~agent_handler() {
   impl.unregister_agent_handler(this);
}

void
agent_handler::on_initialized() {
   // Default implementation: do nothing.
}

void
agent_main_loop(const char * agent_name, int argc, char ** argv) {
   assert(agent_name);   // Must not be NULL.
   assert(*agent_name);  // Must be at least one char long.
   impl.main_loop(agent_name);
   assert(!"why did main_loop return?");
   for(;;) {
      abort();
   }
}

}
