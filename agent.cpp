// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>
#include <cstdlib>  // for abort()
#include <functional> // For dummy agent_id impl

#include "eos/agent.h"
#include "impl.h"

namespace eos {

agent_handler::agent_handler(agent_mgr * mgr) : base_handler(mgr) {
   mgr_->add_handler(this);
}

void agent_handler::on_initialized() {
   // Default implementation: do nothing.
}

class agent_mgr_impl : public agent_mgr {
 public:
   agent_mgr_impl() {
   }

   void main_loop(const char * agent_name, int argc, char ** argv) {
      assert(agent_name);   // Must not be NULL.
      assert(*agent_name);  // Must be at least one char long.
      impl.agent_name_is(agent_name);
      impl.main_loop();
   }

   void on_initialized() {
      handler_foreach([=] (agent_handler* handler) {
         handler->on_initialized();
      });
   }
};

void handle_agent_initialize(agent_mgr * mgr) {
   static_cast<agent_mgr_impl*>(mgr)->on_initialized();
}

agent_mgr * new_agent_mgr() {
   return new agent_mgr_impl();
}

void delete_agent_mgr(agent_mgr * mgr) {
   delete mgr;
}

agent_mgr::agent_mgr() {
}

agent_mgr::~agent_mgr() {
}

void agent_mgr::exit() {
   impl.stop_loop();
}

uint32_t agent_mgr::id(const char * agent_name) {
   // Dummy implementation. Eventually we should base this of
   // /proc/run or some other universal lookup.
   std::hash<const char *> h;
   return h(agent_name);
}

}
