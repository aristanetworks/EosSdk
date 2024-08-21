// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_NEXTHOP_GROUP_TUNNEL_H
#define EOS_INLINE_TYPES_NEXTHOP_GROUP_TUNNEL_H

namespace eos {

ip_prefix_t
nexthop_group_tunnel_t::tunnel_endpoint() const {
   return pimpl->tunnel_endpoint();
}
void
nexthop_group_tunnel_t::tunnel_endpoint_is(ip_prefix_t const & tunnel_endpoint) {
   pimpl->tunnel_endpoint_is(tunnel_endpoint);
}
void
nexthop_group_tunnel_t::tunnel_endpoint_is(ip_prefix_t && tunnel_endpoint) {
   pimpl->tunnel_endpoint_is(std::move(tunnel_endpoint));
}
std::string
nexthop_group_tunnel_t::nhg_name() const {
   return pimpl->nhg_name();
}
void
nexthop_group_tunnel_t::nhg_name_is(std::string const & nhg_name) {
   pimpl->nhg_name_is(nhg_name);
}
void
nexthop_group_tunnel_t::nhg_name_is(std::string && nhg_name) {
   pimpl->nhg_name_is(std::move(nhg_name));
}
uint8_t
nexthop_group_tunnel_t::igp_pref() const {
   return pimpl->igp_pref();
}
void
nexthop_group_tunnel_t::igp_pref_is(uint8_t igp_pref) {
   pimpl->igp_pref_is(igp_pref);
}
uint32_t
nexthop_group_tunnel_t::igp_metric() const {
   return pimpl->igp_metric();
}
void
nexthop_group_tunnel_t::igp_metric_is(uint32_t igp_metric) {
   pimpl->igp_metric_is(igp_metric);
}
bool
nexthop_group_tunnel_t::operator==(nexthop_group_tunnel_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
nexthop_group_tunnel_t::operator!=(nexthop_group_tunnel_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
nexthop_group_tunnel_t::hash() const {
   return pimpl->hash();
}
void
nexthop_group_tunnel_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
nexthop_group_tunnel_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const nexthop_group_tunnel_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_NEXTHOP_GROUP_TUNNEL_H
