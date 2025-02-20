// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/mpls_vrf_label.h"
#include "eos/types/mpls_vrf_label_impl.h"

namespace eos {

// Default constructor.
mpls_vrf_label_t::mpls_vrf_label_t() :
   pimpl(std::make_shared<mpls_vrf_label_impl_t>()) {}
mpls_vrf_label_t::mpls_vrf_label_t(mpls_label_t label, std::string vrf_name) :
   pimpl(std::make_shared<mpls_vrf_label_impl_t>(
      label,
      vrf_name
   )) {}
EOS_SDK_PUBLIC mpls_vrf_label_t::mpls_vrf_label_t(
   const mpls_vrf_label_t& other) :
   pimpl(std::make_shared<mpls_vrf_label_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC mpls_vrf_label_t&
mpls_vrf_label_t::operator=(
   mpls_vrf_label_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<mpls_vrf_label_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC mpls_vrf_label_t::mpls_vrf_label_t(
   mpls_vrf_label_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC mpls_vrf_label_t&
mpls_vrf_label_t::operator=(
   mpls_vrf_label_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
mpls_vrf_label_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
mpls_vrf_label_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
