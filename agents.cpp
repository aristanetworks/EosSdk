// Copyright (c) 2026 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/agents.h"
#include "impl.h"

namespace eos {

class agents_mgr_impl : public agents_mgr {
 public:
   agents_mgr_impl() {
   }

   agents_iter_t agents_iter() const {
      agents_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   bool agent_exists(std::string const& agent_name) const {
      return false;
   }

   std::string agent_status(std::string const& agent_name,
                            std::string const& key) const {
      return "";
   }

   bool agent_status_exists(std::string const& agent_name,
                            std::string const& key) const {
      return false;
   }

   agents_status_iter_t agent_status_iter(std::string const& agent_name) const {
      agents_status_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   std::string agent_option(std::string const& agent_name,
                            std::string const& key) const {
      return "";
   }

   bool agent_option_exists(std::string const& agent_name,
                            std::string const& key) const {
      return false;
   }

   agents_option_iter_t agent_option_iter(std::string const& agent_name) const {
      agents_option_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }
};

DEFINE_STUB_MGR_CTOR(agents_mgr)

agents_handler::agents_handler(agents_mgr *mgr) :
      base_handler<agents_mgr, agents_handler>(mgr) {
}

void agents_handler::watch_all_agents(bool enable) {}

void agents_handler::watch_agent(std::string const& agent_name, bool enable) {}

void agents_handler::on_agent_status_set(std::string const& agent_name,
                                         std::string const& key,
                                         std::string const& value) {}

void agents_handler::on_agent_status_del(std::string const& agent_name,
                                         std::string const& key) {}

void agents_handler::on_agent_enabled_set(std::string const& agent_name,
                                          bool enabled) {}

} // end eos namespace
