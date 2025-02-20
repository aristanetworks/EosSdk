// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/policy_map.h"
#include "eos/types/policy_map_impl.h"

namespace eos {

policy_map_key_t::policy_map_key_t() :
   pimpl(std::make_shared<policy_map_key_impl_t>()) {}
policy_map_key_t::policy_map_key_t(std::string const & name,
                                   policy_feature_t feature) :
   pimpl(std::make_shared<policy_map_key_impl_t>(
      name,
      feature
   )) {}
EOS_SDK_PUBLIC policy_map_key_t::policy_map_key_t(
   const policy_map_key_t& other) :
   pimpl(std::make_shared<policy_map_key_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC policy_map_key_t&
policy_map_key_t::operator=(
   policy_map_key_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<policy_map_key_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC policy_map_key_t::policy_map_key_t(
   policy_map_key_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC policy_map_key_t&
policy_map_key_t::operator=(
   policy_map_key_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
policy_map_key_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
policy_map_key_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Default constructor of a PBR/QOS action.
policy_map_action_t::policy_map_action_t() :
   pimpl(std::make_shared<policy_map_action_impl_t>()) {}
policy_map_action_t::policy_map_action_t(policy_action_type_t action_type) :
   pimpl(std::make_shared<policy_map_action_impl_t>(
      action_type
   )) {}
EOS_SDK_PUBLIC policy_map_action_t::policy_map_action_t(
   const policy_map_action_t& other) :
   pimpl(std::make_shared<policy_map_action_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC policy_map_action_t&
policy_map_action_t::operator=(
   policy_map_action_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<policy_map_action_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC policy_map_action_t::policy_map_action_t(
   policy_map_action_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC policy_map_action_t&
policy_map_action_t::operator=(
   policy_map_action_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
policy_map_action_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
policy_map_action_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Default constructor of a traffic-policy action.
traffic_policy_action_t::traffic_policy_action_t() :
   pimpl(std::make_shared<traffic_policy_action_impl_t>()) {}
traffic_policy_action_t::traffic_policy_action_t(
         traffic_policy_action_type_t action_type) :
   pimpl(std::make_shared<traffic_policy_action_impl_t>(
      action_type
   )) {}
EOS_SDK_PUBLIC traffic_policy_action_t::traffic_policy_action_t(
   const traffic_policy_action_t& other) :
   pimpl(std::make_shared<traffic_policy_action_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC traffic_policy_action_t&
traffic_policy_action_t::operator=(
   traffic_policy_action_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<traffic_policy_action_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC traffic_policy_action_t::traffic_policy_action_t(
   traffic_policy_action_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC traffic_policy_action_t&
traffic_policy_action_t::operator=(
   traffic_policy_action_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
traffic_policy_action_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
traffic_policy_action_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



policy_map_rule_t::policy_map_rule_t() :
   pimpl(std::make_shared<policy_map_rule_impl_t>()) {}
policy_map_rule_t::policy_map_rule_t(class_map_key_t const & class_map_key) :
   pimpl(std::make_shared<policy_map_rule_impl_t>(
      class_map_key
   )) {}
EOS_SDK_PUBLIC policy_map_rule_t::policy_map_rule_t(
   const policy_map_rule_t& other) :
   pimpl(std::make_shared<policy_map_rule_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC policy_map_rule_t&
policy_map_rule_t::operator=(
   policy_map_rule_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<policy_map_rule_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC policy_map_rule_t::policy_map_rule_t(
   policy_map_rule_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC policy_map_rule_t&
policy_map_rule_t::operator=(
   policy_map_rule_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
policy_map_rule_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
policy_map_rule_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



policy_map_t::policy_map_t() :
   pimpl(std::make_shared<policy_map_impl_t>()) {}
policy_map_t::policy_map_t(policy_map_key_t const & key) :
   pimpl(std::make_shared<policy_map_impl_t>(
      key
   )) {}
EOS_SDK_PUBLIC policy_map_t::policy_map_t(
   const policy_map_t& other) :
   pimpl(std::make_shared<policy_map_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC policy_map_t&
policy_map_t::operator=(
   policy_map_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<policy_map_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC policy_map_t::policy_map_t(
   policy_map_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC policy_map_t&
policy_map_t::operator=(
   policy_map_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
policy_map_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
policy_map_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



traffic_policy_rule_t::traffic_policy_rule_t() :
   pimpl(std::make_shared<traffic_policy_rule_impl_t>()) {}
traffic_policy_rule_t::traffic_policy_rule_t(
         std::string match_rule_name,
         traffic_policy_rule_type_t traffic_policy_rule_type) :
   pimpl(std::make_shared<traffic_policy_rule_impl_t>(
      match_rule_name,
      traffic_policy_rule_type
   )) {}
EOS_SDK_PUBLIC traffic_policy_rule_t::traffic_policy_rule_t(
   const traffic_policy_rule_t& other) :
   pimpl(std::make_shared<traffic_policy_rule_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC traffic_policy_rule_t&
traffic_policy_rule_t::operator=(
   traffic_policy_rule_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<traffic_policy_rule_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC traffic_policy_rule_t::traffic_policy_rule_t(
   traffic_policy_rule_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC traffic_policy_rule_t&
traffic_policy_rule_t::operator=(
   traffic_policy_rule_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
traffic_policy_rule_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
traffic_policy_rule_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



traffic_policy_t::traffic_policy_t(std::string const & key) :
   pimpl(std::make_shared<traffic_policy_impl_t>(
      key
   )) {}
EOS_SDK_PUBLIC traffic_policy_t::traffic_policy_t(
   const traffic_policy_t& other) :
   pimpl(std::make_shared<traffic_policy_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC traffic_policy_t&
traffic_policy_t::operator=(
   traffic_policy_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<traffic_policy_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC traffic_policy_t::traffic_policy_t(
   traffic_policy_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC traffic_policy_t&
traffic_policy_t::operator=(
   traffic_policy_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
traffic_policy_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
traffic_policy_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



traffic_policy_counter_data_t::traffic_policy_counter_data_t() :
   pimpl(std::make_shared<traffic_policy_counter_data_impl_t>()) {}
traffic_policy_counter_data_t::traffic_policy_counter_data_t(uint64_t pktHits,
                                                             uint64_t byteHits,
                                                             uint64_t pktDrops,
                                                             uint64_t byteDrops) :
   pimpl(std::make_shared<traffic_policy_counter_data_impl_t>(
      pktHits,
      byteHits,
      pktDrops,
      byteDrops
   )) {}
EOS_SDK_PUBLIC traffic_policy_counter_data_t::traffic_policy_counter_data_t(
   const traffic_policy_counter_data_t& other) :
   pimpl(std::make_shared<traffic_policy_counter_data_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC traffic_policy_counter_data_t&
traffic_policy_counter_data_t::operator=(
   traffic_policy_counter_data_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<traffic_policy_counter_data_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC traffic_policy_counter_data_t::traffic_policy_counter_data_t(
   traffic_policy_counter_data_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC traffic_policy_counter_data_t&
traffic_policy_counter_data_t::operator=(
   traffic_policy_counter_data_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
traffic_policy_counter_data_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
traffic_policy_counter_data_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



traffic_policy_counter_t::traffic_policy_counter_t(std::string const & key) :
   pimpl(std::make_shared<traffic_policy_counter_impl_t>(
      key
   )) {}
EOS_SDK_PUBLIC traffic_policy_counter_t::traffic_policy_counter_t(
   const traffic_policy_counter_t& other) :
   pimpl(std::make_shared<traffic_policy_counter_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC traffic_policy_counter_t&
traffic_policy_counter_t::operator=(
   traffic_policy_counter_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<traffic_policy_counter_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC traffic_policy_counter_t::traffic_policy_counter_t(
   traffic_policy_counter_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC traffic_policy_counter_t&
traffic_policy_counter_t::operator=(
   traffic_policy_counter_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
traffic_policy_counter_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
traffic_policy_counter_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



policy_map_hw_status_key_t::policy_map_hw_status_key_t() :
   pimpl(std::make_shared<policy_map_hw_status_key_impl_t>()) {}
policy_map_hw_status_key_t::policy_map_hw_status_key_t(intf_id_t intf_id,
                                                       acl_direction_t direction) :
   pimpl(std::make_shared<policy_map_hw_status_key_impl_t>(
      intf_id,
      direction
   )) {}
EOS_SDK_PUBLIC policy_map_hw_status_key_t::policy_map_hw_status_key_t(
   const policy_map_hw_status_key_t& other) :
   pimpl(std::make_shared<policy_map_hw_status_key_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC policy_map_hw_status_key_t&
policy_map_hw_status_key_t::operator=(
   policy_map_hw_status_key_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<policy_map_hw_status_key_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC policy_map_hw_status_key_t::policy_map_hw_status_key_t(
   policy_map_hw_status_key_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC policy_map_hw_status_key_t&
policy_map_hw_status_key_t::operator=(
   policy_map_hw_status_key_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
policy_map_hw_status_key_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
policy_map_hw_status_key_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



policy_map_hw_statuses_t::policy_map_hw_statuses_t() :
   pimpl(std::make_shared<policy_map_hw_statuses_impl_t>()) {}
policy_map_hw_statuses_t::policy_map_hw_statuses_t(
         
         std::map<policy_map_hw_status_key_t, policy_map_status_t> const &
         intf_statuses) :
   pimpl(std::make_shared<policy_map_hw_statuses_impl_t>(
      intf_statuses
   )) {}
EOS_SDK_PUBLIC policy_map_hw_statuses_t::policy_map_hw_statuses_t(
   const policy_map_hw_statuses_t& other) :
   pimpl(std::make_shared<policy_map_hw_statuses_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC policy_map_hw_statuses_t&
policy_map_hw_statuses_t::operator=(
   policy_map_hw_statuses_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<policy_map_hw_statuses_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC policy_map_hw_statuses_t::policy_map_hw_statuses_t(
   policy_map_hw_statuses_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC policy_map_hw_statuses_t&
policy_map_hw_statuses_t::operator=(
   policy_map_hw_statuses_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
policy_map_hw_statuses_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
policy_map_hw_statuses_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
