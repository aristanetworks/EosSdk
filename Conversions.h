// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOSSDK_CONVERSIONS_H
#define EOSSDK_CONVERSIONS_H

/**
 * Contains in-line conversions for commonly-used types.
 * This header is internal only.  Common value types like
 * interfaces, MAC addresses, IP types, can be added here
 * to easily go back and forth between the SDK types and
 * tacc types.
 */

#include <eos/intf.h>
#include <eos/ip.h>

#include <Arnet/IntfId.h>
#include <Arnet/Ip6Addr.h>
#include <Arnet/IpAddr.h>

namespace eos {

struct IntfIdHelper : public Arnet::IntfId {
   explicit IntfIdHelper(intf_id_t intfId) {
      intfIdIs(intfId.intfId_);
   }
};

static inline intf_id_t convert(Arnet::IntfId i) {
   return intf_id_t(i.intfId());
}


static inline Arnet::IntfId convert(intf_id_t i) {
   return IntfIdHelper(i);
}

// Hidden consturctors for conversions from TACC types
static inline ip_addr_t convert(Arnet::IpAddr const & other) {
   return ip_addr_t(other.value());  // ctor takes host byte order.
}

static inline ip_addr_t convert(Arnet::Ip6Addr const & other) {
   struct in6_addr ip6 {{{  // <-- extra braces to work around GCC bug 25137.
      other.u8(0), other.u8(1), other.u8(2), other.u8(3),
      other.u8(4), other.u8(5), other.u8(6), other.u8(7),
      other.u8(8), other.u8(9), other.u8(10), other.u8(11),
      other.u8(12), other.u8(13), other.u8(14), other.u8(15)
   }}};
   return ip_addr_t(ip6);
}

};

#endif // EOSSDK_CONVERSIONS_H
