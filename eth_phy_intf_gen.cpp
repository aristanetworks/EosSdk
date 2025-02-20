// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/base.h"
#include "eos/types/eth_phy_intf.h"
#include "eos/types/eth_phy_intf_impl.h"

namespace eos {

// Default constructor.
eth_phy_intf_counters_t::eth_phy_intf_counters_t() :
   pimpl(std::make_shared<eth_phy_intf_counters_impl_t>()) {}
eth_phy_intf_counters_t::eth_phy_intf_counters_t(
         uint64_t single_collision_frames, uint64_t multiple_collision_frames,
         uint64_t fcs_errors, uint64_t alignment_errors,
         uint64_t deferred_transmissions, uint64_t late_collisions,
         uint64_t excessive_collisions, uint64_t internal_mac_transmit_errors,
         uint64_t carrier_sense_errors, uint64_t internal_mac_receive_errors,
         uint64_t frame_too_shorts, uint64_t frame_too_longs,
         uint64_t sqe_test_errors, uint64_t symbol_errors,
         uint64_t in_unknown_opcodes, uint64_t out_pause_frames,
         uint64_t in_pause_frames, uint64_t fragments, uint64_t jabbers) :
   pimpl(std::make_shared<eth_phy_intf_counters_impl_t>(
      single_collision_frames,
      multiple_collision_frames,
      fcs_errors,
      alignment_errors,
      deferred_transmissions,
      late_collisions,
      excessive_collisions,
      internal_mac_transmit_errors,
      carrier_sense_errors,
      internal_mac_receive_errors,
      frame_too_shorts,
      frame_too_longs,
      sqe_test_errors,
      symbol_errors,
      in_unknown_opcodes,
      out_pause_frames,
      in_pause_frames,
      fragments,
      jabbers
   )) {}
EOS_SDK_PUBLIC eth_phy_intf_counters_t::eth_phy_intf_counters_t(
   const eth_phy_intf_counters_t& other) :
   pimpl(std::make_shared<eth_phy_intf_counters_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC eth_phy_intf_counters_t&
eth_phy_intf_counters_t::operator=(
   eth_phy_intf_counters_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<eth_phy_intf_counters_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC eth_phy_intf_counters_t::eth_phy_intf_counters_t(
   eth_phy_intf_counters_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC eth_phy_intf_counters_t&
eth_phy_intf_counters_t::operator=(
   eth_phy_intf_counters_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
eth_phy_intf_counters_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
eth_phy_intf_counters_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}



// Default constructor.
eth_phy_intf_bin_counters_t::eth_phy_intf_bin_counters_t() :
   pimpl(std::make_shared<eth_phy_intf_bin_counters_impl_t>()) {}
eth_phy_intf_bin_counters_t::eth_phy_intf_bin_counters_t(
         uint64_t in_64_octet_frames, uint64_t in_65_to_127_octet_frames,
         uint64_t in_128_to_255_octet_frames, uint64_t in_256_to_511_octet_frames,
         uint64_t in_512_to_1023_octet_frames,
         uint64_t in_1024_to_1522_octet_frames,
         uint64_t in_1523_to_max_octet_frames, uint64_t out_64_octet_frames,
         uint64_t out_65_to_127_octet_frames, uint64_t out_128_to_255_octet_frames,
         uint64_t out_256_to_511_octet_frames,
         uint64_t out_512_to_1023_octet_frames,
         uint64_t out_1024_to_1522_octet_frames,
         uint64_t out_1523_to_max_octet_frames) :
   pimpl(std::make_shared<eth_phy_intf_bin_counters_impl_t>(
      in_64_octet_frames,
      in_65_to_127_octet_frames,
      in_128_to_255_octet_frames,
      in_256_to_511_octet_frames,
      in_512_to_1023_octet_frames,
      in_1024_to_1522_octet_frames,
      in_1523_to_max_octet_frames,
      out_64_octet_frames,
      out_65_to_127_octet_frames,
      out_128_to_255_octet_frames,
      out_256_to_511_octet_frames,
      out_512_to_1023_octet_frames,
      out_1024_to_1522_octet_frames,
      out_1523_to_max_octet_frames
   )) {}
EOS_SDK_PUBLIC eth_phy_intf_bin_counters_t::eth_phy_intf_bin_counters_t(
   const eth_phy_intf_bin_counters_t& other) :
   pimpl(std::make_shared<eth_phy_intf_bin_counters_impl_t>(
      *other.pimpl)) {}
EOS_SDK_PUBLIC eth_phy_intf_bin_counters_t&
eth_phy_intf_bin_counters_t::operator=(
   eth_phy_intf_bin_counters_t const & other)
{
   if(this != &other) {
      pimpl = std::make_shared<eth_phy_intf_bin_counters_impl_t>(
         *other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC eth_phy_intf_bin_counters_t::eth_phy_intf_bin_counters_t(
   eth_phy_intf_bin_counters_t && other) noexcept  :
   pimpl(std::move(other.pimpl)) {}
EOS_SDK_PUBLIC eth_phy_intf_bin_counters_t&
eth_phy_intf_bin_counters_t::operator=(
   eth_phy_intf_bin_counters_t && other) noexcept 
{
   if(this != &other) {
      std::swap(pimpl, other.pimpl);
   }
   return *this;
}

EOS_SDK_PUBLIC void *
eth_phy_intf_bin_counters_t::operator new( std::size_t size ) {
   return ::operator new( size );
}
EOS_SDK_PUBLIC void
eth_phy_intf_bin_counters_t::operator delete( void * p ) noexcept {
   ::operator delete( p );
}


} // namespace eos
