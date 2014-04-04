// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ETH_INTF_H
#define EOS_ETH_INTF_H

#include <eos/base.h>
#include <eos/eth.h>
#include <eos/intf.h>
#include <eos/iterator.h>

namespace eos {

/// Mode of operation of a switch port.
enum switchport_mode_t {
   SWITCHPORT_MODE_ACCESS,        ///< Interface only has access to its access VLAN.
   SWITCHPORT_MODE_TRUNK,         ///< Interface is in 802.1q mode ("trunk mode").
   SWITCHPORT_MODE_DOT1Q_TUNNEL,  ///< Interface is in 802.1ad mode ("QinQ mode").
   SWITCHPORT_MODE_TAP,           ///< Interface is in tap mode ("span mode").
   SWITCHPORT_MODE_TOOL,          ///< Interface is a tool port (egress for a tap).
   SWITCHPORT_MODE_ROUTED,        ///< Interface routed ("no switchport").
};

/**
 * Event handler for ethernet interface specific events.
 *
 * Handles events on ethernet interfaces. Includes physical interfaces
 * and LAGs (port-channels) among other interface types.
 */
class EOS_SDK_PUBLIC eth_intf_handler {
 public:
   eth_intf_handler();
   virtual ~eth_intf_handler();

   /**
    * Registers to receive updates on changes to the interface.
    *
    * @param bool Signifyies whether notifications should be
    * propagated to this handler instance or not.
    */
   void watch_all_eth_intfs(bool);

  /**
    * Registers this class to receive change updates on the given interface.
    *
    * @param intf_id_t Signifyies which interface to subscribe to.
    * @param bool Signifyies whether notifications should be
    * propagated to this handler instance or not.
    */
   void watch_eth_intf(intf_id_t, bool);

   /// Handler called when an ethernet interface is created
   virtual void on_eth_intf_create(intf_id_t);
   /// Handler called when an ethernet interface is deleted
   virtual void on_eth_intf_delete(intf_id_t);
   /// Handler called when the mac address of an interface changes
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
class EOS_SDK_PUBLIC eth_intf_mgr {
 public:
   // Collection management
   eth_intf_iter_t eth_intf_iter() const;
   typedef bool (*callback_func_eth_intf)(intf_id_t, void * context);
   void eth_intf_foreach(callback_func_eth_intf handler, void * context);
   void eth_intf_foreach(callback_func_eth_intf handler, void * context,
                         intf_id_t bookmark);
   bool exists(intf_id_t) const;

   // Attribute accessors
   /// Returns the operational ethernet address of the interface
   eth_addr_t eth_addr(intf_id_t) const;
   /// Returns the currently configured ethernet address
   eth_addr_t configured_eth_addr(intf_id_t) const;

   /**
    * Configures the ethernet address of the interface
    * @param intf_id_t The interface ID of the interface to change the address of
    * @param eth_addr_t The address to set
    */
   void eth_addr_is(intf_id_t, eth_addr_t);

   /**
    * Returns the currently configured mode of operation of a given interface.
    * Note that only Ethernet and Port-Channel interfaces can be switchports,
    * using any other type of interface will lead to a panic.
    */
   switchport_mode_t switchport_mode(intf_id_t) const;

   /**
    * Configures the mode of operation of a given interface.
    * Note that only Ethernet and Port-Channel interfaces can be switchports,
    * using any other type of interface will lead to a panic.
    */
   void switchport_mode_is(intf_id_t, switchport_mode_t);

   /**
    * Returns the 'default' VLAN of a given interface.
    * The 'default' VLAN depends on the switchport mode of the interface.
    * If the interface is in access mode, then the access VLAN is returned.
    * If the interface is in tap or trunk mode, then the native VLAN is
    * returned.  If no native VLAN is configured, then 0 is returned.
    */
   vlan_id_t default_vlan(intf_id_t) const;

   /**
    * Configures the 'default' VLAN of a given interface.
    * The 'default' VLAN depends on the switchport mode of the interface.
    * If the interface is in access mode, then the access VLAN is configured.
    * If the interface is in tap or trunk mode, then the native VLAN is
    * configured.
    */
   void default_vlan_is(intf_id_t, vlan_id_t);

   /**
    * Returns the set of VLANs trunked on this interface.
    * Note that by default all VLANs are trunked on all interfaces.
    */
   vlan_set trunk_vlans(intf_id_t) const;

   /**
    * Adds a VLAN to the set of allowed VLANs when in trunk mode.
    * If the interface isn't in trunk mode, then the configuration is changed
    * nevertheless, but the configuration won't take effect until the
    * interface is switched to trunk mode.
    */
   void trunk_vlan_set(intf_id_t, vlan_id_t);

   /**
    * Configures the set of allowed VLANs when in trunk mode.
    * If the interface isn't in trunk mode, then the configuration is changed
    * nevertheless, but the configuration won't take effect until the
    * interface is switched to trunk mode.
    */
   void trunk_vlan_is(intf_id_t, vlan_set const & vlans);

   /**
    * Removes a VLAN to the set of allowed VLANs when in trunk mode.
    * If the interface isn't in trunk mode, then the configuration is changed
    * nevertheless, but the configuration won't take effect until the
    * interface is switched to trunk mode.
    */
   void trunk_vlan_del(intf_id_t, vlan_id_t);

 protected:
   eth_intf_mgr() EOS_SDK_PRIVATE;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(eth_intf_mgr);
};

/// Returns an ethernet interface manager instance
eth_intf_mgr * get_eth_intf_mgr() EOS_SDK_PUBLIC;

}

#endif // EOS_ETH_INTF_H
