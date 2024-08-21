// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/eth_lag_intf.h>
#include "impl.h"

namespace eos {

eth_lag_intf_handler::eth_lag_intf_handler(eth_lag_intf_mgr * mgr) :
      base_handler<eth_lag_intf_mgr, eth_lag_intf_handler>(mgr) {
}

eth_lag_intf_handler::~eth_lag_intf_handler() {
}

void
eth_lag_intf_handler::watch_all_eth_lag_intfs(bool) {
   // TODO: No op impl.
}

void
eth_lag_intf_handler::watch_eth_lag_intf(intf_id_t, bool) {
   // TODO: No op impl.
}

void
eth_lag_intf_handler::on_eth_lag_intf_create(intf_id_t lag) {
   // TODO: No op impl.
}

void
eth_lag_intf_handler::on_eth_lag_intf_delete(intf_id_t lag) {
   // TODO: No op impl.
}

void
eth_lag_intf_handler::on_lag_member_set(intf_id_t lag, intf_id_t member) {
   // TODO: No op impl.
}

void
eth_lag_intf_handler::on_lag_member_del(intf_id_t lag, intf_id_t member) {
   // TODO: No op impl.
}

void
eth_lag_intf_handler::on_lag_intf_speed(intf_id_t lag, uint64_t speed) {
   // TODO: No op impl.
}

/// The manager for Lag interface
class eth_lag_intf_mgr_impl : public eth_lag_intf_mgr {
 public:
   eth_lag_intf_mgr_impl() {
   }

   eth_lag_intf_iter_t eth_lag_intf_iter() const {
      eth_lag_intf_iter_t * nop = 0;
      return *nop;
   }

   bool exists(intf_id_t intf_id) const {
      return false;
   }

   eth_lag_intf_member_iter_t eth_lag_intf_member_iter() const {
      eth_lag_intf_member_iter_t * nop = 0;
      return *nop;
   }

   eth_lag_intf_member_iter_t eth_lag_intf_member_iter(
         intf_id_t eth_lag_intf_id) const {
      eth_lag_intf_member_iter_t * nop = 0;
      return *nop;
   }

   void eth_lag_intf_is(intf_id_t eth_lag_intf_id) {
   }

   eth_lag_intf_t eth_lag_intf(intf_id_t eth_lag_intf_id) const {
      return eth_lag_intf_t();
   }

   void eth_lag_intf_del(intf_id_t eth_lag_intf_id) {
   }

   uint64_t speed(intf_id_t eth_lag_intf_id) const {
      return 100;
   }

   void min_links_is(intf_id_t eth_lag_intf_id, uint32_t min_links) {
      return;
   }

   uint32_t min_links(intf_id_t eth_lag_intf_id) const {
      return 8;
   }

   void min_speed_is(intf_id_t eth_lag_intf_id, uint64_t min_speed) {
      return;
   }

   uint64_t min_speed(intf_id_t eth_lag_intf_id) const {
      return 0;
   }

   void fallback_type_is(intf_id_t eth_lag_intf_id,
                         eth_lag_intf_fallback_type_t fallback_type) {
      return;
   }

   eth_lag_intf_fallback_type_t fallback_type(intf_id_t eth_lag_intf_id) const {
      return ETH_LAG_INTF_FALLBACK_NONE;
   }

   void fallback_timeout_is(intf_id_t eht_lag_intf_id, uint16_t fallback_timeout) {
      return;
   }

   uint16_t fallback_timeout(intf_id_t eth_lag_intf_id) const {
      return 0;
   }

   uint16_t fallback_timeout_default(intf_id_t eth_lag_intf_id) const {
      return ETH_LAG_INTF_FALLBACK_TIMEOUT_DEFAULT;
   }

   void membership_set(intf_id_t member_intf_id, intf_id_t eth_lag_intf_id,
                       eth_lag_intf_member_lacp_mode_t mode) {
   }

   void membership_del(intf_id_t member_intf_id) {
   }

   eth_lag_intf_membership_t membership_status(intf_id_t member_intf_id) const {
      return eth_lag_intf_membership_t();
   }

   intf_id_t membership(intf_id_t member_intf_id) const {
      return intf_id_t();
   }

   eth_lag_intf_membership_t 
         eth_lag_intf_membership_status(intf_id_t member_intf_id) const {
      return eth_lag_intf_membership_t();
   }

   void member_priority_is(intf_id_t member_intf_id, uint16_t priority) {
   }

   void eth_lag_intf_member_priority_is(intf_id_t member_intf_id, 
                                        uint16_t priority) {
   }

   uint16_t member_priority(intf_id_t member_intf_id) const {
      return 0;
   }

   void eth_lag_intf_member_mode_is(intf_id_t member_intf_id, 
                                    eth_lag_intf_member_lacp_mode_t mode) {
   }
   void member_mode_is(intf_id_t member_intf_id,
                       eth_lag_intf_member_lacp_mode_t mode) {
   }

   eth_lag_intf_member_lacp_mode_t member_mode(intf_id_t member_intf_id) const {
      return ETH_LAG_INTF_MEMBER_LACP_MODE_OFF;
   }

   void eth_lag_intf_member_timeout_is(intf_id_t member_intf_id,
                             eth_lag_intf_member_lacp_timeout_t timeout) {
   }

   void member_timeout_is(intf_id_t member_intf_id,
                          eth_lag_intf_member_lacp_timeout_t timeout) {
   }

   eth_lag_intf_member_lacp_timeout_t
         member_timeout(intf_id_t member_intf_id) const {
      return ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_SHORT;
   }

   bool member_active(intf_id_t member_intf_id) const {
      return true;
   }

   double member_time(intf_id_t member_intf_id) const {
      return 1.0;
   }

   std::string member_reason(intf_id_t member_intf_id) const {
      return "Hello World";
   }
};

// -- pimpl wrappers to min_speed/min_speed_is

uint64_t eth_lag_intf_mgr::min_speed(intf_id_t eth_lag_intf_id) const {
   return static_cast<eth_lag_intf_mgr_impl const*>(this)->min_speed(
       eth_lag_intf_id);
}

void eth_lag_intf_mgr::min_speed_is(intf_id_t eth_lag_intf_id, uint64_t speed) {
   static_cast<eth_lag_intf_mgr_impl*>(this)->min_speed_is(eth_lag_intf_id, speed);
}

// -- end of wrappers

DEFINE_STUB_MGR_CTOR(eth_lag_intf_mgr)

} // end namespace eos
