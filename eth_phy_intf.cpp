// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/eth_phy_intf.h"
#include "impl.h"

namespace eos {

eth_phy_intf_handler::eth_phy_intf_handler(eth_phy_intf_mgr * mgr)
      : base_handler<eth_phy_intf_mgr, eth_phy_intf_handler>(mgr) {
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

void
eth_phy_intf_handler::on_eth_phy_intf_hardware_present(intf_id_t, bool) {
   // TODO: No op impl.
}

void
eth_phy_intf_handler::on_eth_phy_intf_link_speed(intf_id_t, eth_link_speed_t) {
   // TODO: No op impl.
}

void
eth_phy_intf_handler::on_eth_phy_intf_transceiver_present(intf_id_t, bool) {
   // TODO: No op impl.
}

class eth_phy_intf_mgr_impl : public eth_phy_intf_mgr {
 public:
   eth_phy_intf_mgr_impl() {
   }

   eth_phy_intf_iter_t eth_phy_intf_iter() const {
      eth_phy_intf_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   bool exists(intf_id_t) const {
      return false;
   }

   bool hardware_present(intf_id_t) const {
      return false;
   }

   // Read the "burned in" address
   eth_addr_t burned_in_eth_addr(intf_id_t) const {
      return eth_addr_t();
   }

   eth_link_speed_t link_speed(intf_id_t intf_id) const {
      return LINK_SPEED_UNKNOWN;  // TODO: No op impl.
   }

   bool transceiver_present(intf_id_t intf_id) const {
      return false;  // TODO: No op impl.
   }

};

DEFINE_STUB_MGR_CTOR(eth_phy_intf_mgr)
 
class eth_phy_intf_counter_mgr_impl : public eth_phy_intf_counter_mgr {
 public:
   eth_phy_intf_counter_mgr_impl() {
   }

   eth_phy_intf_counters_t counters(intf_id_t) const {
      return eth_phy_intf_counters_t();
   }
   
   eth_phy_intf_bin_counters_t bin_counters(intf_id_t) const {
      return eth_phy_intf_bin_counters_t();
   }

};

DEFINE_STUB_MGR_CTOR(eth_phy_intf_counter_mgr)

}
