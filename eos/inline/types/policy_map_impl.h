// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_POLICY_MAP_IMPL_H
#define EOS_INLINE_TYPES_POLICY_MAP_IMPL_H

namespace eos {













policy_map_key_impl_t::policy_map_key_impl_t() :
      name_(), feature_() {
}

policy_map_key_impl_t::policy_map_key_impl_t(std::string const & name,
                                                    policy_feature_t feature) :
      name_(name), feature_(feature) {
}

std::string
policy_map_key_impl_t::name() const {
   return name_;
}

void
policy_map_key_impl_t::name_is(std::string const & name) {
   name_ = name;
}

policy_feature_t
policy_map_key_impl_t::feature() const {
   return feature_;
}

void
policy_map_key_impl_t::feature_is(policy_feature_t feature) {
   feature_ = feature;
}

bool
policy_map_key_impl_t::operator==(policy_map_key_impl_t const & other) const {
   return name_ == other.name_ &&
          feature_ == other.feature_;
}

bool
policy_map_key_impl_t::operator!=(policy_map_key_impl_t const & other) const {
   return !operator==(other);
}

bool
policy_map_key_impl_t::operator<(policy_map_key_impl_t const & other) const {
   if(name_ != other.name_) {
      return name_ < other.name_;
   } else if(feature_ != other.feature_) {
      return feature_ < other.feature_;
   }
   return false;
}

uint32_t
policy_map_key_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
policy_map_key_impl_t::mix_me(hash_mix & h) const {
   h.mix(name_); // std::string
   h.mix(feature_); // policy_feature_t
}

std::string
policy_map_key_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "policy_map_key_t(";
   ss << "name='" << name_ << "'";
   ss << ", feature=" << feature_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const policy_map_key_impl_t& obj) {
   os << obj.to_string();
   return os;
}







// Default constructor of a PBR/QOS action.
policy_map_action_impl_t::policy_map_action_impl_t() :
      action_type_(), nexthop_group_name_(), nexthops_(), vrf_(), dscp_(),
      traffic_class_() {
}

policy_map_action_impl_t::policy_map_action_impl_t(
         policy_action_type_t action_type) :
      action_type_(action_type), nexthop_group_name_(), nexthops_(), vrf_(),
      dscp_(), traffic_class_() {
}


policy_map_action_impl_t::~policy_map_action_impl_t() {

}

policy_action_type_t
policy_map_action_impl_t::action_type() const {
   return action_type_;
}

void
policy_map_action_impl_t::action_type_is(policy_action_type_t action_type) {
   action_type_ = action_type;
}

std::string
policy_map_action_impl_t::nexthop_group_name() const {
   return nexthop_group_name_;
}

void
policy_map_action_impl_t::nexthop_group_name_is(
         std::string const & nexthop_group_name) {
   nexthop_group_name_ = nexthop_group_name;
}

std::unordered_set<ip_addr_t> const &
policy_map_action_impl_t::nexthops() const {
   return nexthops_;
}

void
policy_map_action_impl_t::nexthops_is(
         std::unordered_set<ip_addr_t> const & nexthops) {
   nexthops_ = nexthops;
}

void
policy_map_action_impl_t::nexthop_set(ip_addr_t const & value) {
   nexthops_.insert(value);
}

void
policy_map_action_impl_t::nexthop_del(ip_addr_t const & value) {
   nexthops_.erase(value);
}

std::string
policy_map_action_impl_t::vrf() const {
   return vrf_;
}

void
policy_map_action_impl_t::vrf_is(std::string const & vrf) {
   vrf_ = vrf;
}

uint8_t
policy_map_action_impl_t::dscp() const {
   return dscp_;
}

void
policy_map_action_impl_t::dscp_is(uint8_t dscp) {
   dscp_ = dscp;
}

uint8_t
policy_map_action_impl_t::traffic_class() const {
   return traffic_class_;
}

void
policy_map_action_impl_t::traffic_class_is(uint8_t traffic_class) {
   traffic_class_ = traffic_class;
}

bool
policy_map_action_impl_t::operator==(policy_map_action_impl_t const & other) const {
   return action_type_ == other.action_type_ &&
          nexthop_group_name_ == other.nexthop_group_name_ &&
          nexthops_ == other.nexthops_ &&
          vrf_ == other.vrf_ &&
          dscp_ == other.dscp_ &&
          traffic_class_ == other.traffic_class_;
}

bool
policy_map_action_impl_t::operator!=(policy_map_action_impl_t const & other) const {
   return !operator==(other);
}

bool
policy_map_action_impl_t::operator<(policy_map_action_impl_t const & other) const {
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

uint32_t
policy_map_action_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
policy_map_action_impl_t::mix_me(hash_mix & h) const {
   h.mix(action_type_); // policy_action_type_t
   h.mix(nexthop_group_name_); // std::string
   for (auto it=nexthops_.cbegin();
        it!=nexthops_.cend(); ++it) {
      h.mix(*it); // ip_addr_t
   }
   h.mix(vrf_); // std::string
   h.mix(dscp_); // uint8_t
   h.mix(traffic_class_); // uint8_t
}

std::string
policy_map_action_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "policy_map_action_t(";
   ss << "action_type=" << action_type_;
   ss << ", nexthop_group_name='" << nexthop_group_name_ << "'";
   ss << ", nexthops=" <<"'";
   bool first_nexthops = true;
   for (auto it=nexthops_.cbegin();
        it!=nexthops_.cend(); ++it) {
      if (first_nexthops) {
         ss << (*it);
         first_nexthops = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", vrf='" << vrf_ << "'";
   ss << ", dscp=" << dscp_;
   ss << ", traffic_class=" << traffic_class_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const policy_map_action_impl_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor of a traffic-policy action.
traffic_policy_action_impl_t::traffic_policy_action_impl_t() :
      action_type_(), counter_name_(), goto_class_name_(), goto_next_(), dscp_(),
      traffic_class_(), vrf_(), mirror_session_(), police_rate_(),
      police_burst_size_(), police_rate_unit_(), police_burst_unit_(),
      nexthop_groups_(), nexthops_() {
}

traffic_policy_action_impl_t::traffic_policy_action_impl_t(
         traffic_policy_action_type_t action_type) :
      action_type_(action_type), counter_name_(), goto_class_name_(), goto_next_(),
      dscp_(), traffic_class_(), vrf_(), mirror_session_(), police_rate_(),
      police_burst_size_(), police_rate_unit_(), police_burst_unit_(),
      nexthop_groups_(), nexthops_() {
}


traffic_policy_action_impl_t::~traffic_policy_action_impl_t() {

}

traffic_policy_action_type_t
traffic_policy_action_impl_t::action_type() const {
   return action_type_;
}

void
traffic_policy_action_impl_t::action_type_is(
         traffic_policy_action_type_t action_type) {
   action_type_ = action_type;
}

std::string
traffic_policy_action_impl_t::counter_name() const {
   return counter_name_;
}

void
traffic_policy_action_impl_t::counter_name_is(std::string const & counter_name) {
   counter_name_ = counter_name;
}

std::string
traffic_policy_action_impl_t::goto_class_name() const {
   return goto_class_name_;
}

void
traffic_policy_action_impl_t::goto_class_name_is(
         std::string const & goto_class_name) {
   goto_class_name_ = goto_class_name;
}

bool
traffic_policy_action_impl_t::goto_next() const {
   return goto_next_;
}

void
traffic_policy_action_impl_t::goto_next_is(bool const & goto_next) {
   goto_next_ = goto_next;
}

uint8_t
traffic_policy_action_impl_t::dscp() const {
   return dscp_;
}

void
traffic_policy_action_impl_t::dscp_is(uint8_t dscp) {
   dscp_ = dscp;
}

uint8_t
traffic_policy_action_impl_t::traffic_class() const {
   return traffic_class_;
}

void
traffic_policy_action_impl_t::traffic_class_is(uint8_t traffic_class) {
   traffic_class_ = traffic_class;
}

std::string
traffic_policy_action_impl_t::vrf() const {
   return vrf_;
}

void
traffic_policy_action_impl_t::vrf_is(std::string const & vrf) {
   vrf_ = vrf;
}

std::string
traffic_policy_action_impl_t::mirror_session() const {
   return mirror_session_;
}

void
traffic_policy_action_impl_t::mirror_session_is(std::string const & mirror_session)
       {
   mirror_session_ = mirror_session;
}

uint64_t
traffic_policy_action_impl_t::police_rate() const {
   return police_rate_;
}

void
traffic_policy_action_impl_t::police_rate_is(uint64_t const & police_rate) {
   police_rate_ = police_rate;
}

uint64_t
traffic_policy_action_impl_t::police_burst_size() const {
   return police_burst_size_;
}

void
traffic_policy_action_impl_t::police_burst_size_is(
         uint64_t const & police_burst_size) {
   police_burst_size_ = police_burst_size;
}

police_rate_unit_t
traffic_policy_action_impl_t::police_rate_unit() const {
   return police_rate_unit_;
}

void
traffic_policy_action_impl_t::police_rate_unit_is(
         police_rate_unit_t const & police_rate_unit) {
   police_rate_unit_ = police_rate_unit;
}

police_burst_unit_t
traffic_policy_action_impl_t::police_burst_unit() const {
   return police_burst_unit_;
}

void
traffic_policy_action_impl_t::police_burst_unit_is(
         police_burst_unit_t const & police_burst_unit) {
   police_burst_unit_ = police_burst_unit;
}

std::unordered_set<std::string> const &
traffic_policy_action_impl_t::nexthop_groups() const {
   return nexthop_groups_;
}

void
traffic_policy_action_impl_t::nexthop_groups_is(
         std::unordered_set<std::string> const & nexthop_groups) {
   nexthop_groups_ = nexthop_groups;
}

void
traffic_policy_action_impl_t::nexthop_group_set(std::string const & value) {
   nexthop_groups_.insert(value);
}

void
traffic_policy_action_impl_t::nexthop_group_del(std::string const & value) {
   nexthop_groups_.erase(value);
}

std::unordered_set<ip_addr_t> const &
traffic_policy_action_impl_t::nexthops() const {
   return nexthops_;
}

void
traffic_policy_action_impl_t::nexthops_is(
         std::unordered_set<ip_addr_t> const & nexthops) {
   nexthops_ = nexthops;
}

void
traffic_policy_action_impl_t::nexthop_set(ip_addr_t const & value) {
   nexthops_.insert(value);
}

void
traffic_policy_action_impl_t::nexthop_del(ip_addr_t const & value) {
   nexthops_.erase(value);
}

bool
traffic_policy_action_impl_t::operator==(
         traffic_policy_action_impl_t const & other) const {
   return action_type_ == other.action_type_ &&
          counter_name_ == other.counter_name_ &&
          goto_class_name_ == other.goto_class_name_ &&
          goto_next_ == other.goto_next_ &&
          dscp_ == other.dscp_ &&
          traffic_class_ == other.traffic_class_ &&
          vrf_ == other.vrf_ &&
          mirror_session_ == other.mirror_session_ &&
          police_rate_ == other.police_rate_ &&
          police_burst_size_ == other.police_burst_size_ &&
          police_rate_unit_ == other.police_rate_unit_ &&
          police_burst_unit_ == other.police_burst_unit_ &&
          nexthop_groups_ == other.nexthop_groups_ &&
          nexthops_ == other.nexthops_;
}

bool
traffic_policy_action_impl_t::operator!=(
         traffic_policy_action_impl_t const & other) const {
   return !operator==(other);
}

bool
traffic_policy_action_impl_t::operator<(traffic_policy_action_impl_t const & other)
       const {
   if(action_type_ != other.action_type_) {
      return action_type_ < other.action_type_;
   } else if(counter_name_ != other.counter_name_) {
      return counter_name_ < other.counter_name_;
   } else if(goto_class_name_ != other.goto_class_name_) {
      return goto_class_name_ < other.goto_class_name_;
   } else if(goto_next_ != other.goto_next_) {
      return goto_next_ < other.goto_next_;
   } else if(dscp_ != other.dscp_) {
      return dscp_ < other.dscp_;
   } else if(traffic_class_ != other.traffic_class_) {
      return traffic_class_ < other.traffic_class_;
   } else if(vrf_ != other.vrf_) {
      return vrf_ < other.vrf_;
   } else if(mirror_session_ != other.mirror_session_) {
      return mirror_session_ < other.mirror_session_;
   } else if(police_rate_ != other.police_rate_) {
      return police_rate_ < other.police_rate_;
   } else if(police_burst_size_ != other.police_burst_size_) {
      return police_burst_size_ < other.police_burst_size_;
   } else if(police_rate_unit_ != other.police_rate_unit_) {
      return police_rate_unit_ < other.police_rate_unit_;
   } else if(police_burst_unit_ != other.police_burst_unit_) {
      return police_burst_unit_ < other.police_burst_unit_;
   }
   return false;
}

uint32_t
traffic_policy_action_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
traffic_policy_action_impl_t::mix_me(hash_mix & h) const {
   h.mix(action_type_); // traffic_policy_action_type_t
   h.mix(counter_name_); // std::string
   h.mix(goto_class_name_); // std::string
   h.mix(goto_next_); // bool
   h.mix(dscp_); // uint8_t
   h.mix(traffic_class_); // uint8_t
   h.mix(vrf_); // std::string
   h.mix(mirror_session_); // std::string
   h.mix(police_rate_); // uint64_t
   h.mix(police_burst_size_); // uint64_t
   h.mix(police_rate_unit_); // police_rate_unit_t
   h.mix(police_burst_unit_); // police_burst_unit_t
   for (auto it=nexthop_groups_.cbegin();
        it!=nexthop_groups_.cend(); ++it) {
      h.mix(*it); // std::string
   }
   for (auto it=nexthops_.cbegin();
        it!=nexthops_.cend(); ++it) {
      h.mix(*it); // ip_addr_t
   }
}

std::string
traffic_policy_action_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "traffic_policy_action_t(";
   ss << "action_type=" << action_type_;
   ss << ", counter_name='" << counter_name_ << "'";
   ss << ", goto_class_name='" << goto_class_name_ << "'";
   ss << ", goto_next=" << goto_next_;
   ss << ", dscp=" << dscp_;
   ss << ", traffic_class=" << traffic_class_;
   ss << ", vrf='" << vrf_ << "'";
   ss << ", mirror_session='" << mirror_session_ << "'";
   ss << ", police_rate=" << police_rate_;
   ss << ", police_burst_size=" << police_burst_size_;
   ss << ", police_rate_unit=" << police_rate_unit_;
   ss << ", police_burst_unit=" << police_burst_unit_;
   ss << ", nexthop_groups=" <<"'";
   bool first_nexthop_groups = true;
   for (auto it=nexthop_groups_.cbegin();
        it!=nexthop_groups_.cend(); ++it) {
      if (first_nexthop_groups) {
         ss << (*it);
         first_nexthop_groups = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", nexthops=" <<"'";
   bool first_nexthops = true;
   for (auto it=nexthops_.cbegin();
        it!=nexthops_.cend(); ++it) {
      if (first_nexthops) {
         ss << (*it);
         first_nexthops = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const traffic_policy_action_impl_t& obj) {
   os << obj.to_string();
   return os;
}



policy_map_rule_impl_t::policy_map_rule_impl_t() :
      class_map_key_(), policy_map_rule_type_(POLICY_RULE_TYPE_CLASSMAP),
      raw_rule_(), actions_() {
}

policy_map_rule_impl_t::policy_map_rule_impl_t(
         class_map_key_t const & class_map_key) :
      class_map_key_(class_map_key),
      policy_map_rule_type_(POLICY_RULE_TYPE_CLASSMAP), raw_rule_(), actions_() {
}

class_map_key_t
policy_map_rule_impl_t::class_map_key() const {
   return class_map_key_;
}

void
policy_map_rule_impl_t::class_map_key_is(class_map_key_t const & class_map_key) {
   class_map_key_ = class_map_key;
}

policy_map_rule_type_t
policy_map_rule_impl_t::policy_map_rule_type() const {
   return policy_map_rule_type_;
}

void
policy_map_rule_impl_t::policy_map_rule_type_is(
         policy_map_rule_type_t policy_map_rule_type) {
   policy_map_rule_type_ = policy_map_rule_type;
}

acl_rule_ip_t
policy_map_rule_impl_t::raw_rule() const {
   return raw_rule_;
}

void
policy_map_rule_impl_t::raw_rule_is(acl_rule_ip_t raw_rule) {
   raw_rule_ = raw_rule;
}

std::set<policy_map_action_t> const &
policy_map_rule_impl_t::actions() const {
   return actions_;
}

void
policy_map_rule_impl_t::actions_is(std::set<policy_map_action_t> const & actions) {
   actions_ = actions;
}

void
policy_map_rule_impl_t::action_set(policy_map_action_t const & value) {
   actions_.insert(value);
}

void
policy_map_rule_impl_t::action_del(policy_map_action_t const & value) {
   actions_.erase(value);
}

void
policy_map_rule_impl_t::action_del(policy_action_type_t action_type) {
   auto act = actions_.begin();
   while(act != actions_.end()) {
      if(act->action_type() == action_type) {
         act = actions_.erase(act);
      } else {
         ++act;
      }
   }
}

void
policy_map_rule_impl_t::raw_rule_is(acl_rule_ip_t acl_rule,
                                    policy_map_rule_type_t rule_type) {
   policy_map_rule_type_is(rule_type);
   raw_rule_is(acl_rule);
}

bool
policy_map_rule_impl_t::operator==(policy_map_rule_impl_t const & other) const {
   return class_map_key_ == other.class_map_key_ &&
          policy_map_rule_type_ == other.policy_map_rule_type_ &&
          raw_rule_ == other.raw_rule_ &&
          actions_ == other.actions_;
}

bool
policy_map_rule_impl_t::operator!=(policy_map_rule_impl_t const & other) const {
   return !operator==(other);
}

bool
policy_map_rule_impl_t::operator<(policy_map_rule_impl_t const & other) const {
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

uint32_t
policy_map_rule_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
policy_map_rule_impl_t::mix_me(hash_mix & h) const {
   h.mix(class_map_key_); // class_map_key_t
   h.mix(policy_map_rule_type_); // policy_map_rule_type_t
   h.mix(raw_rule_); // acl_rule_ip_t
   for (auto it=actions_.cbegin();
        it!=actions_.cend(); ++it) {
      h.mix(*it); // policy_map_action_t
   }
}

std::string
policy_map_rule_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "policy_map_rule_t(";
   ss << "class_map_key=" << class_map_key_;
   ss << ", policy_map_rule_type=" << policy_map_rule_type_;
   ss << ", raw_rule=" << raw_rule_;
   ss << ", actions=" <<"'";
   bool first_actions = true;
   for (auto it=actions_.cbegin();
        it!=actions_.cend(); ++it) {
      if (first_actions) {
         ss << (*it);
         first_actions = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const policy_map_rule_impl_t& obj) {
   os << obj.to_string();
   return os;
}



policy_map_impl_t::policy_map_impl_t() :
      key_(), rules_() {
}

policy_map_impl_t::policy_map_impl_t(policy_map_key_t const & key) :
      key_(key), rules_() {
}

policy_map_key_t
policy_map_impl_t::key() const {
   return key_;
}

void
policy_map_impl_t::key_is(policy_map_key_t const & key) {
   key_ = key;
}

std::map<uint32_t, policy_map_rule_t> const &
policy_map_impl_t::rules() const {
   return rules_;
}

void
policy_map_impl_t::rules_is(std::map<uint32_t, policy_map_rule_t> const & rules) {

      uint32_t mpls_ = 0;
      uint32_t non_mpls_ = 0;
      std::string const QOS_RULE_CONFIG_ERROR_ = \
         "QoS policy maps do not support MPLS match rules";
      std::string const QOS_RAW_RULE_CONFIG_ERROR_ = \
         "QoS policy maps do not support raw match statements";
      std::string const CLASS_MAP_MPLS_ANY_ = "__mpls_permit_any__";
      std::string const RULE_CONFIG_ERROR_ = \
          "Policy maps have either one MPLS match rule or "
          "a collection of other rules";

      for(auto it = rules.cbegin(); it != rules.cend(); ++it) {
         if (it->second.class_map_key().name() == CLASS_MAP_MPLS_ANY_) {
            mpls_++;
         } else {
            non_mpls_++;
         }
         if((key_.feature() == POLICY_FEATURE_QOS) &&
            (it->second.policy_map_rule_type() != POLICY_RULE_TYPE_CLASSMAP)) {
            panic(configuration_error(QOS_RAW_RULE_CONFIG_ERROR_));
         }
      }
      // Check if the collection's invariant has been invalidated
      if((non_mpls_ > 0 && mpls_ > 0) || mpls_ > 1) {
         panic(configuration_error(RULE_CONFIG_ERROR_));
      }
      if(mpls_ != 0 && key_.feature() == POLICY_FEATURE_QOS) {
         panic(configuration_error(QOS_RULE_CONFIG_ERROR_));
      }
      rules_ = rules;

}

void
policy_map_impl_t::rule_set(uint32_t key, policy_map_rule_t const & value) {

      std::string const QOS_RULE_CONFIG_ERROR_ = \
         "QoS policy maps do not support MPLS match rules";
      std::string const QOS_RAW_RULE_CONFIG_ERROR_ = \
         "QoS policy maps do not support raw match statements";
      std::string const CLASS_MAP_MPLS_ANY_ = "__mpls_permit_any__";
      std::string const RULE_CONFIG_ERROR_ = \
          "Policy maps have either one MPLS match rule or "
          "a collection of other rules";

      if(value.class_map_key().name() == CLASS_MAP_MPLS_ANY_ &&
         key_.feature() == POLICY_FEATURE_QOS) {
         panic(configuration_error(QOS_RULE_CONFIG_ERROR_));
      }
      if((key_.feature() == POLICY_FEATURE_QOS) &&
         (value.policy_map_rule_type() != POLICY_RULE_TYPE_CLASSMAP)) {
         panic(configuration_error(QOS_RAW_RULE_CONFIG_ERROR_));
      }
      // We can set only one MPLS rule and no others in a map.
      if(rules_.size() > 1 ||
           (rules_.size() && rules_.cbegin()->first != key)) {
         if(value.class_map_key().name() == CLASS_MAP_MPLS_ANY_){
            panic(configuration_error(RULE_CONFIG_ERROR_));
         } else {
            if(rules_.cbegin()->second.class_map_key().name() ==
                  CLASS_MAP_MPLS_ANY_) {
               panic(configuration_error(RULE_CONFIG_ERROR_));
            }
         }
      }
      rules_[key] = value;

}

void
policy_map_impl_t::rule_del(uint32_t key) {
   rules_.erase(key);
}

bool
policy_map_impl_t::operator==(policy_map_impl_t const & other) const {
   return key_ == other.key_ &&
          rules_ == other.rules_;
}

bool
policy_map_impl_t::operator!=(policy_map_impl_t const & other) const {
   return !operator==(other);
}

bool
policy_map_impl_t::operator<(policy_map_impl_t const & other) const {
   if(key_ != other.key_) {
      return key_ < other.key_;
   } else if(rules_ != other.rules_) {
      return rules_ < other.rules_;
   }
   return false;
}

uint32_t
policy_map_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
policy_map_impl_t::mix_me(hash_mix & h) const {
   h.mix(key_); // policy_map_key_t
   for (auto it=rules_.cbegin();
        it!=rules_.cend(); ++it) {
      h.mix(it->first); // uint32_t
      h.mix(it->second); // policy_map_rule_t
   }
}

std::string
policy_map_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "policy_map_t(";
   ss << "key=" << key_;
   ss << ", rules=" <<"'";
   bool first_rules = true;
   for (auto it=rules_.cbegin();
        it!=rules_.cend(); ++it) {
      if (first_rules) {
         ss << it->first << "=" << it->second;
         first_rules = false;
      } else {
         ss << "," << it->first << "=" << it->second;
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const policy_map_impl_t& obj) {
   os << obj.to_string();
   return os;
}



traffic_policy_rule_impl_t::traffic_policy_rule_impl_t() :
      match_rule_name_(), traffic_policy_rule_type_(), raw_rule_(), actions_() {
}

traffic_policy_rule_impl_t::traffic_policy_rule_impl_t(
         std::string match_rule_name,
         traffic_policy_rule_type_t traffic_policy_rule_type) :
      match_rule_name_(match_rule_name),
      traffic_policy_rule_type_(traffic_policy_rule_type), raw_rule_(), actions_() {
}

std::string
traffic_policy_rule_impl_t::match_rule_name() const {
   return match_rule_name_;
}

traffic_policy_rule_type_t
traffic_policy_rule_impl_t::traffic_policy_rule_type() const {
   return traffic_policy_rule_type_;
}

tp_rule_filter_t
traffic_policy_rule_impl_t::raw_rule() const {
   return raw_rule_;
}

std::set<traffic_policy_action_t> const &
traffic_policy_rule_impl_t::actions() const {
   return actions_;
}

void
traffic_policy_rule_impl_t::actions_is(
         std::set<traffic_policy_action_t> const & actions) {
   actions_ = actions;
}

void
traffic_policy_rule_impl_t::action_set(traffic_policy_action_t const & value) {
   actions_.insert(value);
}

void
traffic_policy_rule_impl_t::action_del(traffic_policy_action_t const & value) {
   actions_.erase(value);
}

void
traffic_policy_rule_impl_t::raw_rule_is(tp_rule_filter_t const & raw_rule) {

      std::string const TP_FILTER_TYPE_MISMATCH_CONFIG_ERROR_ = \
         "Configured filter type does not match the traffic-policy rule type";
      if(traffic_policy_rule_type_ != raw_rule.filter_type()) {
            panic(configuration_error(TP_FILTER_TYPE_MISMATCH_CONFIG_ERROR_));
      }
      raw_rule_ = raw_rule;
                 
}

void
traffic_policy_rule_impl_t::action_del(traffic_policy_action_type_t action_type) {
   auto act = actions_.begin();
   while(act != actions_.end()) {
      if(act->action_type() == action_type) {
         act = actions_.erase(act);
      } else {
         ++act;
      }
   }
}

bool
traffic_policy_rule_impl_t::operator==(traffic_policy_rule_impl_t const & other)
       const {
   return match_rule_name_ == other.match_rule_name_ &&
          traffic_policy_rule_type_ == other.traffic_policy_rule_type_ &&
          raw_rule_ == other.raw_rule_ &&
          actions_ == other.actions_;
}

bool
traffic_policy_rule_impl_t::operator!=(traffic_policy_rule_impl_t const & other)
       const {
   return !operator==(other);
}

bool
traffic_policy_rule_impl_t::operator<(traffic_policy_rule_impl_t const & other)
       const {
   if(match_rule_name_ != other.match_rule_name_) {
      return match_rule_name_ < other.match_rule_name_;
   } else if(traffic_policy_rule_type_ != other.traffic_policy_rule_type_) {
      return traffic_policy_rule_type_ < other.traffic_policy_rule_type_;
   } else if(raw_rule_ != other.raw_rule_) {
      return raw_rule_ < other.raw_rule_;
   } else if(actions_ != other.actions_) {
      return actions_ < other.actions_;
   }
   return false;
}

uint32_t
traffic_policy_rule_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
traffic_policy_rule_impl_t::mix_me(hash_mix & h) const {
   h.mix(match_rule_name_); // std::string
   h.mix(traffic_policy_rule_type_); // traffic_policy_rule_type_t
   h.mix(raw_rule_); // tp_rule_filter_t
   for (auto it=actions_.cbegin();
        it!=actions_.cend(); ++it) {
      h.mix(*it); // traffic_policy_action_t
   }
}

std::string
traffic_policy_rule_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "traffic_policy_rule_t(";
   ss << "match_rule_name='" << match_rule_name_ << "'";
   ss << ", traffic_policy_rule_type=" << traffic_policy_rule_type_;
   ss << ", raw_rule=" << raw_rule_;
   ss << ", actions=" <<"'";
   bool first_actions = true;
   for (auto it=actions_.cbegin();
        it!=actions_.cend(); ++it) {
      if (first_actions) {
         ss << (*it);
         first_actions = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const traffic_policy_rule_impl_t& obj) {
   os << obj.to_string();
   return os;
}



traffic_policy_impl_t::traffic_policy_impl_t(std::string const & key) :
      key_(key), named_counters_(), rules_() {
}

std::string
traffic_policy_impl_t::key() const {
   return key_;
}

std::unordered_set<std::string> const &
traffic_policy_impl_t::named_counters() const {
   return named_counters_;
}

void
traffic_policy_impl_t::named_counters_is(
         std::unordered_set<std::string> const & named_counters) {
   named_counters_ = named_counters;
}

void
traffic_policy_impl_t::named_counter_set(std::string const & value) {
   named_counters_.insert(value);
}

void
traffic_policy_impl_t::named_counter_del(std::string const & value) {
   named_counters_.erase(value);
}

std::map<uint32_t, traffic_policy_rule_t> const &
traffic_policy_impl_t::rules() const {
   return rules_;
}

void
traffic_policy_impl_t::rules_is(
         std::map<uint32_t, traffic_policy_rule_t> const & rules) {
   rules_ = rules;
}

void
traffic_policy_impl_t::rule_set(uint32_t key, traffic_policy_rule_t const & value) {
   rules_[key] = value;
}

void
traffic_policy_impl_t::rule_del(uint32_t key) {
   rules_.erase(key);
}

bool
traffic_policy_impl_t::operator==(traffic_policy_impl_t const & other) const {
   return key_ == other.key_ &&
          named_counters_ == other.named_counters_ &&
          rules_ == other.rules_;
}

bool
traffic_policy_impl_t::operator!=(traffic_policy_impl_t const & other) const {
   return !operator==(other);
}

bool
traffic_policy_impl_t::operator<(traffic_policy_impl_t const & other) const {
   if(key_ != other.key_) {
      return key_ < other.key_;
   } else if(rules_ != other.rules_) {
      return rules_ < other.rules_;
   }
   return false;
}

uint32_t
traffic_policy_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
traffic_policy_impl_t::mix_me(hash_mix & h) const {
   h.mix(key_); // std::string
   for (auto it=named_counters_.cbegin();
        it!=named_counters_.cend(); ++it) {
      h.mix(*it); // std::string
   }
   for (auto it=rules_.cbegin();
        it!=rules_.cend(); ++it) {
      h.mix(it->first); // uint32_t
      h.mix(it->second); // traffic_policy_rule_t
   }
}

std::string
traffic_policy_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "traffic_policy_t(";
   ss << "key='" << key_ << "'";
   ss << ", named_counters=" <<"'";
   bool first_named_counters = true;
   for (auto it=named_counters_.cbegin();
        it!=named_counters_.cend(); ++it) {
      if (first_named_counters) {
         ss << (*it);
         first_named_counters = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", rules=" <<"'";
   bool first_rules = true;
   for (auto it=rules_.cbegin();
        it!=rules_.cend(); ++it) {
      if (first_rules) {
         ss << it->first << "=" << it->second;
         first_rules = false;
      } else {
         ss << "," << it->first << "=" << it->second;
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const traffic_policy_impl_t& obj) {
   os << obj.to_string();
   return os;
}



traffic_policy_counter_data_impl_t::traffic_policy_counter_data_impl_t() :
      pktHits_(), byteHits_(), pktDrops_(), byteDrops_() {
}

traffic_policy_counter_data_impl_t::traffic_policy_counter_data_impl_t(
         uint64_t pktHits, uint64_t byteHits, uint64_t pktDrops,
         uint64_t byteDrops) :
      pktHits_(pktHits), byteHits_(byteHits), pktDrops_(pktDrops),
      byteDrops_(byteDrops) {
}

uint64_t
traffic_policy_counter_data_impl_t::pktHits() const {
   return pktHits_;
}

uint64_t
traffic_policy_counter_data_impl_t::byteHits() const {
   return byteHits_;
}

uint64_t
traffic_policy_counter_data_impl_t::pktDrops() const {
   return pktDrops_;
}

uint64_t
traffic_policy_counter_data_impl_t::byteDrops() const {
   return byteDrops_;
}

bool
traffic_policy_counter_data_impl_t::operator==(
         traffic_policy_counter_data_impl_t const & other) const {
   return pktHits_ == other.pktHits_ &&
          byteHits_ == other.byteHits_ &&
          pktDrops_ == other.pktDrops_ &&
          byteDrops_ == other.byteDrops_;
}

bool
traffic_policy_counter_data_impl_t::operator!=(
         traffic_policy_counter_data_impl_t const & other) const {
   return !operator==(other);
}

bool
traffic_policy_counter_data_impl_t::operator<(
         traffic_policy_counter_data_impl_t const & other) const {
   if(pktHits_ != other.pktHits_) {
      return pktHits_ < other.pktHits_;
   } else if(byteHits_ != other.byteHits_) {
      return byteHits_ < other.byteHits_;
   } else if(pktDrops_ != other.pktDrops_) {
      return pktDrops_ < other.pktDrops_;
   } else if(byteDrops_ != other.byteDrops_) {
      return byteDrops_ < other.byteDrops_;
   }
   return false;
}

uint32_t
traffic_policy_counter_data_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
traffic_policy_counter_data_impl_t::mix_me(hash_mix & h) const {
   h.mix(pktHits_); // uint64_t
   h.mix(byteHits_); // uint64_t
   h.mix(pktDrops_); // uint64_t
   h.mix(byteDrops_); // uint64_t
}

std::string
traffic_policy_counter_data_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "traffic_policy_counter_data_t(";
   ss << "pktHits=" << pktHits_;
   ss << ", byteHits=" << byteHits_;
   ss << ", pktDrops=" << pktDrops_;
   ss << ", byteDrops=" << byteDrops_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const traffic_policy_counter_data_impl_t& obj) {
   os << obj.to_string();
   return os;
}



traffic_policy_counter_impl_t::traffic_policy_counter_impl_t(
         std::string const & key) :
      key_(key), named_counter_data_(), class_counter_data_() {
}

std::string
traffic_policy_counter_impl_t::key() const {
   return key_;
}

std::map<std::string, traffic_policy_counter_data_t> const &
traffic_policy_counter_impl_t::named_counter_data() const {
   return named_counter_data_;
}

void
traffic_policy_counter_impl_t::named_counter_data_is(
         
         std::map<std::string, traffic_policy_counter_data_t> const &
         named_counter_data) {
   named_counter_data_ = named_counter_data;
}

void
traffic_policy_counter_impl_t::named_counter_data_set(
         std::string const & key, traffic_policy_counter_data_t const & value) {
   named_counter_data_[key] = value;
}

void
traffic_policy_counter_impl_t::named_counter_data_del(std::string const & key) {
   named_counter_data_.erase(key);
}

std::map<std::string, traffic_policy_counter_data_t> const &
traffic_policy_counter_impl_t::class_counter_data() const {
   return class_counter_data_;
}

void
traffic_policy_counter_impl_t::class_counter_data_is(
         
         std::map<std::string, traffic_policy_counter_data_t> const &
         class_counter_data) {
   class_counter_data_ = class_counter_data;
}

void
traffic_policy_counter_impl_t::class_counter_data_set(
         std::string const & key, traffic_policy_counter_data_t const & value) {
   class_counter_data_[key] = value;
}

void
traffic_policy_counter_impl_t::class_counter_data_del(std::string const & key) {
   class_counter_data_.erase(key);
}

bool
traffic_policy_counter_impl_t::operator==(
         traffic_policy_counter_impl_t const & other) const {
   return key_ == other.key_ &&
          named_counter_data_ == other.named_counter_data_ &&
          class_counter_data_ == other.class_counter_data_;
}

bool
traffic_policy_counter_impl_t::operator!=(
         traffic_policy_counter_impl_t const & other) const {
   return !operator==(other);
}

bool
traffic_policy_counter_impl_t::operator<(
         traffic_policy_counter_impl_t const & other) const {
   if(key_ != other.key_) {
      return key_ < other.key_;
   } else if(named_counter_data_ != other.named_counter_data_) {
      return named_counter_data_ < other.named_counter_data_;
   } else if(class_counter_data_ != other.class_counter_data_) {
      return class_counter_data_ < other.class_counter_data_;
   }
   return false;
}

uint32_t
traffic_policy_counter_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
traffic_policy_counter_impl_t::mix_me(hash_mix & h) const {
   h.mix(key_); // std::string
   for (auto it=named_counter_data_.cbegin();
        it!=named_counter_data_.cend(); ++it) {
      h.mix(it->first); // std::string
      h.mix(it->second); // traffic_policy_counter_data_t
   }
   for (auto it=class_counter_data_.cbegin();
        it!=class_counter_data_.cend(); ++it) {
      h.mix(it->first); // std::string
      h.mix(it->second); // traffic_policy_counter_data_t
   }
}

std::string
traffic_policy_counter_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "traffic_policy_counter_t(";
   ss << "key='" << key_ << "'";
   ss << ", named_counter_data=" <<"'";
   bool first_named_counter_data = true;
   for (auto it=named_counter_data_.cbegin();
        it!=named_counter_data_.cend(); ++it) {
      if (first_named_counter_data) {
         ss << it->first << "=" << it->second;
         first_named_counter_data = false;
      } else {
         ss << "," << it->first << "=" << it->second;
      }
   }
   ss << "'";
   ss << ", class_counter_data=" <<"'";
   bool first_class_counter_data = true;
   for (auto it=class_counter_data_.cbegin();
        it!=class_counter_data_.cend(); ++it) {
      if (first_class_counter_data) {
         ss << it->first << "=" << it->second;
         first_class_counter_data = false;
      } else {
         ss << "," << it->first << "=" << it->second;
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const traffic_policy_counter_impl_t& obj) {
   os << obj.to_string();
   return os;
}







policy_map_hw_status_key_impl_t::policy_map_hw_status_key_impl_t() :
      intf_id_(), direction_() {
}

policy_map_hw_status_key_impl_t::policy_map_hw_status_key_impl_t(
         intf_id_t intf_id, acl_direction_t direction) :
      intf_id_(intf_id), direction_(direction) {
}

intf_id_t
policy_map_hw_status_key_impl_t::intf_id() const {
   return intf_id_;
}

void
policy_map_hw_status_key_impl_t::intf_id_is(intf_id_t intf_id) {
   intf_id_ = intf_id;
}

acl_direction_t
policy_map_hw_status_key_impl_t::direction() const {
   return direction_;
}

void
policy_map_hw_status_key_impl_t::direction_is(acl_direction_t direction) {
   direction_ = direction;
}

bool
policy_map_hw_status_key_impl_t::operator==(
         policy_map_hw_status_key_impl_t const & other) const {
   return intf_id_ == other.intf_id_ &&
          direction_ == other.direction_;
}

bool
policy_map_hw_status_key_impl_t::operator!=(
         policy_map_hw_status_key_impl_t const & other) const {
   return !operator==(other);
}

bool
policy_map_hw_status_key_impl_t::operator<(
         policy_map_hw_status_key_impl_t const & other) const {
   if(intf_id_ != other.intf_id_) {
      return intf_id_ < other.intf_id_;
   } else if(direction_ != other.direction_) {
      return direction_ < other.direction_;
   }
   return false;
}

uint32_t
policy_map_hw_status_key_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
policy_map_hw_status_key_impl_t::mix_me(hash_mix & h) const {
   h.mix(intf_id_); // intf_id_t
   h.mix(direction_); // acl_direction_t
}

std::string
policy_map_hw_status_key_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "policy_map_hw_status_key_t(";
   ss << "intf_id=" << intf_id_;
   ss << ", direction=" << direction_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const policy_map_hw_status_key_impl_t& obj) {
   os << obj.to_string();
   return os;
}



policy_map_hw_statuses_impl_t::policy_map_hw_statuses_impl_t() :
      intf_statuses_() {
}

policy_map_hw_statuses_impl_t::policy_map_hw_statuses_impl_t(
         
         std::map<policy_map_hw_status_key_t, policy_map_status_t> const &
         intf_statuses) :
      intf_statuses_(intf_statuses) {
}

std::map<policy_map_hw_status_key_t, policy_map_status_t> const &
policy_map_hw_statuses_impl_t::intf_statuses() const {
   return intf_statuses_;
}

void
policy_map_hw_statuses_impl_t::intf_statuses_is(
         
         std::map<policy_map_hw_status_key_t, policy_map_status_t> const &
         intf_statuses) {
   intf_statuses_ = intf_statuses;
}

void
policy_map_hw_statuses_impl_t::intf_statuse_set(
         policy_map_hw_status_key_t const & key, policy_map_status_t const & value)
       {
   intf_statuses_[key] = value;
}

void
policy_map_hw_statuses_impl_t::intf_statuse_del(
         policy_map_hw_status_key_t const & key) {
   intf_statuses_.erase(key);
}

bool
policy_map_hw_statuses_impl_t::operator==(
         policy_map_hw_statuses_impl_t const & other) const {
   return intf_statuses_ == other.intf_statuses_;
}

bool
policy_map_hw_statuses_impl_t::operator!=(
         policy_map_hw_statuses_impl_t const & other) const {
   return !operator==(other);
}

bool
policy_map_hw_statuses_impl_t::operator<(
         policy_map_hw_statuses_impl_t const & other) const {
   if(intf_statuses_ != other.intf_statuses_) {
      return intf_statuses_ < other.intf_statuses_;
   }
   return false;
}

uint32_t
policy_map_hw_statuses_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
policy_map_hw_statuses_impl_t::mix_me(hash_mix & h) const {
   for (auto it=intf_statuses_.cbegin();
        it!=intf_statuses_.cend(); ++it) {
      h.mix(it->first); // policy_map_hw_status_key_t
      h.mix(it->second); // policy_map_status_t
   }
}

std::string
policy_map_hw_statuses_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "policy_map_hw_statuses_t(";
   ss << "intf_statuses=" <<"'";
   bool first_intf_statuses = true;
   for (auto it=intf_statuses_.cbegin();
        it!=intf_statuses_.cend(); ++it) {
      if (first_intf_statuses) {
         ss << it->first << "=" << it->second;
         first_intf_statuses = false;
      } else {
         ss << "," << it->first << "=" << it->second;
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const policy_map_hw_statuses_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/policy_map.h>

#endif // EOS_INLINE_TYPES_POLICY_MAP_IMPL_H
