// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_NEIGHBOR_TABLE_H
#define EOS_INLINE_TYPES_NEIGHBOR_TABLE_H

namespace eos {

// Default constructor.
inline neighbor_entry_t::neighbor_entry_t() :
      ip_addr_(), eth_addr_(), entry_type_(NEIGHBOR_ENTRY_TYPE_DYNAMIC) {
}

inline neighbor_entry_t::neighbor_entry_t(ip_addr_t ip_addr, eth_addr_t eth_addr, 
                                   neighbor_entry_type_t entry_type) :
      ip_addr_(ip_addr), eth_addr_(eth_addr), entry_type_(entry_type) {
}

inline ip_addr_t
neighbor_entry_t::ip_addr() const {
   return ip_addr_;
}

inline eth_addr_t
neighbor_entry_t::eth_addr() const {
   return eth_addr_;
}

inline neighbor_entry_type_t
neighbor_entry_t::entry_type() const {
   return entry_type_;
}

inline std::string
neighbor_entry_t::to_string() const {
   std::ostringstream ss;
   ss << "neighbor_entry_t(";
   ss << "ip_addr=" << ip_addr_.to_string();
   ss << ", eth_addr=" << eth_addr_.to_string();
   ss << ", entry_type=" << entry_type_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const neighbor_entry_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_NEIGHBOR_TABLE_H
