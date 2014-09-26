// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>
#include <cstring>

#include "eos/event_loop.h"
#include "eos/sdk.h"
#include "impl.h"

static char DEFAULT_AGENT_PROCESS_NAME[] = "TestAgent";

namespace eos {

sdk::sdk()
   : acl_mgr_(0),
     agent_mgr_(0),
     aresolve_mgr_(0),
     class_map_mgr_(0),
     decap_group_mgr_(0),
     directflow_mgr_(0),
     eth_intf_mgr_(0),
     eth_phy_intf_mgr_(0),
     eth_phy_intf_counter_mgr_(0),
     eth_lag_intf_mgr_(0),
     event_loop_(0),
     fib_mgr_(0),
     intf_mgr_(0),
     intf_counter_mgr_(0),
     ip_intf_mgr_(0),
     ip_route_mgr_(0),
     mac_table_mgr_(0),
     mlag_mgr_(0),
     mount_mgr_(0),
     mpls_route_mgr_(0),
     neighbor_table_mgr_(0),
     nexthop_group_mgr_(0),
     policy_map_mgr_(0),
     system_mgr_(0),
     timeout_mgr_(0) {
   char * agent_process_name = getenv("AGENT_PROCESS_NAME");
   if (!agent_process_name) {
      agent_process_name = DEFAULT_AGENT_PROCESS_NAME;
   }
   for (uint16_t i = 0; i < strlen(agent_process_name); i++) {
      char c = agent_process_name[i];
      if(!isalnum(c) && c != '-' && c != '_') {
         panic(configuration_error("Invalid name specified in AGENT_PROCESS_NAME. "
                                   "Only alphanumeric characters, underscores, "
                                   "and dashes are permitted."));
      }
   }
   name_ = agent_process_name;
   impl.register_sdk(this);
}

sdk::sdk(std::string const name)
   : acl_mgr_(0),
     agent_mgr_(0),
     aresolve_mgr_(0),
     class_map_mgr_(0),
     decap_group_mgr_(0),
     directflow_mgr_(0),
     eth_intf_mgr_(0),
     eth_phy_intf_mgr_(0),
     eth_phy_intf_counter_mgr_(0),
     eth_lag_intf_mgr_(0),
     event_loop_(0),
     fib_mgr_(0),
     intf_mgr_(0),
     intf_counter_mgr_(0),
     ip_intf_mgr_(0),
     ip_route_mgr_(0),
     mac_table_mgr_(0),
     mlag_mgr_(0),
     mount_mgr_(0),
     mpls_route_mgr_(0),
     neighbor_table_mgr_(0),
     nexthop_group_mgr_(0),
     policy_map_mgr_(0),
     system_mgr_(0),
     timeout_mgr_(0) {
   name_ = name;
   impl.register_sdk(this);
}

void
sdk::main_loop(int argc, char ** argv) {
   assert(!name_.empty() && "No agent name set");
   impl.agent_name_is(name_.c_str());
   impl.main_loop();

}

void delete_agent_mgr(agent_mgr *);

sdk::~sdk() {
   delete_agent_mgr(agent_mgr_);
}

INIT_STUB_MGR(acl_mgr)
INIT_STUB_MGR(agent_mgr)
INIT_STUB_MGR(aresolve_mgr)
INIT_STUB_MGR(class_map_mgr)
INIT_STUB_MGR(decap_group_mgr)
INIT_STUB_MGR(directflow_mgr)
INIT_STUB_MGR(eth_intf_mgr)
INIT_STUB_MGR(eth_phy_intf_mgr)
INIT_STUB_MGR(eth_phy_intf_counter_mgr)
INIT_STUB_MGR(eth_lag_intf_mgr)
INIT_STUB_MGR(fib_mgr)
INIT_STUB_MGR(intf_mgr)
INIT_STUB_MGR(intf_counter_mgr)
INIT_STUB_MGR(ip_intf_mgr)
INIT_STUB_MGR(ip_route_mgr)
INIT_STUB_MGR(mac_table_mgr)
INIT_STUB_MGR(mlag_mgr)
INIT_STUB_MGR(mpls_route_mgr)
INIT_STUB_MGR(neighbor_table_mgr)
INIT_STUB_MGR(nexthop_group_mgr)
INIT_STUB_MGR(policy_map_mgr)
INIT_STUB_MGR(system_mgr)
INIT_STUB_MGR(timeout_mgr)

void sdk::init_event_loop() {
   if(!event_loop_) {
      event_loop_ = new event_loop(0);
   }
}

void sdk::init_mount_mgr() {
   // BUG86400 - Not a public function
}

}
