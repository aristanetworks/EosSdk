// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_INTF_H
#define EOS_TYPES_INTF_H

#include <eos/exception.h>
#include <eos/hash_mix.h>
#include <eos/panic.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

/** The operational status of an interface. */
enum oper_status_t {
   INTF_OPER_NULL,
   INTF_OPER_UP,
   INTF_OPER_DOWN,
};
/** Appends a string representation of enum oper_status_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const oper_status_t & enum_val);

/** The interface's type. */
enum intf_type_t {
   INTF_TYPE_NULL,
   INTF_TYPE_OTHER,
   INTF_TYPE_ETH,
   INTF_TYPE_VLAN,
   INTF_TYPE_MANAGEMENT,
   INTF_TYPE_LOOPBACK,
   INTF_TYPE_LAG,
   INTF_TYPE_NULL0,
   INTF_TYPE_CPU,
   INTF_TYPE_VXLAN,
};
/** Appends a string representation of enum intf_type_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const intf_type_t & enum_val);

/** Unique identifier for an interface. */
class EOS_SDK_PUBLIC intf_id_t {
 public:
   /** Default constructor. */
   intf_id_t();
   /**
    * Constructor based on an interface name, i.e. 'Ethernet3/1', or 'Management1'.
    */
   explicit intf_id_t(char const * name);
   /**
    * Constructor based on an interface name, i.e. 'Ethernet3/1', or 'Management1'.
    */
   explicit intf_id_t(std::string const & name);

   /**
    * Constructor based on internal id representation, not part of the public API.
    */
   explicit intf_id_t(uint64_t) EOS_SDK_INTERNAL;

   /** Returns true if the interface is Null0. */
   bool is_null0() const;
   /** Returns true if the interface is a subinterface. */
   bool is_subintf() const;
   /** Returns the interface's type. */
   intf_type_t intf_type() const;

   /** Returns the interface name as a string, e.g., 'Ethernet3/1'. */
   std::string to_string() const;

   /**
    * Only the 'default interface' provided by the default constructor evaluates to
    * false.
    */
   bool operator!() const;
   bool operator==(intf_id_t const & other) const;
   bool operator!=(intf_id_t const & other) const;
   bool operator<(intf_id_t const & other) const;
   /** The hash function for type intf_id_t. */
   uint32_t hash() const;
   /** The hash mix function for type intf_id_t. */
   void mix_me(hash_mix & h) const;
   /**
    * A utility stream operator that adds a string representation of intf_id_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const intf_id_t& obj);

 private:
   friend struct IntfIdHelper;
   uint64_t intfId_;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const intf_id_t& obj);

class intf_counters_impl_t;
/**
 * Interface counter class.
 *
 * All of these attributes have the same meanings as the corresponding objects in
 * the Interface MIB (RFC 2863, 'IF-MIB').
 */
class EOS_SDK_PUBLIC intf_counters_t {
 public:
   intf_counters_t();
   intf_counters_t(uint64_t out_ucast_pkts, uint64_t out_multicast_pkts,
                   uint64_t out_broadcast_pkts, uint64_t in_ucast_pkts,
                   uint64_t in_multicast_pkts, uint64_t in_broadcast_pkts,
                   uint64_t out_octets, uint64_t in_octets, uint64_t out_discards,
                   uint64_t out_errors, uint64_t in_discards, uint64_t in_errors,
                   seconds_t sample_time);
   intf_counters_t(const intf_counters_t& other);
   intf_counters_t& operator=(
      intf_counters_t const & other);


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

   bool operator==(intf_counters_t const & other) const;
   bool operator!=(intf_counters_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os, const intf_counters_t& obj);

 private:
   std::shared_ptr<intf_counters_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const intf_counters_t& obj);

class intf_traffic_rates_impl_t;
/** Interface traffic rates class. */
class EOS_SDK_PUBLIC intf_traffic_rates_t {
 public:
   intf_traffic_rates_t();
   intf_traffic_rates_t(double out_pkts_rate, double in_pkts_rate,
                        double out_bits_rate, double in_bits_rate,
                        seconds_t sample_time);
   intf_traffic_rates_t(const intf_traffic_rates_t& other);
   intf_traffic_rates_t& operator=(
      intf_traffic_rates_t const & other);


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

   bool operator==(intf_traffic_rates_t const & other) const;
   bool operator!=(intf_traffic_rates_t const & other) const;
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
                                   const intf_traffic_rates_t& obj);

 private:
   std::shared_ptr<intf_traffic_rates_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const intf_traffic_rates_t& obj);

/** Non-existent interface error. */
class EOS_SDK_PUBLIC no_such_interface_error : public error {
 public:
   explicit no_such_interface_error(intf_id_t intf) noexcept;
   explicit no_such_interface_error(std::string const & intfName) noexcept;
   virtual ~no_such_interface_error() noexcept;

   intf_id_t intf() const noexcept;

   virtual void raise() const;
   /** The hash function for type no_such_interface_error. */
   uint32_t hash() const;
   /** The hash mix function for type no_such_interface_error. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * no_such_interface_error to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const no_such_interface_error& obj);

 private:
   intf_id_t intf_;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const no_such_interface_error& obj);

/**
 * Error of configuring an interface as a routed port that cannot be a routed port.
 */
class EOS_SDK_PUBLIC not_switchport_eligible_error : public error {
 public:
   explicit not_switchport_eligible_error(intf_id_t intf) noexcept;
   virtual ~not_switchport_eligible_error() noexcept;

   intf_id_t intf() const noexcept;

   virtual void raise() const;
   /** The hash function for type not_switchport_eligible_error. */
   uint32_t hash() const;
   /** The hash mix function for type not_switchport_eligible_error. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * not_switchport_eligible_error to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const not_switchport_eligible_error& obj);

 private:
   intf_id_t intf_;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os,
                         const not_switchport_eligible_error& obj);
}

#endif // EOS_TYPES_INTF_H
