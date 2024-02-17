// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/nexthop_group.h"
#include "eos/types/nexthop_group_impl.h"

namespace eos {

nexthop_group_mpls_action_t::nexthop_group_mpls_action_t() :
   pimpl(std::make_shared<nexthop_group_mpls_action_impl_t>()) {}
nexthop_group_mpls_action_t::nexthop_group_mpls_action_t(mpls_action_t action_type) :
   pimpl(std::make_shared<nexthop_group_mpls_action_impl_t>(
      action_type
   )) {}
nexthop_group_mpls_action_t::nexthop_group_mpls_action_t(
         mpls_action_t action_type,
         std::forward_list<mpls_label_t> const & label_stack) :
   pimpl(std::make_shared<nexthop_group_mpls_action_impl_t>(
      action_type,
      label_stack
   )) {}
EOS_SDK_PUBLIC nexthop_group_mpls_action_t::nexthop_group_mpls_action_t(
   const nexthop_group_mpls_action_t& other) :
   pimpl(std::make_shared<nexthop_group_mpls_action_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC nexthop_group_mpls_action_t&
nexthop_group_mpls_action_t::operator=(
   nexthop_group_mpls_action_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<nexthop_group_mpls_action_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
nexthop_group_mpls_action_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
nexthop_group_mpls_action_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



nexthop_group_entry_counter_t::nexthop_group_entry_counter_t() :
   pimpl(std::make_shared<nexthop_group_entry_counter_impl_t>()) {}
nexthop_group_entry_counter_t::nexthop_group_entry_counter_t(uint64_t packets,
                                                             uint64_t bytes,
                                                             bool valid) :
   pimpl(std::make_shared<nexthop_group_entry_counter_impl_t>(
      packets,
      bytes,
      valid
   )) {}
EOS_SDK_PUBLIC nexthop_group_entry_counter_t::nexthop_group_entry_counter_t(
   const nexthop_group_entry_counter_t& other) :
   pimpl(std::make_shared<nexthop_group_entry_counter_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC nexthop_group_entry_counter_t&
nexthop_group_entry_counter_t::operator=(
   nexthop_group_entry_counter_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<nexthop_group_entry_counter_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
nexthop_group_entry_counter_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
nexthop_group_entry_counter_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



nexthop_group_entry_t::nexthop_group_entry_t() :
   pimpl(std::make_shared<nexthop_group_entry_impl_t>()) {}
nexthop_group_entry_t::nexthop_group_entry_t(ip_addr_t const & nexthop) :
   pimpl(std::make_shared<nexthop_group_entry_impl_t>(
      nexthop
   )) {}
nexthop_group_entry_t::nexthop_group_entry_t(ip_addr_t const & nexthop,
                                             intf_id_t const & intf) :
   pimpl(std::make_shared<nexthop_group_entry_impl_t>(
      nexthop,
      intf
   )) {}
nexthop_group_entry_t::nexthop_group_entry_t(
         std::string const & child_nexthop_group) :
   pimpl(std::make_shared<nexthop_group_entry_impl_t>(
      child_nexthop_group
   )) {}
EOS_SDK_PUBLIC nexthop_group_entry_t::nexthop_group_entry_t(
   const nexthop_group_entry_t& other) :
   pimpl(std::make_shared<nexthop_group_entry_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC nexthop_group_entry_t&
nexthop_group_entry_t::operator=(
   nexthop_group_entry_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<nexthop_group_entry_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
nexthop_group_entry_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
nexthop_group_entry_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



nexthop_group_t::nexthop_group_t() :
   pimpl(std::make_shared<nexthop_group_impl_t>()) {}
nexthop_group_t::nexthop_group_t(std::string name, nexthop_group_encap_t type) :
   pimpl(std::make_shared<nexthop_group_impl_t>(
      name,
      type
   )) {}
nexthop_group_t::nexthop_group_t(std::string name, nexthop_group_encap_t type,
                                 nexthop_group_gre_key_t gre_key_type) :
   pimpl(std::make_shared<nexthop_group_impl_t>(
      name,
      type,
      gre_key_type
   )) {}
nexthop_group_t::nexthop_group_t(std::string name, ip_addr_t const & source_ip) :
   pimpl(std::make_shared<nexthop_group_impl_t>(
      name,
      source_ip
   )) {}
nexthop_group_t::nexthop_group_t(
         std::string name, ip_addr_t const & source_ip,
         std::map<uint16_t, nexthop_group_entry_t> const & nexthops) :
   pimpl(std::make_shared<nexthop_group_impl_t>(
      name,
      source_ip,
      nexthops
   )) {}
EOS_SDK_PUBLIC nexthop_group_t::nexthop_group_t(
   const nexthop_group_t& other) :
   pimpl(std::make_shared<nexthop_group_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC nexthop_group_t&
nexthop_group_t::operator=(
   nexthop_group_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<nexthop_group_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
nexthop_group_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
nexthop_group_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



nexthop_group_programmed_status_t::nexthop_group_programmed_status_t() :
   pimpl(std::make_shared<nexthop_group_programmed_status_impl_t>()) {}
nexthop_group_programmed_status_t::nexthop_group_programmed_status_t(
         nexthop_group_counter_state_t counter_state) :
   pimpl(std::make_shared<nexthop_group_programmed_status_impl_t>(
      counter_state
   )) {}
EOS_SDK_PUBLIC nexthop_group_programmed_status_t::nexthop_group_programmed_status_t(
   const nexthop_group_programmed_status_t& other) :
   pimpl(std::make_shared<nexthop_group_programmed_status_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC nexthop_group_programmed_status_t&
nexthop_group_programmed_status_t::operator=(
   nexthop_group_programmed_status_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<nexthop_group_programmed_status_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
nexthop_group_programmed_status_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
nexthop_group_programmed_status_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
