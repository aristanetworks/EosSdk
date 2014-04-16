// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_SDK_H
#define EOS_INLINE_SDK_H

namespace eos {

inline directflow_mgr * sdk::get_directflow_mgr() {
   if (!directflow_mgr_) {
      init_directflow_mgr();
   }
   return directflow_mgr_;
}

inline eth_intf_mgr * sdk::get_eth_intf_mgr() {
   if (!eth_intf_mgr_) {
      init_eth_intf_mgr();
   }
   return eth_intf_mgr_;
}

inline eth_phy_intf_mgr * sdk::get_eth_phy_intf_mgr() {
   if (!eth_phy_intf_mgr_) {
      init_eth_phy_intf_mgr();
   }
   return eth_phy_intf_mgr_;
}

inline intf_mgr * sdk::get_intf_mgr() {
   if (!intf_mgr_) {
      init_intf_mgr();
   }
   return intf_mgr_;
}

}

#endif // EOS_INLINE_SDK_H
