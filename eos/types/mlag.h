// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_MLAG_H
#define EOS_TYPES_MLAG_H


namespace eos {

enum mlag_state_t {
   MLAG_STATE_UNKNOWN,
   MLAG_STATE_DISABLED,
   MLAG_STATE_INACTIVE,
   MLAG_STATE_PRIMARY,
   MLAG_STATE_SECONDARY,
};

}

#endif // EOS_TYPES_MLAG_H
