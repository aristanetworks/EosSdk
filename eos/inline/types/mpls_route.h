// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MPLS_ROUTE_H
#define EOS_INLINE_TYPES_MPLS_ROUTE_H

namespace eos {

std::vector<mpls_label_t> const &
mpls_route_key_t::labels() const {
   return pimpl->labels();
}
void
mpls_route_key_t::labels_is(std::vector<mpls_label_t> const & labels) {
   pimpl->labels_is(labels);
}
void
mpls_route_key_t::labels_is(std::vector<mpls_label_t> && labels) {
   pimpl->labels_is(std::move(labels));
}
void
mpls_route_key_t::label_set(uint32_t index, mpls_label_t const & value) {
   pimpl->label_set(index, value);
}
void
mpls_route_key_t::label_set(uint32_t index, mpls_label_t && value) {
   pimpl->label_set(index, std::move(value));
}
void
mpls_route_key_t::label_del(uint32_t index) {
   pimpl->label_del(index);
}
mpls_route_metric_t
mpls_route_key_t::metric() const {
   return pimpl->metric();
}
void
mpls_route_key_t::metric_is(mpls_route_metric_t metric) {
   pimpl->metric_is(metric);
}
mpls_label_t
mpls_route_key_t::top_label() const {
   return pimpl->top_label();
}
void
mpls_route_key_t::top_label_is(mpls_label_t top_label) {
   pimpl->top_label_is(top_label);
}
bool
mpls_route_key_t::operator==(mpls_route_key_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
mpls_route_key_t::operator!=(mpls_route_key_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
mpls_route_key_t::operator<(mpls_route_key_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
mpls_route_key_t::hash() const {
   return pimpl->hash();
}
void
mpls_route_key_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
mpls_route_key_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const mpls_route_key_t& obj) {
   return operator<<(os, *obj.pimpl);
}


mpls_route_key_t
mpls_route_t::key() const {
   return pimpl->key();
}
void
mpls_route_t::key_is(mpls_route_key_t key) {
   pimpl->key_is(key);
}
uint32_t
mpls_route_t::version_id() const {
   return pimpl->version_id();
}
void
mpls_route_t::version_id_is(uint32_t version_id) {
   pimpl->version_id_is(version_id);
}
bool
mpls_route_t::operator==(mpls_route_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
mpls_route_t::operator!=(mpls_route_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
mpls_route_t::hash() const {
   return pimpl->hash();
}
void
mpls_route_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
mpls_route_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const mpls_route_t& obj) {
   return operator<<(os, *obj.pimpl);
}


mpls_route_key_t
mpls_route_via_t::route_key() const {
   return pimpl->route_key();
}
void
mpls_route_via_t::route_key_is(mpls_route_key_t route_key) {
   pimpl->route_key_is(route_key);
}
ip_addr_t
mpls_route_via_t::hop() const {
   return pimpl->hop();
}
void
mpls_route_via_t::hop_is(ip_addr_t const & hop) {
   pimpl->hop_is(hop);
}
void
mpls_route_via_t::hop_is(ip_addr_t && hop) {
   pimpl->hop_is(std::move(hop));
}
intf_id_t
mpls_route_via_t::intf() const {
   return pimpl->intf();
}
void
mpls_route_via_t::intf_is(intf_id_t const & intf) {
   pimpl->intf_is(intf);
}
void
mpls_route_via_t::intf_is(intf_id_t && intf) {
   pimpl->intf_is(std::move(intf));
}
mpls_label_t
mpls_route_via_t::pushswap_label() const {
   return pimpl->pushswap_label();
}
void
mpls_route_via_t::pushswap_label_is(mpls_label_t top_label) {
   pimpl->pushswap_label_is(top_label);
}
mpls_action_t
mpls_route_via_t::label_action() const {
   return pimpl->label_action();
}
void
mpls_route_via_t::label_action_is(mpls_action_t label_action) {
   pimpl->label_action_is(label_action);
}
mpls_ttl_mode_t
mpls_route_via_t::ttl_mode() const {
   return pimpl->ttl_mode();
}
void
mpls_route_via_t::ttl_mode_is(mpls_ttl_mode_t ttl_mode) {
   pimpl->ttl_mode_is(ttl_mode);
}
mpls_payload_type_t
mpls_route_via_t::payload_type() const {
   return pimpl->payload_type();
}
void
mpls_route_via_t::payload_type_is(mpls_payload_type_t payload_type) {
   pimpl->payload_type_is(payload_type);
}
bool
mpls_route_via_t::skip_egress_acl() const {
   return pimpl->skip_egress_acl();
}
void
mpls_route_via_t::skip_egress_acl_is(bool skip_egress_acl) {
   pimpl->skip_egress_acl_is(skip_egress_acl);
}
std::string
mpls_route_via_t::nexthop_group() const {
   return pimpl->nexthop_group();
}
void
mpls_route_via_t::nexthop_group_is(std::string nexthop_group) {
   pimpl->nexthop_group_is(nexthop_group);
}
uint32_t
mpls_route_via_t::weight() const {
   return pimpl->weight();
}
void
mpls_route_via_t::weight_is(uint32_t weight) {
   pimpl->weight_is(weight);
}
std::forward_list<mpls_label_t> const &
mpls_route_via_t::pushswap_label_stack() const {
   return pimpl->pushswap_label_stack();
}
void
mpls_route_via_t::pushswap_label_stack_is(
         std::forward_list<mpls_label_t> const & pushswap_label_stack) {
   pimpl->pushswap_label_stack_is(pushswap_label_stack);
}
void
mpls_route_via_t::pushswap_label_stack_is(
         std::forward_list<mpls_label_t> && pushswap_label_stack) {
   pimpl->pushswap_label_stack_is(std::move(pushswap_label_stack));
}
void
mpls_route_via_t::pushswap_label_stack_set(
         mpls_label_t const & pushswap_label_stack) {
   pimpl->pushswap_label_stack_set(pushswap_label_stack);
}
void
mpls_route_via_t::pushswap_label_stack_set(mpls_label_t && pushswap_label_stack) {
   pimpl->pushswap_label_stack_set(std::move(pushswap_label_stack));
}
void
mpls_route_via_t::pushswap_label_stack_del(
         mpls_label_t const & pushswap_label_stack) {
   pimpl->pushswap_label_stack_del(pushswap_label_stack);
}
bool
mpls_route_via_t::operator==(mpls_route_via_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
mpls_route_via_t::operator!=(mpls_route_via_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
mpls_route_via_t::hash() const {
   return pimpl->hash();
}
void
mpls_route_via_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
mpls_route_via_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const mpls_route_via_t& obj) {
   return operator<<(os, *obj.pimpl);
}


uint64_t
mpls_fec_id_t::id() const {
   return pimpl->id();
}
void
mpls_fec_id_t::id_is(uint64_t id) {
   pimpl->id_is(id);
}
bool
mpls_fec_id_t::operator==(mpls_fec_id_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
mpls_fec_id_t::operator!=(mpls_fec_id_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
mpls_fec_id_t::operator<(mpls_fec_id_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
mpls_fec_id_t::hash() const {
   return pimpl->hash();
}
void
mpls_fec_id_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
mpls_fec_id_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const mpls_fec_id_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_MPLS_ROUTE_H
