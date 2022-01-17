// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_DECAP_GROUP_H
#define EOS_INLINE_TYPES_DECAP_GROUP_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const decap_protocol_type_t & enum_val) {
   if (enum_val==PROTOCOL_TYPE_NULL) {
      os << "PROTOCOL_TYPE_NULL";
   } else if (enum_val==PROTOCOL_TYPE_GRE) {
      os << "PROTOCOL_TYPE_GRE";
   } else {
      os << "Unknown value";
   }
   return os;
}



// Default constructor, sets NULL protocol type.
inline decap_group_t::decap_group_t() :
      group_name_(), destination_addr_(), protocol_type_(PROTOCOL_TYPE_NULL) {
}

inline decap_group_t::decap_group_t(std::string const & group_name,
                                    ip_addr_t const & destination_addr,
                                    decap_protocol_type_t protocol_type) :
      group_name_(group_name), destination_addr_(destination_addr),
      protocol_type_(protocol_type) {
   if(group_name.empty()) {
      panic(invalid_argument_error("group_name","must be a non-empty string"));
   }
}

inline std::string
decap_group_t::group_name() const {
   return group_name_;
}

inline ip_addr_t
decap_group_t::destination_addr() const {
   return destination_addr_;
}

inline void
decap_group_t::destination_addr_is(ip_addr_t const & destination_addr) {
   destination_addr_ = destination_addr;
}

inline decap_protocol_type_t
decap_group_t::protocol_type() const {
   return protocol_type_;
}

inline void
decap_group_t::protocol_type_is(decap_protocol_type_t protocol_type) {
   protocol_type_ = protocol_type;
}

inline bool
decap_group_t::operator==(decap_group_t const & other) const {
   return group_name_ == other.group_name_ &&
          destination_addr_ == other.destination_addr_ &&
          protocol_type_ == other.protocol_type_;
}

inline bool
decap_group_t::operator!=(decap_group_t const & other) const {
   return !operator==(other);
}

inline bool
decap_group_t::operator<(decap_group_t const & other) const {
   if(group_name_ != other.group_name_) {
      return group_name_ < other.group_name_;
   } else if(destination_addr_ != other.destination_addr_) {
      return destination_addr_ < other.destination_addr_;
   } else if(protocol_type_ != other.protocol_type_) {
      return protocol_type_ < other.protocol_type_;
   }
   return false;
}

inline uint32_t
decap_group_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
decap_group_t::mix_me(hash_mix & h) const {
   h.mix(group_name_); // std::string
   h.mix(destination_addr_); // ip_addr_t
   h.mix(protocol_type_); // decap_protocol_type_t
}

inline std::string
decap_group_t::to_string() const {
   std::ostringstream ss;
   ss << "decap_group_t(";
   ss << "group_name='" << group_name_ << "'";
   ss << ", destination_addr=" << destination_addr_;
   ss << ", protocol_type=" << protocol_type_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const decap_group_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_DECAP_GROUP_H
