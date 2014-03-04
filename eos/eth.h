// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ETH_H
#define EOS_ETH_H

#include <string>
#include <stddef.h>
#include <eos/base.h>

namespace eos {

/**
 * An Ethernet address.
 */
class EOS_SDK_PUBLIC eth_addr_t {
 public:
   eth_addr_t();  // Default constructor
   // Copy constructor and assignment operator implicitly declared.

   /**
    * Constructs an address from a char *.
    * Supported formats are xx:xx:xx:xx:xx:xx, xx-xx-xx-xx-xx-xx,
    * or xxxx.xxxx.xxxx
    */
   explicit eth_addr_t(char const * addr);
   /**
    * Constructs an address from a std::string.
    * Supported formats are xx:xx:xx:xx:xx:xx, xx-xx-xx-xx-xx-xx,
    * or xxxx.xxxx.xxxx
    */
   explicit eth_addr_t(std::string const & addr);
   /// Constructs an address from the 6 bytes that make it up.
   eth_addr_t(uint8_t byte0, uint8_t byte1, uint8_t byte2,
              uint8_t byte3, uint8_t byte4, uint8_t byte5);
   /// Constructs an address from a byte array. The array will be copied.
   explicit eth_addr_t(uint8_t const bytes[6]);

   /// String representation of a Ethernet address, e.g "xx:xx:xx:xx:xx"
   std::string to_string() const;

   // Only the default MAC address (all zeros) evaluates to false.
   bool operator!() const;
   bool operator==(eth_addr_t const & other) const;
   bool operator!=(eth_addr_t const & other) const;
   operator bool() const;

   /// Returns the given byte from the address
   uint8_t byte(int index) const;
   /// Copies the bytes of the Ethernet address to the given address
   void bytes(void *) const;

 private:
   uint8_t bytes_[6];
};

}

#include <eos/inline/eth.h>

#endif // EOS_ETH_H
