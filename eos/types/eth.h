// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_ETH_H
#define EOS_TYPES_ETH_H

#include <assert.h>
#include <bitset>
#include <eos/base.h>
#include <eos/exception.h>
#include <eos/hash_mix.h>
#include <eos/utility.h>
#include <memory>
#include <netinet/in.h>
#include <sstream>
#include <stddef.h>
#include <stdio.h>

namespace eos {

/// A bitset representing a collection of VLAN IDs
class EOS_SDK_PUBLIC vlan_set_t: public std::bitset<4096> {
};

/// A deprecated alias. Use eos::vlan_set_t instead.
typedef vlan_set_t vlan_set;

/** Valid range of 1-4094 (0/4095 are reserved). */
typedef uint16_t vlan_id_t;


/** An Ethernet address. */
class EOS_SDK_PUBLIC eth_addr_t {
 public:
   /**
    * Default constructor. Copy constructor and assignment operator implicitly
    * declared.
    */
   eth_addr_t();
   /**
    * Constructs an address from a char *.
    * Supported formats are xx:xx:xx:xx:xx:xx, xx-xx-xx-xx-xx-xx, or
    * xxxx.xxxx.xxxx.
    */
   explicit eth_addr_t(char const * addr);
   /**
    * Constructs an address from a std::string.
    * Supported formats are xx:xx:xx:xx:xx:xx, xx-xx-xx-xx-xx-xx, or
    * xxxx.xxxx.xxxx.
    */
   explicit eth_addr_t(std::string const & addr);
   /** Constructs an address from the 6 bytes that make it up. */
   eth_addr_t(uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3,
              uint8_t byte4, uint8_t byte5);
   /** Constructs an address from a byte array. The array will be copied. */
   explicit eth_addr_t(uint8_t const bytes[6]);

   /** String representation of a Ethernet address, e.g "xx:xx:xx:xx:xx:xx". */
   std::string to_string() const;

   /** Only the default MAC address (all zeros) evaluates to false. */
   bool operator!() const;
   bool operator==(eth_addr_t other) const;
   bool operator!=(eth_addr_t other) const;
   bool operator<(eth_addr_t other) const;
   explicit operator bool() const;
   /** The hash function for type eth_addr_t. */
   uint32_t hash() const;
   /** The hash mix function for type eth_addr_t. */
   void mix_me(hash_mix & h) const;

   /** Returns the given byte from the address. */
   uint8_t byte(int index) const;
   /** Copies the bytes of the Ethernet address to the given address. */
   void bytes(void * arr) const;
   /** Returns true if the Ethernet address is a unicast address. */
   bool is_unicast() const;
   /** Returns true if the Ethernet address is a multicast address. */
   bool is_multicast() const;
   /** Returns true if the Ethernet address is a broadcast address. */
   bool is_broadcast() const;
   /**
    * A utility stream operator that adds a string representation of eth_addr_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const eth_addr_t& obj);

 private:
   uint8_t bytes_[6];
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const eth_addr_t& obj);


/** The given VLAN number was invalid (for example 0 or 4095). */
class EOS_SDK_PUBLIC invalid_vlan_error : public error {
 public:
   explicit invalid_vlan_error(vlan_id_t vlan) noexcept;
   virtual ~invalid_vlan_error() noexcept;

   vlan_id_t vlan() const noexcept;

   virtual void raise() const;
   /** The hash function for type invalid_vlan_error. */
   uint32_t hash() const;
   /** The hash mix function for type invalid_vlan_error. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * invalid_vlan_error to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const invalid_vlan_error& obj);

 private:
   vlan_id_t vlan_;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const invalid_vlan_error& obj);


/** Tried to configure an internal VLAN on a trunk port. */
class EOS_SDK_PUBLIC internal_vlan_error : public configuration_error {
 public:
   explicit internal_vlan_error(vlan_id_t vlan) noexcept;
   virtual ~internal_vlan_error() noexcept;

   vlan_id_t vlan() const noexcept;

   virtual void raise() const;
   /** The hash function for type internal_vlan_error. */
   uint32_t hash() const;
   /** The hash mix function for type internal_vlan_error. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * internal_vlan_error to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const internal_vlan_error& obj);

 private:
   vlan_id_t vlan_;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const internal_vlan_error& obj);
}

#endif // EOS_TYPES_ETH_H
