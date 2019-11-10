// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <iostream>

#include "eos/exception.h"
#include "eos/panic.h"
#include "eos/event_loop.h"
#include "eos/sdk.h"
#include "impl.h"

namespace eos {

sdk_scoped_lock::sdk_scoped_lock() {
}

sdk_scoped_lock::~sdk_scoped_lock() {
}

#include "GetAgentProcessName.cpp"

sdk::sdk()
   : acl_mgr_(0),
     agent_mgr_(0),
     aresolve_mgr_(0),
     bfd_session_mgr_(0),
     bgp_path_mgr_(0),
     class_map_mgr_(0),
     decap_group_mgr_(0),
     directflow_mgr_(0),
     eapi_mgr_(0),
     eth_intf_mgr_(0),
     eth_phy_intf_mgr_(0),
     eth_phy_intf_counter_mgr_(0),
     eth_lag_intf_mgr_(0),
     event_loop_(0),
     fib_mgr_(0),
     hardware_table_mgr_(0),
     intf_mgr_helper_(0),
     intf_mgr_(0),
     intf_counter_mgr_(0),
     ip_intf_mgr_(0),
     ip_route_mgr_(0),
     lldp_mgr_(0),
     macsec_mgr_(0),
     mac_table_mgr_(0),
     mlag_mgr_(0),
     mount_mgr_(0),
     mpls_route_mgr_(0),
     mpls_vrf_label_mgr_(0),
     neighbor_table_mgr_(0),
     nexthop_group_mgr_(0),
     nexthop_group_tunnel_mgr_(0),
     policy_map_mgr_(0),
     subintf_mgr_(0),
     system_mgr_(0),
     timeout_mgr_(0),
     vrf_mgr_(0) {
   name_ = get_agent_process_name();
   eossdk_context_ = NULL;
   impl.register_sdk(this);
   print_profiles::set_print_profiles(name_.c_str());
}

sdk::sdk(std::string const name, void *eossdk_context)
   : acl_mgr_(0),
     agent_mgr_(0),
     aresolve_mgr_(0),
     class_map_mgr_(0),
     decap_group_mgr_(0),
     directflow_mgr_(0),
     eapi_mgr_(0),
     eth_intf_mgr_(0),
     eth_phy_intf_mgr_(0),
     eth_phy_intf_counter_mgr_(0),
     eth_lag_intf_mgr_(0),
     event_loop_(0),
     fib_mgr_(0),
     hardware_table_mgr_(0),
     intf_mgr_helper_(0),     
     intf_mgr_(0),
     intf_counter_mgr_(0),
     ip_intf_mgr_(0),
     ip_route_mgr_(0),
     lldp_mgr_(0),
     macsec_mgr_(0),
     mac_table_mgr_(0),
     mlag_mgr_(0),
     mount_mgr_(0),
     mpls_route_mgr_(0),
     mpls_vrf_label_mgr_(0),
     neighbor_table_mgr_(0),
     nexthop_group_mgr_(0),
     nexthop_group_tunnel_mgr_(0),
     policy_map_mgr_(0),
     subintf_mgr_(0),
     system_mgr_(0),
     timeout_mgr_(0),
     vrf_mgr_(0) {
   name_ = name;
   eossdk_context_ = eossdk_context;
   impl.register_sdk(this);
   print_profiles::set_print_profiles(name_.c_str());
}

void
sdk::main_loop(int argc, char ** argv) {
   assert(!name_.empty() && "No agent name set");
   impl.agent_name_is(name_.c_str());
   print_profiles::write_profiles();
   impl.main_loop();

}

void delete_agent_mgr(agent_mgr *);

sdk::~sdk() {
   delete_agent_mgr(agent_mgr_);
}

void sdk::initialize_context() {
}

INIT_STUB_MGR(acl_mgr)
INIT_STUB_MGR(agent_mgr)
INIT_STUB_MGR(aresolve_mgr)
INIT_STUB_MGR(bfd_session_mgr)
INIT_STUB_MGR(bgp_path_mgr)
INIT_STUB_MGR(class_map_mgr)
INIT_STUB_MGR(decap_group_mgr)
INIT_STUB_MGR(directflow_mgr)
INIT_STUB_MGR(eapi_mgr)
INIT_STUB_MGR(eth_intf_mgr)
INIT_STUB_MGR(eth_phy_intf_mgr)
INIT_STUB_MGR(eth_phy_intf_counter_mgr)
INIT_STUB_MGR(eth_lag_intf_mgr)
INIT_STUB_MGR(hardware_table_mgr)
INIT_STUB_MGR(intf_mgr)
INIT_STUB_MGR(intf_counter_mgr)
INIT_STUB_MGR(ip_intf_mgr)
INIT_STUB_MGR(ip_route_mgr)
INIT_STUB_MGR(lldp_mgr)
INIT_STUB_MGR(macsec_mgr)
INIT_STUB_MGR(mac_table_mgr)
INIT_STUB_MGR(mlag_mgr)
INIT_STUB_MGR(mpls_route_mgr)
INIT_STUB_MGR(mpls_vrf_label_mgr)
INIT_STUB_MGR(neighbor_table_mgr)
INIT_STUB_MGR(nexthop_group_mgr)
INIT_STUB_MGR(nexthop_group_tunnel_mgr)
INIT_STUB_MGR(policy_map_mgr)
INIT_STUB_MGR(subintf_mgr)
INIT_STUB_MGR(system_mgr)
INIT_STUB_MGR(timeout_mgr)
INIT_STUB_MGR(vrf_mgr)

void sdk::init_event_loop() {
   if(!event_loop_) {
      event_loop_ = new event_loop(0);
   }
}

void sdk::init_fib_mgr(mgr_mode_type_t mode) {
   // TODO: No op impl.
}

void sdk::init_mount_mgr() {
   // BUG86400 - Not a public function
}

void sdk::init_intf_mgr_helper() {
   // BUG86400 - Not a public function
}

void default_signal_handler(int signo) {
   // TODO: No op impl.
}

void internal_connection_buffer_size_is(uint32_t bytes) {
}

// Real functions to facilitate the making of customized sysdb-mount-profiles 
// (to use in place of the brute-force one called "EosSdk", see 
// /usr/lib/SysdbMountProfiles/EosSdkAll), an app can be started with the env var 
// EOS_PRINT_PROFILES_AND_EXIT pointing to a filename where the profile should be 
// written, then exit.
#include "MaybePrintProfilesAndExit.cpp"

}
