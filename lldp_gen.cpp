// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/lldp.h"
#include "eos/types/lldp_impl.h"

namespace eos {

// TLV Type, default constructor.
lldp_tlv_type_t::lldp_tlv_type_t() :
   pimpl(std::make_shared<lldp_tlv_type_impl_t>()) {}
// TLV Type, full constructor.
lldp_tlv_type_t::lldp_tlv_type_t(uint32_t organization, uint8_t subtype) :
   pimpl(std::make_shared<lldp_tlv_type_impl_t>(
      organization,
      subtype
   )) {}
EOS_SDK_PUBLIC lldp_tlv_type_t::lldp_tlv_type_t(
   const lldp_tlv_type_t& other) :
   pimpl(std::make_shared<lldp_tlv_type_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC lldp_tlv_type_t&
lldp_tlv_type_t::operator=(
   lldp_tlv_type_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<lldp_tlv_type_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC lldp_tlv_type_t::lldp_tlv_type_t(
   lldp_tlv_type_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC lldp_tlv_type_t&
lldp_tlv_type_t::operator=(
   lldp_tlv_type_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
lldp_tlv_type_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
lldp_tlv_type_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



lldp_std_tlv_type_t::lldp_std_tlv_type_t() :
   pimpl(std::make_shared<lldp_std_tlv_type_impl_t>()) {}
EOS_SDK_PUBLIC lldp_std_tlv_type_t::lldp_std_tlv_type_t(
   const lldp_std_tlv_type_t& other) :
   pimpl(std::make_shared<lldp_std_tlv_type_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC lldp_std_tlv_type_t&
lldp_std_tlv_type_t::operator=(
   lldp_std_tlv_type_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<lldp_std_tlv_type_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC lldp_std_tlv_type_t::lldp_std_tlv_type_t(
   lldp_std_tlv_type_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC lldp_std_tlv_type_t&
lldp_std_tlv_type_t::operator=(
   lldp_std_tlv_type_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
lldp_std_tlv_type_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
lldp_std_tlv_type_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



lldp_syscap_t::lldp_syscap_t() :
   pimpl(std::make_shared<lldp_syscap_impl_t>()) {}
// syscap, full constructor.
lldp_syscap_t::lldp_syscap_t(lldp_syscap_bits_t bitset) :
   pimpl(std::make_shared<lldp_syscap_impl_t>(
      bitset
   )) {}
EOS_SDK_PUBLIC lldp_syscap_t::lldp_syscap_t(
   const lldp_syscap_t& other) :
   pimpl(std::make_shared<lldp_syscap_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC lldp_syscap_t&
lldp_syscap_t::operator=(
   lldp_syscap_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<lldp_syscap_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC lldp_syscap_t::lldp_syscap_t(
   lldp_syscap_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC lldp_syscap_t&
lldp_syscap_t::operator=(
   lldp_syscap_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
lldp_syscap_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
lldp_syscap_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



lldp_management_address_t::lldp_management_address_t() :
   pimpl(std::make_shared<lldp_management_address_impl_t>()) {}
// Managment Info constructor.
lldp_management_address_t::lldp_management_address_t(uint32_t address_family,
                                                     std::string address,
                                                     uint32_t snmp_ifindex,
                                                     std::string oid) :
   pimpl(std::make_shared<lldp_management_address_impl_t>(
      address_family,
      address,
      snmp_ifindex,
      oid
   )) {}
EOS_SDK_PUBLIC lldp_management_address_t::lldp_management_address_t(
   const lldp_management_address_t& other) :
   pimpl(std::make_shared<lldp_management_address_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC lldp_management_address_t&
lldp_management_address_t::operator=(
   lldp_management_address_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<lldp_management_address_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC lldp_management_address_t::lldp_management_address_t(
   lldp_management_address_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC lldp_management_address_t&
lldp_management_address_t::operator=(
   lldp_management_address_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
lldp_management_address_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
lldp_management_address_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



lldp_lacp_t::lldp_lacp_t() :
   pimpl(std::make_shared<lldp_lacp_impl_t>()) {}
// LACP Info constructor.
lldp_lacp_t::lldp_lacp_t(bool capable, bool enabled, uint32_t id, bool valid) :
   pimpl(std::make_shared<lldp_lacp_impl_t>(
      capable,
      enabled,
      id,
      valid
   )) {}
EOS_SDK_PUBLIC lldp_lacp_t::lldp_lacp_t(
   const lldp_lacp_t& other) :
   pimpl(std::make_shared<lldp_lacp_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC lldp_lacp_t&
lldp_lacp_t::operator=(
   lldp_lacp_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<lldp_lacp_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC lldp_lacp_t::lldp_lacp_t(
   lldp_lacp_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC lldp_lacp_t&
lldp_lacp_t::operator=(
   lldp_lacp_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
lldp_lacp_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
lldp_lacp_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



lldp_phy_t::lldp_phy_t() :
   pimpl(std::make_shared<lldp_phy_impl_t>()) {}
// PHY Info constructor.
lldp_phy_t::lldp_phy_t(bool autonegSupported, bool autonegEnabled,
                       uint16_t autonegCapabilitiesBm, bool valid) :
   pimpl(std::make_shared<lldp_phy_impl_t>(
      autonegSupported,
      autonegEnabled,
      autonegCapabilitiesBm,
      valid
   )) {}
EOS_SDK_PUBLIC lldp_phy_t::lldp_phy_t(
   const lldp_phy_t& other) :
   pimpl(std::make_shared<lldp_phy_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC lldp_phy_t&
lldp_phy_t::operator=(
   lldp_phy_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<lldp_phy_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC lldp_phy_t::lldp_phy_t(
   lldp_phy_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC lldp_phy_t&
lldp_phy_t::operator=(
   lldp_phy_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
lldp_phy_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
lldp_phy_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



lldp_chassis_id_t::lldp_chassis_id_t() :
   pimpl(std::make_shared<lldp_chassis_id_impl_t>()) {}
// chassis name, full constructor.
lldp_chassis_id_t::lldp_chassis_id_t(lldp_chassis_id_encoding_t encoding,
                                     std::string value) :
   pimpl(std::make_shared<lldp_chassis_id_impl_t>(
      encoding,
      value
   )) {}
EOS_SDK_PUBLIC lldp_chassis_id_t::lldp_chassis_id_t(
   const lldp_chassis_id_t& other) :
   pimpl(std::make_shared<lldp_chassis_id_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC lldp_chassis_id_t&
lldp_chassis_id_t::operator=(
   lldp_chassis_id_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<lldp_chassis_id_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC lldp_chassis_id_t::lldp_chassis_id_t(
   lldp_chassis_id_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC lldp_chassis_id_t&
lldp_chassis_id_t::operator=(
   lldp_chassis_id_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
lldp_chassis_id_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
lldp_chassis_id_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



lldp_intf_id_t::lldp_intf_id_t() :
   pimpl(std::make_shared<lldp_intf_id_impl_t>()) {}
// interface name, full constructor.
lldp_intf_id_t::lldp_intf_id_t(lldp_intf_id_encoding_t encoding, std::string value) :
   pimpl(std::make_shared<lldp_intf_id_impl_t>(
      encoding,
      value
   )) {}
EOS_SDK_PUBLIC lldp_intf_id_t::lldp_intf_id_t(
   const lldp_intf_id_t& other) :
   pimpl(std::make_shared<lldp_intf_id_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC lldp_intf_id_t&
lldp_intf_id_t::operator=(
   lldp_intf_id_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<lldp_intf_id_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC lldp_intf_id_t::lldp_intf_id_t(
   lldp_intf_id_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC lldp_intf_id_t&
lldp_intf_id_t::operator=(
   lldp_intf_id_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
lldp_intf_id_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
lldp_intf_id_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// remote system, default constructor.
lldp_remote_system_t::lldp_remote_system_t() :
   pimpl(std::make_shared<lldp_remote_system_impl_t>()) {}
// remote system, full constructor.
lldp_remote_system_t::lldp_remote_system_t(lldp_chassis_id_t chassis,
                                           lldp_intf_id_t port) :
   pimpl(std::make_shared<lldp_remote_system_impl_t>(
      chassis,
      port
   )) {}
EOS_SDK_PUBLIC lldp_remote_system_t::lldp_remote_system_t(
   const lldp_remote_system_t& other) :
   pimpl(std::make_shared<lldp_remote_system_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC lldp_remote_system_t&
lldp_remote_system_t::operator=(
   lldp_remote_system_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<lldp_remote_system_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC lldp_remote_system_t::lldp_remote_system_t(
   lldp_remote_system_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC lldp_remote_system_t&
lldp_remote_system_t::operator=(
   lldp_remote_system_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
lldp_remote_system_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
lldp_remote_system_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// remote system, default constructor.
lldp_neighbor_t::lldp_neighbor_t() :
   pimpl(std::make_shared<lldp_neighbor_impl_t>()) {}
// first remote system.
lldp_neighbor_t::lldp_neighbor_t(intf_id_t intf) :
   pimpl(std::make_shared<lldp_neighbor_impl_t>(
      intf
   )) {}
// specific remote system.
lldp_neighbor_t::lldp_neighbor_t(intf_id_t intf,
                                 lldp_remote_system_t remote_system) :
   pimpl(std::make_shared<lldp_neighbor_impl_t>(
      intf,
      remote_system
   )) {}
EOS_SDK_PUBLIC lldp_neighbor_t::lldp_neighbor_t(
   const lldp_neighbor_t& other) :
   pimpl(std::make_shared<lldp_neighbor_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC lldp_neighbor_t&
lldp_neighbor_t::operator=(
   lldp_neighbor_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<lldp_neighbor_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC lldp_neighbor_t::lldp_neighbor_t(
   lldp_neighbor_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC lldp_neighbor_t&
lldp_neighbor_t::operator=(
   lldp_neighbor_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
lldp_neighbor_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
lldp_neighbor_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
