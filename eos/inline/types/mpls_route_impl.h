// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MPLS_ROUTE_IMPL_H
#define EOS_INLINE_TYPES_MPLS_ROUTE_IMPL_H

namespace eos {

mpls_route_key_impl_t::mpls_route_key_impl_t() :
      labels_(std::vector< mpls_label_t >{0}), metric_(0) {
}

mpls_route_key_impl_t::mpls_route_key_impl_t(mpls_label_t top_label,
                                                    mpls_route_metric_t metric) :
      labels_(std::vector< mpls_label_t >{top_label}), metric_(metric) {
   if (top_label.label() > (uint32_t)mpls_label_t::MAX) {
      panic(invalid_mpls_label(top_label.label()));
   }
}

mpls_route_key_impl_t::mpls_route_key_impl_t(
         std::vector<mpls_label_t> const & labels, mpls_route_metric_t metric) :
      labels_(labels), metric_(metric) {
   for (auto label: labels) {
      if (label.label() > (uint32_t)mpls_label_t::MAX) {
         panic(invalid_mpls_label(label.label()));
      }
   }
}

std::vector<mpls_label_t> const &
mpls_route_key_impl_t::labels() const {
   return labels_;
}

void
mpls_route_key_impl_t::labels_is(std::vector<mpls_label_t> const & labels) {
   labels_ = labels;
}

void
mpls_route_key_impl_t::label_set(uint32_t index, mpls_label_t const & value) {
   labels_.insert(labels_.begin() + index, value);
}

void
mpls_route_key_impl_t::label_del(uint32_t index) {
   labels_.erase(labels_.begin() + index);
}

mpls_route_metric_t
mpls_route_key_impl_t::metric() const {
   return metric_;
}

void
mpls_route_key_impl_t::metric_is(mpls_route_metric_t metric) {
   metric_ = metric;
}

mpls_label_t
mpls_route_key_impl_t::top_label() const {

   if (labels_.empty()) {
      return mpls_label_t();
   } else {
      return labels_.front();
   }

}

void
mpls_route_key_impl_t::top_label_is(mpls_label_t top_label) {

   labels_ = std::vector< mpls_label_t > { top_label };

}

bool
mpls_route_key_impl_t::operator==(mpls_route_key_impl_t const & other) const {
   return labels_ == other.labels_ &&
          metric_ == other.metric_;
}

bool
mpls_route_key_impl_t::operator!=(mpls_route_key_impl_t const & other) const {
   return !operator==(other);
}

bool
mpls_route_key_impl_t::operator<(mpls_route_key_impl_t const & other) const {
   if(labels_ != other.labels_) {
      return labels_ < other.labels_;
   } else if(metric_ != other.metric_) {
      return metric_ < other.metric_;
   }
   return false;
}

uint32_t
mpls_route_key_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
mpls_route_key_impl_t::mix_me(hash_mix & h) const {
   for (auto it=labels_.cbegin();
        it!=labels_.cend(); ++it) {
      h.mix(*it); // mpls_label_t
   }
   h.mix(metric_); // mpls_route_metric_t
}

std::string
mpls_route_key_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "mpls_route_key_t(";
   ss << "labels=" <<"'";
   bool first_labels = true;
   for (auto it=labels_.cbegin();
        it!=labels_.cend(); ++it) {
      if (first_labels) {
         ss << (*it);
         first_labels = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", metric=" << metric_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const mpls_route_key_impl_t& obj) {
   os << obj.to_string();
   return os;
}



mpls_route_impl_t::mpls_route_impl_t() :
      key_() {
}

mpls_route_impl_t::mpls_route_impl_t(mpls_route_key_t key) :
      key_(key) {
}

mpls_route_key_t
mpls_route_impl_t::key() const {
   return key_;
}

void
mpls_route_impl_t::key_is(mpls_route_key_t key) {
   key_ = key;
}

bool
mpls_route_impl_t::operator==(mpls_route_impl_t const & other) const {
   return key_ == other.key_;
}

bool
mpls_route_impl_t::operator!=(mpls_route_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
mpls_route_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
mpls_route_impl_t::mix_me(hash_mix & h) const {
   h.mix(key_); // mpls_route_key_t
}

std::string
mpls_route_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "mpls_route_t(";
   ss << "key=" << key_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const mpls_route_impl_t& obj) {
   os << obj.to_string();
   return os;
}



mpls_route_via_impl_t::mpls_route_via_impl_t() :
      route_key_(), hop_(), intf_(), pushswap_label_(0),
      label_action_(MPLS_ACTION_NULL), ttl_mode_(MPLS_TTLMODE_NULL),
      payload_type_(MPLS_PAYLOAD_TYPE_NULL), skip_egress_acl_(false),
      nexthop_group_() {
}

mpls_route_via_impl_t::mpls_route_via_impl_t(mpls_route_key_t route_key) :
      route_key_(route_key), hop_(), intf_(), pushswap_label_(0),
      label_action_(MPLS_ACTION_NULL), ttl_mode_(MPLS_TTLMODE_NULL),
      payload_type_(MPLS_PAYLOAD_TYPE_NULL), skip_egress_acl_(false),
      nexthop_group_() {
}

mpls_route_via_impl_t::mpls_route_via_impl_t(mpls_route_key_t route_key,
                                                    mpls_action_t label_action) :
      route_key_(route_key), hop_(), intf_(), pushswap_label_(0),
      label_action_(label_action), ttl_mode_(MPLS_TTLMODE_NULL),
      payload_type_(MPLS_PAYLOAD_TYPE_NULL), skip_egress_acl_(false),
      nexthop_group_() {
}

mpls_route_key_t
mpls_route_via_impl_t::route_key() const {
   return route_key_;
}

void
mpls_route_via_impl_t::route_key_is(mpls_route_key_t route_key) {
   route_key_ = route_key;
}

ip_addr_t
mpls_route_via_impl_t::hop() const {
   return hop_;
}

void
mpls_route_via_impl_t::hop_is(ip_addr_t const & hop) {
   hop_ = hop;
}

intf_id_t
mpls_route_via_impl_t::intf() const {
   return intf_;
}

void
mpls_route_via_impl_t::intf_is(intf_id_t const & intf) {
   intf_ = intf;
}

mpls_label_t
mpls_route_via_impl_t::pushswap_label() const {
   return pushswap_label_;
}

void
mpls_route_via_impl_t::pushswap_label_is(mpls_label_t pushswap_label) {
   pushswap_label_ = pushswap_label;
}

mpls_action_t
mpls_route_via_impl_t::label_action() const {
   return label_action_;
}

void
mpls_route_via_impl_t::label_action_is(mpls_action_t label_action) {
   label_action_ = label_action;
}

mpls_ttl_mode_t
mpls_route_via_impl_t::ttl_mode() const {
   return ttl_mode_;
}

void
mpls_route_via_impl_t::ttl_mode_is(mpls_ttl_mode_t ttl_mode) {
   ttl_mode_ = ttl_mode;
}

mpls_payload_type_t
mpls_route_via_impl_t::payload_type() const {
   return payload_type_;
}

void
mpls_route_via_impl_t::payload_type_is(mpls_payload_type_t payload_type) {
   payload_type_ = payload_type;
}

bool
mpls_route_via_impl_t::skip_egress_acl() const {
   return skip_egress_acl_;
}

void
mpls_route_via_impl_t::skip_egress_acl_is(bool skip_egress_acl) {
   skip_egress_acl_ = skip_egress_acl;
}

std::string
mpls_route_via_impl_t::nexthop_group() const {
   return nexthop_group_;
}

void
mpls_route_via_impl_t::nexthop_group_is(std::string nexthop_group) {
   nexthop_group_ = nexthop_group;
}

bool
mpls_route_via_impl_t::operator==(mpls_route_via_impl_t const & other) const {
   return route_key_ == other.route_key_ &&
          hop_ == other.hop_ &&
          intf_ == other.intf_ &&
          pushswap_label_ == other.pushswap_label_ &&
          label_action_ == other.label_action_ &&
          ttl_mode_ == other.ttl_mode_ &&
          payload_type_ == other.payload_type_ &&
          skip_egress_acl_ == other.skip_egress_acl_ &&
          nexthop_group_ == other.nexthop_group_;
}

bool
mpls_route_via_impl_t::operator!=(mpls_route_via_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
mpls_route_via_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
mpls_route_via_impl_t::mix_me(hash_mix & h) const {
   h.mix(route_key_); // mpls_route_key_t
   h.mix(hop_); // ip_addr_t
   h.mix(intf_); // intf_id_t
   h.mix(pushswap_label_); // mpls_label_t
   h.mix(label_action_); // mpls_action_t
   h.mix(ttl_mode_); // mpls_ttl_mode_t
   h.mix(payload_type_); // mpls_payload_type_t
   h.mix(skip_egress_acl_); // bool
   h.mix(nexthop_group_); // std::string
}

std::string
mpls_route_via_impl_t::to_string() const {
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
   ss << ", nexthop_group='" << nexthop_group_ << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const mpls_route_via_impl_t& obj) {
   os << obj.to_string();
   return os;
}



mpls_fec_id_impl_t::mpls_fec_id_impl_t() :
      id_(0) {
}

mpls_fec_id_impl_t::mpls_fec_id_impl_t(uint64_t id) :
      id_(id) {
}

uint64_t
mpls_fec_id_impl_t::id() const {
   return id_;
}

void
mpls_fec_id_impl_t::id_is(uint64_t id) {
   id_ = id;
}

bool
mpls_fec_id_impl_t::operator==(mpls_fec_id_impl_t const & other) const {
   return id_ == other.id_;
}

bool
mpls_fec_id_impl_t::operator!=(mpls_fec_id_impl_t const & other) const {
   return !operator==(other);
}

bool
mpls_fec_id_impl_t::operator<(mpls_fec_id_impl_t const & other) const {
   if(id_ != other.id_) {
      return id_ < other.id_;
   }
   return false;
}

uint32_t
mpls_fec_id_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
mpls_fec_id_impl_t::mix_me(hash_mix & h) const {
   h.mix(id_); // uint64_t
}

std::string
mpls_fec_id_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "mpls_fec_id_t(";
   ss << "id=" << id_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const mpls_fec_id_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/mpls_route.h>

#endif // EOS_INLINE_TYPES_MPLS_ROUTE_IMPL_H
