// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/exception.h"
#include "eos/intf.h"
#include "eos/ip.h"
#include "eos/ip_intf.h"
#include "eos/panic.h"
#include "impl.h"

namespace eos {

//
// ip_intf_handler implementations
//
//
ip_intf_handler::ip_intf_handler(ip_intf_mgr * mgr)
   : base_handler<ip_intf_mgr, ip_intf_handler>(mgr) {
   // TODO: No op impl.
}

void ip_intf_handler::watch_all_ip_intfs(bool interest) {
   // TODO: No op impl.
}

void ip_intf_handler::watch_ip_intf(intf_id_t i, bool interest) {
   // TODO: No op impl.
}

// Dummy implementations for virtual handler methods
void ip_intf_handler::on_ip_addr_add(intf_id_t, ip_addr_mask_t const &) {}
void ip_intf_handler::on_ip_addr_del(intf_id_t, ip_addr_mask_t const &) {}
void ip_intf_handler::on_internal_vlan_id(intf_id_t, vlan_id_t new_vlan) {}

class ip_intf_mgr_impl : public ip_intf_mgr {
 public:
   ip_intf_mgr_impl() {
   }

   bool exists(intf_id_t) const {
      return false;
   }

   std::set<ip_addr_mask_t> ip_addrs(intf_id_t) const {
      return std::set<ip_addr_mask_t>();
   }

   void ip_addrs_is(intf_id_t, std::set<ip_addr_mask_t> const &) {
   }

   void ip_addr_add(intf_id_t, ip_addr_mask_t const &) {
   }

   void ip_addr_del(intf_id_t, ip_addr_mask_t const &) {
   }

   void ip_addr_merge_mode_is(intf_id_t, bool) {
   }

   bool ip_addr_merge_mode(intf_id_t) const {
      return false;
   }

   vlan_id_t internal_vlan_id(intf_id_t) const {
      return vlan_id_t(123);
   }
};

DEFINE_STUB_MGR_CTOR(ip_intf_mgr)

}
