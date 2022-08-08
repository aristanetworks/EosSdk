// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_NEIGHBOR_TABLE_H
#define EOS_INLINE_TYPES_NEIGHBOR_TABLE_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const neighbor_entry_type_t & enum_val) {
   if (enum_val==NEIGHBOR_ENTRY_TYPE_NULL) {
      os << "NEIGHBOR_ENTRY_TYPE_NULL";
   } else if (enum_val==NEIGHBOR_ENTRY_TYPE_DYNAMIC) {
      os << "NEIGHBOR_ENTRY_TYPE_DYNAMIC";
   } else if (enum_val==NEIGHBOR_ENTRY_TYPE_STATIC) {
      os << "NEIGHBOR_ENTRY_TYPE_STATIC";
   } else {
      os << "Unknown value";
   }
   return os;
}


// Default constructor.
neighbor_key_t::neighbor_key_t() {
   pimpl = std::shared_ptr<neighbor_key_impl_t>(
      new neighbor_key_impl_t()
   );
}
neighbor_key_t::neighbor_key_t(ip_addr_t const & ip_addr) {
   pimpl = std::shared_ptr<neighbor_key_impl_t>(
      new neighbor_key_impl_t(
         ip_addr
      )
   );
}
neighbor_key_t::neighbor_key_t(ip_addr_t const & ip_addr, intf_id_t intf_id) {
   pimpl = std::shared_ptr<neighbor_key_impl_t>(
      new neighbor_key_impl_t(
         ip_addr,
         intf_id
      )
   );
}
neighbor_key_t::neighbor_key_t(
   const neighbor_key_t& other)
{
   pimpl = std::make_unique<neighbor_key_impl_t>(
      neighbor_key_impl_t(*other.pimpl));
}
neighbor_key_t&
neighbor_key_t::operator=(
   neighbor_key_t const & other)
{
   pimpl = std::shared_ptr<neighbor_key_impl_t>(
      new neighbor_key_impl_t(*other.pimpl));
   return *this;
}

ip_addr_t
neighbor_key_t::ip_addr() const {
   return pimpl->ip_addr();
}
intf_id_t
neighbor_key_t::intf_id() const {
   return pimpl->intf_id();
}
bool
neighbor_key_t::operator==(neighbor_key_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
neighbor_key_t::operator!=(neighbor_key_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
neighbor_key_t::operator<(neighbor_key_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
neighbor_key_t::hash() const {
   return pimpl->hash();
}
void
neighbor_key_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
neighbor_key_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const neighbor_key_t& obj) {
   return operator<<(os, *obj.pimpl);
}


// Default constructor.
neighbor_entry_t::neighbor_entry_t() {
   pimpl = std::shared_ptr<neighbor_entry_impl_t>(
      new neighbor_entry_impl_t()
   );
}
neighbor_entry_t::neighbor_entry_t(neighbor_key_t const & neighbor_key,
                                          eth_addr_t eth_addr,
                                          neighbor_entry_type_t entry_type) {
   pimpl = std::shared_ptr<neighbor_entry_impl_t>(
      new neighbor_entry_impl_t(
         neighbor_key,
         eth_addr,
         entry_type
      )
   );
}
neighbor_entry_t::neighbor_entry_t(
   const neighbor_entry_t& other)
{
   pimpl = std::make_unique<neighbor_entry_impl_t>(
      neighbor_entry_impl_t(*other.pimpl));
}
neighbor_entry_t&
neighbor_entry_t::operator=(
   neighbor_entry_t const & other)
{
   pimpl = std::shared_ptr<neighbor_entry_impl_t>(
      new neighbor_entry_impl_t(*other.pimpl));
   return *this;
}

neighbor_key_t
neighbor_entry_t::neighbor_key() const {
   return pimpl->neighbor_key();
}
eth_addr_t
neighbor_entry_t::eth_addr() const {
   return pimpl->eth_addr();
}
neighbor_entry_type_t
neighbor_entry_t::entry_type() const {
   return pimpl->entry_type();
}
bool
neighbor_entry_t::operator==(neighbor_entry_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
neighbor_entry_t::operator!=(neighbor_entry_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
neighbor_entry_t::operator<(neighbor_entry_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
neighbor_entry_t::hash() const {
   return pimpl->hash();
}
void
neighbor_entry_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
neighbor_entry_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const neighbor_entry_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_NEIGHBOR_TABLE_H
