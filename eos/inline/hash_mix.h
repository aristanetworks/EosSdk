// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_HASH_MIX_H
#define INLINE_HASH_MIX_H

#include <string>

namespace eos {

inline hash_mix::hash_mix() : val_(0) {}

inline void hash_mix::mix(bool val) {
   mix_bytes((uint8_t const *)&val, sizeof(val));
}

inline void hash_mix::mix(double val) {
   mix_bytes((uint8_t const *)&val, sizeof(val));
}

inline void hash_mix::mix(float val) {
   mix_bytes((uint8_t const *)&val, sizeof(val));
}

inline void hash_mix::mix(uint8_t val) {
   mix_bytes((uint8_t const *)&val, sizeof(val));
}

inline void hash_mix::mix(uint16_t val) {
   mix_bytes((uint8_t const *)&val, sizeof(val));
}

inline void hash_mix::mix(uint32_t val) {
   mix_bytes((uint8_t const *)&val, sizeof(val));
}

inline void hash_mix::mix(uint64_t val) {
   mix_bytes((uint8_t const *)&val, sizeof(val));
}

inline void hash_mix::mix(int8_t val) {
   mix_bytes((uint8_t const *)&val, sizeof(val));
}

inline void hash_mix::mix(int16_t val) {
   mix_bytes((uint8_t const *)&val, sizeof(val));
}

inline void hash_mix::mix(int32_t val) {
   mix_bytes((uint8_t const *)&val, sizeof( val ));
}

inline void hash_mix::mix(int64_t val) {
   mix_bytes((uint8_t const *)&val, sizeof(val));
}

inline void hash_mix::mix(std::string const & val) {
   mix_bytes((uint8_t const *)val.c_str(), val.size());
}

inline void hash_mix::mix_bytes(uint8_t const * key, int len) {
   // The incremental mix step
   for(int i = 0; i < len; ++i) {
      val_ += key[i];
      val_ += val_ << 10;
      val_ ^= val_ >> 6;
   }
}

inline uint32_t hash_mix::result() const {
   uint32_t seed = val_;
   // Do the final mixing step
   seed += seed << 3;
   seed ^= seed >> 11;
   seed += seed << 15;
   return seed;
}

}

#endif // INLINE_HASH_MIX_H
