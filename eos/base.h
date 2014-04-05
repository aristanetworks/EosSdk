// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_BASE_H
#define EOS_BASE_H

#include <stdint.h> // for uint8_t, uint16_t, uint32_t, uint64_t, etc.

/**
 * @mainpage
 * @section s_intro The Arista EOS Software Development Kit
 */

/**
 * Arista EOS Software Development Kit
 */
namespace eos {

// Big endian (network byte order) hinted forms of uint16_t/uint32_t/uint64_t
/// A uint16_t in big endian (network byte) order
typedef uint16_t uint16_be_t;
/// A uint32_t in big endian (network byte) order
typedef uint32_t uint32_be_t;
/// A uint64_t in big endian (network byte) order
typedef uint64_t uint64_be_t;

/// A decimal number of seconds, used for timestamps and durations
typedef double seconds_t;

#if defined(__GNUC__) && !defined(SWIG)
#define EOS_SDK_PUBLIC __attribute__ ((visibility ("default")))
#define EOS_SDK_PRIVATE __attribute__ ((visibility ("hidden")))
// Things we need to expose but that aren't part of the API.
// TODO(tsuna): Why can't we make this visibility protected?
#define EOS_SDK_INTERNAL __attribute__ ((visibility ("default")))
#define EOS_SDK_NORETURN __attribute__ ((noreturn))
#define EOS_SDK_DEPRECATED __attribute__ ((deprecated))
#else
// SWIG doesn't understand __attribute__ overload macros
#define EOS_SDK_PUBLIC
#define EOS_SDK_PRIVATE
#define EOS_SDK_INTERNAL
#define EOS_SDK_NORETURN
#define EOS_SDK_DEPRECATED
#endif

#define EOS_SDK_DISALLOW_COPY_CTOR(ClassName) \
 private: \
   ClassName(ClassName const &) EOS_SDK_PRIVATE; \
   ClassName & operator=(ClassName const &) EOS_SDK_PRIVATE;

}

#endif // EOS_BASE_H
