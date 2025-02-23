// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_ACL_H
#define EOS_TYPES_ACL_H

#include <eos/eth.h>
#include <eos/hash_mix.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <list>
#include <memory>
#include <sstream>

#ifdef SWIG
%ignore eos::acl_ttl_spec_t(eos::acl_ttl_spec_t &&) noexcept;
%ignore eos::acl_ttl_spec_t::operator=(eos::acl_ttl_spec_t &&) noexcept;
%ignore eos::acl_port_spec_t(eos::acl_port_spec_t &&) noexcept;
%ignore eos::acl_port_spec_t::operator=(eos::acl_port_spec_t &&) noexcept;
%ignore eos::acl_port_spec_t::ports_is(std::list<uint16_t> &&);
%ignore eos::port_set(uint16_t &&);
%ignore eos::acl_rule_base_t(eos::acl_rule_base_t &&) noexcept;
%ignore eos::acl_rule_base_t::operator=(eos::acl_rule_base_t &&) noexcept;
%ignore eos::acl_rule_ip_t(eos::acl_rule_ip_t &&) noexcept;
%ignore eos::acl_rule_ip_t::operator=(eos::acl_rule_ip_t &&) noexcept;
%ignore eos::acl_rule_ip_t::source_addr_is(eos::ip_addr_mask_t &&);
%ignore eos::acl_rule_ip_t::destination_addr_is(eos::ip_addr_mask_t &&);
%ignore eos::acl_rule_eth_t(eos::acl_rule_eth_t &&) noexcept;
%ignore eos::acl_rule_eth_t::operator=(eos::acl_rule_eth_t &&) noexcept;
#endif

namespace eos {

enum  {
   ALL_ICMP = 65535,
};

class acl_internal;

/** The ACL type, of which valid types are either IPv4, IPv6, or Ethernet. */
enum acl_type_t {
   ACL_TYPE_NULL,
   ACL_TYPE_IPV4,
   ACL_TYPE_IPV6,
   ACL_TYPE_ETH,
   ACL_TYPE_MPLS,
};
/** Appends a string representation of enum acl_type_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const acl_type_t & enum_val);

/**
 * The direction in which an ACL is applied.
 * To apply in both directions, use both operations in order.
 */
enum acl_direction_t {
   ACL_DIRECTION_NULL,
   ACL_IN,
   ACL_OUT,
};
/** Appends a string representation of enum acl_direction_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const acl_direction_t & enum_val);

/** The type of range operator for TTL and port specifications below. */
enum acl_range_operator_t {
   ACL_RANGE_NULL,
   ACL_RANGE_ANY,
   ACL_RANGE_EQ,
   ACL_RANGE_GT,
   ACL_RANGE_LT,
   ACL_RANGE_NEQ,
   ACL_RANGE_BETWEEN,
};
/**
 * Appends a string representation of enum acl_range_operator_t value to the
 * ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const acl_range_operator_t & enum_val);

/** The action to take for an individual ACL rule. */
enum acl_action_t {
   ACL_ACTION_NULL,
   ACL_PERMIT,
   ACL_DENY,
};
/** Appends a string representation of enum acl_action_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const acl_action_t & enum_val);

/** TCP flags used in IP rules to specify which TCP flags to match. */
enum acl_tcp_flag_t {
   ACL_TCP_NULL,
   ACL_TCP_FIN = 1,
   ACL_TCP_SYN = 2,
   ACL_TCP_RST = 4,
   ACL_TCP_PSH = 8,
   ACL_TCP_ACK = 16,
   ACL_TCP_URG = 32,
   ACL_TCP_ECE = 64,
   ACL_TCP_CWR = 128,
};
/** Appends a string representation of enum acl_tcp_flag_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const acl_tcp_flag_t & enum_val);

/**
 * IP traffic type to be matched. This value is parsed from the Ethernet header's
 * EtherType field.
 */
enum acl_ip_type_t {
   /**
    * Match any IP traffic. This is the default value when it is not explicitly
    * set.
    */
   ACL_IP_TYPE_ANY,
   /** Match IPv4/IPv6 over Ethernet traffic. */
   ACL_IP_TYPE_IP,
   /** Match IPv4/IPv6 over MPLS traffic. */
   ACL_IP_TYPE_MPLS,
};
/** Appends a string representation of enum acl_ip_type_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const acl_ip_type_t & enum_val);

class acl_ttl_spec_impl_t;
/**
 * A TTL specifier, used in an IP ACL rule to define TTLs to match.
 *
 * Create an instance of the classes below, such as a acl_ttl_spec_gt_t to specify
 * matching TTLs greater than the value passed.
 */
class EOS_SDK_PUBLIC acl_ttl_spec_t {
 public:
   acl_ttl_spec_t();
   acl_ttl_spec_t(acl_range_operator_t oper, uint8_t ttl);
   acl_ttl_spec_t(const acl_ttl_spec_t& other);
   acl_ttl_spec_t& operator=(
      acl_ttl_spec_t const & other);

   acl_ttl_spec_t(acl_ttl_spec_t && other) noexcept;
   acl_ttl_spec_t & operator=(acl_ttl_spec_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /** Getter for 'oper': the type of range, note, BETWEEN is not supported. */
   acl_range_operator_t oper() const;
   /** Setter for 'oper'. */
   void oper_is(acl_range_operator_t oper);

   uint8_t ttl() const;
   void ttl_is(uint8_t ttl);

   bool operator==(acl_ttl_spec_t const & other) const;
   bool operator!=(acl_ttl_spec_t const & other) const;
   bool operator<(acl_ttl_spec_t const & other) const;
   /** The hash function for type acl_ttl_spec_t. */
   uint32_t hash() const;
   /** The hash mix function for type acl_ttl_spec_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of acl_ttl_spec_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const acl_ttl_spec_t& obj);

 private:
   std::shared_ptr<acl_ttl_spec_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const acl_ttl_spec_t& obj);

class acl_port_spec_impl_t;
/**
 * A UDP or TCP port specifier.
 *
 * Pick one of either:
 * - acl_port_spec_eq_t : Matches 1-10 port numbers.
 * - acl_port_spec_neq_t : Doesn't match these 1-10 ports.
 * - acl_port_spec_lt_t : Matches ports less than the value.
 * - acl_port_spec_gt_t : Matches ports greater than the value.
 * - acl_port_spec_between_t : Matches ports between the two values.
 */
class EOS_SDK_PUBLIC acl_port_spec_t {
 public:
   /** Default constructor, matches any port. */
   acl_port_spec_t();
   acl_port_spec_t(acl_range_operator_t oper, std::list<uint16_t> const & ports);
   acl_port_spec_t(const acl_port_spec_t& other);
   acl_port_spec_t& operator=(
      acl_port_spec_t const & other);

   acl_port_spec_t(acl_port_spec_t && other) noexcept;
   acl_port_spec_t & operator=(acl_port_spec_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   acl_range_operator_t oper() const;
   void oper_is(acl_range_operator_t oper);

   std::list<uint16_t> const & ports() const;
   void ports_is(std::list<uint16_t> const & ports);
   void ports_is(std::list<uint16_t> && ports);
   /** Prepend one port to the list. */
   void port_set(uint16_t const & ports);
   /** Prepend one port to the list. */
   void port_set(uint16_t && ports);
   /** Remove all matching port elements. */
   void port_del(uint16_t const & ports);

   bool operator==(acl_port_spec_t const & other) const;
   bool operator!=(acl_port_spec_t const & other) const;
   bool operator<(acl_port_spec_t const & other) const;
   /** The hash function for type acl_port_spec_t. */
   uint32_t hash() const;
   /** The hash mix function for type acl_port_spec_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * acl_port_spec_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const acl_port_spec_t& obj);

 private:
   std::shared_ptr<acl_port_spec_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const acl_port_spec_t& obj);

EOS_SDK_PUBLIC
acl_port_spec_t get_acl_port_spec_eq(uint16_t port);

EOS_SDK_PUBLIC
acl_port_spec_t get_acl_port_spec_eq(std::list<uint16_t> const & ports);

EOS_SDK_PUBLIC
acl_port_spec_t get_acl_port_spec_neq(uint16_t port);

EOS_SDK_PUBLIC
acl_port_spec_t get_acl_port_spec_neq(std::list<uint16_t> const & ports);

EOS_SDK_PUBLIC
acl_port_spec_t get_acl_port_spec_between(uint16_t low, uint16_t high);

EOS_SDK_PUBLIC
acl_port_spec_t get_acl_port_spec_gt(uint16_t port);

EOS_SDK_PUBLIC
acl_port_spec_t get_acl_port_spec_lt(uint16_t port);

EOS_SDK_PUBLIC
acl_port_spec_t get_acl_port_spec_any();

/** An ACL key is the combination of its name and ACL type (IPv4, IPv6 or ETH). */
class EOS_SDK_PUBLIC acl_key_t {
 public:
   acl_key_t();
   acl_key_t(std::string const & acl_name, acl_type_t acl_type);

   std::string acl_name() const;

   acl_type_t acl_type() const;

   bool operator()(acl_key_t const & lhs, acl_key_t const & rhs) const;
   bool operator==(acl_key_t const & other) const;
   bool operator!=(acl_key_t const & other) const;
   /** The hash function for type acl_key_t. */
   uint32_t hash() const;
   /** The hash mix function for type acl_key_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of acl_key_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const acl_key_t& obj);

 private:
   std::string acl_name_;
   acl_type_t acl_type_;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const acl_key_t& obj);

class acl_rule_base_impl_t;
/**
 * Following are classes that represent access lists (ACLs).
 * Access lists are sequences of rules specifying per-packet rules filters apply to
 * either IPv4, IPv6 or ETH (layer 2) traffic and are attached to traffic arriving
 * (in) or leaving (out) on zero or more interfaces.
 *
 * To use ACL rules in these libraries, construct the appropriate concrete type of
 * rule you desire, either a:
 *   * acl_rule_ip_t  or a
 *   * acl_rule_eth_t
 *
 * Base parameters common to all filter types are defined on the parent
 * acl_rule_base_t, such as "log" to enable logging of packets matching the rule,
 * and the action applied to packets matching the rule.
 *
 * Base ACL rule class containing common fields.
 * Instead of this, instantiate one of the concrete rule classes.
 */
class EOS_SDK_PUBLIC acl_rule_base_t {
 public:
 protected:
   acl_rule_base_t();
 public:
   acl_rule_base_t(const acl_rule_base_t& other);
   acl_rule_base_t& operator=(
      acl_rule_base_t const & other);

   acl_rule_base_t(acl_rule_base_t && other) noexcept;
   acl_rule_base_t & operator=(acl_rule_base_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   acl_action_t action() const;
   void action_is(acl_action_t action);

   bool log() const;
   void log_is(bool log);

   bool tracked() const;
   void tracked_is(bool tracked);

   /** The hash function for type acl_rule_base_t. */
   uint32_t hash() const;
   /** The hash mix function for type acl_rule_base_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * acl_rule_base_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const acl_rule_base_t& obj);

 private:
   std::shared_ptr<acl_rule_base_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const acl_rule_base_t& obj);

class acl_rule_ip_impl_t;
/** An individual ACL rule for IPv4 or IPv6 ACLs. */
class EOS_SDK_PUBLIC acl_rule_ip_t : public acl_rule_base_t {
 public:
   acl_rule_ip_t();
   acl_rule_ip_t(const acl_rule_ip_t& other);
   acl_rule_ip_t& operator=(
      acl_rule_ip_t const & other);

   acl_rule_ip_t(acl_rule_ip_t && other) noexcept;
   acl_rule_ip_t & operator=(acl_rule_ip_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   vlan_id_t vlan() const;
   void vlan_is(vlan_id_t vlan);

   vlan_id_t vlan_mask() const;
   void vlan_mask_is(vlan_id_t vlan_mask);

   vlan_id_t inner_vlan() const;
   void inner_vlan_is(vlan_id_t inner_vlan);

   vlan_id_t inner_vlan_mask() const;
   void inner_vlan_mask_is(vlan_id_t inner_vlan_mask);

   uint8_t ip_protocol() const;
   void ip_protocol_is(uint8_t ip_protocol);

   acl_ttl_spec_t ttl() const;
   void ttl_is(acl_ttl_spec_t ttl);

   ip_addr_mask_t source_addr() const;
   void source_addr_is(ip_addr_mask_t const & source_addr);
   void source_addr_is(ip_addr_mask_t && source_addr);

   ip_addr_mask_t destination_addr() const;
   void destination_addr_is(ip_addr_mask_t const & destination_addr);
   void destination_addr_is(ip_addr_mask_t && destination_addr);

   acl_port_spec_t source_port() const;
   void source_port_is(acl_port_spec_t source_port);

   acl_port_spec_t destination_port() const;
   void destination_port_is(acl_port_spec_t destination_port);

   /** Getter for 'nexthop_group': match nexthop-group in the FIB lookup result. */
   std::string nexthop_group() const;
   /** Setter for 'nexthop_group'. */
   void nexthop_group_is(std::string nexthop_group);

   /** Getter for 'tcp_flags': bitmask of TCP flags to match, if set. */
   uint16_t tcp_flags() const;
   /** Setter for 'tcp_flags'. */
   void tcp_flags_is(uint16_t tcp_flags);

   /** Getter for 'ip_type': EtherType value in the Ethernet header. */
   acl_ip_type_t ip_type() const;
   /** Setter for 'ip_type'. */
   void ip_type_is(acl_ip_type_t ip_type);

   /** Getter for 'established': match "established" connections. */
   bool established() const;
   /** Setter for 'established'. */
   void established_is(bool established);

   /**
    * Getter for 'icmp_type': match a specific ICMP type and code, the default
    * value 0xFFFF matches all types or codes.
    */
   uint16_t icmp_type() const;
   /** Setter for 'icmp_type'. */
   void icmp_type_is(uint16_t icmp_type);

   /** Getter for 'icmp_code': match a specific ICMP type and code. */
   uint16_t icmp_code() const;
   /** Setter for 'icmp_code'. */
   void icmp_code_is(uint16_t icmp_code);

   /**
    * Getter for 'priority_value': IPv4: 0..63: DSCP value to match; IPv6: 0..255:
    * DSCP + ECN bits (traffic class byte). Warning: for IPv6 the DSCP value must
    * be shifted (ipv4_dscp<<2). Warning: for IPV4 also need to call
    * match_ip_priority. Warning: mask default is 0 (all bits are wildcarded).
    */
   uint8_t priority_value() const;
   /** Setter for 'priority_value'. */
   void priority_value_is(uint8_t priority_value);

   /**
    * Getter for 'priority_mask': 0..63 for IPv4; 0..255 for IPv6. Warning: the
    * default mask is 0: any dscp will match.
    */
   uint8_t priority_mask() const;
   /** Setter for 'priority_mask'. */
   void priority_mask_is(uint8_t priority_mask);

   /** Getter for 'match_fragments': match IP fragments. */
   bool match_fragments() const;
   /** Setter for 'match_fragments'. */
   void match_fragments_is(bool match_fragments);

   /**
    * Getter for 'match_ip_priority': IPv4: enable for priority_{value,mask} to be
    * effective; IPv6: dont care (not needed for match to happen).
    */
   bool match_ip_priority() const;
   /** Setter for 'match_ip_priority'. */
   void match_ip_priority_is(bool match_ip_priority);

   bool operator==(acl_rule_ip_t const & other) const;
   bool operator!=(acl_rule_ip_t const & other) const;
   bool operator<(acl_rule_ip_t const & other) const;
   /** The hash function for type acl_rule_ip_t. */
   uint32_t hash() const;
   /** The hash mix function for type acl_rule_ip_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of acl_rule_ip_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const acl_rule_ip_t& obj);

 private:
   std::shared_ptr<acl_rule_ip_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const acl_rule_ip_t& obj);

class acl_rule_eth_impl_t;
/** An Ethernet ACL, which can be applied to Ethernet, Vlan, and MLAG interfaces. */
class EOS_SDK_PUBLIC acl_rule_eth_t : public acl_rule_base_t {
 public:
   acl_rule_eth_t();
   acl_rule_eth_t(const acl_rule_eth_t& other);
   acl_rule_eth_t& operator=(
      acl_rule_eth_t const & other);

   acl_rule_eth_t(acl_rule_eth_t && other) noexcept;
   acl_rule_eth_t & operator=(acl_rule_eth_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   vlan_id_t vlan() const;
   void vlan_is(vlan_id_t vlan);

   vlan_id_t vlan_mask() const;
   void vlan_mask_is(vlan_id_t vlan_mask);

   vlan_id_t inner_vlan() const;
   void inner_vlan_is(vlan_id_t inner_vlan);

   vlan_id_t inner_vlan_mask() const;
   void inner_vlan_mask_is(vlan_id_t inner_vlan_mask);

   eth_addr_t source_addr() const;
   void source_addr_is(eth_addr_t source_addr);

   eth_addr_t destination_addr() const;
   void destination_addr_is(eth_addr_t destination_addr);

   eth_addr_t source_mask() const;
   void source_mask_is(eth_addr_t source_mask);

   eth_addr_t destination_mask() const;
   void destination_mask_is(eth_addr_t destination_mask);

   uint32_t eth_protocol() const;
   void eth_protocol_is(uint32_t eth_protocol);

   bool operator==(acl_rule_eth_t const & other) const;
   bool operator!=(acl_rule_eth_t const & other) const;
   /** The hash function for type acl_rule_eth_t. */
   uint32_t hash() const;
   /** The hash mix function for type acl_rule_eth_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of acl_rule_eth_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const acl_rule_eth_t& obj);

 private:
   std::shared_ptr<acl_rule_eth_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const acl_rule_eth_t& obj);
}

#endif // EOS_TYPES_ACL_H
