// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_L1_SOURCE_IMPL_H
#define EOS_INLINE_TYPES_L1_SOURCE_IMPL_H

namespace eos {



l1_source_impl_t::l1_source_impl_t() :
      l1_source_type_(), port_() {
}

l1_source_impl_t::l1_source_impl_t(l1_source_type_t l1_source_type) :
      l1_source_type_(l1_source_type), port_() {
}

l1_source_impl_t::l1_source_impl_t(l1_source_type_t l1_source_type,
                                          intf_id_t port) :
      l1_source_type_(l1_source_type), port_(port) {
}

l1_source_type_t
l1_source_impl_t::l1_source_type() const {
   return l1_source_type_;
}

void
l1_source_impl_t::l1_source_type_is(l1_source_type_t l1_source_type) {
   l1_source_type_ = l1_source_type;
}

intf_id_t
l1_source_impl_t::port() const {
   return port_;
}

void
l1_source_impl_t::port_is(intf_id_t port) {
   port_ = port;
}

bool
l1_source_impl_t::operator==(l1_source_impl_t const & other) const {
   return l1_source_type_ == other.l1_source_type_ &&
          port_ == other.port_;
}

bool
l1_source_impl_t::operator!=(l1_source_impl_t const & other) const {
   return !operator==(other);
}

bool
l1_source_impl_t::operator<(l1_source_impl_t const & other) const {
   if(l1_source_type_ != other.l1_source_type_) {
      return l1_source_type_ < other.l1_source_type_;
   } else if(port_ != other.port_) {
      return port_ < other.port_;
   }
   return false;
}

uint32_t
l1_source_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
l1_source_impl_t::mix_me(hash_mix & h) const {
   h.mix(l1_source_type_); // l1_source_type_t
   h.mix(port_); // intf_id_t
}

std::string
l1_source_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "l1_source_t(";
   ss << "l1_source_type=" << l1_source_type_;
   ss << ", port=" << port_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const l1_source_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/l1_source.h>

#endif // EOS_INLINE_TYPES_L1_SOURCE_IMPL_H
