// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_FIB_H
#define EOS_TYPES_FIB_H

#include <eos/ip.h>
#include <eos/ip_route.h>
#include <eos/utility.h>
#include <sstream>

namespace eos {

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
   ROUTE_TYPE_BGP_AGGREGATE,
   ROUTE_TYPE_OSPF_AGGREGATE,
   ROUTE_TYPE_OSPF_INTRA_AREA,
   ROUTE_TYPE_OSPF_INTER_AREA,
   ROUTE_TYPE_OSPF_EXTERNAL_TYPE1,
   ROUTE_TYPE_OSPF_EXTERNAL_TYPE2,
   ROUTE_TYPE_OSPF_NSSA_EXTERNAL_TYPE1,
   ROUTE_TYPE_OSPF_NSSA_EXTERNAL_TYPE2,
   ROUTE_TYPE_IBGP,
   ROUTE_TYPE_EBGP,
   ROUTE_TYPE_ISIS,
   ROUTE_TYPE_NEXTHOP_GROUP,
};


/**
 * An IP route that goes in FIB.
 * The "fec_id" represents the fec a.k.a adjacency associated with
 * the route. Note FEC stands for Forwarding Equivalence Class.
 */
class EOS_SDK_PUBLIC fib_route_t {
 public:
   fib_route_t();
   explicit fib_route_t(ip_prefix_t const & prefix);

   /** Getter for 'prefix': IP v4/v6 network prefix. */
   ip_prefix_t prefix() const;
   /** Setter for 'prefix'. */
   void prefix_is(ip_prefix_t const & prefix);

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
   void fec_id_is(uint64_t const & fec_id);

   bool operator==(fib_route_t const & other) const;
   bool operator!=(fib_route_t const & other) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of fib_route_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const fib_route_t& obj);

 private:
   ip_prefix_t prefix_;
   ip_route_preference_t preference_;
   ip_route_metric_t metric_;
   fib_route_type_t route_type_;
   uint64_t fec_id_;
};


/** via (nexthop) information. */
class EOS_SDK_PUBLIC fib_via_t {
 public:
   fib_via_t();
   fib_via_t(ip_addr_t const & hop, intf_id_t const & intf);

   ip_addr_t hop() const;
   void hop_is(ip_addr_t const & hop);

   intf_id_t intf() const;
   void intf_is(intf_id_t const & intf);

   bool operator==(fib_via_t const & other) const;
   bool operator!=(fib_via_t const & other) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of fib_via_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const fib_via_t& obj);

 private:
   ip_addr_t hop_;
   intf_id_t intf_;
};


enum fib_fec_type_t {
   FEC_TYPE_FORWARD,
   FEC_TYPE_DROP,
   FEC_TYPE_RECEIVE,
   FEC_TYPE_ATTACHED,
   FEC_TYPE_RECEIVE_BCAST,
   FEC_TYPE_NEXTHOP_GROUP,
   FEC_TYPE_KERNEL,
};


/**
 * FEC (Forwarding Equivalence Class),
 * consists of collection (one or more) vias.
 */
class EOS_SDK_PUBLIC fib_fec_t {
 public:
   fib_fec_t();
   explicit fib_fec_t(uint64_t const & fec_id);

   /**
    * Getter for 'fec_id': fec_id[56:63] denotes the feature, 0: fib Fec, 1 :
    * resilientEcmp feature, 2: nextHopGroup feature.
    */
   uint64_t fec_id() const;
   /** Setter for 'fec_id'. */
   void fec_id_is(uint64_t const & fec_id);

   fib_fec_type_t fec_type() const;
   void fec_type_is(fib_fec_type_t fec_type);

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

   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of fib_fec_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const fib_fec_t& obj);

 private:
   uint64_t fec_id_;
   fib_fec_type_t fec_type_;
   std::forward_list<fib_via_t> via_;
};

}

#include <eos/inline/types/fib.h>

#endif // EOS_TYPES_FIB_H
