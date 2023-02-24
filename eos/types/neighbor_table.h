// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_NEIGHBOR_TABLE_H
#define EOS_TYPES_NEIGHBOR_TABLE_H

#include <eos/eth.h>
#include <eos/hash_mix.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

/** Neighbor entry types. */
enum neighbor_entry_type_t {
   NEIGHBOR_ENTRY_TYPE_NULL,
   NEIGHBOR_ENTRY_TYPE_DYNAMIC,
   NEIGHBOR_ENTRY_TYPE_STATIC,
};
/**
 * Appends a string representation of enum neighbor_entry_type_t value to the
 * ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const neighbor_entry_type_t & enum_val);

class neighbor_key_impl_t;
/**
 * The neighbor entry key class.
 * Maps an IP address to its associated MAC address on a specific interface. Note:
 * the "intf_id" attribute is only relevant for IPv6 neighbors.
 */
class EOS_SDK_PUBLIC neighbor_key_t {
 public:
   neighbor_key_t();
   explicit neighbor_key_t(ip_addr_t const & ip_addr);
   /** IPv6 neighbor keys include an interface ID. */
   neighbor_key_t(ip_addr_t const & ip_addr, intf_id_t intf_id);
   neighbor_key_t(const neighbor_key_t& other);
   neighbor_key_t& operator=(
      neighbor_key_t const & other);


   /** Getter for 'ip_addr': the ip address of the neighbor entry. */
   ip_addr_t ip_addr() const;

   /** Getter for 'intf_id': the interface of the neighbor entry. */
   intf_id_t intf_id() const;

   bool operator==(neighbor_key_t const & other) const;
   bool operator!=(neighbor_key_t const & other) const;
   bool operator<(neighbor_key_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os, const neighbor_key_t& obj);

 private:
   std::shared_ptr<neighbor_key_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const neighbor_key_t& obj);

class neighbor_entry_impl_t;
/** The neighbor entry class. */
class EOS_SDK_PUBLIC neighbor_entry_t {
 public:
   neighbor_entry_t();
   neighbor_entry_t(neighbor_key_t const & neighbor_key, eth_addr_t eth_addr,
                    neighbor_entry_type_t entry_type);
   neighbor_entry_t(const neighbor_entry_t& other);
   neighbor_entry_t& operator=(
      neighbor_entry_t const & other);


   /** Getter for 'neighbor_key': the key of the neighbor entry. */
   neighbor_key_t neighbor_key() const;

   /** Getter for 'eth_addr': the Ethernet address of the neighbor entry. */
   eth_addr_t eth_addr() const;

   /**
    * Getter for 'entry_type': the type of neighbor entry, it will be either STATIC
    * or DYNAMIC.
    */
   neighbor_entry_type_t entry_type() const;

   bool operator==(neighbor_entry_t const & other) const;
   bool operator!=(neighbor_entry_t const & other) const;
   bool operator<(neighbor_entry_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os, const neighbor_entry_t& obj);

 private:
   std::shared_ptr<neighbor_entry_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const neighbor_entry_t& obj);
}

#endif // EOS_TYPES_NEIGHBOR_TABLE_H
