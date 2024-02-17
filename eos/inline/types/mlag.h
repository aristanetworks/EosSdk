// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MLAG_H
#define EOS_INLINE_TYPES_MLAG_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const mlag_state_t & enum_val) {
   if (enum_val==MLAG_STATE_UNKNOWN) {
      os << "MLAG_STATE_UNKNOWN";
   } else if (enum_val==MLAG_STATE_DISABLED) {
      os << "MLAG_STATE_DISABLED";
   } else if (enum_val==MLAG_STATE_INACTIVE) {
      os << "MLAG_STATE_INACTIVE";
   } else if (enum_val==MLAG_STATE_PRIMARY) {
      os << "MLAG_STATE_PRIMARY";
   } else if (enum_val==MLAG_STATE_SECONDARY) {
      os << "MLAG_STATE_SECONDARY";
   } else {
      os << "Unknown value";
   }
   return os;
}

}

#endif // EOS_INLINE_TYPES_MLAG_H
