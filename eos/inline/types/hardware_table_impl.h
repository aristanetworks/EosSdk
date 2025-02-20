// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_HARDWARE_TABLE_IMPL_H
#define EOS_INLINE_TYPES_HARDWARE_TABLE_IMPL_H

namespace eos {

hardware_table_key_impl_t::hardware_table_key_impl_t() :
      table_name_(), feature_(), chip_() {
}

hardware_table_key_impl_t::hardware_table_key_impl_t(
         std::string const & table_name, std::string const & feature,
         std::string const & chip) :
      table_name_(table_name), feature_(feature), chip_(chip) {
}

hardware_table_key_impl_t::hardware_table_key_impl_t(
         std::string const & table_name, std::string const & feature) :
      table_name_(table_name), feature_(feature), chip_() {
}

hardware_table_key_impl_t::hardware_table_key_impl_t(
         std::string const & table_name) :
      table_name_(table_name), feature_(), chip_() {
}

std::string
hardware_table_key_impl_t::table_name() const {
   return table_name_;
}

std::string
hardware_table_key_impl_t::feature() const {
   return feature_;
}

std::string
hardware_table_key_impl_t::chip() const {
   return chip_;
}

bool
hardware_table_key_impl_t::operator==(hardware_table_key_impl_t const & other)
       const {
   return table_name_ == other.table_name_ &&
          feature_ == other.feature_ &&
          chip_ == other.chip_;
}

bool
hardware_table_key_impl_t::operator!=(hardware_table_key_impl_t const & other)
       const {
   return !operator==(other);
}

bool
hardware_table_key_impl_t::operator<(hardware_table_key_impl_t const & other)
       const {
   if(table_name_ != other.table_name_) {
      return table_name_ < other.table_name_;
   } else if(feature_ != other.feature_) {
      return feature_ < other.feature_;
   } else if(chip_ != other.chip_) {
      return chip_ < other.chip_;
   }
   return false;
}

uint32_t
hardware_table_key_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
hardware_table_key_impl_t::mix_me(hash_mix & h) const {
   h.mix(table_name_); // std::string
   h.mix(feature_); // std::string
   h.mix(chip_); // std::string
}

std::string
hardware_table_key_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "hardware_table_key_t(";
   ss << "table_name='" << table_name_ << "'";
   ss << ", feature='" << feature_ << "'";
   ss << ", chip='" << chip_ << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const hardware_table_key_impl_t& obj) {
   os << obj.to_string();
   return os;
}



hardware_table_high_watermark_impl_t::hardware_table_high_watermark_impl_t() :
      max_entries_(0), timestamp_(0) {
}

hardware_table_high_watermark_impl_t::hardware_table_high_watermark_impl_t(
         uint32_t max_entries, time_t timestamp) :
      max_entries_(max_entries), timestamp_(timestamp) {
}

uint32_t
hardware_table_high_watermark_impl_t::max_entries() const {
   return max_entries_;
}

time_t
hardware_table_high_watermark_impl_t::timestamp() const {
   return timestamp_;
}

bool
hardware_table_high_watermark_impl_t::operator==(
         hardware_table_high_watermark_impl_t const & other) const {
   return max_entries_ == other.max_entries_ &&
          timestamp_ == other.timestamp_;
}

bool
hardware_table_high_watermark_impl_t::operator!=(
         hardware_table_high_watermark_impl_t const & other) const {
   return !operator==(other);
}

bool
hardware_table_high_watermark_impl_t::operator<(
         hardware_table_high_watermark_impl_t const & other) const {
   if(max_entries_ != other.max_entries_) {
      return max_entries_ < other.max_entries_;
   } else if(timestamp_ != other.timestamp_) {
      return timestamp_ < other.timestamp_;
   }
   return false;
}

uint32_t
hardware_table_high_watermark_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
hardware_table_high_watermark_impl_t::mix_me(hash_mix & h) const {
   h.mix(max_entries_); // uint32_t
   h.mix(timestamp_); // time_t
}

std::string
hardware_table_high_watermark_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "hardware_table_high_watermark_t(";
   ss << "max_entries=" << max_entries_;
   ss << ", timestamp=" << timestamp_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const hardware_table_high_watermark_impl_t& obj) {
   os << obj.to_string();
   return os;
}



hardware_table_usage_impl_t::hardware_table_usage_impl_t() :
      used_entries_(0), free_entries_(0), committed_entries_(0) {
}

hardware_table_usage_impl_t::hardware_table_usage_impl_t(
         uint32_t used_entries, uint32_t free_entries, uint32_t committed_entries) :
      used_entries_(used_entries), free_entries_(free_entries),
      committed_entries_(committed_entries) {
}

uint32_t
hardware_table_usage_impl_t::used_entries() const {
   return used_entries_;
}

uint32_t
hardware_table_usage_impl_t::free_entries() const {
   return free_entries_;
}

uint32_t
hardware_table_usage_impl_t::committed_entries() const {
   return committed_entries_;
}

bool
hardware_table_usage_impl_t::operator==(hardware_table_usage_impl_t const & other)
       const {
   return used_entries_ == other.used_entries_ &&
          free_entries_ == other.free_entries_ &&
          committed_entries_ == other.committed_entries_;
}

bool
hardware_table_usage_impl_t::operator!=(hardware_table_usage_impl_t const & other)
       const {
   return !operator==(other);
}

bool
hardware_table_usage_impl_t::operator<(hardware_table_usage_impl_t const & other)
       const {
   if(used_entries_ != other.used_entries_) {
      return used_entries_ < other.used_entries_;
   } else if(free_entries_ != other.free_entries_) {
      return free_entries_ < other.free_entries_;
   } else if(committed_entries_ != other.committed_entries_) {
      return committed_entries_ < other.committed_entries_;
   }
   return false;
}

uint32_t
hardware_table_usage_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
hardware_table_usage_impl_t::mix_me(hash_mix & h) const {
   h.mix(used_entries_); // uint32_t
   h.mix(free_entries_); // uint32_t
   h.mix(committed_entries_); // uint32_t
}

std::string
hardware_table_usage_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "hardware_table_usage_t(";
   ss << "used_entries=" << used_entries_;
   ss << ", free_entries=" << free_entries_;
   ss << ", committed_entries=" << committed_entries_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const hardware_table_usage_impl_t& obj) {
   os << obj.to_string();
   return os;
}



hardware_table_entry_impl_t::hardware_table_entry_impl_t() :
      usage_(hardware_table_usage_t()), max_entries_(0),
      high_watermark_(hardware_table_high_watermark_t()) {
}

hardware_table_entry_impl_t::hardware_table_entry_impl_t(
         hardware_table_usage_t const & usage, uint32_t max_entries,
         hardware_table_high_watermark_t const & high_watermark) :
      usage_(usage), max_entries_(max_entries), high_watermark_(high_watermark) {
}

hardware_table_usage_t
hardware_table_entry_impl_t::usage() const {
   return usage_;
}

uint32_t
hardware_table_entry_impl_t::max_entries() const {
   return max_entries_;
}

hardware_table_high_watermark_t
hardware_table_entry_impl_t::high_watermark() const {
   return high_watermark_;
}

bool
hardware_table_entry_impl_t::operator==(hardware_table_entry_impl_t const & other)
       const {
   return usage_ == other.usage_ &&
          max_entries_ == other.max_entries_ &&
          high_watermark_ == other.high_watermark_;
}

bool
hardware_table_entry_impl_t::operator!=(hardware_table_entry_impl_t const & other)
       const {
   return !operator==(other);
}

bool
hardware_table_entry_impl_t::operator<(hardware_table_entry_impl_t const & other)
       const {
   if(usage_ != other.usage_) {
      return usage_ < other.usage_;
   } else if(max_entries_ != other.max_entries_) {
      return max_entries_ < other.max_entries_;
   } else if(high_watermark_ != other.high_watermark_) {
      return high_watermark_ < other.high_watermark_;
   }
   return false;
}

uint32_t
hardware_table_entry_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
hardware_table_entry_impl_t::mix_me(hash_mix & h) const {
   h.mix(usage_); // hardware_table_usage_t
   h.mix(max_entries_); // uint32_t
   h.mix(high_watermark_); // hardware_table_high_watermark_t
}

std::string
hardware_table_entry_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "hardware_table_entry_t(";
   ss << "usage=" << usage_;
   ss << ", max_entries=" << max_entries_;
   ss << ", high_watermark=" << high_watermark_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const hardware_table_entry_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/hardware_table.h>

#endif // EOS_INLINE_TYPES_HARDWARE_TABLE_IMPL_H
