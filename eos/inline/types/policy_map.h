// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_POLICY_MAP_H
#define EOS_INLINE_TYPES_POLICY_MAP_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const policy_match_condition_t & enum_val) {
   if (enum_val==POLICY_MAP_CONDITION_NULL) {
      os << "POLICY_MAP_CONDITION_NULL";
   } else if (enum_val==POLICY_MAP_CONDITION_ANY) {
      os << "POLICY_MAP_CONDITION_ANY";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const policy_feature_t & enum_val) {
   if (enum_val==POLICY_FEATURE_NULL) {
      os << "POLICY_FEATURE_NULL";
   } else if (enum_val==POLICY_FEATURE_PBR) {
      os << "POLICY_FEATURE_PBR";
   } else if (enum_val==POLICY_FEATURE_QOS) {
      os << "POLICY_FEATURE_QOS";
   } else if (enum_val==POLICY_FEATURE_TAP_AGG) {
      os << "POLICY_FEATURE_TAP_AGG";
   } else if (enum_val==POLICY_FEATURE_TRAFFIC_POLICY) {
      os << "POLICY_FEATURE_TRAFFIC_POLICY";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const policy_action_type_t & enum_val) {
   if (enum_val==POLICY_ACTION_NULL) {
      os << "POLICY_ACTION_NULL";
   } else if (enum_val==POLICY_ACTION_NONE) {
      os << "POLICY_ACTION_NONE";
   } else if (enum_val==POLICY_ACTION_DROP) {
      os << "POLICY_ACTION_DROP";
   } else if (enum_val==POLICY_ACTION_NEXTHOP) {
      os << "POLICY_ACTION_NEXTHOP";
   } else if (enum_val==POLICY_ACTION_NEXTHOP_GROUP) {
      os << "POLICY_ACTION_NEXTHOP_GROUP";
   } else if (enum_val==POLICY_ACTION_DSCP) {
      os << "POLICY_ACTION_DSCP";
   } else if (enum_val==POLICY_ACTION_TRAFFIC_CLASS) {
      os << "POLICY_ACTION_TRAFFIC_CLASS";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const traffic_policy_action_type_t & enum_val) {
   if (enum_val==TRAFFIC_POLICY_ACTION_DROP) {
      os << "TRAFFIC_POLICY_ACTION_DROP";
   } else if (enum_val==TRAFFIC_POLICY_ACTION_POLICE) {
      os << "TRAFFIC_POLICY_ACTION_POLICE";
   } else if (enum_val==TRAFFIC_POLICY_ACTION_COUNT) {
      os << "TRAFFIC_POLICY_ACTION_COUNT";
   } else if (enum_val==TRAFFIC_POLICY_ACTION_LOG) {
      os << "TRAFFIC_POLICY_ACTION_LOG";
   } else if (enum_val==TRAFFIC_POLICY_ACTION_GOTO) {
      os << "TRAFFIC_POLICY_ACTION_GOTO";
   } else if (enum_val==TRAFFIC_POLICY_ACTION_DSCP) {
      os << "TRAFFIC_POLICY_ACTION_DSCP";
   } else if (enum_val==TRAFFIC_POLICY_ACTION_TRAFFIC_CLASS) {
      os << "TRAFFIC_POLICY_ACTION_TRAFFIC_CLASS";
   } else if (enum_val==TRAFFIC_POLICY_ACTION_SET_VRF) {
      os << "TRAFFIC_POLICY_ACTION_SET_VRF";
   } else if (enum_val==TRAFFIC_POLICY_ACTION_SET_VRF_SECONDARY) {
      os << "TRAFFIC_POLICY_ACTION_SET_VRF_SECONDARY";
   } else if (enum_val==TRAFFIC_POLICY_ACTION_USE_VRF_SECONDARY) {
      os << "TRAFFIC_POLICY_ACTION_USE_VRF_SECONDARY";
   } else if (enum_val==TRAFFIC_POLICY_ACTION_MIRROR) {
      os << "TRAFFIC_POLICY_ACTION_MIRROR";
   } else if (enum_val==TRAFFIC_POLICY_ACTION_SFLOW) {
      os << "TRAFFIC_POLICY_ACTION_SFLOW";
   } else if (enum_val==TRAFFIC_POLICY_ACTION_NEXTHOP) {
      os << "TRAFFIC_POLICY_ACTION_NEXTHOP";
   } else if (enum_val==TRAFFIC_POLICY_ACTION_NEXTHOP_GROUP) {
      os << "TRAFFIC_POLICY_ACTION_NEXTHOP_GROUP";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const traffic_policy_direction_t & enum_val) {
   if (enum_val==TRAFFIC_POLICY_DIRECTION_NULL) {
      os << "TRAFFIC_POLICY_DIRECTION_NULL";
   } else if (enum_val==TRAFFIC_POLICY_DIRECTION_INPUT) {
      os << "TRAFFIC_POLICY_DIRECTION_INPUT";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const policy_map_rule_type_t & enum_val) {
   if (enum_val==POLICY_RULE_TYPE_CLASSMAP) {
      os << "POLICY_RULE_TYPE_CLASSMAP";
   } else if (enum_val==POLICY_RULE_TYPE_IPV4) {
      os << "POLICY_RULE_TYPE_IPV4";
   } else if (enum_val==POLICY_RULE_TYPE_IPV6) {
      os << "POLICY_RULE_TYPE_IPV6";
   } else {
      os << "Unknown value";
   }
   return os;
}


std::string
policy_map_key_t::name() const {
   return pimpl->name();
}
void
policy_map_key_t::name_is(std::string const & name) {
   pimpl->name_is(name);
}
policy_feature_t
policy_map_key_t::feature() const {
   return pimpl->feature();
}
void
policy_map_key_t::feature_is(policy_feature_t feature) {
   pimpl->feature_is(feature);
}
bool
policy_map_key_t::operator==(policy_map_key_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
policy_map_key_t::operator!=(policy_map_key_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
policy_map_key_t::operator<(policy_map_key_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
policy_map_key_t::hash() const {
   return pimpl->hash();
}
void
policy_map_key_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
policy_map_key_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const policy_map_key_t& obj) {
   return operator<<(os, *obj.pimpl);
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const police_rate_unit_t & enum_val) {
   if (enum_val==BPS) {
      os << "BPS";
   } else if (enum_val==KBPS) {
      os << "KBPS";
   } else if (enum_val==MBPS) {
      os << "MBPS";
   } else if (enum_val==GBPS) {
      os << "GBPS";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const police_burst_unit_t & enum_val) {
   if (enum_val==BYTES) {
      os << "BYTES";
   } else if (enum_val==KBYTES) {
      os << "KBYTES";
   } else if (enum_val==MBYTES) {
      os << "MBYTES";
   } else {
      os << "Unknown value";
   }
   return os;
}



policy_map_action_t::~policy_map_action_t() {

}
policy_action_type_t
policy_map_action_t::action_type() const {
   return pimpl->action_type();
}
void
policy_map_action_t::action_type_is(policy_action_type_t action_type) {
   pimpl->action_type_is(action_type);
}
std::string
policy_map_action_t::nexthop_group_name() const {
   return pimpl->nexthop_group_name();
}
void
policy_map_action_t::nexthop_group_name_is(std::string const & nexthop_group_name) {
   pimpl->nexthop_group_name_is(nexthop_group_name);
}
std::unordered_set<ip_addr_t> const &
policy_map_action_t::nexthops() const {
   return pimpl->nexthops();
}
void
policy_map_action_t::nexthops_is(std::unordered_set<ip_addr_t> const & nexthops) {
   pimpl->nexthops_is(nexthops);
}
void
policy_map_action_t::nexthop_set(ip_addr_t const & value) {
   pimpl->nexthop_set(value);
}
void
policy_map_action_t::nexthop_del(ip_addr_t const & value) {
   pimpl->nexthop_del(value);
}
std::string
policy_map_action_t::vrf() const {
   return pimpl->vrf();
}
void
policy_map_action_t::vrf_is(std::string const & vrf) {
   pimpl->vrf_is(vrf);
}
uint8_t
policy_map_action_t::dscp() const {
   return pimpl->dscp();
}
void
policy_map_action_t::dscp_is(uint8_t dscp) {
   pimpl->dscp_is(dscp);
}
uint8_t
policy_map_action_t::traffic_class() const {
   return pimpl->traffic_class();
}
void
policy_map_action_t::traffic_class_is(uint8_t traffic_class) {
   pimpl->traffic_class_is(traffic_class);
}
bool
policy_map_action_t::operator==(policy_map_action_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
policy_map_action_t::operator!=(policy_map_action_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
policy_map_action_t::operator<(policy_map_action_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
policy_map_action_t::hash() const {
   return pimpl->hash();
}
void
policy_map_action_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
policy_map_action_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const policy_map_action_t& obj) {
   return operator<<(os, *obj.pimpl);
}



traffic_policy_action_t::~traffic_policy_action_t() {

}
traffic_policy_action_type_t
traffic_policy_action_t::action_type() const {
   return pimpl->action_type();
}
void
traffic_policy_action_t::action_type_is(traffic_policy_action_type_t action_type) {
   pimpl->action_type_is(action_type);
}
std::string
traffic_policy_action_t::counter_name() const {
   return pimpl->counter_name();
}
void
traffic_policy_action_t::counter_name_is(std::string const & counter_name) {
   pimpl->counter_name_is(counter_name);
}
std::string
traffic_policy_action_t::goto_class_name() const {
   return pimpl->goto_class_name();
}
void
traffic_policy_action_t::goto_class_name_is(std::string const & goto_class_name) {
   pimpl->goto_class_name_is(goto_class_name);
}
bool
traffic_policy_action_t::goto_next() const {
   return pimpl->goto_next();
}
void
traffic_policy_action_t::goto_next_is(bool const & goto_next) {
   pimpl->goto_next_is(goto_next);
}
uint8_t
traffic_policy_action_t::dscp() const {
   return pimpl->dscp();
}
void
traffic_policy_action_t::dscp_is(uint8_t dscp) {
   pimpl->dscp_is(dscp);
}
uint8_t
traffic_policy_action_t::traffic_class() const {
   return pimpl->traffic_class();
}
void
traffic_policy_action_t::traffic_class_is(uint8_t traffic_class) {
   pimpl->traffic_class_is(traffic_class);
}
std::string
traffic_policy_action_t::vrf() const {
   return pimpl->vrf();
}
void
traffic_policy_action_t::vrf_is(std::string const & vrf) {
   pimpl->vrf_is(vrf);
}
std::string
traffic_policy_action_t::mirror_session() const {
   return pimpl->mirror_session();
}
void
traffic_policy_action_t::mirror_session_is(std::string const & mirror_session) {
   pimpl->mirror_session_is(mirror_session);
}
uint64_t
traffic_policy_action_t::police_rate() const {
   return pimpl->police_rate();
}
void
traffic_policy_action_t::police_rate_is(uint64_t const & police_rate) {
   pimpl->police_rate_is(police_rate);
}
uint64_t
traffic_policy_action_t::police_burst_size() const {
   return pimpl->police_burst_size();
}
void
traffic_policy_action_t::police_burst_size_is(uint64_t const & police_burst_size) {
   pimpl->police_burst_size_is(police_burst_size);
}
police_rate_unit_t
traffic_policy_action_t::police_rate_unit() const {
   return pimpl->police_rate_unit();
}
void
traffic_policy_action_t::police_rate_unit_is(
         police_rate_unit_t const & police_rate_unit) {
   pimpl->police_rate_unit_is(police_rate_unit);
}
police_burst_unit_t
traffic_policy_action_t::police_burst_unit() const {
   return pimpl->police_burst_unit();
}
void
traffic_policy_action_t::police_burst_unit_is(
         police_burst_unit_t const & police_burst_unit) {
   pimpl->police_burst_unit_is(police_burst_unit);
}
std::unordered_set<std::string> const &
traffic_policy_action_t::nexthop_groups() const {
   return pimpl->nexthop_groups();
}
void
traffic_policy_action_t::nexthop_groups_is(
         std::unordered_set<std::string> const & nexthop_groups) {
   pimpl->nexthop_groups_is(nexthop_groups);
}
void
traffic_policy_action_t::nexthop_group_set(std::string const & value) {
   pimpl->nexthop_group_set(value);
}
void
traffic_policy_action_t::nexthop_group_del(std::string const & value) {
   pimpl->nexthop_group_del(value);
}
std::unordered_set<ip_addr_t> const &
traffic_policy_action_t::nexthops() const {
   return pimpl->nexthops();
}
void
traffic_policy_action_t::nexthops_is(
         std::unordered_set<ip_addr_t> const & nexthops) {
   pimpl->nexthops_is(nexthops);
}
void
traffic_policy_action_t::nexthop_set(ip_addr_t const & value) {
   pimpl->nexthop_set(value);
}
void
traffic_policy_action_t::nexthop_del(ip_addr_t const & value) {
   pimpl->nexthop_del(value);
}
bool
traffic_policy_action_t::operator==(traffic_policy_action_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
traffic_policy_action_t::operator!=(traffic_policy_action_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
traffic_policy_action_t::operator<(traffic_policy_action_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
traffic_policy_action_t::hash() const {
   return pimpl->hash();
}
void
traffic_policy_action_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
traffic_policy_action_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const traffic_policy_action_t& obj) {
   return operator<<(os, *obj.pimpl);
}


class_map_key_t
policy_map_rule_t::class_map_key() const {
   return pimpl->class_map_key();
}
void
policy_map_rule_t::class_map_key_is(class_map_key_t const & class_map_key) {
   pimpl->class_map_key_is(class_map_key);
}
policy_map_rule_type_t
policy_map_rule_t::policy_map_rule_type() const {
   return pimpl->policy_map_rule_type();
}
void
policy_map_rule_t::policy_map_rule_type_is(
         policy_map_rule_type_t policy_map_rule_type) {
   pimpl->policy_map_rule_type_is(policy_map_rule_type);
}
acl_rule_ip_t
policy_map_rule_t::raw_rule() const {
   return pimpl->raw_rule();
}
void
policy_map_rule_t::raw_rule_is(acl_rule_ip_t raw_rule) {
   pimpl->raw_rule_is(raw_rule);
}
std::set<policy_map_action_t> const &
policy_map_rule_t::actions() const {
   return pimpl->actions();
}
void
policy_map_rule_t::actions_is(std::set<policy_map_action_t> const & actions) {
   pimpl->actions_is(actions);
}
void
policy_map_rule_t::action_set(policy_map_action_t const & value) {
   pimpl->action_set(value);
}
void
policy_map_rule_t::action_del(policy_map_action_t const & value) {
   pimpl->action_del(value);
}
void
policy_map_rule_t::action_del(policy_action_type_t action_type) {
   pimpl->action_del(action_type);
}
void
policy_map_rule_t::raw_rule_is(acl_rule_ip_t acl_rule,
                               policy_map_rule_type_t rule_type) {
   pimpl->raw_rule_is(acl_rule, rule_type);
}
bool
policy_map_rule_t::operator==(policy_map_rule_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
policy_map_rule_t::operator!=(policy_map_rule_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
policy_map_rule_t::operator<(policy_map_rule_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
policy_map_rule_t::hash() const {
   return pimpl->hash();
}
void
policy_map_rule_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
policy_map_rule_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const policy_map_rule_t& obj) {
   return operator<<(os, *obj.pimpl);
}


policy_map_key_t
policy_map_t::key() const {
   return pimpl->key();
}
void
policy_map_t::key_is(policy_map_key_t const & key) {
   pimpl->key_is(key);
}
std::map<uint32_t, policy_map_rule_t> const &
policy_map_t::rules() const {
   return pimpl->rules();
}
void
policy_map_t::rules_is(std::map<uint32_t, policy_map_rule_t> const & rules) {
   pimpl->rules_is(rules);
}
void
policy_map_t::rule_set(uint32_t key, policy_map_rule_t const & value) {
   pimpl->rule_set(key, value);
}
void
policy_map_t::rule_del(uint32_t key) {
   pimpl->rule_del(key);
}
bool
policy_map_t::operator==(policy_map_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
policy_map_t::operator!=(policy_map_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
policy_map_t::operator<(policy_map_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
policy_map_t::hash() const {
   return pimpl->hash();
}
void
policy_map_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
policy_map_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const policy_map_t& obj) {
   return operator<<(os, *obj.pimpl);
}


std::string
traffic_policy_rule_t::match_rule_name() const {
   return pimpl->match_rule_name();
}
traffic_policy_rule_type_t
traffic_policy_rule_t::traffic_policy_rule_type() const {
   return pimpl->traffic_policy_rule_type();
}
tp_rule_filter_t
traffic_policy_rule_t::raw_rule() const {
   return pimpl->raw_rule();
}
std::set<traffic_policy_action_t> const &
traffic_policy_rule_t::actions() const {
   return pimpl->actions();
}
void
traffic_policy_rule_t::actions_is(
         std::set<traffic_policy_action_t> const & actions) {
   pimpl->actions_is(actions);
}
void
traffic_policy_rule_t::action_set(traffic_policy_action_t const & value) {
   pimpl->action_set(value);
}
void
traffic_policy_rule_t::action_del(traffic_policy_action_t const & value) {
   pimpl->action_del(value);
}
void
traffic_policy_rule_t::raw_rule_is(tp_rule_filter_t const & raw_rule) {
   pimpl->raw_rule_is(raw_rule);
}
void
traffic_policy_rule_t::action_del(traffic_policy_action_type_t action_type) {
   pimpl->action_del(action_type);
}
bool
traffic_policy_rule_t::operator==(traffic_policy_rule_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
traffic_policy_rule_t::operator!=(traffic_policy_rule_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
traffic_policy_rule_t::operator<(traffic_policy_rule_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
traffic_policy_rule_t::hash() const {
   return pimpl->hash();
}
void
traffic_policy_rule_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
traffic_policy_rule_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const traffic_policy_rule_t& obj) {
   return operator<<(os, *obj.pimpl);
}


std::string
traffic_policy_t::key() const {
   return pimpl->key();
}
std::unordered_set<std::string> const &
traffic_policy_t::named_counters() const {
   return pimpl->named_counters();
}
void
traffic_policy_t::named_counters_is(
         std::unordered_set<std::string> const & named_counters) {
   pimpl->named_counters_is(named_counters);
}
void
traffic_policy_t::named_counter_set(std::string const & value) {
   pimpl->named_counter_set(value);
}
void
traffic_policy_t::named_counter_del(std::string const & value) {
   pimpl->named_counter_del(value);
}
std::map<uint32_t, traffic_policy_rule_t> const &
traffic_policy_t::rules() const {
   return pimpl->rules();
}
void
traffic_policy_t::rules_is(std::map<uint32_t, traffic_policy_rule_t> const & rules)
       {
   pimpl->rules_is(rules);
}
void
traffic_policy_t::rule_set(uint32_t key, traffic_policy_rule_t const & value) {
   pimpl->rule_set(key, value);
}
void
traffic_policy_t::rule_del(uint32_t key) {
   pimpl->rule_del(key);
}
bool
traffic_policy_t::operator==(traffic_policy_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
traffic_policy_t::operator!=(traffic_policy_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
traffic_policy_t::operator<(traffic_policy_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
traffic_policy_t::hash() const {
   return pimpl->hash();
}
void
traffic_policy_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
traffic_policy_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const traffic_policy_t& obj) {
   return operator<<(os, *obj.pimpl);
}


unsupported_policy_feature_error::unsupported_policy_feature_error(
         policy_feature_t policy_feature) noexcept :
      unsupported_error(std::string("Unsupported policy feature")),
      policy_feature_(policy_feature) {

}


unsupported_policy_feature_error::~unsupported_policy_feature_error() noexcept {

}

policy_feature_t
unsupported_policy_feature_error::policy_feature() const noexcept {
   return policy_feature_;
}

void
unsupported_policy_feature_error::raise() const {
   throw *this;
}

uint32_t
unsupported_policy_feature_error::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
unsupported_policy_feature_error::mix_me(hash_mix & h) const {
   h.mix(policy_feature_); // policy_feature_t
}

std::string
unsupported_policy_feature_error::to_string() const {
   std::ostringstream ss;
   ss << "unsupported_policy_feature_error(";
   ss << "policy_feature=" << policy_feature_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const unsupported_policy_feature_error& obj) {
   os << obj.to_string();
   return os;
}



EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const policy_map_status_t & enum_val) {
   if (enum_val==POLICY_STATUS_NOT_FOUND) {
      os << "POLICY_STATUS_NOT_FOUND";
   } else if (enum_val==POLICY_STATUS_IN_PROGRESS) {
      os << "POLICY_STATUS_IN_PROGRESS";
   } else if (enum_val==POLICY_STATUS_FAILED) {
      os << "POLICY_STATUS_FAILED";
   } else if (enum_val==POLICY_STATUS_SUCCESS) {
      os << "POLICY_STATUS_SUCCESS";
   } else {
      os << "Unknown value";
   }
   return os;
}


intf_id_t
policy_map_hw_status_key_t::intf_id() const {
   return pimpl->intf_id();
}
void
policy_map_hw_status_key_t::intf_id_is(intf_id_t intf_id) {
   pimpl->intf_id_is(intf_id);
}
acl_direction_t
policy_map_hw_status_key_t::direction() const {
   return pimpl->direction();
}
void
policy_map_hw_status_key_t::direction_is(acl_direction_t direction) {
   pimpl->direction_is(direction);
}
bool
policy_map_hw_status_key_t::operator==(policy_map_hw_status_key_t const & other)
       const {
   return pimpl->operator==(*other.pimpl);
}
bool
policy_map_hw_status_key_t::operator!=(policy_map_hw_status_key_t const & other)
       const {
   return pimpl->operator!=(*other.pimpl);
}
bool
policy_map_hw_status_key_t::operator<(policy_map_hw_status_key_t const & other)
       const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
policy_map_hw_status_key_t::hash() const {
   return pimpl->hash();
}
void
policy_map_hw_status_key_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
policy_map_hw_status_key_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const policy_map_hw_status_key_t& obj) {
   return operator<<(os, *obj.pimpl);
}


std::map<policy_map_hw_status_key_t, policy_map_status_t> const &
policy_map_hw_statuses_t::intf_statuses() const {
   return pimpl->intf_statuses();
}
void
policy_map_hw_statuses_t::intf_statuses_is(
         
         std::map<policy_map_hw_status_key_t, policy_map_status_t> const &
         intf_statuses) {
   pimpl->intf_statuses_is(intf_statuses);
}
void
policy_map_hw_statuses_t::intf_statuse_set(policy_map_hw_status_key_t const & key,
                                           policy_map_status_t const & value) {
   pimpl->intf_statuse_set(key, value);
}
void
policy_map_hw_statuses_t::intf_statuse_del(policy_map_hw_status_key_t const & key) {
   pimpl->intf_statuse_del(key);
}
bool
policy_map_hw_statuses_t::operator==(policy_map_hw_statuses_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
policy_map_hw_statuses_t::operator!=(policy_map_hw_statuses_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
policy_map_hw_statuses_t::operator<(policy_map_hw_statuses_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
policy_map_hw_statuses_t::hash() const {
   return pimpl->hash();
}
void
policy_map_hw_statuses_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
policy_map_hw_statuses_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const policy_map_hw_statuses_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_POLICY_MAP_H
