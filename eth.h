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
   // Construct an address from the 3 words that make it up.
   eth_addr_t(uint16_t word0, uint16_t word1, uint16_t word2);

   std::string to_string() const;

   // Only the default MAC address (all zeros) evaluates to false.
   bool operator!() const;
   bool operator==(eth_addr_t const & other) const;
   bool operator!=(eth_addr_t const & other) const;

   uint16_t word0() const {
      return words_[0];
   }

   uint16_t word1() const {
      return words_[1];
   }

   uint16_t word2() const {
      return words_[2];
   }

 private:
   uint16_t words_[3];
};

};


#endif // EOS_ETH_H
