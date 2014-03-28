// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_FIB_H
#define EOS_FIB_H

#include <forward_list>
#include <eos/base.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/ip_route.h>
#include <eos/iterator.h>

namespace eos {

enum fib_route_type_t {
   ROUTE_TYPE_INVALID,
   // Host Routes
   ROUTE_TYPE_RECEIVE,
   ROUTE_TYPE_RECEIVE_BCAST,
   ROUTE_TYPE_ATTACHED,
   // unknown routing protocol
   ROUTE_TYPE_UNKNOWN,
   // FIB Routes
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
 * ip route that goes in FIB
 * fec_id represents the fec a.k.a adjacency associated with the route
 * FEC stands for Forwarding Equivalence Class.
 */
class EOS_SDK_PUBLIC fib_route_t {
 public:
   fib_route_t();
   explicit fib_route_t(ip_prefix_t const &);

   bool operator==(fib_route_t const & other) const;

   ip_prefix_t prefix() const;
   void prefix_is(ip_prefix_t const &);

   ip_route_preference_t preference() const;
   void preference_is(ip_route_preference_t);

   ip_route_metric_t metric() const;
   void metric_is(ip_route_metric_t);

   fib_route_type_t route_type() const;
   void route_type_is(fib_route_type_t);

   uint64_t fec_id() const;
   void fec_id_is(uint64_t const &);

 private:
   // IP v4/v6 network prefix
   ip_prefix_t prefix_;
   // 0..255 only, defaults to 1
   ip_route_preference_t preference_;
   ip_route_metric_t metric_;
   fib_route_type_t route_type_;
   // id that links prefix to the fec a.k.a Adjacency.
   uint64_t fec_id_;
};

/// via (nexthop) information
class EOS_SDK_PUBLIC fib_via_t {
 public:
   fib_via_t();
   fib_via_t(ip_addr_t const &, intf_id_t const &);

   bool operator==(fib_via_t const & other) const;

   ip_addr_t hop() const;
   void hop_is(ip_addr_t const &);

   intf_id_t intf() const;
   void intf_is(intf_id_t const &);

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
 * FEC (Forwarding Equivalence Class)
 * consists of collection (one or more) vias.
 */
class EOS_SDK_PUBLIC fib_fec_t {
 public:
   fib_fec_t();
   explicit fib_fec_t(uint64_t const &);

   uint64_t fec_id() const;
   void fec_id_is(uint64_t const &);

   fib_fec_type_t fec_type();
   void fec_type_is(fib_fec_type_t);

   // Returns a reference to the current via list
   std::forward_list<fib_via_t> via() const;
   void via_is(std::forward_list<fib_via_t> const &);
   // Add/Remove single via from the list
   void via_set(fib_via_t const &);
   void via_del(fib_via_t const &);

 private:
   // fec_id_[56:63] denotes the feature
   // 0 : fib Fec
   // 1 : resilientEcmp feature
   // 2 : nextHopGroup feature
   uint64_t fec_id_;
   fib_fec_type_t fec_type_;
   // Using list instead of set as list allows duplicates
   // This will help to supported weighted vias.
   std::forward_list<fib_via_t> via_;
};


class fib_route_iter_impl;

class EOS_SDK_PUBLIC fib_route_iter_t {
   // Uncomment when Iterator is defined.
   // : public iter_base<fib_route_t, fib_route_iter_impl> {

 private:
   friend class fib_route_iter_impl;
   explicit fib_route_iter_t(fib_route_iter_impl * const) EOS_SDK_PRIVATE;
};

class fib_fec_iter_impl;

class EOS_SDK_PUBLIC fib_fec_iter_t {
   // Uncomment when Iterator is defined.
   //: public iter_base<fib_fec_t, fib_fec_iter_impl> {

 private:
   friend class fib_fec_iter_impl;
   explicit fib_fec_iter_t(fib_fec_iter_impl * const) EOS_SDK_PRIVATE;
};



/// The FIB Manager
class EOS_SDK_PUBLIC fib_mgr {
 public:

   // Iterators
   fib_route_iter_t fib_route_iter() const;
   fib_fec_iter_t fib_fec_iter() const;

   // FEC management
   bool fib_fec_set(fib_fec_t const &);
   void fib_fec_del(uint64_t const &);
   bool fib_fec_exists(uint64_t const &);
   fib_fec_t fib_fec(uint64_t const &);

   // Route Management
   bool fib_route_set(fib_route_t const &);
   void fib_route_del(ip_prefix_t const &);
   bool fib_route_exists(ip_prefix_t const &);
   fib_route_t fib_route(ip_prefix_t const &);

 protected:
   fib_mgr() EOS_SDK_PRIVATE;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(fib_mgr);
};

fib_mgr * get_fib_mgr() EOS_SDK_PUBLIC;

#include <eos/inline/fib.h>

} // end namespace eos

#endif // EOS_FIB_H

