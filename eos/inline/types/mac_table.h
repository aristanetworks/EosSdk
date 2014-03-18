// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MAC_TABLE_H
#define EOS_INLINE_TYPES_MAC_TABLE_H

namespace eos {

// Default constructor.
inline mac_entry_t::mac_entry_t() :
      eth_addr_(), intf_() {
}

inline mac_entry_t::mac_entry_t(eth_addr_t eth_addr, intf_id_t intf) :
      eth_addr_(eth_addr), intf_(intf) {
}

inline eth_addr_t
mac_entry_t::eth_addr() const {
   return eth_addr_;
}

inline intf_id_t
mac_entry_t::intf() const {
   return intf_;
}

inline bool
mac_entry_t::operator!() const {
   return !eth_addr_ && !intf_;
}

inline std::string
mac_entry_t::to_string() const {
   std::ostringstream ss;
   ss << "mac_entry_t(";
   ss << "eth_addr=" << eth_addr_.to_string();
   ss << ", intf=" << intf_.to_string();
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const mac_entry_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_MAC_TABLE_H
