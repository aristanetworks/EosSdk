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

#include "eos/acl.h"
#include "eos/aresolve.h"
#include "eos/bfd.h"
#include "eos/bgp.h"
#include "eos/bgp_path.h"
#include "eos/class_map.h"
#include "eos/decap_group.h"
#include "eos/directflow.h"
#include "eos/eapi.h"
#include "eos/eth.h"
#include "eos/eth_intf.h"
#include "eos/eth_lag_intf.h"
#include "eos/eth_phy_intf.h"
#include "eos/fib.h"
#include "eos/hardware_table.h"
#include "eos/intf.h"
#include "eos/ip.h"
#include "eos/ip_route.h"
#include "eos/lldp.h"
#include "eos/macsec.h"
#include "eos/mac_table.h"
#include "eos/mlag.h"
#include "eos/mpls.h"
#include "eos/mpls_route.h"
#include "eos/mpls_vrf_label.h"
#include "eos/neighbor_table.h"
#include "eos/nexthop_group.h"
#include "eos/nexthop_group_tunnel.h"
#include "eos/policy_map.h"
#include "eos/route_map.h"
#include "eos/subintf.h"
#include "eos/vrf.h"

#include "eos/types/sdk.h"
#include "eos/types/acl.h"
#include "eos/types/structured_filter.h"
#include "eos/types/aresolve.h"
#include "eos/types/bfd.h"
#include "eos/types/bgp.h"
#include "eos/types/bgp_path.h"
#include "eos/types/class_map.h"
#include "eos/types/decap_group.h"
#include "eos/types/directflow.h"
#include "eos/types/eapi.h"
#include "eos/types/eth.h"
#include "eos/types/eth_intf.h"
#include "eos/types/eth_lag_intf.h"
#include "eos/types/eth_phy_intf.h"
#include "eos/types/fib.h"
#include "eos/types/hardware_table.h"
#include "eos/types/intf.h"
#include "eos/types/ip.h"
#include "eos/types/ip_route.h"
#include "eos/types/lldp.h"
#include "eos/types/macsec.h"
#include "eos/types/mac_table.h"
#include "eos/types/mlag.h"
#include "eos/types/mpls.h"
#include "eos/types/mpls_route.h"
#include "eos/types/mpls_vrf_label.h"
#include "eos/types/neighbor_table.h"
#include "eos/types/nexthop_group.h"
#include "eos/types/nexthop_group_tunnel.h"
#include "eos/types/policy_map.h"
#include "eos/types/route_map.h"
#include "eos/types/subintf.h"
#include "eos/types/vrf.h"

#include "eos/types/acl_impl.h"
#include "eos/types/structured_filter_impl.h"
#include "eos/types/aresolve_impl.h"
#include "eos/types/bfd_impl.h"
#include "eos/types/bgp_impl.h"
#include "eos/types/bgp_path_impl.h"
#include "eos/types/class_map_impl.h"
#include "eos/types/decap_group_impl.h"
#include "eos/types/directflow_impl.h"
#include "eos/types/eapi_impl.h"
#include "eos/types/eth_impl.h"
#include "eos/types/eth_intf_impl.h"
#include "eos/types/eth_lag_intf_impl.h"
#include "eos/types/eth_phy_intf_impl.h"
#include "eos/types/fib_impl.h"
#include "eos/types/hardware_table_impl.h"
#include "eos/types/intf_impl.h"
#include "eos/types/ip_impl.h"
#include "eos/types/ip_route_impl.h"
#include "eos/types/lldp_impl.h"
#include "eos/types/macsec_impl.h"
#include "eos/types/mac_table_impl.h"
#include "eos/types/mlag_impl.h"
#include "eos/types/mpls_impl.h"
#include "eos/types/mpls_route_impl.h"
#include "eos/types/mpls_vrf_label_impl.h"
#include "eos/types/neighbor_table_impl.h"
#include "eos/types/nexthop_group_impl.h"
#include "eos/types/nexthop_group_tunnel_impl.h"
#include "eos/types/policy_map_impl.h"
#include "eos/types/route_map_impl.h"
#include "eos/types/subintf_impl.h"
#include "eos/types/vrf_impl.h"

#include "eos/inline/types/acl_impl.h"
#include "eos/inline/types/structured_filter_impl.h"
#include "eos/inline/types/aresolve_impl.h"
#include "eos/inline/types/bfd_impl.h"
#include "eos/inline/types/bgp_impl.h"
#include "eos/inline/types/bgp_path_impl.h"
#include "eos/inline/types/class_map_impl.h"
#include "eos/inline/types/decap_group_impl.h"
#include "eos/inline/types/directflow_impl.h"
#include "eos/inline/types/eapi_impl.h"
#include "eos/inline/types/eth_impl.h"
#include "eos/inline/types/eth_intf_impl.h"
#include "eos/inline/types/eth_lag_intf_impl.h"
#include "eos/inline/types/eth_phy_intf_impl.h"
#include "eos/inline/types/fib_impl.h"
#include "eos/inline/types/hardware_table_impl.h"
#include "eos/inline/types/intf_impl.h"
#include "eos/inline/types/ip_impl.h"
#include "eos/inline/types/ip_route_impl.h"
#include "eos/inline/types/lldp_impl.h"
#include "eos/inline/types/macsec_impl.h"
#include "eos/inline/types/mac_table_impl.h"
#include "eos/inline/types/mlag_impl.h"
#include "eos/inline/types/mpls_impl.h"
#include "eos/inline/types/mpls_route_impl.h"
#include "eos/inline/types/mpls_vrf_label_impl.h"
#include "eos/inline/types/neighbor_table_impl.h"
#include "eos/inline/types/nexthop_group_impl.h"
#include "eos/inline/types/nexthop_group_tunnel_impl.h"
#include "eos/inline/types/policy_map_impl.h"
#include "eos/inline/types/route_map_impl.h"
#include "eos/inline/types/subintf_impl.h"
#include "eos/inline/types/vrf_impl.h"

#include "eos/inline/types/sdk.h"
#include "eos/inline/types/acl.h"
#include "eos/inline/types/structured_filter.h"
#include "eos/inline/types/aresolve.h"
#include "eos/inline/types/bfd.h"
#include "eos/inline/types/bgp.h"
#include "eos/inline/types/bgp_path.h"
#include "eos/inline/types/class_map.h"
#include "eos/inline/types/decap_group.h"
#include "eos/inline/types/directflow.h"
#include "eos/inline/types/eapi.h"
#include "eos/inline/types/eth.h"
#include "eos/inline/types/eth_intf.h"
#include "eos/inline/types/eth_lag_intf.h"
#include "eos/inline/types/eth_phy_intf.h"
#include "eos/inline/types/fib.h"
#include "eos/inline/types/hardware_table.h"
#include "eos/inline/types/intf.h"
#include "eos/inline/types/ip.h"
#include "eos/inline/types/ip_route.h"
#include "eos/inline/types/lldp.h"
#include "eos/inline/types/macsec.h"
#include "eos/inline/types/mac_table.h"
#include "eos/inline/types/mlag.h"
#include "eos/inline/types/mpls.h"
#include "eos/inline/types/mpls_route.h"
#include "eos/inline/types/mpls_vrf_label.h"
#include "eos/inline/types/neighbor_table.h"
#include "eos/inline/types/nexthop_group.h"
#include "eos/inline/types/nexthop_group_tunnel.h"
#include "eos/inline/types/policy_map.h"
#include "eos/inline/types/route_map.h"
#include "eos/inline/types/subintf.h"
#include "eos/inline/types/vrf.h"

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

xcvr_mgr * sdk::get_xcvr_mgr() {
   return sdkImpl->get_xcvr_mgr();
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
