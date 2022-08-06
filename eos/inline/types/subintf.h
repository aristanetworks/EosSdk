// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_SUBINTF_H
#define EOS_INLINE_TYPES_SUBINTF_H

namespace eos {

// Default constructor.
subintf_t::subintf_t() {
   pimpl = std::shared_ptr<subintf_impl_t>(
      new subintf_impl_t()
   );
}
subintf_t::subintf_t(intf_id_t intf_id, vlan_id_t vlan_id) {
   pimpl = std::shared_ptr<subintf_impl_t>(
      new subintf_impl_t(
         intf_id,
         vlan_id
      )
   );
}
subintf_t::subintf_t(
   const subintf_t& other)
{
   pimpl = std::make_unique<subintf_impl_t>(
      subintf_impl_t(*other.pimpl));
}
subintf_t&
subintf_t::operator=(
   subintf_t const & other)
{
   pimpl = std::shared_ptr<subintf_impl_t>(
      new subintf_impl_t(*other.pimpl));
   return *this;
}

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
