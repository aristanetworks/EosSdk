// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_POLICY_H
#define EOS_INLINE_POLICY_H

namespace eos {

inline policy_map_mgr * policy_map_handler::get_policy_map_mgr() const {
   return mgr_;
}

} // namespace eos

#endif // EOS_INLINE_POLICY_H
