// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_VRF_H
#define EOS_INLINE_TYPES_VRF_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const vrf_state_t & enum_val) {
   if (enum_val==VRF_NULL) {
      os << "VRF_NULL";
   } else if (enum_val==VRF_INITIALIZING) {
      os << "VRF_INITIALIZING";
   } else if (enum_val==VRF_ACTIVE) {
      os << "VRF_ACTIVE";
   } else if (enum_val==VRF_DELETING) {
      os << "VRF_DELETING";
   } else {
      os << "Unknown value";
   }
   return os;
}


// Default constructor.
vrf_t::vrf_t() {
   pimpl = std::shared_ptr<vrf_impl_t>(
      new vrf_impl_t()
   );
}
vrf_t::vrf_t(std::string name, vrf_state_t state, uint64_t rd) {
   pimpl = std::shared_ptr<vrf_impl_t>(
      new vrf_impl_t(
         name,
         state,
         rd
      )
   );
}
vrf_t::vrf_t(
   const vrf_t& other)
{
   pimpl = std::make_unique<vrf_impl_t>(
      vrf_impl_t(*other.pimpl));
}
vrf_t&
vrf_t::operator=(
   vrf_t const & other)
{
   pimpl = std::shared_ptr<vrf_impl_t>(
      new vrf_impl_t(*other.pimpl));
   return *this;
}

std::string
vrf_t::name() const {
   return pimpl->name();
}
vrf_state_t
vrf_t::state() const {
   return pimpl->state();
}
uint64_t
vrf_t::rd() const {
   return pimpl->rd();
}
bool
vrf_t::operator==(vrf_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
vrf_t::operator!=(vrf_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
vrf_t::operator<(vrf_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
vrf_t::hash() const {
   return pimpl->hash();
}
void
vrf_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
vrf_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const vrf_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_VRF_H
