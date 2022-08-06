// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_L1_SOURCE_H
#define EOS_INLINE_TYPES_L1_SOURCE_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const l1_source_type_t & enum_val) {
   if (enum_val==unknown) {
      os << "unknown";
   } else if (enum_val==none) {
      os << "none";
   } else if (enum_val==port) {
      os << "port";
   } else if (enum_val==mac) {
      os << "mac";
   } else if (enum_val==switchPort) {
      os << "switchPort";
   } else {
      os << "Unknown value";
   }
   return os;
}


l1_source_t::l1_source_t() {
   pimpl = std::shared_ptr<l1_source_impl_t>(
      new l1_source_impl_t()
   );
}
l1_source_t::l1_source_t(l1_source_type_t l1_source_type) {
   pimpl = std::shared_ptr<l1_source_impl_t>(
      new l1_source_impl_t(
         l1_source_type
      )
   );
}
l1_source_t::l1_source_t(l1_source_type_t l1_source_type, intf_id_t port) {
   pimpl = std::shared_ptr<l1_source_impl_t>(
      new l1_source_impl_t(
         l1_source_type,
         port
      )
   );
}
l1_source_t::l1_source_t(
   const l1_source_t& other)
{
   pimpl = std::make_unique<l1_source_impl_t>(
      l1_source_impl_t(*other.pimpl));
}
l1_source_t&
l1_source_t::operator=(
   l1_source_t const & other)
{
   pimpl = std::shared_ptr<l1_source_impl_t>(
      new l1_source_impl_t(*other.pimpl));
   return *this;
}

l1_source_type_t
l1_source_t::l1_source_type() const {
   return pimpl->l1_source_type();
}
void
l1_source_t::l1_source_type_is(l1_source_type_t l1_source_type) {
   pimpl->l1_source_type_is(l1_source_type);
}
intf_id_t
l1_source_t::port() const {
   return pimpl->port();
}
void
l1_source_t::port_is(intf_id_t port) {
   pimpl->port_is(port);
}
bool
l1_source_t::operator==(l1_source_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
l1_source_t::operator!=(l1_source_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
l1_source_t::operator<(l1_source_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
l1_source_t::hash() const {
   return pimpl->hash();
}
void
l1_source_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
l1_source_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const l1_source_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_L1_SOURCE_H
