// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_MAC_TABLE_H
#define EOS_TYPES_MAC_TABLE_H

#include <eos/eth.h>
#include <eos/hash_mix.h>
#include <eos/intf.h>
#include <eos/utility.h>
#include <set>
#include <sstream>

namespace eos {

/** Types of MAC entries. */
enum mac_entry_type_t {
   MAC_ENTRY_NULL,
   MAC_ENTRY_LEARNED_DYNAMIC,
   MAC_ENTRY_LEARNED_SECURE,
   MAC_ENTRY_CONFIGURED_DYNAMIC,
   MAC_ENTRY_CONFIGURED_SECURE,
   MAC_ENTRY_CONFIGURED_STATIC,
   MAC_ENTRY_PEER_DYNAMIC,
   MAC_ENTRY_PEER_STATIC,
   MAC_ENTRY_PEER_SECURE,
   MAC_ENTRY_LEARNED_REMOTE,
   MAC_ENTRY_CONFIGURED_REMOTE,
   MAC_ENTRY_RECEIVED_REMOTE,
};
/** Appends a string representation of enum mac_entry_type_t value to the ostream. */
std::ostream& operator<<(std::ostream& os, const mac_entry_type_t & enum_val);

/**
 * The MAC entry key class.
 * Maps a MAC address with a specific VLAN ID to an interface.
 */
class EOS_SDK_PUBLIC mac_key_t {
 public:
   /** Default constructor. */
   mac_key_t();
   mac_key_t(vlan_id_t vlan_id, eth_addr_t const & eth_addr);

   /** Getter for 'vlan_id': the VLAN subdomain identifier. */
   vlan_id_t vlan_id() const;

   /** Getter for 'eth_addr': the Ethernet address of the MAC entry. */
   eth_addr_t eth_addr() const;

   /** Non-existent keys are effectively false(so this returns true). */
   bool operator!() const;
   bool operator==(mac_key_t const & other) const;
   bool operator!=(mac_key_t const & other) const;
   bool operator<(mac_key_t const & other) const;
   /** The hash function for type mac_key_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of mac_key_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const mac_key_t& obj);

 private:
   vlan_id_t vlan_id_;
   eth_addr_t eth_addr_;
};

/** An entry from the MAC address table. */
class EOS_SDK_PUBLIC mac_entry_t {
 public:
   /** Default constructor. */
   mac_entry_t();
   /** Constructor for basic MAC entry. */
   explicit mac_entry_t(mac_key_t const & mac_key);
   /** Constructor for unicast MAC entry and interface. */
   mac_entry_t(mac_key_t const & mac_key, intf_id_t intf);
   /** Constructor for multicast MAC entry and interfaces. */
   mac_entry_t(mac_key_t const & mac_key, std::set<intf_id_t> const & intfs);
   /** Deprecated constructor. */
   mac_entry_t(vlan_id_t vlan_id, eth_addr_t eth_addr);

   /** Getter for 'mac_key': the key of the MAC entry. */
   mac_key_t mac_key() const;
   /** Setter for 'mac_key'. */
   void mac_key_is(mac_key_t const & mac_key);

   /**
    * Getter for 'intfs': the set of interfaces that this key forwards to. For
    * unicast MAC entries, this expects a set with either 1 interface or 0
    * interfaces to signify a drop. If passed a multicast MAC address, 'intfs' can
    * contain one or more output interfaces.
    */
   std::set<intf_id_t> const & intfs() const;
   /** Setter for 'intfs'. */
   void intfs_is(std::set<intf_id_t> const & intfs);
   /** Inserts one intf of 'value' to the set. */
   void intf_set(intf_id_t const & value);
   /** Deletes one intf of 'value' from the set. */
   void intf_del(intf_id_t const & value);

   /**
    * Getter for 'persistent': indicates whether this MAC entry persists in system
    * configuration. If true, MAC entry appears in "show running-config".
    */
   bool persistent() const;
   /** Setter for 'persistent'. */
   void persistent_is(bool persistent);

   /**
    * Returns 'true' if this key is "empty", that is if neither the VLAN nor the
    * MAC address is set.
    */
   bool operator!() const;
   /** The VLAN subdomain identifier of the MAC entry. */
   vlan_id_t vlan_id() const;
   /** The Ethernet address of the MAC entry. */
   eth_addr_t eth_addr() const;
   /**
    * Return the interface of the unicast MAC entry, the first interface of a
    * multicast MAC entry, or an empty object if the entry is a drop entry.
    */
   intf_id_t intf() const;
   /** Setter for 'intf': a single interface in a MAC entry. */
   void intf_is(intf_id_t intf);
   bool operator==(mac_entry_t const & other) const;
   bool operator!=(mac_entry_t const & other) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of mac_entry_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const mac_entry_t& obj);

 private:
   mac_key_t mac_key_;
   std::set<intf_id_t> intfs_;
   bool persistent_;
};
}

#include <eos/inline/types/mac_table.h>

#endif // EOS_TYPES_MAC_TABLE_H
