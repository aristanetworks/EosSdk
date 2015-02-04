// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_NEXTHOP_GROUP_H
#define EOS_INLINE_NEXTHOP_GROUP_H

namespace eos {

inline nexthop_group_mgr * nexthop_group_handler::get_nexthop_group_mgr() const {
   return mgr_;
}

}

#endif // EOS_INLINE_NEXTHOP_GROUP_H
