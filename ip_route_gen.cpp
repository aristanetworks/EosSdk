// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/ip_route.h"
#include "eos/types/ip_route_impl.h"

namespace eos {

ip_route_key_t::ip_route_key_t() :
   pimpl(std::make_shared<ip_route_key_impl_t>()) {}
ip_route_key_t::ip_route_key_t(ip_prefix_t const & prefix) :
   pimpl(std::make_shared<ip_route_key_impl_t>(
      prefix
   )) {}
ip_route_key_t::ip_route_key_t(ip_prefix_t const & prefix,
                               ip_route_preference_t preference) :
   pimpl(std::make_shared<ip_route_key_impl_t>(
      prefix,
      preference
   )) {}
EOS_SDK_PUBLIC ip_route_key_t::ip_route_key_t(
   const ip_route_key_t& other) :
   pimpl(std::make_shared<ip_route_key_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC ip_route_key_t&
ip_route_key_t::operator=(
   ip_route_key_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<ip_route_key_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC ip_route_key_t::ip_route_key_t(
   ip_route_key_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC ip_route_key_t&
ip_route_key_t::operator=(
   ip_route_key_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
ip_route_key_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
ip_route_key_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



ip_route_t::ip_route_t() :
   pimpl(std::make_shared<ip_route_impl_t>()) {}
ip_route_t::ip_route_t(ip_route_key_t const & key) :
   pimpl(std::make_shared<ip_route_impl_t>(
      key
   )) {}
EOS_SDK_PUBLIC ip_route_t::ip_route_t(
   const ip_route_t& other) :
   pimpl(std::make_shared<ip_route_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC ip_route_t&
ip_route_t::operator=(
   ip_route_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<ip_route_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC ip_route_t::ip_route_t(
   ip_route_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC ip_route_t&
ip_route_t::operator=(
   ip_route_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
ip_route_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
ip_route_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



ip_route_via_t::ip_route_via_t() :
   pimpl(std::make_shared<ip_route_via_impl_t>()) {}
ip_route_via_t::ip_route_via_t(ip_route_key_t const & route_key) :
   pimpl(std::make_shared<ip_route_via_impl_t>(
      route_key
   )) {}
EOS_SDK_PUBLIC ip_route_via_t::ip_route_via_t(
   const ip_route_via_t& other) :
   pimpl(std::make_shared<ip_route_via_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC ip_route_via_t&
ip_route_via_t::operator=(
   ip_route_via_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<ip_route_via_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC ip_route_via_t::ip_route_via_t(
   ip_route_via_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC ip_route_via_t&
ip_route_via_t::operator=(
   ip_route_via_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
ip_route_via_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
ip_route_via_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
