// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MPLS_VRF_LABEL_H
#define EOS_INLINE_TYPES_MPLS_VRF_LABEL_H

namespace eos {

// Default constructor.
mpls_vrf_label_t::mpls_vrf_label_t() {
   pimpl = std::shared_ptr<mpls_vrf_label_impl_t>(
      new mpls_vrf_label_impl_t()
   );
}
mpls_vrf_label_t::mpls_vrf_label_t(mpls_label_t label, std::string vrf_name) {
   pimpl = std::shared_ptr<mpls_vrf_label_impl_t>(
      new mpls_vrf_label_impl_t(
         label,
         vrf_name
      )
   );
}
mpls_vrf_label_t::mpls_vrf_label_t(
   const mpls_vrf_label_t& other)
{
   pimpl = std::make_unique<mpls_vrf_label_impl_t>(
      mpls_vrf_label_impl_t(*other.pimpl));
}
mpls_vrf_label_t&
mpls_vrf_label_t::operator=(
   mpls_vrf_label_t const & other)
{
   pimpl = std::shared_ptr<mpls_vrf_label_impl_t>(
      new mpls_vrf_label_impl_t(*other.pimpl));
   return *this;
}

mpls_label_t
mpls_vrf_label_t::label() const {
   return pimpl->label();
}
std::string
mpls_vrf_label_t::vrf_name() const {
   return pimpl->vrf_name();
}
bool
mpls_vrf_label_t::operator==(mpls_vrf_label_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
mpls_vrf_label_t::operator!=(mpls_vrf_label_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
mpls_vrf_label_t::operator<(mpls_vrf_label_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
mpls_vrf_label_t::hash() const {
   return pimpl->hash();
}
void
mpls_vrf_label_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
mpls_vrf_label_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const mpls_vrf_label_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_MPLS_VRF_LABEL_H
