// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/bgp.h"
#include "eos/types/bgp_impl.h"

namespace eos {

bgp_peer_key_t::bgp_peer_key_t() :
   pimpl(std::make_shared<bgp_peer_key_impl_t>()) {}
bgp_peer_key_t::bgp_peer_key_t(std::string const & vrf_name,
                               ip_addr_t const & peer_addr) :
   pimpl(std::make_shared<bgp_peer_key_impl_t>(
      vrf_name,
      peer_addr
   )) {}
EOS_SDK_PUBLIC bgp_peer_key_t::bgp_peer_key_t(
   const bgp_peer_key_t& other) :
   pimpl(std::make_shared<bgp_peer_key_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC bgp_peer_key_t&
bgp_peer_key_t::operator=(
   bgp_peer_key_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<bgp_peer_key_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
bgp_peer_key_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
bgp_peer_key_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
