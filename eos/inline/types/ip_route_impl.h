// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_IP_ROUTE_IMPL_H
#define EOS_INLINE_TYPES_IP_ROUTE_IMPL_H

namespace eos {



ip_route_key_impl_t::ip_route_key_impl_t() :
      prefix_(), preference_(1) {
}

ip_route_key_impl_t::ip_route_key_impl_t(ip_prefix_t const & prefix) :
      prefix_(prefix), preference_(1) {
}

ip_route_key_impl_t::ip_route_key_impl_t(ip_prefix_t const & prefix,
                                                ip_route_preference_t preference) :
      prefix_(prefix), preference_(preference) {
}

ip_prefix_t
ip_route_key_impl_t::prefix() const {
   return prefix_;
}

void
ip_route_key_impl_t::prefix_is(ip_prefix_t const & prefix) {
   prefix_ = prefix;
}

void
ip_route_key_impl_t::prefix_is(ip_prefix_t && prefix) {
   prefix_ = std::move(prefix);
}

ip_route_preference_t
ip_route_key_impl_t::preference() const {
   return preference_;
}

void
ip_route_key_impl_t::preference_is(ip_route_preference_t preference) {
   preference_ = preference;
}

af_t
ip_route_key_impl_t::af() const {
   return prefix_.af();
}

bool
ip_route_key_impl_t::operator==(ip_route_key_impl_t const & other) const {
   return prefix_ == other.prefix_ &&
          preference_ == other.preference_;
}

bool
ip_route_key_impl_t::operator!=(ip_route_key_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
ip_route_key_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
ip_route_key_impl_t::mix_me(hash_mix & h) const {
   h.mix(prefix_); // ip_prefix_t
   h.mix(preference_); // ip_route_preference_t
}

std::string
ip_route_key_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "ip_route_key_t(";
   ss << "prefix=" << prefix_;
   ss << ", preference=" << preference_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const ip_route_key_impl_t& obj) {
   os << obj.to_string();
   return os;
}



ip_route_impl_t::ip_route_impl_t() :
      key_(), tag_(0), rib_bypass_(), command_tag_() {
}

ip_route_impl_t::ip_route_impl_t(ip_route_key_t const & key) :
      key_(key), tag_(0), rib_bypass_(), command_tag_() {
}

ip_route_key_t
ip_route_impl_t::key() const {
   return key_;
}

void
ip_route_impl_t::key_is(ip_route_key_t const & key) {
   key_ = key;
}

void
ip_route_impl_t::key_is(ip_route_key_t && key) {
   key_ = std::move(key);
}

ip_route_tag_t
ip_route_impl_t::tag() const {
   return tag_;
}

void
ip_route_impl_t::tag_is(ip_route_tag_t tag) {
   tag_ = tag;
}

bool
ip_route_impl_t::rib_bypass() const {
   return rib_bypass_;
}

void
ip_route_impl_t::rib_bypass_is(bool rib_bypass) {
   rib_bypass_ = rib_bypass;
}

std::string
ip_route_impl_t::command_tag() const {
   return command_tag_;
}

void
ip_route_impl_t::command_tag_is(std::string const & command_tag) {
   command_tag_ = command_tag;
}

void
ip_route_impl_t::command_tag_is(std::string && command_tag) {
   command_tag_ = std::move(command_tag);
}

af_t
ip_route_impl_t::af() const {
   return key_.af();
}

bool
ip_route_impl_t::operator==(ip_route_impl_t const & other) const {
   return key_ == other.key_ &&
          tag_ == other.tag_ &&
          rib_bypass_ == other.rib_bypass_ &&
          command_tag_ == other.command_tag_;
}

bool
ip_route_impl_t::operator!=(ip_route_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
ip_route_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
ip_route_impl_t::mix_me(hash_mix & h) const {
   h.mix(key_); // ip_route_key_t
   h.mix(tag_); // ip_route_tag_t
   h.mix(rib_bypass_); // bool
   h.mix(command_tag_); // std::string
}

std::string
ip_route_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "ip_route_t(";
   ss << "key=" << key_;
   ss << ", tag=" << tag_;
   ss << ", rib_bypass=" << rib_bypass_;
   ss << ", command_tag='" << command_tag_ << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const ip_route_impl_t& obj) {
   os << obj.to_string();
   return os;
}



ip_route_via_impl_t::ip_route_via_impl_t() :
      route_key_(), hop_(), intf_(), nexthop_group_(), mpls_label_(), vni_(),
      vtep_addr_(), router_mac_(), egress_vrf_(), metric_(0), vxlan_intf_(),
      vtep_sip_validation_(), weight_() {
}

ip_route_via_impl_t::ip_route_via_impl_t(ip_route_key_t const & route_key) :
      route_key_(route_key), hop_(), intf_(), nexthop_group_(), mpls_label_(),
      vni_(), vtep_addr_(), router_mac_(), egress_vrf_(), metric_(0),
      vxlan_intf_(), vtep_sip_validation_(), weight_() {
}

ip_route_key_t
ip_route_via_impl_t::route_key() const {
   return route_key_;
}

void
ip_route_via_impl_t::route_key_is(ip_route_key_t const & route_key) {
   route_key_ = route_key;
}

void
ip_route_via_impl_t::route_key_is(ip_route_key_t && route_key) {
   route_key_ = std::move(route_key);
}

ip_addr_t
ip_route_via_impl_t::hop() const {
   return hop_;
}

void
ip_route_via_impl_t::hop_is(ip_addr_t const & hop) {
   hop_ = hop;
}

void
ip_route_via_impl_t::hop_is(ip_addr_t && hop) {
   hop_ = std::move(hop);
}

intf_id_t
ip_route_via_impl_t::intf() const {
   return intf_;
}

void
ip_route_via_impl_t::intf_is(intf_id_t intf) {
   intf_ = intf;
}

std::string
ip_route_via_impl_t::nexthop_group() const {
   return nexthop_group_;
}

void
ip_route_via_impl_t::nexthop_group_is(std::string const & nexthop_group) {
   nexthop_group_ = nexthop_group;
}

void
ip_route_via_impl_t::nexthop_group_is(std::string && nexthop_group) {
   nexthop_group_ = std::move(nexthop_group);
}

mpls_label_t
ip_route_via_impl_t::mpls_label() const {
   return mpls_label_;
}

void
ip_route_via_impl_t::mpls_label_is(mpls_label_t mpls_label) {
   mpls_label_ = mpls_label;
}

vni_t
ip_route_via_impl_t::vni() const {
   return vni_;
}

void
ip_route_via_impl_t::vni_is(vni_t vni) {
   vni_ = vni;
}

ip_addr_t
ip_route_via_impl_t::vtep_addr() const {
   return vtep_addr_;
}

void
ip_route_via_impl_t::vtep_addr_is(ip_addr_t vtep_addr) {
   vtep_addr_ = vtep_addr;
}

eth_addr_t
ip_route_via_impl_t::router_mac() const {
   return router_mac_;
}

void
ip_route_via_impl_t::router_mac_is(eth_addr_t router_mac) {
   router_mac_ = router_mac;
}

std::string
ip_route_via_impl_t::egress_vrf() const {
   return egress_vrf_;
}

void
ip_route_via_impl_t::egress_vrf_is(std::string const & egress_vrf) {
   egress_vrf_ = egress_vrf;
}

void
ip_route_via_impl_t::egress_vrf_is(std::string && egress_vrf) {
   egress_vrf_ = std::move(egress_vrf);
}

ip_via_metric_t
ip_route_via_impl_t::metric() const {
   return metric_;
}

void
ip_route_via_impl_t::metric_is(ip_via_metric_t metric) {
   metric_ = metric;
}

intf_id_t
ip_route_via_impl_t::vxlan_intf() const {
   return vxlan_intf_;
}

void
ip_route_via_impl_t::vxlan_intf_is(intf_id_t vxlan_intf) {
   vxlan_intf_ = vxlan_intf;
}

bool
ip_route_via_impl_t::vtep_sip_validation() const {
   return vtep_sip_validation_;
}

void
ip_route_via_impl_t::vtep_sip_validation_is(bool vtep_sip_validation) {
   vtep_sip_validation_ = vtep_sip_validation;
}

ip_via_weight_t
ip_route_via_impl_t::weight() const {
   return weight_;
}

void
ip_route_via_impl_t::weight_is(ip_via_weight_t weight) {
   weight_ = weight;
}

bool
ip_route_via_impl_t::operator==(ip_route_via_impl_t const & other) const {
   return route_key_ == other.route_key_ &&
          hop_ == other.hop_ &&
          intf_ == other.intf_ &&
          nexthop_group_ == other.nexthop_group_ &&
          mpls_label_ == other.mpls_label_ &&
          vni_ == other.vni_ &&
          vtep_addr_ == other.vtep_addr_ &&
          router_mac_ == other.router_mac_ &&
          egress_vrf_ == other.egress_vrf_ &&
          metric_ == other.metric_ &&
          vxlan_intf_ == other.vxlan_intf_ &&
          vtep_sip_validation_ == other.vtep_sip_validation_ &&
          weight_ == other.weight_;
}

bool
ip_route_via_impl_t::operator!=(ip_route_via_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
ip_route_via_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
ip_route_via_impl_t::mix_me(hash_mix & h) const {
   h.mix(route_key_); // ip_route_key_t
   h.mix(hop_); // ip_addr_t
   h.mix(intf_); // intf_id_t
   h.mix(nexthop_group_); // std::string
   h.mix(mpls_label_); // mpls_label_t
   h.mix(vni_); // vni_t
   h.mix(vtep_addr_); // ip_addr_t
   h.mix(router_mac_); // eth_addr_t
   h.mix(egress_vrf_); // std::string
   h.mix(metric_); // ip_via_metric_t
   h.mix(vxlan_intf_); // intf_id_t
   h.mix(vtep_sip_validation_); // bool
   h.mix(weight_); // ip_via_weight_t
}

std::string
ip_route_via_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "ip_route_via_t(";
   ss << "route_key=" << route_key_;
   ss << ", hop=" << hop_;
   ss << ", intf=" << intf_;
   ss << ", nexthop_group='" << nexthop_group_ << "'";
   ss << ", mpls_label=" << mpls_label_;
   ss << ", vni=" << vni_;
   ss << ", vtep_addr=" << vtep_addr_;
   ss << ", router_mac=" << router_mac_;
   ss << ", egress_vrf='" << egress_vrf_ << "'";
   ss << ", metric=" << metric_;
   ss << ", vxlan_intf=" << vxlan_intf_;
   ss << ", vtep_sip_validation=" << vtep_sip_validation_;
   ss << ", weight=" << weight_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const ip_route_via_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/ip_route.h>

#endif // EOS_INLINE_TYPES_IP_ROUTE_IMPL_H
