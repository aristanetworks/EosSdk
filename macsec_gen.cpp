// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/macsec.h"
#include "eos/types/macsec_impl.h"

namespace eos {

macsec_key_t::macsec_key_t() :
   pimpl(std::make_shared<macsec_key_impl_t>()) {}
EOS_SDK_PUBLIC macsec_key_t::macsec_key_t(
   const macsec_key_t& other) :
   pimpl(std::make_shared<macsec_key_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC macsec_key_t&
macsec_key_t::operator=(
   macsec_key_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<macsec_key_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC macsec_key_t::macsec_key_t(
   macsec_key_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC macsec_key_t&
macsec_key_t::operator=(
   macsec_key_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
macsec_key_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
macsec_key_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



macsec_profile_t::macsec_profile_t() :
   pimpl(std::make_shared<macsec_profile_impl_t>()) {}
macsec_profile_t::macsec_profile_t(macsec_profile_name_t name) :
   pimpl(std::make_shared<macsec_profile_impl_t>(
      name
   )) {}
EOS_SDK_PUBLIC macsec_profile_t::macsec_profile_t(
   const macsec_profile_t& other) :
   pimpl(std::make_shared<macsec_profile_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC macsec_profile_t&
macsec_profile_t::operator=(
   macsec_profile_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<macsec_profile_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC macsec_profile_t::macsec_profile_t(
   macsec_profile_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC macsec_profile_t&
macsec_profile_t::operator=(
   macsec_profile_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
macsec_profile_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
macsec_profile_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



macsec_intf_status_t::macsec_intf_status_t() :
   pimpl(std::make_shared<macsec_intf_status_impl_t>()) {}
EOS_SDK_PUBLIC macsec_intf_status_t::macsec_intf_status_t(
   const macsec_intf_status_t& other) :
   pimpl(std::make_shared<macsec_intf_status_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC macsec_intf_status_t&
macsec_intf_status_t::operator=(
   macsec_intf_status_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<macsec_intf_status_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC macsec_intf_status_t::macsec_intf_status_t(
   macsec_intf_status_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC macsec_intf_status_t&
macsec_intf_status_t::operator=(
   macsec_intf_status_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
macsec_intf_status_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
macsec_intf_status_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



macsec_intf_counters_t::macsec_intf_counters_t() :
   pimpl(std::make_shared<macsec_intf_counters_impl_t>()) {}
macsec_intf_counters_t::macsec_intf_counters_t(uint64_t out_pkts_encrypted,
                                               uint64_t out_octets_encrypted,
                                               uint64_t in_pkts_decrypted,
                                               uint64_t in_octets_decrypted,
                                               uint64_t in_pkts_not_valid) :
   pimpl(std::make_shared<macsec_intf_counters_impl_t>(
      out_pkts_encrypted,
      out_octets_encrypted,
      in_pkts_decrypted,
      in_octets_decrypted,
      in_pkts_not_valid
   )) {}
EOS_SDK_PUBLIC macsec_intf_counters_t::macsec_intf_counters_t(
   const macsec_intf_counters_t& other) :
   pimpl(std::make_shared<macsec_intf_counters_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC macsec_intf_counters_t&
macsec_intf_counters_t::operator=(
   macsec_intf_counters_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<macsec_intf_counters_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC macsec_intf_counters_t::macsec_intf_counters_t(
   macsec_intf_counters_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC macsec_intf_counters_t&
macsec_intf_counters_t::operator=(
   macsec_intf_counters_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
macsec_intf_counters_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
macsec_intf_counters_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
