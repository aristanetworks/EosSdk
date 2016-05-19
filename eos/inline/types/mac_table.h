// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MAC_TABLE_H
#define EOS_INLINE_TYPES_MAC_TABLE_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const mac_entry_type_t & enum_val) {
   if (enum_val==MAC_ENTRY_NULL) {
      os << "MAC_ENTRY_NULL";
   } else if (enum_val==MAC_ENTRY_LEARNED_DYNAMIC) {
      os << "MAC_ENTRY_LEARNED_DYNAMIC";
   } else if (enum_val==MAC_ENTRY_LEARNED_SECURE) {
      os << "MAC_ENTRY_LEARNED_SECURE";
   } else if (enum_val==MAC_ENTRY_CONFIGURED_DYNAMIC) {
      os << "MAC_ENTRY_CONFIGURED_DYNAMIC";
   } else if (enum_val==MAC_ENTRY_CONFIGURED_SECURE) {
      os << "MAC_ENTRY_CONFIGURED_SECURE";
   } else if (enum_val==MAC_ENTRY_CONFIGURED_STATIC) {
      os << "MAC_ENTRY_CONFIGURED_STATIC";
   } else if (enum_val==MAC_ENTRY_PEER_DYNAMIC) {
      os << "MAC_ENTRY_PEER_DYNAMIC";
   } else if (enum_val==MAC_ENTRY_PEER_STATIC) {
      os << "MAC_ENTRY_PEER_STATIC";
   } else if (enum_val==MAC_ENTRY_PEER_SECURE) {
      os << "MAC_ENTRY_PEER_SECURE";
   } else if (enum_val==MAC_ENTRY_LEARNED_REMOTE) {
      os << "MAC_ENTRY_LEARNED_REMOTE";
   } else if (enum_val==MAC_ENTRY_CONFIGURED_REMOTE) {
      os << "MAC_ENTRY_CONFIGURED_REMOTE";
   } else if (enum_val==MAC_ENTRY_RECEIVED_REMOTE) {
      os << "MAC_ENTRY_RECEIVED_REMOTE";
   } else if (enum_val==MAC_ENTRY_PEER_LEARNED_REMOTE) {
      os << "MAC_ENTRY_PEER_LEARNED_REMOTE";
   } else if (enum_val==MAC_ENTRY_PEER_CONFIGURED_REMOTE) {
      os << "MAC_ENTRY_PEER_CONFIGURED_REMOTE";
   } else if (enum_val==MAC_ENTRY_PEER_RECEIVED_REMOTE) {
      os << "MAC_ENTRY_PEER_RECEIVED_REMOTE";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline mac_key_t::mac_key_t() :
      vlan_id_(), eth_addr_() {
}

inline mac_key_t::mac_key_t(vlan_id_t vlan_id, eth_addr_t const & eth_addr) :
      vlan_id_(vlan_id), eth_addr_(eth_addr) {
}

inline vlan_id_t
mac_key_t::vlan_id() const {
   return vlan_id_;
}

inline eth_addr_t
mac_key_t::eth_addr() const {
   return eth_addr_;
}

inline bool
mac_key_t::operator!() const {
   return !vlan_id_ && !eth_addr_;
}

inline bool
mac_key_t::operator==(mac_key_t const & other) const {
   return vlan_id_ == other.vlan_id_ &&
          eth_addr_ == other.eth_addr_;
}

inline bool
mac_key_t::operator!=(mac_key_t const & other) const {
   return !operator==(other);
}

inline bool
mac_key_t::operator<(mac_key_t const & other) const {
   if(vlan_id_ != other.vlan_id_) {
      return vlan_id_ < other.vlan_id_;
   } else if(eth_addr_ != other.eth_addr_) {
      return eth_addr_ < other.eth_addr_;
   }
   return false;
}

inline uint32_t
mac_key_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&vlan_id_,
              sizeof(vlan_id_t), ret);
   ret = hash_mix::mix((uint8_t *)&eth_addr_,
              sizeof(eth_addr_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
mac_key_t::to_string() const {
   std::ostringstream ss;
   ss << "mac_key_t(";
   ss << "vlan_id=" << vlan_id_;
   ss << ", eth_addr=" << eth_addr_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const mac_key_t& obj) {
   os << obj.to_string();
   return os;
}



inline mac_entry_t::mac_entry_t() :
      mac_key_(), intfs_(), persistent_(false) {
}

inline mac_entry_t::mac_entry_t(mac_key_t const & mac_key) :
      mac_key_(mac_key), intfs_(), persistent_(false) {
}

inline mac_entry_t::mac_entry_t(mac_key_t const & mac_key, intf_id_t intf) :
      mac_key_(mac_key), intfs_{intf}, persistent_(false) {
}

inline mac_entry_t::mac_entry_t(mac_key_t const & mac_key, 
                                std::set<intf_id_t> const & intfs) :
      mac_key_(mac_key), intfs_(intfs), persistent_(false) {
}

inline mac_entry_t::mac_entry_t(vlan_id_t vlan_id, eth_addr_t eth_addr) :
      mac_key_(mac_key_t(vlan_id, eth_addr)), intfs_(), persistent_(false) {
}

inline mac_entry_t::mac_entry_t(eth_addr_t eth_addr, intf_id_t intf) :
      mac_key_(mac_key_t(vlan_id_t(), eth_addr)), intfs_{intf}, persistent_(false) {
}

inline mac_key_t
mac_entry_t::mac_key() const {
   return mac_key_;
}

inline void
mac_entry_t::mac_key_is(mac_key_t const & mac_key) {
   mac_key_ = mac_key;
}

inline std::set<intf_id_t> const &
mac_entry_t::intfs() const {
   return intfs_;
}

inline void
mac_entry_t::intfs_is(std::set<intf_id_t> const & intfs) {
   intfs_ = intfs;
}

inline void
mac_entry_t::intf_set(intf_id_t const & value) {
   intfs_.insert(value);
}

inline void
mac_entry_t::intf_del(intf_id_t const & value) {
   intfs_.erase(value);
}

inline bool
mac_entry_t::persistent() const {
   return persistent_;
}

inline void
mac_entry_t::persistent_is(bool persistent) {
   persistent_ = persistent;
}

inline bool
mac_entry_t::operator!() const {
   return !mac_key_;
}

inline vlan_id_t
mac_entry_t::vlan_id() const {
   return mac_key_.vlan_id();
}

inline eth_addr_t
mac_entry_t::eth_addr() const {
   return mac_key_.eth_addr();
}

inline intf_id_t
mac_entry_t::intf() const {
   return intfs_.size() ? *intfs_.begin() : intf_id_t();
}

inline void
mac_entry_t::intf_is(intf_id_t intf) {
   intfs_ = {intf};
}

inline bool
mac_entry_t::operator==(mac_entry_t const & other) const {
   return mac_key_ == other.mac_key_ &&
          intfs_ == other.intfs_ &&
          persistent_ == other.persistent_;
}

inline bool
mac_entry_t::operator!=(mac_entry_t const & other) const {
   return !operator==(other);
}

inline uint32_t
mac_entry_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&mac_key_,
              sizeof(mac_key_t), ret);
   for (auto it=intfs_.cbegin(); it!=intfs_.cend(); ++it) {
      ret = hash_mix::mix((uint8_t *)&(*it),
            sizeof(intf_id_t), ret);
   }
   ret = hash_mix::mix((uint8_t *)&persistent_,
              sizeof(bool), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
mac_entry_t::to_string() const {
   std::ostringstream ss;
   ss << "mac_entry_t(";
   ss << "mac_key=" << mac_key_;
   ss << ", intfs=" <<"'";
   bool first_intfs = true;
   for (auto it=intfs_.cbegin(); it!=intfs_.cend(); ++it) {
      if (first_intfs) {
         ss << (*it);
         first_intfs = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", persistent=" << persistent_;
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
