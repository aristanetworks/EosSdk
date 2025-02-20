// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/neighbor_table.h"
#include "eos/types/neighbor_table_impl.h"

namespace eos {

// Default constructor.
neighbor_key_t::neighbor_key_t() :
   pimpl(std::make_shared<neighbor_key_impl_t>()) {}
neighbor_key_t::neighbor_key_t(ip_addr_t const & ip_addr) :
   pimpl(std::make_shared<neighbor_key_impl_t>(
      ip_addr
   )) {}
neighbor_key_t::neighbor_key_t(ip_addr_t const & ip_addr, intf_id_t intf_id) :
   pimpl(std::make_shared<neighbor_key_impl_t>(
      ip_addr,
      intf_id
   )) {}
EOS_SDK_PUBLIC neighbor_key_t::neighbor_key_t(
   const neighbor_key_t& other) :
   pimpl(std::make_shared<neighbor_key_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC neighbor_key_t&
neighbor_key_t::operator=(
   neighbor_key_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<neighbor_key_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC neighbor_key_t::neighbor_key_t(
   neighbor_key_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC neighbor_key_t&
neighbor_key_t::operator=(
   neighbor_key_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
neighbor_key_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
neighbor_key_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Default constructor.
neighbor_entry_t::neighbor_entry_t() :
   pimpl(std::make_shared<neighbor_entry_impl_t>()) {}
neighbor_entry_t::neighbor_entry_t(neighbor_key_t const & neighbor_key,
                                   eth_addr_t eth_addr,
                                   neighbor_entry_type_t entry_type) :
   pimpl(std::make_shared<neighbor_entry_impl_t>(
      neighbor_key,
      eth_addr,
      entry_type
   )) {}
EOS_SDK_PUBLIC neighbor_entry_t::neighbor_entry_t(
   const neighbor_entry_t& other) :
   pimpl(std::make_shared<neighbor_entry_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC neighbor_entry_t&
neighbor_entry_t::operator=(
   neighbor_entry_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<neighbor_entry_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC neighbor_entry_t::neighbor_entry_t(
   neighbor_entry_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC neighbor_entry_t&
neighbor_entry_t::operator=(
   neighbor_entry_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
neighbor_entry_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
neighbor_entry_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
