// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_LLDP_H
#define EOS_INLINE_LLDP_H

namespace eos {

inline lldp_mgr * lldp_handler::get_lldp_mgr() const {
   return mgr_;
}

}

#endif // EOS_INLINE_LLDP_H
