// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/fib.h"
#include "eos/types/fib_impl.h"

namespace eos {

// Default constructor.
fib_route_key_t::fib_route_key_t() :
   pimpl(std::make_shared<fib_route_key_impl_t>()) {}
fib_route_key_t::fib_route_key_t(ip_prefix_t const & prefix) :
   pimpl(std::make_shared<fib_route_key_impl_t>(
      prefix
   )) {}
EOS_SDK_PUBLIC fib_route_key_t::fib_route_key_t(
   const fib_route_key_t& other) :
   pimpl(std::make_shared<fib_route_key_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC fib_route_key_t&
fib_route_key_t::operator=(
   fib_route_key_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<fib_route_key_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC fib_route_key_t::fib_route_key_t(
   fib_route_key_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC fib_route_key_t&
fib_route_key_t::operator=(
   fib_route_key_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
fib_route_key_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
fib_route_key_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Default constructor.
fib_route_t::fib_route_t() :
   pimpl(std::make_shared<fib_route_impl_t>()) {}
fib_route_t::fib_route_t(fib_route_key_t const & route_key) :
   pimpl(std::make_shared<fib_route_impl_t>(
      route_key
   )) {}
EOS_SDK_PUBLIC fib_route_t::fib_route_t(
   const fib_route_t& other) :
   pimpl(std::make_shared<fib_route_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC fib_route_t&
fib_route_t::operator=(
   fib_route_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<fib_route_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC fib_route_t::fib_route_t(
   fib_route_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC fib_route_t&
fib_route_t::operator=(
   fib_route_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
fib_route_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
fib_route_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Default constructor.
fib_fec_key_t::fib_fec_key_t() :
   pimpl(std::make_shared<fib_fec_key_impl_t>()) {}
fib_fec_key_t::fib_fec_key_t(uint64_t fec_id) :
   pimpl(std::make_shared<fib_fec_key_impl_t>(
      fec_id
   )) {}
EOS_SDK_PUBLIC fib_fec_key_t::fib_fec_key_t(
   const fib_fec_key_t& other) :
   pimpl(std::make_shared<fib_fec_key_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC fib_fec_key_t&
fib_fec_key_t::operator=(
   fib_fec_key_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<fib_fec_key_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC fib_fec_key_t::fib_fec_key_t(
   fib_fec_key_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC fib_fec_key_t&
fib_fec_key_t::operator=(
   fib_fec_key_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
fib_fec_key_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
fib_fec_key_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Default constructor.
fib_via_t::fib_via_t() :
   pimpl(std::make_shared<fib_via_impl_t>()) {}
fib_via_t::fib_via_t(ip_addr_t const & hop, intf_id_t intf) :
   pimpl(std::make_shared<fib_via_impl_t>(
      hop,
      intf
   )) {}
EOS_SDK_PUBLIC fib_via_t::fib_via_t(
   const fib_via_t& other) :
   pimpl(std::make_shared<fib_via_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC fib_via_t&
fib_via_t::operator=(
   fib_via_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<fib_via_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC fib_via_t::fib_via_t(
   fib_via_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC fib_via_t&
fib_via_t::operator=(
   fib_via_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
fib_via_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
fib_via_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Default constructor.
fib_fec_t::fib_fec_t() :
   pimpl(std::make_shared<fib_fec_impl_t>()) {}
fib_fec_t::fib_fec_t(fib_fec_key_t fec_key) :
   pimpl(std::make_shared<fib_fec_impl_t>(
      fec_key
   )) {}
EOS_SDK_PUBLIC fib_fec_t::fib_fec_t(
   const fib_fec_t& other) :
   pimpl(std::make_shared<fib_fec_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC fib_fec_t&
fib_fec_t::operator=(
   fib_fec_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<fib_fec_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC fib_fec_t::fib_fec_t(
   fib_fec_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC fib_fec_t&
fib_fec_t::operator=(
   fib_fec_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
fib_fec_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
fib_fec_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
