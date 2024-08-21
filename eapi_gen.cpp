// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/eapi.h"
#include "eos/types/eapi_impl.h"

namespace eos {

eapi_response_t::eapi_response_t() :
   pimpl(std::make_shared<eapi_response_impl_t>()) {}
eapi_response_t::eapi_response_t(bool success, uint32_t error_code,
                                 std::string const & error_message,
                                 std::vector<std::string> const & responses) :
   pimpl(std::make_shared<eapi_response_impl_t>(
      success,
      error_code,
      error_message,
      responses
   )) {}
EOS_SDK_PUBLIC eapi_response_t::eapi_response_t(
   const eapi_response_t& other) :
   pimpl(std::make_shared<eapi_response_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC eapi_response_t&
eapi_response_t::operator=(
   eapi_response_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<eapi_response_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC eapi_response_t::eapi_response_t(
   eapi_response_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC eapi_response_t&
eapi_response_t::operator=(
   eapi_response_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
eapi_response_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
eapi_response_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
