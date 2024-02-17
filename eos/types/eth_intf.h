// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_ETH_INTF_H
#define EOS_TYPES_ETH_INTF_H

#include <memory>

namespace eos {

/** The mode of operation of a switch port. */
enum switchport_mode_t {
   /** Interface only has access to its access VLAN. */
   SWITCHPORT_MODE_ACCESS,
   /** Interface is in 802.1q mode ("trunk mode"). */
   SWITCHPORT_MODE_TRUNK,
   /** Interface is in 802.1ad mode ("QinQ mode"). */
   SWITCHPORT_MODE_DOT1Q_TUNNEL,
   /** Interface is in tap mode ("span mode"). */
   SWITCHPORT_MODE_TAP,
   /** Interface is a tool port (egress for a tap). */
   SWITCHPORT_MODE_TOOL,
   /** Interface is routed ("no switchport"). */
   SWITCHPORT_MODE_ROUTED,
};
/**
 * Appends a string representation of enum switchport_mode_t value to the ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const switchport_mode_t & enum_val);
}

#endif // EOS_TYPES_ETH_INTF_H
