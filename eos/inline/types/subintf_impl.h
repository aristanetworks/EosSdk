// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_SUBINTF_IMPL_H
#define EOS_INLINE_TYPES_SUBINTF_IMPL_H

namespace eos {

// Default constructor.
subintf_impl_t::subintf_impl_t() :
      intf_id_(intf_id_t()), vlan_id_(vlan_id_t()) {
}

subintf_impl_t::subintf_impl_t(intf_id_t intf_id, vlan_id_t vlan_id) :
      intf_id_(intf_id), vlan_id_(vlan_id) {
}

intf_id_t
subintf_impl_t::intf_id() const {
   return intf_id_;
}

vlan_id_t
subintf_impl_t::vlan_id() const {
   return vlan_id_;
}

void
subintf_impl_t::vlan_id_is(vlan_id_t vlan_id) {
   vlan_id_ = vlan_id;
}

bool
subintf_impl_t::operator==(subintf_impl_t const & other) const {
   return intf_id_ == other.intf_id_ &&
          vlan_id_ == other.vlan_id_;
}

bool
subintf_impl_t::operator!=(subintf_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
subintf_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
subintf_impl_t::mix_me(hash_mix & h) const {
   h.mix(intf_id_); // intf_id_t
   h.mix(vlan_id_); // vlan_id_t
}

std::string
subintf_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "subintf_t(";
   ss << "intf_id=" << intf_id_;
   ss << ", vlan_id=" << vlan_id_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const subintf_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/subintf.h>

#endif // EOS_INLINE_TYPES_SUBINTF_IMPL_H
