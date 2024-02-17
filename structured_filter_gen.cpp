// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/structured_filter.h"
#include "eos/types/structured_filter_impl.h"

namespace eos {

protocol_range_t::protocol_range_t() :
   pimpl(std::make_shared<protocol_range_impl_t>()) {}
EOS_SDK_PUBLIC protocol_range_t::protocol_range_t(
   const protocol_range_t& other) :
   pimpl(std::make_shared<protocol_range_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC protocol_range_t&
protocol_range_t::operator=(
   protocol_range_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<protocol_range_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
protocol_range_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
protocol_range_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



port_range_t::port_range_t() :
   pimpl(std::make_shared<port_range_impl_t>()) {}
EOS_SDK_PUBLIC port_range_t::port_range_t(
   const port_range_t& other) :
   pimpl(std::make_shared<port_range_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC port_range_t&
port_range_t::operator=(
   port_range_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<port_range_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
port_range_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
port_range_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



port_field_t::port_field_t() :
   pimpl(std::make_shared<port_field_impl_t>()) {}
EOS_SDK_PUBLIC port_field_t::port_field_t(
   const port_field_t& other) :
   pimpl(std::make_shared<port_field_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC port_field_t&
port_field_t::operator=(
   port_field_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<port_field_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
port_field_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
port_field_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



protocol_field_t::protocol_field_t() :
   pimpl(std::make_shared<protocol_field_impl_t>()) {}
EOS_SDK_PUBLIC protocol_field_t::protocol_field_t(
   const protocol_field_t& other) :
   pimpl(std::make_shared<protocol_field_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC protocol_field_t&
protocol_field_t::operator=(
   protocol_field_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<protocol_field_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
protocol_field_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
protocol_field_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



tp_rule_filter_t::tp_rule_filter_t() :
   pimpl(std::make_shared<tp_rule_filter_impl_t>()) {}
tp_rule_filter_t::tp_rule_filter_t(traffic_policy_rule_type_t filter_type) :
   pimpl(std::make_shared<tp_rule_filter_impl_t>(
      filter_type
   )) {}
EOS_SDK_PUBLIC tp_rule_filter_t::tp_rule_filter_t(
   const tp_rule_filter_t& other) :
   pimpl(std::make_shared<tp_rule_filter_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC tp_rule_filter_t&
tp_rule_filter_t::operator=(
   tp_rule_filter_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<tp_rule_filter_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
tp_rule_filter_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
tp_rule_filter_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
