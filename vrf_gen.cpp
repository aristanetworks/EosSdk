// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/vrf.h"
#include "eos/types/vrf_impl.h"

namespace eos {

// Default constructor.
vrf_t::vrf_t() :
   pimpl(std::make_shared<vrf_impl_t>()) {}
vrf_t::vrf_t(std::string name, vrf_state_t state, uint64_t rd) :
   pimpl(std::make_shared<vrf_impl_t>(
      name,
      state,
      rd
   )) {}
EOS_SDK_PUBLIC vrf_t::vrf_t(
   const vrf_t& other) :
   pimpl(std::make_shared<vrf_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC vrf_t&
vrf_t::operator=(
   vrf_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<vrf_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC vrf_t::vrf_t(
   vrf_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC vrf_t&
vrf_t::operator=(
   vrf_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
vrf_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
vrf_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
