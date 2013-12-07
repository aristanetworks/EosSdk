// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_IP_H
#define EOS_IP_H

#include <netinet/in.h>

#include <string>
#include <eos/base.h>

#include <stddef.h>
#include <netinet/in.h>

//= hidden
#include <Arnet/Arnet.h>
#include <Arnet/IpAddr.h>
//= end_hidden

namespace eos {

enum af_t {
   AF_NULL = 0,
   AF_IPV4 = 4,
   AF_IPV6 = 6,
};

// An IP address type that supports IPv4 and IPv6
//
class EOS_SDK_PUBLIC ip_addr_t {
 public:
   ip_addr_t();
   ip_addr_t(af_t, uint8_t const * ip_addr);  // copied; in network byte order
   explicit ip_addr_t(in_addr const &);
   explicit ip_addr_t(in6_addr const &);
   explicit ip_addr_t(char const * name); // converts from IPv4/v6 string
   explicit ip_addr_t(std::string const & name); // converts from IPv4/v6 string
   explicit ip_addr_t(uint32_be_t addr_v4);

   bool operator==(ip_addr_t const & other) const;
   bool operator!=(ip_addr_t const & other) const;

   af_t af() const;
   uint8_t const * addr() const;
   uint32_be_t addr_v4() const;

   std::string to_string() const;

   //=> private:
   union {
      uint8_t bytes[16];
      uint32_t words[4];
   } addr_;
   uint8_t af_;   // af_t in one byte.
};

// A v4 or v6 IP route prefix of a network address and a prefix_length.
// Network adresses have non-zero bits in only the first prefix_length
// bits (in big/network endian)
class EOS_SDK_PUBLIC ip_prefix_t {
 public:
   ip_prefix_t();
   ip_prefix_t(ip_addr_t const &, int);
   ip_prefix_t(char const *);  // Converts IPv4/IPv6 prefix string

   af_t af() const;
   uint8_t const * network() const;
   uint32_t network_v4() const;
   int prefix_length() const;

   std::string to_string() const;  // returns "10.2.3.4/24", "::1" or "::1/128", etc

   //=> private:
   ip_addr_t addr_;
   uint8_t prefix_length_;
};

// An IPv4 or IPv6 address with a full 32-bit mask, to allow for non-
// contiguous subnet masks (e.g., for ACLs).
class EOS_SDK_PUBLIC ip_addr_mask_t {
 public:
   ip_addr_mask_t();
   ip_addr_mask_t(ip_addr_t const &, int mask_length);

   af_t af() const;
   uint8_t const * addr() const;
   uint32_be_t addr_v4() const;
   int mask_length() const; // e.g., 24
   uint32_be_t mask() const; // e.g., 0xffffff00

   std::string to_string() const;

   //=> private:
   ip_addr_t addr_;
   uint8_t mask_length_;

   //= hidden
   // Private helper function used by EOS SDK users of ip.h
   Arnet::IpAddrWithFullMask getIpAddrWithFullMask() const;
   Arnet::Ip6AddrWithMask getIp6AddrWithMask() const;
   //= end_hidden
};

// e.g., "10.1.2.0/24" or "fffe::0001/96"
// Note that "10.1.2.7/24" is not legal.
bool parse_ip_prefix(char const *, ip_prefix_t * result) EOS_SDK_PUBLIC;

// same as above but without the prefix length.
bool parse_ip_addr(char const *, ip_addr_t * result) EOS_SDK_PUBLIC;

// same as above but "10.1.2.7/24" is legal.
bool parse_ip_addr_mask(char const *, ip_addr_mask_t * result) EOS_SDK_PUBLIC;

};  // end namespace eos

#endif // EOS_IP_H
