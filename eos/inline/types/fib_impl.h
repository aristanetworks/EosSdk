// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_FIB_IMPL_H
#define EOS_INLINE_TYPES_FIB_IMPL_H

namespace eos {

// Default constructor.
fib_route_key_impl_t::fib_route_key_impl_t() :
      prefix_() {
}

fib_route_key_impl_t::fib_route_key_impl_t(ip_prefix_t const & prefix) :
      prefix_(prefix) {
}

ip_prefix_t
fib_route_key_impl_t::prefix() const {
   return prefix_;
}

void
fib_route_key_impl_t::prefix_is(ip_prefix_t const & prefix) {
   prefix_ = prefix;
}

bool
fib_route_key_impl_t::operator==(fib_route_key_impl_t const & other) const {
   return prefix_ == other.prefix_;
}

bool
fib_route_key_impl_t::operator!=(fib_route_key_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
fib_route_key_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
fib_route_key_impl_t::mix_me(hash_mix & h) const {
   h.mix(prefix_); // ip_prefix_t
}

std::string
fib_route_key_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "fib_route_key_t(";
   ss << "prefix=" << prefix_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const fib_route_key_impl_t& obj) {
   os << obj.to_string();
   return os;
}





// Default constructor.
fib_route_impl_t::fib_route_impl_t() :
      route_key_(), preference_(1), metric_(0), route_type_(), fec_id_(0) {
}

fib_route_impl_t::fib_route_impl_t(fib_route_key_t const & route_key) :
      route_key_(route_key), preference_(1), metric_(0), route_type_(), fec_id_(0) {
}

fib_route_key_t
fib_route_impl_t::route_key() const {
   return route_key_;
}

void
fib_route_impl_t::route_key_is(fib_route_key_t const & route_key) {
   route_key_ = route_key;
}

ip_route_preference_t
fib_route_impl_t::preference() const {
   return preference_;
}

void
fib_route_impl_t::preference_is(ip_route_preference_t preference) {
   preference_ = preference;
}

ip_route_metric_t
fib_route_impl_t::metric() const {
   return metric_;
}

void
fib_route_impl_t::metric_is(ip_route_metric_t metric) {
   metric_ = metric;
}

fib_route_type_t
fib_route_impl_t::route_type() const {
   return route_type_;
}

void
fib_route_impl_t::route_type_is(fib_route_type_t route_type) {
   route_type_ = route_type;
}

uint64_t
fib_route_impl_t::fec_id() const {
   return fec_id_;
}

void
fib_route_impl_t::fec_id_is(uint64_t fec_id) {
   fec_id_ = fec_id;
}

bool
fib_route_impl_t::operator==(fib_route_impl_t const & other) const {
   return route_key_ == other.route_key_ &&
          preference_ == other.preference_ &&
          metric_ == other.metric_ &&
          route_type_ == other.route_type_ &&
          fec_id_ == other.fec_id_;
}

bool
fib_route_impl_t::operator!=(fib_route_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
fib_route_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
fib_route_impl_t::mix_me(hash_mix & h) const {
   h.mix(route_key_); // fib_route_key_t
   h.mix(preference_); // ip_route_preference_t
   h.mix(metric_); // ip_route_metric_t
   h.mix(route_type_); // fib_route_type_t
   h.mix(fec_id_); // uint64_t
}

std::string
fib_route_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "fib_route_t(";
   ss << "route_key=" << route_key_;
   ss << ", preference=" << preference_;
   ss << ", metric=" << metric_;
   ss << ", route_type=" << route_type_;
   ss << ", fec_id=" << fec_id_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const fib_route_impl_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
fib_fec_key_impl_t::fib_fec_key_impl_t() :
      fec_id_(0) {
}

fib_fec_key_impl_t::fib_fec_key_impl_t(uint64_t fec_id) :
      fec_id_(fec_id) {
}

uint64_t
fib_fec_key_impl_t::fec_id() const {
   return fec_id_;
}

void
fib_fec_key_impl_t::fec_id_is(uint64_t fec_id) {
   fec_id_ = fec_id;
}

bool
fib_fec_key_impl_t::operator==(fib_fec_key_impl_t const & other) const {
   return fec_id_ == other.fec_id_;
}

bool
fib_fec_key_impl_t::operator!=(fib_fec_key_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
fib_fec_key_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
fib_fec_key_impl_t::mix_me(hash_mix & h) const {
   h.mix(fec_id_); // uint64_t
}

std::string
fib_fec_key_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "fib_fec_key_t(";
   ss << "fec_id=" << fec_id_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const fib_fec_key_impl_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
fib_via_impl_t::fib_via_impl_t() :
      hop_(), intf_(), mpls_label_() {
}

fib_via_impl_t::fib_via_impl_t(ip_addr_t const & hop, intf_id_t intf) :
      hop_(hop), intf_(intf), mpls_label_() {
}

ip_addr_t
fib_via_impl_t::hop() const {
   return hop_;
}

void
fib_via_impl_t::hop_is(ip_addr_t const & hop) {
   hop_ = hop;
}

intf_id_t
fib_via_impl_t::intf() const {
   return intf_;
}

void
fib_via_impl_t::intf_is(intf_id_t intf) {
   intf_ = intf;
}

mpls_label_t
fib_via_impl_t::mpls_label() const {
   return mpls_label_;
}

void
fib_via_impl_t::mpls_label_is(mpls_label_t mpls_label) {
   mpls_label_ = mpls_label;
}

bool
fib_via_impl_t::operator==(fib_via_impl_t const & other) const {
   return hop_ == other.hop_ &&
          intf_ == other.intf_ &&
          mpls_label_ == other.mpls_label_;
}

bool
fib_via_impl_t::operator!=(fib_via_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
fib_via_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
fib_via_impl_t::mix_me(hash_mix & h) const {
   h.mix(hop_); // ip_addr_t
   h.mix(intf_); // intf_id_t
   h.mix(mpls_label_); // mpls_label_t
}

std::string
fib_via_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "fib_via_t(";
   ss << "hop=" << hop_;
   ss << ", intf=" << intf_;
   ss << ", mpls_label=" << mpls_label_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const fib_via_impl_t& obj) {
   os << obj.to_string();
   return os;
}





// Default constructor.
fib_fec_impl_t::fib_fec_impl_t() :
      fec_key_(), fec_type_(), nexthop_group_name_(), via_() {
}

fib_fec_impl_t::fib_fec_impl_t(fib_fec_key_t fec_key) :
      fec_key_(fec_key), fec_type_(), nexthop_group_name_(), via_() {
}

fib_fec_key_t
fib_fec_impl_t::fec_key() const {
   return fec_key_;
}

void
fib_fec_impl_t::fec_key_is(fib_fec_key_t fec_key) {
   fec_key_ = fec_key;
}

fib_fec_type_t
fib_fec_impl_t::fec_type() const {
   return fec_type_;
}

void
fib_fec_impl_t::fec_type_is(fib_fec_type_t fec_type) {
   fec_type_ = fec_type;
}

std::string
fib_fec_impl_t::nexthop_group_name() const {
   return nexthop_group_name_;
}

void
fib_fec_impl_t::nexthop_group_name_is(std::string nexthop_group_name) {
   nexthop_group_name_ = nexthop_group_name;
}

std::forward_list<fib_via_t> const &
fib_fec_impl_t::via() const {
   return via_;
}

void
fib_fec_impl_t::via_is(std::forward_list<fib_via_t> const & via) {
   via_ = via;
}

void
fib_fec_impl_t::via_set(fib_via_t const & via) {
   via_.push_front(via);
}

void
fib_fec_impl_t::via_del(fib_via_t const & via) {
   via_.remove(via);
}

uint32_t
fib_fec_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
fib_fec_impl_t::mix_me(hash_mix & h) const {
   h.mix(fec_key_); // fib_fec_key_t
   h.mix(fec_type_); // fib_fec_type_t
   h.mix(nexthop_group_name_); // std::string
   for (auto it=via_.cbegin();
        it!=via_.cend(); ++it) {
      h.mix(*it); // fib_via_t
   }
}

std::string
fib_fec_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "fib_fec_t(";
   ss << "fec_key=" << fec_key_;
   ss << ", fec_type=" << fec_type_;
   ss << ", nexthop_group_name='" << nexthop_group_name_ << "'";
   ss << ", via=" <<"'";
   bool first_via = true;
   for (auto it=via_.cbegin();
        it!=via_.cend(); ++it) {
      if (first_via) {
         ss << (*it);
         first_via = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const fib_fec_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/fib.h>

#endif // EOS_INLINE_TYPES_FIB_IMPL_H
