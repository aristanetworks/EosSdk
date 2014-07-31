// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_SDK_HASH_MIX
#define EOS_SDK_HASH_MIX

#include <iostream>
#include <functional>
#include <string>

namespace eos {

/**
 * This is a helper class for incrementally-computed implementation of Bob
 * Jenkins' one-at-a-time hash, in C++.  It's needed in hash function.
 */

class EOS_SDK_PUBLIC hash_mix {
 public:
   static uint32_t mix( uint8_t * key, int len, uint32_t seed ) {
      // The incremental mix step
      for (int i = 0; i < len; ++i) {
         seed += key[i];
         seed += seed << 10;
         seed ^= seed >> 6;
      }
      return seed;
   }

   static uint32_t final_mix( uint32_t seed ) {
      // Do the final mixing step
      seed += seed << 3;
      seed ^= seed >> 11;
      seed += seed << 15;
      return seed;
   }
};

}

#endif
