// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_IP_H
#define EOS_IP_H

#include <string>
#include <eos/base.h>

namespace eos {

typedef enum addr_family_e {
   addr_family_null,
   addr_family_ipv4,
   addr_family_ipv6
} addr_family_t;

class ip_prefix_t {
 public:

   ip_prefix_t(addr_family_t, void const * address); // address gets copied.
   ip_prefix_t(addr_family_t, void const * address, int prefix_length);
   explicit ip_prefix_t(uint32_t); // IPv4 only, network byte order.
   addr_family_t addr_family();
   void const * address();
   uint32_t addressV4();
   std::string to_string() const;  // returns "10.2.3.4/24", "::1" or "::1/128", etc
   void address_is(uint32_t); // also sets addr_family to IPv4.
   void address_is(addr_family_t, void const *);
   int prefix_length();
   void prefix_length_is(int);

 //=> private:
   uint8_t bytes_[16];
   uint8_t addr_family_;   // addr_family_t in one byte.
   uint8_t prefix_length_;
};

// An IP address is just an IP prefix whose prefix_length is 32 (128
// for v6).
typedef ip_prefix_t ip_addr_t;

// e.g., "10.1.2.0/24" or "fffe::0001/96"
bool parse_ip_prefix(char const *, ip_prefix_t * result);

// same as above but without the prefix.
bool parse_ip_addr(char const *, ip_addr_t * result);

};  // end namespace eos

#endif // EOS_IP_H
