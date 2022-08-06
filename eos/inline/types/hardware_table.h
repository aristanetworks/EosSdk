// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_HARDWARE_TABLE_H
#define EOS_INLINE_TYPES_HARDWARE_TABLE_H

namespace eos {

hardware_table_key_t::hardware_table_key_t() {
   pimpl = std::shared_ptr<hardware_table_key_impl_t>(
      new hardware_table_key_impl_t()
   );
}
hardware_table_key_t::hardware_table_key_t(std::string const & table_name,
                                                  std::string const & feature,
                                                  std::string const & chip) {
   pimpl = std::shared_ptr<hardware_table_key_impl_t>(
      new hardware_table_key_impl_t(
         table_name,
         feature,
         chip
      )
   );
}
hardware_table_key_t::hardware_table_key_t(std::string const & table_name,
                                                  std::string const & feature) {
   pimpl = std::shared_ptr<hardware_table_key_impl_t>(
      new hardware_table_key_impl_t(
         table_name,
         feature
      )
   );
}
hardware_table_key_t::hardware_table_key_t(std::string const & table_name) {
   pimpl = std::shared_ptr<hardware_table_key_impl_t>(
      new hardware_table_key_impl_t(
         table_name
      )
   );
}
hardware_table_key_t::hardware_table_key_t(
   const hardware_table_key_t& other)
{
   pimpl = std::make_unique<hardware_table_key_impl_t>(
      hardware_table_key_impl_t(*other.pimpl));
}
hardware_table_key_t&
hardware_table_key_t::operator=(
   hardware_table_key_t const & other)
{
   pimpl = std::shared_ptr<hardware_table_key_impl_t>(
      new hardware_table_key_impl_t(*other.pimpl));
   return *this;
}

std::string
hardware_table_key_t::table_name() const {
   return pimpl->table_name();
}
std::string
hardware_table_key_t::feature() const {
   return pimpl->feature();
}
std::string
hardware_table_key_t::chip() const {
   return pimpl->chip();
}
bool
hardware_table_key_t::operator==(hardware_table_key_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
hardware_table_key_t::operator!=(hardware_table_key_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
hardware_table_key_t::operator<(hardware_table_key_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
hardware_table_key_t::hash() const {
   return pimpl->hash();
}
void
hardware_table_key_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
hardware_table_key_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const hardware_table_key_t& obj) {
   return operator<<(os, *obj.pimpl);
}


hardware_table_high_watermark_t::hardware_table_high_watermark_t() {
   pimpl = std::shared_ptr<hardware_table_high_watermark_impl_t>(
      new hardware_table_high_watermark_impl_t()
   );
}
hardware_table_high_watermark_t::hardware_table_high_watermark_t(
         uint32_t max_entries, time_t timestamp) {
   pimpl = std::shared_ptr<hardware_table_high_watermark_impl_t>(
      new hardware_table_high_watermark_impl_t(
         max_entries,
         timestamp
      )
   );
}
hardware_table_high_watermark_t::hardware_table_high_watermark_t(
   const hardware_table_high_watermark_t& other)
{
   pimpl = std::make_unique<hardware_table_high_watermark_impl_t>(
      hardware_table_high_watermark_impl_t(*other.pimpl));
}
hardware_table_high_watermark_t&
hardware_table_high_watermark_t::operator=(
   hardware_table_high_watermark_t const & other)
{
   pimpl = std::shared_ptr<hardware_table_high_watermark_impl_t>(
      new hardware_table_high_watermark_impl_t(*other.pimpl));
   return *this;
}

uint32_t
hardware_table_high_watermark_t::max_entries() const {
   return pimpl->max_entries();
}
time_t
hardware_table_high_watermark_t::timestamp() const {
   return pimpl->timestamp();
}
bool
hardware_table_high_watermark_t::operator==(
         hardware_table_high_watermark_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
hardware_table_high_watermark_t::operator!=(
         hardware_table_high_watermark_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
hardware_table_high_watermark_t::operator<(
         hardware_table_high_watermark_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
hardware_table_high_watermark_t::hash() const {
   return pimpl->hash();
}
void
hardware_table_high_watermark_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
hardware_table_high_watermark_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const hardware_table_high_watermark_t& obj) {
   return operator<<(os, *obj.pimpl);
}


hardware_table_usage_t::hardware_table_usage_t() {
   pimpl = std::shared_ptr<hardware_table_usage_impl_t>(
      new hardware_table_usage_impl_t()
   );
}
hardware_table_usage_t::hardware_table_usage_t(uint32_t used_entries,
                                                      uint32_t free_entries,
                                                      uint32_t committed_entries) {
   pimpl = std::shared_ptr<hardware_table_usage_impl_t>(
      new hardware_table_usage_impl_t(
         used_entries,
         free_entries,
         committed_entries
      )
   );
}
hardware_table_usage_t::hardware_table_usage_t(
   const hardware_table_usage_t& other)
{
   pimpl = std::make_unique<hardware_table_usage_impl_t>(
      hardware_table_usage_impl_t(*other.pimpl));
}
hardware_table_usage_t&
hardware_table_usage_t::operator=(
   hardware_table_usage_t const & other)
{
   pimpl = std::shared_ptr<hardware_table_usage_impl_t>(
      new hardware_table_usage_impl_t(*other.pimpl));
   return *this;
}

uint32_t
hardware_table_usage_t::used_entries() const {
   return pimpl->used_entries();
}
uint32_t
hardware_table_usage_t::free_entries() const {
   return pimpl->free_entries();
}
uint32_t
hardware_table_usage_t::committed_entries() const {
   return pimpl->committed_entries();
}
bool
hardware_table_usage_t::operator==(hardware_table_usage_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
hardware_table_usage_t::operator!=(hardware_table_usage_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
hardware_table_usage_t::operator<(hardware_table_usage_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
hardware_table_usage_t::hash() const {
   return pimpl->hash();
}
void
hardware_table_usage_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
hardware_table_usage_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const hardware_table_usage_t& obj) {
   return operator<<(os, *obj.pimpl);
}


hardware_table_entry_t::hardware_table_entry_t() {
   pimpl = std::shared_ptr<hardware_table_entry_impl_t>(
      new hardware_table_entry_impl_t()
   );
}
hardware_table_entry_t::hardware_table_entry_t(
         hardware_table_usage_t const & usage, uint32_t max_entries,
         hardware_table_high_watermark_t const & high_watermark) {
   pimpl = std::shared_ptr<hardware_table_entry_impl_t>(
      new hardware_table_entry_impl_t(
         usage,
         max_entries,
         high_watermark
      )
   );
}
hardware_table_entry_t::hardware_table_entry_t(
   const hardware_table_entry_t& other)
{
   pimpl = std::make_unique<hardware_table_entry_impl_t>(
      hardware_table_entry_impl_t(*other.pimpl));
}
hardware_table_entry_t&
hardware_table_entry_t::operator=(
   hardware_table_entry_t const & other)
{
   pimpl = std::shared_ptr<hardware_table_entry_impl_t>(
      new hardware_table_entry_impl_t(*other.pimpl));
   return *this;
}

hardware_table_usage_t
hardware_table_entry_t::usage() const {
   return pimpl->usage();
}
uint32_t
hardware_table_entry_t::max_entries() const {
   return pimpl->max_entries();
}
hardware_table_high_watermark_t
hardware_table_entry_t::high_watermark() const {
   return pimpl->high_watermark();
}
bool
hardware_table_entry_t::operator==(hardware_table_entry_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
hardware_table_entry_t::operator!=(hardware_table_entry_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
hardware_table_entry_t::operator<(hardware_table_entry_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
hardware_table_entry_t::hash() const {
   return pimpl->hash();
}
void
hardware_table_entry_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
hardware_table_entry_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const hardware_table_entry_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_HARDWARE_TABLE_H
