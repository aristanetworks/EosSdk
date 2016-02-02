// Copyright (c) 2016 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_MPLS_ROUTE_H
#define INLINE_MPLS_ROUTE_H

namespace eos {

inline mpls_route_mgr *mpls_route_handler::get_mpls_route_mgr() const {
   return mgr_;
}

}  // end namespace eos

#endif // INLINE_MPLS_ROUTE_H
