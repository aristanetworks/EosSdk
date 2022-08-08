// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_ETH_PHY_INTF_IMPL_H
#define EOS_TYPES_ETH_PHY_INTF_IMPL_H

#include <eos/hash_mix.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

/**
 * Ethernet interface counter class.
 *
 * All of these attributes have the same meanings as the corresponding objects in
 * the Ethernetlike (RFC3635) and RMON (RFC2819) MIBs.
 */
class EOS_SDK_PUBLIC eth_phy_intf_counters_impl_t {
 public:
   eth_phy_intf_counters_impl_t();
   eth_phy_intf_counters_impl_t(uint64_t single_collision_frames,
                                uint64_t multiple_collision_frames,
                                uint64_t fcs_errors, uint64_t alignment_errors,
                                uint64_t deferred_transmissions,
                                uint64_t late_collisions,
                                uint64_t excessive_collisions,
                                uint64_t internal_mac_transmit_errors,
                                uint64_t carrier_sense_errors,
                                uint64_t internal_mac_receive_errors,
                                uint64_t frame_too_shorts,
                                uint64_t frame_too_longs, uint64_t sqe_test_errors,
                                uint64_t symbol_errors,
                                uint64_t in_unknown_opcodes,
                                uint64_t out_pause_frames,
                                uint64_t in_pause_frames, uint64_t fragments,
                                uint64_t jabbers);

   /**
    * Getter for 'single_collision_frames': Etherlike-MIB singleCollisionFrames
    * counter.
    */
   uint64_t single_collision_frames() const;

   /**
    * Getter for 'multiple_collision_frames': Etherlike-MIB multipleCollisionFrames
    * counter.
    */
   uint64_t multiple_collision_frames() const;

   /** Getter for 'fcs_errors': Etherlike-MIB fcsErrors counter. */
   uint64_t fcs_errors() const;

   /** Getter for 'alignment_errors': Etherlike-MIB alignmentErrors counter. */
   uint64_t alignment_errors() const;

   /**
    * Getter for 'deferred_transmissions': Etherlike-MIB deferredTransmissions
    * counter.
    */
   uint64_t deferred_transmissions() const;

   /** Getter for 'late_collisions': Etherlike-MIB lateCollisions counter. */
   uint64_t late_collisions() const;

   /**
    * Getter for 'excessive_collisions': Etherlike-MIB excessiveCollisions counter.
    */
   uint64_t excessive_collisions() const;

   /**
    * Getter for 'internal_mac_transmit_errors': Etherlike-MIB
    * internalMacTransmitErrors counter.
    */
   uint64_t internal_mac_transmit_errors() const;

   /**
    * Getter for 'carrier_sense_errors': Etherlike-MIB carrierSenseErrors counter.
    */
   uint64_t carrier_sense_errors() const;

   /**
    * Getter for 'internal_mac_receive_errors': Etherlike-MIB
    * internalMacReceiveErrors counter.
    */
   uint64_t internal_mac_receive_errors() const;

   /** Getter for 'frame_too_shorts': Etherlike-MIB frameTooShorts counter. */
   uint64_t frame_too_shorts() const;

   /** Getter for 'frame_too_longs': Etherlike-MIB frameTooLongs counter. */
   uint64_t frame_too_longs() const;

   /** Getter for 'sqe_test_errors': Etherlike-MIB sqeTestErrors counter. */
   uint64_t sqe_test_errors() const;

   /** Getter for 'symbol_errors': Etherlike-MIB symbolErrors counter. */
   uint64_t symbol_errors() const;

   /** Getter for 'in_unknown_opcodes': Etherlike-MIB inUnknownOpcodes counter. */
   uint64_t in_unknown_opcodes() const;

   /** Getter for 'out_pause_frames': Etherlike-MIB outPauseFrames counter. */
   uint64_t out_pause_frames() const;

   /** Getter for 'in_pause_frames': Etherlike-MIB inPauseFrames counter. */
   uint64_t in_pause_frames() const;



   /** Getter for 'fragments': RMON-MIB fragments counter. */
   uint64_t fragments() const;

   /** Getter for 'jabbers': RMON-MIB jabbers counter. */
   uint64_t jabbers() const;


   bool operator==(eth_phy_intf_counters_impl_t const & other) const;
   bool operator!=(eth_phy_intf_counters_impl_t const & other) const;
   /** The hash function for type eth_phy_intf_counters_t. */
   uint32_t hash() const;
   /** The hash mix function for type eth_phy_intf_counters_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * eth_phy_intf_counters_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const eth_phy_intf_counters_impl_t& obj);

 private:
   uint64_t single_collision_frames_;
   uint64_t multiple_collision_frames_;
   uint64_t fcs_errors_;
   uint64_t alignment_errors_;
   uint64_t deferred_transmissions_;
   uint64_t late_collisions_;
   uint64_t excessive_collisions_;
   uint64_t internal_mac_transmit_errors_;
   uint64_t carrier_sense_errors_;
   uint64_t internal_mac_receive_errors_;
   uint64_t frame_too_shorts_;
   uint64_t frame_too_longs_;
   uint64_t sqe_test_errors_;
   uint64_t symbol_errors_;
   uint64_t in_unknown_opcodes_;
   uint64_t out_pause_frames_;
   uint64_t in_pause_frames_;
   uint64_t fragments_;
   uint64_t jabbers_;
};

/**
 * Ethernet interface bin counters class.
 *
 * All of these attributes have the same meanings as the corresponding objects in
 * the RMON MIB (RFC2819).
 */
class EOS_SDK_PUBLIC eth_phy_intf_bin_counters_impl_t {
 public:
   eth_phy_intf_bin_counters_impl_t();
   eth_phy_intf_bin_counters_impl_t(uint64_t in_64_octet_frames,
                                    uint64_t in_65_to_127_octet_frames,
                                    uint64_t in_128_to_255_octet_frames,
                                    uint64_t in_256_to_511_octet_frames,
                                    uint64_t in_512_to_1023_octet_frames,
                                    uint64_t in_1024_to_1522_octet_frames,
                                    uint64_t in_1523_to_max_octet_frames,
                                    uint64_t out_64_octet_frames,
                                    uint64_t out_65_to_127_octet_frames,
                                    uint64_t out_128_to_255_octet_frames,
                                    uint64_t out_256_to_511_octet_frames,
                                    uint64_t out_512_to_1023_octet_frames,
                                    uint64_t out_1024_to_1522_octet_frames,
                                    uint64_t out_1523_to_max_octet_frames);

   /** Getter for 'in_64_octet_frames': Input 64 octet frame counter. */
   uint64_t in_64_octet_frames() const;

   /**
    * Getter for 'in_65_to_127_octet_frames': Input 65 to 127 octet frame counter.
    */
   uint64_t in_65_to_127_octet_frames() const;

   /**
    * Getter for 'in_128_to_255_octet_frames': Input 128 to 255 octet frame
    * counter.
    */
   uint64_t in_128_to_255_octet_frames() const;

   /**
    * Getter for 'in_256_to_511_octet_frames': Input 256 to 511 octet frame
    * counter.
    */
   uint64_t in_256_to_511_octet_frames() const;

   /**
    * Getter for 'in_512_to_1023_octet_frames': Input 512 to 1023 octet frame
    * counter.
    */
   uint64_t in_512_to_1023_octet_frames() const;

   /**
    * Getter for 'in_1024_to_1522_octet_frames': Input 1024 to 1522 octet frame
    * counter.
    */
   uint64_t in_1024_to_1522_octet_frames() const;

   /**
    * Getter for 'in_1523_to_max_octet_frames': Input 1523 to max octet frame
    * counter.
    */
   uint64_t in_1523_to_max_octet_frames() const;


   /** Getter for 'out_64_octet_frames': Output 64 octet frame counter. */
   uint64_t out_64_octet_frames() const;

   /**
    * Getter for 'out_65_to_127_octet_frames': Output 65 to 127 octet frame
    * counter.
    */
   uint64_t out_65_to_127_octet_frames() const;

   /**
    * Getter for 'out_128_to_255_octet_frames': Output 128 to 255 octet frame
    * counter.
    */
   uint64_t out_128_to_255_octet_frames() const;

   /**
    * Getter for 'out_256_to_511_octet_frames': Output 256 to 511 octet frame
    * counter.
    */
   uint64_t out_256_to_511_octet_frames() const;

   /**
    * Getter for 'out_512_to_1023_octet_frames': Output 512 to 1023 octet frame
    * counter.
    */
   uint64_t out_512_to_1023_octet_frames() const;

   /**
    * Getter for 'out_1024_to_1522_octet_frames': Output 1024 to 1522 octet frame
    * counter.
    */
   uint64_t out_1024_to_1522_octet_frames() const;

   /**
    * Getter for 'out_1523_to_max_octet_frames': Output 1523 to max octet frame
    * counter.
    */
   uint64_t out_1523_to_max_octet_frames() const;

   bool operator==(eth_phy_intf_bin_counters_impl_t const & other) const;
   bool operator!=(eth_phy_intf_bin_counters_impl_t const & other) const;
   /** The hash function for type eth_phy_intf_bin_counters_t. */
   uint32_t hash() const;
   /** The hash mix function for type eth_phy_intf_bin_counters_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * eth_phy_intf_bin_counters_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const eth_phy_intf_bin_counters_impl_t& obj);

 private:
   uint64_t in_64_octet_frames_;
   uint64_t in_65_to_127_octet_frames_;
   uint64_t in_128_to_255_octet_frames_;
   uint64_t in_256_to_511_octet_frames_;
   uint64_t in_512_to_1023_octet_frames_;
   uint64_t in_1024_to_1522_octet_frames_;
   uint64_t in_1523_to_max_octet_frames_;
   uint64_t out_64_octet_frames_;
   uint64_t out_65_to_127_octet_frames_;
   uint64_t out_128_to_255_octet_frames_;
   uint64_t out_256_to_511_octet_frames_;
   uint64_t out_512_to_1023_octet_frames_;
   uint64_t out_1024_to_1522_octet_frames_;
   uint64_t out_1523_to_max_octet_frames_;
};
}

#endif // EOS_TYPES_ETH_PHY_INTF_IMPL_H
