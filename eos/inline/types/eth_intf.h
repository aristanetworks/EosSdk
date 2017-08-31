// Copyright (c) 2016 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ETH_INTF_H
#define EOS_INLINE_TYPES_ETH_INTF_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const switchport_mode_t & enum_val) {
   if (enum_val==SWITCHPORT_MODE_ACCESS) {
      os << "SWITCHPORT_MODE_ACCESS";
   } else if (enum_val==SWITCHPORT_MODE_TRUNK) {
      os << "SWITCHPORT_MODE_TRUNK";
   } else if (enum_val==SWITCHPORT_MODE_DOT1Q_TUNNEL) {
      os << "SWITCHPORT_MODE_DOT1Q_TUNNEL";
   } else if (enum_val==SWITCHPORT_MODE_TAP) {
      os << "SWITCHPORT_MODE_TAP";
   } else if (enum_val==SWITCHPORT_MODE_TOOL) {
      os << "SWITCHPORT_MODE_TOOL";
   } else if (enum_val==SWITCHPORT_MODE_ROUTED) {
      os << "SWITCHPORT_MODE_ROUTED";
   } else {
      os << "Unknown value";
   }
   return os;
}


}

#endif // EOS_INLINE_TYPES_ETH_INTF_H
