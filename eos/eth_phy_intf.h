// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ETH_PHY_INTF_H
#define EOS_ETH_PHY_INTF_H

#include <eos/eth.h>
#include <eos/intf.h>
#include <eos/iterator.h>

namespace eos {

enum eth_link_speed_t {
   LINK_SPEED_UNKNOWN,
   LINK_SPEED_10MBPS,
   LINK_SPEED_100MBPS,
   LINK_SPEED_1GBPS,
   LINK_SPEED_10GBPS,
   LINK_SPEED_40GBPS,
   LINK_SPEED_100GBPS,
};

class EOS_SDK_PUBLIC eth_phy_intf_handler {
 public:
   eth_phy_intf_handler();
   virtual ~eth_phy_intf_handler();

   // Registers this class to receive updates on changes to the
   // interface. Expects a boolean signifying whether notifications
   // should be propagated to this instance or not.
   void watch_all_eth_phy_intfs(bool);

   // Handler called when a physical ethernet interface is created
   virtual void on_eth_phy_intf_create(intf_id_t);
   // Handler called when a physical ethernet interface is deleted
   virtual void on_eth_phy_intf_delete(intf_id_t);

 private:
   bool watching_all_intfs_;
};


class eth_phy_intf_iter_impl;

class EOS_SDK_PUBLIC eth_phy_intf_iter_t : public iter_base<intf_id_t,
                                                            eth_phy_intf_iter_impl> {
 private:
   friend class eth_phy_intf_iter_impl;
   explicit eth_phy_intf_iter_t(eth_phy_intf_iter_impl * const) EOS_SDK_PRIVATE;
};


class EOS_SDK_PUBLIC eth_phy_intf_mgr {
 public:
   // Collection management
   eth_phy_intf_iter_t eth_phy_intf_iter() const;
   typedef bool (*callback_func_eth_phy_intf)(intf_id_t, void * context);
   void eth_phy_intf_foreach(callback_func_eth_phy_intf handler, void * context);
   void eth_phy_intf_foreach(callback_func_eth_phy_intf handler, void * context,
                             intf_id_t bookmark);
   bool exists(intf_id_t) const;

   // Read the "burned in" address
   eth_addr_t burned_in_eth_addr(intf_id_t) const;

   // Returns the operational link speed
   eth_link_speed_t link_speed(intf_id_t) const;

 protected:
   eth_phy_intf_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(eth_phy_intf_mgr);
};

eth_phy_intf_mgr * get_eth_phy_intf_mgr() EOS_SDK_PUBLIC;

}

#endif // EOS_ETH_PHY_INTF_H
