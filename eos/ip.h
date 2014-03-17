// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_IP_H
#define EOS_IP_H

#include <netinet/in.h>

#include <string>
#include <eos/base.h>

#include <stddef.h>

namespace eos {

/// The address family of an IP address.
enum af_t {
   /// Not a valid address family (e.g., the default address).
   AF_NULL = 0,
   /// An IPv4 address.
   AF_IPV4 = 4,
   /// An IPv6 address.
   AF_IPV6 = 6,
};

/**
 * An IP address.
 * Both IPv4 and IPv6 addresses are supported by this class.
 */
class EOS_SDK_PUBLIC ip_addr_t {
 public:
   ip_addr_t();
   /**
    * Creates an address from an address family and a network order array of bytes.
    * Pass exactly 4 bytes for AF_IPV4 address type or 16 bytes for AF_IPV6.
    */
   ip_addr_t(af_t, uint8_t const * ip_addr);
   /// Creates an IP address from a POSIX in_addr (IPv4).
   explicit ip_addr_t(in_addr const &);
   /// Creates an IP address from a POSIX in6_addr (IPv6).
   explicit ip_addr_t(in6_addr const &);

   /**
    * Creates an IP address from the provided string.
    * panic() is called if an invalid (non IPv4 or IPv6) address is supplied.
    * @param[in] addr An IPv4 or IPv6 address as a string
    */
   explicit ip_addr_t(std::string const & addr); // converts from IPv4/v6 string
   /**
    * Creates an IP address from the provided string.
    * panic() is called if an invalid (non IPv4 or IPv6) address is supplied.
    * @param[in] addr An IPv4 or IPv6 address as a string
    */
   explicit ip_addr_t(char const * addr); // converts from IPv4/v6 string
   /// Takes a network order 32-bit unsigned integer as an IPv4 address.
   explicit ip_addr_t(uint32_be_t addr_v4);

   bool operator==(ip_addr_t const & other) const;
   bool operator!=(ip_addr_t const & other) const;
   bool operator<(ip_addr_t const & other) const;
   operator bool() const;

   /// The address family of this IP address.
   af_t af() const;
   /**
    * The IP address as a big endian array of bytes.
    * @return A byte array, 4 bytes long if af() == AF_IPV4 and 16 for AF_IPV6.
    */
   uint8_t const * addr() const;

   /**
    * The IP address as a big endian 32-bit integer.
    *
    * Only valid for IPv4 addresses; panic() is called if used on an
    * AF_IPV6 family address.
    */
   uint32_be_t addr_v4() const;
   /// String representation of the IP address, e.g. "1.2.3.4" or "f00d::1".
   std::string to_string() const;

 private:
   af_t af_;
   union {
      uint8_t bytes[16];
      uint32_t words[4];
   } addr_;

   friend bool parse_ip_addr(char const *, ip_addr_t * result);
};

/**
 * An IPv4 or IPv6 route prefix.
 *
 * A route prefix combines a network address and a prefix length.
 * A network address has no 1 bits in the host component of the address
 * (i.e., only the first prefix_length bits of the address can be
 * non-zero).
*/
class EOS_SDK_PUBLIC ip_prefix_t {
 public:
   ip_prefix_t();
   /**
    * Constructs a prefix from an IP network address and prefix length in bits.
    *
    * panic() is called if the address provided is not a valid network
    * address given the provided prefix length.
    */
   ip_prefix_t(ip_addr_t const &, int);

   /**
    * Constructs a prefix with the provided IP prefix string.
    * Supports IPv4 and IPv6 address prefixes. This constructor
    * will call panic() if the string passed is not a valid network
    * prefix (e.g., "10.1.2.7/24" is invalid, while "10.1.2.0/24" is OK).
    */
   explicit ip_prefix_t(char const *);

   /// The address family of the prefix.
   af_t af() const;
   /// The prefix's network address.
   ip_addr_t const network() const;
   /// The prefix length in bits.
   int prefix_length() const;
   /**
    * The prefix as mask. A prefix length of 8 on a v4 address will
    * yield the mask 255.0.0.0
    */
   ip_addr_t const mask() const;
   /// Returns the prefix as a string, e.g., "10.2.3.4/24" or "cafe::1/128"
   std::string to_string() const;

 private:
   ip_addr_t addr_;
   uint8_t prefix_length_;
   friend bool parse_ip_prefix(char const *, ip_prefix_t * result);
};

/**
 * An IP address with a subnet mask.
 *
 * This allows for contiguous subnet masks only for IPv4 and IPv6 addresses.
 *
 * IPv6 addresses in EOS only support contiguous masks, so
 * for IPv6 addresses mask() provides the same value as mask_length().
 */
class EOS_SDK_PUBLIC ip_addr_mask_t {
 public:
   ip_addr_mask_t();
   ip_addr_mask_t(ip_addr_t const &, int mask_length);

   bool operator==(ip_addr_mask_t const & other) const;
   bool operator!=(ip_addr_mask_t const & other) const;

   /// Address family of this address/mask.
   af_t af() const;
   /// The address/mask's IP address.
   ip_addr_t const addr() const;

   /// The bit mask length, e.g., 24.
   int mask_length() const;
   /// The bit mask itself, e.g., 0xFFFFFF00 (IPv4). For IPv6, same as mask_length().
   uint32_be_t mask() const;

   /// The IP address and mask as a string, e.g., '192.0.2.1/0xFFFFFF00'.
   std::string to_string() const;

 private:
   ip_addr_t addr_;
   uint8_t mask_length_;
};

/**
 * Parses a string IP address, returning true if the address is valid.
 * Supports both IPv4 and IPv6 addresses.
 *
 * @param[in] addr Pointer to a C string containing an address to parse.
 * @param[out] result Mutable arugment to place a successfully parsed result into.
 * @return true if the address parsed successfully, false otherwise.
 */
bool parse_ip_addr(char const * addr, ip_addr_t * result) EOS_SDK_PUBLIC;

/**
 * Parses an IP route prefix, returns true if the prefix is valid.
 * Supports both IPv4 and IPv6 route prefixes.
 *
 * For example, "10.1.2.0/24" or "fffe:abab:1234::/96" are legal, but
 * "10.1.2.7/24" is not, as 10.1.2.7 is not a valid network address for
 * a 24-bit prefix length.
 *
 * @param[in] addr Pointer to a C string containing a prefix to parse.
 * @param[out] result Mutable arugment to place a successfully parsed result into.
 * @return true if the route prefix parsed successfully, false otherwise.
 */
bool parse_ip_prefix(char const * addr, ip_prefix_t * result) EOS_SDK_PUBLIC;

}  // end namespace eos

#include <eos/inline/ip.h>  /// Inline definitions

#endif // EOS_IP_H
