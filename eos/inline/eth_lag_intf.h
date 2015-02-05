// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_ETH_LAG_INTF_H
#define INLINE_ETH_LAG_INTF_H

namespace eos {

inline eth_lag_intf_mgr * eth_lag_intf_handler::get_eth_lag_intf_mgr() const {
   return mgr_;
}

}

#endif // INLINE_ETH_LAG_INTF_H
