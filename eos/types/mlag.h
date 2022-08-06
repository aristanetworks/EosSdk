// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_MLAG_H
#define EOS_TYPES_MLAG_H

#include <memory>

namespace eos {

enum mlag_state_t {
   MLAG_STATE_UNKNOWN,
   MLAG_STATE_DISABLED,
   MLAG_STATE_INACTIVE,
   MLAG_STATE_PRIMARY,
   MLAG_STATE_SECONDARY,
};
/** Appends a string representation of enum mlag_state_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const mlag_state_t & enum_val);
}

#endif // EOS_TYPES_MLAG_H
