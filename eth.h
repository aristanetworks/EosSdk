// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ETH_H
#define EOS_ETH_H

#include <string>
#include <stddef.h>
#include <eos/base.h>

#include <Arnet/EthAddr.h> //= eos_internal

namespace eos {

class EOS_SDK_PUBLIC eth_addr_t {
 public:
   // Default constructor
   eth_addr_t();
   // Construct an address from one of three string forms:
   // xx:xx:xx:xx:xx:xx, xx-xx-xx-xx-xx-xx, or xxxx.xxxx.xxxx
   explicit eth_addr_t(char const *name);
   eth_addr_t(const Arnet::EthAddr &); //= eos_internal

   std::string to_string() const;

   bool operator !() const;
   bool operator==(eth_addr_t const & other);
   bool operator!=(eth_addr_t const & other);
   Arnet::EthAddr ethAddr_; //= hide

 //=> private:
   //=> uint32_t words_[3];

};

};


#endif // EOS_ETH_H
