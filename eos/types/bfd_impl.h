// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_BFD_IMPL_H
#define EOS_TYPES_BFD_IMPL_H

#include <eos/hash_mix.h>
#include <eos/utility.h>
#include <forward_list>
#include <memory>
#include <sstream>

namespace eos {

/**
 * BFD session key class.
 * Used to identify a BFD session on a switch.
 */
class EOS_SDK_PUBLIC bfd_session_key_impl_t {
 public:
   bfd_session_key_impl_t();
   bfd_session_key_impl_t(ip_addr_t ip_addr, std::string vrf,
                          bfd_session_type_t type, intf_id_t intf);
   bfd_session_key_impl_t(ip_addr_t ip_addr, std::string vrf,
                          bfd_session_type_t type, intf_id_t intf,
                          ip_addr_t src_ip_addr);
   bfd_session_key_impl_t(ip_addr_t ip_addr, std::string vrf,
                          bfd_session_type_t type, uint64_t tunnel_id);
   bfd_session_key_impl_t(ip_addr_t ip_addr, std::string vrf,
                          bfd_session_type_t type, intf_id_t intf,
                          ip_addr_t src_ip_addr, uint64_t tunnel_id);

   /** Getter for 'ip_addr': IP address of the peer. */
   ip_addr_t ip_addr() const;

   /** Getter for 'vrf': vrf associated with the BFD session. */
   std::string vrf() const;

   /** Getter for 'type': type associated with the BFD session. */
   bfd_session_type_t type() const;

   /** Getter for 'intf': local interface associated with the BFD session. */
   intf_id_t intf() const;

   /** Getter for 'src_ip_addr': Src IP address associated with the BFD session. */
   ip_addr_t src_ip_addr() const;

   /** Getter for 'tunnel_id': Tunnel Id associated with the BFD session. */
   uint64_t tunnel_id() const;

   bool operator==(bfd_session_key_impl_t const & other) const;
   bool operator!=(bfd_session_key_impl_t const & other) const;
   bool operator<(bfd_session_key_impl_t const & other) const;
   /** The hash function for type bfd_session_key_t. */
   uint32_t hash() const;
   /** The hash mix function for type bfd_session_key_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * bfd_session_key_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const bfd_session_key_impl_t& obj);

 private:
   ip_addr_t ip_addr_;
   std::string vrf_;
   bfd_session_type_t type_;
   intf_id_t intf_;
   ip_addr_t src_ip_addr_;
   uint64_t tunnel_id_;
};

/**
 * BFD interval configuration class.
 * Used to specify BFD timer interval.
 */
class EOS_SDK_PUBLIC bfd_interval_impl_t {
 public:
   bfd_interval_impl_t();
   bfd_interval_impl_t(uint16_t tx, uint16_t rx, uint8_t mult);

   /** Getter for 'tx': desired minimum tx interval. */
   uint16_t tx() const;

   /** Getter for 'rx': required minimum rx interval. */
   uint16_t rx() const;

   /** Getter for 'mult': detection multiplier. */
   uint8_t mult() const;

   bool operator==(bfd_interval_impl_t const & other) const;
   bool operator!=(bfd_interval_impl_t const & other) const;
   /** The hash function for type bfd_interval_t. */
   uint32_t hash() const;
   /** The hash mix function for type bfd_interval_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of bfd_interval_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const bfd_interval_impl_t& obj);

 private:
   uint16_t tx_;
   uint16_t rx_;
   uint8_t mult_;
};

/** This data structure is used to describe a BFD session. */
class EOS_SDK_PUBLIC bfd_session_impl_t {
 public:
   bfd_session_impl_t();
   bfd_session_impl_t(bfd_session_key_t peer, bfd_session_status_t status);

   /** Getter for 'peer': the peer for this BFD session. */
   bfd_session_key_t peer() const;

   /** Getter for 'status': the status of the BFD session. */
   bfd_session_status_t status() const;

   bool operator==(bfd_session_impl_t const & other) const;
   bool operator!=(bfd_session_impl_t const & other) const;
   bool operator<(bfd_session_impl_t const & other) const;
   /** The hash function for type bfd_session_t. */
   uint32_t hash() const;
   /** The hash mix function for type bfd_session_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of bfd_session_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const bfd_session_impl_t& obj);

 private:
   bfd_session_key_t peer_;
   bfd_session_status_t status_;
};

/**
 * sBFD echo session key class.
 * Used to identify a sBFD echo session on a switch.
 */
class EOS_SDK_PUBLIC sbfd_echo_session_key_impl_t {
 public:
   sbfd_echo_session_key_impl_t();
   sbfd_echo_session_key_impl_t(ip_addr_t nexthop, intf_id_t nexthop_intf,
                                std::forward_list<mpls_label_t> const & labels,
                                uint8_t ip_dscp, uint8_t mpls_exp);
   /** ip_dscp & mpls_exp defaults to CS6 and 6 respectively. */
   sbfd_echo_session_key_impl_t(ip_addr_t nexthop, intf_id_t nexthop_intf,
                                std::forward_list<mpls_label_t> const & labels);

   /**
    * Getter for 'nexthop': nexthop IP address to send the probes to.
    * If the nexthop is an IPv4 address, the probes will be IPv4 packets, if the
    * nexthop is an IPv6 packet, the probes will be IPv6 packets.
    */
   ip_addr_t nexthop() const;

   /** Getter for 'nexthop_intf': local interface to send probes on. */
   intf_id_t nexthop_intf() const;

   /**
    * Getter for 'labels': MPLS labels to impose on the probes.
    *
    * The first element in iteration order is the outermost label, the last element
    * in iteration order is the innermost label.
    * When using std::forward_list< eos::mpls_label_t >::push_front to build the
    * label stack, the first element pushed will be the innermost label, also known
    * as bottom of stack.
    */
   std::forward_list<mpls_label_t> const & labels() const;

   /** Getter for 'ip_dscp': IPv4/IPv6 DSCP value of the probe. */
   uint8_t ip_dscp() const;

   /** Getter for 'mpls_exp': MPLS exp value of the probe. */
   uint8_t mpls_exp() const;

   bool operator==(sbfd_echo_session_key_impl_t const & other) const;
   bool operator!=(sbfd_echo_session_key_impl_t const & other) const;
   bool operator<(sbfd_echo_session_key_impl_t const & other) const;
   /** The hash function for type sbfd_echo_session_key_t. */
   uint32_t hash() const;
   /** The hash mix function for type sbfd_echo_session_key_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * sbfd_echo_session_key_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const sbfd_echo_session_key_impl_t& obj);

 private:
   ip_addr_t nexthop_;
   intf_id_t nexthop_intf_;
   std::forward_list<mpls_label_t> labels_;
   uint8_t ip_dscp_;
   uint8_t mpls_exp_;
};

/**
 * sBFD echo interval configuration class.
 * Used to specify sBFD echo timer interval.
 */
class EOS_SDK_PUBLIC sbfd_interval_impl_t {
 public:
   sbfd_interval_impl_t();
   sbfd_interval_impl_t(uint16_t tx, uint8_t mult);

   /** Getter for 'tx': desired minimum tx interval, in milliseconds. */
   uint16_t tx() const;

   /** Getter for 'mult': detection multiplier. */
   uint8_t mult() const;

   bool operator==(sbfd_interval_impl_t const & other) const;
   bool operator!=(sbfd_interval_impl_t const & other) const;
   /** The hash function for type sbfd_interval_t. */
   uint32_t hash() const;
   /** The hash mix function for type sbfd_interval_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * sbfd_interval_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const sbfd_interval_impl_t& obj);

 private:
   uint16_t tx_;
   uint8_t mult_;
};

/**
 * sBFD RTT statistics class.
 * Used to report RTT statistics.
 */
class EOS_SDK_PUBLIC sbfd_echo_session_rtt_stats_impl_t {
 public:
   sbfd_echo_session_rtt_stats_impl_t(uint32_t last_rtt, uint32_t min_rtt,
                                      uint32_t avg_rtt, uint32_t max_rtt,
                                      uint32_t snapshot_min_rtt,
                                      uint32_t snapshot_avg_rtt,
                                      uint32_t snapshot_max_rtt);

   /** Getter for 'last_rtt': RTT of the last received probe, in microseconds. */
   uint32_t last_rtt() const;

   /** Getter for 'min_rtt': Minimum RTT for lifetime of session, in microseconds. */
   uint32_t min_rtt() const;

   /** Getter for 'avg_rtt': Average RTT for lifetime of session, in microseconds. */
   uint32_t avg_rtt() const;

   /** Getter for 'max_rtt': Maximum RTT for lifetime of session, in microseconds. */
   uint32_t max_rtt() const;

   /**
    * Getter for 'snapshot_min_rtt': Minimum RTT since last RTT report, in
    * microseconds.
    */
   uint32_t snapshot_min_rtt() const;

   /**
    * Getter for 'snapshot_avg_rtt': Average RTT since last RTT report, in
    * microseconds.
    */
   uint32_t snapshot_avg_rtt() const;

   /**
    * Getter for 'snapshot_max_rtt': Maximum RTT since last RTT report, in
    * microseconds.
    */
   uint32_t snapshot_max_rtt() const;

   bool operator==(sbfd_echo_session_rtt_stats_impl_t const & other) const;
   bool operator!=(sbfd_echo_session_rtt_stats_impl_t const & other) const;
   /** The hash function for type sbfd_echo_session_rtt_stats_t. */
   uint32_t hash() const;
   /** The hash mix function for type sbfd_echo_session_rtt_stats_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * sbfd_echo_session_rtt_stats_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const sbfd_echo_session_rtt_stats_impl_t& obj);

 private:
   uint32_t last_rtt_;
   uint32_t min_rtt_;
   uint32_t avg_rtt_;
   uint32_t max_rtt_;
   uint32_t snapshot_min_rtt_;
   uint32_t snapshot_avg_rtt_;
   uint32_t snapshot_max_rtt_;
};
}

#endif // EOS_TYPES_BFD_IMPL_H
