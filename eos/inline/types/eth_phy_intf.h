// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ETH_PHY_INTF_H
#define EOS_INLINE_TYPES_ETH_PHY_INTF_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const eth_link_speed_t & enum_val) {
   if (enum_val==LINK_SPEED_UNKNOWN) {
      os << "LINK_SPEED_UNKNOWN";
   } else if (enum_val==LINK_SPEED_10MBPS) {
      os << "LINK_SPEED_10MBPS";
   } else if (enum_val==LINK_SPEED_100MBPS) {
      os << "LINK_SPEED_100MBPS";
   } else if (enum_val==LINK_SPEED_1GBPS) {
      os << "LINK_SPEED_1GBPS";
   } else if (enum_val==LINK_SPEED_10GBPS) {
      os << "LINK_SPEED_10GBPS";
   } else if (enum_val==LINK_SPEED_40GBPS) {
      os << "LINK_SPEED_40GBPS";
   } else if (enum_val==LINK_SPEED_100GBPS) {
      os << "LINK_SPEED_100GBPS";
   } else {
      os << "Unknown value";
   }
   return os;
}


}

#endif // EOS_INLINE_TYPES_ETH_PHY_INTF_H
