// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_BGP_PATH_H
#define INLINE_BGP_PATH_H

namespace eos {

inline bgp_path_mgr * bgp_path_handler::get_bgp_path_mgr() const {
   return mgr_;
}

}  // end namespace eos

#endif // INLINE_BGP_PATH_H

