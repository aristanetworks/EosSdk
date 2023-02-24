// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_CLASS_MAP_H
#define EOS_INLINE_TYPES_CLASS_MAP_H

namespace eos {

// Default constructor.
class_map_rule_t::class_map_rule_t() {
   pimpl = std::shared_ptr<class_map_rule_impl_t>(
      new class_map_rule_impl_t()
   );
}
class_map_rule_t::class_map_rule_t(acl_key_t const & acl_key) {
   pimpl = std::shared_ptr<class_map_rule_impl_t>(
      new class_map_rule_impl_t(
         acl_key
      )
   );
}
class_map_rule_t::class_map_rule_t(
   const class_map_rule_t& other)
{
   pimpl = std::make_unique<class_map_rule_impl_t>(
      class_map_rule_impl_t(*other.pimpl));
}
class_map_rule_t&
class_map_rule_t::operator=(
   class_map_rule_t const & other)
{
   pimpl = std::shared_ptr<class_map_rule_impl_t>(
      new class_map_rule_impl_t(*other.pimpl));
   return *this;
}

acl_key_t
class_map_rule_t::acl_key() const {
   return pimpl->acl_key();
}
bool
class_map_rule_t::operator==(class_map_rule_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
class_map_rule_t::operator!=(class_map_rule_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
class_map_rule_t::hash() const {
   return pimpl->hash();
}
void
class_map_rule_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
class_map_rule_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const class_map_rule_t& obj) {
   return operator<<(os, *obj.pimpl);
}


// Default constructor.
class_map_t::class_map_t() {
   pimpl = std::shared_ptr<class_map_impl_t>(
      new class_map_impl_t()
   );
}
class_map_t::class_map_t(class_map_key_t const & key) {
   pimpl = std::shared_ptr<class_map_impl_t>(
      new class_map_impl_t(
         key
      )
   );
}
class_map_t::class_map_t(
   const class_map_t& other)
{
   pimpl = std::make_unique<class_map_impl_t>(
      class_map_impl_t(*other.pimpl));
}
class_map_t&
class_map_t::operator=(
   class_map_t const & other)
{
   pimpl = std::shared_ptr<class_map_impl_t>(
      new class_map_impl_t(*other.pimpl));
   return *this;
}

class_map_key_t
class_map_t::key() const {
   return pimpl->key();
}
void
class_map_t::key_is(class_map_key_t const & key) {
   pimpl->key_is(key);
}
std::map<uint32_t, class_map_rule_t> const &
class_map_t::rules() const {
   return pimpl->rules();
}
void
class_map_t::rules_is(std::map<uint32_t, class_map_rule_t> const & rules) {
   pimpl->rules_is(rules);
}
void
class_map_t::rule_set(uint32_t key, class_map_rule_t const & value) {
   pimpl->rule_set(key, value);
}
void
class_map_t::rule_del(uint32_t key) {
   pimpl->rule_del(key);
}
bool
class_map_t::operator==(class_map_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
class_map_t::operator!=(class_map_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
class_map_t::hash() const {
   return pimpl->hash();
}
void
class_map_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
class_map_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const class_map_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_CLASS_MAP_H
