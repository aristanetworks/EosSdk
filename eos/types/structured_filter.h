// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_STRUCTURED_FILTER_H
#define EOS_TYPES_STRUCTURED_FILTER_H

#include <eos/exception.h>
#include <eos/hash_mix.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <unordered_set>

#ifdef SWIG
%ignore eos::protocol_range_t(eos::protocol_range_t &&) noexcept;
%ignore eos::protocol_range_t::operator=(eos::protocol_range_t &&) noexcept;
%ignore eos::port_range_t(eos::port_range_t &&) noexcept;
%ignore eos::port_range_t::operator=(eos::port_range_t &&) noexcept;
%ignore eos::port_field_t(eos::port_field_t &&) noexcept;
%ignore eos::port_field_t::operator=(eos::port_field_t &&) noexcept;
%ignore eos::port_field_t::src_ports_is(std::set<eos::port_range_t> &&);
%ignore eos::src_port_set(eos::port_range_t &&);
%ignore eos::port_field_t::dst_ports_is(std::set<eos::port_range_t> &&);
%ignore eos::dst_port_set(eos::port_range_t &&);
%ignore eos::port_field_t::src_port_field_sets_is(
         std::unordered_set<std::string> &&);
%ignore eos::src_port_field_set_set(std::string &&);
%ignore eos::port_field_t::dst_port_field_sets_is(
         std::unordered_set<std::string> &&);
%ignore eos::dst_port_field_set_set(std::string &&);
%ignore eos::protocol_field_t(eos::protocol_field_t &&) noexcept;
%ignore eos::protocol_field_t::operator=(eos::protocol_field_t &&) noexcept;
%ignore eos::protocol_field_t::ports_is(std::map<uint32_t, port_field_t> &&);
%ignore eos::tp_rule_filter_t(eos::tp_rule_filter_t &&) noexcept;
%ignore eos::tp_rule_filter_t::operator=(eos::tp_rule_filter_t &&) noexcept;
%ignore eos::tp_rule_filter_t::protocols_is(
         std::map<protocol_range_t, protocol_field_t> &&);
#endif

namespace eos {

/**
 * Constant enums for traffic-policy to define the maximum values of fields
 * (protocols, l4-ports).
 */
enum tp_max_values_t {
   TP_MAX_PROTO = 255,
   TP_MAX_L4PORT = 65535,
};
/** Appends a string representation of enum tp_max_values_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const tp_max_values_t & enum_val);

class protocol_range_impl_t;
/** Range type for configuring protocol ranges of traffic-policy. */
class EOS_SDK_PUBLIC protocol_range_t {
 public:
   protocol_range_t();
   protocol_range_t(const protocol_range_t& other);
   protocol_range_t& operator=(
      protocol_range_t const & other);

   protocol_range_t(protocol_range_t && other) noexcept;
   protocol_range_t & operator=(protocol_range_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   uint32_t range_start() const;
   void range_start_is(uint32_t range_start);

   uint32_t range_end() const;
   void range_end_is(uint32_t range_end);

   bool operator==(protocol_range_t const & other) const;
   bool operator!=(protocol_range_t const & other) const;
   bool operator<(protocol_range_t const & other) const;
   /** The hash function for type protocol_range_t. */
   uint32_t hash() const;
   /** The hash mix function for type protocol_range_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * protocol_range_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const protocol_range_t& obj);

 private:
   std::shared_ptr<protocol_range_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const protocol_range_t& obj);

class port_range_impl_t;
/** Range type for configuring port ranges of traffic-policy. */
class EOS_SDK_PUBLIC port_range_t {
 public:
   port_range_t();
   port_range_t(const port_range_t& other);
   port_range_t& operator=(
      port_range_t const & other);

   port_range_t(port_range_t && other) noexcept;
   port_range_t & operator=(port_range_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   uint32_t range_start() const;
   void range_start_is(uint32_t range_start);

   uint32_t range_end() const;
   void range_end_is(uint32_t range_end);

   bool operator==(port_range_t const & other) const;
   bool operator!=(port_range_t const & other) const;
   bool operator<(port_range_t const & other) const;
   /** The hash function for type port_range_t. */
   uint32_t hash() const;
   /** The hash mix function for type port_range_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of port_range_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const port_range_t& obj);

 private:
   std::shared_ptr<port_range_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const port_range_t& obj);

class port_field_impl_t;
/** Field type used to configure the port ranges or port field-sets. */
class EOS_SDK_PUBLIC port_field_t {
 public:
   port_field_t();
   port_field_t(const port_field_t& other);
   port_field_t& operator=(
      port_field_t const & other);

   port_field_t(port_field_t && other) noexcept;
   port_field_t & operator=(port_field_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   std::set<port_range_t> const & src_ports() const;
   void src_ports_is(std::set<port_range_t> const & src_ports);
   void src_ports_is(std::set<port_range_t> && src_ports);
   /** Inserts one src_port of 'value' to the set. */
   void src_port_set(port_range_t const & value);
   /** Inserts one src_port of 'value' to the set. */
   void src_port_set(port_range_t && value);
   /** Deletes one src_port of 'value' from the set. */
   void src_port_del(port_range_t const & value);

   std::set<port_range_t> const & dst_ports() const;
   void dst_ports_is(std::set<port_range_t> const & dst_ports);
   void dst_ports_is(std::set<port_range_t> && dst_ports);
   /** Inserts one dst_port of 'value' to the set. */
   void dst_port_set(port_range_t const & value);
   /** Inserts one dst_port of 'value' to the set. */
   void dst_port_set(port_range_t && value);
   /** Deletes one dst_port of 'value' from the set. */
   void dst_port_del(port_range_t const & value);

   std::unordered_set<std::string> const & src_port_field_sets() const;
   void src_port_field_sets_is(
         std::unordered_set<std::string> const & src_port_field_sets);
   void src_port_field_sets_is(
         std::unordered_set<std::string> && src_port_field_sets);
   /** Inserts one src_port_field_set of 'value' to the set. */
   void src_port_field_set_set(std::string const & value);
   /** Inserts one src_port_field_set of 'value' to the set. */
   void src_port_field_set_set(std::string && value);
   /** Deletes one src_port_field_set of 'value' from the set. */
   void src_port_field_set_del(std::string const & value);

   std::unordered_set<std::string> const & dst_port_field_sets() const;
   void dst_port_field_sets_is(
         std::unordered_set<std::string> const & dst_port_field_sets);
   void dst_port_field_sets_is(
         std::unordered_set<std::string> && dst_port_field_sets);
   /** Inserts one dst_port_field_set of 'value' to the set. */
   void dst_port_field_set_set(std::string const & value);
   /** Inserts one dst_port_field_set of 'value' to the set. */
   void dst_port_field_set_set(std::string && value);
   /** Deletes one dst_port_field_set of 'value' from the set. */
   void dst_port_field_set_del(std::string const & value);

   bool operator==(port_field_t const & other) const;
   bool operator!=(port_field_t const & other) const;
   bool operator<(port_field_t const & other) const;
   /** The hash function for type port_field_t. */
   uint32_t hash() const;
   /** The hash mix function for type port_field_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of port_field_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const port_field_t& obj);

 private:
   std::shared_ptr<port_field_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const port_field_t& obj);

class protocol_field_impl_t;
/** Field type used to configure the protocol ranges or protocol field-sets. */
class EOS_SDK_PUBLIC protocol_field_t {
 public:
   protocol_field_t();
   protocol_field_t(const protocol_field_t& other);
   protocol_field_t& operator=(
      protocol_field_t const & other);

   protocol_field_t(protocol_field_t && other) noexcept;
   protocol_field_t & operator=(protocol_field_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /** Getter for 'ports': the key of the map ports should be an unique id. */
   std::map<uint32_t, port_field_t> const & ports() const;
   /** Setter for 'ports'. */
   void ports_is(std::map<uint32_t, port_field_t> const & ports);
   /** Moving Setter for 'ports'. */
   void ports_is(std::map<uint32_t, port_field_t> && ports);
   /** Inserts key/value pair to the map. */
   void port_set(uint32_t key, port_field_t const & value);
   /** Inserts key/value pair to the map. */
   void port_set(uint32_t key, port_field_t && value);
   /** Deletes the key/value pair from the map. */
   void port_del(uint32_t key);

   bool operator==(protocol_field_t const & other) const;
   bool operator!=(protocol_field_t const & other) const;
   bool operator<(protocol_field_t const & other) const;
   /** The hash function for type protocol_field_t. */
   uint32_t hash() const;
   /** The hash mix function for type protocol_field_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * protocol_field_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const protocol_field_t& obj);

 private:
   std::shared_ptr<protocol_field_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const protocol_field_t& obj);

/** The traffic policy rule type. Valid types are IPV4 and IPV6. */
enum traffic_policy_rule_type_t {
   TRAFFIC_POLICY_RULE_TYPE_NULL,
   TRAFFIC_POLICY_RULE_TYPE_IPV4,
   TRAFFIC_POLICY_RULE_TYPE_IPV6,
};
/**
 * Appends a string representation of enum traffic_policy_rule_type_t value to the
 * ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(
         std::ostream& os, const traffic_policy_rule_type_t & enum_val);

class tp_rule_filter_impl_t;
/**
 * This type is used to store the configs of all match fields of a traffic-policy
 * rule.
 */
class EOS_SDK_PUBLIC tp_rule_filter_t {
 public:
   tp_rule_filter_t();
   explicit tp_rule_filter_t(traffic_policy_rule_type_t filter_type);
   tp_rule_filter_t(const tp_rule_filter_t& other);
   tp_rule_filter_t& operator=(
      tp_rule_filter_t const & other);

   tp_rule_filter_t(tp_rule_filter_t && other) noexcept;
   tp_rule_filter_t & operator=(tp_rule_filter_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   std::set<ip_addr_mask_t> const & src_addrs() const;

   std::unordered_set<std::string> const & src_addr_field_sets() const;

   std::set<ip_addr_mask_t> const & dst_addrs() const;

   std::unordered_set<std::string> const & dst_addr_field_sets() const;

   std::map<protocol_range_t, protocol_field_t> const & protocols() const;
   void protocols_is(
         std::map<protocol_range_t, protocol_field_t> const & protocols);
   void protocols_is(std::map<protocol_range_t, protocol_field_t> && protocols);
   /** Inserts key/value pair to the map. */
   void protocol_set(protocol_range_t key, protocol_field_t const & value);
   /** Inserts key/value pair to the map. */
   void protocol_set(protocol_range_t key, protocol_field_t && value);
   /** Deletes the key/value pair from the map. */
   void protocol_del(protocol_range_t key);

   traffic_policy_rule_type_t filter_type() const;

   void src_addr_set(ip_addr_mask_t const & value);
   void src_addr_del(ip_addr_mask_t const & value);
   void src_addrs_is(std::set<ip_addr_mask_t> const & src_addrs);
   void dst_addr_set(ip_addr_mask_t const & value);
   void dst_addr_del(ip_addr_mask_t const & value);
   void dst_addrs_is(std::set<ip_addr_mask_t> const & dst_addrs);
   void src_addr_field_set_set(std::string const & value);
   void src_addr_field_set_del(std::string const & value);
   void src_addr_field_sets_is(
         std::unordered_set<std::string> const & src_addr_field_sets);
   void dst_addr_field_set_set(std::string const & value);
   void dst_addr_field_set_del(std::string const & value);
   void dst_addr_field_sets_is(
         std::unordered_set<std::string> const & dst_addr_field_sets);
   bool operator==(tp_rule_filter_t const & other) const;
   bool operator!=(tp_rule_filter_t const & other) const;
   bool operator<(tp_rule_filter_t const & other) const;
   /** The hash function for type tp_rule_filter_t. */
   uint32_t hash() const;
   /** The hash mix function for type tp_rule_filter_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * tp_rule_filter_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const tp_rule_filter_t& obj);

 private:
   std::shared_ptr<tp_rule_filter_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const tp_rule_filter_t& obj);
}

#endif // EOS_TYPES_STRUCTURED_FILTER_H
