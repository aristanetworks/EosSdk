// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_NEXTHOP_GROUP_TUNNEL_H
#define EOS_TYPES_NEXTHOP_GROUP_TUNNEL_H

#include <eos/hash_mix.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

class nexthop_group_tunnel_impl_t;
/**
 * An IP nexthop group tunnel.
 *
 * An IP nexthop group tunnel represents a tunnel
 * over a nexthop-group.
 */
class EOS_SDK_PUBLIC nexthop_group_tunnel_t {
 public:
   /** Default constructor. */
   nexthop_group_tunnel_t();
   /**
    * Creates an ip nexthop group tunnel for a given
    * tunnel endpoint prefix and nexthop-group.
    */
   explicit nexthop_group_tunnel_t(ip_prefix_t const & tunnel_endpoint,
                                   std::string const & nhg_name);
   nexthop_group_tunnel_t(const nexthop_group_tunnel_t& other);
   nexthop_group_tunnel_t& operator=(
      nexthop_group_tunnel_t const & other);


   /** Getter for 'tunnel_endpoint': IP v4/v6 prefix. */
   ip_prefix_t tunnel_endpoint() const;
   /** Setter for 'tunnel_endpoint'. */
   void tunnel_endpoint_is(ip_prefix_t const & tunnel_endpoint);

   /** Getter for 'nhg_name': nexthop group name. */
   std::string nhg_name() const;
   /** Setter for 'nhg_name'. */
   void nhg_name_is(std::string const & nhg_name);

   /** Getter for 'igp_pref': the IGP preference of the tunnel endpoint. */
   uint8_t igp_pref() const;
   /** Setter for 'igp_pref'. */
   void igp_pref_is(uint8_t igp_pref);

   /** Getter for 'igp_metric': the IGP metric of the tunnel endpoint. */
   uint32_t igp_metric() const;
   /** Setter for 'igp_metric'. */
   void igp_metric_is(uint32_t igp_metric);

   bool operator==(nexthop_group_tunnel_t const & other) const;
   bool operator!=(nexthop_group_tunnel_t const & other) const;
   /** The hash function for type nexthop_group_tunnel_t. */
   uint32_t hash() const;
   /** The hash mix function for type nexthop_group_tunnel_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * nexthop_group_tunnel_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const nexthop_group_tunnel_t& obj);

 private:
   std::shared_ptr<nexthop_group_tunnel_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const nexthop_group_tunnel_t& obj);
}

#endif // EOS_TYPES_NEXTHOP_GROUP_TUNNEL_H
