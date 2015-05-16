// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ETH_INTF_H
#define EOS_ETH_INTF_H

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/eth.h>
#include <eos/intf.h>
#include <eos/iterator.h>
#include <eos/types/eth_intf.h>

namespace eos {

class eth_intf_mgr;

/**
 * Event handler for ethernet interface specific events.
 *
 * Handles events on ethernet interfaces. Includes physical interfaces
 * and LAGs (port-channels) among other interface types.
 */
class EOS_SDK_PUBLIC eth_intf_handler : public base_handler<eth_intf_mgr,
                                                            eth_intf_handler> {
 public:
   explicit eth_intf_handler(eth_intf_mgr *);
   eth_intf_mgr * get_eth_intf_mgr() const;

   /**
    * Registers to receive updates on changes to the interface.
    *
    * @param bool Signifies whether notifications should be
    * propagated to this handler instance or not.
    */
   void watch_all_eth_intfs(bool);

  /**
    * Registers this class to receive change updates on the given interface.
    *
    * @param intf_id_t Signifies which interface to subscribe to.
    * @param bool Signifies whether notifications should be
    * propagated to this handler instance or not.
    */
   void watch_eth_intf(intf_id_t, bool);

   /**
    * Handler called when an ethernet interface is created.
    *
    * After on_eth_intf_create is called, the given intf_id is
    * guaranteed to exist (ie eth_intf_mgr::exists will return true).
    * At that point, the intf_id can be used will all methods of the
    * eth_intf_mgr class.
    *
    * This also means that the intf_id can be used with all other
    * relevant *intf_mgr classes (ie intf_mgr, eth_phy_intf_mgr,
    * eth_lag_intf_mgr, and subintf_mgr as appropriate based on the
    * intf_type).
    */
   virtual void on_eth_intf_create(intf_id_t);
   /**
    * Handler called when an ethernet interface is deleted.
    *
    * After on_eth_intf_delete is called, the given intf_id is
    * guaranteed to not exist (ie eth_intf_mgr::exists will return
    * false). At that point, the intf_id cannot be used will any
    * methods in the eth_intf_mgr class.
    *
    * This also means that the intf_id can no longer be used with all
    * other relevant *intf_mgr classes (ie intf_mgr, eth_phy_intf_mgr,
    * eth_lag_intf_mgr, and subintf_mgr as appropriate based on the
    * intf_type).
    */
   virtual void on_eth_intf_delete(intf_id_t);
   /**
    * Handler called when the mac address of an interface changes
    *
    * Note that for physical interfaces, the on_eth_addr handler
    * will get called with the default eth_addr_t value when
    * the hardware for that physical interface is removed.
    */
   virtual void on_eth_addr(intf_id_t, eth_addr_t);
};


class eth_intf_iter_impl;

/// Iterator type for ethernet interfaces
class EOS_SDK_PUBLIC eth_intf_iter_t : public iter_base<intf_id_t,
                                                        eth_intf_iter_impl> {
 private:
   friend class eth_intf_iter_impl;
   explicit eth_intf_iter_t(eth_intf_iter_impl * const) EOS_SDK_PRIVATE;
};


/// The ethernet interface manager
class EOS_SDK_PUBLIC eth_intf_mgr : public base_mgr<eth_intf_handler, intf_id_t> {
 public:
   virtual ~eth_intf_mgr();

   // Collection management
   virtual eth_intf_iter_t eth_intf_iter() const = 0;

   /**
    * Returns whether the given ethernet interface exists.
    *
    * If exists returns true, then this intf_id_t can be successfully
    * passed into every method of the eth_intf_mgr. If not, then
    * methods of the eth_intf_mgr can throw a no_such_interface_error
    * exception.
    *
    * The exists method of all *intf_mgr classes that manage a given
    * interface (ie intf_mgr, eth_intf_mgr, eth_phy_intf_mgr,
    * eth_lag_intf_mgr, and/or subintf_mgr) are all guaranteed to
    * return the same result.
    */
   virtual bool exists(intf_id_t) const = 0;

   // Attribute accessors
   /// Returns the operational ethernet address of the interface
   virtual eth_addr_t eth_addr(intf_id_t) const = 0;
   /// Returns the currently configured ethernet address
   virtual eth_addr_t configured_eth_addr(intf_id_t) const = 0;

   /**
    * Configures the ethernet address of the interface
    * @param intf_id_t The interface ID of the interface to change the address of
    * @param eth_addr_t The address to set
    */
   virtual void eth_addr_is(intf_id_t, eth_addr_t) = 0;

   /**
    * Returns the currently configured mode of operation of a given interface.
    * Note that only Ethernet and Port-Channel interfaces can be switchports,
    * using any other type of interface will lead to a panic.
    */
   virtual switchport_mode_t switchport_mode(intf_id_t) const = 0;

   /**
    * Configures the mode of operation of a given interface.
    * Note that only Ethernet and Port-Channel interfaces can be switchports,
    * using any other type of interface will lead to a panic.
    */
   virtual void switchport_mode_is(intf_id_t, switchport_mode_t) = 0;

   /**
    * Returns the 'default' VLAN of a given interface.
    * The 'default' VLAN depends on the switchport mode of the interface.
    * If the interface is in access mode, then the access VLAN is returned.
    * If the interface is in tap or trunk mode, then the native VLAN is
    * returned.  If no native VLAN is configured, then 0 is returned.
    */
   virtual vlan_id_t default_vlan(intf_id_t) const = 0;

   /**
    * Configures the 'default' VLAN of a given interface.
    * The 'default' VLAN depends on the switchport mode of the interface.
    * If the interface is in access mode, then the access VLAN is configured.
    * If the interface is in tap or trunk mode, then the native VLAN is
    * configured.
    */
   virtual void default_vlan_is(intf_id_t, vlan_id_t) = 0;

   /**
    * Returns the set of VLANs trunked on this interface.
    * Note that by default all VLANs are trunked on all interfaces.
    */
   virtual vlan_set_t trunk_vlans(intf_id_t) const = 0;

   /**
    * Adds a VLAN to the set of allowed VLANs when in trunk mode.
    * If the interface isn't in trunk mode, then the configuration is changed
    * nevertheless, but the configuration won't take effect until the
    * interface is switched to trunk mode.
    */
   virtual void trunk_vlan_set(intf_id_t, vlan_id_t) = 0;

   /**
    * Configures the set of allowed VLANs when in trunk mode.
    * If the interface isn't in trunk mode, then the configuration is changed
    * nevertheless, but the configuration won't take effect until the
    * interface is switched to trunk mode.
    */
   virtual void trunk_vlan_is(intf_id_t, vlan_set_t const & vlans) = 0;

   /**
    * Removes a VLAN to the set of allowed VLANs when in trunk mode.
    * If the interface isn't in trunk mode, then the configuration is changed
    * nevertheless, but the configuration won't take effect until the
    * interface is switched to trunk mode.
    */
   virtual void trunk_vlan_del(intf_id_t, vlan_id_t) = 0;

 protected:
   eth_intf_mgr() EOS_SDK_PRIVATE;
   friend class eth_intf_handler;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(eth_intf_mgr);
};

}

#include <eos/inline/eth_intf.h>

#endif // EOS_ETH_INTF_H
