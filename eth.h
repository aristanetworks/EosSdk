// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ETH_H
#define EOS_ETH_H

#include <stddef.h>
#include <eos/types.h>

#include <Arnet/EthAddr.h> //= hide

namespace eos {

class eth_addr_t {
 public:
   explicit eth_addr_t(char const *name);

   void to_string(char *namebuf, size_t namebuf_size);

   bool operator==(eth_addr_t const & other);
   bool operator!=(eth_addr_t const & other);
   void validate(); //= hide
   Arnet::EthAddr ethAddr_; //= hide

 //=> private:
   //=> uint32_t[3] words_;

};

};


#endif // EOS_ETH_H
