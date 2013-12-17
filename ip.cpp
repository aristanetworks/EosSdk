// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>
#include <cstring>

#include "eos/ip.h"

namespace eos {

ip_addr_t::ip_addr_t(char const *address_string) {
   assert(parse_ip_addr(address_string, this));
}

ip_addr_t::ip_addr_t(std::string const &address) {
   assert(parse_ip_addr(address.c_str(), this));
}

// Take an address family and an array of 4 (v4) or 16 (v6) uint8_t's.
// Representation compatible to Linux's sockaddr_in6.sin6_addr (i.e.,
// __be8[16]).
// NOTE: 'address' is in network byte order for both IPv4 and IPv6 as
// per Linux and Arnet.
ip_addr_t::ip_addr_t(af_t af, uint8_t const * addr) {
   af_ = af;
   memcpy(&addr_, addr, af_ == AF_IPV4 ? 4 : 16);
}

// Construct from a Linux in_addr (IPv4)
ip_addr_t::ip_addr_t(in_addr const & addr) {
   af_ = AF_IPV4;
   memcpy(&addr_, &addr, sizeof(addr));
}

// Construct from a Linux in6_addr (IPv6)
ip_addr_t::ip_addr_t(in6_addr const & addr) {
   // Linux in.h in_addr is in network byte order, no conversion required
   af_ = AF_IPV6;
   memcpy(&addr_, &addr, sizeof(addr));
}

// ip_prefix_t constructors

ip_prefix_t::ip_prefix_t(char const *prefix_string) {
   assert(!parse_ip_prefix(prefix_string, this));
}

// ip_addr_mask_t constructors

ip_addr_mask_t::ip_addr_mask_t(ip_addr_t const &address, int mask_length) {
   addr_ = address;
   if (mask_length >= 0 and mask_length < 129) {
      mask_length_ = uint8_t(mask_length);
   } else {
      assert(!"mask_length must be between 0..128");
   }
}

// Operators

bool
ip_addr_t::operator==(ip_addr_t const &other) const {
   if (af_ != other.af_) {
      return false;
   }
   return memcmp(addr_.bytes, other.addr_.bytes, af_ == AF_IPV4 ? 4 : 16) == 0;
}

// Accessors

// The IPv4 address as a word in network byte order
uint32_be_t
ip_addr_t::addr_v4() const {
   assert(af_ == AF_IPV4 && "cannot call addr_v4() for non AF_IPV4 addresses");
   return addr_.words[0];
}

bool
parse_ip_prefix(char const *, ip_prefix_t * result) {
   return true;  // TODO: No op impl.
}

bool
parse_ip_addr(char const *addr, ip_addr_t *result) {
   return true;  // TODO: No op impl.
}

std::string
ip_addr_t::to_string() const {
   return "not.implemented.yet";
}

std::string
ip_prefix_t::to_string() const {
   return "not.implemented/yet";
}

}
