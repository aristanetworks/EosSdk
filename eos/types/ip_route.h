// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_IP_ROUTE_H
#define EOS_TYPES_IP_ROUTE_H

#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/mpls.h>
#include <eos/utility.h>
#include <sstream>

namespace eos {

typedef uint32_t ip_route_tag_t;
typedef uint8_t ip_route_preference_t;
typedef uint32_t ip_route_metric_t;

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

   ip_route_metric_t metric() const;
   void metric_is(ip_route_metric_t metric);

   bool operator==(ip_route_key_t const & other) const;
   bool operator!=(ip_route_key_t const & other) const;
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
   ip_route_metric_t metric_;
};

/**
 * An IP v4/v6 static route.
 * 'Via', or nexthops, for this route are stored separately and are associated by
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

   /**
    * Getter for 'persistent': indicates whether this route persists in system
    * configuration. If true, the route appears in 'show running-config', and will
    * be saved to startup-config if a 'copy running start' or 'write memory' CLI
    * command is issued.
    */
   bool persistent() const;
   /** Setter for 'persistent'. */
   void persistent_is(bool persistent);

   bool operator==(ip_route_t const & other) const;
   bool operator!=(ip_route_t const & other) const;
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
   bool persistent_;
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
   void intf_is(intf_id_t const & intf);

   /**
    * Getter for 'nexthop_group': name of the next-hop group to use. If this string
    * is non-empty, the next-hop group of the given name will be used, and both
    * "hop" and "intf" must be left to their default value otherwise we will
    * panic(). Note this is currently only supported for IPv4 routes.
    */
   std::string nexthop_group() const;
   /** Setter for 'nexthop_group'. */
   void nexthop_group_is(std::string const & nexthop_group);

   /** Getter for 'mpls_label': Push an MPLS label. */
   mpls_label_t mpls_label() const;
   /** Setter for 'mpls_label'. */
   void mpls_label_is(mpls_label_t const & mpls_label);

   bool operator==(ip_route_via_t const & other) const;
   bool operator!=(ip_route_via_t const & other) const;
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
};
}

#include <eos/inline/types/ip_route.h>

#endif // EOS_TYPES_IP_ROUTE_H
