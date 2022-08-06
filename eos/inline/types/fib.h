// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_FIB_H
#define EOS_INLINE_TYPES_FIB_H

namespace eos {

// Default constructor.
fib_route_key_t::fib_route_key_t() {
   pimpl = std::shared_ptr<fib_route_key_impl_t>(
      new fib_route_key_impl_t()
   );
}
fib_route_key_t::fib_route_key_t(ip_prefix_t const & prefix) {
   pimpl = std::shared_ptr<fib_route_key_impl_t>(
      new fib_route_key_impl_t(
         prefix
      )
   );
}
fib_route_key_t::fib_route_key_t(
   const fib_route_key_t& other)
{
   pimpl = std::make_unique<fib_route_key_impl_t>(
      fib_route_key_impl_t(*other.pimpl));
}
fib_route_key_t&
fib_route_key_t::operator=(
   fib_route_key_t const & other)
{
   pimpl = std::shared_ptr<fib_route_key_impl_t>(
      new fib_route_key_impl_t(*other.pimpl));
   return *this;
}

ip_prefix_t
fib_route_key_t::prefix() const {
   return pimpl->prefix();
}
void
fib_route_key_t::prefix_is(ip_prefix_t const & prefix) {
   pimpl->prefix_is(prefix);
}
bool
fib_route_key_t::operator==(fib_route_key_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
fib_route_key_t::operator!=(fib_route_key_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
fib_route_key_t::hash() const {
   return pimpl->hash();
}
void
fib_route_key_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
fib_route_key_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const fib_route_key_t& obj) {
   return operator<<(os, *obj.pimpl);
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const fib_route_type_t & enum_val) {
   if (enum_val==ROUTE_TYPE_INVALID) {
      os << "ROUTE_TYPE_INVALID";
   } else if (enum_val==ROUTE_TYPE_RECEIVE) {
      os << "ROUTE_TYPE_RECEIVE";
   } else if (enum_val==ROUTE_TYPE_RECEIVE_BCAST) {
      os << "ROUTE_TYPE_RECEIVE_BCAST";
   } else if (enum_val==ROUTE_TYPE_ATTACHED) {
      os << "ROUTE_TYPE_ATTACHED";
   } else if (enum_val==ROUTE_TYPE_UNKNOWN) {
      os << "ROUTE_TYPE_UNKNOWN";
   } else if (enum_val==ROUTE_TYPE_STATIC_CONFIG) {
      os << "ROUTE_TYPE_STATIC_CONFIG";
   } else if (enum_val==ROUTE_TYPE_KERNEL) {
      os << "ROUTE_TYPE_KERNEL";
   } else if (enum_val==ROUTE_TYPE_RIP) {
      os << "ROUTE_TYPE_RIP";
   } else if (enum_val==ROUTE_TYPE_CONNECTED) {
      os << "ROUTE_TYPE_CONNECTED";
   } else if (enum_val==ROUTE_TYPE_REDIRECT) {
      os << "ROUTE_TYPE_REDIRECT";
   } else if (enum_val==ROUTE_TYPE_BGP_AGGREGATE) {
      os << "ROUTE_TYPE_BGP_AGGREGATE";
   } else if (enum_val==ROUTE_TYPE_OSPF_AGGREGATE) {
      os << "ROUTE_TYPE_OSPF_AGGREGATE";
   } else if (enum_val==ROUTE_TYPE_OSPF_INTRA_AREA) {
      os << "ROUTE_TYPE_OSPF_INTRA_AREA";
   } else if (enum_val==ROUTE_TYPE_OSPF_INTER_AREA) {
      os << "ROUTE_TYPE_OSPF_INTER_AREA";
   } else if (enum_val==ROUTE_TYPE_OSPF_EXTERNAL_TYPE1) {
      os << "ROUTE_TYPE_OSPF_EXTERNAL_TYPE1";
   } else if (enum_val==ROUTE_TYPE_OSPF_EXTERNAL_TYPE2) {
      os << "ROUTE_TYPE_OSPF_EXTERNAL_TYPE2";
   } else if (enum_val==ROUTE_TYPE_OSPF_NSSA_EXTERNAL_TYPE1) {
      os << "ROUTE_TYPE_OSPF_NSSA_EXTERNAL_TYPE1";
   } else if (enum_val==ROUTE_TYPE_OSPF_NSSA_EXTERNAL_TYPE2) {
      os << "ROUTE_TYPE_OSPF_NSSA_EXTERNAL_TYPE2";
   } else if (enum_val==ROUTE_TYPE_BGP) {
      os << "ROUTE_TYPE_BGP";
   } else if (enum_val==ROUTE_TYPE_IBGP) {
      os << "ROUTE_TYPE_IBGP";
   } else if (enum_val==ROUTE_TYPE_EBGP) {
      os << "ROUTE_TYPE_EBGP";
   } else if (enum_val==ROUTE_TYPE_LBGP) {
      os << "ROUTE_TYPE_LBGP";
   } else if (enum_val==ROUTE_TYPE_ISIS) {
      os << "ROUTE_TYPE_ISIS";
   } else if (enum_val==ROUTE_TYPE_ISIS_LEVEL1) {
      os << "ROUTE_TYPE_ISIS_LEVEL1";
   } else if (enum_val==ROUTE_TYPE_ISIS_LEVEL2) {
      os << "ROUTE_TYPE_ISIS_LEVEL2";
   } else if (enum_val==ROUTE_TYPE_NEXTHOP_GROUP) {
      os << "ROUTE_TYPE_NEXTHOP_GROUP";
   } else if (enum_val==ROUTE_TYPE_OSPF3) {
      os << "ROUTE_TYPE_OSPF3";
   } else {
      os << "Unknown value";
   }
   return os;
}


// Default constructor.
fib_route_t::fib_route_t() {
   pimpl = std::shared_ptr<fib_route_impl_t>(
      new fib_route_impl_t()
   );
}
fib_route_t::fib_route_t(fib_route_key_t const & route_key) {
   pimpl = std::shared_ptr<fib_route_impl_t>(
      new fib_route_impl_t(
         route_key
      )
   );
}
fib_route_t::fib_route_t(
   const fib_route_t& other)
{
   pimpl = std::make_unique<fib_route_impl_t>(
      fib_route_impl_t(*other.pimpl));
}
fib_route_t&
fib_route_t::operator=(
   fib_route_t const & other)
{
   pimpl = std::shared_ptr<fib_route_impl_t>(
      new fib_route_impl_t(*other.pimpl));
   return *this;
}

fib_route_key_t
fib_route_t::route_key() const {
   return pimpl->route_key();
}
void
fib_route_t::route_key_is(fib_route_key_t const & route_key) {
   pimpl->route_key_is(route_key);
}
ip_route_preference_t
fib_route_t::preference() const {
   return pimpl->preference();
}
void
fib_route_t::preference_is(ip_route_preference_t preference) {
   pimpl->preference_is(preference);
}
ip_route_metric_t
fib_route_t::metric() const {
   return pimpl->metric();
}
void
fib_route_t::metric_is(ip_route_metric_t metric) {
   pimpl->metric_is(metric);
}
fib_route_type_t
fib_route_t::route_type() const {
   return pimpl->route_type();
}
void
fib_route_t::route_type_is(fib_route_type_t route_type) {
   pimpl->route_type_is(route_type);
}
uint64_t
fib_route_t::fec_id() const {
   return pimpl->fec_id();
}
void
fib_route_t::fec_id_is(uint64_t fec_id) {
   pimpl->fec_id_is(fec_id);
}
bool
fib_route_t::operator==(fib_route_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
fib_route_t::operator!=(fib_route_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
fib_route_t::hash() const {
   return pimpl->hash();
}
void
fib_route_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
fib_route_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const fib_route_t& obj) {
   return operator<<(os, *obj.pimpl);
}


// Default constructor.
fib_fec_key_t::fib_fec_key_t() {
   pimpl = std::shared_ptr<fib_fec_key_impl_t>(
      new fib_fec_key_impl_t()
   );
}
fib_fec_key_t::fib_fec_key_t(uint64_t fec_id) {
   pimpl = std::shared_ptr<fib_fec_key_impl_t>(
      new fib_fec_key_impl_t(
         fec_id
      )
   );
}
fib_fec_key_t::fib_fec_key_t(
   const fib_fec_key_t& other)
{
   pimpl = std::make_unique<fib_fec_key_impl_t>(
      fib_fec_key_impl_t(*other.pimpl));
}
fib_fec_key_t&
fib_fec_key_t::operator=(
   fib_fec_key_t const & other)
{
   pimpl = std::shared_ptr<fib_fec_key_impl_t>(
      new fib_fec_key_impl_t(*other.pimpl));
   return *this;
}

uint64_t
fib_fec_key_t::fec_id() const {
   return pimpl->fec_id();
}
void
fib_fec_key_t::fec_id_is(uint64_t fec_id) {
   pimpl->fec_id_is(fec_id);
}
bool
fib_fec_key_t::operator==(fib_fec_key_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
fib_fec_key_t::operator!=(fib_fec_key_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
fib_fec_key_t::hash() const {
   return pimpl->hash();
}
void
fib_fec_key_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
fib_fec_key_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const fib_fec_key_t& obj) {
   return operator<<(os, *obj.pimpl);
}


// Default constructor.
fib_via_t::fib_via_t() {
   pimpl = std::shared_ptr<fib_via_impl_t>(
      new fib_via_impl_t()
   );
}
fib_via_t::fib_via_t(ip_addr_t const & hop, intf_id_t intf) {
   pimpl = std::shared_ptr<fib_via_impl_t>(
      new fib_via_impl_t(
         hop,
         intf
      )
   );
}
fib_via_t::fib_via_t(
   const fib_via_t& other)
{
   pimpl = std::make_unique<fib_via_impl_t>(
      fib_via_impl_t(*other.pimpl));
}
fib_via_t&
fib_via_t::operator=(
   fib_via_t const & other)
{
   pimpl = std::shared_ptr<fib_via_impl_t>(
      new fib_via_impl_t(*other.pimpl));
   return *this;
}

ip_addr_t
fib_via_t::hop() const {
   return pimpl->hop();
}
void
fib_via_t::hop_is(ip_addr_t const & hop) {
   pimpl->hop_is(hop);
}
intf_id_t
fib_via_t::intf() const {
   return pimpl->intf();
}
void
fib_via_t::intf_is(intf_id_t intf) {
   pimpl->intf_is(intf);
}
mpls_label_t
fib_via_t::mpls_label() const {
   return pimpl->mpls_label();
}
void
fib_via_t::mpls_label_is(mpls_label_t mpls_label) {
   pimpl->mpls_label_is(mpls_label);
}
bool
fib_via_t::operator==(fib_via_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
fib_via_t::operator!=(fib_via_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
fib_via_t::hash() const {
   return pimpl->hash();
}
void
fib_via_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
fib_via_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const fib_via_t& obj) {
   return operator<<(os, *obj.pimpl);
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const fib_fec_type_t & enum_val) {
   if (enum_val==FEC_TYPE_FORWARD) {
      os << "FEC_TYPE_FORWARD";
   } else if (enum_val==FEC_TYPE_DROP) {
      os << "FEC_TYPE_DROP";
   } else if (enum_val==FEC_TYPE_RECEIVE) {
      os << "FEC_TYPE_RECEIVE";
   } else if (enum_val==FEC_TYPE_ATTACHED) {
      os << "FEC_TYPE_ATTACHED";
   } else if (enum_val==FEC_TYPE_RECEIVE_BCAST) {
      os << "FEC_TYPE_RECEIVE_BCAST";
   } else if (enum_val==FEC_TYPE_NEXTHOP_GROUP) {
      os << "FEC_TYPE_NEXTHOP_GROUP";
   } else if (enum_val==FEC_TYPE_KERNEL) {
      os << "FEC_TYPE_KERNEL";
   } else if (enum_val==FEC_TYPE_UNKNOWN) {
      os << "FEC_TYPE_UNKNOWN";
   } else {
      os << "Unknown value";
   }
   return os;
}


// Default constructor.
fib_fec_t::fib_fec_t() {
   pimpl = std::shared_ptr<fib_fec_impl_t>(
      new fib_fec_impl_t()
   );
}
fib_fec_t::fib_fec_t(fib_fec_key_t fec_key) {
   pimpl = std::shared_ptr<fib_fec_impl_t>(
      new fib_fec_impl_t(
         fec_key
      )
   );
}
fib_fec_t::fib_fec_t(
   const fib_fec_t& other)
{
   pimpl = std::make_unique<fib_fec_impl_t>(
      fib_fec_impl_t(*other.pimpl));
}
fib_fec_t&
fib_fec_t::operator=(
   fib_fec_t const & other)
{
   pimpl = std::shared_ptr<fib_fec_impl_t>(
      new fib_fec_impl_t(*other.pimpl));
   return *this;
}

fib_fec_key_t
fib_fec_t::fec_key() const {
   return pimpl->fec_key();
}
void
fib_fec_t::fec_key_is(fib_fec_key_t fec_key) {
   pimpl->fec_key_is(fec_key);
}
fib_fec_type_t
fib_fec_t::fec_type() const {
   return pimpl->fec_type();
}
void
fib_fec_t::fec_type_is(fib_fec_type_t fec_type) {
   pimpl->fec_type_is(fec_type);
}
std::string
fib_fec_t::nexthop_group_name() const {
   return pimpl->nexthop_group_name();
}
void
fib_fec_t::nexthop_group_name_is(std::string nexthop_group_name) {
   pimpl->nexthop_group_name_is(nexthop_group_name);
}
std::forward_list<fib_via_t> const &
fib_fec_t::via() const {
   return pimpl->via();
}
void
fib_fec_t::via_is(std::forward_list<fib_via_t> const & via) {
   pimpl->via_is(via);
}
void
fib_fec_t::via_set(fib_via_t const & via) {
   pimpl->via_set(via);
}
void
fib_fec_t::via_del(fib_via_t const & via) {
   pimpl->via_del(via);
}
uint32_t
fib_fec_t::hash() const {
   return pimpl->hash();
}
void
fib_fec_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
fib_fec_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const fib_fec_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_FIB_H
