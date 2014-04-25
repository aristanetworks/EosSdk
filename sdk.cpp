// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/sdk.h"
#include "impl.h"

namespace eos {

sdk::sdk() {
   impl.register_sdk(this);
}

sdk::~sdk() {
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

void sdk::init_fib_mgr() {
   // TODO: No op impl.
}

void sdk::init_intf_mgr() {
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

}
