// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ETH_H
#define EOS_ETH_H

#include <string>
#include <stddef.h>
#include <eos/base.h>

namespace eos {

class EOS_SDK_PUBLIC eth_addr_t {
 public:
   eth_addr_t();  // Default constructor
   // Copy constructor and assignment operator implicitly declared.

   // Construct an address from one of three string forms:
   // xx:xx:xx:xx:xx:xx, xx-xx-xx-xx-xx-xx, or xxxx.xxxx.xxxx
   explicit eth_addr_t(char const * addr);
   explicit eth_addr_t(std::string const & addr);
   // Construct an address from the 3 bytes that make it up.
   eth_addr_t(uint8_t byte0, uint8_t byte1, uint8_t byte2,
              uint8_t byte3, uint8_t byte4, uint8_t byte5);
   // Same constructor but with an array.  The array will be copied.
   explicit eth_addr_t(uint8_t const bytes[6]);

   std::string to_string() const;

   // Only the default MAC address (all zeros) evaluates to false.
   bool operator!() const;
   bool operator==(eth_addr_t const & other) const;
   bool operator!=(eth_addr_t const & other) const;
   operator bool() const;

   uint8_t byte(int index) const;
   void bytes(void *) const;

 private:
   uint8_t bytes_[6];
};

}

#include <eos/inline/eth.h>

#endif // EOS_ETH_H
