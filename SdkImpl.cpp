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
#include "SdkImpl.h"
#include "impl.h"

namespace eos {

#define SDK_INITIALIZATION_LIST                 \
   acl_mgr_(0),                                 \
   agent_mgr_(0),                               \
   aresolve_mgr_(0),                            \
   bfd_session_mgr_(0),                         \
   bgp_mgr_(0),                                 \
   bgp_path_mgr_(0),                            \
   class_map_mgr_(0),                           \
   decap_group_mgr_(0),                         \
   directflow_mgr_(0),                          \
   eapi_mgr_(0),                                \
   eth_intf_mgr_(0),                            \
   eth_phy_intf_mgr_(0),                        \
   eth_phy_intf_counter_mgr_(0),                \
   eth_lag_intf_mgr_(0),                        \
   event_loop_(0),                              \
   fib_mgr_(0),                                 \
   hardware_table_mgr_(0),                      \
   intf_mgr_helper_(0),                         \
   intf_mgr_(0),                                \
   intf_counter_mgr_(0),                        \
   ip_intf_mgr_(0),                             \
   ip_route_mgr_(0),                            \
   lldp_mgr_(0),                                \
   macsec_mgr_(0),                              \
   mac_table_mgr_(0),                           \
   mlag_mgr_(0),                                \
   mount_mgr_(0),                               \
   mpls_route_mgr_(0),                          \
   mpls_vrf_label_mgr_(0),                      \
   neighbor_table_mgr_(0),                      \
   nexthop_group_mgr_(0),                       \
   nexthop_group_tunnel_mgr_(0),                \
   policy_map_mgr_(0),                          \
   route_map_mgr_(0),                           \
   subintf_mgr_(0),                             \
   system_mgr_(0),                              \
   timeout_mgr_(0),                             \
   vrf_mgr_(0),                                 \
   xcvr_mgr_(0)                                 \

// this is code we share with the stubs, used to figure out the name of the agent
// based on /proc/self/cmdline (at that point we no longer have access to argv), and
// doing some massaging, like removing .py extensions and replacing wierd chars.
#include "GetAgentProcessName.cpp"

sdk::SdkImpl::SdkImpl() : SDK_INITIALIZATION_LIST {
   name_ = get_agent_process_name();
   eossdk_context_ = NULL;
   impl.register_sdk(this);
   print_profiles::set_print_profiles(name_.c_str());
}

sdk::SdkImpl::SdkImpl(std::string const name, void *eossdk_context) 
   : SDK_INITIALIZATION_LIST {
   name_ = name;
   eossdk_context_ = eossdk_context;
   impl.register_sdk(this);
   print_profiles::set_print_profiles(name_.c_str());
}

void
sdk::SdkImpl::main_loop(int argc, char ** argv) {
   assert(!name_.empty() && "No agent name set");
   impl.agent_name_is(name_.c_str());
   print_profiles::write_profiles();
   impl.main_loop();

}

void delete_agent_mgr(agent_mgr *);

sdk::SdkImpl::~SdkImpl() {
   delete_agent_mgr(agent_mgr_);
}

void sdk::SdkImpl::initialize_context() {
}

INIT_STUB_MGR(acl_mgr)
INIT_STUB_MGR(agent_mgr)
INIT_STUB_MGR(aresolve_mgr)
INIT_STUB_MGR(bfd_session_mgr)
INIT_STUB_MGR(bgp_mgr)
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
INIT_STUB_MGR(route_map_mgr)
INIT_STUB_MGR(subintf_mgr)
INIT_STUB_MGR(system_mgr)
INIT_STUB_MGR(timeout_mgr)
INIT_STUB_MGR(vrf_mgr)
INIT_STUB_MGR(xcvr_mgr)

void sdk::SdkImpl::init_event_loop() {
   if(!event_loop_) {
      event_loop_ = new event_loop(0);
   }
}

void sdk::SdkImpl::init_fib_mgr(mgr_mode_type_t mode) {
   // TODO: No op impl.
}

// Explicit definition for counter manager init with arguments
intf_counter_mgr * new_intf_counter_mgr();
void sdk::SdkImpl::init_intf_counter_mgr( mgr_mode_type_t ) {
   if(!intf_counter_mgr_) {
         intf_counter_mgr_ = new_intf_counter_mgr();
   }
}

void sdk::SdkImpl::init_mount_mgr() {
   // BUG86400 - Not a public function
}

void sdk::SdkImpl::init_intf_mgr_helper() {
   // BUG86400 - Not a public function
}

void default_signal_handler(int signo) {
   // TODO: No op impl.
}

void internal_connection_buffer_size_is(uint32_t bytes) {
}

void api_trace_enable_is(bool new_api_trace) {
}

void param_trace_enable_is(bool new_param_trace) {
}

void api_trace_buffer_sizes_is(int(&size_spec)[10]) {
}

// Real functions to facilitate the making of customized sysdb-mount-profiles 
// (to use in place of the brute-force one called "EosSdk", see 
// /usr/lib/SysdbMountProfiles/EosSdkAll), an app can be started with the env var 
// EOS_PRINT_PROFILES_AND_EXIT pointing to a filename where the profile should be 
// written, then exit.
#include "MaybePrintProfilesAndExit.cpp"

sdk_scoped_lock::sdk_scoped_lock() {
}

sdk_scoped_lock::~sdk_scoped_lock() {
}

}
