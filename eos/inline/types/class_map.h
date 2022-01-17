// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_CLASS_MAP_H
#define EOS_INLINE_TYPES_CLASS_MAP_H

namespace eos {

// Default constructor.
inline class_map_rule_t::class_map_rule_t() :
      acl_key_() {
}

inline class_map_rule_t::class_map_rule_t(acl_key_t const & acl_key) :
      acl_key_(acl_key) {
}

inline acl_key_t
class_map_rule_t::acl_key() const {
   return acl_key_;
}

inline bool
class_map_rule_t::operator==(class_map_rule_t const & other) const {
   return acl_key_ == other.acl_key_;
}

inline bool
class_map_rule_t::operator!=(class_map_rule_t const & other) const {
   return !operator==(other);
}

inline uint32_t
class_map_rule_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
class_map_rule_t::mix_me(hash_mix & h) const {
   h.mix(acl_key_); // acl_key_t
}

inline std::string
class_map_rule_t::to_string() const {
   std::ostringstream ss;
   ss << "class_map_rule_t(";
   ss << "acl_key=" << acl_key_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const class_map_rule_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
inline class_map_t::class_map_t() :
      key_(), rules_() {
}

inline class_map_t::class_map_t(class_map_key_t const & key) :
      key_(key), rules_() {
}

inline class_map_key_t
class_map_t::key() const {
   return key_;
}

inline void
class_map_t::key_is(class_map_key_t const & key) {
   key_ = key;
}

inline std::map<uint32_t, class_map_rule_t> const &
class_map_t::rules() const {
   return rules_;
}

inline void
class_map_t::rules_is(std::map<uint32_t, class_map_rule_t> const & rules) {
   rules_ = rules;
}

inline void
class_map_t::rule_set(uint32_t key, class_map_rule_t const & value) {
   rules_[key] = value;
}

inline void
class_map_t::rule_del(uint32_t key) {
   rules_.erase(key);
}

inline bool
class_map_t::operator==(class_map_t const & other) const {
   return key_ == other.key_ &&
          rules_ == other.rules_;
}

inline bool
class_map_t::operator!=(class_map_t const & other) const {
   return !operator==(other);
}

inline uint32_t
class_map_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
class_map_t::mix_me(hash_mix & h) const {
   h.mix(key_); // class_map_key_t
   for (auto it=rules_.cbegin(); it!=rules_.cend(); ++it) {
      h.mix(it->first); // uint32_t
      h.mix(it->second); // class_map_rule_t
   }
}

inline std::string
class_map_t::to_string() const {
   std::ostringstream ss;
   ss << "class_map_t(";
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
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const class_map_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_CLASS_MAP_H
