// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_BFD_H
#define EOS_INLINE_TYPES_BFD_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const bfd_session_status_t & enum_val) {
   if (enum_val==BFD_SESSION_STATUS_NULL) {
      os << "BFD_SESSION_STATUS_NULL";
   } else if (enum_val==BFD_SESSION_STATUS_DOWN) {
      os << "BFD_SESSION_STATUS_DOWN";
   } else if (enum_val==BFD_SESSION_STATUS_INIT) {
      os << "BFD_SESSION_STATUS_INIT";
   } else if (enum_val==BFD_SESSION_STATUS_UP) {
      os << "BFD_SESSION_STATUS_UP";
   } else if (enum_val==BFD_SESSION_STATUS_ADMIN_DOWN) {
      os << "BFD_SESSION_STATUS_ADMIN_DOWN";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const bfd_session_type_t & enum_val) {
   if (enum_val==BFD_SESSION_TYPE_NULL) {
      os << "BFD_SESSION_TYPE_NULL";
   } else if (enum_val==BFD_SESSION_TYPE_NORMAL) {
      os << "BFD_SESSION_TYPE_NORMAL";
   } else if (enum_val==BFD_SESSION_TYPE_MICRO) {
      os << "BFD_SESSION_TYPE_MICRO";
   } else if (enum_val==BFD_SESSION_TYPE_VXLANTUNNEL) {
      os << "BFD_SESSION_TYPE_VXLANTUNNEL";
   } else if (enum_val==BFD_SESSION_TYPE_LAGRFC7130) {
      os << "BFD_SESSION_TYPE_LAGRFC7130";
   } else if (enum_val==BFD_SESSION_TYPE_MICRORFC7130) {
      os << "BFD_SESSION_TYPE_MICRORFC7130";
   } else if (enum_val==BFD_SESSION_TYPE_MULTIHOP) {
      os << "BFD_SESSION_TYPE_MULTIHOP";
   } else if (enum_val==BFD_SESSION_TYPE_SBFD_INITIATOR) {
      os << "BFD_SESSION_TYPE_SBFD_INITIATOR";
   } else if (enum_val==BFD_SESSION_TYPE_SBFD_REFLECTOR) {
      os << "BFD_SESSION_TYPE_SBFD_REFLECTOR";
   } else {
      os << "Unknown value";
   }
   return os;
}



// Default constructor.
inline bfd_session_key_t::bfd_session_key_t() :
      ip_addr_(), vrf_(), type_(), intf_() {
}

inline bfd_session_key_t::bfd_session_key_t(ip_addr_t ip_addr, std::string vrf,
                                            bfd_session_type_t type,
                                            intf_id_t intf) :
      ip_addr_(ip_addr), vrf_(vrf), type_(type), intf_(intf) {
}

inline ip_addr_t
bfd_session_key_t::ip_addr() const {
   return ip_addr_;
}

inline std::string
bfd_session_key_t::vrf() const {
   return vrf_;
}

inline bfd_session_type_t
bfd_session_key_t::type() const {
   return type_;
}

inline intf_id_t
bfd_session_key_t::intf() const {
   return intf_;
}

inline bool
bfd_session_key_t::operator==(bfd_session_key_t const & other) const {
   return ip_addr_ == other.ip_addr_ &&
          vrf_ == other.vrf_ &&
          type_ == other.type_ &&
          intf_ == other.intf_;
}

inline bool
bfd_session_key_t::operator!=(bfd_session_key_t const & other) const {
   return !operator==(other);
}

inline bool
bfd_session_key_t::operator<(bfd_session_key_t const & other) const {
   if(ip_addr_ != other.ip_addr_) {
      return ip_addr_ < other.ip_addr_;
   } else if(vrf_ != other.vrf_) {
      return vrf_ < other.vrf_;
   } else if(type_ != other.type_) {
      return type_ < other.type_;
   } else if(intf_ != other.intf_) {
      return intf_ < other.intf_;
   }
   return false;
}

inline uint32_t
bfd_session_key_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&ip_addr_,
              sizeof(ip_addr_t), ret);
   ret ^= std::hash<std::string>()(vrf_);
   ret = hash_mix::mix((uint8_t *)&type_,
              sizeof(bfd_session_type_t), ret);
   ret = hash_mix::mix((uint8_t *)&intf_,
              sizeof(intf_id_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
bfd_session_key_t::to_string() const {
   std::ostringstream ss;
   ss << "bfd_session_key_t(";
   ss << "ip_addr=" << ip_addr_;
   ss << ", vrf='" << vrf_ << "'";
   ss << ", type=" << type_;
   ss << ", intf=" << intf_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const bfd_session_key_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
inline bfd_interval_t::bfd_interval_t() :
      tx_(300), rx_(300), mult_(3) {
}

inline bfd_interval_t::bfd_interval_t(uint16_t tx, uint16_t rx, uint8_t mult) :
      tx_(tx), rx_(rx), mult_(mult) {
}

inline uint16_t
bfd_interval_t::tx() const {
   return tx_;
}

inline uint16_t
bfd_interval_t::rx() const {
   return rx_;
}

inline uint8_t
bfd_interval_t::mult() const {
   return mult_;
}

inline bool
bfd_interval_t::operator==(bfd_interval_t const & other) const {
   return tx_ == other.tx_ &&
          rx_ == other.rx_ &&
          mult_ == other.mult_;
}

inline bool
bfd_interval_t::operator!=(bfd_interval_t const & other) const {
   return !operator==(other);
}

inline uint32_t
bfd_interval_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&tx_,
              sizeof(uint16_t), ret);
   ret = hash_mix::mix((uint8_t *)&rx_,
              sizeof(uint16_t), ret);
   ret = hash_mix::mix((uint8_t *)&mult_,
              sizeof(uint8_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
bfd_interval_t::to_string() const {
   std::ostringstream ss;
   ss << "bfd_interval_t(";
   ss << "tx=" << tx_;
   ss << ", rx=" << rx_;
   ss << ", mult=" << mult_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const bfd_interval_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
inline bfd_session_t::bfd_session_t() :
      peer_(), status_(BFD_SESSION_STATUS_NULL) {
}

inline bfd_session_t::bfd_session_t(bfd_session_key_t peer,
                                    bfd_session_status_t status) :
      peer_(peer), status_(status) {
}

inline bfd_session_key_t
bfd_session_t::peer() const {
   return peer_;
}

inline bfd_session_status_t
bfd_session_t::status() const {
   return status_;
}

inline bool
bfd_session_t::operator==(bfd_session_t const & other) const {
   return peer_ == other.peer_ &&
          status_ == other.status_;
}

inline bool
bfd_session_t::operator!=(bfd_session_t const & other) const {
   return !operator==(other);
}

inline bool
bfd_session_t::operator<(bfd_session_t const & other) const {
   if(peer_ != other.peer_) {
      return peer_ < other.peer_;
   } else if(status_ != other.status_) {
      return status_ < other.status_;
   }
   return false;
}

inline uint32_t
bfd_session_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&peer_,
              sizeof(bfd_session_key_t), ret);
   ret = hash_mix::mix((uint8_t *)&status_,
              sizeof(bfd_session_status_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
bfd_session_t::to_string() const {
   std::ostringstream ss;
   ss << "bfd_session_t(";
   ss << "peer=" << peer_;
   ss << ", status=" << status_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const bfd_session_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_BFD_H
