// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_HAM_H
#define EOS_INLINE_HAM_H

namespace eos{

inline ham_mgr * ham_handler::get_ham_mgr() const {
   return mgr_;
}

}

#endif // EOS_INLINE_HAM_H
