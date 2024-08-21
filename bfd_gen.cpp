// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/bfd.h"
#include "eos/types/bfd_impl.h"

namespace eos {

// Default constructor.
bfd_session_key_t::bfd_session_key_t() :
   pimpl(std::make_shared<bfd_session_key_impl_t>()) {}
bfd_session_key_t::bfd_session_key_t(ip_addr_t ip_addr, std::string vrf,
                                     bfd_session_type_t type, intf_id_t intf) :
   pimpl(std::make_shared<bfd_session_key_impl_t>(
      ip_addr,
      vrf,
      type,
      intf
   )) {}
bfd_session_key_t::bfd_session_key_t(ip_addr_t ip_addr, std::string vrf,
                                     bfd_session_type_t type, intf_id_t intf,
                                     ip_addr_t src_ip_addr) :
   pimpl(std::make_shared<bfd_session_key_impl_t>(
      ip_addr,
      vrf,
      type,
      intf,
      src_ip_addr
   )) {}
// Sbfd session constructor.
bfd_session_key_t::bfd_session_key_t(ip_addr_t ip_addr, std::string vrf,
                                     bfd_session_type_t type, uint64_t tunnel_id) :
   pimpl(std::make_shared<bfd_session_key_impl_t>(
      ip_addr,
      vrf,
      type,
      tunnel_id
   )) {}
// Constructor with complete argument list.
bfd_session_key_t::bfd_session_key_t(ip_addr_t ip_addr, std::string vrf,
                                     bfd_session_type_t type, intf_id_t intf,
                                     ip_addr_t src_ip_addr, uint64_t tunnel_id) :
   pimpl(std::make_shared<bfd_session_key_impl_t>(
      ip_addr,
      vrf,
      type,
      intf,
      src_ip_addr,
      tunnel_id
   )) {}
EOS_SDK_PUBLIC bfd_session_key_t::bfd_session_key_t(
   const bfd_session_key_t& other) :
   pimpl(std::make_shared<bfd_session_key_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC bfd_session_key_t&
bfd_session_key_t::operator=(
   bfd_session_key_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<bfd_session_key_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC bfd_session_key_t::bfd_session_key_t(
   bfd_session_key_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC bfd_session_key_t&
bfd_session_key_t::operator=(
   bfd_session_key_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
bfd_session_key_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
bfd_session_key_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Default constructor.
bfd_interval_t::bfd_interval_t() :
   pimpl(std::make_shared<bfd_interval_impl_t>()) {}
bfd_interval_t::bfd_interval_t(uint16_t tx, uint16_t rx, uint8_t mult) :
   pimpl(std::make_shared<bfd_interval_impl_t>(
      tx,
      rx,
      mult
   )) {}
EOS_SDK_PUBLIC bfd_interval_t::bfd_interval_t(
   const bfd_interval_t& other) :
   pimpl(std::make_shared<bfd_interval_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC bfd_interval_t&
bfd_interval_t::operator=(
   bfd_interval_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<bfd_interval_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC bfd_interval_t::bfd_interval_t(
   bfd_interval_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC bfd_interval_t&
bfd_interval_t::operator=(
   bfd_interval_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
bfd_interval_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
bfd_interval_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Default constructor.
bfd_session_t::bfd_session_t() :
   pimpl(std::make_shared<bfd_session_impl_t>()) {}
bfd_session_t::bfd_session_t(bfd_session_key_t peer, bfd_session_status_t status) :
   pimpl(std::make_shared<bfd_session_impl_t>(
      peer,
      status
   )) {}
EOS_SDK_PUBLIC bfd_session_t::bfd_session_t(
   const bfd_session_t& other) :
   pimpl(std::make_shared<bfd_session_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC bfd_session_t&
bfd_session_t::operator=(
   bfd_session_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<bfd_session_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC bfd_session_t::bfd_session_t(
   bfd_session_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC bfd_session_t&
bfd_session_t::operator=(
   bfd_session_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
bfd_session_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
bfd_session_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Default constructor.
sbfd_echo_session_key_t::sbfd_echo_session_key_t() :
   pimpl(std::make_shared<sbfd_echo_session_key_impl_t>()) {}
sbfd_echo_session_key_t::sbfd_echo_session_key_t(
         ip_addr_t nexthop, intf_id_t nexthop_intf,
         std::forward_list<mpls_label_t> const & labels, uint8_t ip_dscp,
         uint8_t mpls_exp) :
   pimpl(std::make_shared<sbfd_echo_session_key_impl_t>(
      nexthop,
      nexthop_intf,
      labels,
      ip_dscp,
      mpls_exp
   )) {}
sbfd_echo_session_key_t::sbfd_echo_session_key_t(
         ip_addr_t nexthop, intf_id_t nexthop_intf,
         std::forward_list<mpls_label_t> const & labels) :
   pimpl(std::make_shared<sbfd_echo_session_key_impl_t>(
      nexthop,
      nexthop_intf,
      labels
   )) {}
EOS_SDK_PUBLIC sbfd_echo_session_key_t::sbfd_echo_session_key_t(
   const sbfd_echo_session_key_t& other) :
   pimpl(std::make_shared<sbfd_echo_session_key_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC sbfd_echo_session_key_t&
sbfd_echo_session_key_t::operator=(
   sbfd_echo_session_key_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<sbfd_echo_session_key_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC sbfd_echo_session_key_t::sbfd_echo_session_key_t(
   sbfd_echo_session_key_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC sbfd_echo_session_key_t&
sbfd_echo_session_key_t::operator=(
   sbfd_echo_session_key_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
sbfd_echo_session_key_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
sbfd_echo_session_key_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Default constructor.
sbfd_interval_t::sbfd_interval_t() :
   pimpl(std::make_shared<sbfd_interval_impl_t>()) {}
sbfd_interval_t::sbfd_interval_t(uint16_t tx, uint8_t mult) :
   pimpl(std::make_shared<sbfd_interval_impl_t>(
      tx,
      mult
   )) {}
EOS_SDK_PUBLIC sbfd_interval_t::sbfd_interval_t(
   const sbfd_interval_t& other) :
   pimpl(std::make_shared<sbfd_interval_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC sbfd_interval_t&
sbfd_interval_t::operator=(
   sbfd_interval_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<sbfd_interval_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC sbfd_interval_t::sbfd_interval_t(
   sbfd_interval_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC sbfd_interval_t&
sbfd_interval_t::operator=(
   sbfd_interval_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
sbfd_interval_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
sbfd_interval_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



sbfd_echo_session_rtt_stats_t::sbfd_echo_session_rtt_stats_t(
         uint32_t last_rtt, uint32_t min_rtt, uint32_t avg_rtt, uint32_t max_rtt,
         uint32_t snapshot_min_rtt, uint32_t snapshot_avg_rtt,
         uint32_t snapshot_max_rtt) :
   pimpl(std::make_shared<sbfd_echo_session_rtt_stats_impl_t>(
      last_rtt,
      min_rtt,
      avg_rtt,
      max_rtt,
      snapshot_min_rtt,
      snapshot_avg_rtt,
      snapshot_max_rtt
   )) {}
EOS_SDK_PUBLIC sbfd_echo_session_rtt_stats_t::sbfd_echo_session_rtt_stats_t(
   const sbfd_echo_session_rtt_stats_t& other) :
   pimpl(std::make_shared<sbfd_echo_session_rtt_stats_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC sbfd_echo_session_rtt_stats_t&
sbfd_echo_session_rtt_stats_t::operator=(
   sbfd_echo_session_rtt_stats_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<sbfd_echo_session_rtt_stats_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC sbfd_echo_session_rtt_stats_t::sbfd_echo_session_rtt_stats_t(
   sbfd_echo_session_rtt_stats_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC sbfd_echo_session_rtt_stats_t&
sbfd_echo_session_rtt_stats_t::operator=(
   sbfd_echo_session_rtt_stats_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
sbfd_echo_session_rtt_stats_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
sbfd_echo_session_rtt_stats_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
