// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_UTILITY_H
#define INLINE_UTILITY_H

namespace eos {

inline std::ostream &operator<<(std::ostream &os, uint8_t v) {
   return os << static_cast<uint32_t>(v);
}

}

#endif // INLINE_UTILITY_H
