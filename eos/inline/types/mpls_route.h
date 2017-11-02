// Copyright (c) 2017 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MPLS_ROUTE_H
#define EOS_INLINE_TYPES_MPLS_ROUTE_H

namespace eos {

inline mpls_route_key_t::mpls_route_key_t() :
      top_label_(0), metric_(0) {
}

inline mpls_route_key_t::mpls_route_key_t(mpls_label_t top_label,
                                          mpls_route_metric_t metric) :
      top_label_(top_label), metric_(metric) {
}

inline mpls_label_t
mpls_route_key_t::top_label() const {
   return top_label_;
}

inline void
mpls_route_key_t::top_label_is(mpls_label_t top_label) {
   top_label_ = top_label;
}

inline mpls_route_metric_t
mpls_route_key_t::metric() const {
   return metric_;
}

inline void
mpls_route_key_t::metric_is(mpls_route_metric_t metric) {
   metric_ = metric;
}

inline bool
mpls_route_key_t::operator==(mpls_route_key_t const & other) const {
   return top_label_ == other.top_label_ &&
          metric_ == other.metric_;
}

inline bool
mpls_route_key_t::operator!=(mpls_route_key_t const & other) const {
   return !operator==(other);
}

inline uint32_t
mpls_route_key_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&top_label_,
              sizeof(mpls_label_t), ret);
   ret = hash_mix::mix((uint8_t *)&metric_,
              sizeof(mpls_route_metric_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
mpls_route_key_t::to_string() const {
   std::ostringstream ss;
   ss << "mpls_route_key_t(";
   ss << "top_label=" << top_label_;
   ss << ", metric=" << metric_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const mpls_route_key_t& obj) {
   os << obj.to_string();
   return os;
}



inline mpls_route_t::mpls_route_t() :
      key_() {
}

inline mpls_route_t::mpls_route_t(mpls_route_key_t key) :
      key_(key) {
}

inline mpls_route_key_t
mpls_route_t::key() const {
   return key_;
}

inline void
mpls_route_t::key_is(mpls_route_key_t key) {
   key_ = key;
}

inline bool
mpls_route_t::operator==(mpls_route_t const & other) const {
   return key_ == other.key_;
}

inline bool
mpls_route_t::operator!=(mpls_route_t const & other) const {
   return !operator==(other);
}

inline uint32_t
mpls_route_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&key_,
              sizeof(mpls_route_key_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
mpls_route_t::to_string() const {
   std::ostringstream ss;
   ss << "mpls_route_t(";
   ss << "key=" << key_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const mpls_route_t& obj) {
   os << obj.to_string();
   return os;
}



inline mpls_route_via_t::mpls_route_via_t() :
      route_key_(), hop_(), intf_(), pushswap_label_(0),
      label_action_(MPLS_ACTION_NULL), ttl_mode_(MPLS_TTLMODE_NULL),
      payload_type_(MPLS_PAYLOAD_TYPE_NULL), skip_egress_acl_(false) {
}

inline mpls_route_via_t::mpls_route_via_t(mpls_route_key_t route_key) :
      route_key_(route_key), hop_(), intf_(), pushswap_label_(0),
      label_action_(MPLS_ACTION_NULL), ttl_mode_(MPLS_TTLMODE_NULL),
      payload_type_(MPLS_PAYLOAD_TYPE_NULL), skip_egress_acl_(false) {
}

inline mpls_route_via_t::mpls_route_via_t(mpls_route_key_t route_key,
                                          mpls_action_t label_action) :
      route_key_(route_key), hop_(), intf_(), pushswap_label_(0),
      label_action_(label_action), ttl_mode_(MPLS_TTLMODE_NULL),
      payload_type_(MPLS_PAYLOAD_TYPE_NULL), skip_egress_acl_(false) {
}

inline mpls_route_key_t
mpls_route_via_t::route_key() const {
   return route_key_;
}

inline void
mpls_route_via_t::route_key_is(mpls_route_key_t route_key) {
   route_key_ = route_key;
}

inline ip_addr_t
mpls_route_via_t::hop() const {
   return hop_;
}

inline void
mpls_route_via_t::hop_is(ip_addr_t const & hop) {
   hop_ = hop;
}

inline intf_id_t
mpls_route_via_t::intf() const {
   return intf_;
}

inline void
mpls_route_via_t::intf_is(intf_id_t const & intf) {
   intf_ = intf;
}

inline mpls_label_t
mpls_route_via_t::pushswap_label() const {
   return pushswap_label_;
}

inline void
mpls_route_via_t::pushswap_label_is(mpls_label_t pushswap_label) {
   pushswap_label_ = pushswap_label;
}

inline mpls_action_t
mpls_route_via_t::label_action() const {
   return label_action_;
}

inline void
mpls_route_via_t::label_action_is(mpls_action_t label_action) {
   label_action_ = label_action;
}

inline mpls_ttl_mode_t
mpls_route_via_t::ttl_mode() const {
   return ttl_mode_;
}

inline void
mpls_route_via_t::ttl_mode_is(mpls_ttl_mode_t ttl_mode) {
   ttl_mode_ = ttl_mode;
}

inline mpls_payload_type_t
mpls_route_via_t::payload_type() const {
   return payload_type_;
}

inline void
mpls_route_via_t::payload_type_is(mpls_payload_type_t payload_type) {
   payload_type_ = payload_type;
}

inline bool
mpls_route_via_t::skip_egress_acl() const {
   return skip_egress_acl_;
}

inline void
mpls_route_via_t::skip_egress_acl_is(bool skip_egress_acl) {
   skip_egress_acl_ = skip_egress_acl;
}

inline bool
mpls_route_via_t::operator==(mpls_route_via_t const & other) const {
   return route_key_ == other.route_key_ &&
          hop_ == other.hop_ &&
          intf_ == other.intf_ &&
          pushswap_label_ == other.pushswap_label_ &&
          label_action_ == other.label_action_ &&
          ttl_mode_ == other.ttl_mode_ &&
          payload_type_ == other.payload_type_ &&
          skip_egress_acl_ == other.skip_egress_acl_;
}

inline bool
mpls_route_via_t::operator!=(mpls_route_via_t const & other) const {
   return !operator==(other);
}

inline uint32_t
mpls_route_via_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&route_key_,
              sizeof(mpls_route_key_t), ret);
   ret = hash_mix::mix((uint8_t *)&hop_,
              sizeof(ip_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&intf_,
              sizeof(intf_id_t), ret);
   ret = hash_mix::mix((uint8_t *)&pushswap_label_,
              sizeof(mpls_label_t), ret);
   ret = hash_mix::mix((uint8_t *)&label_action_,
              sizeof(mpls_action_t), ret);
   ret = hash_mix::mix((uint8_t *)&ttl_mode_,
              sizeof(mpls_ttl_mode_t), ret);
   ret = hash_mix::mix((uint8_t *)&payload_type_,
              sizeof(mpls_payload_type_t), ret);
   ret = hash_mix::mix((uint8_t *)&skip_egress_acl_,
              sizeof(bool), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
mpls_route_via_t::to_string() const {
   std::ostringstream ss;
   ss << "mpls_route_via_t(";
   ss << "route_key=" << route_key_;
   ss << ", hop=" << hop_;
   ss << ", intf=" << intf_;
   ss << ", pushswap_label=" << pushswap_label_;
   ss << ", label_action=" << label_action_;
   ss << ", ttl_mode=" << ttl_mode_;
   ss << ", payload_type=" << payload_type_;
   ss << ", skip_egress_acl=" << skip_egress_acl_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const mpls_route_via_t& obj) {
   os << obj.to_string();
   return os;
}



inline mpls_fec_id_t::mpls_fec_id_t() :
      id_(0) {
}

inline mpls_fec_id_t::mpls_fec_id_t(uint64_t id) :
      id_(id) {
}

inline uint64_t
mpls_fec_id_t::id() const {
   return id_;
}

inline void
mpls_fec_id_t::id_is(uint64_t id) {
   id_ = id;
}

inline bool
mpls_fec_id_t::operator==(mpls_fec_id_t const & other) const {
   return id_ == other.id_;
}

inline bool
mpls_fec_id_t::operator!=(mpls_fec_id_t const & other) const {
   return !operator==(other);
}

inline bool
mpls_fec_id_t::operator<(mpls_fec_id_t const & other) const {
   if(id_ != other.id_) {
      return id_ < other.id_;
   }
   return false;
}

inline uint32_t
mpls_fec_id_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&id_,
              sizeof(uint64_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
mpls_fec_id_t::to_string() const {
   std::ostringstream ss;
   ss << "mpls_fec_id_t(";
   ss << "id=" << id_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const mpls_fec_id_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_MPLS_ROUTE_H
