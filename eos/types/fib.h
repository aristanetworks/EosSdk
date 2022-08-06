// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_FIB_H
#define EOS_TYPES_FIB_H

#include <eos/hash_mix.h>
#include <eos/ip.h>
#include <eos/ip_route.h>
#include <eos/mpls.h>
#include <eos/utility.h>
#include <forward_list>
#include <memory>
#include <sstream>

namespace eos {

class fib_route_key_impl_t;
/** An IP route key that goes in FIB. */
class EOS_SDK_PUBLIC fib_route_key_t {
 public:
   fib_route_key_t();
   explicit fib_route_key_t(ip_prefix_t const & prefix);
   fib_route_key_t(const fib_route_key_t& other);
   fib_route_key_t& operator=(
      fib_route_key_t const & other);


   /** Getter for 'prefix': IP v4/v6 network prefix. */
   ip_prefix_t prefix() const;
   /** Setter for 'prefix'. */
   void prefix_is(ip_prefix_t const & prefix);

   bool operator==(fib_route_key_t const & other) const;
   bool operator!=(fib_route_key_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os, const fib_route_key_t& obj);

 private:
   std::shared_ptr<fib_route_key_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const fib_route_key_t& obj);

/** Enums for host routes and FIB routes. */
enum fib_route_type_t {
   ROUTE_TYPE_INVALID,
   /** Host routes. */
   ROUTE_TYPE_RECEIVE,
   ROUTE_TYPE_RECEIVE_BCAST,
   ROUTE_TYPE_ATTACHED,
   /** Unknows routing protocol. */
   ROUTE_TYPE_UNKNOWN,
   /** FIB routes. */
   ROUTE_TYPE_STATIC_CONFIG,
   ROUTE_TYPE_KERNEL,
   ROUTE_TYPE_RIP,
   ROUTE_TYPE_CONNECTED,
   ROUTE_TYPE_REDIRECT,
   ROUTE_TYPE_BGP_AGGREGATE,
   ROUTE_TYPE_OSPF_AGGREGATE,
   ROUTE_TYPE_OSPF_INTRA_AREA,
   ROUTE_TYPE_OSPF_INTER_AREA,
   ROUTE_TYPE_OSPF_EXTERNAL_TYPE1,
   ROUTE_TYPE_OSPF_EXTERNAL_TYPE2,
   ROUTE_TYPE_OSPF_NSSA_EXTERNAL_TYPE1,
   ROUTE_TYPE_OSPF_NSSA_EXTERNAL_TYPE2,
   ROUTE_TYPE_BGP,
   ROUTE_TYPE_IBGP,
   ROUTE_TYPE_EBGP,
   ROUTE_TYPE_LBGP,
   /** Unused in EOS 4.15.1, use ROUTE_TYPE_ISIS_LEVEL1/2 instead. */
   ROUTE_TYPE_ISIS,
   ROUTE_TYPE_ISIS_LEVEL1,
   ROUTE_TYPE_ISIS_LEVEL2,
   ROUTE_TYPE_NEXTHOP_GROUP,
   ROUTE_TYPE_OSPF3,
};
/** Appends a string representation of enum fib_route_type_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const fib_route_type_t & enum_val);

class fib_route_impl_t;
/**
 * An IP route that goes in FIB.
 * The "fec_id" represents the fec a.k.a adjacency associated with
 * the route. Note FEC stands for Forwarding Equivalence Class.
 */
class EOS_SDK_PUBLIC fib_route_t {
 public:
   fib_route_t();
   explicit fib_route_t(fib_route_key_t const & route_key);
   fib_route_t(const fib_route_t& other);
   fib_route_t& operator=(
      fib_route_t const & other);


   /** Getter for 'route_key': IP v4/v6 network route key consisting of prefix. */
   fib_route_key_t route_key() const;
   /** Setter for 'route_key'. */
   void route_key_is(fib_route_key_t const & route_key);

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

   bool operator==(fib_route_t const & other) const;
   bool operator!=(fib_route_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os, const fib_route_t& obj);

 private:
   std::shared_ptr<fib_route_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const fib_route_t& obj);

class fib_fec_key_impl_t;
/** FEC key that goes in FIB. */
class EOS_SDK_PUBLIC fib_fec_key_t {
 public:
   fib_fec_key_t();
   explicit fib_fec_key_t(uint64_t fec_id);
   fib_fec_key_t(const fib_fec_key_t& other);
   fib_fec_key_t& operator=(
      fib_fec_key_t const & other);


   /**
    * Getter for 'fec_id': fec_id[56:63] denotes the feature, 0: fib Fec, 1:
    * resilientEcmp feature, 2: nextHopGroup feature.
    */
   uint64_t fec_id() const;
   /** Setter for 'fec_id'. */
   void fec_id_is(uint64_t fec_id);

   bool operator==(fib_fec_key_t const & other) const;
   bool operator!=(fib_fec_key_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os, const fib_fec_key_t& obj);

 private:
   std::shared_ptr<fib_fec_key_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const fib_fec_key_t& obj);

class fib_via_impl_t;
/** via (nexthop) information. */
class EOS_SDK_PUBLIC fib_via_t {
 public:
   fib_via_t();
   fib_via_t(ip_addr_t const & hop, intf_id_t intf);
   fib_via_t(const fib_via_t& other);
   fib_via_t& operator=(
      fib_via_t const & other);


   ip_addr_t hop() const;
   void hop_is(ip_addr_t const & hop);

   intf_id_t intf() const;
   void intf_is(intf_id_t intf);

   mpls_label_t mpls_label() const;
   void mpls_label_is(mpls_label_t mpls_label);

   bool operator==(fib_via_t const & other) const;
   bool operator!=(fib_via_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os, const fib_via_t& obj);

 private:
   std::shared_ptr<fib_via_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const fib_via_t& obj);

enum fib_fec_type_t {
   FEC_TYPE_FORWARD,
   FEC_TYPE_DROP,
   FEC_TYPE_RECEIVE,
   FEC_TYPE_ATTACHED,
   FEC_TYPE_RECEIVE_BCAST,
   FEC_TYPE_NEXTHOP_GROUP,
   FEC_TYPE_KERNEL,
   FEC_TYPE_UNKNOWN,
};
/** Appends a string representation of enum fib_fec_type_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const fib_fec_type_t & enum_val);

class fib_fec_impl_t;
/**
 * FEC (Forwarding Equivalence Class),
 * consists of collection (one or more) vias.
 */
class EOS_SDK_PUBLIC fib_fec_t {
 public:
   fib_fec_t();
   explicit fib_fec_t(fib_fec_key_t fec_key);
   fib_fec_t(const fib_fec_t& other);
   fib_fec_t& operator=(
      fib_fec_t const & other);


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
   /** Prepend one via to the list. */
   void via_set(fib_via_t const & via);
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
   friend std::ostream& operator<<(std::ostream& os, const fib_fec_t& obj);

 private:
   std::shared_ptr<fib_fec_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const fib_fec_t& obj);
}

#endif // EOS_TYPES_FIB_H
