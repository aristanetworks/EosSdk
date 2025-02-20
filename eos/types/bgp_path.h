// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_BGP_PATH_H
#define EOS_TYPES_BGP_PATH_H

#include <eos/hash_mix.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>
#include <unordered_set>

#ifdef SWIG
%ignore eos::bgp_path_attr_fields_t(eos::bgp_path_attr_fields_t &&) noexcept;
%ignore eos::bgp_path_attr_fields_t::operator=(eos::bgp_path_attr_fields_t &&)
   noexcept;
%ignore eos::bgp_path_options_t(eos::bgp_path_options_t &&) noexcept;
%ignore eos::bgp_path_options_t::operator=(eos::bgp_path_options_t &&) noexcept;
%ignore eos::bgp_path_options_t::path_attr_fields_is(
         eos::bgp_path_attr_fields_t &&);
%ignore eos::bgp_path_attr_t(eos::bgp_path_attr_t &&) noexcept;
%ignore eos::bgp_path_attr_t::operator=(eos::bgp_path_attr_t &&) noexcept;
%ignore eos::bgp_path_attr_t::next_hop_is(eos::ip_addr_t &&);
%ignore eos::bgp_path_attr_t::community_list_is(std::unordered_set<uint32_t> &&);
%ignore eos::community_list_set(uint32_t &&);
%ignore eos::bgp_path_key_t(eos::bgp_path_key_t &&) noexcept;
%ignore eos::bgp_path_key_t::operator=(eos::bgp_path_key_t &&) noexcept;
%ignore eos::bgp_path_key_t::prefix_is(eos::ip_prefix_t &&);
%ignore eos::bgp_path_key_t::peer_addr_is(eos::ip_addr_t &&);
%ignore eos::bgp_path_key_t::vrf_name_is(std::string &&);
%ignore eos::bgp_path_t(eos::bgp_path_t &&) noexcept;
%ignore eos::bgp_path_t::operator=(eos::bgp_path_t &&) noexcept;
%ignore eos::bgp_path_t::path_key_is(eos::bgp_path_key_t &&);
%ignore eos::bgp_path_t::path_attr_is(eos::bgp_path_attr_t &&);
#endif

namespace eos {

/** BGP Address Family Identifiers and Subsequent Address Family Identifiers. */
enum bgp_afi_safi_t {
   BGP_IPV4_UNICAST,
   BGP_IPV6_UNICAST,
};
/** Appends a string representation of enum bgp_afi_safi_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const bgp_afi_safi_t & enum_val);

/** The BGP path stage before/after the inbound policies are applied on the route. */
enum bgp_receive_route_stage_t {
   BGP_PATH_PRE_POLICY,
   BGP_PATH_POST_POLICY,
};
/**
 * Appends a string representation of enum bgp_receive_route_stage_t value to the
 * ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const bgp_receive_route_stage_t & enum_val);

class bgp_path_attr_fields_impl_t;
/** The BGP path option to enable lookup of additional path attributes fields. */
class EOS_SDK_PUBLIC bgp_path_attr_fields_t {
 public:
   bgp_path_attr_fields_t();
   /** Create BGP path attribute field options. */
   explicit bgp_path_attr_fields_t(bool next_hop);
   bgp_path_attr_fields_t(const bgp_path_attr_fields_t& other);
   bgp_path_attr_fields_t& operator=(
      bgp_path_attr_fields_t const & other);

   bgp_path_attr_fields_t(bgp_path_attr_fields_t && other) noexcept;
   bgp_path_attr_fields_t & operator=(bgp_path_attr_fields_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

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
   /** The hash mix function for type bgp_path_attr_fields_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * bgp_path_attr_fields_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const bgp_path_attr_fields_t& obj);

 private:
   std::shared_ptr<bgp_path_attr_fields_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const bgp_path_attr_fields_t& obj);

class bgp_path_options_impl_t;
/** The BGP path lookup options. */
class EOS_SDK_PUBLIC bgp_path_options_t {
 public:
   bgp_path_options_t();
   /** Create BGP path options. */
   explicit bgp_path_options_t(bgp_receive_route_stage_t receive_route_stage);
   bgp_path_options_t(const bgp_path_options_t& other);
   bgp_path_options_t& operator=(
      bgp_path_options_t const & other);

   bgp_path_options_t(bgp_path_options_t && other) noexcept;
   bgp_path_options_t & operator=(bgp_path_options_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

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
   /** Moving Setter for 'path_attr_fields'. */
   void path_attr_fields_is(bgp_path_attr_fields_t && path_attr_fields);

   bool operator==(bgp_path_options_t const & other) const;
   bool operator!=(bgp_path_options_t const & other) const;
   /** The hash function for type bgp_path_options_t. */
   uint32_t hash() const;
   /** The hash mix function for type bgp_path_options_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * bgp_path_options_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const bgp_path_options_t& obj);

 private:
   std::shared_ptr<bgp_path_options_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const bgp_path_options_t& obj);

class bgp_path_attr_impl_t;
/** The BGP path attribute entry. */
class EOS_SDK_PUBLIC bgp_path_attr_t {
 public:
   bgp_path_attr_t();
   explicit bgp_path_attr_t(uint8_t origin, uint32_t med, uint32_t local_pref);
   bgp_path_attr_t(const bgp_path_attr_t& other);
   bgp_path_attr_t& operator=(
      bgp_path_attr_t const & other);

   bgp_path_attr_t(bgp_path_attr_t && other) noexcept;
   bgp_path_attr_t & operator=(bgp_path_attr_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /** Getter for 'next_hop': The nexthop address for the route. */
   ip_addr_t next_hop() const;
   /** Setter for 'next_hop'. */
   void next_hop_is(ip_addr_t const & next_hop);
   /** Moving Setter for 'next_hop'. */
   void next_hop_is(ip_addr_t && next_hop);

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
   /** Moving Setter for 'community_list'. */
   void community_list_is(std::unordered_set<uint32_t> && community_list);
   /** Inserts one community_list of 'value' to the set. */
   void community_list_set(uint32_t const & value);
   /** Inserts one community_list of 'value' to the set. */
   void community_list_set(uint32_t && value);
   /** Deletes one community_list of 'value' from the set. */
   void community_list_del(uint32_t const & value);

   bool operator==(bgp_path_attr_t const & other) const;
   bool operator!=(bgp_path_attr_t const & other) const;
   /** The hash function for type bgp_path_attr_t. */
   uint32_t hash() const;
   /** The hash mix function for type bgp_path_attr_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * bgp_path_attr_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const bgp_path_attr_t& obj);

 private:
   std::shared_ptr<bgp_path_attr_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const bgp_path_attr_t& obj);

class bgp_path_key_impl_t;
/** The key which uniquely identifies a BGP path. Supports IPV4/IPV6 Unicast. */
class EOS_SDK_PUBLIC bgp_path_key_t {
 public:
   bgp_path_key_t();
   /** Create BGP path key. */
   explicit bgp_path_key_t(ip_prefix_t const & prefix, ip_addr_t const & peer_addr,
                           std::string const & vrf_name);
   bgp_path_key_t(const bgp_path_key_t& other);
   bgp_path_key_t& operator=(
      bgp_path_key_t const & other);

   bgp_path_key_t(bgp_path_key_t && other) noexcept;
   bgp_path_key_t & operator=(bgp_path_key_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /** Getter for 'prefix': IPv4/IPv6 network prefix. */
   ip_prefix_t prefix() const;
   /** Setter for 'prefix'. */
   void prefix_is(ip_prefix_t const & prefix);
   /** Moving Setter for 'prefix'. */
   void prefix_is(ip_prefix_t && prefix);

   /** Getter for 'peer_addr': BGP peer address. */
   ip_addr_t peer_addr() const;
   /** Setter for 'peer_addr'. */
   void peer_addr_is(ip_addr_t const & peer_addr);
   /** Moving Setter for 'peer_addr'. */
   void peer_addr_is(ip_addr_t && peer_addr);

   /** Getter for 'vrf_name': VRF name. */
   std::string vrf_name() const;
   /** Setter for 'vrf_name'. */
   void vrf_name_is(std::string const & vrf_name);
   /** Moving Setter for 'vrf_name'. */
   void vrf_name_is(std::string && vrf_name);

   bool operator==(bgp_path_key_t const & other) const;
   bool operator!=(bgp_path_key_t const & other) const;
   bool operator<(bgp_path_key_t const & other) const;
   /** The hash function for type bgp_path_key_t. */
   uint32_t hash() const;
   /** The hash mix function for type bgp_path_key_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of bgp_path_key_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const bgp_path_key_t& obj);

 private:
   std::shared_ptr<bgp_path_key_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const bgp_path_key_t& obj);

class bgp_path_impl_t;
/** The BGP path entry. */
class EOS_SDK_PUBLIC bgp_path_t {
 public:
   bgp_path_t();
   explicit bgp_path_t(bgp_path_key_t const & path_key);
   bgp_path_t(const bgp_path_t& other);
   bgp_path_t& operator=(
      bgp_path_t const & other);

   bgp_path_t(bgp_path_t && other) noexcept;
   bgp_path_t & operator=(bgp_path_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /** Getter for 'path_key': The BGP path key. */
   bgp_path_key_t path_key() const;
   /** Setter for 'path_key'. */
   void path_key_is(bgp_path_key_t const & path_key);
   /** Moving Setter for 'path_key'. */
   void path_key_is(bgp_path_key_t && path_key);

   /** Getter for 'path_attr': The BGP path attributes. */
   bgp_path_attr_t path_attr() const;
   /** Setter for 'path_attr'. */
   void path_attr_is(bgp_path_attr_t const & path_attr);
   /** Moving Setter for 'path_attr'. */
   void path_attr_is(bgp_path_attr_t && path_attr);

   bool operator==(bgp_path_t const & other) const;
   bool operator!=(bgp_path_t const & other) const;
   /** The hash function for type bgp_path_t. */
   uint32_t hash() const;
   /** The hash mix function for type bgp_path_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of bgp_path_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const bgp_path_t& obj);

 private:
   std::shared_ptr<bgp_path_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const bgp_path_t& obj);
}

#endif // EOS_TYPES_BGP_PATH_H
