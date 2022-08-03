// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_HARDWARE_TABLE_H
#define EOS_INLINE_TYPES_HARDWARE_TABLE_H

namespace eos {

inline hardware_table_key_t::hardware_table_key_t() :
      table_name_(), feature_(), chip_() {
}

inline hardware_table_key_t::hardware_table_key_t(std::string const & table_name,
                                                  std::string const & feature,
                                                  std::string const & chip) :
      table_name_(table_name), feature_(feature), chip_(chip) {
}

inline hardware_table_key_t::hardware_table_key_t(std::string const & table_name,
                                                  std::string const & feature) :
      table_name_(table_name), feature_(feature), chip_() {
}

inline hardware_table_key_t::hardware_table_key_t(std::string const & table_name) :
      table_name_(table_name), feature_(), chip_() {
}

inline std::string
hardware_table_key_t::table_name() const {
   return table_name_;
}

inline std::string
hardware_table_key_t::feature() const {
   return feature_;
}

inline std::string
hardware_table_key_t::chip() const {
   return chip_;
}

inline bool
hardware_table_key_t::operator==(hardware_table_key_t const & other) const {
   return table_name_ == other.table_name_ &&
          feature_ == other.feature_ &&
          chip_ == other.chip_;
}

inline bool
hardware_table_key_t::operator!=(hardware_table_key_t const & other) const {
   return !operator==(other);
}

inline bool
hardware_table_key_t::operator<(hardware_table_key_t const & other) const {
   if(table_name_ != other.table_name_) {
      return table_name_ < other.table_name_;
   } else if(feature_ != other.feature_) {
      return feature_ < other.feature_;
   } else if(chip_ != other.chip_) {
      return chip_ < other.chip_;
   }
   return false;
}

inline uint32_t
hardware_table_key_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
hardware_table_key_t::mix_me(hash_mix & h) const {
   h.mix(table_name_); // std::string
   h.mix(feature_); // std::string
   h.mix(chip_); // std::string
}

inline std::string
hardware_table_key_t::to_string() const {
   std::ostringstream ss;
   ss << "hardware_table_key_t(";
   ss << "table_name='" << table_name_ << "'";
   ss << ", feature='" << feature_ << "'";
   ss << ", chip='" << chip_ << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const hardware_table_key_t& obj) {
   os << obj.to_string();
   return os;
}



inline hardware_table_high_watermark_t::hardware_table_high_watermark_t() :
      max_entries_(0), timestamp_(0) {
}

inline hardware_table_high_watermark_t::hardware_table_high_watermark_t(
         uint32_t max_entries, time_t timestamp) :
      max_entries_(max_entries), timestamp_(timestamp) {
}

inline uint32_t
hardware_table_high_watermark_t::max_entries() const {
   return max_entries_;
}

inline time_t
hardware_table_high_watermark_t::timestamp() const {
   return timestamp_;
}

inline bool
hardware_table_high_watermark_t::operator==(
         hardware_table_high_watermark_t const & other) const {
   return max_entries_ == other.max_entries_ &&
          timestamp_ == other.timestamp_;
}

inline bool
hardware_table_high_watermark_t::operator!=(
         hardware_table_high_watermark_t const & other) const {
   return !operator==(other);
}

inline bool
hardware_table_high_watermark_t::operator<(
         hardware_table_high_watermark_t const & other) const {
   if(max_entries_ != other.max_entries_) {
      return max_entries_ < other.max_entries_;
   } else if(timestamp_ != other.timestamp_) {
      return timestamp_ < other.timestamp_;
   }
   return false;
}

inline uint32_t
hardware_table_high_watermark_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
hardware_table_high_watermark_t::mix_me(hash_mix & h) const {
   h.mix(max_entries_); // uint32_t
   h.mix(timestamp_); // time_t
}

inline std::string
hardware_table_high_watermark_t::to_string() const {
   std::ostringstream ss;
   ss << "hardware_table_high_watermark_t(";
   ss << "max_entries=" << max_entries_;
   ss << ", timestamp=" << timestamp_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const hardware_table_high_watermark_t& obj) {
   os << obj.to_string();
   return os;
}



inline hardware_table_usage_t::hardware_table_usage_t() :
      used_entries_(0), free_entries_(0), committed_entries_(0) {
}

inline hardware_table_usage_t::hardware_table_usage_t(uint32_t used_entries,
                                                      uint32_t free_entries,
                                                      uint32_t committed_entries) :
      used_entries_(used_entries), free_entries_(free_entries),
      committed_entries_(committed_entries) {
}

inline uint32_t
hardware_table_usage_t::used_entries() const {
   return used_entries_;
}

inline uint32_t
hardware_table_usage_t::free_entries() const {
   return free_entries_;
}

inline uint32_t
hardware_table_usage_t::committed_entries() const {
   return committed_entries_;
}

inline bool
hardware_table_usage_t::operator==(hardware_table_usage_t const & other) const {
   return used_entries_ == other.used_entries_ &&
          free_entries_ == other.free_entries_ &&
          committed_entries_ == other.committed_entries_;
}

inline bool
hardware_table_usage_t::operator!=(hardware_table_usage_t const & other) const {
   return !operator==(other);
}

inline bool
hardware_table_usage_t::operator<(hardware_table_usage_t const & other) const {
   if(used_entries_ != other.used_entries_) {
      return used_entries_ < other.used_entries_;
   } else if(free_entries_ != other.free_entries_) {
      return free_entries_ < other.free_entries_;
   } else if(committed_entries_ != other.committed_entries_) {
      return committed_entries_ < other.committed_entries_;
   }
   return false;
}

inline uint32_t
hardware_table_usage_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
hardware_table_usage_t::mix_me(hash_mix & h) const {
   h.mix(used_entries_); // uint32_t
   h.mix(free_entries_); // uint32_t
   h.mix(committed_entries_); // uint32_t
}

inline std::string
hardware_table_usage_t::to_string() const {
   std::ostringstream ss;
   ss << "hardware_table_usage_t(";
   ss << "used_entries=" << used_entries_;
   ss << ", free_entries=" << free_entries_;
   ss << ", committed_entries=" << committed_entries_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const hardware_table_usage_t& obj) {
   os << obj.to_string();
   return os;
}



inline hardware_table_entry_t::hardware_table_entry_t() :
      usage_(hardware_table_usage_t()), max_entries_(0),
      high_watermark_(hardware_table_high_watermark_t()) {
}

inline hardware_table_entry_t::hardware_table_entry_t(
         hardware_table_usage_t const & usage, uint32_t max_entries,
         hardware_table_high_watermark_t const & high_watermark) :
      usage_(usage), max_entries_(max_entries), high_watermark_(high_watermark) {
}

inline hardware_table_usage_t
hardware_table_entry_t::usage() const {
   return usage_;
}

inline uint32_t
hardware_table_entry_t::max_entries() const {
   return max_entries_;
}

inline hardware_table_high_watermark_t
hardware_table_entry_t::high_watermark() const {
   return high_watermark_;
}

inline bool
hardware_table_entry_t::operator==(hardware_table_entry_t const & other) const {
   return usage_ == other.usage_ &&
          max_entries_ == other.max_entries_ &&
          high_watermark_ == other.high_watermark_;
}

inline bool
hardware_table_entry_t::operator!=(hardware_table_entry_t const & other) const {
   return !operator==(other);
}

inline bool
hardware_table_entry_t::operator<(hardware_table_entry_t const & other) const {
   if(usage_ != other.usage_) {
      return usage_ < other.usage_;
   } else if(max_entries_ != other.max_entries_) {
      return max_entries_ < other.max_entries_;
   } else if(high_watermark_ != other.high_watermark_) {
      return high_watermark_ < other.high_watermark_;
   }
   return false;
}

inline uint32_t
hardware_table_entry_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
hardware_table_entry_t::mix_me(hash_mix & h) const {
   h.mix(usage_); // hardware_table_usage_t
   h.mix(max_entries_); // uint32_t
   h.mix(high_watermark_); // hardware_table_high_watermark_t
}

inline std::string
hardware_table_entry_t::to_string() const {
   std::ostringstream ss;
   ss << "hardware_table_entry_t(";
   ss << "usage=" << usage_;
   ss << ", max_entries=" << max_entries_;
   ss << ", high_watermark=" << high_watermark_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const hardware_table_entry_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_HARDWARE_TABLE_H
