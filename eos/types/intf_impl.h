// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_INTF_IMPL_H
#define EOS_TYPES_INTF_IMPL_H

#include <eos/exception.h>
#include <eos/hash_mix.h>
#include <eos/panic.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {


/**
 * Interface counter class.
 *
 * All of these attributes have the same meanings as the corresponding objects in
 * the Interface MIB (RFC 2863, 'IF-MIB').
 */
class EOS_SDK_PUBLIC intf_counters_impl_t {
 public:
   intf_counters_impl_t();
   intf_counters_impl_t(uint64_t out_ucast_pkts, uint64_t out_multicast_pkts,
                        uint64_t out_broadcast_pkts, uint64_t in_ucast_pkts,
                        uint64_t in_multicast_pkts, uint64_t in_broadcast_pkts,
                        uint64_t out_octets, uint64_t in_octets,
                        uint64_t out_discards, uint64_t out_errors,
                        uint64_t in_discards, uint64_t in_errors,
                        seconds_t sample_time);

   /**
    * Getter for 'out_ucast_pkts': IF-MIB ifOutUcastPkts.
    * Note that IF-MIB specifies that ifOutUcastPkts should include packets that
    * were dropped due to excessive collisions, as if they were successfully
    * transmitted. We count these as out_errors.
    */
   uint64_t out_ucast_pkts() const;

   /** Getter for 'out_multicast_pkts': IF-MIB ifOutMulticastPkts counter. */
   uint64_t out_multicast_pkts() const;

   /** Getter for 'out_broadcast_pkts': IF-MIB ifOutBroadcastPkts counter. */
   uint64_t out_broadcast_pkts() const;


   /** Getter for 'in_ucast_pkts': IF-MIB ifInUcastPkts. */
   uint64_t in_ucast_pkts() const;

   /** Getter for 'in_multicast_pkts': IF-MIB ifInMulticastPkts counter. */
   uint64_t in_multicast_pkts() const;

   /** Getter for 'in_broadcast_pkts': IF-MIB ifInBroadcastPkts counter. */
   uint64_t in_broadcast_pkts() const;


   /**
    * Getter for 'out_octets': IF-MIB ifOutOctets counter.
    * Note that for Ethernet interfaces, the octet counters include the MAC header
    * and FCS (but not the preamble or SFD).  This is different to the IEEE 802.3
    * counters (which do not include MAC header and FCS).  See RFC 3635.
    */
   uint64_t out_octets() const;

   /**
    * Getter for 'in_octets': IF-MIB ifInOctets counter.
    * Note that for Ethernet interfaces, the octet counters include the MAC header
    * and FCS (but not the preamble or SFD).  This is different to the IEEE 802.3
    * counters (which do not include MAC header and FCS).  See RFC 3635.
    */
   uint64_t in_octets() const;


   /** Getter for 'out_discards': IF-MIB ifOutDiscards counter. */
   uint64_t out_discards() const;

   /** Getter for 'out_errors': IF-MIB ifOutErrors counter. */
   uint64_t out_errors() const;

   /** Getter for 'in_discards': IF-MIB ifInDiscards counter. */
   uint64_t in_discards() const;

   /**
    * Getter for 'in_errors': IF-MIB ifInErrors counter.
    * The IF-MIB specifies that CRC errors should not get counted at all!, and that
    * inErrors should include IP header checksum errors.  We do not do this. We
    * count CRC errors as inErrors, and IP header checksum errors as good packets
    * at this level (in_ucast_pkts).
    */
   uint64_t in_errors() const;

   /** Getter for 'sample_time': time when the counters were updated. */
   seconds_t sample_time() const;

   bool operator==(intf_counters_impl_t const & other) const;
   bool operator!=(intf_counters_impl_t const & other) const;
   /** The hash function for type intf_counters_t. */
   uint32_t hash() const;
   /** The hash mix function for type intf_counters_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * intf_counters_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const intf_counters_impl_t& obj);

 private:
   uint64_t out_ucast_pkts_;
   uint64_t out_multicast_pkts_;
   uint64_t out_broadcast_pkts_;
   uint64_t in_ucast_pkts_;
   uint64_t in_multicast_pkts_;
   uint64_t in_broadcast_pkts_;
   uint64_t out_octets_;
   uint64_t in_octets_;
   uint64_t out_discards_;
   uint64_t out_errors_;
   uint64_t in_discards_;
   uint64_t in_errors_;
   seconds_t sample_time_;
};

/** Interface traffic rates class. */
class EOS_SDK_PUBLIC intf_traffic_rates_impl_t {
 public:
   intf_traffic_rates_impl_t();
   intf_traffic_rates_impl_t(double out_pkts_rate, double in_pkts_rate,
                             double out_bits_rate, double in_bits_rate,
                             seconds_t sample_time);

   /** Getter for 'out_pkts_rate': output packets per second. */
   double out_pkts_rate() const;

   /** Getter for 'in_pkts_rate': input packets per second. */
   double in_pkts_rate() const;

   /** Getter for 'out_bits_rate': output bits per second. */
   double out_bits_rate() const;

   /** Getter for 'in_bits_rate': input bits per second. */
   double in_bits_rate() const;

   /** Getter for 'sample_time': time when the rates were updated. */
   seconds_t sample_time() const;

   bool operator==(intf_traffic_rates_impl_t const & other) const;
   bool operator!=(intf_traffic_rates_impl_t const & other) const;
   /** The hash function for type intf_traffic_rates_t. */
   uint32_t hash() const;
   /** The hash mix function for type intf_traffic_rates_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * intf_traffic_rates_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const intf_traffic_rates_impl_t& obj);

 private:
   double out_pkts_rate_;
   double in_pkts_rate_;
   double out_bits_rate_;
   double in_bits_rate_;
   seconds_t sample_time_;
};


}

#endif // EOS_TYPES_INTF_IMPL_H
