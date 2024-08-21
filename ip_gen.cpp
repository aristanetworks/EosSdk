// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/ip.h"
#include "eos/types/ip_impl.h"

namespace eos {

ip_addr_mask_t::ip_addr_mask_t() :
   pimpl(std::make_shared<ip_addr_mask_impl_t>()) {}
ip_addr_mask_t::ip_addr_mask_t(ip_addr_t const & addr, uint8_t mask_length) :
   pimpl(std::make_shared<ip_addr_mask_impl_t>(
      addr,
      mask_length
   )) {}
EOS_SDK_PUBLIC ip_addr_mask_t::ip_addr_mask_t(
   const ip_addr_mask_t& other) :
   pimpl(std::make_shared<ip_addr_mask_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC ip_addr_mask_t&
ip_addr_mask_t::operator=(
   ip_addr_mask_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<ip_addr_mask_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC ip_addr_mask_t::ip_addr_mask_t(
   ip_addr_mask_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC ip_addr_mask_t&
ip_addr_mask_t::operator=(
   ip_addr_mask_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
ip_addr_mask_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
ip_addr_mask_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
