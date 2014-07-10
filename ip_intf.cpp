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
};

DEFINE_STUB_MGR_CTOR(ip_intf_mgr)

}
