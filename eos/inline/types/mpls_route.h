// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MPLS_ROUTE_H
#define EOS_INLINE_TYPES_MPLS_ROUTE_H

namespace eos {

mpls_route_key_t::mpls_route_key_t() {
   pimpl = std::shared_ptr<mpls_route_key_impl_t>(
      new mpls_route_key_impl_t()
   );
}
mpls_route_key_t::mpls_route_key_t(mpls_label_t top_label,
                                          mpls_route_metric_t metric) {
   pimpl = std::shared_ptr<mpls_route_key_impl_t>(
      new mpls_route_key_impl_t(
         top_label,
         metric
      )
   );
}
mpls_route_key_t::mpls_route_key_t(std::vector<mpls_label_t> const & labels,
                                          mpls_route_metric_t metric) {
   pimpl = std::shared_ptr<mpls_route_key_impl_t>(
      new mpls_route_key_impl_t(
         labels,
         metric
      )
   );
}
mpls_route_key_t::mpls_route_key_t(
   const mpls_route_key_t& other)
{
   pimpl = std::make_unique<mpls_route_key_impl_t>(
      mpls_route_key_impl_t(*other.pimpl));
}
mpls_route_key_t&
mpls_route_key_t::operator=(
   mpls_route_key_t const & other)
{
   pimpl = std::shared_ptr<mpls_route_key_impl_t>(
      new mpls_route_key_impl_t(*other.pimpl));
   return *this;
}

std::vector<mpls_label_t> const &
mpls_route_key_t::labels() const {
   return pimpl->labels();
}
void
mpls_route_key_t::labels_is(std::vector<mpls_label_t> const & labels) {
   pimpl->labels_is(labels);
}
void
mpls_route_key_t::label_set(uint32_t index, mpls_label_t const & value) {
   pimpl->label_set(index, value);
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


mpls_route_t::mpls_route_t() {
   pimpl = std::shared_ptr<mpls_route_impl_t>(
      new mpls_route_impl_t()
   );
}
mpls_route_t::mpls_route_t(mpls_route_key_t key) {
   pimpl = std::shared_ptr<mpls_route_impl_t>(
      new mpls_route_impl_t(
         key
      )
   );
}
mpls_route_t::mpls_route_t(
   const mpls_route_t& other)
{
   pimpl = std::make_unique<mpls_route_impl_t>(
      mpls_route_impl_t(*other.pimpl));
}
mpls_route_t&
mpls_route_t::operator=(
   mpls_route_t const & other)
{
   pimpl = std::shared_ptr<mpls_route_impl_t>(
      new mpls_route_impl_t(*other.pimpl));
   return *this;
}

mpls_route_key_t
mpls_route_t::key() const {
   return pimpl->key();
}
void
mpls_route_t::key_is(mpls_route_key_t key) {
   pimpl->key_is(key);
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


mpls_route_via_t::mpls_route_via_t() {
   pimpl = std::shared_ptr<mpls_route_via_impl_t>(
      new mpls_route_via_impl_t()
   );
}
mpls_route_via_t::mpls_route_via_t(mpls_route_key_t route_key) {
   pimpl = std::shared_ptr<mpls_route_via_impl_t>(
      new mpls_route_via_impl_t(
         route_key
      )
   );
}
mpls_route_via_t::mpls_route_via_t(mpls_route_key_t route_key,
                                          mpls_action_t label_action) {
   pimpl = std::shared_ptr<mpls_route_via_impl_t>(
      new mpls_route_via_impl_t(
         route_key,
         label_action
      )
   );
}
mpls_route_via_t::mpls_route_via_t(
   const mpls_route_via_t& other)
{
   pimpl = std::make_unique<mpls_route_via_impl_t>(
      mpls_route_via_impl_t(*other.pimpl));
}
mpls_route_via_t&
mpls_route_via_t::operator=(
   mpls_route_via_t const & other)
{
   pimpl = std::shared_ptr<mpls_route_via_impl_t>(
      new mpls_route_via_impl_t(*other.pimpl));
   return *this;
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
intf_id_t
mpls_route_via_t::intf() const {
   return pimpl->intf();
}
void
mpls_route_via_t::intf_is(intf_id_t const & intf) {
   pimpl->intf_is(intf);
}
mpls_label_t
mpls_route_via_t::pushswap_label() const {
   return pimpl->pushswap_label();
}
void
mpls_route_via_t::pushswap_label_is(mpls_label_t pushswap_label) {
   pimpl->pushswap_label_is(pushswap_label);
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


mpls_fec_id_t::mpls_fec_id_t() {
   pimpl = std::shared_ptr<mpls_fec_id_impl_t>(
      new mpls_fec_id_impl_t()
   );
}
mpls_fec_id_t::mpls_fec_id_t(uint64_t id) {
   pimpl = std::shared_ptr<mpls_fec_id_impl_t>(
      new mpls_fec_id_impl_t(
         id
      )
   );
}
mpls_fec_id_t::mpls_fec_id_t(
   const mpls_fec_id_t& other)
{
   pimpl = std::make_unique<mpls_fec_id_impl_t>(
      mpls_fec_id_impl_t(*other.pimpl));
}
mpls_fec_id_t&
mpls_fec_id_t::operator=(
   mpls_fec_id_t const & other)
{
   pimpl = std::shared_ptr<mpls_fec_id_impl_t>(
      new mpls_fec_id_impl_t(*other.pimpl));
   return *this;
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
