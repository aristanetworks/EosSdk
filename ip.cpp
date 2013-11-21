// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <string.h>

#include <EosSdk/ip.h>
#include <EosSdk/panic.h>
#include <EosSdk/types.h>

namespace eos {

ip_prefix_t::ip_prefix_t(addr_family_t af, void const * address) {
   addr_family_ = af;
   if (af == addr_family_ipv4) {
      // copy the first 4 bytes from address for IPv6
      memcpy(&bytes_, address, sizeof(uint8_t)*4);
      prefix_length_ = 32;
   } else if (af == addr_family_ipv6) {
      memcpy(&bytes_, address, sizeof(bytes_));
      prefix_length_ = 128;
   } else {
      // If the user hasn't specified either v4 or v6, panic now
      panic("the address_family must be set to ipv4 or ipv6");
   }
}

ip_prefix_t::ip_prefix_t(addr_family_t af, void const * address, int prefix_length) {
   prefix_length_ = prefix_length;
   // copy the address from the argument
   if (af == addr_family_ipv4) {
      memcpy(&bytes_, address, sizeof(uint8_t)*4);
   } else if (af == addr_family_ipv6) {
      memcpy(&bytes_, address, sizeof(bytes_));
   }
}

// IPv4 address constructor only. prefix length is 32
ip_prefix_t::ip_prefix_t(uint32_t address) {
   addr_family_ = addr_family_ipv4;
   prefix_length_ = 32;
   memset(bytes_, 0, sizeof(bytes_));
   bytes_[0] = (address >> 0) & 0xFF;
   bytes_[1] = (address >> 8) & 0xFF;
   bytes_[2] = (address >> 16) & 0xFF;
   bytes_[3] = (address >> 24) & 0xFF;
}

// Mutators
// void
// ip_prefix_t::address_is(uint32_t) {
//    memcpy(&bytes_, address, sizeof(uint8_t)*4);
// }

void
ip_prefix_t::address_is(addr_family_t af, void const * address) {
   addr_family_ = af;
   if (af == addr_family_ipv4) {
      memcpy(&bytes_, address, sizeof(uint8_t)*4);
   } else if (af == addr_family_ipv6) {
      memcpy(&bytes_, address, sizeof(bytes_));
   }
}

void
ip_prefix_t::prefix_length_is(int prefix_length) {
   switch (addr_family_) {
    case addr_family_ipv4:
      if (prefix_length < 0 || prefix_length > 32) {
         panic("invalid prefix length");
      }
      break;
    case addr_family_ipv6:
      if (prefix_length < 0 || prefix_length > 32) {
         panic("invalid prefix length");
      }
      break;
   }
   prefix_length_ = prefix_length;
}

// Accessors

// Return an array of uint8_t bytes for the IP address (v4 or v6)
void const * ip_prefix_t::address() {
   return (void const *)bytes_;
}

// IPv4 address as a uint32_t. panic() called if address_family not ipv4
uint32_t ip_prefix_t::addressV4() {
   uint32_t v4addr = 0;
   if (addr_family_ == addr_family_ipv4) {
      v4addr = ( bytes_[3] << 24 | bytes_[2] << 16 | bytes_[1] << 8 |
                 bytes_[0] << 0);
   } else {
      panic("invalid address family to call addressV4");
   }
   return v4addr;
}

addr_family_t
ip_prefix_t::addr_family() {
   return addr_family_t(addr_family_);
}

int ip_prefix_t::prefix_length() {
   return prefix_length_;
}


};
