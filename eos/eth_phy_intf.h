// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ETH_PHY_INTF_H
#define EOS_ETH_PHY_INTF_H

#include <eos/base.h>
#include <eos/base_mgr.h>
#include <eos/eth.h>
#include <eos/intf.h>
#include <eos/iterator.h>

namespace eos {

/// Possible interface link speeds
enum eth_link_speed_t {
   LINK_SPEED_UNKNOWN,
   LINK_SPEED_10MBPS,
   LINK_SPEED_100MBPS,
   LINK_SPEED_1GBPS,
   LINK_SPEED_10GBPS,
   LINK_SPEED_40GBPS,
   LINK_SPEED_100GBPS,
};

class eth_phy_intf_mgr;

/**
 * A handler for Ethernet Physical Interface events.
 */
class EOS_SDK_PUBLIC eth_phy_intf_handler {
 public:
   explicit eth_phy_intf_handler(eth_phy_intf_mgr *);
   virtual ~eth_phy_intf_handler();

   /**
    * Registers this class to receive interface change update notifications.
    *
    * Expects a boolean signifying whether notifications
    * should be propagated to this instance or not.
    */
   void watch_all_eth_phy_intfs(bool);

   /**
    * Registers this class to receive interface change update notifications for the
    * given interface.
    *
    * Expects the id of the corresponding interface and a boolean signifying whether
    * notifications should be propagated to this instance or not.
    */
   void watch_eth_phy_intf(intf_id_t, bool);

   /// Handler called when a physical ethernet interface is created
   virtual void on_eth_phy_intf_create(intf_id_t);
   /// Handler called when a physical ethernet interface is deleted
   virtual void on_eth_phy_intf_delete(intf_id_t);

 protected:
   eth_phy_intf_mgr * eth_phy_intf_mgr_;
};


class eth_phy_intf_iter_impl;

/// Iterator over physical interfaces
class EOS_SDK_PUBLIC eth_phy_intf_iter_t : public iter_base<intf_id_t,
                                                            eth_phy_intf_iter_impl> {
 private:
   friend class eth_phy_intf_iter_impl;
   explicit eth_phy_intf_iter_t(eth_phy_intf_iter_impl * const) EOS_SDK_PRIVATE;
};


class EOS_SDK_PUBLIC eth_phy_intf_mgr : protected base_mgr<eth_phy_intf_handler,
                                                           intf_id_t> {
 public:
   virtual ~eth_phy_intf_mgr();

   // Collection management
   virtual eth_phy_intf_iter_t eth_phy_intf_iter() const = 0;
   typedef bool (*callback_func_eth_phy_intf)(intf_id_t, void * context);
   /// @deprecated Use eth_phy_intf_iter() instead.
   virtual void eth_phy_intf_foreach(callback_func_eth_phy_intf, void *)
      EOS_SDK_DEPRECATED = 0;
   /// @deprecated Use eth_phy_intf_iter() instead.
   virtual void eth_phy_intf_foreach(callback_func_eth_phy_intf, void *, intf_id_t)
      EOS_SDK_DEPRECATED = 0;
   /// Returns true if the interface ID passed exists in the system configuration
   virtual bool exists(intf_id_t) const = 0;

   /// Returns the "burned in" address of the interface
   virtual eth_addr_t burned_in_eth_addr(intf_id_t) const = 0;

   /// Returns the operational link speed
   virtual eth_link_speed_t link_speed(intf_id_t) const = 0;

 protected:
   eth_phy_intf_mgr() EOS_SDK_PRIVATE;
   friend class eth_phy_intf_handler;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(eth_phy_intf_mgr);
};

}

#endif // EOS_ETH_PHY_INTF_H
