// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/eth_phy_intf.h"

namespace eos {

eth_phy_intf_handler::eth_phy_intf_handler(eth_phy_intf_mgr * mgr) {
}

eth_phy_intf_handler::~eth_phy_intf_handler() {
}

void
eth_phy_intf_handler::watch_all_eth_phy_intfs(bool all) {
   // TODO: No op impl.
}

void
eth_phy_intf_handler::watch_eth_phy_intf(intf_id_t, bool) {
   // TODO: No op impl.
}

void
eth_phy_intf_handler::on_eth_phy_intf_create(intf_id_t) {
   // TODO: No op impl.
}

void
eth_phy_intf_handler::on_eth_phy_intf_delete(intf_id_t) {
   // TODO: No op impl.
}

eth_phy_intf_mgr::eth_phy_intf_mgr() {
}

eth_phy_intf_mgr::~eth_phy_intf_mgr() {
}

class eth_phy_intf_mgr_impl : public eth_phy_intf_mgr {
 public:
   eth_phy_intf_mgr_impl() {
   }

   eth_phy_intf_iter_t eth_phy_intf_iter() const {
      eth_phy_intf_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   void eth_phy_intf_foreach(callback_func_eth_phy_intf, void *) {
      // TODO: No op impl.
   }

   void eth_phy_intf_foreach(callback_func_eth_phy_intf, void *, intf_id_t) {
      // TODO: No op impl.
   }

   bool exists(intf_id_t) const {
      return false;
   }

   // Read the "burned in" address
   eth_addr_t burned_in_eth_addr(intf_id_t) const {
      return eth_addr_t();
   }

   eth_link_speed_t link_speed(intf_id_t intf_id) const {
      return LINK_SPEED_UNKNOWN;  // TODO: No op impl.
   }

};

}
