// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/nexthop_group_tunnel.h"
#include "eos/types/nexthop_group_tunnel_impl.h"

namespace eos {

nexthop_group_tunnel_t::nexthop_group_tunnel_t() :
   pimpl(std::make_shared<nexthop_group_tunnel_impl_t>()) {}
nexthop_group_tunnel_t::nexthop_group_tunnel_t(ip_prefix_t const & tunnel_endpoint,
                                               std::string const & nhg_name) :
   pimpl(std::make_shared<nexthop_group_tunnel_impl_t>(
      tunnel_endpoint,
      nhg_name
   )) {}
EOS_SDK_PUBLIC nexthop_group_tunnel_t::nexthop_group_tunnel_t(
   const nexthop_group_tunnel_t& other) :
   pimpl(std::make_shared<nexthop_group_tunnel_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC nexthop_group_tunnel_t&
nexthop_group_tunnel_t::operator=(
   nexthop_group_tunnel_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<nexthop_group_tunnel_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC nexthop_group_tunnel_t::nexthop_group_tunnel_t(
   nexthop_group_tunnel_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC nexthop_group_tunnel_t&
nexthop_group_tunnel_t::operator=(
   nexthop_group_tunnel_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
nexthop_group_tunnel_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
nexthop_group_tunnel_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
