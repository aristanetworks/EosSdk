// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/sdk.h"
#include "impl.h"

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
     eth_lag_intf_mgr_(0),
     event_loop_(0),
     fib_mgr_(0),
     intf_mgr_(0),
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
   impl.register_sdk(this);
}

void delete_agent_mgr(agent_mgr *);

sdk::~sdk() {
   delete_agent_mgr(agent_mgr_);
}

void sdk::init_acl_mgr() {
   // TODO: No op impl.
}

agent_mgr * new_agent_mgr();

void sdk::init_agent_mgr() {
   if (!agent_mgr_) {
      agent_mgr_ = new_agent_mgr();
   }
}

void sdk::init_aresolve_mgr() {
   // TODO: No op impl.
}

void sdk::init_class_map_mgr() {
   // TODO: No op impl.
}

void sdk::init_decap_group_mgr() {
   // TODO: No op impl.
}

void sdk::init_directflow_mgr() {
   // TODO: No op impl.
}

void sdk::init_eth_intf_mgr() {
   // TODO: No op impl.
}

void sdk::init_eth_phy_intf_mgr() {
   // TODO: No op impl.
}

void sdk::init_eth_lag_intf_mgr() {
   // TODO: No op impl.
}

void sdk::init_event_loop() {
   // TODO: No op impl.
}

void sdk::init_fib_mgr() {
   // TODO: No op impl.
}

void sdk::init_intf_mgr() {
   // TODO: No op impl.
}

void sdk::init_intf_counter_mgr() {
   // TODO: No op impl.
}

void sdk::init_ip_intf_mgr() {
   // TODO: No op impl.
}

void sdk::init_ip_route_mgr() {
   // TODO: No op impl.
}

void sdk::init_mac_table_mgr() {
   // TODO: No op impl.
}

void sdk::init_mlag_mgr() {
   // TODO: No op impl.
}

void sdk::init_mount_mgr() {
   // TODO: No op impl.
}

void sdk::init_mpls_route_mgr() {
   // TODO: No op impl.
}

void sdk::init_neighbor_table_mgr() {
   // TODO: No op impl.
}

void sdk::init_nexthop_group_mgr() {
   // TODO: No op impl.
}

void sdk::init_policy_map_mgr() {
   // TODO: No op impl.
}

void sdk::init_system_mgr() {
   // TODO: No op impl.
}

void sdk::init_timeout_mgr() {
   // TODO: No op impl.
}

}
