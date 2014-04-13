// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_MAC_TABLE_H
#define EOS_INLINE_MAC_TABLE_H

namespace eos {

inline
mac_entry_t::mac_entry_t() : address_(), intf_() {
}

inline
mac_entry_t::mac_entry_t(eth_addr_t address, intf_id_t intf)
   : address_(address), intf_(intf) {
}

inline eth_addr_t
mac_entry_t::eth_addr() const {
   return address_;
}

inline intf_id_t
mac_entry_t::intf() const {
   return intf_;
}

inline bool
mac_entry_t::operator!() const {
   return !address_ && !intf_;
}

}

#endif // EOS_INLINE_MAC_TABLE_H
