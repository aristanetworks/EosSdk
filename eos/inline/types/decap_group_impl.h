// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_DECAP_GROUP_IMPL_H
#define EOS_INLINE_TYPES_DECAP_GROUP_IMPL_H

namespace eos {



// Default constructor, sets NULL protocol type.
decap_group_impl_t::decap_group_impl_t() :
      group_name_(), destination_addr_(), protocol_type_(PROTOCOL_TYPE_NULL) {
}

decap_group_impl_t::decap_group_impl_t(std::string const & group_name,
                                              ip_addr_t const & destination_addr,
                                              decap_protocol_type_t protocol_type) :
      group_name_(group_name), destination_addr_(destination_addr),
      protocol_type_(protocol_type) {
   if(group_name.empty()) {
      panic(invalid_argument_error("group_name","must be a non-empty string"));
   }
}

std::string
decap_group_impl_t::group_name() const {
   return group_name_;
}

ip_addr_t
decap_group_impl_t::destination_addr() const {
   return destination_addr_;
}

void
decap_group_impl_t::destination_addr_is(ip_addr_t const & destination_addr) {
   destination_addr_ = destination_addr;
}

decap_protocol_type_t
decap_group_impl_t::protocol_type() const {
   return protocol_type_;
}

void
decap_group_impl_t::protocol_type_is(decap_protocol_type_t protocol_type) {
   protocol_type_ = protocol_type;
}

bool
decap_group_impl_t::operator==(decap_group_impl_t const & other) const {
   return group_name_ == other.group_name_ &&
          destination_addr_ == other.destination_addr_ &&
          protocol_type_ == other.protocol_type_;
}

bool
decap_group_impl_t::operator!=(decap_group_impl_t const & other) const {
   return !operator==(other);
}

bool
decap_group_impl_t::operator<(decap_group_impl_t const & other) const {
   if(group_name_ != other.group_name_) {
      return group_name_ < other.group_name_;
   } else if(destination_addr_ != other.destination_addr_) {
      return destination_addr_ < other.destination_addr_;
   } else if(protocol_type_ != other.protocol_type_) {
      return protocol_type_ < other.protocol_type_;
   }
   return false;
}

uint32_t
decap_group_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
decap_group_impl_t::mix_me(hash_mix & h) const {
   h.mix(group_name_); // std::string
   h.mix(destination_addr_); // ip_addr_t
   h.mix(protocol_type_); // decap_protocol_type_t
}

std::string
decap_group_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "decap_group_t(";
   ss << "group_name='" << group_name_ << "'";
   ss << ", destination_addr=" << destination_addr_;
   ss << ", protocol_type=" << protocol_type_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const decap_group_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/decap_group.h>

#endif // EOS_INLINE_TYPES_DECAP_GROUP_IMPL_H
