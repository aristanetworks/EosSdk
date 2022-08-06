// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_ACL_IMPL_H
#define EOS_TYPES_ACL_IMPL_H

#include <eos/hash_mix.h>
#include <eos/utility.h>
#include <list>
#include <memory>
#include <sstream>

namespace eos {

/**
 * A TTL specifier, used in an IP ACL rule to define TTLs to match.
 *
 * Create an instance of the classes below, such as a acl_ttl_spec_gt_t to specify
 * matching TTLs greater than the value passed.
 */
class EOS_SDK_PUBLIC acl_ttl_spec_impl_t {
 public:
   acl_ttl_spec_impl_t();
   acl_ttl_spec_impl_t(acl_range_operator_t oper, uint8_t ttl);

   /** Getter for 'oper': the type of range, note, BETWEEN is not supported. */
   acl_range_operator_t oper() const;
   /** Setter for 'oper'. */
   void oper_is(acl_range_operator_t oper);

   /** Getter for 'ttl': the type of range, note, BETWEEN is not supported. */
   uint8_t ttl() const;
   /** Setter for 'ttl'. */
   void ttl_is(uint8_t ttl);

   bool operator==(acl_ttl_spec_impl_t const & other) const;
   bool operator!=(acl_ttl_spec_impl_t const & other) const;
   bool operator<(acl_ttl_spec_impl_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os,
                                   const acl_ttl_spec_impl_t& obj);

 private:
   acl_range_operator_t oper_;
   uint8_t ttl_;
};

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
class EOS_SDK_PUBLIC acl_port_spec_impl_t {
 public:
   /** Default constructor, matches any port. */
   acl_port_spec_impl_t();
   acl_port_spec_impl_t(acl_range_operator_t oper,
                        std::list<uint16_t> const & ports);

   acl_range_operator_t oper() const;
   void oper_is(acl_range_operator_t oper);

   std::list<uint16_t> const & ports() const;
   void ports_is(std::list<uint16_t> const & ports);
   /** Prepend one port to the list. */
   void port_set(uint16_t const & ports);
   /** Remove all matching port elements. */
   void port_del(uint16_t const & ports);

   bool operator==(acl_port_spec_impl_t const & other) const;
   bool operator!=(acl_port_spec_impl_t const & other) const;
   bool operator<(acl_port_spec_impl_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os,
                                   const acl_port_spec_impl_t& obj);

 private:
   acl_range_operator_t oper_;
   std::list<uint16_t> ports_;
};


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
 * acl_base_filter_t, such as "log" to enable logging of packets matching the rule,
 * and the action applied to packets matching the rule.
 *
 * Base ACL rule class containing common fields.
 * Instead of this, instantiate one of the concrete rule classes.
 */
class EOS_SDK_PUBLIC acl_rule_base_impl_t {
 public:
 protected:
   acl_rule_base_impl_t();
   friend class acl_rule_base_t;
 public:

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
   friend std::ostream& operator<<(std::ostream& os,
                                   const acl_rule_base_impl_t& obj);

 private:
   acl_action_t action_;
   bool log_;
   bool tracked_;
};

/** An individual ACL rule for IPv4 or IPv6 ACLs. */
class EOS_SDK_PUBLIC acl_rule_ip_impl_t {
 public:
   acl_rule_ip_impl_t();

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

   ip_addr_mask_t destination_addr() const;
   void destination_addr_is(ip_addr_mask_t const & destination_addr);

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

   bool operator==(acl_rule_ip_impl_t const & other) const;
   bool operator!=(acl_rule_ip_impl_t const & other) const;
   bool operator<(acl_rule_ip_impl_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os, const acl_rule_ip_impl_t& obj);

 private:
   vlan_id_t vlan_;
   vlan_id_t vlan_mask_;
   vlan_id_t inner_vlan_;
   vlan_id_t inner_vlan_mask_;
   uint8_t ip_protocol_;
   acl_ttl_spec_t ttl_;
   ip_addr_mask_t source_addr_;
   ip_addr_mask_t destination_addr_;
   acl_port_spec_t source_port_;
   acl_port_spec_t destination_port_;
   std::string nexthop_group_;
   uint16_t tcp_flags_;
   bool established_;
   uint16_t icmp_type_;
   uint16_t icmp_code_;
   uint8_t priority_value_;
   uint8_t priority_mask_;
   bool match_fragments_;
   bool match_ip_priority_;
};

/** An Ethernet ACL, which can be applied to Ethernet, Vlan, and MLAG interfaces. */
class EOS_SDK_PUBLIC acl_rule_eth_impl_t {
 public:
   acl_rule_eth_impl_t();

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

   bool operator==(acl_rule_eth_impl_t const & other) const;
   bool operator!=(acl_rule_eth_impl_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os,
                                   const acl_rule_eth_impl_t& obj);

 private:
   vlan_id_t vlan_;
   vlan_id_t vlan_mask_;
   vlan_id_t inner_vlan_;
   vlan_id_t inner_vlan_mask_;
   eth_addr_t source_addr_;
   eth_addr_t destination_addr_;
   eth_addr_t source_mask_;
   eth_addr_t destination_mask_;
   uint32_t eth_protocol_;
};
}

#endif // EOS_TYPES_ACL_IMPL_H
