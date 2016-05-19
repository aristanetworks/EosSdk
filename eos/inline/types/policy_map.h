// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_POLICY_MAP_H
#define EOS_INLINE_TYPES_POLICY_MAP_H

namespace eos {

inline std::ostream&
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



inline std::ostream&
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



inline std::ostream&
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



inline std::ostream&
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



inline policy_map_key_t::policy_map_key_t() :
      name_(), feature_() {
}

inline policy_map_key_t::policy_map_key_t(std::string const & name, 
                                          policy_feature_t feature) :
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
policy_map_key_t::feature_is(policy_feature_t feature) {
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

inline uint32_t
policy_map_key_t::hash() const {
   uint32_t ret = 0;
   ret ^= std::hash<std::string>()(name_);
   ret = hash_mix::mix((uint8_t *)&feature_,
              sizeof(policy_feature_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
policy_map_key_t::to_string() const {
   std::ostringstream ss;
   ss << "policy_map_key_t(";
   ss << "name='" << name_ << "'";
   ss << ", feature=" << feature_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const policy_map_key_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
inline policy_map_action_t::policy_map_action_t() :
      action_type_(), nexthop_group_name_(), nexthops_(), vrf_(), dscp_(), 
      traffic_class_() {
}

inline policy_map_action_t::policy_map_action_t(policy_action_type_t action_type) :
      action_type_(action_type), nexthop_group_name_(), nexthops_(), vrf_(), 
      dscp_(), traffic_class_() {
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

inline std::string
policy_map_action_t::vrf() const {
   return vrf_;
}

inline void
policy_map_action_t::vrf_is(std::string const & vrf) {
   vrf_ = vrf;
}

inline uint8_t
policy_map_action_t::dscp() const {
   return dscp_;
}

inline void
policy_map_action_t::dscp_is(uint8_t dscp) {
   dscp_ = dscp;
}

inline uint8_t
policy_map_action_t::traffic_class() const {
   return traffic_class_;
}

inline void
policy_map_action_t::traffic_class_is(uint8_t traffic_class) {
   traffic_class_ = traffic_class;
}

inline bool
policy_map_action_t::operator==(policy_map_action_t const & other) const {
   return action_type_ == other.action_type_ &&
          nexthop_group_name_ == other.nexthop_group_name_ &&
          nexthops_ == other.nexthops_ &&
          vrf_ == other.vrf_ &&
          dscp_ == other.dscp_ &&
          traffic_class_ == other.traffic_class_;
}

inline bool
policy_map_action_t::operator!=(policy_map_action_t const & other) const {
   return !operator==(other);
}

inline bool
policy_map_action_t::operator<(policy_map_action_t const & other) const {
   if(action_type_ != other.action_type_) {
      return action_type_ < other.action_type_;
   } else if(nexthop_group_name_ != other.nexthop_group_name_) {
      return nexthop_group_name_ < other.nexthop_group_name_;
   } else if(vrf_ != other.vrf_) {
      return vrf_ < other.vrf_;
   } else if(dscp_ != other.dscp_) {
      return dscp_ < other.dscp_;
   } else if(traffic_class_ != other.traffic_class_) {
      return traffic_class_ < other.traffic_class_;
   }
   return false;
}

inline uint32_t
policy_map_action_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&action_type_,
              sizeof(policy_action_type_t), ret);
   ret ^= std::hash<std::string>()(nexthop_group_name_);
   for (auto it=nexthops_.cbegin(); it!=nexthops_.cend(); ++it) {
      ret = hash_mix::mix((uint8_t *)&(*it),
            sizeof(ip_addr_t), ret);
   }
   ret ^= std::hash<std::string>()(vrf_);
   ret = hash_mix::mix((uint8_t *)&dscp_,
              sizeof(uint8_t), ret);
   ret = hash_mix::mix((uint8_t *)&traffic_class_,
              sizeof(uint8_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
policy_map_action_t::to_string() const {
   std::ostringstream ss;
   ss << "policy_map_action_t(";
   ss << "action_type=" << action_type_;
   ss << ", nexthop_group_name='" << nexthop_group_name_ << "'";
   ss << ", nexthops=" <<"'";
   bool first_nexthops = true;
   for (auto it=nexthops_.cbegin(); it!=nexthops_.cend(); ++it) {
      if (first_nexthops) {
         ss << (*it).to_string();
         first_nexthops = false;
      } else {
         ss << "," << (*it).to_string();
      }
   }
   ss << "'";
   ss << ", vrf='" << vrf_ << "'";
   ss << ", dscp=" << dscp_;
   ss << ", traffic_class=" << traffic_class_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const policy_map_action_t& obj) {
   os << obj.to_string();
   return os;
}



inline policy_map_rule_t::policy_map_rule_t() :
      class_map_key_(), policy_map_rule_type_(POLICY_RULE_TYPE_CLASSMAP), 
      raw_rule_(), actions_() {
}

inline policy_map_rule_t::policy_map_rule_t(class_map_key_t const & class_map_key) :
      class_map_key_(class_map_key), 
      policy_map_rule_type_(POLICY_RULE_TYPE_CLASSMAP), raw_rule_(), actions_() {
}

inline class_map_key_t
policy_map_rule_t::class_map_key() const {
   return class_map_key_;
}

inline void
policy_map_rule_t::class_map_key_is(class_map_key_t const & class_map_key) {
   class_map_key_ = class_map_key;
}

inline policy_map_rule_type_t
policy_map_rule_t::policy_map_rule_type() const {
   return policy_map_rule_type_;
}

inline void
policy_map_rule_t::policy_map_rule_type_is(
         policy_map_rule_type_t policy_map_rule_type) {
   policy_map_rule_type_ = policy_map_rule_type;
}

inline acl_rule_ip_t
policy_map_rule_t::raw_rule() const {
   return raw_rule_;
}

inline void
policy_map_rule_t::raw_rule_is(acl_rule_ip_t raw_rule) {
   raw_rule_ = raw_rule;
}

inline std::set<policy_map_action_t> const &
policy_map_rule_t::actions() const {
   return actions_;
}

inline void
policy_map_rule_t::actions_is(std::set<policy_map_action_t> const & actions) {
   actions_ = actions;
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

inline void
policy_map_rule_t::raw_rule_is(acl_rule_ip_t acl_rule, 
                               policy_map_rule_type_t rule_type) {
   policy_map_rule_type_is(rule_type);
   raw_rule_is(acl_rule);
}

inline bool
policy_map_rule_t::operator==(policy_map_rule_t const & other) const {
   return class_map_key_ == other.class_map_key_ &&
          policy_map_rule_type_ == other.policy_map_rule_type_ &&
          raw_rule_ == other.raw_rule_ &&
          actions_ == other.actions_;
}

inline bool
policy_map_rule_t::operator!=(policy_map_rule_t const & other) const {
   return !operator==(other);
}

inline bool
policy_map_rule_t::operator<(policy_map_rule_t const & other) const {
   if(class_map_key_ != other.class_map_key_) {
      return class_map_key_ < other.class_map_key_;
   } else if(policy_map_rule_type_ != other.policy_map_rule_type_) {
      return policy_map_rule_type_ < other.policy_map_rule_type_;
   } else if(raw_rule_ != other.raw_rule_) {
      return raw_rule_ < other.raw_rule_;
   } else if(actions_ != other.actions_) {
      return actions_ < other.actions_;
   }
   return false;
}

inline uint32_t
policy_map_rule_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&class_map_key_,
              sizeof(class_map_key_t), ret);
   ret = hash_mix::mix((uint8_t *)&policy_map_rule_type_,
              sizeof(policy_map_rule_type_t), ret);
   ret = hash_mix::mix((uint8_t *)&raw_rule_,
              sizeof(acl_rule_ip_t), ret);
   for (auto it=actions_.cbegin(); it!=actions_.cend(); ++it) {
      ret = hash_mix::mix((uint8_t *)&(*it),
            sizeof(policy_map_action_t), ret);
   }
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
policy_map_rule_t::to_string() const {
   std::ostringstream ss;
   ss << "policy_map_rule_t(";
   ss << "class_map_key=" << class_map_key_;
   ss << ", policy_map_rule_type=" << policy_map_rule_type_;
   ss << ", raw_rule=" << raw_rule_;
   ss << ", actions=" <<"'";
   bool first_actions = true;
   for (auto it=actions_.cbegin(); it!=actions_.cend(); ++it) {
      if (first_actions) {
         ss << (*it).to_string();
         first_actions = false;
      } else {
         ss << "," << (*it).to_string();
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const policy_map_rule_t& obj) {
   os << obj.to_string();
   return os;
}



inline policy_map_t::policy_map_t() :
      key_(), rules_(), persistent_(false) {
}

inline policy_map_t::policy_map_t(policy_map_key_t const & key) :
      key_(key), rules_(), persistent_(false) {
}

inline policy_map_key_t
policy_map_t::key() const {
   return key_;
}

inline void
policy_map_t::key_is(policy_map_key_t const & key) {
   key_ = key;
}

inline std::map<uint32_t, policy_map_rule_t> const &
policy_map_t::rules() const {
   return rules_;
}

inline void
policy_map_t::rule_del(uint32_t key) {
   rules_.erase(key);
}

inline bool
policy_map_t::persistent() const {
   return persistent_;
}

inline void
policy_map_t::persistent_is(bool persistent) {
   persistent_ = persistent;
}

inline bool
policy_map_t::operator==(policy_map_t const & other) const {
   return key_ == other.key_ &&
          rules_ == other.rules_ &&
          persistent_ == other.persistent_;
}

inline bool
policy_map_t::operator!=(policy_map_t const & other) const {
   return !operator==(other);
}

inline bool
policy_map_t::operator<(policy_map_t const & other) const {
   if(key_ != other.key_) {
      return key_ < other.key_;
   } else if(rules_ != other.rules_) {
      return rules_ < other.rules_;
   } else if(persistent_ != other.persistent_) {
      return persistent_ < other.persistent_;
   }
   return false;
}

inline uint32_t
policy_map_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&key_,
              sizeof(policy_map_key_t), ret);
   for (auto it=rules_.cbegin(); it!=rules_.cend(); ++it) {
      ret = hash_mix::mix((uint8_t *)&it->first,
                 sizeof(uint32_t), ret);
      ret = hash_mix::mix((uint8_t *)&it->second,
                 sizeof(policy_map_rule_t), ret);
   }
   ret = hash_mix::mix((uint8_t *)&persistent_,
              sizeof(bool), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
policy_map_t::to_string() const {
   std::ostringstream ss;
   ss << "policy_map_t(";
   ss << "key=" << key_;
   ss << ", rules=" <<"'";
   bool first_rules = true;
   for (auto it=rules_.cbegin(); it!=rules_.cend(); ++it) {
      if (first_rules) {
         ss << it->first << "=" << it->second;
         first_rules = false;
      } else {
         ss << "," << it->first << "=" << it->second;
      }
   }
   ss << "'";
   ss << ", persistent=" << persistent_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const policy_map_t& obj) {
   os << obj.to_string();
   return os;
}



inline unsupported_policy_feature_error::unsupported_policy_feature_error(
         policy_feature_t policy_feature) noexcept :
      unsupported_error(std::string("Unsupported policy feature")), 
      policy_feature_(policy_feature) {
   
}

inline 
unsupported_policy_feature_error::~unsupported_policy_feature_error() noexcept {
   
}

inline policy_feature_t
unsupported_policy_feature_error::policy_feature() const noexcept {
   return policy_feature_;
}

inline void
unsupported_policy_feature_error::raise() const {
   throw *this;
}

inline uint32_t
unsupported_policy_feature_error::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&policy_feature_,
              sizeof(policy_feature_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
unsupported_policy_feature_error::to_string() const {
   std::ostringstream ss;
   ss << "unsupported_policy_feature_error(";
   ss << "policy_feature=" << policy_feature_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const unsupported_policy_feature_error& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_POLICY_MAP_H
