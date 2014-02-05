// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_BASE_H
#define EOS_BASE_H

#include <cstdint> // for uint8_t, uint16_t, uint32_t, uint64_t, etc.

namespace eos {

// Big endian (network byte order) hinted forms of uint16_t/uint32_t/uint64_t
typedef uint16_t uint16_be_t;
typedef uint32_t uint32_be_t;
typedef uint64_t uint64_be_t;

typedef double seconds_t;

#if defined(__GNUC__) && !defined(SWIG)
#define EOS_SDK_PUBLIC __attribute__ ((visibility ("default")))
#define EOS_SDK_PRIVATE __attribute__ ((visibility ("hidden")))
// Things we need to expose but that aren't part of the API.
// TODO(tsuna): Why can't we make this visibility protected?
#define EOS_SDK_INTERNAL __attribute__ ((visibility ("default")))
#else
// SWIG doesn't understand __attribute__ overload macros
#define EOS_SDK_PUBLIC
#define EOS_SDK_PRIVATE
#define EOS_SDK_INTERNAL
#endif

#define EOS_SDK_DISALLOW_COPY_CTOR(ClassName) \
 private: \
   ClassName(ClassName const &) EOS_SDK_PRIVATE; \
   ClassName & operator=(ClassName const &) EOS_SDK_PRIVATE;

}

#endif // EOS_BASE_H
