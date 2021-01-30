// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_L1_SOURCE_H
#define EOS_INLINE_L1_SOURCE_H

#include <eos/panic.h>

namespace eos {

inline l1_source_mgr * l1_source_handler::get_l1_source_mgr() const {
   return mgr_;
}

}

#endif // EOS_INLINE_L1_SOURCE_H
