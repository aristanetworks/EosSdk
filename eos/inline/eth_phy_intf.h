// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_ETH_PHY_INTF_H
#define EOS_INLINE_ETH_PHY_INTF_H

namespace eos {

inline eth_phy_intf_mgr * eth_phy_intf_handler::get_eth_phy_intf_mgr() const {
   return mgr_;
}

}

#endif // EOS_INLINE_ETH_PHY_INTF_H

