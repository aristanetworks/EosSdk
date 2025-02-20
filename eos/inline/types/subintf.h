// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_SUBINTF_H
#define EOS_INLINE_TYPES_SUBINTF_H

namespace eos {

intf_id_t
subintf_t::intf_id() const {
   return pimpl->intf_id();
}
vlan_id_t
subintf_t::vlan_id() const {
   return pimpl->vlan_id();
}
void
subintf_t::vlan_id_is(vlan_id_t vlan_id) {
   pimpl->vlan_id_is(vlan_id);
}
bool
subintf_t::operator==(subintf_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
subintf_t::operator!=(subintf_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
subintf_t::hash() const {
   return pimpl->hash();
}
void
subintf_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
subintf_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const subintf_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_SUBINTF_H
