// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
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


policy_map_key_t::policy_map_key_t() {
   pimpl = std::shared_ptr<policy_map_key_impl_t>(
      new policy_map_key_impl_t()
   );
}
policy_map_key_t::policy_map_key_t(std::string const & name,
                                          policy_feature_t feature) {
   pimpl = std::shared_ptr<policy_map_key_impl_t>(
      new policy_map_key_impl_t(
         name,
         feature
      )
   );
}
policy_map_key_t::policy_map_key_t(
   const policy_map_key_t& other)
{
   pimpl = std::make_unique<policy_map_key_impl_t>(
      policy_map_key_impl_t(*other.pimpl));
}
policy_map_key_t&
policy_map_key_t::operator=(
   policy_map_key_t const & other)
{
   pimpl = std::shared_ptr<policy_map_key_impl_t>(
      new policy_map_key_impl_t(*other.pimpl));
   return *this;
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


// Default constructor.
policy_map_action_t::policy_map_action_t() {
   pimpl = std::shared_ptr<policy_map_action_impl_t>(
      new policy_map_action_impl_t()
   );
}
policy_map_action_t::policy_map_action_t(policy_action_type_t action_type) {
   pimpl = std::shared_ptr<policy_map_action_impl_t>(
      new policy_map_action_impl_t(
         action_type
      )
   );
}
policy_map_action_t::policy_map_action_t(
   const policy_map_action_t& other)
{
   pimpl = std::make_unique<policy_map_action_impl_t>(
      policy_map_action_impl_t(*other.pimpl));
}
policy_map_action_t&
policy_map_action_t::operator=(
   policy_map_action_t const & other)
{
   pimpl = std::shared_ptr<policy_map_action_impl_t>(
      new policy_map_action_impl_t(*other.pimpl));
   return *this;
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


policy_map_rule_t::policy_map_rule_t() {
   pimpl = std::shared_ptr<policy_map_rule_impl_t>(
      new policy_map_rule_impl_t()
   );
}
policy_map_rule_t::policy_map_rule_t(class_map_key_t const & class_map_key) {
   pimpl = std::shared_ptr<policy_map_rule_impl_t>(
      new policy_map_rule_impl_t(
         class_map_key
      )
   );
}
policy_map_rule_t::policy_map_rule_t(
   const policy_map_rule_t& other)
{
   pimpl = std::make_unique<policy_map_rule_impl_t>(
      policy_map_rule_impl_t(*other.pimpl));
}
policy_map_rule_t&
policy_map_rule_t::operator=(
   policy_map_rule_t const & other)
{
   pimpl = std::shared_ptr<policy_map_rule_impl_t>(
      new policy_map_rule_impl_t(*other.pimpl));
   return *this;
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


policy_map_t::policy_map_t() {
   pimpl = std::shared_ptr<policy_map_impl_t>(
      new policy_map_impl_t()
   );
}
policy_map_t::policy_map_t(policy_map_key_t const & key) {
   pimpl = std::shared_ptr<policy_map_impl_t>(
      new policy_map_impl_t(
         key
      )
   );
}
policy_map_t::policy_map_t(
   const policy_map_t& other)
{
   pimpl = std::make_unique<policy_map_impl_t>(
      policy_map_impl_t(*other.pimpl));
}
policy_map_t&
policy_map_t::operator=(
   policy_map_t const & other)
{
   pimpl = std::shared_ptr<policy_map_impl_t>(
      new policy_map_impl_t(*other.pimpl));
   return *this;
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


policy_map_hw_status_key_t::policy_map_hw_status_key_t() {
   pimpl = std::shared_ptr<policy_map_hw_status_key_impl_t>(
      new policy_map_hw_status_key_impl_t()
   );
}
policy_map_hw_status_key_t::policy_map_hw_status_key_t(
         intf_id_t intf_id, acl_direction_t direction) {
   pimpl = std::shared_ptr<policy_map_hw_status_key_impl_t>(
      new policy_map_hw_status_key_impl_t(
         intf_id,
         direction
      )
   );
}
policy_map_hw_status_key_t::policy_map_hw_status_key_t(
   const policy_map_hw_status_key_t& other)
{
   pimpl = std::make_unique<policy_map_hw_status_key_impl_t>(
      policy_map_hw_status_key_impl_t(*other.pimpl));
}
policy_map_hw_status_key_t&
policy_map_hw_status_key_t::operator=(
   policy_map_hw_status_key_t const & other)
{
   pimpl = std::shared_ptr<policy_map_hw_status_key_impl_t>(
      new policy_map_hw_status_key_impl_t(*other.pimpl));
   return *this;
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


policy_map_hw_statuses_t::policy_map_hw_statuses_t() {
   pimpl = std::shared_ptr<policy_map_hw_statuses_impl_t>(
      new policy_map_hw_statuses_impl_t()
   );
}
policy_map_hw_statuses_t::policy_map_hw_statuses_t(
         
         std::map<policy_map_hw_status_key_t, policy_map_status_t> const &
         intf_statuses) {
   pimpl = std::shared_ptr<policy_map_hw_statuses_impl_t>(
      new policy_map_hw_statuses_impl_t(
         intf_statuses
      )
   );
}
policy_map_hw_statuses_t::policy_map_hw_statuses_t(
   const policy_map_hw_statuses_t& other)
{
   pimpl = std::make_unique<policy_map_hw_statuses_impl_t>(
      policy_map_hw_statuses_impl_t(*other.pimpl));
}
policy_map_hw_statuses_t&
policy_map_hw_statuses_t::operator=(
   policy_map_hw_statuses_t const & other)
{
   pimpl = std::shared_ptr<policy_map_hw_statuses_impl_t>(
      new policy_map_hw_statuses_impl_t(*other.pimpl));
   return *this;
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
