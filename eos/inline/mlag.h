// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_MLAG_H
#define EOS_INLINE_MLAG_H

namespace eos {

inline mlag_mgr * mlag_handler::get_mlag_mgr() const {
   return mgr_;
}

}

#endif // EOS_INLINE_MLAG_H
