// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_IP_H
#define EOS_INLINE_IP_H

#include <eos/panic.h>

namespace eos {

// ip_addr_t constructors

// default constructor produces has AF_NULL, making it
// invalid to pass to many higher level constructors.
inline ip_addr_t::ip_addr_t() : af_(AF_NULL), addr_() {
}

// Parse the IPv4 or IPv6 address string supplied. Calls panic() if
// the address is invalid, so if user input is provided, first
// validate with parse_ip_addr().
inline ip_addr_t::ip_addr_t(char const *address_string) {
   if (!parse_ip_addr(address_string, this)) {
      panic("invalid IP address");
   }
}

inline ip_addr_t::ip_addr_t(std::string const &address) {
   // TODO: Remove this code duplication by using a delegating constructor.
   // Apparently our >3 year old version of g++ (4.5.1 now) doesn't parse
   // those, we need at least 4.7.
   if (!parse_ip_addr(address.c_str(), this)) {
      panic("invalid IP address");
   }
}

// IPv4 address (one word) in network byte order
inline ip_addr_t::ip_addr_t(uint32_be_t addr_v4) : af_(AF_IPV4) {
   addr_.words[0] = addr_v4;
}

// ip_prefix_t constructors

inline ip_prefix_t::ip_prefix_t() {
}

inline ip_prefix_t::ip_prefix_t(ip_addr_t const & address, int prefix_length)
   : addr_(address), prefix_length_(prefix_length) {
}

inline ip_prefix_t::ip_prefix_t(char const *prefix_string) {
   if (!parse_ip_prefix(prefix_string, this)) {
      panic("input is not an IPv4 or IPV6 prefix");
   }
}

// ip_addr_mask_t constructors

inline ip_addr_mask_t::ip_addr_mask_t()
   : addr_(ip_addr_t()),
     mask_length_() {
}

inline ip_addr_mask_t::ip_addr_mask_t(ip_addr_t const &address, int mask_length) {
   addr_ = address;
   if (mask_length >= 0 and mask_length < 129) {
      mask_length_ = uint8_t(mask_length);
   } else {
      panic("mask_length must be between 0..128");
   }
}

// Operators

inline bool
ip_addr_t::operator!=(ip_addr_t const & other) const {
   return !(*this == other);
}

inline
ip_addr_t::operator bool() const {
   return (af_ != AF_NULL);
}

inline bool
ip_addr_mask_t::operator==(ip_addr_mask_t const & other) const {
   return (addr_ == other.addr_) && (mask_length_ == other.mask_length_);
}

inline bool
ip_addr_mask_t::operator!=(ip_addr_mask_t const & other) const {
   return !(*this == other);
}

// Accessors

// The IPv4 address as a word in network byte order
inline uint32_be_t
ip_addr_t::addr_v4() const {
   if(af_ != AF_IPV4) {
      panic("cannot call addr_v4() for non AF_IPV4 addresses");
   }
   return addr_.words[0];
}

// Returns the 16-byte address for the address, in network byte order
// IPv4 addresses occupy the first word only; words 2-4 are empty
inline uint8_t const *
ip_addr_t::addr() const {
   return static_cast<uint8_t const *>(addr_.bytes);
}

inline ip_addr_t const
ip_addr_mask_t::addr() const {
   return addr_;
}

inline ip_addr_t const
ip_prefix_t::network() const {
   return addr_;
}

inline ip_addr_t const
ip_prefix_t::mask() const {
   uint8_t addr[16] = {};
   int word;
   for(word = 0; word < prefix_length_ / 8; word++) {
      // Set any full words.
      addr[word] = 0xFF;
   }
   if(word < (af() == AF_IPV4 ? 4 : 16) && prefix_length_ % 8) {
      // There are remaining bits to set
      addr[word] = 0xFF;
      addr[word] <<= (8 - prefix_length_ % 8);
   }
   return ip_addr_t(af(), addr);
}

inline af_t
ip_addr_t::af() const {
   return af_;
}

inline af_t
ip_prefix_t::af() const {
   return addr_.af();
}

inline af_t
ip_addr_mask_t::af() const {
   return addr_.af();
}

inline int
ip_prefix_t::prefix_length() const {
   return prefix_length_;
}

inline int
ip_addr_mask_t::mask_length() const {
   return mask_length_;
}

inline uint32_be_t
ip_addr_mask_t::mask() const {
   uint32_be_t r = (0xFFFFFFFF << (32 - mask_length_)) & 0xFFFFFFFF;
   return r;
}

}

#endif // EOS_INLINE_IP_H
