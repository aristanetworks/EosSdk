// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_BGP_H
#define EOS_INLINE_TYPES_BGP_H

namespace eos {

inline bgp_peer_key_t::bgp_peer_key_t() :
      vrf_name_(), peer_addr_() {
}

inline bgp_peer_key_t::bgp_peer_key_t(std::string const & vrf_name,
                                      ip_addr_t const & peer_addr) :
      vrf_name_(vrf_name), peer_addr_(peer_addr) {
}

inline std::string
bgp_peer_key_t::vrf_name() const {
   return vrf_name_;
}

inline void
bgp_peer_key_t::vrf_name_is(std::string const & vrf_name) {
   vrf_name_ = vrf_name;
}

inline ip_addr_t
bgp_peer_key_t::peer_addr() const {
   return peer_addr_;
}

inline void
bgp_peer_key_t::peer_addr_is(ip_addr_t const & peer_addr) {
   peer_addr_ = peer_addr;
}

inline bool
bgp_peer_key_t::operator==(bgp_peer_key_t const & other) const {
   return vrf_name_ == other.vrf_name_ &&
          peer_addr_ == other.peer_addr_;
}

inline bool
bgp_peer_key_t::operator!=(bgp_peer_key_t const & other) const {
   return !operator==(other);
}

inline bool
bgp_peer_key_t::operator<(bgp_peer_key_t const & other) const {
   if(vrf_name_ != other.vrf_name_) {
      return vrf_name_ < other.vrf_name_;
   } else if(peer_addr_ != other.peer_addr_) {
      return peer_addr_ < other.peer_addr_;
   }
   return false;
}

inline uint32_t
bgp_peer_key_t::hash() const {
   uint32_t ret = 0;
   ret ^= std::hash<std::string>()(vrf_name_);
   ret = hash_mix::mix((uint8_t *)&peer_addr_,
              sizeof(ip_addr_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
bgp_peer_key_t::to_string() const {
   std::ostringstream ss;
   ss << "bgp_peer_key_t(";
   ss << "vrf_name='" << vrf_name_ << "'";
   ss << ", peer_addr=" << peer_addr_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const bgp_peer_key_t& obj) {
   os << obj.to_string();
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const bgp_peer_state_t & enum_val) {
   if (enum_val==PEER_UNKNOWN) {
      os << "PEER_UNKNOWN";
   } else if (enum_val==PEER_IDLE) {
      os << "PEER_IDLE";
   } else if (enum_val==PEER_CONNECT) {
      os << "PEER_CONNECT";
   } else if (enum_val==PEER_ACTIVE) {
      os << "PEER_ACTIVE";
   } else if (enum_val==PEER_OPENSENT) {
      os << "PEER_OPENSENT";
   } else if (enum_val==PEER_OPENCONFIRM) {
      os << "PEER_OPENCONFIRM";
   } else if (enum_val==PEER_ESTABLISHED) {
      os << "PEER_ESTABLISHED";
   } else {
      os << "Unknown value";
   }
   return os;
}


}

#endif // EOS_INLINE_TYPES_BGP_H
