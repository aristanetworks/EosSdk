/**
 * @file
 * The eth_lag_intf module manages link aggregation groups (LAGs), also known as
 * Port Channels.
 *
 * LAGs bundle physical interfaces together into a single logical link to provide
 * combined bandwidth and other benefits. This module provides APIs to provision
 * LAG interfaces. APIs include LAG creation, deletion, retrieval,  member interface
 * adding to or removal from LAG interfaces. Two iterators are also provided to
 * allow iteration through all the LAG interfaces and also all the member interfaces
 * that are configured on the system.
 *
 * The LAG APIs are best working with "intf" module, as shown in the sample code
 * below.
 *
 * @code{.cpp}
 *
   #include <eos/agent.h>
   #include <eos/eth_lag_intf.h>
   #include <eos/panic.h>
   #include <eos/sdk.h>

   static eos::eth_lag_intf_mgr *eth_lag_intf_mgr;

   class ApplicationAgent : public eos::agent_handler,
                                   eos::intf_handler {
    public:
      explicit ApplicationAgent(eos::sdk & sdk) :
                             eos::agent_handler(sdk.get_agent_mgr()),
                             eos::intf_handler(sdk.get_intf_mgr()) {
          watch_intf( eos::intf_id_t("Port-Channel23"), true );
          watch_intf( eos::intf_id_t("Port-Channel24"), true );
      }

      // Called when all agents are initialized
      void on_initialized() {
         // Creates PC 23, no mode specified
         eth_lag_intf_mgr->eth_lag_intf_is(eos::intf_id_t("Port-Channel23"));
      }

      // Handler for LAG interface creation
      void on_intf_create(eos::intf_id_t i) {
         if (i == eos::intf_id_t("Port-Channel23")) {
            try {
               eth_lag_intf_mgr->eth_lag_intf_is(eos::intf_id_t("Port-Channel23"));
            } catch (eos::invalid_argument_error &ia) {
               // Expected, since LAG 23 created already in "on_initialized" handler
               assert(ia.argument_name()=="eth_lag_intf.pc_create");
            }

            // Application logic goes here, such as creating more LAG interfaces
            // or adding member interfaces to it.
            try {
               eth_lag_intf_mgr->membership_set(intf_id_t("Ethernet1"),
                                    i,
                                    eos::ETH_LAG_INTF_MEMBER_LACP_MODE_PASSIVE);
            } catch (eos::invalid_argument_error &ia) {
               assert(false);
            } catch (eos::no_such_interface_error &e) {
               assert(false);
            }
         }
         return;
      }
   }

   int main(int argc, char **argv) {
      eos::sdk sdk;
      eth_lag_intf_mgr = sdk.get_eth_lag_intf_mgr();
      ApplicationAgent agent(sdk);
      sdk.main_loop(argc, argv);
   }
 * @endcode
 */


// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ETH_LAG_INTF_H
#define EOS_ETH_LAG_INTF_H

#include <string>

#include <eos/intf.h>
#include <eos/iterator.h>

#include <eos/types/eth_lag_intf.h>

namespace eos {

class eth_lag_intf_iter_impl;
class eth_lag_intf_member_iter_impl;

/**
 * An LAG interface iterator iterating through all LAG interfaces
 * created in the system.
 */
class EOS_SDK_PUBLIC eth_lag_intf_iter_t : public iter_base< intf_id_t,
                                                  eth_lag_intf_iter_impl> {
 private:
   friend class eth_lag_intf_iter_impl;
   explicit eth_lag_intf_iter_t(eth_lag_intf_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * An LAG member iterator iterating through all interfaces configured as a
 * member of one LAG interface in the system.
 */
class EOS_SDK_PUBLIC eth_lag_intf_member_iter_t : public iter_base< intf_id_t,
                                                  eth_lag_intf_member_iter_impl> {
 private:
   friend class eth_lag_intf_member_iter_impl;
   explicit eth_lag_intf_member_iter_t(
                         eth_lag_intf_member_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * The manager for LAG interface, this is the main entry point for applications
 * to use EosSdk LAG APIs.
 */
class EOS_SDK_PUBLIC eth_lag_intf_mgr {
 public:
   virtual ~eth_lag_intf_mgr();

   /**
    * Iterate the LAG interfaces in system, intf_id_t pointer is returned for
    * each LAG interface.
    */
   virtual eth_lag_intf_iter_t eth_lag_intf_iter() const = 0;
   /**
    * Iterate the physical interfaces configured as a member of an LAG interface 
    * in system, note the interface may not be in an LAG interface yet, but still
    * shows up if its priority/mode/timeout set.
    * "intf_id_t *" is returned for each member intf.
    */
   virtual eth_lag_intf_member_iter_t eth_lag_intf_member_iter() const = 0;
   /**
    * This API creates an LAG interface, when given the LAG id. No action will
    * be taken if the LAG exists already.
    */
   virtual eth_lag_intf_t eth_lag_intf_is(intf_id_t eth_lag_intf_id) = 0;
   /**
    * This API returns an LAG interface with the specified LAG id. Will return
    * an empty eth_lag_intf_t if the LAG does not exist already.
    */
   virtual eth_lag_intf_t eth_lag_intf(intf_id_t eth_lag_intf_id) const = 0;
   /**
    * This API deletes an LAG interface, it will simply return if the specified
    * LAG interface is not in existence.
    */
   virtual void eth_lag_intf_del( intf_id_t eth_lag_intf_id) = 0;
   /**
    * This API adds/removes one eth intf to/from an LAG interface.
    * To add an interface, the interface id and its LACP mode are needed.
    * To remove an interface from an LAG interface, the "intf" needs to be
    * provided, and eth_lag_intf_id needs to be the empty intf with
    * intf_type()==INTF_TYPE_NULL (created by intf_id_t()).
    *
    * When removing an interface from an LAG interface, this API may throw 
    * "no_such_interface_error" exception if the specified LAG interface does
    * not exist. It may also throw "invalid_argument_error" exception if the
    * specified "intf" is not in any LAG interface.
    *
    * When adding an interface to an LAG interface, this API may throw "Invalid_
    * argument_error" error if the interface's mode is not compatible with
    * the LAG interface mode.
    */
   virtual void membership_set(intf_id_t intf,
                               intf_id_t eth_lag_intf_id,
                               eth_lag_intf_member_lacp_mode_t mode) = 0;
   /**
    * This API returns the LAG interface id to which the physical intf is
    * configured to belong.
    * May throw "no_such_interface_error" if the "intf" does not exist.
    */
   virtual intf_id_t membership(intf_id_t intf) = 0;
   /**
    * This API returns the member intf operational status.
    * It may throw "no_such_interface_error" if the specified "intf" does not
    * exist.
    */
   virtual eth_lag_intf_membership_t
                         eth_lag_intf_membership_status(intf_id_t intf) = 0;

   /// This API sets the port LACP priority 
   virtual void eth_lag_intf_member_priority_is(intf_id_t intf,
                               uint16_t priority) = 0;
   /// This API sets the mode of this member in an LAG interface.
   virtual void eth_lag_intf_member_mode_is(intf_id_t intf,
                               eth_lag_intf_member_lacp_mode_t mode) = 0;
   /**
    * This API sets the LACP timeout for this member, the valid values are "short"
    * or "long".
    * It may throw "invalid_argument_error" exception, if the "timeout" value
    * is invalid.
    */
   virtual void eth_lag_intf_member_timeout_is(intf_id_t intf,
                               eth_lag_intf_member_lacp_timeout_t timeout) = 0;

 protected:
   eth_lag_intf_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(eth_lag_intf_mgr);
};

} // end namespace eos

#endif // EOS_ETH_LAG_INTF_H
