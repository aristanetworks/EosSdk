// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_FIB_IMPL_H
#define EOS_TYPES_FIB_IMPL_H

#include <eos/hash_mix.h>
#include <eos/ip.h>
#include <eos/ip_route.h>
#include <eos/mpls.h>
#include <eos/utility.h>
#include <forward_list>
#include <memory>
#include <sstream>

namespace eos {

/** An IP route key that goes in FIB. */
class EOS_SDK_PUBLIC fib_route_key_impl_t {
 public:
   fib_route_key_impl_t();
   explicit fib_route_key_impl_t(ip_prefix_t const & prefix);

   /** Getter for 'prefix': IP v4/v6 network prefix. */
   ip_prefix_t prefix() const;
   /** Setter for 'prefix'. */
   void prefix_is(ip_prefix_t const & prefix);
   /** Moving Setter for 'prefix'. */
   void prefix_is(ip_prefix_t && prefix);

   bool operator==(fib_route_key_impl_t const & other) const;
   bool operator!=(fib_route_key_impl_t const & other) const;
   /** The hash function for type fib_route_key_t. */
   uint32_t hash() const;
   /** The hash mix function for type fib_route_key_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * fib_route_key_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const fib_route_key_impl_t& obj);

 private:
   ip_prefix_t prefix_;
};

/**
 * An IP route that goes in FIB.
 * The "fec_id" represents the fec a.k.a adjacency associated with
 * the route. Note FEC stands for Forwarding Equivalence Class.
 */
class EOS_SDK_PUBLIC fib_route_impl_t {
 public:
   fib_route_impl_t();
   explicit fib_route_impl_t(fib_route_key_t const & route_key);

   /** Getter for 'route_key': IP v4/v6 network route key consisting of prefix. */
   fib_route_key_t route_key() const;
   /** Setter for 'route_key'. */
   void route_key_is(fib_route_key_t const & route_key);
   /** Moving Setter for 'route_key'. */
   void route_key_is(fib_route_key_t && route_key);

   /** Getter for 'preference': 0..255 only, defaults to 1. */
   ip_route_preference_t preference() const;
   /** Setter for 'preference'. */
   void preference_is(ip_route_preference_t preference);

   ip_route_metric_t metric() const;
   void metric_is(ip_route_metric_t metric);

   fib_route_type_t route_type() const;
   void route_type_is(fib_route_type_t route_type);

   /** Getter for 'fec_id': id that links prefix to the fec a.k.a Adjacency. */
   uint64_t fec_id() const;
   /** Setter for 'fec_id'. */
   void fec_id_is(uint64_t fec_id);

   bool operator==(fib_route_impl_t const & other) const;
   bool operator!=(fib_route_impl_t const & other) const;
   /** The hash function for type fib_route_t. */
   uint32_t hash() const;
   /** The hash mix function for type fib_route_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of fib_route_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const fib_route_impl_t& obj);

 private:
   fib_route_key_t route_key_;
   ip_route_preference_t preference_;
   ip_route_metric_t metric_;
   fib_route_type_t route_type_;
   uint64_t fec_id_;
};

/** FEC key that goes in FIB. */
class EOS_SDK_PUBLIC fib_fec_key_impl_t {
 public:
   fib_fec_key_impl_t();
   explicit fib_fec_key_impl_t(uint64_t fec_id);

   /**
    * Getter for 'fec_id': fec_id[56:63] denotes the feature, 0: fib Fec, 1:
    * resilientEcmp feature, 2: nextHopGroup feature.
    */
   uint64_t fec_id() const;
   /** Setter for 'fec_id'. */
   void fec_id_is(uint64_t fec_id);

   bool operator==(fib_fec_key_impl_t const & other) const;
   bool operator!=(fib_fec_key_impl_t const & other) const;
   /** The hash function for type fib_fec_key_t. */
   uint32_t hash() const;
   /** The hash mix function for type fib_fec_key_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of fib_fec_key_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const fib_fec_key_impl_t& obj);

 private:
   uint64_t fec_id_;
};

/** via (nexthop) information. */
class EOS_SDK_PUBLIC fib_via_impl_t {
 public:
   fib_via_impl_t();
   fib_via_impl_t(ip_addr_t const & hop, intf_id_t intf);

   ip_addr_t hop() const;
   void hop_is(ip_addr_t const & hop);
   void hop_is(ip_addr_t && hop);

   intf_id_t intf() const;
   void intf_is(intf_id_t intf);

   mpls_label_t mpls_label() const;
   void mpls_label_is(mpls_label_t mpls_label);

   bool operator==(fib_via_impl_t const & other) const;
   bool operator!=(fib_via_impl_t const & other) const;
   /** The hash function for type fib_via_t. */
   uint32_t hash() const;
   /** The hash mix function for type fib_via_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of fib_via_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const fib_via_impl_t& obj);

 private:
   ip_addr_t hop_;
   intf_id_t intf_;
   mpls_label_t mpls_label_;
};

/**
 * FEC (Forwarding Equivalence Class),
 * consists of collection (one or more) vias.
 */
class EOS_SDK_PUBLIC fib_fec_impl_t {
 public:
   fib_fec_impl_t();
   explicit fib_fec_impl_t(fib_fec_key_t fec_key);

   /** Getter for 'fec_key': fec_key consisting of fec_id. */
   fib_fec_key_t fec_key() const;
   /** Setter for 'fec_key'. */
   void fec_key_is(fib_fec_key_t fec_key);

   fib_fec_type_t fec_type() const;
   void fec_type_is(fib_fec_type_t fec_type);

   /**
    * Getter for 'nexthop_group_name': Name of the nexthop group, in case fec_type
    * is FEC_TYPE_NEXTHOP_GROUP.
    */
   std::string nexthop_group_name() const;
   /** Setter for 'nexthop_group_name'. */
   void nexthop_group_name_is(std::string nexthop_group_name);

   /**
    * Getter for 'via': A list of vias that traffic will be distributed amongst.
    * Duplicate vias will be weighted heavily.
    */
   std::forward_list<fib_via_t> const & via() const;
   /** Setter for 'via'. */
   void via_is(std::forward_list<fib_via_t> const & via);
   /** Moving Setter for 'via'. */
   void via_is(std::forward_list<fib_via_t> && via);
   /** Prepend one via to the list. */
   void via_set(fib_via_t const & via);
   /** Prepend one via to the list. */
   void via_set(fib_via_t && via);
   /** Remove all matching via elements. */
   void via_del(fib_via_t const & via);

   /** The hash function for type fib_fec_t. */
   uint32_t hash() const;
   /** The hash mix function for type fib_fec_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of fib_fec_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const fib_fec_impl_t& obj);

 private:
   fib_fec_key_t fec_key_;
   fib_fec_type_t fec_type_;
   std::string nexthop_group_name_;
   std::forward_list<fib_via_t> via_;
};
}

#endif // EOS_TYPES_FIB_IMPL_H
