// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_NEIGHBOR_TABLE_H
#define EOS_INLINE_TYPES_NEIGHBOR_TABLE_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const neighbor_entry_type_t & enum_val) {
   if (enum_val==NEIGHBOR_ENTRY_TYPE_NULL) {
      os << "NEIGHBOR_ENTRY_TYPE_NULL";
   } else if (enum_val==NEIGHBOR_ENTRY_TYPE_DYNAMIC) {
      os << "NEIGHBOR_ENTRY_TYPE_DYNAMIC";
   } else if (enum_val==NEIGHBOR_ENTRY_TYPE_STATIC) {
      os << "NEIGHBOR_ENTRY_TYPE_STATIC";
   } else {
      os << "Unknown value";
   }
   return os;
}



// Default constructor.
inline neighbor_key_t::neighbor_key_t() :
      ip_addr_(), intf_id_() {
}

inline neighbor_key_t::neighbor_key_t(ip_addr_t const & ip_addr) :
      ip_addr_(ip_addr), intf_id_() {
}

inline neighbor_key_t::neighbor_key_t(ip_addr_t const & ip_addr, intf_id_t intf_id) :
      ip_addr_(ip_addr), intf_id_(intf_id) {
}

inline ip_addr_t
neighbor_key_t::ip_addr() const {
   return ip_addr_;
}

inline intf_id_t
neighbor_key_t::intf_id() const {
   return intf_id_;
}

inline bool
neighbor_key_t::operator==(neighbor_key_t const & other) const {
   return ip_addr_ == other.ip_addr_ &&
          intf_id_ == other.intf_id_;
}

inline bool
neighbor_key_t::operator!=(neighbor_key_t const & other) const {
   return !operator==(other);
}

inline bool
neighbor_key_t::operator<(neighbor_key_t const & other) const {
   if(ip_addr_ != other.ip_addr_) {
      return ip_addr_ < other.ip_addr_;
   } else if(intf_id_ != other.intf_id_) {
      return intf_id_ < other.intf_id_;
   }
   return false;
}

inline uint32_t
neighbor_key_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&ip_addr_,
              sizeof(ip_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&intf_id_,
              sizeof(intf_id_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
neighbor_key_t::to_string() const {
   std::ostringstream ss;
   ss << "neighbor_key_t(";
   ss << "ip_addr=" << ip_addr_.to_string();
   ss << ", intf_id=" << intf_id_.to_string();
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const neighbor_key_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
inline neighbor_entry_t::neighbor_entry_t() :
      neighbor_key_(), eth_addr_(), entry_type_(NEIGHBOR_ENTRY_TYPE_DYNAMIC) {
}

inline neighbor_entry_t::neighbor_entry_t(neighbor_key_t const & neighbor_key, 
                                          eth_addr_t eth_addr, 
                                          neighbor_entry_type_t entry_type) :
      neighbor_key_(neighbor_key), eth_addr_(eth_addr), entry_type_(entry_type) {
}

inline neighbor_key_t
neighbor_entry_t::neighbor_key() const {
   return neighbor_key_;
}

inline eth_addr_t
neighbor_entry_t::eth_addr() const {
   return eth_addr_;
}

inline neighbor_entry_type_t
neighbor_entry_t::entry_type() const {
   return entry_type_;
}

inline bool
neighbor_entry_t::operator==(neighbor_entry_t const & other) const {
   return neighbor_key_ == other.neighbor_key_ &&
          eth_addr_ == other.eth_addr_ &&
          entry_type_ == other.entry_type_;
}

inline bool
neighbor_entry_t::operator!=(neighbor_entry_t const & other) const {
   return !operator==(other);
}

inline bool
neighbor_entry_t::operator<(neighbor_entry_t const & other) const {
   if(neighbor_key_ != other.neighbor_key_) {
      return neighbor_key_ < other.neighbor_key_;
   } else if(eth_addr_ != other.eth_addr_) {
      return eth_addr_ < other.eth_addr_;
   } else if(entry_type_ != other.entry_type_) {
      return entry_type_ < other.entry_type_;
   }
   return false;
}

inline uint32_t
neighbor_entry_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&neighbor_key_,
              sizeof(neighbor_key_t), ret);
   ret = hash_mix::mix((uint8_t *)&eth_addr_,
              sizeof(eth_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&entry_type_,
              sizeof(neighbor_entry_type_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
neighbor_entry_t::to_string() const {
   std::ostringstream ss;
   ss << "neighbor_entry_t(";
   ss << "neighbor_key=" << neighbor_key_;
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
