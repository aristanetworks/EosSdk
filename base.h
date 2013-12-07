// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_BASE_H
#define EOS_BASE_H

#include <cstdint> // for uint8_t, uint16_t, uint32_t, uint64_t, etc.

// Big endian (network byte order) hinted forms of uint16_t/uint32_t
typedef uint16_t uint16_be_t;
typedef uint32_t uint32_be_t;

#if __GNUC__ < 4
// We could easily support other compilers but we don't need it right now.
#error You must use a supported compiler (GCC 4.x or above)
#endif

#define EOS_SDK_PUBLIC __attribute__ ((visibility ("default")))
#define EOS_SDK_PRIVATE __attribute__ ((visibility ("hidden")))
// Things we need to expose but that aren't part of the API.
// TODO(tsuna): Why can't we make this visibility protected?
#define EOS_SDK_INTERNAL __attribute__ ((visibility ("default")))

#endif // EOS_BASE_H
