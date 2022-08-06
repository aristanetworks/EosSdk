// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/ip.h"
#include <arpa/inet.h>
#include <string.h>

namespace eos {

// Take an address family and an array of 4 (v4) or 16 (v6) uint8_t's.
// Representation compatible to Linux's sockaddr_in6.sin6_addr (i.e., __be8[16]).
// NOTE: 'address' is in network byte order for both IPv4 and IPv6 as per Linux and
// Arnet.
ip_addr_t::ip_addr_t(af_t af, uint8_t const * addr) {
   af_ = af;
   memcpy(&addr_, addr, af_ == AF_IPV4 ? 4 : 16);
}

// Construct from a Linux in_addr (IPv4).
ip_addr_t::ip_addr_t(in_addr const & addr) {
   af_ = AF_IPV4;
   memcpy(&addr_, &addr, sizeof(addr));
}

// Construct from a Linux in6_addr (IPv6).
ip_addr_t::ip_addr_t(in6_addr const & addr) {
   // Linux in.h in_addr is in network byte order, no conversion required
   af_ = AF_IPV6;
   memcpy(&addr_, &addr, sizeof(addr));
}

bool
ip_addr_t::operator==(ip_addr_t const & other) const {
   
   if (af_ != other.af_) {
      return false;
   }
   return memcmp(addr_.bytes, other.addr_.bytes, af_ == AF_IPV4 ? 4 : 16) == 0;
   
}

bool
ip_addr_t::operator<(ip_addr_t const & other) const {
   
   if(af_ < other.af_) return true;
   if(af_ != other.af_) return false;
   return memcmp(addr_.bytes, other.addr_.bytes, af_ == AF_IPV4 ? 4 : 16) < 0;
   
}



bool
parse_ip_addr(char const * addr, ip_addr_t * result) {
   
   struct in_addr ipv4;
   struct in6_addr ipv6;
   if (!inet_pton(AF_INET, addr, &ipv4)) {
      if (!inet_pton(AF_INET6, addr, &ipv6)) {
         return false;
      }  else {
         result->af_ = AF_IPV6;
         for (int i=0; i < 16; i++) {
            result->addr_.bytes[i] = uint32_t(ipv6.s6_addr[i]);
         }
      }
   } else {
      result->af_ = AF_IPV4;
      result->addr_.words[0] = ipv4.s_addr;
   }
   return true;
   
}



bool
parse_ip_prefix(char const * addr, ip_prefix_t * result) {
   
   char* str = strdupa(addr);
   char* slash = strchr(str, '/');
   if (!slash) {
      return false;
   }
   ip_addr_t ipa;
   *slash = 0;
   if (!parse_ip_addr(str, &ipa)) {
      panic(invalid_argument_error("ip_prefix_t",
                                   "found no IPv4 or IPV6 address"));
   }
   switch (ipa.af()) {
    case AF_IPV4:
      result->addr_ = ip_addr_t(AF_IPV4, ipa.addr());
      result->prefix_length_ = atoi(slash+1);
      break;
    case AF_IPV6:
      result->addr_ = ip_addr_t(AF_IPV6, ipa.addr());
      result->prefix_length_ = atoi(slash+1);
     break;
     default:
        panic(invalid_argument_error("ip_prefix_t",
                                     "found ipv7 ;-)"));
   }
   return true;
   
}




static inline std::string address_overlap_error_msg(ip_addr_mask_t const & addr) {
   std::stringstream str;
   str << "Address " << addr.to_string() << " overlaps with an already configured"
      " address";
   return str.str();
}



address_overlap_error::address_overlap_error(ip_addr_mask_t const & addr) noexcept :
      configuration_error(address_overlap_error_msg(addr)), addr_(addr) {
   
}


}
