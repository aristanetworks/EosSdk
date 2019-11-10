// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_SDK_H
#define EOS_INLINE_SDK_H

#include <eos/panic.h>
#include <eos/exception.h>

#define GET_MGR(__mgr__)          \
   print_profiles::add_profile( #__mgr__ );       \
   if (! __mgr__ ## _mgr_) {      \
      init_ ## __mgr__ ## _mgr(); \
   }                              \
   return __mgr__ ## _mgr_;       \

#define GET_NO_MOUNT_MGR(__mgr__)          \
   if (! __mgr__ ## _mgr_) {      \
      init_ ## __mgr__ ## _mgr(); \
   }                              \
   return __mgr__ ## _mgr_;       \

namespace eos {

// To facilitate the making of customized sysdb-mount-profiles (in place of the
// brute-force one "EosSdk", see /usr/lib/SysdbMountProfiles/EosSdkAll), an app can
// be started with the env var EOS_PRINT_PROFILES_AND_EXIT pointing to a filename
// where the profile should be written, then exit.
class EOS_SDK_PUBLIC print_profiles {
  public:
   static void set_print_profiles(const char* name);
   static void add_profile(const char * profile);
   static void write_profiles(); // will call exit() after printing

  private:
   static FILE* print_profiles_fp;
   static std::map<std::string, bool> profiles_to_print;
   static const char* eossdk_progname;
};

inline std::string sdk::name() {
   return name_;
}

inline acl_mgr * sdk::get_acl_mgr() {
   print_profiles::add_profile("IntfMgrHelper");
   GET_MGR(acl)
}

inline agent_mgr * sdk::get_agent_mgr() {
   GET_MGR(agent)
}

inline aresolve_mgr * sdk::get_aresolve_mgr() {
   GET_NO_MOUNT_MGR(aresolve)
}

inline bfd_session_mgr * sdk::get_bfd_session_mgr() {
   print_profiles::add_profile("IntfMgrHelper");
   GET_MGR(bfd_session)
}

inline bgp_path_mgr * sdk::get_bgp_path_mgr() {
   GET_MGR(bgp_path)
}

inline class_map_mgr * sdk::get_class_map_mgr() {
   GET_MGR(class_map)
}

inline decap_group_mgr * sdk::get_decap_group_mgr() {
   GET_MGR(decap_group)
}

inline directflow_mgr * sdk::get_directflow_mgr() {
   GET_MGR(directflow)
}

inline eapi_mgr * sdk::get_eapi_mgr() {
   GET_NO_MOUNT_MGR(eapi)
}

inline eth_intf_mgr * sdk::get_eth_intf_mgr() {
   print_profiles::add_profile("IntfMgrHelper");
   GET_MGR(eth_intf)
}

inline eth_lag_intf_mgr * sdk::get_eth_lag_intf_mgr() {
   print_profiles::add_profile("IntfMgrHelper");
   GET_MGR(eth_lag_intf)
}

inline eth_phy_intf_mgr * sdk::get_eth_phy_intf_mgr() {
   print_profiles::add_profile("IntfMgrHelper");
   GET_MGR(eth_phy_intf)
}

inline eth_phy_intf_counter_mgr * sdk::get_eth_phy_intf_counter_mgr() {
   print_profiles::add_profile("IntfMgrHelper");
   print_profiles::add_profile("eth_phy_intf"); // _counter does not have own profile
   GET_NO_MOUNT_MGR(eth_phy_intf_counter)
}

inline event_loop * sdk::get_event_loop() {
   // if setup (env) to display needed sysdb profiles, this will print them and exit
   print_profiles::write_profiles();
   if (!event_loop_) {
      init_event_loop();
   }
   return event_loop_;
}

inline fib_mgr * sdk::get_fib_mgr(mgr_mode_type_t mode) {
   // cannot use GET_MGR because init_ takes an arg
   print_profiles::add_profile("fib");
   if (!fib_mgr_) {
      init_fib_mgr(mode);
   }
   return fib_mgr_;
}


inline hardware_table_mgr * sdk::get_hardware_table_mgr() {
   GET_MGR(hardware_table)
}

inline intf_mgr * sdk::get_intf_mgr() {
   print_profiles::add_profile("IntfMgrHelper");
   GET_MGR(intf)
}

inline intf_counter_mgr * sdk::get_intf_counter_mgr() {
   print_profiles::add_profile("intf");
   GET_NO_MOUNT_MGR(intf_counter)
}

inline ip_intf_mgr * sdk::get_ip_intf_mgr() {
   print_profiles::add_profile("intf");
   GET_MGR(ip_intf)
}

inline ip_route_mgr * sdk::get_ip_route_mgr() {
   GET_MGR(ip_route)
}

// Unconventional naming: should be "intf_helper_mgr" and the profile name
// should be renamed too, except that there might be customers out there
// with it in their custom profiles (why not merge it into intf_mgr?).
inline intf_mgr_helper * sdk::get_intf_mgr_helper() {
   print_profiles::add_profile("IntfMgrHelper");
   if (!intf_mgr_helper_) {
      init_intf_mgr_helper();
   }
   return intf_mgr_helper_;
}

inline macsec_mgr * sdk::get_macsec_mgr() {
   GET_MGR(macsec)
}

inline mac_table_mgr * sdk::get_mac_table_mgr() {
   GET_MGR(mac_table)
}

inline mlag_mgr * sdk::get_mlag_mgr() {
   GET_MGR(mlag)
}

inline mount_mgr * sdk::get_mount_mgr() {
   GET_NO_MOUNT_MGR(mount);
}

inline mpls_route_mgr * sdk::get_mpls_route_mgr() {
   GET_MGR(mpls_route)
}

inline mpls_vrf_label_mgr * sdk::get_mpls_vrf_label_mgr() {
   GET_MGR(mpls_vrf_label)
}

inline neighbor_table_mgr * sdk::get_neighbor_table_mgr() {
   GET_MGR(neighbor_table)
}

inline nexthop_group_mgr * sdk::get_nexthop_group_mgr() {
   GET_MGR(nexthop_group)
}

inline policy_map_mgr * sdk::get_policy_map_mgr() {
   GET_MGR(policy_map)
}

inline subintf_mgr * sdk::get_subintf_mgr() {
   print_profiles::add_profile("IntfMgrHelper");
   GET_MGR(subintf)
}

inline system_mgr * sdk::get_system_mgr() {
   GET_MGR(system)
}

inline timeout_mgr * sdk::get_timeout_mgr() {
   GET_NO_MOUNT_MGR(timeout);
}

inline vrf_mgr * sdk::get_vrf_mgr() {
   GET_MGR(vrf)
}


inline lldp_mgr * sdk::get_lldp_mgr() {
   GET_MGR(lldp)
}

inline nexthop_group_tunnel_mgr * sdk::get_nexthop_group_tunnel_mgr() {
   GET_MGR(nexthop_group_tunnel)
}

}

#endif // EOS_INLINE_SDK_H
