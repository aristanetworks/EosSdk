// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/mpls_route.h"
#include "eos/types/mpls_route_impl.h"

namespace eos {

mpls_route_key_t::mpls_route_key_t() :
   pimpl(std::make_shared<mpls_route_key_impl_t>()) {}
mpls_route_key_t::mpls_route_key_t(mpls_label_t top_label,
                                   mpls_route_metric_t metric) :
   pimpl(std::make_shared<mpls_route_key_impl_t>(
      top_label,
      metric
   )) {}
mpls_route_key_t::mpls_route_key_t(std::vector<mpls_label_t> const & labels,
                                   mpls_route_metric_t metric) :
   pimpl(std::make_shared<mpls_route_key_impl_t>(
      labels,
      metric
   )) {}
EOS_SDK_PUBLIC mpls_route_key_t::mpls_route_key_t(
   const mpls_route_key_t& other) :
   pimpl(std::make_shared<mpls_route_key_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC mpls_route_key_t&
mpls_route_key_t::operator=(
   mpls_route_key_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<mpls_route_key_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
mpls_route_key_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
mpls_route_key_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



mpls_route_t::mpls_route_t() :
   pimpl(std::make_shared<mpls_route_impl_t>()) {}
mpls_route_t::mpls_route_t(mpls_route_key_t key) :
   pimpl(std::make_shared<mpls_route_impl_t>(
      key
   )) {}
EOS_SDK_PUBLIC mpls_route_t::mpls_route_t(
   const mpls_route_t& other) :
   pimpl(std::make_shared<mpls_route_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC mpls_route_t&
mpls_route_t::operator=(
   mpls_route_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<mpls_route_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
mpls_route_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
mpls_route_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



mpls_route_via_t::mpls_route_via_t() :
   pimpl(std::make_shared<mpls_route_via_impl_t>()) {}
mpls_route_via_t::mpls_route_via_t(mpls_route_key_t route_key) :
   pimpl(std::make_shared<mpls_route_via_impl_t>(
      route_key
   )) {}
mpls_route_via_t::mpls_route_via_t(mpls_route_key_t route_key,
                                   mpls_action_t label_action) :
   pimpl(std::make_shared<mpls_route_via_impl_t>(
      route_key,
      label_action
   )) {}
EOS_SDK_PUBLIC mpls_route_via_t::mpls_route_via_t(
   const mpls_route_via_t& other) :
   pimpl(std::make_shared<mpls_route_via_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC mpls_route_via_t&
mpls_route_via_t::operator=(
   mpls_route_via_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<mpls_route_via_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
mpls_route_via_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
mpls_route_via_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



mpls_fec_id_t::mpls_fec_id_t() :
   pimpl(std::make_shared<mpls_fec_id_impl_t>()) {}
mpls_fec_id_t::mpls_fec_id_t(uint64_t id) :
   pimpl(std::make_shared<mpls_fec_id_impl_t>(
      id
   )) {}
EOS_SDK_PUBLIC mpls_fec_id_t::mpls_fec_id_t(
   const mpls_fec_id_t& other) :
   pimpl(std::make_shared<mpls_fec_id_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC mpls_fec_id_t&
mpls_fec_id_t::operator=(
   mpls_fec_id_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<mpls_fec_id_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
mpls_fec_id_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
mpls_fec_id_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
