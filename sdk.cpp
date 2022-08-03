// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/sdk.h"
#include "SdkImpl.h"
#include "eos/event_loop.h"
#include "eos/panic.h"

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

sdk::sdk() :
   sdkImpl{std::make_unique<SdkImpl>()}
{}

sdk::sdk(std::string const name, void *eossdk_context) :
   sdkImpl{std::make_unique<SdkImpl>(name, eossdk_context)}
{}

sdk::~sdk() {
   //delete sdkImpl;
}

void sdk::initialize_context() {
   sdkImpl->initialize_context();
}

void
sdk::main_loop(int argc, char ** argv) {
   sdkImpl->main_loop(argc, argv);
}

std::string sdk::name() {
   return sdkImpl->name();
}




acl_mgr * sdk::get_acl_mgr() {
   return sdkImpl->get_acl_mgr();
}

agent_mgr * sdk::get_agent_mgr() {
   return sdkImpl->get_agent_mgr();
}

aresolve_mgr * sdk::get_aresolve_mgr() {
   return sdkImpl->get_aresolve_mgr();
}

bfd_session_mgr * sdk::get_bfd_session_mgr() {
   return sdkImpl->get_bfd_session_mgr();
}

bgp_mgr * sdk::get_bgp_mgr() {
   return sdkImpl->get_bgp_mgr();
}

bgp_path_mgr * sdk::get_bgp_path_mgr() {
   return sdkImpl->get_bgp_path_mgr();
}

class_map_mgr * sdk::get_class_map_mgr() {
   return sdkImpl->get_class_map_mgr();
}

decap_group_mgr * sdk::get_decap_group_mgr() {
   return sdkImpl->get_decap_group_mgr();
}

directflow_mgr * sdk::get_directflow_mgr() {
   return sdkImpl->get_directflow_mgr();
}

eapi_mgr * sdk::get_eapi_mgr() {
   return sdkImpl->get_eapi_mgr();
}

eth_intf_mgr * sdk::get_eth_intf_mgr() {
   return sdkImpl->get_eth_intf_mgr();
}

eth_lag_intf_mgr * sdk::get_eth_lag_intf_mgr() {
   return sdkImpl->get_eth_lag_intf_mgr();
}

eth_phy_intf_mgr * sdk::get_eth_phy_intf_mgr() {
   return sdkImpl->get_eth_phy_intf_mgr();
}

eth_phy_intf_counter_mgr * sdk::get_eth_phy_intf_counter_mgr() {
   return sdkImpl->get_eth_phy_intf_counter_mgr();
}

event_loop * sdk::get_event_loop() {
   return sdkImpl->get_event_loop();
}

fib_mgr * sdk::get_fib_mgr(mgr_mode_type_t mode) {
   return sdkImpl->get_fib_mgr(mode);
}

fpga_mgr * sdk::get_fpga_mgr() {
   return sdkImpl->get_fpga_mgr();
}

ham_mgr * sdk::get_ham_mgr() {
   return sdkImpl->get_ham_mgr();
}

hardware_table_mgr * sdk::get_hardware_table_mgr() {
   return sdkImpl->get_hardware_table_mgr();
}

intf_mgr * sdk::get_intf_mgr() {
   return sdkImpl->get_intf_mgr();
}

intf_counter_mgr * sdk::get_intf_counter_mgr() {
   return sdkImpl->get_intf_counter_mgr();
}

ip_intf_mgr * sdk::get_ip_intf_mgr() {
   return sdkImpl->get_ip_intf_mgr();
}

ip_route_mgr * sdk::get_ip_route_mgr() {
   return sdkImpl->get_ip_route_mgr();
}

#if 0
intf_mgr_helper * sdk::get_intf_mgr_helper() {
   return sdkImpl->get_intf_mgr_helper() {
}
#endif

l1_source_mgr * sdk::get_l1_source_mgr() {
   return sdkImpl->get_l1_source_mgr();
}

macsec_mgr * sdk::get_macsec_mgr() {
   return sdkImpl->get_macsec_mgr();
}

mac_table_mgr * sdk::get_mac_table_mgr() {
   return sdkImpl->get_mac_table_mgr();
}

mlag_mgr * sdk::get_mlag_mgr() {
   return sdkImpl->get_mlag_mgr();
}

mount_mgr * sdk::get_mount_mgr() {
   return sdkImpl->get_mount_mgr();
}

mpls_route_mgr * sdk::get_mpls_route_mgr() {
   return sdkImpl->get_mpls_route_mgr();
}

mpls_vrf_label_mgr * sdk::get_mpls_vrf_label_mgr() {
   return sdkImpl->get_mpls_vrf_label_mgr();
}

neighbor_table_mgr * sdk::get_neighbor_table_mgr() {
   return sdkImpl->get_neighbor_table_mgr();
}

nexthop_group_mgr * sdk::get_nexthop_group_mgr() {
   return sdkImpl->get_nexthop_group_mgr();
}

policy_map_mgr * sdk::get_policy_map_mgr() {
   return sdkImpl->get_policy_map_mgr();
}

route_map_mgr * sdk::get_route_map_mgr() {
   return sdkImpl->get_route_map_mgr();
}

subintf_mgr * sdk::get_subintf_mgr() {
   return sdkImpl->get_subintf_mgr();
}

system_mgr * sdk::get_system_mgr() {
   return sdkImpl->get_system_mgr();
}

timeout_mgr * sdk::get_timeout_mgr() {
   return sdkImpl->get_timeout_mgr();
}

vrf_mgr * sdk::get_vrf_mgr() {
   return sdkImpl->get_vrf_mgr();
}

lldp_mgr * sdk::get_lldp_mgr() {
   return sdkImpl->get_lldp_mgr();
}

nexthop_group_tunnel_mgr * sdk::get_nexthop_group_tunnel_mgr() {
   return sdkImpl->get_nexthop_group_tunnel_mgr();
}

}
