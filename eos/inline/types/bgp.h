// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_BGP_H
#define EOS_INLINE_TYPES_BGP_H

namespace eos {

bgp_peer_key_t::bgp_peer_key_t() {
   pimpl = std::shared_ptr<bgp_peer_key_impl_t>(
      new bgp_peer_key_impl_t()
   );
}
bgp_peer_key_t::bgp_peer_key_t(std::string const & vrf_name,
                                      ip_addr_t const & peer_addr) {
   pimpl = std::shared_ptr<bgp_peer_key_impl_t>(
      new bgp_peer_key_impl_t(
         vrf_name,
         peer_addr
      )
   );
}
bgp_peer_key_t::bgp_peer_key_t(
   const bgp_peer_key_t& other)
{
   pimpl = std::make_unique<bgp_peer_key_impl_t>(
      bgp_peer_key_impl_t(*other.pimpl));
}
bgp_peer_key_t&
bgp_peer_key_t::operator=(
   bgp_peer_key_t const & other)
{
   pimpl = std::shared_ptr<bgp_peer_key_impl_t>(
      new bgp_peer_key_impl_t(*other.pimpl));
   return *this;
}

std::string
bgp_peer_key_t::vrf_name() const {
   return pimpl->vrf_name();
}
void
bgp_peer_key_t::vrf_name_is(std::string const & vrf_name) {
   pimpl->vrf_name_is(vrf_name);
}
ip_addr_t
bgp_peer_key_t::peer_addr() const {
   return pimpl->peer_addr();
}
void
bgp_peer_key_t::peer_addr_is(ip_addr_t const & peer_addr) {
   pimpl->peer_addr_is(peer_addr);
}
bool
bgp_peer_key_t::operator==(bgp_peer_key_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
bgp_peer_key_t::operator!=(bgp_peer_key_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
bgp_peer_key_t::operator<(bgp_peer_key_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
bgp_peer_key_t::hash() const {
   return pimpl->hash();
}
void
bgp_peer_key_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
bgp_peer_key_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const bgp_peer_key_t& obj) {
   return operator<<(os, *obj.pimpl);
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const bgp_peer_state_t & enum_val) {
   if (enum_val==PEER_UNKNOWN) {
      os << "PEER_UNKNOWN";
   } else if (enum_val==PEER_IDLE) {
      os << "PEER_IDLE";
   } else if (enum_val==PEER_CONNECT) {
      os << "PEER_CONNECT";
   } else if (enum_val==PEER_ACTIVE) {
      os << "PEER_ACTIVE";
   } else if (enum_val==PEER_OPENSENT) {
      os << "PEER_OPENSENT";
   } else if (enum_val==PEER_OPENCONFIRM) {
      os << "PEER_OPENCONFIRM";
   } else if (enum_val==PEER_ESTABLISHED) {
      os << "PEER_ESTABLISHED";
   } else {
      os << "Unknown value";
   }
   return os;
}

}

#endif // EOS_INLINE_TYPES_BGP_H
