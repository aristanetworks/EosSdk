// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_SYSTEM_H
#define EOS_INLINE_SYSTEM_H

namespace eos {

inline system_mgr * system_handler::get_system_mgr() const {
   return mgr_;
}

}

#endif // EOS_INLINE_SYSTEM_H
