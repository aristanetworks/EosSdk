// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/eth_lag_intf.h"
#include "eos/types/eth_lag_intf_impl.h"

namespace eos {

// Default constructor.
eth_lag_intf_membership_t::eth_lag_intf_membership_t() :
   pimpl(std::make_shared<eth_lag_intf_membership_impl_t>()) {}
eth_lag_intf_membership_t::eth_lag_intf_membership_t(
         intf_id_t eth_lag_intf_id, bool active, std::string const & reason,
         double member_time, eth_lag_intf_member_lacp_mode_t mode) :
   pimpl(std::make_shared<eth_lag_intf_membership_impl_t>(
      eth_lag_intf_id,
      active,
      reason,
      member_time,
      mode
   )) {}
EOS_SDK_PUBLIC eth_lag_intf_membership_t::eth_lag_intf_membership_t(
   const eth_lag_intf_membership_t& other) :
   pimpl(std::make_shared<eth_lag_intf_membership_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC eth_lag_intf_membership_t&
eth_lag_intf_membership_t::operator=(
   eth_lag_intf_membership_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<eth_lag_intf_membership_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC eth_lag_intf_membership_t::eth_lag_intf_membership_t(
   eth_lag_intf_membership_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC eth_lag_intf_membership_t&
eth_lag_intf_membership_t::operator=(
   eth_lag_intf_membership_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
eth_lag_intf_membership_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
eth_lag_intf_membership_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Default constructor.
eth_lag_intf_t::eth_lag_intf_t() :
   pimpl(std::make_shared<eth_lag_intf_impl_t>()) {}
eth_lag_intf_t::eth_lag_intf_t(intf_id_t intf) :
   pimpl(std::make_shared<eth_lag_intf_impl_t>(
      intf
   )) {}
eth_lag_intf_t::eth_lag_intf_t(intf_id_t intf, uint32_t min_links, uint64_t speed,
                               eth_lag_intf_fallback_type_t fallback_type,
                               uint16_t fallback_timeout, uint64_t min_speed) :
   pimpl(std::make_shared<eth_lag_intf_impl_t>(
      intf,
      min_links,
      speed,
      fallback_type,
      fallback_timeout,
      min_speed
   )) {}
EOS_SDK_PUBLIC eth_lag_intf_t::eth_lag_intf_t(
   const eth_lag_intf_t& other) :
   pimpl(std::make_shared<eth_lag_intf_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC eth_lag_intf_t&
eth_lag_intf_t::operator=(
   eth_lag_intf_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<eth_lag_intf_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC eth_lag_intf_t::eth_lag_intf_t(
   eth_lag_intf_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC eth_lag_intf_t&
eth_lag_intf_t::operator=(
   eth_lag_intf_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
eth_lag_intf_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
eth_lag_intf_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
