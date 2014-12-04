// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_SDK_H
#define EOS_SDK_H

#include <eos/agent.h>
#include <eos/base.h>

namespace eos {

class acl_mgr;
class aresolve_mgr;
class class_map_mgr;
class decap_group_mgr;
class directflow_mgr;
class eth_intf_mgr;
class eth_lag_intf_mgr;
class eth_phy_intf_mgr;
class eth_phy_intf_counter_mgr;
class event_loop;
class fib_mgr;
class intf_mgr;
class intf_counter_mgr;
class ip_intf_mgr;
class ip_route_mgr;
class mac_table_mgr;
class mlag_mgr;
class mount_mgr;
class mpls_route_mgr;
class neighbor_table_mgr;
class nexthop_group_mgr;
class policy_map_mgr;
class system_mgr;
class timeout_mgr;


/**
 * The following lock lets multiple threads use the SDK
 * simultaneously. This lock uses the RAII idiom; in multithreaded
 * environments, instantiate an eos::sdk_scoped_lock before using any
 * eos::sdk features. Users do not need to grab a lock if they only
 * have one thread, or if they perform all operations on the SDK from
 * the thread which owns the `main_loop`, as the SDK grabs the lock
 * before calling any *_handler callbacks and before performing any
 * internal bookkeeping. Do note that the lock is not re-entrant, so
 * attempting to grab the lock twice will cause a deadlock. 
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
 * Manages the differents managers of the SDK. One manager of each
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
   explicit sdk(std::string const agent_name);
   ~sdk();
   
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
   void init_class_map_mgr();
   void init_decap_group_mgr();
   void init_directflow_mgr();
   void init_eth_intf_mgr();
   void init_eth_lag_intf_mgr();
   void init_eth_phy_intf_mgr();
   void init_eth_phy_intf_counter_mgr();
   void init_event_loop();
   void init_fib_mgr(mgr_mode_type_t mode=MODE_TYPE_READ_ONLY);
   void init_intf_mgr();
   void init_intf_counter_mgr();
   void init_ip_intf_mgr();
   void init_ip_route_mgr();
   void init_mac_table_mgr();
   void init_mlag_mgr();
   void init_mpls_route_mgr();
   void init_neighbor_table_mgr();
   void init_nexthop_group_mgr();
   void init_policy_map_mgr();
   void init_system_mgr();
   void init_timeout_mgr();
   
   acl_mgr * get_acl_mgr();
   agent_mgr * get_agent_mgr();
   aresolve_mgr * get_aresolve_mgr();
   class_map_mgr * get_class_map_mgr();
   decap_group_mgr * get_decap_group_mgr();
   directflow_mgr * get_directflow_mgr();
   eth_intf_mgr * get_eth_intf_mgr();
   eth_lag_intf_mgr * get_eth_lag_intf_mgr();
   eth_phy_intf_mgr * get_eth_phy_intf_mgr();
   eth_phy_intf_counter_mgr * get_eth_phy_intf_counter_mgr();
   event_loop * get_event_loop();
   fib_mgr * get_fib_mgr(mgr_mode_type_t mode=MODE_TYPE_READ_ONLY);
   intf_mgr * get_intf_mgr();
   intf_counter_mgr * get_intf_counter_mgr();
   ip_intf_mgr * get_ip_intf_mgr();
   ip_route_mgr * get_ip_route_mgr();
   mac_table_mgr * get_mac_table_mgr();
   mlag_mgr * get_mlag_mgr();
   // TODO: move back to private (BUG86400)
   mount_mgr * get_mount_mgr();
   mpls_route_mgr * get_mpls_route_mgr();
   neighbor_table_mgr * get_neighbor_table_mgr();
   nexthop_group_mgr * get_nexthop_group_mgr();
   policy_map_mgr * get_policy_map_mgr();
   system_mgr * get_system_mgr();
   timeout_mgr * get_timeout_mgr();

  private:
   void init_mount_mgr();
   
   EOS_SDK_DISALLOW_COPY_CTOR(sdk);
   acl_mgr * acl_mgr_;
   agent_mgr * agent_mgr_;
   aresolve_mgr * aresolve_mgr_;
   class_map_mgr * class_map_mgr_;
   decap_group_mgr * decap_group_mgr_;
   directflow_mgr * directflow_mgr_;
   eth_intf_mgr * eth_intf_mgr_;
   eth_phy_intf_mgr * eth_phy_intf_mgr_;
   eth_phy_intf_counter_mgr * eth_phy_intf_counter_mgr_;
   eth_lag_intf_mgr * eth_lag_intf_mgr_;
   event_loop * event_loop_;
   fib_mgr * fib_mgr_;
   intf_mgr * intf_mgr_;
   intf_counter_mgr * intf_counter_mgr_;
   ip_intf_mgr * ip_intf_mgr_;
   ip_route_mgr * ip_route_mgr_;
   mac_table_mgr * mac_table_mgr_;
   mlag_mgr * mlag_mgr_;
   mount_mgr * mount_mgr_;
   mpls_route_mgr * mpls_route_mgr_;
   neighbor_table_mgr * neighbor_table_mgr_;
   nexthop_group_mgr * nexthop_group_mgr_;
   policy_map_mgr * policy_map_mgr_;
   system_mgr * system_mgr_;
   timeout_mgr * timeout_mgr_;
   
   std::string name_;
   
   friend class mount_mgr;
};

}

#include <eos/inline/sdk.h>

#endif // EOS_SDK_H
