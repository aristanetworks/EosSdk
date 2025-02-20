// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/directflow.h"
#include "eos/types/directflow_impl.h"

namespace eos {

flow_match_t::flow_match_t() :
   pimpl(std::make_shared<flow_match_impl_t>()) {}
EOS_SDK_PUBLIC flow_match_t::flow_match_t(
   const flow_match_t& other) :
   pimpl(std::make_shared<flow_match_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC flow_match_t&
flow_match_t::operator=(
   flow_match_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<flow_match_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC flow_match_t::flow_match_t(
   flow_match_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC flow_match_t&
flow_match_t::operator=(
   flow_match_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
flow_match_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
flow_match_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



flow_action_t::flow_action_t() :
   pimpl(std::make_shared<flow_action_impl_t>()) {}
EOS_SDK_PUBLIC flow_action_t::flow_action_t(
   const flow_action_t& other) :
   pimpl(std::make_shared<flow_action_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC flow_action_t&
flow_action_t::operator=(
   flow_action_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<flow_action_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC flow_action_t::flow_action_t(
   flow_action_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC flow_action_t&
flow_action_t::operator=(
   flow_action_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
flow_action_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
flow_action_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



flow_entry_t::flow_entry_t() :
   pimpl(std::make_shared<flow_entry_impl_t>()) {}
flow_entry_t::flow_entry_t(std::string const & name, flow_match_t match,
                           flow_action_t action, flow_priority_t priority) :
   pimpl(std::make_shared<flow_entry_impl_t>(
      name,
      match,
      action,
      priority
   )) {}
EOS_SDK_PUBLIC flow_entry_t::flow_entry_t(
   const flow_entry_t& other) :
   pimpl(std::make_shared<flow_entry_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC flow_entry_t&
flow_entry_t::operator=(
   flow_entry_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<flow_entry_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC flow_entry_t::flow_entry_t(
   flow_entry_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC flow_entry_t&
flow_entry_t::operator=(
   flow_entry_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
flow_entry_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
flow_entry_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



flow_counters_t::flow_counters_t() :
   pimpl(std::make_shared<flow_counters_impl_t>()) {}
EOS_SDK_PUBLIC flow_counters_t::flow_counters_t(
   const flow_counters_t& other) :
   pimpl(std::make_shared<flow_counters_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC flow_counters_t&
flow_counters_t::operator=(
   flow_counters_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<flow_counters_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC flow_counters_t::flow_counters_t(
   flow_counters_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC flow_counters_t&
flow_counters_t::operator=(
   flow_counters_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
flow_counters_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
flow_counters_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
