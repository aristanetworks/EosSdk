// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/bgp_path.h"
#include "eos/types/bgp_path_impl.h"

namespace eos {

bgp_path_attr_fields_t::bgp_path_attr_fields_t() :
   pimpl(std::make_shared<bgp_path_attr_fields_impl_t>()) {}
bgp_path_attr_fields_t::bgp_path_attr_fields_t(bool next_hop) :
   pimpl(std::make_shared<bgp_path_attr_fields_impl_t>(
      next_hop
   )) {}
EOS_SDK_PUBLIC bgp_path_attr_fields_t::bgp_path_attr_fields_t(
   const bgp_path_attr_fields_t& other) :
   pimpl(std::make_shared<bgp_path_attr_fields_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC bgp_path_attr_fields_t&
bgp_path_attr_fields_t::operator=(
   bgp_path_attr_fields_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<bgp_path_attr_fields_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC bgp_path_attr_fields_t::bgp_path_attr_fields_t(
   bgp_path_attr_fields_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC bgp_path_attr_fields_t&
bgp_path_attr_fields_t::operator=(
   bgp_path_attr_fields_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
bgp_path_attr_fields_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
bgp_path_attr_fields_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



bgp_path_options_t::bgp_path_options_t() :
   pimpl(std::make_shared<bgp_path_options_impl_t>()) {}
bgp_path_options_t::bgp_path_options_t(
         bgp_receive_route_stage_t receive_route_stage) :
   pimpl(std::make_shared<bgp_path_options_impl_t>(
      receive_route_stage
   )) {}
EOS_SDK_PUBLIC bgp_path_options_t::bgp_path_options_t(
   const bgp_path_options_t& other) :
   pimpl(std::make_shared<bgp_path_options_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC bgp_path_options_t&
bgp_path_options_t::operator=(
   bgp_path_options_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<bgp_path_options_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC bgp_path_options_t::bgp_path_options_t(
   bgp_path_options_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC bgp_path_options_t&
bgp_path_options_t::operator=(
   bgp_path_options_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
bgp_path_options_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
bgp_path_options_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



bgp_path_attr_t::bgp_path_attr_t() :
   pimpl(std::make_shared<bgp_path_attr_impl_t>()) {}
bgp_path_attr_t::bgp_path_attr_t(uint8_t origin, uint32_t med, uint32_t local_pref) :
   pimpl(std::make_shared<bgp_path_attr_impl_t>(
      origin,
      med,
      local_pref
   )) {}
EOS_SDK_PUBLIC bgp_path_attr_t::bgp_path_attr_t(
   const bgp_path_attr_t& other) :
   pimpl(std::make_shared<bgp_path_attr_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC bgp_path_attr_t&
bgp_path_attr_t::operator=(
   bgp_path_attr_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<bgp_path_attr_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC bgp_path_attr_t::bgp_path_attr_t(
   bgp_path_attr_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC bgp_path_attr_t&
bgp_path_attr_t::operator=(
   bgp_path_attr_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
bgp_path_attr_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
bgp_path_attr_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



bgp_path_key_t::bgp_path_key_t() :
   pimpl(std::make_shared<bgp_path_key_impl_t>()) {}
bgp_path_key_t::bgp_path_key_t(ip_prefix_t const & prefix,
                               ip_addr_t const & peer_addr,
                               std::string const & vrf_name) :
   pimpl(std::make_shared<bgp_path_key_impl_t>(
      prefix,
      peer_addr,
      vrf_name
   )) {}
EOS_SDK_PUBLIC bgp_path_key_t::bgp_path_key_t(
   const bgp_path_key_t& other) :
   pimpl(std::make_shared<bgp_path_key_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC bgp_path_key_t&
bgp_path_key_t::operator=(
   bgp_path_key_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<bgp_path_key_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC bgp_path_key_t::bgp_path_key_t(
   bgp_path_key_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC bgp_path_key_t&
bgp_path_key_t::operator=(
   bgp_path_key_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
bgp_path_key_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
bgp_path_key_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



bgp_path_t::bgp_path_t() :
   pimpl(std::make_shared<bgp_path_impl_t>()) {}
bgp_path_t::bgp_path_t(bgp_path_key_t const & path_key) :
   pimpl(std::make_shared<bgp_path_impl_t>(
      path_key
   )) {}
EOS_SDK_PUBLIC bgp_path_t::bgp_path_t(
   const bgp_path_t& other) :
   pimpl(std::make_shared<bgp_path_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC bgp_path_t&
bgp_path_t::operator=(
   bgp_path_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<bgp_path_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC bgp_path_t::bgp_path_t(
   bgp_path_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC bgp_path_t&
bgp_path_t::operator=(
   bgp_path_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
bgp_path_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
bgp_path_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
