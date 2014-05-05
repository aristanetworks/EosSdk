// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_CLASS_MAP_H
#define INLINE_CLASS_MAP_H

namespace eos {

inline
class_map_rule_t::class_map_rule_t() : acl_key_() {
}

inline
class_map_rule_t::class_map_rule_t(acl_key_t const & acl_key)
      : acl_key_(acl_key) {
}

inline acl_key_t const &
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

inline
class_map_t::class_map_t() : key_(), rules_() {
}

inline
class_map_t::class_map_t(class_map_key_t const & key) : key_(key), rules_() {
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
class_map_t::rule_set(uint32_t seq, class_map_rule_t const & rule) {
   rules_[seq] = rule;
}

inline void
class_map_t::rule_del(uint32_t seq) {
   rules_.erase(seq);
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

}

#endif // INLINE_CLASS_MAP_H
