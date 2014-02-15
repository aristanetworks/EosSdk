// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>
#include <cstdlib>  // for abort()
#include <functional> // For dummy agent_id impl

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
   impl.agent_name_is(agent_name);
   impl.main_loop();
}

void
agent_exit() {
   impl.stop_loop();
}

uint32_t
agent_id(const char * agent_name) {
   // Dummy implementation. Eventually we should base this of
   // /proc/run or some other universal lookup.
   std::hash<const char *> h;
   return h(agent_name);
}

}
