// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/decap_group.h"
#include "eos/types/decap_group_impl.h"

namespace eos {

// Default constructor, sets NULL protocol type.
decap_group_t::decap_group_t() :
   pimpl(std::make_shared<decap_group_impl_t>()) {}
decap_group_t::decap_group_t(std::string const & group_name,
                             ip_addr_t const & destination_addr,
                             decap_protocol_type_t protocol_type) :
   pimpl(std::make_shared<decap_group_impl_t>(
      group_name,
      destination_addr,
      protocol_type
   )) {}
EOS_SDK_PUBLIC decap_group_t::decap_group_t(
   const decap_group_t& other) :
   pimpl(std::make_shared<decap_group_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC decap_group_t&
decap_group_t::operator=(
   decap_group_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<decap_group_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
decap_group_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
decap_group_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
