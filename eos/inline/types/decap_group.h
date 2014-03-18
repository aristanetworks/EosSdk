// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_DECAP_GROUP_H
#define EOS_INLINE_TYPES_DECAP_GROUP_H

namespace eos {

// Default constructor, sets NULL protocol type.
inline decap_group_t::decap_group_t() :
      group_name_(), destination_addr_(), protocol_type_(PROTOCOL_TYPE_NULL), 
      persistent_(false) {
}

inline decap_group_t::decap_group_t(std::string group_name, 
                             ip_addr_t const & destination_addr, 
                             decap_protocol_type_t protocol_type) :
      group_name_(group_name), destination_addr_(destination_addr), 
      protocol_type_(protocol_type), persistent_(false) {
   if(group_name.empty()) {
      panic("group_name must be a non-empty string");
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
decap_group_t::persistent() const {
   return persistent_;
}

inline void
decap_group_t::persistent_is(bool persistent) {
   persistent_ = persistent;
}

inline bool
decap_group_t::operator==(decap_group_t const & other) const {
   return group_name_ == other.group_name_ &&
          destination_addr_ == other.destination_addr_ &&
          protocol_type_ == other.protocol_type_ &&
          persistent_ == other.persistent_;
}

inline bool
decap_group_t::operator!=(decap_group_t const & other) const {
   return !operator==(other);
}

inline std::string
decap_group_t::to_string() const {
   std::ostringstream ss;
   ss << "decap_group_t(";
   ss << "group_name='" << group_name_ << "'";
   ss << ", destination_addr=" << destination_addr_.to_string();
   ss << ", protocol_type=" << protocol_type_;
   ss << ", persistent=" << persistent_;
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
