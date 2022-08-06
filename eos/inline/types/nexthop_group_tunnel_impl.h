// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_NEXTHOP_GROUP_TUNNEL_IMPL_H
#define EOS_INLINE_TYPES_NEXTHOP_GROUP_TUNNEL_IMPL_H

namespace eos {

nexthop_group_tunnel_impl_t::nexthop_group_tunnel_impl_t() :
      tunnel_endpoint_(), nhg_name_(), igp_pref_(), igp_metric_() {
}

nexthop_group_tunnel_impl_t::nexthop_group_tunnel_impl_t(
         ip_prefix_t const & tunnel_endpoint, std::string const & nhg_name) :
      tunnel_endpoint_(tunnel_endpoint), nhg_name_(nhg_name), igp_pref_(),
      igp_metric_() {
}

ip_prefix_t
nexthop_group_tunnel_impl_t::tunnel_endpoint() const {
   return tunnel_endpoint_;
}

void
nexthop_group_tunnel_impl_t::tunnel_endpoint_is(
         ip_prefix_t const & tunnel_endpoint) {
   tunnel_endpoint_ = tunnel_endpoint;
}

std::string
nexthop_group_tunnel_impl_t::nhg_name() const {
   return nhg_name_;
}

void
nexthop_group_tunnel_impl_t::nhg_name_is(std::string const & nhg_name) {
   nhg_name_ = nhg_name;
}

uint8_t
nexthop_group_tunnel_impl_t::igp_pref() const {
   return igp_pref_;
}

void
nexthop_group_tunnel_impl_t::igp_pref_is(uint8_t igp_pref) {
   igp_pref_ = igp_pref;
}

uint32_t
nexthop_group_tunnel_impl_t::igp_metric() const {
   return igp_metric_;
}

void
nexthop_group_tunnel_impl_t::igp_metric_is(uint32_t igp_metric) {
   igp_metric_ = igp_metric;
}

bool
nexthop_group_tunnel_impl_t::operator==(nexthop_group_tunnel_impl_t const & other)
       const {
   return tunnel_endpoint_ == other.tunnel_endpoint_ &&
          nhg_name_ == other.nhg_name_ &&
          igp_pref_ == other.igp_pref_ &&
          igp_metric_ == other.igp_metric_;
}

bool
nexthop_group_tunnel_impl_t::operator!=(nexthop_group_tunnel_impl_t const & other)
       const {
   return !operator==(other);
}

uint32_t
nexthop_group_tunnel_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
nexthop_group_tunnel_impl_t::mix_me(hash_mix & h) const {
   h.mix(tunnel_endpoint_); // ip_prefix_t
   h.mix(nhg_name_); // std::string
   h.mix(igp_pref_); // uint8_t
   h.mix(igp_metric_); // uint32_t
}

std::string
nexthop_group_tunnel_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "nexthop_group_tunnel_t(";
   ss << "tunnel_endpoint=" << tunnel_endpoint_;
   ss << ", nhg_name='" << nhg_name_ << "'";
   ss << ", igp_pref=" << igp_pref_;
   ss << ", igp_metric=" << igp_metric_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const nexthop_group_tunnel_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/nexthop_group_tunnel.h>

#endif // EOS_INLINE_TYPES_NEXTHOP_GROUP_TUNNEL_IMPL_H
