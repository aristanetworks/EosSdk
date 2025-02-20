// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/intf.h"
#include "eos/types/intf_impl.h"

namespace eos {

// Default constructor.
intf_counters_t::intf_counters_t() :
   pimpl(std::make_shared<intf_counters_impl_t>()) {}
intf_counters_t::intf_counters_t(uint64_t out_ucast_pkts,
                                 uint64_t out_multicast_pkts,
                                 uint64_t out_broadcast_pkts,
                                 uint64_t in_ucast_pkts,
                                 uint64_t in_multicast_pkts,
                                 uint64_t in_broadcast_pkts, uint64_t out_octets,
                                 uint64_t in_octets, uint64_t out_discards,
                                 uint64_t out_errors, uint64_t in_discards,
                                 uint64_t in_errors, seconds_t sample_time) :
   pimpl(std::make_shared<intf_counters_impl_t>(
      out_ucast_pkts,
      out_multicast_pkts,
      out_broadcast_pkts,
      in_ucast_pkts,
      in_multicast_pkts,
      in_broadcast_pkts,
      out_octets,
      in_octets,
      out_discards,
      out_errors,
      in_discards,
      in_errors,
      sample_time
   )) {}
EOS_SDK_PUBLIC intf_counters_t::intf_counters_t(
   const intf_counters_t& other) :
   pimpl(std::make_shared<intf_counters_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC intf_counters_t&
intf_counters_t::operator=(
   intf_counters_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<intf_counters_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC intf_counters_t::intf_counters_t(
   intf_counters_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC intf_counters_t&
intf_counters_t::operator=(
   intf_counters_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
intf_counters_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
intf_counters_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Default constructor.
intf_traffic_rates_t::intf_traffic_rates_t() :
   pimpl(std::make_shared<intf_traffic_rates_impl_t>()) {}
intf_traffic_rates_t::intf_traffic_rates_t(double out_pkts_rate,
                                           double in_pkts_rate,
                                           double out_bits_rate,
                                           double in_bits_rate,
                                           seconds_t sample_time) :
   pimpl(std::make_shared<intf_traffic_rates_impl_t>(
      out_pkts_rate,
      in_pkts_rate,
      out_bits_rate,
      in_bits_rate,
      sample_time
   )) {}
EOS_SDK_PUBLIC intf_traffic_rates_t::intf_traffic_rates_t(
   const intf_traffic_rates_t& other) :
   pimpl(std::make_shared<intf_traffic_rates_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC intf_traffic_rates_t&
intf_traffic_rates_t::operator=(
   intf_traffic_rates_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<intf_traffic_rates_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC intf_traffic_rates_t::intf_traffic_rates_t(
   intf_traffic_rates_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC intf_traffic_rates_t&
intf_traffic_rates_t::operator=(
   intf_traffic_rates_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
intf_traffic_rates_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
intf_traffic_rates_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
