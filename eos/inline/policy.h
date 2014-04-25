// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_POLICY_H
#define EOS_INLINE_POLICY_H

namespace eos {

inline policy_map_key_t::policy_map_key_t() : name_(), feature_() {
}

inline policy_map_key_t::policy_map_key_t(
      std::string const & name, policy_feature_t feature)
      : name_(name), feature_(feature) {
}

inline std::string const & policy_map_key_t::name() const {
   return name_;
}

inline void policy_map_key_t::name_is(std::string const & name) {
   name_ = name;
}

inline policy_feature_t policy_map_key_t::feature() const {
   return feature_;
}

inline void policy_map_key_t::feature_is(policy_feature_t feature) {
   feature_ = feature;
}

inline policy_map_rule_t::policy_map_rule_t() : class_map_key_(), actions_() {
}

inline policy_map_rule_t::policy_map_rule_t(policy_map_key_t const & key)
      : class_map_key_(key), actions_() {
}

inline policy_map_action_t::policy_map_action_t()
      : type_(), drop_(), next_hop_group_name_(), next_hops_() {
}

inline policy_action_type_t policy_map_action_t::action_type() const {
   return type_;
}

} // namespace eos

#endif // EOS_INLINE_POLICY_H
