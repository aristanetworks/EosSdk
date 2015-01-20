// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>
#include "eos/eth_intf.h"
#include "impl.h"

namespace eos {

eth_intf_handler::eth_intf_handler(eth_intf_mgr * mgr) : 
      base_handler<eth_intf_mgr, eth_intf_handler>(mgr) {
}

void
eth_intf_handler::watch_all_eth_intfs(bool all) {
   // TODO: No op impl.
}

void
eth_intf_handler::watch_eth_intf(intf_id_t, bool) {
   // TODO: No op impl.
}

void eth_intf_handler::on_eth_intf_create(intf_id_t) {
   // No-op impl.
}

void eth_intf_handler::on_eth_intf_delete(intf_id_t) {
   // No-op impl.
}

void eth_intf_handler::on_eth_addr(intf_id_t, eth_addr_t) {
   // No-op impl.
}

class eth_intf_mgr_impl : public eth_intf_mgr {
 public:
   eth_intf_mgr_impl() {
   }

   eth_intf_iter_t eth_intf_iter() const {
      eth_intf_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   bool exists(intf_id_t) const {
      return false;
   }

   eth_addr_t eth_addr(intf_id_t) const {
      return eth_addr_t();  // TODO: No-op impl.
   }

   eth_addr_t configured_eth_addr(intf_id_t) const {
      return eth_addr_t();  // TODO: No-op impl.
   }

   void eth_addr_is(intf_id_t, eth_addr_t) {
   }

   switchport_mode_t switchport_mode(intf_id_t) const {
      return SWITCHPORT_MODE_ACCESS;
   }

   void switchport_mode_is(intf_id_t, switchport_mode_t) {
      // TODO: No-op impl.
   }

   vlan_id_t default_vlan(intf_id_t) const {
      return 0;  // TODO: No-op impl.
   }

   void default_vlan_is(intf_id_t, vlan_id_t) {
      // TODO: No-op impl.
   }

   vlan_set_t trunk_vlans(intf_id_t) const {
      vlan_set_t vlans;
      // TODO: No-op impl.
      return vlans;
   }

   void trunk_vlan_set(intf_id_t, vlan_id_t) {
      // TODO: No-op impl.
   }

   void trunk_vlan_is(intf_id_t, vlan_set_t const &) {
      // TODO: No-op impl.
   }

   void trunk_vlan_del(intf_id_t, vlan_id_t) {
      // TODO: No-op impl.
   }
};

DEFINE_STUB_MGR_CTOR(eth_intf_mgr)

}
