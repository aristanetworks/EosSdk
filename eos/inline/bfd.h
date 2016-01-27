// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_BFD_H
#define EOS_INLINE_BFD_H

namespace eos {

inline bfd_session_mgr *
bfd_session_handler::get_bfd_session_mgr() const {
   return mgr_;
}

} // end namespace eos

#endif // INLINE_BFD_H

