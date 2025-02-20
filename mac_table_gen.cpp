// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/mac_table.h"
#include "eos/types/mac_table_impl.h"

namespace eos {

mac_key_t::mac_key_t() :
   pimpl(std::make_shared<mac_key_impl_t>()) {}
mac_key_t::mac_key_t(vlan_id_t vlan_id, eth_addr_t const & eth_addr) :
   pimpl(std::make_shared<mac_key_impl_t>(
      vlan_id,
      eth_addr
   )) {}
EOS_SDK_PUBLIC mac_key_t::mac_key_t(
   const mac_key_t& other) :
   pimpl(std::make_shared<mac_key_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC mac_key_t&
mac_key_t::operator=(
   mac_key_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<mac_key_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC mac_key_t::mac_key_t(
   mac_key_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC mac_key_t&
mac_key_t::operator=(
   mac_key_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
mac_key_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
mac_key_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



mac_entry_t::mac_entry_t() :
   pimpl(std::make_shared<mac_entry_impl_t>()) {}
mac_entry_t::mac_entry_t(mac_key_t const & mac_key) :
   pimpl(std::make_shared<mac_entry_impl_t>(
      mac_key
   )) {}
mac_entry_t::mac_entry_t(mac_key_t const & mac_key, intf_id_t intf) :
   pimpl(std::make_shared<mac_entry_impl_t>(
      mac_key,
      intf
   )) {}
mac_entry_t::mac_entry_t(mac_key_t const & mac_key,
                         std::set<intf_id_t> const & intfs) :
   pimpl(std::make_shared<mac_entry_impl_t>(
      mac_key,
      intfs
   )) {}
mac_entry_t::mac_entry_t(vlan_id_t vlan_id, eth_addr_t eth_addr) :
   pimpl(std::make_shared<mac_entry_impl_t>(
      vlan_id,
      eth_addr
   )) {}
mac_entry_t::mac_entry_t(eth_addr_t eth_addr, intf_id_t intf) :
   pimpl(std::make_shared<mac_entry_impl_t>(
      eth_addr,
      intf
   )) {}
EOS_SDK_PUBLIC mac_entry_t::mac_entry_t(
   const mac_entry_t& other) :
   pimpl(std::make_shared<mac_entry_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC mac_entry_t&
mac_entry_t::operator=(
   mac_entry_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<mac_entry_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC mac_entry_t::mac_entry_t(
   mac_entry_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC mac_entry_t&
mac_entry_t::operator=(
   mac_entry_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
mac_entry_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
mac_entry_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
