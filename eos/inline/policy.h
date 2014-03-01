// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_POLICY_H
#define EOS_INLINE_POLICY_H

#include <eos/panic.h>

namespace eos {

policy_map_key_t::policy_map_key_t() {
}

policy_map_key_t::policy_map_key_t(std::string const & name,
                                   policy_feature_t feature) : name_(), feature_() {
}

std::string const &
policy_map_key_t::name() const {
   return name_;
}

policy_feature_t
feature() const {
   return feature_;
}

class_map_match_type_t
class_map_match_base_t::match_type() {
   return match_type_;
}

class_map_match_base_t::class_map_match_base_t() : match_type_() {
}

class_map_match_acl_t::class_map_match_acl_t() : match_type_(CLASS_MAP_MATCH_ACL) {
}

class_map_match_acl_t::class_map_match_acl_t(acl_key_t const & acl_key)
      : match_type_(), acl_key_(acl_key) {
}

class_map_match_acl_t::acl_key() const {
   return acl_key_t();
}

class_map_match_acl_rule_ip_t::class_map_match_acl_rule_ip_t() : match_type_() {
}

class_map_match_acl_rule_ip_t::class_map_match_acl_rule_ip_t(
      acl_rule_ip_t const & acl_rule) : match_type_(), acl_rule_(acl_rule) {
}

acl_rule_ip_t const &
class_map_match_acl_rule_ip_t::rule() const {
   return rule_;
}

class_map_match_acl_rule_eth_t::class_map_match_acl_rule_eth_t() {
}

acl_rule_eth_t const &
class_map_match_acl_rule_eth_t::rule() const {
   return rule_;
}

policy_map_action_base_t::policy_map_action_base_t() {
}

policy_action_type_t
policy_map_action_base_t::action_type() const {
   return action_type_;
}

policy_map_action_nexthop_t::policy_map_action_nexthop_t() {
}

policy_map_action_nexthop_t::policy_map_action_nexthop_t(
      std::list<ip_addr_t const &> addrs) {
   nexthop_(addrs);
}

std::list<ip_addr_t>
policy_map_action_nexthop_t::nexthop() const {
   return nexthop_;
}

policy_map_action_nexthop_group_t::policy_map_action_nexthop_group_t()
      : nexthop_group_() {
}

std::string const &
policy_map_action_nexthop_group_t::nexthop_group() const {
   return nexthop_group_;
}




#endif // EOS_INLINE_POLICY_H
