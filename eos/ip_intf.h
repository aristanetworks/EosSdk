// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_IP_INTF_H
#define EOS_IP_INTF_H

#include <set>

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
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
};

/// The IP address interface manager.
/// For the changes to be visible, the interface may have to be passed in routed
/// mode (see switchport_mode in eth_intf.h).
class EOS_SDK_PUBLIC ip_intf_mgr : public base_mgr<ip_intf_handler, intf_id_t> {
 public:
   virtual ~ip_intf_mgr();

   /// Returns whether the interface exists and is able to have IP addresses.
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

 protected:
   ip_intf_mgr() EOS_SDK_PRIVATE;
   friend class ip_intf_handler;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(ip_intf_mgr);
};

}

#include <eos/inline/ip_intf.h>

#endif // EOS_IP_INTF_H

