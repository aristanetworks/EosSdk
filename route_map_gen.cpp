// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/route_map.h"
#include "eos/types/route_map_impl.h"

namespace eos {

link_bandwidth_t::link_bandwidth_t(float value, bandwidth_unit_t unit) :
   pimpl(std::make_shared<link_bandwidth_impl_t>(
      value,
      unit
   )) {}
link_bandwidth_t::link_bandwidth_t(float value) :
   pimpl(std::make_shared<link_bandwidth_impl_t>(
      value
   )) {}
link_bandwidth_t::link_bandwidth_t() :
   pimpl(std::make_shared<link_bandwidth_impl_t>()) {}
EOS_SDK_PUBLIC link_bandwidth_t::link_bandwidth_t(
   const link_bandwidth_t& other) :
   pimpl(std::make_shared<link_bandwidth_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC link_bandwidth_t&
link_bandwidth_t::operator=(
   link_bandwidth_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<link_bandwidth_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
link_bandwidth_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
link_bandwidth_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



route_map_link_bandwidth_t::route_map_link_bandwidth_t() :
   pimpl(std::make_shared<route_map_link_bandwidth_impl_t>()) {}
EOS_SDK_PUBLIC route_map_link_bandwidth_t::route_map_link_bandwidth_t(
   const route_map_link_bandwidth_t& other) :
   pimpl(std::make_shared<route_map_link_bandwidth_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC route_map_link_bandwidth_t&
route_map_link_bandwidth_t::operator=(
   route_map_link_bandwidth_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<route_map_link_bandwidth_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
route_map_link_bandwidth_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
route_map_link_bandwidth_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



route_map_entry_t::route_map_entry_t() :
   pimpl(std::make_shared<route_map_entry_impl_t>()) {}
route_map_entry_t::route_map_entry_t(bool permit) :
   pimpl(std::make_shared<route_map_entry_impl_t>(
      permit
   )) {}
EOS_SDK_PUBLIC route_map_entry_t::route_map_entry_t(
   const route_map_entry_t& other) :
   pimpl(std::make_shared<route_map_entry_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC route_map_entry_t&
route_map_entry_t::operator=(
   route_map_entry_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<route_map_entry_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
route_map_entry_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
route_map_entry_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



route_map_t::route_map_t() :
   pimpl(std::make_shared<route_map_impl_t>()) {}
EOS_SDK_PUBLIC route_map_t::route_map_t(
   const route_map_t& other) :
   pimpl(std::make_shared<route_map_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC route_map_t&
route_map_t::operator=(
   route_map_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<route_map_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
route_map_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
route_map_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
