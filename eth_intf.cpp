// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>
#include "eos/eth_intf.h"

namespace eos {

eth_intf_handler::eth_intf_handler() {
}

eth_intf_handler::~eth_intf_handler() {
}

void
eth_intf_handler::watch_all_eth_intfs(bool all) {
  watching_all_intfs_ = all;
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


void
eth_intf_mgr::eth_intf_foreach(bool (*handler)(intf_id_t, void *), void *) {
}

void
eth_intf_mgr::eth_intf_foreach(bool (*handler)(intf_id_t, void *), void *,
                      intf_id_t bookmark) {
}

bool
eth_intf_mgr::exists(intf_id_t) const {
   return false;
}

eth_addr_t
eth_intf_mgr::eth_addr(intf_id_t) const {
   return eth_addr_t();  // TODO: No-op impl.
}

eth_addr_t
eth_intf_mgr::configured_eth_addr(intf_id_t) const {
   return eth_addr_t();  // TODO: No-op impl.
}

void
eth_intf_mgr::eth_addr_is(intf_id_t, eth_addr_t) {
}

eth_intf_mgr::eth_intf_mgr() {
}

class eth_intf_mgr_impl : public eth_intf_mgr {
 public:
   eth_intf_mgr_impl() {
   }
};

eth_intf_mgr * get_eth_intf_mgr() {
   static eth_intf_mgr_impl mgr;
   return &mgr;
}

}
