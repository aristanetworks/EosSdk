// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_IP_IMPL_H
#define EOS_TYPES_IP_IMPL_H

#include <arpa/inet.h>
#include <assert.h>
#include <eos/base.h>
#include <eos/exception.h>
#include <eos/hash_mix.h>
#include <eos/panic.h>
#include <memory>
#include <netinet/in.h>
#include <sstream>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

namespace eos {



/**
 * An IP address with a subnet mask.
 *
 * This allows for contiguous subnet masks only for IPv4 and IPv6 addresses.
 *
 * IPv6 addresses in EOS only support contiguous masks, so for IPv6 addresses
 * mask() provides the same value as mask_length().
 */
class EOS_SDK_PUBLIC ip_addr_mask_impl_t {
 public:
   ip_addr_mask_impl_t();
   ip_addr_mask_impl_t(ip_addr_t const & addr, uint8_t mask_length);

   /** Getter for 'addr': the address/mask's IP address. */
   ip_addr_t addr() const;

   /** Getter for 'mask_length': the bit mask length, e.g., 24. */
   uint8_t mask_length() const;

   /** The address family of the prefix. */
   af_t af() const;
   /**
    * The bit mask itself, e.g., 0xFFFFFF00 (IPv4). For IPv6, same as
    * mask_length().
    */
   uint32_be_t mask() const;
   /** The IP address and mask as a string, e.g., "192.0.2.1/0xFFFFFF00". */
   std::string to_string() const;
   bool operator==(ip_addr_mask_impl_t const & other) const;
   bool operator!=(ip_addr_mask_impl_t const & other) const;
   bool operator<(ip_addr_mask_impl_t const & other) const;
   /** The hash function for type ip_addr_mask_t. */
   uint32_t hash() const;
   /** The hash mix function for type ip_addr_mask_t. */
   void mix_me(hash_mix & h) const;
   /**
    * A utility stream operator that adds a string representation of ip_addr_mask_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const ip_addr_mask_impl_t& obj);

 private:
   ip_addr_t addr_;
   uint8_t mask_length_;
};

}

#endif // EOS_TYPES_IP_IMPL_H
