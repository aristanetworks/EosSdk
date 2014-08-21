// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MPLS_ROUTE_H
#define EOS_INLINE_TYPES_MPLS_ROUTE_H

namespace eos {

inline mpls_route_key_t::mpls_route_key_t() :
      top_label_(0), metric_(0) {
}

inline mpls_route_key_t::mpls_route_key_t(mpls_label_t const & top_label, 
                                   mpls_route_metric_t metric) :
      top_label_(top_label), metric_(metric) {
}

inline mpls_label_t
mpls_route_key_t::top_label() const {
   return top_label_;
}

inline void
mpls_route_key_t::top_label_is(mpls_label_t const & top_label) {
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

inline std::string
mpls_route_key_t::to_string() const {
   std::ostringstream ss;
   ss << "mpls_route_key_t(";
   ss << "top_label=" << top_label_.to_string();
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
      key_(), persistent_(false) {
}

inline mpls_route_t::mpls_route_t(mpls_route_key_t const & key) :
      key_(key), persistent_(false) {
}

inline mpls_route_key_t
mpls_route_t::key() const {
   return key_;
}

inline void
mpls_route_t::key_is(mpls_route_key_t const & key) {
   key_ = key;
}

inline bool
mpls_route_t::persistent() const {
   return persistent_;
}

inline void
mpls_route_t::persistent_is(bool persistent) {
   persistent_ = persistent;
}

inline bool
mpls_route_t::operator==(mpls_route_t const & other) const {
   return key_ == other.key_ &&
          persistent_ == other.persistent_;
}

inline bool
mpls_route_t::operator!=(mpls_route_t const & other) const {
   return !operator==(other);
}

inline std::string
mpls_route_t::to_string() const {
   std::ostringstream ss;
   ss << "mpls_route_t(";
   ss << "key=" << key_;
   ss << ", persistent=" << persistent_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const mpls_route_t& obj) {
   os << obj.to_string();
   return os;
}



inline mpls_route_via_t::mpls_route_via_t() :
      route_key_(), hop_(), intf_(), pushswap_label_(0), label_action_(MPLS_ACTION_NULL), 
      ttl_mode_(MPLS_TTLMODE_NULL), payload_type_(MPLS_PAYLOAD_TYPE_NULL) {
}

inline mpls_route_via_t::mpls_route_via_t(mpls_route_key_t const & route_key) :
      route_key_(route_key), hop_(), intf_(), pushswap_label_(0), 
      label_action_(MPLS_ACTION_NULL), ttl_mode_(MPLS_TTLMODE_NULL), 
      payload_type_(MPLS_PAYLOAD_TYPE_NULL) {
}

inline mpls_route_key_t
mpls_route_via_t::route_key() const {
   return route_key_;
}

inline void
mpls_route_via_t::route_key_is(mpls_route_key_t const & route_key) {
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
mpls_route_via_t::operator==(mpls_route_via_t const & other) const {
   return route_key_ == other.route_key_ &&
          hop_ == other.hop_ &&
          intf_ == other.intf_ &&
          pushswap_label_ == other.pushswap_label_ &&
          label_action_ == other.label_action_ &&
          ttl_mode_ == other.ttl_mode_ &&
          payload_type_ == other.payload_type_;
}

inline bool
mpls_route_via_t::operator!=(mpls_route_via_t const & other) const {
   return !operator==(other);
}

inline std::string
mpls_route_via_t::to_string() const {
   std::ostringstream ss;
   ss << "mpls_route_via_t(";
   ss << "route_key=" << route_key_;
   ss << ", hop=" << hop_.to_string();
   ss << ", intf=" << intf_.to_string();
   ss << ", pushswap_label=" << pushswap_label_.to_string();
   ss << ", label_action=" << label_action_;
   ss << ", ttl_mode=" << ttl_mode_;
   ss << ", payload_type=" << payload_type_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const mpls_route_via_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_MPLS_ROUTE_H
