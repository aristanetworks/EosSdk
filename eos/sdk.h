// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_SDK_H
#define EOS_SDK_H

#include <eos/agent.h>
#include <eos/base.h>
#include <eos/types/sdk.h>
#include <memory>

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
class hardware_table_mgr;
class intf_mgr_helper;
class intf_mgr;
class intf_counter_mgr;
class ip_intf_mgr;
class ip_route_mgr;
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
 * The following lock lets multiple threads use the SDK
 * simultaneously. This lock uses the RAII idiom; in multithreaded
 * environments, instantiate an eos::sdk_scoped_lock before using any
 * eos::sdk features. Users do not need to grab a lock if they only
 * have one thread, or if they perform all operations on the SDK from
 * the thread which owns the `main_loop`, as the SDK grabs the lock
 * before calling any *_handler callbacks and before performing any
 * internal bookkeeping. Do note that the lock is re-entrant, so
 * attempting to grab the lock twice is fine.
 * Example usage:
 *
 *  Thread 1:
 *    running sdk.main_loop()
 *
 *  Thread 2:
 *    { // Start a new scope to hold the lock
 *      eos::sdk_scoped_lock ssl;
 *      sdk.get_agent_mgr()->status_set("Look", "I can interact with Sysdb!");
 *    } // End the scope, causing the sdk_scoped_lock to be destructed and released
 *
 */
class EOS_SDK_PUBLIC sdk_scoped_lock {
  public:
   sdk_scoped_lock();
   ~sdk_scoped_lock();

  private:
   void * lock;
};


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
class EOS_SDK_PUBLIC sdk {
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
   sdk();

   /**
    * Construct an SDK object with an explicitly set name. If running
    * an agent using this constructor from the CLI, note that the name
    * used here must match the name used in the CLI configuration.
    */
   explicit sdk(std::string const agent_name, void *eossdk_context=NULL);
   ~sdk();

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
   hardware_table_mgr * get_hardware_table_mgr();
   intf_mgr * get_intf_mgr();
   intf_counter_mgr * get_intf_counter_mgr();
   intf_counter_mgr * get_intf_counter_mgr_with_mode(mgr_mode_type_t mode);
   ip_intf_mgr * get_ip_intf_mgr();
   ip_route_mgr * get_ip_route_mgr();
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

   class SdkImpl;
 private:
   std::unique_ptr<SdkImpl> sdkImpl;
};

/**
 * A reference to the default signal handler.
 *
 * This handler is installed for SIGTERM and SIGINT so agents cleanly
 * exit the event loop upon receiving those signals. This function is
 * exposed for agents that install their own signal handlers. If
 * desired, the agent can call this function from its new signal
 * handler, or re-install this if it no longer wants to use a custom
 * signal handler.
 */
void default_signal_handler(int signal) EOS_SDK_PUBLIC;

/**
 * @deprecated This method changes the size of the internal buffer
 * used for enqueuing state updates.
 *
 * It should be used for specific applications that attempt
 * to do large numbers of updates without yielding to the event
 * loop. It should only be rarely used, and future versions of EOS
 * will eliminate the need for this method entirely. At that point,
 * this method will be removed, so please contact the EOS SDK
 * developers before using this method.
 * 
 * To use, call this method at the beginning of your on_initialized()
 * callback.
 * 
 * This method takes in a number of bytes that the buffer should
 * be. By default, this buffer size is set to 8.3 MB (which the kernel
 * doubles to 16.7 MB) - the max kernel buffer size.
 * 
 * Unlike setsockopt, the number of bytes you pass to this function is
 * NOT doubled for setting the actual socket buffer size. Note though
 * that the new buffer size may not exactly match the requested buffer
 * size, but we guarantee that it the new size is at least as big as
 * the requested size.
 */
void internal_connection_buffer_size_is(uint32_t bytes) EOS_SDK_PUBLIC;

/**
 * This function enables (default) or disables API Tracing. Tracing
 * begins once an sdk object is created; to avoid all tracing, use this
 * before instantiating an sdk object.
 */
void api_trace_enable_is(bool new_api_trace) EOS_SDK_PUBLIC;

/**
 * This function does the same as the above, but controls whether function
 * parameters get traced or not.
 */
void param_trace_enable_is(bool new_param_trace) EOS_SDK_PUBLIC;

/**
 * Change the size of quick trace ring buffers, per level. Default 10kb
 * per level. If this is used before sdk object constructor, the constructor
 * will reset the buffers to default size.
 */
void api_trace_buffer_sizes_is(int(&size_spec)[10]) EOS_SDK_PUBLIC;
}

#include <eos/inline/sdk.h>

#endif // EOS_SDK_H
