// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_IP_INTF_H
#define EOS_IP_INTF_H

#include <set>

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/eth.h>
#include <eos/intf.h>
#include <eos/ip.h>

/**
 * @file
 * Network Interface IP addressing module.
 *
 * Changes to IP addresses bound to network interfaces can be reacted to using this
 * module, providing a callback that can be used to trigger server socket binding or
 * reconfiguration events.
 */

namespace eos {

class ip_intf_mgr;

/**
 * Event handler for interfaces with IP addresses specific events.
 *
 * By default, no interfaces are watched.
 */
class EOS_SDK_PUBLIC ip_intf_handler : public base_handler<ip_intf_mgr,
                                                           ip_intf_handler> {
 public:
   explicit ip_intf_handler(ip_intf_mgr *);
   ip_intf_mgr * get_ip_intf_mgr() const;

   /**
    * Registers to receive updates on changes to any interface.
    *
    * @param bool Whether or not this handler should be notified of IP address
    * assignment changes on any interface.
    */
   void watch_all_ip_intfs(bool);

   /**
    * Registers this class to receive change updates on the given interface.
    *
    * @param intf_id_t Which interface to subscribe to.
    * @param bool Whether or not this handler should be notified of IP address
    * assignment changes on the given interface.
    */
   void watch_ip_intf(intf_id_t, bool);

   /// Handler called when an IP address is added to the interface.
   virtual void on_ip_addr_add(intf_id_t, ip_addr_mask_t const &);
   /// Handler called when an IP address is deleted from the interface.
   virtual void on_ip_addr_del(intf_id_t, ip_addr_mask_t const &);

   /** 
    * Handler called when the internal VLAN ID for an interface
    * changes. If the interface loses its internal vlan id (i.e. is no
    * longer a routed port), this will be set to 0
    */
   virtual void on_internal_vlan_id(intf_id_t, vlan_id_t);
};

/// The IP address interface manager.
/// For the changes to be visible, the interface may have to be passed in routed
/// mode (see switchport_mode in eth_intf.h).
class EOS_SDK_PUBLIC ip_intf_mgr : public base_mgr<ip_intf_handler, intf_id_t> {
 public:
   virtual ~ip_intf_mgr();

   /**
    * Returns whether the given interface exists and is able to have IP addresses.
    *
    * If exists returns true, then this intf_id_t can be successfully
    * passed into every method of the ip_intf_mgr. If not, then
    * methods of the ip_intf_mgr can throw a no_such_interface_error
    * exception.
    *
    * Note that ip_intf_mgr::exists being true does not guarantee that
    * the underlying L2 interface, as managed by intf_mgr,
    * eth_intf_mgr, eth_phy_intf_mgr, eth_lag_intf_mgr, or
    * subintf_mgr, also exists.
    */
   virtual bool exists(intf_id_t) const = 0;

   // Attribute accessors
   /// Returns the operational set of IP addresses of the interface.
   virtual std::set<ip_addr_mask_t> ip_addrs(intf_id_t) const = 0;

   /**
    * Configures the IP addresses of the interface.
    * @param intf_id_t The interface ID of the interface to change the addresses of.
    * @param std::set<ip_addr_mask_t> The set of addresses to set.
    */
   virtual void ip_addrs_is(intf_id_t, std::set<ip_addr_mask_t> const &) = 0;

   /**
    * Adds an IP address to the interface.
    * @param intf_id_t The interface ID of the interface to add the address in.
    * @param ip_addr_mask_t The address to add.
    */
   virtual void ip_addr_add(intf_id_t, ip_addr_mask_t const &) = 0;

   /**
    * Deletes an IP address of the interface.
    * @param intf_id_t The interface ID of the interface to delete the address in.
    * @param ip_addr_mask_t The address to delete.
    */
   virtual void ip_addr_del(intf_id_t, ip_addr_mask_t const &) = 0;
   
   /**
    * Whether IP address configuration for a given interface is replaced or
    * merged with configuration from other agents.
    * If false, configuration will be replaced by that of higher priority
    * agents (such as the CLI). If true, configuration will be merged.
    * Default is false.
    * @param intf_id_t The interface ID of the interface to set the merge mode of.
    * @param bool Whether or not IP address configuration should be merged
    */
    virtual void ip_addr_merge_mode_is(intf_id_t, bool) = 0;

    /* Returns the IP address merge mode for a given interface.
     * @param intf_id_t The interface ID of the interface to get the merge mode of.
     */
    virtual bool ip_addr_merge_mode(intf_id_t) const = 0;

   /**
    * Returns the internal VLAN ID related to a layer 3 interface.
    * If the interface supplied is a routed interface (i.e., is
    * configured with "no switchport"), this function will return the
    * internal VLAN ID for the interface. If the interface is an SVI,
    * the VLAN ID of the SVI is returned. If the interface is a layer
    * 2 interface, VLAN ID 0 is returned.
    * @param intf_id_t An interface ID to query the internal VLAN ID of
    */
   virtual vlan_id_t internal_vlan_id(intf_id_t) const = 0;

 protected:
   ip_intf_mgr() EOS_SDK_PRIVATE;
   friend class ip_intf_handler;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(ip_intf_mgr);
};

}

#include <eos/inline/ip_intf.h>

#endif // EOS_IP_INTF_H

