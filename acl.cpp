// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/acl.h"

// TODO: an implementation that provides a mock Sysdb view
// Current implmentation is mostly no-ops

namespace eos {

// acl_handler methods

acl_handler::acl_handler(acl_mgr * mgr) {
}

acl_handler::~acl_handler() {
}

void
acl_handler::watch_all_acls(bool all) {
}

void
acl_handler::on_acl_sync() {
}

void
acl_handler::on_acl_sync_fail(std::string const & linecard,
                              std::string const & message) {
}

// acl_mgr methods

acl_mgr::acl_mgr() {
}

acl_mgr::~acl_mgr() {
}

class acl_mgr_impl : acl_mgr {
 public:
   acl_mgr_impl() {
   }

   acl_iter_t acl_iter() const {
      acl_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   void acl_foreach(acl_cb handle, void * context) {
   }

   void acl_foreach(acl_cb handle, void * context, acl_key_t bookmark) {
   }

   acl_rule_eth_iter_t acl_rule_eth_iter(acl_key_t const &) const {
      acl_rule_eth_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   void acl_rule_eth_foreach(acl_key_t const &,
                                 acl_rule_eth_cb handle, void * context) {
   }

   void acl_rule_ip_foreach(acl_key_t const &,
                                acl_rule_ip_cb handle, void * context) {
   }

   bool acl_exists(acl_key_t const & key) const {
      return true;
   }

   void acl_apply(acl_key_t const & key, intf_id_t intf,
                  acl_direction_t direction, bool apply) {
   }

   void acl_rule_set(acl_key_t const &, uint32_t, acl_rule_ip_t const &) {
   }

   void acl_rule_set(acl_key_t const &, uint32_t, acl_rule_eth_t const &) {
   }

   void acl_rule_del(acl_key_t const &, uint32_t seq) {
   }

   void acl_del(acl_key_t const &) {
   }

   void acl_counters_enabled_set(acl_key_t const &, bool enabled) {
   }

   void acl_fragments_enabled_set(acl_key_t const &, bool enabled) {
   }

   void acl_commit() {
   }
};

}  // end namespace eos
