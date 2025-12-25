// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_NEIGHBOR_TABLE_IMPL_H
#define EOS_TYPES_NEIGHBOR_TABLE_IMPL_H

#include <eos/eth.h>
#include <eos/hash_mix.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

/**
 * The neighbor entry key class.
 * Maps an IP address to its associated MAC address on a specific interface. Note:
 * the "intf_id" attribute is only relevant for IPv6 neighbors.
 */
class EOS_SDK_PUBLIC neighbor_key_impl_t {
 public:
   neighbor_key_impl_t();
   explicit neighbor_key_impl_t(ip_addr_t const & ip_addr);
   /** IPv6 neighbor keys include an interface ID. */
   neighbor_key_impl_t(ip_addr_t const & ip_addr, intf_id_t intf_id);

   std::string vrf_name() const;
   void vrf_name_is(std::string vrf_name);

   /** Getter for 'ip_addr': the ip address of the neighbor entry. */
   ip_addr_t ip_addr() const;

   /** Getter for 'intf_id': the interface of the neighbor entry. */
   intf_id_t intf_id() const;

   bool operator==(neighbor_key_impl_t const & other) const;
   bool operator!=(neighbor_key_impl_t const & other) const;
   bool operator<(neighbor_key_impl_t const & other) const;
   /** The hash function for type neighbor_key_t. */
   uint32_t hash() const;
   /** The hash mix function for type neighbor_key_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of neighbor_key_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const neighbor_key_impl_t& obj);

 private:
   std::string vrf_name_;
   ip_addr_t ip_addr_;
   intf_id_t intf_id_;
};

/** The neighbor entry class. */
class EOS_SDK_PUBLIC neighbor_entry_impl_t {
 public:
   neighbor_entry_impl_t();
   neighbor_entry_impl_t(neighbor_key_t const & neighbor_key, eth_addr_t eth_addr,
                         neighbor_entry_type_t entry_type);

   /** Getter for 'neighbor_key': the key of the neighbor entry. */
   neighbor_key_t neighbor_key() const;

   /** Getter for 'eth_addr': the Ethernet address of the neighbor entry. */
   eth_addr_t eth_addr() const;

   /**
    * Getter for 'entry_type': the type of neighbor entry, it will be either STATIC
    * or DYNAMIC.
    */
   neighbor_entry_type_t entry_type() const;

   bool operator==(neighbor_entry_impl_t const & other) const;
   bool operator!=(neighbor_entry_impl_t const & other) const;
   bool operator<(neighbor_entry_impl_t const & other) const;
   /** The hash function for type neighbor_entry_t. */
   uint32_t hash() const;
   /** The hash mix function for type neighbor_entry_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * neighbor_entry_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const neighbor_entry_impl_t& obj);

 private:
   neighbor_key_t neighbor_key_;
   eth_addr_t eth_addr_;
   neighbor_entry_type_t entry_type_;
};
}

#endif // EOS_TYPES_NEIGHBOR_TABLE_IMPL_H
