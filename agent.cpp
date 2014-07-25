// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>
#include <cstdlib>  // for abort()
#include <functional> // For dummy agent_id impl

#include "eos/agent.h"
#include "impl.h"

namespace eos {

agent_handler::agent_handler(agent_mgr * mgr) : 
      base_handler<agent_mgr, agent_handler>(mgr) {
   mgr_->add_handler(this);
}

void agent_handler::on_initialized() {
   // Default implementation: do nothing.
}

void agent_handler::on_agent_enabled(bool enabled) {
   // Default implementation calls agent_shutdown_complete_is
   // automatically when the agent is disabled
   if(!enabled) {
      get_agent_mgr()->agent_shutdown_complete_is(true);
   }
}

void agent_handler::on_agent_option(std::string const & name,
                                    std::string const & value) {
   // Default implementation: do nothing.
}

static void call_on_initialized(agent_handler* handler) {
   handler->on_initialized();
}

class agent_mgr_impl : public agent_mgr {
 public:
   agent_mgr_impl() {
   }

   void main_loop(const char * agent_name, int argc, char ** argv) {
      assert(agent_name);   // Must not be NULL.
      assert(*agent_name);  // Must be at least one char long.
      agentName_ = std::string(agent_name);
      impl.agent_name_is(agent_name);
      impl.main_loop();
   }

   void on_initialized() {
      handler_foreach(call_on_initialized);
   }

   std::string agent_name() const {
      return agentName_;
   }

   bool enabled() const {
      return true;
   }

   void agent_shutdown_complete_is(bool complete) {
   }

   std::string agent_option(std::string const & name) const {
      return "";
   }

   void
   status_set(std::string const & key, std::string const & value) {
   }

   void
   status_del(std::string const & key) {
   }
   
   std::string
   status(std::string const & key) const {
      return "";
   }

 private:
   std::string agentName_;
};

void handle_agent_initialize(agent_mgr * mgr) {
   static_cast<agent_mgr_impl*>(mgr)->on_initialized();
}

DEFINE_STUB_MGR_CTOR(agent_mgr)

void delete_agent_mgr(agent_mgr * mgr) {
   delete mgr;
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
