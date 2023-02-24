// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_IP_ROUTE_H
#define EOS_INLINE_TYPES_IP_ROUTE_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const ip_route_action_t & enum_val) {
   if (enum_val==IP_ROUTE_ACTION_NULL) {
      os << "IP_ROUTE_ACTION_NULL";
   } else if (enum_val==IP_ROUTE_ACTION_FORWARD) {
      os << "IP_ROUTE_ACTION_FORWARD";
   } else if (enum_val==IP_ROUTE_ACTION_DROP) {
      os << "IP_ROUTE_ACTION_DROP";
   } else if (enum_val==IP_ROUTE_ACTION_NEXTHOP_GROUP) {
      os << "IP_ROUTE_ACTION_NEXTHOP_GROUP";
   } else {
      os << "Unknown value";
   }
   return os;
}


ip_route_key_t::ip_route_key_t() {
   pimpl = std::shared_ptr<ip_route_key_impl_t>(
      new ip_route_key_impl_t()
   );
}
ip_route_key_t::ip_route_key_t(ip_prefix_t const & prefix) {
   pimpl = std::shared_ptr<ip_route_key_impl_t>(
      new ip_route_key_impl_t(
         prefix
      )
   );
}
ip_route_key_t::ip_route_key_t(ip_prefix_t const & prefix,
                                      ip_route_preference_t preference) {
   pimpl = std::shared_ptr<ip_route_key_impl_t>(
      new ip_route_key_impl_t(
         prefix,
         preference
      )
   );
}
ip_route_key_t::ip_route_key_t(
   const ip_route_key_t& other)
{
   pimpl = std::make_unique<ip_route_key_impl_t>(
      ip_route_key_impl_t(*other.pimpl));
}
ip_route_key_t&
ip_route_key_t::operator=(
   ip_route_key_t const & other)
{
   pimpl = std::shared_ptr<ip_route_key_impl_t>(
      new ip_route_key_impl_t(*other.pimpl));
   return *this;
}

ip_prefix_t
ip_route_key_t::prefix() const {
   return pimpl->prefix();
}
void
ip_route_key_t::prefix_is(ip_prefix_t const & prefix) {
   pimpl->prefix_is(prefix);
}
ip_route_preference_t
ip_route_key_t::preference() const {
   return pimpl->preference();
}
void
ip_route_key_t::preference_is(ip_route_preference_t preference) {
   pimpl->preference_is(preference);
}
bool
ip_route_key_t::operator==(ip_route_key_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
ip_route_key_t::operator!=(ip_route_key_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
ip_route_key_t::hash() const {
   return pimpl->hash();
}
void
ip_route_key_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
ip_route_key_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const ip_route_key_t& obj) {
   return operator<<(os, *obj.pimpl);
}


ip_route_t::ip_route_t() {
   pimpl = std::shared_ptr<ip_route_impl_t>(
      new ip_route_impl_t()
   );
}
ip_route_t::ip_route_t(ip_route_key_t const & key) {
   pimpl = std::shared_ptr<ip_route_impl_t>(
      new ip_route_impl_t(
         key
      )
   );
}
ip_route_t::ip_route_t(
   const ip_route_t& other)
{
   pimpl = std::make_unique<ip_route_impl_t>(
      ip_route_impl_t(*other.pimpl));
}
ip_route_t&
ip_route_t::operator=(
   ip_route_t const & other)
{
   pimpl = std::shared_ptr<ip_route_impl_t>(
      new ip_route_impl_t(*other.pimpl));
   return *this;
}

ip_route_key_t
ip_route_t::key() const {
   return pimpl->key();
}
void
ip_route_t::key_is(ip_route_key_t const & key) {
   pimpl->key_is(key);
}
ip_route_tag_t
ip_route_t::tag() const {
   return pimpl->tag();
}
void
ip_route_t::tag_is(ip_route_tag_t tag) {
   pimpl->tag_is(tag);
}
bool
ip_route_t::rib_bypass() const {
   return pimpl->rib_bypass();
}
void
ip_route_t::rib_bypass_is(bool rib_bypass) {
   pimpl->rib_bypass_is(rib_bypass);
}
bool
ip_route_t::operator==(ip_route_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
ip_route_t::operator!=(ip_route_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
ip_route_t::hash() const {
   return pimpl->hash();
}
void
ip_route_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
ip_route_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const ip_route_t& obj) {
   return operator<<(os, *obj.pimpl);
}


ip_route_via_t::ip_route_via_t() {
   pimpl = std::shared_ptr<ip_route_via_impl_t>(
      new ip_route_via_impl_t()
   );
}
ip_route_via_t::ip_route_via_t(ip_route_key_t const & route_key) {
   pimpl = std::shared_ptr<ip_route_via_impl_t>(
      new ip_route_via_impl_t(
         route_key
      )
   );
}
ip_route_via_t::ip_route_via_t(
   const ip_route_via_t& other)
{
   pimpl = std::make_unique<ip_route_via_impl_t>(
      ip_route_via_impl_t(*other.pimpl));
}
ip_route_via_t&
ip_route_via_t::operator=(
   ip_route_via_t const & other)
{
   pimpl = std::shared_ptr<ip_route_via_impl_t>(
      new ip_route_via_impl_t(*other.pimpl));
   return *this;
}

ip_route_key_t
ip_route_via_t::route_key() const {
   return pimpl->route_key();
}
void
ip_route_via_t::route_key_is(ip_route_key_t const & route_key) {
   pimpl->route_key_is(route_key);
}
ip_addr_t
ip_route_via_t::hop() const {
   return pimpl->hop();
}
void
ip_route_via_t::hop_is(ip_addr_t const & hop) {
   pimpl->hop_is(hop);
}
intf_id_t
ip_route_via_t::intf() const {
   return pimpl->intf();
}
void
ip_route_via_t::intf_is(intf_id_t intf) {
   pimpl->intf_is(intf);
}
std::string
ip_route_via_t::nexthop_group() const {
   return pimpl->nexthop_group();
}
void
ip_route_via_t::nexthop_group_is(std::string const & nexthop_group) {
   pimpl->nexthop_group_is(nexthop_group);
}
mpls_label_t
ip_route_via_t::mpls_label() const {
   return pimpl->mpls_label();
}
void
ip_route_via_t::mpls_label_is(mpls_label_t mpls_label) {
   pimpl->mpls_label_is(mpls_label);
}
vni_t
ip_route_via_t::vni() const {
   return pimpl->vni();
}
void
ip_route_via_t::vni_is(vni_t vni) {
   pimpl->vni_is(vni);
}
ip_addr_t
ip_route_via_t::vtep_addr() const {
   return pimpl->vtep_addr();
}
void
ip_route_via_t::vtep_addr_is(ip_addr_t vtep_addr) {
   pimpl->vtep_addr_is(vtep_addr);
}
eth_addr_t
ip_route_via_t::router_mac() const {
   return pimpl->router_mac();
}
void
ip_route_via_t::router_mac_is(eth_addr_t router_mac) {
   pimpl->router_mac_is(router_mac);
}
std::string
ip_route_via_t::egress_vrf() const {
   return pimpl->egress_vrf();
}
void
ip_route_via_t::egress_vrf_is(std::string const & egress_vrf) {
   pimpl->egress_vrf_is(egress_vrf);
}
ip_via_metric_t
ip_route_via_t::metric() const {
   return pimpl->metric();
}
void
ip_route_via_t::metric_is(ip_via_metric_t metric) {
   pimpl->metric_is(metric);
}
intf_id_t
ip_route_via_t::vxlan_intf() const {
   return pimpl->vxlan_intf();
}
void
ip_route_via_t::vxlan_intf_is(intf_id_t vxlan_intf) {
   pimpl->vxlan_intf_is(vxlan_intf);
}
bool
ip_route_via_t::vtep_sip_validation() const {
   return pimpl->vtep_sip_validation();
}
void
ip_route_via_t::vtep_sip_validation_is(bool vtep_sip_validation) {
   pimpl->vtep_sip_validation_is(vtep_sip_validation);
}
bool
ip_route_via_t::operator==(ip_route_via_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
ip_route_via_t::operator!=(ip_route_via_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
ip_route_via_t::hash() const {
   return pimpl->hash();
}
void
ip_route_via_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
ip_route_via_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const ip_route_via_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_IP_ROUTE_H
