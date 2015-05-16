// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

/**
 * @file
 * The subintf module manages subinterfaces.
 *
 * Subinterfaces are multiple logical routed interfaces under an Ethernet or
 * LAG routed interface (also referred to as the parent interface). Each
 * subinterface is assigned a VLAN tag that is unique to the subinterface
 * (among all its sibling subinterfaces under the same parent interface). The
 * VLAN tag is used for mux/demux of data traffic from/to all subinterfaces
 * under the parent interface.
 *
 * This module provides APIs to provision subinterfaces. APIs include subinterface
 * creation, deletion, retrieval and getter/setter for the subinterface VLAN tag.
 * An iterator is also provided to iterate through all the subinterfaces that are
 * configured in the system.
 *
 * The subinterface APIs can be used with the ones in "intf" module, as shown
 * in the sample code below. For example, the eos::intf_handler's on_intf_create()
 * API can be used to react to the creation of new subinterfaces.
 *
 * @code
 *
   #include <eos/agent.h>
   #include <eos/subintf.h>
   #include <eos/panic.h>
   #include <eos/sdk.h>

   static eos::subintf_mgr *subintf_mgr;

   class ApplicationAgent : public eos::agent_handler, eos::intf_handler {
    public:
      explicit ApplicationAgent(eos::sdk & sdk) :
                                eos::agent_handler(sdk.get_agent_mgr()),
                                eos::intf_handler(sdk.get_intf_mgr()) {
          watch_intf(eos::intf_id_t("Ethernet1.1"), true);
      }

      // Called when all agents are initialized
      void on_initialized() {
         // Creates subinterface
         subintf_mgr->subintf_is(eos::intf_id_t("Ethernet1.1"));
      }

      // Handler for subinterface creation
      void on_intf_create(eos::intf_id_t i) {
         if (i == eos::intf_id_t("Ethernet1.1")) {
            // Ethernet1.1 is now usable.
            // Other application logic goes here, such as creating more subinterfaces
         }
         return;
      }
   }

   int main(int argc, char **argv) {
      eos::sdk sdk;
      subintf_mgr = sdk.get_subintf_mgr();
      ApplicationAgent agent(sdk);
      sdk.main_loop(argc, argv);
   }
 * @endcode
 */


#ifndef EOS_SUBINTF_H
#define EOS_SUBINTF_H

#include <eos/intf.h>
#include <eos/iterator.h>
#include <eos/types/subintf.h>

namespace eos {

class subintf_iter_impl;

/**
 * An iterator over all subinterfaces in the system.
 */
class EOS_SDK_PUBLIC subintf_iter_t : public iter_base<intf_id_t,
                                                       subintf_iter_impl> {
 private:
   explicit subintf_iter_t(subintf_iter_impl * const) EOS_SDK_PRIVATE;
   friend class subintf_iter_impl;
};

/**
 * The manager for subinterfaces.  This is the main entry point for applications
 * to use EosSdk subintf APIs.
 */
class EOS_SDK_PUBLIC subintf_mgr {
 public:
   virtual ~subintf_mgr();

   /**
    * Returns an iterator for iterating over the subinterfaces in the system.
    * The iterator yields an intf_id_t for each configured subinterface.
    */
   virtual subintf_iter_t subintf_iter() const = 0;

   /**
    * Returns whether the given subinterface exists.
    *
    * If exists returns true, then this intf_id_t can be successfully
    * passed into every method of the subintf_mgr. If not, then
    * methods of the subintf_mgr can throw a no_such_interface_error
    * exception.
    *
    * The exists method of all *intf_mgr classes that manage a given
    * interface (ie intf_mgr, eth_intf_mgr, and subintf_mgr for
    * subinterfaces) are all guaranteed to return the same result.
    */
   virtual bool exists(intf_id_t) const = 0;

   /**
    * Creates a subinterface when given the subinterface ID.
    * No action will be taken if the subinterface exists already.
    * The subinterface will be created even if its parent interface does not exist.
    * But the subinterface will become operationally up on only after its parent
    * interface becomes operationally up and is in routed mode.
    */
   virtual void subintf_is(intf_id_t) = 0;

   /**
    * Creates a subinterface and sets its VLAN tag.  If the subinterface already
    * exists, its VLAN tag will be updated.
    */
   virtual void subintf_is(intf_id_t, vlan_id_t) = 0;

   /**
    * Returns the subinterface with the given ID.
    * Will return an empty subintf_t if the subinterface does not exist.
    */
   virtual subintf_t subintf(intf_id_t) const = 0;

   /**
    * Deletes a subinterface.  It will simply return if the given subinterface
    * does not exist.
    */
   virtual void subintf_del(intf_id_t) = 0;

   /**
    * Returns the configured VLAN tag of a given subinterface. Returns zero if
    * the subinterface does not exist or if no VLAN tag is configured for the
    * subinterface.
    */
   virtual vlan_id_t vlan_tag(intf_id_t) const = 0;

   /**
    * Configures the VLAN tag of a given subinterface.  Throws
    * invalid_argument_error exception if the subinterface does not exist.
    */
   virtual void vlan_tag_is(intf_id_t, vlan_id_t) = 0;

   /**
    * Returns the parent interface ID for a given subinterface. The parent
    * interface will be an Ethernet or a LAG interface.
    * Returns an empty intf_id_t (with intf_type as INTF_TYPE_NULL), if the given
    * interface is not a subinterface.
    */
   virtual intf_id_t parent_intf(intf_id_t) const = 0;

 protected:
   subintf_mgr() EOS_SDK_PRIVATE;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(subintf_mgr);
};

}

#endif // EOS_SUBINTF_H
