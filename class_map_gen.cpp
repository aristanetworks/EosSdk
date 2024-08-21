// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/class_map.h"
#include "eos/types/class_map_impl.h"

namespace eos {

// Default constructor.
class_map_rule_t::class_map_rule_t() :
   pimpl(std::make_shared<class_map_rule_impl_t>()) {}
class_map_rule_t::class_map_rule_t(acl_key_t const & acl_key) :
   pimpl(std::make_shared<class_map_rule_impl_t>(
      acl_key
   )) {}
EOS_SDK_PUBLIC class_map_rule_t::class_map_rule_t(
   const class_map_rule_t& other) :
   pimpl(std::make_shared<class_map_rule_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC class_map_rule_t&
class_map_rule_t::operator=(
   class_map_rule_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<class_map_rule_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC class_map_rule_t::class_map_rule_t(
   class_map_rule_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC class_map_rule_t&
class_map_rule_t::operator=(
   class_map_rule_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
class_map_rule_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
class_map_rule_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Default constructor.
class_map_t::class_map_t() :
   pimpl(std::make_shared<class_map_impl_t>()) {}
class_map_t::class_map_t(class_map_key_t const & key) :
   pimpl(std::make_shared<class_map_impl_t>(
      key
   )) {}
EOS_SDK_PUBLIC class_map_t::class_map_t(
   const class_map_t& other) :
   pimpl(std::make_shared<class_map_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC class_map_t&
class_map_t::operator=(
   class_map_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<class_map_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC class_map_t::class_map_t(
   class_map_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC class_map_t&
class_map_t::operator=(
   class_map_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
class_map_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
class_map_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
