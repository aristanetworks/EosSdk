// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_NEXTHOP_GROUP_H
#define EOS_TYPES_NEXTHOP_GROUP_H

#include <eos/hash_mix.h>
#include <eos/panic.h>
#include <eos/utility.h>
#include <forward_list>
#include <map>
#include <sstream>

namespace eos {

/**
 * The type of encapsulation to use for this nexthop group.
 *
 * Each tunnel encapsulation type for Nexthop Groups
 * causes a variety of packet headers for packets using the group to
 * be changed to appropriately encapsulate the frame. IP type has no encapsulation.
 */
enum nexthop_group_encap_t {
   NEXTHOP_GROUP_TYPE_NULL,
   /** IP in IP encapsulation. */
   NEXTHOP_GROUP_IP_IN_IP,
   /** GRE encapsulation. */
   NEXTHOP_GROUP_GRE,
   /** MPLS encapsulation. */
   NEXTHOP_GROUP_MPLS,
   /** MPLS over GRE encapsulation. */
   NEXTHOP_GROUP_MPLS_OVER_GRE,
   /** IP no encapsulation. */
   NEXTHOP_GROUP_IP,
};
/**
 * Appends a string representation of enum nexthop_group_encap_t value to the
 * ostream.
 */
std::ostream& operator<<(std::ostream& os, const nexthop_group_encap_t & enum_val);

/** How the GRE tunnel key is set for GRE nexthop groups. */
enum nexthop_group_gre_key_t {
   /** Default value; do not set the GRE tunnel key. */
   NEXTHOP_GROUP_GRE_KEY_NULL,
   /**
    * Use the ingress interface as the tunnel key.
    * Not supported in this release.
    */
   NEXTHOP_GROUP_GRE_KEY_INGRESS_INTF,
};
/**
 * Appends a string representation of enum nexthop_group_gre_key_t value to the
 * ostream.
 */
std::ostream& operator<<(std::ostream& os,
                         const nexthop_group_gre_key_t & enum_val);

/**
 * An MPLS nexthop group switching operation.
 *
 * This structure combines a stack of labels and an MPLS switching operation using
 * those labels, such as eos::MPLS_ACTION_PUSH.
 */
class EOS_SDK_PUBLIC nexthop_group_mpls_action_t {
 public:
   /** Default constructor. */
   nexthop_group_mpls_action_t();
   /** Constructs an MPLS action with a specific switching operation. */
   explicit nexthop_group_mpls_action_t(mpls_action_t action_type);
   /** Constructs a populated MPLS label stack for some switching action. */
   nexthop_group_mpls_action_t(mpls_action_t action_type,
                               std::forward_list<mpls_label_t> const & label_stack);

   /** Getter for 'action_type': the MPLS switching operation for this action. */
   mpls_action_t action_type() const;
   /** Setter for 'action_type'. */
   void action_type_is(mpls_action_t action_type);

   /**
    * Getter for 'label_stack': the MPLS label stack.
    *
    * The first element is the outermost label.
    */
   std::forward_list<mpls_label_t> const & label_stack() const;
   /** Setter for 'label_stack'. */
   void label_stack_is(std::forward_list<mpls_label_t> const & label_stack);
   /** Prepend one label_stack to the list. */
   void label_stack_set(mpls_label_t const & label_stack);
   /** Remove all matching label_stack elements. */
   void label_stack_del(mpls_label_t const & label_stack);

   bool operator==(nexthop_group_mpls_action_t const & other) const;
   bool operator!=(nexthop_group_mpls_action_t const & other) const;
   bool operator<(nexthop_group_mpls_action_t const & other) const;
   /** The hash function for type nexthop_group_mpls_action_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * nexthop_group_mpls_action_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const nexthop_group_mpls_action_t& obj);

 private:
   mpls_action_t action_type_;
   std::forward_list<mpls_label_t> label_stack_;
};

/** Defines counter for a nexthop entry. */
class EOS_SDK_PUBLIC nexthop_group_entry_counter_t {
 public:
   nexthop_group_entry_counter_t();
   nexthop_group_entry_counter_t(uint64_t packets, uint64_t bytes);

   uint64_t packets() const;

   uint64_t bytes() const;

   bool operator==(nexthop_group_entry_counter_t const & other) const;
   bool operator!=(nexthop_group_entry_counter_t const & other) const;
   bool operator<(nexthop_group_entry_counter_t const & other) const;
   /** The hash function for type nexthop_group_entry_counter_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * nexthop_group_entry_counter_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const nexthop_group_entry_counter_t& obj);

 private:
   uint64_t packets_;
   uint64_t bytes_;
};

/**
 * A nexthop group destination entry.
 *
 * An entry consists of a nexthop IP address, and optionally an MPLS
 * label switching operation.
 */
class EOS_SDK_PUBLIC nexthop_group_entry_t {
 public:
   nexthop_group_entry_t();
   explicit nexthop_group_entry_t(ip_addr_t const & nexthop);

   /** Getter for 'mpls_action': MPLS label switching stack for this entry. */
   nexthop_group_mpls_action_t mpls_action() const;
   /** Setter for 'mpls_action'. */
   void mpls_action_is(nexthop_group_mpls_action_t const & mpls_action);

   /** Getter for 'nexthop': the next hop IP address for this entry. */
   ip_addr_t nexthop() const;
   /** Setter for 'nexthop'. */
   void nexthop_is(ip_addr_t const & nexthop);

   bool operator==(nexthop_group_entry_t const & other) const;
   bool operator!=(nexthop_group_entry_t const & other) const;
   bool operator<(nexthop_group_entry_t const & other) const;
   /** The hash function for type nexthop_group_entry_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * nexthop_group_entry_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const nexthop_group_entry_t& obj);

 private:
   nexthop_group_mpls_action_t mpls_action_;
   ip_addr_t nexthop_;
};

/**
 * A nexthop group.
 *
 * A nexthop group represents encapsulation and IP addressing
 * information to be used with a policy routing application.
 */
class EOS_SDK_PUBLIC nexthop_group_t {
 public:
   nexthop_group_t();
   nexthop_group_t(std::string name, nexthop_group_encap_t type);
   nexthop_group_t(std::string name, nexthop_group_encap_t type,
                   nexthop_group_gre_key_t gre_key_type);
   nexthop_group_t(std::string name, ip_addr_t const & source_ip);
   nexthop_group_t(std::string name, ip_addr_t const & source_ip,
                   std::map<uint16_t, nexthop_group_entry_t> const & nexthops);

   /** Getter for 'name': the unique name of the nexthop group. */
   std::string name() const;

   /** Getter for 'type': the type of packet encapsulation used on the group. */
   nexthop_group_encap_t type() const;

   /** Getter for 'gre_key_type': the key of the GRE tunnel. */
   nexthop_group_gre_key_t gre_key_type() const;

   /** Getter for 'ttl': the TTL set in frame headers of IP-in-IP or GRE tunnels. */
   uint16_t ttl() const;
   /** Setter for 'ttl'. */
   void ttl_is(uint16_t ttl);

   /** Getter for 'source_ip': the source IP used on frames sent on this group. */
   ip_addr_t source_ip() const;
   /** Setter for 'source_ip'. */
   void source_ip_is(ip_addr_t const & source_ip);

   /** Getter for 'source_intf': the source interface to use. */
   intf_id_t source_intf() const;
   /** Setter for 'source_intf'. */
   void source_intf_is(intf_id_t source_intf);

   /**
    * Getter for 'autosize': Dynamic resizing configuration for the nexthop group.
    * When set, unresolved entries from the nexthop group are not programmed into
    * hardware, and packets will be hashed across the remaining reachable entries
    * in the group. Disabled (i.e. set to false) by default.
    */
   bool autosize() const;
   /** Setter for 'autosize'. */
   void autosize_is(bool autosize);

   /**
    * Utility method to return the number of entries configured in the nexthop
    * group.
    */
   uint16_t size() const;
   /** Getter for 'nexthops': array index to nexthop group entry map. */
   std::map<uint16_t, nexthop_group_entry_t> const & nexthops() const;
   /** Setter for 'nexthops'. */
   void nexthops_is(std::map<uint16_t, nexthop_group_entry_t> const & nexthops);
   /** Inserts key/value pair to the map. */
   void nexthop_set(uint16_t key, nexthop_group_entry_t const & value);
   /** Deletes the key/value pair from the map. */
   void nexthop_del(uint16_t key);

   /**
    * Getter for 'destination_ips': array index to IP address map.
    * @deprecated Use 'nexthops' instead.
    */
   std::map<uint16_t, ip_addr_t> const & destination_ips() const;
   /** Setter for 'destination_ips'. */
   void destination_ips_is(std::map<uint16_t, ip_addr_t> const & destination_ips);
   /** Inserts key/value pair to the map. */
   void destination_ip_set(uint16_t key, ip_addr_t const & value);
   /** Deletes the key/value pair from the map. */
   void destination_ip_del(uint16_t key);

   /**
    * Getter for 'counters_unshared': Defines whether entry counters are unshared
    * for the nexthop group. When set, do not share counter values between entries
    * that share the same tunnel destination. Each entry will have its own unique
    * counter. Disabled (i.e. set to false) by default.
    */
   bool counters_unshared() const;
   /** Setter for 'counters_unshared'. */
   void counters_unshared_is(bool counters_unshared);

   bool operator==(nexthop_group_t const & other) const;
   bool operator!=(nexthop_group_t const & other) const;
   bool operator<(nexthop_group_t const & other) const;
   /** The hash function for type nexthop_group_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * nexthop_group_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const nexthop_group_t& obj);

 private:
   std::string name_;
   nexthop_group_encap_t type_;
   nexthop_group_gre_key_t gre_key_type_;
   uint16_t ttl_;
   ip_addr_t source_ip_;
   intf_id_t source_intf_;
   bool autosize_;
   std::map<uint16_t, nexthop_group_entry_t> nexthops_;
   std::map<uint16_t, ip_addr_t> destination_ips_;
   bool counters_unshared_;
};
}

#include <eos/inline/types/nexthop_group.h>

#endif // EOS_TYPES_NEXTHOP_GROUP_H
