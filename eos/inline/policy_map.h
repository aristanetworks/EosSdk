// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_POLICY_H
#define EOS_INLINE_POLICY_H

namespace eos {

inline policy_map_mgr * policy_map_handler::get_policy_map_mgr() const {
   return mgr_;
}

inline policy_map_key_t::policy_map_key_t() :
      name_(), feature_() {
}

inline policy_map_key_t::policy_map_key_t(std::string const & name,
                                          policy_feature_t const & feature) :
      name_(name), feature_(feature) {
}

inline std::string
policy_map_key_t::name() const {
   return name_;
}

inline void
policy_map_key_t::name_is(std::string const & name) {
   name_ = name;
}

inline policy_feature_t
policy_map_key_t::feature() const {
   return feature_;
}

inline void
policy_map_key_t::feature_is(policy_feature_t const & feature) {
   feature_ = feature;
}

inline bool
policy_map_key_t::operator==(policy_map_key_t const & other) const {
   return name_ == other.name_ &&
          feature_ == other.feature_;
}

inline bool
policy_map_key_t::operator!=(policy_map_key_t const & other) const {
   return !operator==(other);
}

inline bool
policy_map_key_t::operator<(policy_map_key_t const & other) const {
   if(name_ != other.name_) {
      return name_ < other.name_;
   } else if(feature_ != other.feature_) {
      return feature_ < other.feature_;
   }
   return false;
}



inline policy_map_action_t::policy_map_action_t() :
      action_type_(), nexthop_group_name_(), nexthops_() {
}

inline policy_map_action_t::policy_map_action_t(policy_action_type_t action_type) :
      action_type_(action_type), nexthop_group_name_(), nexthops_() {
}

inline 
policy_map_action_t::~policy_map_action_t() {
   
}

inline policy_action_type_t
policy_map_action_t::action_type() const {
   return action_type_;
}

inline void
policy_map_action_t::action_type_is(policy_action_type_t action_type) {
   action_type_ = action_type;
}

inline std::string
policy_map_action_t::nexthop_group_name() const {
   return nexthop_group_name_;
}

inline void
policy_map_action_t::nexthop_group_name_is(std::string const & nexthop_group_name) {
   nexthop_group_name_ = nexthop_group_name;
}

inline std::unordered_set<ip_addr_t> &
policy_map_action_t::nexthops() {
   return nexthops_;
}

inline std::unordered_set<ip_addr_t> const &
policy_map_action_t::nexthops() const {
   return nexthops_;
}


inline void
policy_map_action_t::nexthops_is(std::unordered_set<ip_addr_t> const & nexthops) {
   nexthops_ = nexthops;
}

inline void
policy_map_action_t::nexthop_set(ip_addr_t const & value) {
   nexthops_.insert(value);
}

inline void
policy_map_action_t::nexthop_del(ip_addr_t const & value) {
   nexthops_.erase(value);
}

inline bool
policy_map_action_t::operator==(policy_map_action_t const & other) const {
   return action_type_ == other.action_type_ &&
          nexthop_group_name_ == other.nexthop_group_name_ &&
          nexthops_ == other.nexthops_;
}

inline bool
policy_map_action_t::operator!=(policy_map_action_t const & other) const {
   return !operator==(other);
}

inline bool
policy_map_action_t::operator<(policy_map_action_t const & other) const {
   return (nexthop_group_name_ < other.nexthop_group_name_);
}

inline policy_map_rule_t::policy_map_rule_t() :
      class_map_key_(), actions_() {
}

inline policy_map_rule_t::policy_map_rule_t(class_map_key_t const & class_map_key) :
      class_map_key_(class_map_key), actions_() {
}

inline class_map_key_t
policy_map_rule_t::class_map_key() const {
   return class_map_key_;
}

inline void
policy_map_rule_t::class_map_key_is(class_map_key_t const & class_map_key) {
   class_map_key_ = class_map_key;
}

inline std::unordered_set<policy_map_action_t> &
policy_map_rule_t::actions() {
   return actions_;
}

inline std::unordered_set<policy_map_action_t> const &
policy_map_rule_t::actions() const {
   return actions_;
}

inline void
policy_map_rule_t::action_set(policy_map_action_t const & value) {
   actions_.insert(value);
}

inline void
policy_map_rule_t::action_del(policy_map_action_t const & value) {
   actions_.erase(value);
}

inline void
policy_map_rule_t::action_del(policy_action_type_t action_type) {
   auto act = actions_.begin();
   while(act != actions_.end()) {
      if(act->action_type() == action_type) {
         act = actions_.erase(act);
      } else {
         ++act;
      }
   }
}

inline bool
policy_map_rule_t::operator==(policy_map_rule_t const & other) const {
   return class_map_key_ == other.class_map_key_ &&
          actions_ == other.actions_;
}

inline bool
policy_map_rule_t::operator!=(policy_map_rule_t const & other) const {
   return !operator==(other);
}

inline bool
policy_map_rule_t::operator<(policy_map_rule_t const& other) const {
   return (class_map_key_ < other.class_map_key_);
}

inline policy_map_t::policy_map_t() :
      key_(), rules_() {
}

inline policy_map_t::policy_map_t(policy_map_key_t const & key) :
      key_(key), rules_() {
}

inline policy_map_key_t
policy_map_t::key() const {
   return key_;
}

inline void
policy_map_t::key_is(policy_map_key_t const & key) {
   key_ = key;
}

inline std::map<uint32_t, policy_map_rule_t> &
policy_map_t::rules() {
   return rules_;
}

inline std::map<uint32_t, policy_map_rule_t> const &
policy_map_t::rules() const {
   return rules_;
}

inline void
policy_map_t::rules_is(std::map<uint32_t, policy_map_rule_t> const & rules) {
   rules_ = rules;
}

inline void
policy_map_t::rule_set(uint32_t key, policy_map_rule_t const & value) {
   rules_[key] = value;
}

inline void
policy_map_t::rule_del(uint32_t key) {
   rules_.erase(key);
}

inline bool
policy_map_t::operator==(policy_map_t const & other) const {
   return key_ == other.key_ &&
          rules_ == other.rules_;
}

inline bool
policy_map_t::operator!=(policy_map_t const & other) const {
   return !operator==(other);
}



} // namespace eos

#endif // EOS_INLINE_POLICY_H
