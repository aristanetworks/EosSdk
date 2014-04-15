// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_SDK_H
#define EOS_INLINE_SDK_H

namespace eos {

inline intf_mgr * sdk::get_intf_mgr() {
   if (!intf_mgr_) {
      init_intf_mgr();
   }
   return intf_mgr_;
}

}

#endif // EOS_INLINE_SDK_H
