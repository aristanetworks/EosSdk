// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_SDK_HASH_MIX
#define EOS_SDK_HASH_MIX

#include <eos/base.h>

namespace eos {

/**
 * This is a helper class for incrementally-computed implementation of Bob
 * Jenkins' one-at-a-time hash, in C++.  It's needed in hash function.
 */

class EOS_SDK_PUBLIC hash_mix {
 public:
   hash_mix();
   uint32_t result() const;

   void mix(bool val);
   void mix(double val);
   void mix(float val);

   void mix(uint8_t val);
   void mix(uint16_t val);
   void mix(uint32_t val);
   void mix(uint64_t val);

   void mix(int8_t val);
   void mix(int16_t val);
   void mix(int32_t val);
   void mix(int64_t val);

   void mix(std::string const & val);

   // Mix enums
   template< typename T >
   typename std::enable_if< std::is_enum< T >::value >::type mix(T const & t) {
      mix(static_cast< typename std::underlying_type< T >::type >(t));
   }

   // Mix scalar types like long not explicitly listed above.
   template< typename T >
   typename std::enable_if< std::is_integral< T >::value >::type mix(T const & t) {
      mix_bytes((uint8_t *) &t, sizeof(t));
   }

   // Mix EosSdk types with mix_me method.
   template< typename T >
   typename std::enable_if< !std::is_integral< T >::value &&
                            !std::is_enum< T >::value >::type mix(T const & t) {
      t.mix_me(*this);
   }

   // Mix an array of bytes.
   void mix_bytes(uint8_t const *key, int len);

  private:
   uint32_t val_;
};

}

#include <eos/inline/hash_mix.h>

#endif
