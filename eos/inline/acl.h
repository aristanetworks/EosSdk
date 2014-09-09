// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_ACL_H
#define EOS_INLINE_ACL_H

namespace eos {


inline acl_mgr * acl_handler::get_acl_mgr() const {
   return mgr_;
}

}  // end namespace eos

#endif // EOS_INLINE_ACL_H
