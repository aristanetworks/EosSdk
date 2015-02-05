// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/eth_lag_intf.h>
#include "impl.h"

namespace eos {

/// The manager for Lag interface
class eth_lag_intf_mgr_impl : public eth_lag_intf_mgr {
 public:
   eth_lag_intf_mgr_impl() {
   }

   eth_lag_intf_iter_t eth_lag_intf_iter() const {
      eth_lag_intf_iter_t * nop = 0;
      return *nop;
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

   eth_lag_intf_t eth_lag_intf_is(intf_id_t eth_lag_intf_id) {
      return eth_lag_intf_t();
   }

   eth_lag_intf_t eth_lag_intf(intf_id_t eth_lag_intf_id) const {
      return eth_lag_intf_t();
   }

   void eth_lag_intf_del(intf_id_t eth_lag_intf_id) {
   }

   void membership_set(intf_id_t intf, intf_id_t eth_lag_intf_id,
                       eth_lag_intf_member_lacp_mode_t mode) {
   }

   intf_id_t membership(intf_id_t intf) {
      return intf_id_t();
   }

   eth_lag_intf_membership_t eth_lag_intf_membership_status(intf_id_t intf) {
      return eth_lag_intf_membership_t();
   }

   void eth_lag_intf_member_priority_is(intf_id_t intf, uint16_t priority) {
   }

   void eth_lag_intf_member_mode_is(intf_id_t intf, 
                                    eth_lag_intf_member_lacp_mode_t mode) {
   }

   void eth_lag_intf_member_timeout_is(intf_id_t intf,
                             eth_lag_intf_member_lacp_timeout_t timeout) {
   }
};

DEFINE_STUB_MGR_CTOR(eth_lag_intf_mgr)

} // end namespace eos
