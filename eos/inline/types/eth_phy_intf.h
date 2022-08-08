// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ETH_PHY_INTF_H
#define EOS_INLINE_TYPES_ETH_PHY_INTF_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const eth_link_speed_t & enum_val) {
   if (enum_val==LINK_SPEED_UNKNOWN) {
      os << "LINK_SPEED_UNKNOWN";
   } else if (enum_val==LINK_SPEED_10MBPS) {
      os << "LINK_SPEED_10MBPS";
   } else if (enum_val==LINK_SPEED_100MBPS) {
      os << "LINK_SPEED_100MBPS";
   } else if (enum_val==LINK_SPEED_1GBPS) {
      os << "LINK_SPEED_1GBPS";
   } else if (enum_val==LINK_SPEED_2P5GBPS) {
      os << "LINK_SPEED_2P5GBPS";
   } else if (enum_val==LINK_SPEED_5GBPS) {
      os << "LINK_SPEED_5GBPS";
   } else if (enum_val==LINK_SPEED_10GBPS) {
      os << "LINK_SPEED_10GBPS";
   } else if (enum_val==LINK_SPEED_25GBPS) {
      os << "LINK_SPEED_25GBPS";
   } else if (enum_val==LINK_SPEED_40GBPS) {
      os << "LINK_SPEED_40GBPS";
   } else if (enum_val==LINK_SPEED_50GBPS) {
      os << "LINK_SPEED_50GBPS";
   } else if (enum_val==LINK_SPEED_100GBPS) {
      os << "LINK_SPEED_100GBPS";
   } else if (enum_val==LINK_SPEED_200GBPS) {
      os << "LINK_SPEED_200GBPS";
   } else if (enum_val==LINK_SPEED_400GBPS) {
      os << "LINK_SPEED_400GBPS";
   } else if (enum_val==LINK_SPEED_800GBPS) {
      os << "LINK_SPEED_800GBPS";
   } else if (enum_val==LINK_SPEED_UNEXPECTED) {
      os << "LINK_SPEED_UNEXPECTED";
   } else {
      os << "Unknown value";
   }
   return os;
}


// Default constructor.
eth_phy_intf_counters_t::eth_phy_intf_counters_t() {
   pimpl = std::shared_ptr<eth_phy_intf_counters_impl_t>(
      new eth_phy_intf_counters_impl_t()
   );
}
eth_phy_intf_counters_t::eth_phy_intf_counters_t(
         uint64_t single_collision_frames, uint64_t multiple_collision_frames,
         uint64_t fcs_errors, uint64_t alignment_errors,
         uint64_t deferred_transmissions, uint64_t late_collisions,
         uint64_t excessive_collisions, uint64_t internal_mac_transmit_errors,
         uint64_t carrier_sense_errors, uint64_t internal_mac_receive_errors,
         uint64_t frame_too_shorts, uint64_t frame_too_longs,
         uint64_t sqe_test_errors, uint64_t symbol_errors,
         uint64_t in_unknown_opcodes, uint64_t out_pause_frames,
         uint64_t in_pause_frames, uint64_t fragments, uint64_t jabbers) {
   pimpl = std::shared_ptr<eth_phy_intf_counters_impl_t>(
      new eth_phy_intf_counters_impl_t(
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
      )
   );
}
eth_phy_intf_counters_t::eth_phy_intf_counters_t(
   const eth_phy_intf_counters_t& other)
{
   pimpl = std::make_unique<eth_phy_intf_counters_impl_t>(
      eth_phy_intf_counters_impl_t(*other.pimpl));
}
eth_phy_intf_counters_t&
eth_phy_intf_counters_t::operator=(
   eth_phy_intf_counters_t const & other)
{
   pimpl = std::shared_ptr<eth_phy_intf_counters_impl_t>(
      new eth_phy_intf_counters_impl_t(*other.pimpl));
   return *this;
}

uint64_t
eth_phy_intf_counters_t::single_collision_frames() const {
   return pimpl->single_collision_frames();
}
uint64_t
eth_phy_intf_counters_t::multiple_collision_frames() const {
   return pimpl->multiple_collision_frames();
}
uint64_t
eth_phy_intf_counters_t::fcs_errors() const {
   return pimpl->fcs_errors();
}
uint64_t
eth_phy_intf_counters_t::alignment_errors() const {
   return pimpl->alignment_errors();
}
uint64_t
eth_phy_intf_counters_t::deferred_transmissions() const {
   return pimpl->deferred_transmissions();
}
uint64_t
eth_phy_intf_counters_t::late_collisions() const {
   return pimpl->late_collisions();
}
uint64_t
eth_phy_intf_counters_t::excessive_collisions() const {
   return pimpl->excessive_collisions();
}
uint64_t
eth_phy_intf_counters_t::internal_mac_transmit_errors() const {
   return pimpl->internal_mac_transmit_errors();
}
uint64_t
eth_phy_intf_counters_t::carrier_sense_errors() const {
   return pimpl->carrier_sense_errors();
}
uint64_t
eth_phy_intf_counters_t::internal_mac_receive_errors() const {
   return pimpl->internal_mac_receive_errors();
}
uint64_t
eth_phy_intf_counters_t::frame_too_shorts() const {
   return pimpl->frame_too_shorts();
}
uint64_t
eth_phy_intf_counters_t::frame_too_longs() const {
   return pimpl->frame_too_longs();
}
uint64_t
eth_phy_intf_counters_t::sqe_test_errors() const {
   return pimpl->sqe_test_errors();
}
uint64_t
eth_phy_intf_counters_t::symbol_errors() const {
   return pimpl->symbol_errors();
}
uint64_t
eth_phy_intf_counters_t::in_unknown_opcodes() const {
   return pimpl->in_unknown_opcodes();
}
uint64_t
eth_phy_intf_counters_t::out_pause_frames() const {
   return pimpl->out_pause_frames();
}
uint64_t
eth_phy_intf_counters_t::in_pause_frames() const {
   return pimpl->in_pause_frames();
}
uint64_t
eth_phy_intf_counters_t::fragments() const {
   return pimpl->fragments();
}
uint64_t
eth_phy_intf_counters_t::jabbers() const {
   return pimpl->jabbers();
}
bool
eth_phy_intf_counters_t::operator==(eth_phy_intf_counters_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
eth_phy_intf_counters_t::operator!=(eth_phy_intf_counters_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
eth_phy_intf_counters_t::hash() const {
   return pimpl->hash();
}
void
eth_phy_intf_counters_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
eth_phy_intf_counters_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const eth_phy_intf_counters_t& obj) {
   return operator<<(os, *obj.pimpl);
}


// Default constructor.
eth_phy_intf_bin_counters_t::eth_phy_intf_bin_counters_t() {
   pimpl = std::shared_ptr<eth_phy_intf_bin_counters_impl_t>(
      new eth_phy_intf_bin_counters_impl_t()
   );
}
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
         uint64_t out_1523_to_max_octet_frames) {
   pimpl = std::shared_ptr<eth_phy_intf_bin_counters_impl_t>(
      new eth_phy_intf_bin_counters_impl_t(
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
      )
   );
}
eth_phy_intf_bin_counters_t::eth_phy_intf_bin_counters_t(
   const eth_phy_intf_bin_counters_t& other)
{
   pimpl = std::make_unique<eth_phy_intf_bin_counters_impl_t>(
      eth_phy_intf_bin_counters_impl_t(*other.pimpl));
}
eth_phy_intf_bin_counters_t&
eth_phy_intf_bin_counters_t::operator=(
   eth_phy_intf_bin_counters_t const & other)
{
   pimpl = std::shared_ptr<eth_phy_intf_bin_counters_impl_t>(
      new eth_phy_intf_bin_counters_impl_t(*other.pimpl));
   return *this;
}

uint64_t
eth_phy_intf_bin_counters_t::in_64_octet_frames() const {
   return pimpl->in_64_octet_frames();
}
uint64_t
eth_phy_intf_bin_counters_t::in_65_to_127_octet_frames() const {
   return pimpl->in_65_to_127_octet_frames();
}
uint64_t
eth_phy_intf_bin_counters_t::in_128_to_255_octet_frames() const {
   return pimpl->in_128_to_255_octet_frames();
}
uint64_t
eth_phy_intf_bin_counters_t::in_256_to_511_octet_frames() const {
   return pimpl->in_256_to_511_octet_frames();
}
uint64_t
eth_phy_intf_bin_counters_t::in_512_to_1023_octet_frames() const {
   return pimpl->in_512_to_1023_octet_frames();
}
uint64_t
eth_phy_intf_bin_counters_t::in_1024_to_1522_octet_frames() const {
   return pimpl->in_1024_to_1522_octet_frames();
}
uint64_t
eth_phy_intf_bin_counters_t::in_1523_to_max_octet_frames() const {
   return pimpl->in_1523_to_max_octet_frames();
}
uint64_t
eth_phy_intf_bin_counters_t::out_64_octet_frames() const {
   return pimpl->out_64_octet_frames();
}
uint64_t
eth_phy_intf_bin_counters_t::out_65_to_127_octet_frames() const {
   return pimpl->out_65_to_127_octet_frames();
}
uint64_t
eth_phy_intf_bin_counters_t::out_128_to_255_octet_frames() const {
   return pimpl->out_128_to_255_octet_frames();
}
uint64_t
eth_phy_intf_bin_counters_t::out_256_to_511_octet_frames() const {
   return pimpl->out_256_to_511_octet_frames();
}
uint64_t
eth_phy_intf_bin_counters_t::out_512_to_1023_octet_frames() const {
   return pimpl->out_512_to_1023_octet_frames();
}
uint64_t
eth_phy_intf_bin_counters_t::out_1024_to_1522_octet_frames() const {
   return pimpl->out_1024_to_1522_octet_frames();
}
uint64_t
eth_phy_intf_bin_counters_t::out_1523_to_max_octet_frames() const {
   return pimpl->out_1523_to_max_octet_frames();
}
bool
eth_phy_intf_bin_counters_t::operator==(eth_phy_intf_bin_counters_t const & other)
       const {
   return pimpl->operator==(*other.pimpl);
}
bool
eth_phy_intf_bin_counters_t::operator!=(eth_phy_intf_bin_counters_t const & other)
       const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
eth_phy_intf_bin_counters_t::hash() const {
   return pimpl->hash();
}
void
eth_phy_intf_bin_counters_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
eth_phy_intf_bin_counters_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const eth_phy_intf_bin_counters_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_ETH_PHY_INTF_H
