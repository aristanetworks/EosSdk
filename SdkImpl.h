// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_SDK_IMPL_H
#define EOS_SDK_IMPL_H

#include <eos/agent.h>
#include <eos/base.h>
#include <eos/sdk.h>
#include <eos/types/sdk.h>
#include <eos/panic.h>
#include <eos/exception.h>

namespace eos {

class acl_mgr;
class aresolve_mgr;
class bfd_session_mgr;
class bgp_mgr;
class bgp_path_mgr;
class class_map_mgr;
class decap_group_mgr;
class directflow_mgr;
class eapi_mgr;
class eth_intf_mgr;
class eth_lag_intf_mgr;
class eth_phy_intf_mgr;
class eth_phy_intf_counter_mgr;
class event_loop;
class fib_mgr;
class fpga_mgr;
class ham_mgr;
class hardware_table_mgr;
class intf_mgr_helper;
class intf_mgr;
class intf_counter_mgr;
class ip_intf_mgr;
class ip_route_mgr;
class l1_source_mgr;
class lldp_mgr;
class macsec_mgr;
class mac_table_mgr;
class mlag_mgr;
class mount_mgr;
class mpls_route_mgr;
class mpls_vrf_label_mgr;
class neighbor_table_mgr;
class nexthop_group_mgr;
class nexthop_group_tunnel_mgr;
class policy_map_mgr;
class route_map_mgr;
class subintf_mgr;
class system_mgr;
class timeout_mgr;
class vrf_mgr;
class xcvr_mgr;

/**
 * Manages the different managers of the SDK. One manager of each
 * type can be linked to a SDK object.
 *
 * As managers must be initialized at the beginning of the program, the init_*_mgr()
 * functions should be called for any managers you plan to use.
 * Since the get_*_mgr() functions also call their respective init_*_mgr() functions
 * if necessary, accessing the managers at the beginning of the code (before the
 * agent_loop is called) is enough to initialize them.
 */
class EOS_SDK_PUBLIC sdk::SdkImpl {
 public:
   /**
    * Constructs a top level SDK object.
    *
    * This constructor will read the AGENT_PROCESS_NAME environment
    * variable to determine the operational name of the agent. When
    * running this agent via the CLI, this variable will be set
    * automatically. If running an agent that uses this constructor
    * manually, the AGENT_PROCESS_NAME variable must be set.
    */
   SdkImpl();

   /**
    * Construct an SDK object with an explicitly set name. If running
    * an agent using this constructor from the CLI, note that the name
    * used here must match the name used in the CLI configuration.
    */
   explicit SdkImpl(std::string const agent_name, void *eossdk_context=NULL);
   ~SdkImpl();

   void initialize_context();

   /**
    * Return the name of this SDK object.
    *
    * This variable is used to register the process with EOS's various
    * agent services, including the process name, the name used in the
    * log file, as well as the namespace for custom agent
    * configuration and status.
    */
   std::string name();

   /**
    * Begin the agent's event loop.
    *
    * This function initializes the underlying infrastructure for your
    * agent. It first registers itself as an EOS agent, then
    * synchronizes any needed state with Sysdb, and finally starts the
    * event loop. Before this function is called, no managers are
    * valid (as no state has been synchronized with Sysdb), and no
    * handlers will be triggered (as the event loop is not
    * running). This function will not return unless the agent is
    * disabled or it explicitly calls the agent_mgr's exit() code.
    */
   void main_loop(int argc, char ** argv);

   void init_acl_mgr();
   void init_agent_mgr();
   void init_aresolve_mgr();
   void init_bfd_session_mgr();
   void init_bgp_mgr();
   void init_bgp_path_mgr();
   void init_class_map_mgr();
   void init_decap_group_mgr();
   void init_directflow_mgr();
   void init_eapi_mgr();
   void init_eth_intf_mgr();
   void init_eth_lag_intf_mgr();
   void init_eth_phy_intf_mgr();
   void init_eth_phy_intf_counter_mgr();
   void init_event_loop();
   void init_fib_mgr(mgr_mode_type_t mode=MODE_TYPE_READ_ONLY);
   void init_fpga_mgr();
   void init_ham_mgr();
   void init_hardware_table_mgr();
   void init_intf_mgr();
   void init_intf_counter_mgr();
   void init_ip_intf_mgr();
   void init_ip_route_mgr();
   void init_l1_source_mgr();
   void init_lldp_mgr();
   void init_macsec_mgr();
   void init_mac_table_mgr();
   void init_mlag_mgr();
   void init_mpls_route_mgr();
   void init_mpls_vrf_label_mgr();
   void init_neighbor_table_mgr();
   void init_nexthop_group_mgr();
   void init_nexthop_group_tunnel_mgr();
   void init_policy_map_mgr();
   void init_route_map_mgr();
   void init_subintf_mgr();
   void init_system_mgr();
   void init_timeout_mgr();
   void init_vrf_mgr();
   void init_xcvr_mgr();

   acl_mgr * get_acl_mgr();
   agent_mgr * get_agent_mgr();
   aresolve_mgr * get_aresolve_mgr();
   bfd_session_mgr * get_bfd_session_mgr();
   bgp_mgr * get_bgp_mgr();
   bgp_path_mgr * get_bgp_path_mgr();
   class_map_mgr * get_class_map_mgr();
   decap_group_mgr * get_decap_group_mgr();
   directflow_mgr * get_directflow_mgr();
   eapi_mgr * get_eapi_mgr();
   eth_intf_mgr * get_eth_intf_mgr();
   eth_lag_intf_mgr * get_eth_lag_intf_mgr();
   eth_phy_intf_mgr * get_eth_phy_intf_mgr();
   eth_phy_intf_counter_mgr * get_eth_phy_intf_counter_mgr();
   event_loop * get_event_loop();
   fib_mgr * get_fib_mgr(mgr_mode_type_t mode=MODE_TYPE_READ_ONLY);
   fpga_mgr * get_fpga_mgr();
   ham_mgr * get_ham_mgr();
   hardware_table_mgr * get_hardware_table_mgr();
   intf_mgr * get_intf_mgr();
   intf_counter_mgr * get_intf_counter_mgr();
   ip_intf_mgr * get_ip_intf_mgr();
   ip_route_mgr * get_ip_route_mgr();
   l1_source_mgr * get_l1_source_mgr();
   lldp_mgr * get_lldp_mgr();
   macsec_mgr * get_macsec_mgr();
   mac_table_mgr * get_mac_table_mgr();
   mlag_mgr * get_mlag_mgr();
   mount_mgr * get_mount_mgr();
   mpls_route_mgr * get_mpls_route_mgr();
   mpls_vrf_label_mgr * get_mpls_vrf_label_mgr();
   neighbor_table_mgr * get_neighbor_table_mgr();
   nexthop_group_mgr * get_nexthop_group_mgr();
   nexthop_group_tunnel_mgr * get_nexthop_group_tunnel_mgr();
   policy_map_mgr * get_policy_map_mgr();
   route_map_mgr * get_route_map_mgr();
   subintf_mgr * get_subintf_mgr();
   system_mgr * get_system_mgr();
   timeout_mgr * get_timeout_mgr();
   vrf_mgr * get_vrf_mgr();
   xcvr_mgr * get_xcvr_mgr();

 private:
   void init_mount_mgr();
   
   void init_intf_mgr_helper();
   intf_mgr_helper * get_intf_mgr_helper();

   EOS_SDK_DISALLOW_COPY_CTOR(SdkImpl);
   acl_mgr * acl_mgr_;
   agent_mgr * agent_mgr_;
   aresolve_mgr * aresolve_mgr_;
   bfd_session_mgr * bfd_session_mgr_;
   bgp_mgr * bgp_mgr_;
   bgp_path_mgr * bgp_path_mgr_;
   class_map_mgr * class_map_mgr_;
   decap_group_mgr * decap_group_mgr_;
   directflow_mgr * directflow_mgr_;
   eapi_mgr * eapi_mgr_;
   eth_intf_mgr * eth_intf_mgr_;
   eth_phy_intf_mgr * eth_phy_intf_mgr_;
   eth_phy_intf_counter_mgr * eth_phy_intf_counter_mgr_;
   eth_lag_intf_mgr * eth_lag_intf_mgr_;
   event_loop * event_loop_;
   fib_mgr * fib_mgr_;
   fpga_mgr * fpga_mgr_;
   ham_mgr * ham_mgr_;
   hardware_table_mgr * hardware_table_mgr_;
   intf_mgr_helper * intf_mgr_helper_;
   intf_mgr * intf_mgr_;
   intf_counter_mgr * intf_counter_mgr_;
   ip_intf_mgr * ip_intf_mgr_;
   ip_route_mgr * ip_route_mgr_;
   l1_source_mgr * l1_source_mgr_;
   lldp_mgr * lldp_mgr_;
   macsec_mgr * macsec_mgr_;
   mac_table_mgr * mac_table_mgr_;
   mlag_mgr * mlag_mgr_;
   mount_mgr * mount_mgr_;
   mpls_route_mgr * mpls_route_mgr_;
   mpls_vrf_label_mgr * mpls_vrf_label_mgr_;
   neighbor_table_mgr * neighbor_table_mgr_;
   nexthop_group_mgr * nexthop_group_mgr_;
   nexthop_group_tunnel_mgr * nexthop_group_tunnel_mgr_;
   policy_map_mgr * policy_map_mgr_;
   route_map_mgr * route_map_mgr_;
   subintf_mgr * subintf_mgr_;
   system_mgr * system_mgr_;
   timeout_mgr * timeout_mgr_;
   vrf_mgr * vrf_mgr_;
   xcvr_mgr * xcvr_mgr_;

   std::string name_;
   void * eossdk_context_;

   friend class mount_mgr;
};

#define ENSURE_INITIALIZED()                                            \
   TRACE7(__PRETTY_FUNCTION__);                                         \
   eos::sdk_scoped_lock ssl;                                            \
   ensureInitialized();                                                 \

#define GET_MGR(__mgr__)          \
   eos::print_profiles::add_profile( #__mgr__ );      \
   if (! __mgr__ ## _mgr_) {      \
      init_ ## __mgr__ ## _mgr(); \
   }                              \
   return __mgr__ ## _mgr_;       \

#define GET_NO_MOUNT_MGR(__mgr__)          \
   if (! __mgr__ ## _mgr_) {      \
      init_ ## __mgr__ ## _mgr(); \
   }                              \
   return __mgr__ ## _mgr_;       \

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

inline std::string sdk::SdkImpl::name() {
   return name_;
}

inline acl_mgr * sdk::SdkImpl::get_acl_mgr() {
   eos::print_profiles::add_profile("IntfMgrHelper");
   GET_MGR(acl)
}

inline agent_mgr * sdk::SdkImpl::get_agent_mgr() {
   GET_MGR(agent)
}

inline aresolve_mgr * sdk::SdkImpl::get_aresolve_mgr() {
   GET_NO_MOUNT_MGR(aresolve)
}

inline bfd_session_mgr * sdk::SdkImpl::get_bfd_session_mgr() {
   eos::print_profiles::add_profile("IntfMgrHelper");
   GET_MGR(bfd_session)
}

inline bgp_mgr * sdk::SdkImpl::get_bgp_mgr() {
   GET_MGR(bgp)
}

inline bgp_path_mgr * sdk::SdkImpl::get_bgp_path_mgr() {
   GET_MGR(bgp_path)
}

inline class_map_mgr * sdk::SdkImpl::get_class_map_mgr() {
   GET_MGR(class_map)
}

inline decap_group_mgr * sdk::SdkImpl::get_decap_group_mgr() {
   GET_MGR(decap_group)
}

inline directflow_mgr * sdk::SdkImpl::get_directflow_mgr() {
   GET_MGR(directflow)
}

inline eapi_mgr * sdk::SdkImpl::get_eapi_mgr() {
   GET_NO_MOUNT_MGR(eapi)
}

inline eth_intf_mgr * sdk::SdkImpl::get_eth_intf_mgr() {
   eos::print_profiles::add_profile("IntfMgrHelper");
   GET_MGR(eth_intf)
}

inline eth_lag_intf_mgr * sdk::SdkImpl::get_eth_lag_intf_mgr() {
   eos::print_profiles::add_profile("IntfMgrHelper");
   GET_MGR(eth_lag_intf)
}

inline eth_phy_intf_mgr * sdk::SdkImpl::get_eth_phy_intf_mgr() {
   eos::print_profiles::add_profile("IntfMgrHelper");
   GET_MGR(eth_phy_intf)
}

inline eth_phy_intf_counter_mgr * sdk::SdkImpl::get_eth_phy_intf_counter_mgr() {
   eos::print_profiles::add_profile("IntfMgrHelper");
   eos::print_profiles::add_profile("eth_phy_intf");
   GET_NO_MOUNT_MGR(eth_phy_intf_counter)
}

inline event_loop * sdk::SdkImpl::get_event_loop() {
   // if setup (env) to display needed sysdb profiles, this will print them and exit
   eos::print_profiles::write_profiles();
   if (!event_loop_) {
      init_event_loop();
   }
   return event_loop_;
}

inline fib_mgr * sdk::SdkImpl::get_fib_mgr(mgr_mode_type_t mode) {
   // cannot use GET_MGR because init_ takes an arg
   eos::print_profiles::add_profile("fib");
   if (!fib_mgr_) {
      init_fib_mgr(mode);
   }
   return fib_mgr_;
}

inline fpga_mgr * sdk::SdkImpl::get_fpga_mgr() {
   GET_MGR(fpga)
}

inline ham_mgr * sdk::SdkImpl::get_ham_mgr() {
   GET_MGR(ham)
}

inline hardware_table_mgr * sdk::SdkImpl::get_hardware_table_mgr() {
   GET_MGR(hardware_table)
}

inline intf_mgr * sdk::SdkImpl::get_intf_mgr() {
   eos::print_profiles::add_profile("IntfMgrHelper");
   GET_MGR(intf)
}

inline intf_counter_mgr * sdk::SdkImpl::get_intf_counter_mgr() {
   eos::print_profiles::add_profile("intf");
   GET_NO_MOUNT_MGR(intf_counter)
}

inline ip_intf_mgr * sdk::SdkImpl::get_ip_intf_mgr() {
   eos::print_profiles::add_profile("intf");
   GET_MGR(ip_intf)
}

inline ip_route_mgr * sdk::SdkImpl::get_ip_route_mgr() {
   GET_MGR(ip_route)
}

// Unconventional naming: should be "intf_helper_mgr" and the profile name
// should be renamed too, except that there might be customers out there 
// with it in their custom profiles (why not merge it into intf_mgr?).
inline intf_mgr_helper * sdk::SdkImpl::get_intf_mgr_helper() {
   eos::print_profiles::add_profile("IntfMgrHelper");
   if (!intf_mgr_helper_) {
      init_intf_mgr_helper();
   }
   return intf_mgr_helper_;
}

inline l1_source_mgr * sdk::SdkImpl::get_l1_source_mgr() {
   GET_MGR(l1_source)
}

inline macsec_mgr * sdk::SdkImpl::get_macsec_mgr() {
   GET_MGR(macsec)
}

inline mac_table_mgr * sdk::SdkImpl::get_mac_table_mgr() {
   GET_MGR(mac_table)
}

inline mlag_mgr * sdk::SdkImpl::get_mlag_mgr() {
   GET_MGR(mlag)
}

inline mount_mgr * sdk::SdkImpl::get_mount_mgr() {
   GET_NO_MOUNT_MGR(mount);
}

inline mpls_route_mgr * sdk::SdkImpl::get_mpls_route_mgr() {
   GET_MGR(mpls_route)
}

inline mpls_vrf_label_mgr * sdk::SdkImpl::get_mpls_vrf_label_mgr() {
   GET_MGR(mpls_vrf_label)
}

inline neighbor_table_mgr * sdk::SdkImpl::get_neighbor_table_mgr() {
   GET_MGR(neighbor_table)
}

inline nexthop_group_mgr * sdk::SdkImpl::get_nexthop_group_mgr() {
   GET_MGR(nexthop_group)
}

inline policy_map_mgr * sdk::SdkImpl::get_policy_map_mgr() {
   GET_MGR(policy_map)
}

inline route_map_mgr * sdk::SdkImpl::get_route_map_mgr() {
   GET_MGR(route_map)
}

inline subintf_mgr * sdk::SdkImpl::get_subintf_mgr() {
   eos::print_profiles::add_profile("IntfMgrHelper");
   GET_MGR(subintf)
}

inline system_mgr * sdk::SdkImpl::get_system_mgr() {
   GET_MGR(system)
}

inline timeout_mgr * sdk::SdkImpl::get_timeout_mgr() {
   GET_NO_MOUNT_MGR(timeout);
}

inline vrf_mgr * sdk::SdkImpl::get_vrf_mgr() {
   GET_MGR(vrf)
}


inline lldp_mgr * sdk::SdkImpl::get_lldp_mgr() {
   GET_MGR(lldp)
}

inline nexthop_group_tunnel_mgr * sdk::SdkImpl::get_nexthop_group_tunnel_mgr() {
   GET_MGR(nexthop_group_tunnel)
}

inline xcvr_mgr * sdk::SdkImpl::get_xcvr_mgr() {
   GET_MGR( xcvr )
}

}

#endif // EOS_SDK_H
