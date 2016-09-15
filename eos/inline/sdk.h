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
   GET_MGR(acl)
}

inline agent_mgr * sdk::get_agent_mgr() {
   GET_MGR(agent)
}

inline aresolve_mgr * sdk::get_aresolve_mgr() {
   GET_MGR(aresolve)
}

inline bfd_session_mgr * sdk::get_bfd_session_mgr() {
   GET_MGR(bfd_session)
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

inline eth_intf_mgr * sdk::get_eth_intf_mgr() {
   GET_MGR(eth_intf)
}

inline eth_lag_intf_mgr * sdk::get_eth_lag_intf_mgr() {
   GET_MGR(eth_lag_intf)
}

inline eth_phy_intf_mgr * sdk::get_eth_phy_intf_mgr() {
   GET_MGR(eth_phy_intf)
}

inline eth_phy_intf_counter_mgr * sdk::get_eth_phy_intf_counter_mgr() {
   print_profiles::add_profile("eth_phy_intf");
   if (!eth_phy_intf_counter_mgr_) {
      init_eth_phy_intf_counter_mgr();
   }
   return eth_phy_intf_counter_mgr_;
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
   GET_MGR(intf)
}

inline intf_counter_mgr * sdk::get_intf_counter_mgr() {
   print_profiles::add_profile("intf");
   if (!intf_counter_mgr_) {
      init_intf_counter_mgr();
   }
   return intf_counter_mgr_;
}

inline ip_intf_mgr * sdk::get_ip_intf_mgr() {
   GET_MGR(ip_intf)
}

inline ip_route_mgr * sdk::get_ip_route_mgr() {
   GET_MGR(ip_route)
}

inline intf_mgr_helper * sdk::get_intf_mgr_helper() {
   print_profiles::add_profile("IntfMgrHelper");
   if (!intf_mgr_helper_) {
      init_intf_mgr_helper();
   }
   return intf_mgr_helper_;
}

inline mac_table_mgr * sdk::get_mac_table_mgr() {
   GET_MGR(mac_table)
}

inline mlag_mgr * sdk::get_mlag_mgr() {
   GET_MGR(mlag)
}

inline mount_mgr * sdk::get_mount_mgr() {
   if (!mount_mgr_) {
      init_mount_mgr();
   }
   return mount_mgr_;
}

inline mpls_route_mgr * sdk::get_mpls_route_mgr() {
   GET_MGR(mpls_route)
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
   GET_MGR(subintf)
}

inline system_mgr * sdk::get_system_mgr() {
   GET_MGR(system)
}

inline timeout_mgr * sdk::get_timeout_mgr() {
   if (!timeout_mgr_) {
      init_timeout_mgr();
   }
   return timeout_mgr_;
}

inline vrf_mgr * sdk::get_vrf_mgr() {
   GET_MGR(vrf)
}


inline lldp_mgr * sdk::get_lldp_mgr() {
   GET_MGR(lldp)
}

}

#endif // EOS_INLINE_SDK_H
