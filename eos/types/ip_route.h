// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_IP_ROUTE_H
#define EOS_TYPES_IP_ROUTE_H

#include <eos/eth.h>
#include <eos/hash_mix.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/mpls.h>
#include <eos/utility.h>
#include <sstream>

namespace eos {

typedef uint32_t ip_route_tag_t;
typedef uint8_t ip_route_preference_t;
typedef uint32_t ip_route_metric_t;
/** Valid range of 1 - (2^24)-1, set to 0 if unused. */
typedef uint32_t vni_t;

/**
 * The type of the ip_route_t. This is determined by the ip_route_via_t's attached
 * to this route.
 */
enum ip_route_action_t {
   IP_ROUTE_ACTION_NULL,
   IP_ROUTE_ACTION_FORWARD,
   IP_ROUTE_ACTION_DROP,
   IP_ROUTE_ACTION_NEXTHOP_GROUP,
};
/**
 * Appends a string representation of enum ip_route_action_t value to the ostream.
 */
std::ostream& operator<<(std::ostream& os, const ip_route_action_t & enum_val);

/** An IP route key, consisting of a prefix and preference. */
class EOS_SDK_PUBLIC ip_route_key_t {
 public:
   ip_route_key_t();
   explicit ip_route_key_t(ip_prefix_t const & prefix);
   ip_route_key_t(ip_prefix_t const & prefix, ip_route_preference_t preference);

   /** Getter for 'prefix': the IP v4/v6 network prefix. */
   ip_prefix_t prefix() const;
   /** Setter for 'prefix'. */
   void prefix_is(ip_prefix_t const & prefix);

   /** Getter for 'preference': a value 0..255, defaults to 1. */
   ip_route_preference_t preference() const;
   /** Setter for 'preference'. */
   void preference_is(ip_route_preference_t preference);

   bool operator==(ip_route_key_t const & other) const;
   bool operator!=(ip_route_key_t const & other) const;
   /** The hash function for type ip_route_key_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of ip_route_key_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const ip_route_key_t& obj);

 private:
   ip_prefix_t prefix_;
   ip_route_preference_t preference_;
};

/**
 * An IP v4/v6 static route.
 * "Via", or nexthops, for this route are stored separately and are associated by
 * route key.
 */
class EOS_SDK_PUBLIC ip_route_t {
 public:
   ip_route_t();
   /** Creates an IP static route for the route key. */
   explicit ip_route_t(ip_route_key_t const & key);

   /** Getter for 'key': the route's key. */
   ip_route_key_t key() const;
   /** Setter for 'key'. */
   void key_is(ip_route_key_t const & key);

   /** Getter for 'tag': a numbered tag, used for table segregation. */
   ip_route_tag_t tag() const;
   /** Setter for 'tag'. */
   void tag_is(ip_route_tag_t tag);

   bool operator==(ip_route_t const & other) const;
   bool operator!=(ip_route_t const & other) const;
   /** The hash function for type ip_route_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of ip_route_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const ip_route_t& obj);

 private:
   ip_route_key_t key_;
   ip_route_tag_t tag_;
};

/**
 * A Via describing a particular set of nexthop information. A Via can describe
 * either a nexthop group name to either forward traffic to, or drop traffic if the
 * interface is Null0.
 */
class EOS_SDK_PUBLIC ip_route_via_t {
 public:
   ip_route_via_t();
   /** Creates a route via for a route key. */
   explicit ip_route_via_t(ip_route_key_t const & route_key);

   /** Getter for 'route_key': key for the route that this via is attached to. */
   ip_route_key_t route_key() const;
   /** Setter for 'route_key'. */
   void route_key_is(ip_route_key_t const & route_key);

   /**
    * Getter for 'hop': IP v4/v6 nexthop address, or a default ip_addr_t if not
    * set.
    */
   ip_addr_t hop() const;
   /** Setter for 'hop'. */
   void hop_is(ip_addr_t const & hop);

   /**
    * Getter for 'intf': use the named interface if not a default intf_id_t. Using
    * intf Null0 installs a "drop" route for the given prefix and preference.
    */
   intf_id_t intf() const;
   /** Setter for 'intf'. */
   void intf_is(intf_id_t intf);

   /**
    * Getter for 'nexthop_group': name of the next-hop group to use. If this string
    * is non-empty, the next-hop group of the given name will be used, and both
    * "hop" and "intf" must be left to their default value otherwise we will
    * panic(). Note this is currently only supported for IPv4 routes.
    */
   std::string nexthop_group() const;
   /** Setter for 'nexthop_group'. */
   void nexthop_group_is(std::string const & nexthop_group);

   /**
    * Getter for 'mpls_label': Push this MPLS label onto packets using this route.
    */
   mpls_label_t mpls_label() const;
   /** Setter for 'mpls_label'. */
   void mpls_label_is(mpls_label_t mpls_label);

   /** Getter for 'vni': the VNI to use in the underlay tunnel vxlan header. */
   vni_t vni() const;
   /** Setter for 'vni'. */
   void vni_is(vni_t vni);

   /**
    * Getter for 'vtep_addr': IP v4 destination address for the underlay IP header.
    */
   ip_addr_t vtep_addr() const;
   /** Setter for 'vtep_addr'. */
   void vtep_addr_is(ip_addr_t vtep_addr);

   /** Getter for 'router_mac': DMAC to use in the underlay ethernet header. */
   eth_addr_t router_mac() const;
   /** Setter for 'router_mac'. */
   void router_mac_is(eth_addr_t router_mac);

   /** Getter for 'egress_vrf': VRF name in which nexthop IP address is. */
   std::string egress_vrf() const;
   /** Setter for 'egress_vrf'. */
   void egress_vrf_is(std::string const & egress_vrf);

   bool operator==(ip_route_via_t const & other) const;
   bool operator!=(ip_route_via_t const & other) const;
   /** The hash function for type ip_route_via_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of ip_route_via_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const ip_route_via_t& obj);

 private:
   ip_route_key_t route_key_;
   ip_addr_t hop_;
   intf_id_t intf_;
   std::string nexthop_group_;
   mpls_label_t mpls_label_;
   vni_t vni_;
   ip_addr_t vtep_addr_;
   eth_addr_t router_mac_;
   std::string egress_vrf_;
};
}

#include <eos/inline/types/ip_route.h>

#endif // EOS_TYPES_IP_ROUTE_H
