// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_SDK_H
#define EOS_INLINE_TYPES_SDK_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const mgr_mode_type_t & enum_val) {
   if (enum_val==MODE_TYPE_READ_ONLY) {
      os << "MODE_TYPE_READ_ONLY";
   } else if (enum_val==MODE_TYPE_READ_NOTIFYING) {
      os << "MODE_TYPE_READ_NOTIFYING";
   } else if (enum_val==MODE_TYPE_WRITE) {
      os << "MODE_TYPE_WRITE";
   } else {
      os << "Unknown value";
   }
   return os;
}


}

#endif // EOS_INLINE_TYPES_SDK_H
