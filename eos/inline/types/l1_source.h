// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_L1_SOURCE_H
#define EOS_INLINE_TYPES_L1_SOURCE_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const l1_source_type_t & enum_val) {
   if (enum_val==unknown) {
      os << "unknown";
   } else if (enum_val==none) {
      os << "none";
   } else if (enum_val==port) {
      os << "port";
   } else if (enum_val==mac) {
      os << "mac";
   } else if (enum_val==switchPort) {
      os << "switchPort";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline l1_source_t::l1_source_t() :
      l1_source_type_(), port_() {
}

inline l1_source_t::l1_source_t(l1_source_type_t l1_source_type) :
      l1_source_type_(l1_source_type), port_() {
}

inline l1_source_t::l1_source_t(l1_source_type_t l1_source_type, intf_id_t port) :
      l1_source_type_(l1_source_type), port_(port) {
}

inline l1_source_type_t
l1_source_t::l1_source_type() const {
   return l1_source_type_;
}

inline void
l1_source_t::l1_source_type_is(l1_source_type_t l1_source_type) {
   l1_source_type_ = l1_source_type;
}

inline intf_id_t
l1_source_t::port() const {
   return port_;
}

inline void
l1_source_t::port_is(intf_id_t port) {
   port_ = port;
}

inline bool
l1_source_t::operator==(l1_source_t const & other) const {
   return l1_source_type_ == other.l1_source_type_ &&
          port_ == other.port_;
}

inline bool
l1_source_t::operator!=(l1_source_t const & other) const {
   return !operator==(other);
}

inline bool
l1_source_t::operator<(l1_source_t const & other) const {
   if(l1_source_type_ != other.l1_source_type_) {
      return l1_source_type_ < other.l1_source_type_;
   } else if(port_ != other.port_) {
      return port_ < other.port_;
   }
   return false;
}

inline uint32_t
l1_source_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&l1_source_type_,
              sizeof(l1_source_type_t), ret);
   ret = hash_mix::mix((uint8_t *)&port_,
              sizeof(intf_id_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
l1_source_t::to_string() const {
   std::ostringstream ss;
   ss << "l1_source_t(";
   ss << "l1_source_type=" << l1_source_type_;
   ss << ", port=" << port_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const l1_source_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_L1_SOURCE_H
