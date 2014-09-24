// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_ARESOLVE_H
#define EOS_INLINE_ARESOLVE_H

namespace eos {

inline aresolve_mgr * aresolve_handler::get_aresolve_mgr() const {
   return mgr_;
}

}

#endif // EOS_INLINE_ARESOLVE_H
