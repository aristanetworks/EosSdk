// Copyright (c) 2018 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_NEXTHOP_GROUP_TUNNEL_H
#define INLINE_NEXTHOP_GROUP_TUNNEL_H

namespace eos {

inline nexthop_group_tunnel_mgr *
nexthop_group_tunnel_handler::get_nexthop_group_tunnel_mgr() const {
   return mgr_;
}

}

#endif // INLINE_NEXTHOP_GROUP_TUNNEL_H

