// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_BGP_PATH_H
#define EOS_TYPES_BGP_PATH_H

#include <eos/hash_mix.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <sstream>
#include <unordered_set>

namespace eos {

/** The BGP path stage before/after the inbound policies are applied on the route. */
enum bgp_receive_route_stage_t {
   BGP_PATH_PRE_POLICY,
   BGP_PATH_POST_POLICY,
};
/**
 * Appends a string representation of enum bgp_receive_route_stage_t value to the
 * ostream.
 */
std::ostream& operator<<(std::ostream& os,
                         const bgp_receive_route_stage_t & enum_val);

/** The BGP path option to enable lookup of additional path attributes fields. */
class EOS_SDK_PUBLIC bgp_path_attr_fields_t {
 public:
   bgp_path_attr_fields_t();
   /** Create BGP path attribute field options. */
   explicit bgp_path_attr_fields_t(bool next_hop);

   /**
    * Getter for 'next_hop': true if these path attribute options enable next hop
    * lookup, false otherwise.
    */
   bool next_hop() const;
   /** Setter for 'next_hop'. */
   void next_hop_is(bool next_hop);

   /**
    * Getter for 'community_list': true if these path attribute options enable
    * community list lookup, false otherwise.
    */
   bool community_list() const;
   /** Setter for 'community_list'. */
   void community_list_is(bool community_list);

   bool operator==(bgp_path_attr_fields_t const & other) const;
   bool operator!=(bgp_path_attr_fields_t const & other) const;
   /** The hash function for type bgp_path_attr_fields_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * bgp_path_attr_fields_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const bgp_path_attr_fields_t& obj);

 private:
   bool next_hop_;
   bool community_list_;
};

/** The BGP path lookup options. */
class EOS_SDK_PUBLIC bgp_path_options_t {
 public:
   bgp_path_options_t();
   /** Create BGP path options. */
   explicit bgp_path_options_t(bgp_receive_route_stage_t receive_route_stage);

   /**
    * Getter for 'receive_route_stage': The received routes stage of a path to
    * lookup when retrieving the path entry.
    */
   bgp_receive_route_stage_t receive_route_stage() const;
   /** Setter for 'receive_route_stage'. */
   void receive_route_stage_is(bgp_receive_route_stage_t receive_route_stage);

   /**
    * Getter for 'path_attr_fields': The additional path attributes to populate
    * when retrieving the path entry.
    */
   bgp_path_attr_fields_t path_attr_fields() const;
   /** Setter for 'path_attr_fields'. */
   void path_attr_fields_is(bgp_path_attr_fields_t const & path_attr_fields);

   bool operator==(bgp_path_options_t const & other) const;
   bool operator!=(bgp_path_options_t const & other) const;
   /** The hash function for type bgp_path_options_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * bgp_path_options_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const bgp_path_options_t& obj);

 private:
   bgp_receive_route_stage_t receive_route_stage_;
   bgp_path_attr_fields_t path_attr_fields_;
};

/** The BGP path attribute entry. */
class EOS_SDK_PUBLIC bgp_path_attr_t {
 public:
   bgp_path_attr_t();
   explicit bgp_path_attr_t(uint8_t origin, uint32_t med, uint32_t local_pref);

   /** Getter for 'next_hop': The nexthop address for the route. */
   ip_addr_t next_hop() const;
   /** Setter for 'next_hop'. */
   void next_hop_is(ip_addr_t const & next_hop);

   /** Getter for 'origin': The route origin. */
   uint8_t origin() const;
   /** Setter for 'origin'. */
   void origin_is(uint8_t origin);

   /** Getter for 'med': The Multi Exit Discriminator for the route. */
   uint32_t med() const;
   /** Setter for 'med'. */
   void med_is(uint32_t med);

   /** Getter for 'local_pref': The I-BGP Local preference indicator. */
   uint32_t local_pref() const;
   /** Setter for 'local_pref'. */
   void local_pref_is(uint32_t local_pref);

   /** Getter for 'community_list': The route community list. */
   std::unordered_set<uint32_t> const & community_list() const;
   /** Setter for 'community_list'. */
   void community_list_is(std::unordered_set<uint32_t> const & community_list);
   /** Inserts one community_list of 'value' to the set. */
   void community_list_set(uint32_t const & value);
   /** Deletes one community_list of 'value' from the set. */
   void community_list_del(uint32_t const & value);

   bool operator==(bgp_path_attr_t const & other) const;
   bool operator!=(bgp_path_attr_t const & other) const;
   /** The hash function for type bgp_path_attr_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * bgp_path_attr_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const bgp_path_attr_t& obj);

 private:
   ip_addr_t next_hop_;
   uint8_t origin_;
   uint32_t med_;
   uint32_t local_pref_;
   std::unordered_set<uint32_t> community_list_;
};

/** The key which uniquely identifies a BGP path. Supports IPV4/IPV6 Unicast. */
class EOS_SDK_PUBLIC bgp_path_key_t {
 public:
   bgp_path_key_t();
   /** Create BGP path key. */
   explicit bgp_path_key_t(ip_prefix_t const & prefix, ip_addr_t const & peer_addr,
                           std::string const & vrf_name);

   /** Getter for 'prefix': IPv4/IPv6 network prefix. */
   ip_prefix_t prefix() const;
   /** Setter for 'prefix'. */
   void prefix_is(ip_prefix_t const & prefix);

   /** Getter for 'peer_addr': BGP peer address. */
   ip_addr_t peer_addr() const;
   /** Setter for 'peer_addr'. */
   void peer_addr_is(ip_addr_t const & peer_addr);

   /** Getter for 'vrf_name': VRF name. */
   std::string vrf_name() const;
   /** Setter for 'vrf_name'. */
   void vrf_name_is(std::string const & vrf_name);

   bool operator==(bgp_path_key_t const & other) const;
   bool operator!=(bgp_path_key_t const & other) const;
   /** The hash function for type bgp_path_key_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of bgp_path_key_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const bgp_path_key_t& obj);

 private:
   ip_prefix_t prefix_;
   ip_addr_t peer_addr_;
   std::string vrf_name_;
};

/** The BGP path entry. */
class EOS_SDK_PUBLIC bgp_path_t {
 public:
   bgp_path_t();
   explicit bgp_path_t(bgp_path_key_t const & path_key);

   /** Getter for 'path_key': The BGP path key. */
   bgp_path_key_t path_key() const;
   /** Setter for 'path_key'. */
   void path_key_is(bgp_path_key_t const & path_key);

   /** Getter for 'path_attr': The BGP path attributes. */
   bgp_path_attr_t path_attr() const;
   /** Setter for 'path_attr'. */
   void path_attr_is(bgp_path_attr_t const & path_attr);

   bool operator==(bgp_path_t const & other) const;
   bool operator!=(bgp_path_t const & other) const;
   /** The hash function for type bgp_path_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of bgp_path_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const bgp_path_t& obj);

 private:
   bgp_path_key_t path_key_;
   bgp_path_attr_t path_attr_;
};
}

#include <eos/inline/types/bgp_path.h>

#endif // EOS_TYPES_BGP_PATH_H
