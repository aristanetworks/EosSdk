// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cstring>

#include "eos/ip.h"

namespace eos {

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

// Operators

bool
ip_addr_t::operator==(ip_addr_t const &other) const {
   if (af_ != other.af_) {
      return false;
   }
   return memcmp(addr_.bytes, other.addr_.bytes, af_ == AF_IPV4 ? 4 : 16) == 0;
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

std::string
ip_addr_mask_t::to_string() const {
   return "not.implemented/yet";
}

}
