// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/acl.h"
#include "eos/types/acl_impl.h"

namespace eos {

// Default constructor.
acl_ttl_spec_t::acl_ttl_spec_t() :
   pimpl(std::make_shared<acl_ttl_spec_impl_t>()) {}
// Constructor for different ttl specs, note if oper is ACL_RANGE_ANY, the ttl
// should be set to 0.
acl_ttl_spec_t::acl_ttl_spec_t(acl_range_operator_t oper, uint8_t ttl) :
   pimpl(std::make_shared<acl_ttl_spec_impl_t>(
      oper,
      ttl
   )) {}
EOS_SDK_PUBLIC acl_ttl_spec_t::acl_ttl_spec_t(
   const acl_ttl_spec_t& other) :
   pimpl(std::make_shared<acl_ttl_spec_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC acl_ttl_spec_t&
acl_ttl_spec_t::operator=(
   acl_ttl_spec_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<acl_ttl_spec_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC acl_ttl_spec_t::acl_ttl_spec_t(
   acl_ttl_spec_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC acl_ttl_spec_t&
acl_ttl_spec_t::operator=(
   acl_ttl_spec_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
acl_ttl_spec_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
acl_ttl_spec_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



acl_port_spec_t::acl_port_spec_t() :
   pimpl(std::make_shared<acl_port_spec_impl_t>()) {}
acl_port_spec_t::acl_port_spec_t(acl_range_operator_t oper,
                                 std::list<uint16_t> const & ports) :
   pimpl(std::make_shared<acl_port_spec_impl_t>(
      oper,
      ports
   )) {}
EOS_SDK_PUBLIC acl_port_spec_t::acl_port_spec_t(
   const acl_port_spec_t& other) :
   pimpl(std::make_shared<acl_port_spec_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC acl_port_spec_t&
acl_port_spec_t::operator=(
   acl_port_spec_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<acl_port_spec_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC acl_port_spec_t::acl_port_spec_t(
   acl_port_spec_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC acl_port_spec_t&
acl_port_spec_t::operator=(
   acl_port_spec_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
acl_port_spec_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
acl_port_spec_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



acl_rule_base_t::acl_rule_base_t() :
   pimpl(std::make_shared<acl_rule_base_impl_t>()) {}
EOS_SDK_PUBLIC acl_rule_base_t::acl_rule_base_t(
   const acl_rule_base_t& other) :
   pimpl(std::make_shared<acl_rule_base_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC acl_rule_base_t&
acl_rule_base_t::operator=(
   acl_rule_base_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<acl_rule_base_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC acl_rule_base_t::acl_rule_base_t(
   acl_rule_base_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC acl_rule_base_t&
acl_rule_base_t::operator=(
   acl_rule_base_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
acl_rule_base_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
acl_rule_base_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Constructor for concrete rule ip type passed to acl_add_rule() variants.
acl_rule_ip_t::acl_rule_ip_t() : acl_rule_base_t(),
   pimpl(std::make_shared<acl_rule_ip_impl_t>()) {}
EOS_SDK_PUBLIC acl_rule_ip_t::acl_rule_ip_t(
   const acl_rule_ip_t& other) :
   acl_rule_base_t(other),
   pimpl(std::make_shared<acl_rule_ip_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC acl_rule_ip_t&
acl_rule_ip_t::operator=(
   acl_rule_ip_t const & other)
{
   if(this != &other) {
      acl_rule_base_t::operator=(other);
      pimpl = std::make_shared<acl_rule_ip_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC acl_rule_ip_t::acl_rule_ip_t(
   acl_rule_ip_t && other) noexcept  :
   acl_rule_base_t(std::move(other)),
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC acl_rule_ip_t&
acl_rule_ip_t::operator=(
   acl_rule_ip_t && other) noexcept 
{
   if(this != &other) {
      acl_rule_base_t::operator=(std::move(other));
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
acl_rule_ip_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
acl_rule_ip_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



acl_rule_eth_t::acl_rule_eth_t() : acl_rule_base_t(),
   pimpl(std::make_shared<acl_rule_eth_impl_t>()) {}
EOS_SDK_PUBLIC acl_rule_eth_t::acl_rule_eth_t(
   const acl_rule_eth_t& other) :
   acl_rule_base_t(other),
   pimpl(std::make_shared<acl_rule_eth_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC acl_rule_eth_t&
acl_rule_eth_t::operator=(
   acl_rule_eth_t const & other)
{
   if(this != &other) {
      acl_rule_base_t::operator=(other);
      pimpl = std::make_shared<acl_rule_eth_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC acl_rule_eth_t::acl_rule_eth_t(
   acl_rule_eth_t && other) noexcept  :
   acl_rule_base_t(std::move(other)),
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC acl_rule_eth_t&
acl_rule_eth_t::operator=(
   acl_rule_eth_t && other) noexcept 
{
   if(this != &other) {
      acl_rule_base_t::operator=(std::move(other));
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
acl_rule_eth_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
acl_rule_eth_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
