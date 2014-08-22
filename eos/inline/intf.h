// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_INTF_H
#define EOS_INLINE_INTF_H

#include <eos/panic.h>

namespace eos {

inline intf_mgr * intf_handler::get_intf_mgr() const {
   return mgr_;
}

}

#endif // EOS_INLINE_INTF_H
