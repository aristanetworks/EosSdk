// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_IP_ROUTE_H
#define EOS_TYPES_IP_ROUTE_H

#include <eos/eth.h>
#include <eos/hash_mix.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/mpls.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

#ifdef SWIG
%ignore eos::ip_route_key_t(eos::ip_route_key_t &&) noexcept;
%ignore eos::ip_route_key_t::operator=(eos::ip_route_key_t &&) noexcept;
%ignore eos::ip_route_key_t::prefix_is(eos::ip_prefix_t &&);
%ignore eos::ip_route_t(eos::ip_route_t &&) noexcept;
%ignore eos::ip_route_t::operator=(eos::ip_route_t &&) noexcept;
%ignore eos::ip_route_t::key_is(eos::ip_route_key_t &&);
%ignore eos::ip_route_t::command_tag_is(std::string &&);
%ignore eos::ip_route_via_t(eos::ip_route_via_t &&) noexcept;
%ignore eos::ip_route_via_t::operator=(eos::ip_route_via_t &&) noexcept;
%ignore eos::ip_route_via_t::route_key_is(eos::ip_route_key_t &&);
%ignore eos::ip_route_via_t::hop_is(eos::ip_addr_t &&);
%ignore eos::ip_route_via_t::nexthop_group_is(std::string &&);
%ignore eos::ip_route_via_t::egress_vrf_is(std::string &&);
#endif

namespace eos {

typedef uint32_t ip_route_tag_t;
typedef uint8_t ip_route_preference_t;
typedef uint32_t ip_route_metric_t;
/** Valid range of 1 - (2^24)-1, set to 0 if unused. */
typedef uint32_t vni_t;
typedef uint32_t ip_via_metric_t;
/** Valid range of 1 - (2^24)-1, set to 0 if unused. */
typedef uint32_t ip_via_weight_t;

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
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const ip_route_action_t & enum_val);

class ip_route_key_impl_t;
/** An IP route key, consisting of a prefix and preference. */
class EOS_SDK_PUBLIC ip_route_key_t {
 public:
   ip_route_key_t();
   explicit ip_route_key_t(ip_prefix_t const & prefix);
   ip_route_key_t(ip_prefix_t const & prefix, ip_route_preference_t preference);
   ip_route_key_t(const ip_route_key_t& other);
   ip_route_key_t& operator=(
      ip_route_key_t const & other);

   ip_route_key_t(ip_route_key_t && other) noexcept;
   ip_route_key_t & operator=(ip_route_key_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /** Getter for 'prefix': the IP v4/v6 network prefix. */
   ip_prefix_t prefix() const;
   /** Setter for 'prefix'. */
   void prefix_is(ip_prefix_t const & prefix);
   /** Moving Setter for 'prefix'. */
   void prefix_is(ip_prefix_t && prefix);

   /** Getter for 'preference': a value 0..255, defaults to 1. */
   ip_route_preference_t preference() const;
   /** Setter for 'preference'. */
   void preference_is(ip_route_preference_t preference);

   /** The address family of the route_key_t prefix. */
   af_t af() const;
   bool operator==(ip_route_key_t const & other) const;
   bool operator!=(ip_route_key_t const & other) const;
   /** The hash function for type ip_route_key_t. */
   uint32_t hash() const;
   /** The hash mix function for type ip_route_key_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of ip_route_key_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const ip_route_key_t& obj);

 private:
   std::shared_ptr<ip_route_key_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const ip_route_key_t& obj);

class ip_route_impl_t;
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
   ip_route_t(const ip_route_t& other);
   ip_route_t& operator=(
      ip_route_t const & other);

   ip_route_t(ip_route_t && other) noexcept;
   ip_route_t & operator=(ip_route_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /** Getter for 'key': the route's key. */
   ip_route_key_t key() const;
   /** Setter for 'key'. */
   void key_is(ip_route_key_t const & key);
   /** Moving Setter for 'key'. */
   void key_is(ip_route_key_t && key);

   /** Getter for 'tag': a numbered tag, used for table segregation. */
   ip_route_tag_t tag() const;
   /** Setter for 'tag'. */
   void tag_is(ip_route_tag_t tag);

   /**
    * Getter for 'rib_bypass': Enables EVPN routes to bypass IpRib and be handled
    * by RouteCache instead.
    */
   bool rib_bypass() const;
   /** Setter for 'rib_bypass'. */
   void rib_bypass_is(bool rib_bypass);

   /**
    * Getter for 'command_tag': Associates the route with a command_tag, which
    * might be used to manipulate configuration externally to the agent.
    */
   std::string command_tag() const;
   /** Setter for 'command_tag'. */
   void command_tag_is(std::string const & command_tag);
   /** Moving Setter for 'command_tag'. */
   void command_tag_is(std::string && command_tag);

   /** The address family of the route_key_t prefix. */
   af_t af() const;
   bool operator==(ip_route_t const & other) const;
   bool operator!=(ip_route_t const & other) const;
   /** The hash function for type ip_route_t. */
   uint32_t hash() const;
   /** The hash mix function for type ip_route_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of ip_route_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const ip_route_t& obj);

 private:
   std::shared_ptr<ip_route_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const ip_route_t& obj);

class ip_route_via_impl_t;
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
   ip_route_via_t(const ip_route_via_t& other);
   ip_route_via_t& operator=(
      ip_route_via_t const & other);

   ip_route_via_t(ip_route_via_t && other) noexcept;
   ip_route_via_t & operator=(ip_route_via_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /** Getter for 'route_key': key for the route that this via is attached to. */
   ip_route_key_t route_key() const;
   /** Setter for 'route_key'. */
   void route_key_is(ip_route_key_t const & route_key);
   /** Moving Setter for 'route_key'. */
   void route_key_is(ip_route_key_t && route_key);

   /**
    * Getter for 'hop': IP v4/v6 nexthop address, or a default ip_addr_t if not
    * set.
    */
   ip_addr_t hop() const;
   /** Setter for 'hop'. */
   void hop_is(ip_addr_t const & hop);
   /** Moving Setter for 'hop'. */
   void hop_is(ip_addr_t && hop);

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
   /** Moving Setter for 'nexthop_group'. */
   void nexthop_group_is(std::string && nexthop_group);

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
   /** Moving Setter for 'egress_vrf'. */
   void egress_vrf_is(std::string && egress_vrf);

   /** Getter for 'metric': metric for the via. */
   ip_via_metric_t metric() const;
   /** Setter for 'metric'. */
   void metric_is(ip_via_metric_t metric);

   /** Getter for 'vxlan_intf': VXLAN source interface. */
   intf_id_t vxlan_intf() const;
   /** Setter for 'vxlan_intf'. */
   void vxlan_intf_is(intf_id_t vxlan_intf);

   /** Getter for 'vtep_sip_validation': Enables VTEP SIP validation for this via. */
   bool vtep_sip_validation() const;
   /** Setter for 'vtep_sip_validation'. */
   void vtep_sip_validation_is(bool vtep_sip_validation);

   /** Getter for 'weight': the weight for this via. */
   ip_via_weight_t weight() const;
   /** Setter for 'weight'. */
   void weight_is(ip_via_weight_t weight);

   bool operator==(ip_route_via_t const & other) const;
   bool operator!=(ip_route_via_t const & other) const;
   /** The hash function for type ip_route_via_t. */
   uint32_t hash() const;
   /** The hash mix function for type ip_route_via_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of ip_route_via_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const ip_route_via_t& obj);

 private:
   std::shared_ptr<ip_route_via_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const ip_route_via_t& obj);
}

#endif // EOS_TYPES_IP_ROUTE_H
