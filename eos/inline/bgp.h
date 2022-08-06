// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_BGP_H
#define INLINE_BGP_H

namespace eos {

inline bgp_mgr * bgp_peer_handler::get_bgp_mgr() const {
   return mgr_;
}

}  // end namespace eos

#endif // INLINE_BGP_H

