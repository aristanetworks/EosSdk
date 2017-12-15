// Copyright (c) 2017 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_MACSEC_H
#define INLINE_MACSEC_H

namespace eos {

inline macsec_mgr * macsec_handler::get_macsec_mgr() const {
   return mgr_;
}

}


#endif // INLINE_MACSEC_H

