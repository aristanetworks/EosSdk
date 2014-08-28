// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_HASH_MIX_H
#define INLINE_HASH_MIX_H

namespace eos {

inline uint32_t hash_mix::mix( uint8_t * key, int len, uint32_t seed ) {
   // The incremental mix step
   for (int i = 0; i < len; ++i) {
      seed += key[i];
      seed += seed << 10;
      seed ^= seed >> 6;
   }
   return seed;
}

inline uint32_t hash_mix::final_mix( uint32_t seed ) {
   // Do the final mixing step
   seed += seed << 3;
   seed ^= seed >> 11;
   seed += seed << 15;
   return seed;
}

}

#endif // INLINE_HASH_MIX_H
