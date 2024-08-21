// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/subintf.h"
#include "eos/types/subintf_impl.h"

namespace eos {

// Default constructor.
subintf_t::subintf_t() :
   pimpl(std::make_shared<subintf_impl_t>()) {}
subintf_t::subintf_t(intf_id_t intf_id, vlan_id_t vlan_id) :
   pimpl(std::make_shared<subintf_impl_t>(
      intf_id,
      vlan_id
   )) {}
EOS_SDK_PUBLIC subintf_t::subintf_t(
   const subintf_t& other) :
   pimpl(std::make_shared<subintf_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC subintf_t&
subintf_t::operator=(
   subintf_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<subintf_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC subintf_t::subintf_t(
   subintf_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC subintf_t&
subintf_t::operator=(
   subintf_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
subintf_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
subintf_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
