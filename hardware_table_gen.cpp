// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/hardware_table.h"
#include "eos/types/hardware_table_impl.h"

namespace eos {

hardware_table_key_t::hardware_table_key_t() :
   pimpl(std::make_shared<hardware_table_key_impl_t>()) {}
hardware_table_key_t::hardware_table_key_t(std::string const & table_name,
                                           std::string const & feature,
                                           std::string const & chip) :
   pimpl(std::make_shared<hardware_table_key_impl_t>(
      table_name,
      feature,
      chip
   )) {}
hardware_table_key_t::hardware_table_key_t(std::string const & table_name,
                                           std::string const & feature) :
   pimpl(std::make_shared<hardware_table_key_impl_t>(
      table_name,
      feature
   )) {}
hardware_table_key_t::hardware_table_key_t(std::string const & table_name) :
   pimpl(std::make_shared<hardware_table_key_impl_t>(
      table_name
   )) {}
EOS_SDK_PUBLIC hardware_table_key_t::hardware_table_key_t(
   const hardware_table_key_t& other) :
   pimpl(std::make_shared<hardware_table_key_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC hardware_table_key_t&
hardware_table_key_t::operator=(
   hardware_table_key_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<hardware_table_key_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC hardware_table_key_t::hardware_table_key_t(
   hardware_table_key_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC hardware_table_key_t&
hardware_table_key_t::operator=(
   hardware_table_key_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
hardware_table_key_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
hardware_table_key_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



hardware_table_high_watermark_t::hardware_table_high_watermark_t() :
   pimpl(std::make_shared<hardware_table_high_watermark_impl_t>()) {}
hardware_table_high_watermark_t::hardware_table_high_watermark_t(
         uint32_t max_entries, time_t timestamp) :
   pimpl(std::make_shared<hardware_table_high_watermark_impl_t>(
      max_entries,
      timestamp
   )) {}
EOS_SDK_PUBLIC hardware_table_high_watermark_t::hardware_table_high_watermark_t(
   const hardware_table_high_watermark_t& other) :
   pimpl(std::make_shared<hardware_table_high_watermark_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC hardware_table_high_watermark_t&
hardware_table_high_watermark_t::operator=(
   hardware_table_high_watermark_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<hardware_table_high_watermark_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC hardware_table_high_watermark_t::hardware_table_high_watermark_t(
   hardware_table_high_watermark_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC hardware_table_high_watermark_t&
hardware_table_high_watermark_t::operator=(
   hardware_table_high_watermark_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
hardware_table_high_watermark_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
hardware_table_high_watermark_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



hardware_table_usage_t::hardware_table_usage_t() :
   pimpl(std::make_shared<hardware_table_usage_impl_t>()) {}
hardware_table_usage_t::hardware_table_usage_t(uint32_t used_entries,
                                               uint32_t free_entries,
                                               uint32_t committed_entries) :
   pimpl(std::make_shared<hardware_table_usage_impl_t>(
      used_entries,
      free_entries,
      committed_entries
   )) {}
EOS_SDK_PUBLIC hardware_table_usage_t::hardware_table_usage_t(
   const hardware_table_usage_t& other) :
   pimpl(std::make_shared<hardware_table_usage_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC hardware_table_usage_t&
hardware_table_usage_t::operator=(
   hardware_table_usage_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<hardware_table_usage_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC hardware_table_usage_t::hardware_table_usage_t(
   hardware_table_usage_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC hardware_table_usage_t&
hardware_table_usage_t::operator=(
   hardware_table_usage_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
hardware_table_usage_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
hardware_table_usage_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



hardware_table_entry_t::hardware_table_entry_t() :
   pimpl(std::make_shared<hardware_table_entry_impl_t>()) {}
hardware_table_entry_t::hardware_table_entry_t(
         hardware_table_usage_t const & usage, uint32_t max_entries,
         hardware_table_high_watermark_t const & high_watermark) :
   pimpl(std::make_shared<hardware_table_entry_impl_t>(
      usage,
      max_entries,
      high_watermark
   )) {}
EOS_SDK_PUBLIC hardware_table_entry_t::hardware_table_entry_t(
   const hardware_table_entry_t& other) :
   pimpl(std::make_shared<hardware_table_entry_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC hardware_table_entry_t&
hardware_table_entry_t::operator=(
   hardware_table_entry_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<hardware_table_entry_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC hardware_table_entry_t::hardware_table_entry_t(
   hardware_table_entry_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC hardware_table_entry_t&
hardware_table_entry_t::operator=(
   hardware_table_entry_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
hardware_table_entry_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
hardware_table_entry_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
