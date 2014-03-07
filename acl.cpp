// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/acl.h"

// TODO: an implementation that provides a mock Sysdb view
// Current implmentation is mostly no-ops

namespace eos {

// con/destructors

acl_mgr::acl_mgr() {}

acl_handler::acl_handler() {}
acl_handler::~acl_handler() {}

// acl_mgr methods

void
acl_mgr::acl_foreach(acl_cb handle, void * context) {
}

void
acl_mgr::acl_foreach(acl_cb handle, void * context, acl_key_t bookmark) {
}

void
acl_mgr::acl_rule_eth_foreach(acl_key_t const &,
                              acl_rule_eth_cb handle, void * context) {
}

void
acl_mgr::acl_rule_ip_foreach(acl_key_t const &,
                             acl_rule_ip_cb handle, void * context) {
}

bool
acl_mgr::acl_exists(acl_key_t const & key) const {
   return true;
}

void
acl_mgr::acl_apply(acl_key_t const & key, intf_id_t intf,
                   acl_direction_t direction, bool apply) {
}

void
acl_mgr::acl_rule_set(acl_key_t const &, uint32_t, acl_rule_ip_t const &) {
}

void
acl_mgr::acl_rule_set(acl_key_t const &, uint32_t, acl_rule_eth_t const &) {
}

void
acl_mgr::acl_rule_delete(acl_key_t const &, uint32_t seq) {
}

void
acl_mgr::acl_delete(acl_key_t const &) {
}

void
acl_mgr::acl_counters_enabled_set(acl_key_t const &, bool enabled) {
}

void
acl_mgr::acl_fragments_enabled_set(acl_key_t const &, bool enabled) {
}

void
acl_mgr::acl_commit() {
}

// handler methods

void
acl_handler::watch_all_acls(bool all) {
   watching_all_acls_ = all;
}

void
acl_handler::on_acl_sync() {
}

void
acl_handler::on_acl_sync_fail(std::string const & linecard,
                              std::string const & message) {
}

// manager setup

class acl_mgr_impl : public acl_mgr {
 public:
   acl_mgr_impl() {
   }
};

acl_mgr *
get_acl_mgr() {
   static acl_mgr_impl impl;
   return &impl;
}

}  // end namespace eos
