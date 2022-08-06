// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_SDK_H
#define EOS_TYPES_SDK_H

#include <eos/base.h>
#include <memory>
#include <sstream>

namespace eos {

/** Enums for Manager mode type. */
enum mgr_mode_type_t {
   /** Reader without notifications. */
   MODE_TYPE_READ_ONLY,
   /** Reader with notifications. */
   MODE_TYPE_READ_NOTIFYING,
   /** Writer, manager can read and write state. */
   MODE_TYPE_WRITE,
};
/** Appends a string representation of enum mgr_mode_type_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const mgr_mode_type_t & enum_val);
}

#endif // EOS_TYPES_SDK_H
