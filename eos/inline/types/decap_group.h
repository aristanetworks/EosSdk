// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_DECAP_GROUP_H
#define EOS_INLINE_TYPES_DECAP_GROUP_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
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


std::string
decap_group_t::group_name() const {
   return pimpl->group_name();
}
ip_addr_t
decap_group_t::destination_addr() const {
   return pimpl->destination_addr();
}
void
decap_group_t::destination_addr_is(ip_addr_t const & destination_addr) {
   pimpl->destination_addr_is(destination_addr);
}
void
decap_group_t::destination_addr_is(ip_addr_t && destination_addr) {
   pimpl->destination_addr_is(std::move(destination_addr));
}
decap_protocol_type_t
decap_group_t::protocol_type() const {
   return pimpl->protocol_type();
}
void
decap_group_t::protocol_type_is(decap_protocol_type_t protocol_type) {
   pimpl->protocol_type_is(protocol_type);
}
bool
decap_group_t::operator==(decap_group_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
decap_group_t::operator!=(decap_group_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
decap_group_t::operator<(decap_group_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
decap_group_t::hash() const {
   return pimpl->hash();
}
void
decap_group_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
decap_group_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const decap_group_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_DECAP_GROUP_H
