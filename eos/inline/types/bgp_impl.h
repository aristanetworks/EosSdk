// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_BGP_IMPL_H
#define EOS_INLINE_TYPES_BGP_IMPL_H

namespace eos {

bgp_peer_key_impl_t::bgp_peer_key_impl_t() :
      vrf_name_(), peer_addr_() {
}

bgp_peer_key_impl_t::bgp_peer_key_impl_t(std::string const & vrf_name,
                                                ip_addr_t const & peer_addr) :
      vrf_name_(vrf_name), peer_addr_(peer_addr) {
}

std::string
bgp_peer_key_impl_t::vrf_name() const {
   return vrf_name_;
}

void
bgp_peer_key_impl_t::vrf_name_is(std::string const & vrf_name) {
   vrf_name_ = vrf_name;
}

ip_addr_t
bgp_peer_key_impl_t::peer_addr() const {
   return peer_addr_;
}

void
bgp_peer_key_impl_t::peer_addr_is(ip_addr_t const & peer_addr) {
   peer_addr_ = peer_addr;
}

bool
bgp_peer_key_impl_t::operator==(bgp_peer_key_impl_t const & other) const {
   return vrf_name_ == other.vrf_name_ &&
          peer_addr_ == other.peer_addr_;
}

bool
bgp_peer_key_impl_t::operator!=(bgp_peer_key_impl_t const & other) const {
   return !operator==(other);
}

bool
bgp_peer_key_impl_t::operator<(bgp_peer_key_impl_t const & other) const {
   if(vrf_name_ != other.vrf_name_) {
      return vrf_name_ < other.vrf_name_;
   } else if(peer_addr_ != other.peer_addr_) {
      return peer_addr_ < other.peer_addr_;
   }
   return false;
}

uint32_t
bgp_peer_key_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
bgp_peer_key_impl_t::mix_me(hash_mix & h) const {
   h.mix(vrf_name_); // std::string
   h.mix(peer_addr_); // ip_addr_t
}

std::string
bgp_peer_key_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "bgp_peer_key_t(";
   ss << "vrf_name='" << vrf_name_ << "'";
   ss << ", peer_addr=" << peer_addr_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const bgp_peer_key_impl_t& obj) {
   os << obj.to_string();
   return os;
}




}

#include <eos/inline/types/bgp.h>

#endif // EOS_INLINE_TYPES_BGP_IMPL_H
