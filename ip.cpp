// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <arpa/inet.h>
#include <string.h>

#include <Arnet/Arnet.h>
#include <Tac/Tracing.h>
#include <Tac/Exception.h>

#include <EosSdk/ip.h>
#include <EosSdk/panic.h>
#include <EosSdk/base.h>

DEFAULT_TRACE_HANDLE("EosSdkIp")


namespace eos {

// ip_addr_t constructors

// default constructor produces has AF_NULL, making it
// invalid to pass to many higher level constructors.
ip_addr_t::ip_addr_t() : af_(0) {
   memset(&addr_, 0, sizeof(addr_));
}

// Parse the IPv4 or IPv6 address string supplied. Calls panic() if
// the address is invalid, so if user input is provided, first
// validate with parse_ip_addr().
ip_addr_t::ip_addr_t(const char *address_string) {
   if (!parse_ip_addr(address_string, this)) {
      panic("invalid IP address");
   }
}

ip_addr_t::ip_addr_t(const std::string& address) {
   // TODO: Remove this code duplication by using a delegating constructor.
   // Apparently our >3 year old version of g++ (4.5.1 now) doesn't parse
   // those, we need at least 4.7.
   if (!parse_ip_addr(address.c_str(), this)) {
      panic("invalid IP address");
   }
}

// Take an address family and an array of 4 (v4) or 16 (v6) uint8_t's.
// Representation compatible to Linux's sockaddr_in6.sin6_addr (i.e.,
// __be8[16]).
// NOTE: 'address' is in network byte order for both IPv4 and IPv6 as
// per Linux and Arnet.
ip_addr_t::ip_addr_t(af_t af, uint8_t const * addr) {
   af_ = af;
   if (af_ == AF_IPV4) {
      memcpy(&addr_, addr, 4);
   } else if (af_ == AF_IPV6) {
      memcpy(&addr_, addr, 16);
   }
}

// Construct from a Linux sockaddr in_addr (IPv4)
ip_addr_t::ip_addr_t(struct in_addr const & addr) {
   // Linux in.h in_addr is in network byte order, no conversion required
   af_ = AF_IPV4;
   memcpy(&addr_, &addr, sizeof(addr));
}

// Construct from a Linux sockaddr6 in6_addr (IPv6)
ip_addr_t::ip_addr_t(struct in6_addr const & addr) {
   // Linux in.h in_addr is in network byte order, no conversion required
   af_ = AF_IPV6;
   memcpy(&addr_, &addr, sizeof(addr));
}

// IPv4 address (one word) in network byte order
ip_addr_t::ip_addr_t(uint32_be_t addr_v4) {
   af_ = AF_IPV4;
   addr_.words[0] = addr_v4;
}

// Hidden consturctors for conversions from TACC types
ip_addr_t::ip_addr_t(Arnet::IpAddr const &other) {
   af_ = AF_IPV4;
   addr_.words[0] = other.valueNbo();
}

ip_addr_t::ip_addr_t(Arnet::Ip6Addr const &other) {
   for (int i=0; i < 16; i++) {
      addr_.bytes[i] = uint32_t(other.u8(i));
   }
   af_ = AF_IPV6;
}

// ip_prefix_t constructors

ip_prefix_t::ip_prefix_t() {
}

ip_prefix_t::ip_prefix_t(const char *prefix_string) {
   if (!parse_ip_prefix(prefix_string, this)) {
      panic("input is not an IPv4 or IPV6 prefix");
   }
}

ip_prefix_t::ip_prefix_t(ip_addr_t const & address, int prefix_length) {
   addr_ = address;
   prefix_length_ = prefix_length;
}

// ip_addr_mask_t constructors

ip_addr_mask_t::ip_addr_mask_t() {
   addr_ = ip_addr_t();
   mask_length_ = 0;
}

ip_addr_mask_t::ip_addr_mask_t(ip_addr_t const &address, int mask_length) {
   addr_ = address;
   if (mask_length >= 0 and mask_length < 129) {
      mask_length_ = uint8_t(mask_length);
   } else {
      panic("mask_length must be between 0..128");
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

bool
ip_addr_t::operator!=(ip_addr_t const & other) const {
   return !(*this == other);
}

// Accessors

// Returns the 16-byte address for the address, in network byte order
// IPv4 addresses occupy the first word only; words 2-4 are empty
uint8_t const *
ip_addr_t::addr() const {
   return static_cast<uint8_t const *>(addr_.bytes);
}

uint8_t const *
ip_addr_mask_t::addr() const {
   return addr_.addr();
}

uint8_t const *
ip_prefix_t::network() const {
   return addr_.addr();
}

// The IPv4 address as a word in network byte order
uint32_be_t
ip_addr_t::addr_v4() const {
   if (af_ != AF_IPV4) {
      panic("cannot call addr_v4() for non AF_IPV4 addresses");
   }
   return addr_.words[0];
}

uint32_t
ip_addr_mask_t::addr_v4() const {
   return addr_.addr_v4();
}

uint32_t
ip_prefix_t::network_v4() const {
   return addr_.addr_v4();
}

af_t
ip_addr_t::af() const {
   return af_t(af_);
}

af_t
ip_prefix_t::af() const {
   return af_t(addr_.af_);
}

af_t
ip_addr_mask_t::af() const {
   return addr_.af();
}

int
ip_prefix_t::prefix_length() const {
   return prefix_length_;
}

int
ip_addr_mask_t::mask_length() const {
   return mask_length_;
}

// Parses an v4 or v6 IP address string like "1.2.3.4" and "de:ad:be:ef::"
// True iff the IP address was valid (e.g., 555.555.555.555 is invalid)
// Second argument is updated with the converted results if valid
bool
parse_ip_addr(char const *addr, ip_addr_t *result) {
   TRACE0(__FUNCTION__ << " addr=" << addr);
   bool valid = false;
   // Try IPv4 first
   auto v4_addr = Arnet::IpAddr();
   try {
      Tac::Expect expected(Tac::Exception::unknownException_,
                           Tac::Exception::rangeException_);
      v4_addr.stringValueIs(addr);  // throws when not an IPv4 address string
      valid = true;
   } catch (...) {
      valid = false;
   }
   if (valid) {
      result->af_ = AF_IPV4;
      result->addr_.words[0] = v4_addr.value();
      return result;
   }
   // If IPv4 failed, try IPv6
   auto v6_addr = Arnet::Ip6Addr();
   try {
      Tac::Expect expected(Tac::Exception::unknownException_,
                           Tac::Exception::rangeException_);
      v6_addr.stringValueIs(addr);
      valid = true;
   } catch (...) {
      // Neither a valid IPv4 or IPv6 address
      valid = false;
   }
   if (valid) {
      result->af_ = AF_IPV6;
      for (int i=0; i < 16; i++) {
         result->addr_.bytes[i] = uint32_t(v6_addr.u8(i));
      }
   }
   return valid;
}

// Parses an v4 or v6 IP prefix string
// True iff the prefix is both syntatically and semantically
// a valid IP address prefix. e.g., "1.2.3.4/24" returns false,
// but "1.2.3.0/24" returns true.
// Second argument is updated with the converted results if valid
bool
parse_ip_prefix(char const *prefix, ip_prefix_t *result) {
   TRACE0(__FUNCTION__ << " prefix=" << prefix);
   Arnet::IpGenPrefix pfx;
   try {
      Tac::Expect expected(Tac::Exception::rangeException_,
                           Tac::Exception::unknownException_);

      pfx = Arnet::IpGenPrefix(Tac::Name(prefix));
   } catch (...) {
      return false;
   }
   // The prefix is valid, update the passed ip_prefix_t result
   switch (pfx.af()) {
    case Arnet::ipv4_:
      result->addr_ = ip_addr_t(pfx.v4Prefix().address().value());
      result->prefix_length_ = uint8_t(pfx.v4Prefix().len());
      break;
    case Arnet::ipv6_:
      uint8_t bytes[16];
      for (int i=0; i < 16; i++) {
         bytes[i] = uint8_t(pfx.v6Prefix().address().u8(i));
      }
      result->addr_ = ip_addr_t(AF_IPV6, bytes);
      result->prefix_length_ = uint8_t(pfx.v6Prefix().len());
      break;
    default:
      return false;
   }
   return true;
}

// TBD: use std::string

std::string
ip_addr_t::to_string() const {
   if (af_ == AF_IPV4) {
      auto ip4 = Arnet::IpAddr(addr_v4());
      return std::string(ip4.stringValue().charPtr());
   } else if (af_ == AF_IPV6) {
      auto ip6 = Arnet::Ip6Addr();
      for (int i=0; i < 16; i++) {
         ip6.u8Is(i, U8(addr_.bytes[i]));
      }
      return std::string(ip6.stringValue().charPtr());
   } else {
      panic("Cannot generate string value of unknown address family");
      return std::string();
   }
}

std::string
ip_prefix_t::to_string() const {
   // update buf with the IP address
   auto prefix_string = Tac::String(
         Tac::format("%s/%d", addr_.to_string().c_str(), prefix_length_));
   return prefix_string.stdString();
}

};
