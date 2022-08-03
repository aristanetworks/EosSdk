// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ROUTE_MAP_H
#define EOS_INLINE_TYPES_ROUTE_MAP_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const bandwidth_unit_t & enum_val) {
   if (enum_val==LINK_BANDWIDTH_UNIT_BIT) {
      os << "LINK_BANDWIDTH_UNIT_BIT";
   } else if (enum_val==LINK_BANDWIDTH_UNIT_KILOBIT) {
      os << "LINK_BANDWIDTH_UNIT_KILOBIT";
   } else if (enum_val==LINK_BANDWIDTH_UNIT_MEGABIT) {
      os << "LINK_BANDWIDTH_UNIT_MEGABIT";
   } else if (enum_val==LINK_BANDWIDTH_UNIT_GIGABIT) {
      os << "LINK_BANDWIDTH_UNIT_GIGABIT";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline link_bandwidth_t::link_bandwidth_t(float value, bandwidth_unit_t unit) :
      value_(value), unit_(unit) {
}

inline link_bandwidth_t::link_bandwidth_t(float value) :
      value_(value), unit_(LINK_BANDWIDTH_UNIT_BIT) {
}

inline link_bandwidth_t::link_bandwidth_t() :
      value_(0), unit_(LINK_BANDWIDTH_UNIT_BIT) {
}

inline float
link_bandwidth_t::value() const {
   return value_;
}

inline void
link_bandwidth_t::value_is(float value) {
   value_ = value;
}

inline bandwidth_unit_t
link_bandwidth_t::unit() const {
   return unit_;
}

inline void
link_bandwidth_t::unit_is(bandwidth_unit_t unit) {
   unit_ = unit;
}

inline bool
link_bandwidth_t::operator==(link_bandwidth_t const & other) const {
   return value_ == other.value_ &&
          unit_ == other.unit_;
}

inline bool
link_bandwidth_t::operator!=(link_bandwidth_t const & other) const {
   return !operator==(other);
}

inline bool
link_bandwidth_t::operator<(link_bandwidth_t const & other) const {
   if(value_ != other.value_) {
      return value_ < other.value_;
   } else if(unit_ != other.unit_) {
      return unit_ < other.unit_;
   }
   return false;
}

inline uint32_t
link_bandwidth_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
link_bandwidth_t::mix_me(hash_mix & h) const {
   h.mix(value_); // float
   h.mix(unit_); // bandwidth_unit_t
}

inline std::string
link_bandwidth_t::to_string() const {
   std::ostringstream ss;
   ss << "link_bandwidth_t(";
   ss << "value=" << value_;
   ss << ", unit=" << unit_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const link_bandwidth_t& obj) {
   os << obj.to_string();
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const route_map_operation_type_t & enum_val) {
   if (enum_val==OPERATION_TYPE_NONE) {
      os << "OPERATION_TYPE_NONE";
   } else if (enum_val==OPERATION_TYPE_SET) {
      os << "OPERATION_TYPE_SET";
   } else if (enum_val==OPERATION_TYPE_DELETE) {
      os << "OPERATION_TYPE_DELETE";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline route_map_link_bandwidth_t::route_map_link_bandwidth_t() :
      operation_(), asn_(), bandwidth_() {
}

inline route_map_operation_type_t
route_map_link_bandwidth_t::operation() const {
   return operation_;
}

inline bgp_asn_t
route_map_link_bandwidth_t::asn() const {
   return asn_;
}

inline link_bandwidth_t
route_map_link_bandwidth_t::bandwidth() const {
   return bandwidth_;
}

inline void
route_map_link_bandwidth_t::route_map_operation_type_set_is(
         link_bandwidth_t bandwidth) {
   operation_ = OPERATION_TYPE_SET;
   bandwidth_ = bandwidth;
   asn_ = 0;
}

inline void
route_map_link_bandwidth_t::route_map_operation_type_delete_is(
         link_bandwidth_t bandwidth, bgp_asn_t asn) {
   operation_ = OPERATION_TYPE_DELETE;
   bandwidth_ = bandwidth;
   asn_ = asn;
}

inline bool
route_map_link_bandwidth_t::operator==(route_map_link_bandwidth_t const & other)
       const {
   return operation_ == other.operation_ &&
          asn_ == other.asn_ &&
          bandwidth_ == other.bandwidth_;
}

inline bool
route_map_link_bandwidth_t::operator!=(route_map_link_bandwidth_t const & other)
       const {
   return !operator==(other);
}

inline bool
route_map_link_bandwidth_t::operator<(route_map_link_bandwidth_t const & other)
       const {
   if(operation_ != other.operation_) {
      return operation_ < other.operation_;
   } else if(asn_ != other.asn_) {
      return asn_ < other.asn_;
   } else if(bandwidth_ != other.bandwidth_) {
      return bandwidth_ < other.bandwidth_;
   }
   return false;
}

inline uint32_t
route_map_link_bandwidth_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
route_map_link_bandwidth_t::mix_me(hash_mix & h) const {
   h.mix(operation_); // route_map_operation_type_t
   h.mix(asn_); // bgp_asn_t
   h.mix(bandwidth_); // link_bandwidth_t
}

inline std::string
route_map_link_bandwidth_t::to_string() const {
   std::ostringstream ss;
   ss << "route_map_link_bandwidth_t(";
   ss << "operation=" << operation_;
   ss << ", asn=" << asn_;
   ss << ", bandwidth=" << bandwidth_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const route_map_link_bandwidth_t& obj) {
   os << obj.to_string();
   return os;
}



inline route_map_entry_t::route_map_entry_t() :
      permit_(true), continue_sequence_(), link_bandwidth_() {
}

inline route_map_entry_t::route_map_entry_t(bool permit) :
      permit_(permit), continue_sequence_(), link_bandwidth_() {
}

inline bool
route_map_entry_t::permit() const {
   return permit_;
}

inline void
route_map_entry_t::permit_is(bool permit) {
   permit_ = permit;
}

inline route_map_sequence_number_t
route_map_entry_t::continue_sequence() const {
   return continue_sequence_;
}

inline void
route_map_entry_t::continue_sequence_is(
         route_map_sequence_number_t continue_sequence) {
   continue_sequence_ = continue_sequence;
}

inline route_map_link_bandwidth_t
route_map_entry_t::link_bandwidth() const {
   return link_bandwidth_;
}

inline void
route_map_entry_t::link_bandwidth_is(
         route_map_link_bandwidth_t const & link_bandwidth) {
   link_bandwidth_ = link_bandwidth;
}

inline void
route_map_entry_t::link_bandwidth_del() {
   link_bandwidth_ = route_map_link_bandwidth_t();
}

inline bool
route_map_entry_t::operator==(route_map_entry_t const & other) const {
   return permit_ == other.permit_ &&
          continue_sequence_ == other.continue_sequence_ &&
          link_bandwidth_ == other.link_bandwidth_;
}

inline bool
route_map_entry_t::operator!=(route_map_entry_t const & other) const {
   return !operator==(other);
}

inline uint32_t
route_map_entry_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
route_map_entry_t::mix_me(hash_mix & h) const {
   h.mix(permit_); // bool
   h.mix(continue_sequence_); // route_map_sequence_number_t
   h.mix(link_bandwidth_); // route_map_link_bandwidth_t
}

inline std::string
route_map_entry_t::to_string() const {
   std::ostringstream ss;
   ss << "route_map_entry_t(";
   ss << "permit=" << permit_;
   ss << ", continue_sequence=" << continue_sequence_;
   ss << ", link_bandwidth=" << link_bandwidth_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const route_map_entry_t& obj) {
   os << obj.to_string();
   return os;
}



inline std::map<route_map_sequence_number_t, route_map_entry_t> const &
route_map_t::map_entry() const {
   return map_entry_;
}

inline void
route_map_t::map_entry_is(

         std::map<route_map_sequence_number_t, route_map_entry_t> const &
         map_entry) {
   map_entry_ = map_entry;
}

inline void
route_map_t::map_entry_set(route_map_sequence_number_t const & key,
                           route_map_entry_t const & value) {
   map_entry_[key] = value;
}

inline void
route_map_t::map_entry_del(route_map_sequence_number_t const & key) {
   map_entry_.erase(key);
}

inline bool
route_map_t::operator==(route_map_t const & other) const {
   return map_entry_ == other.map_entry_;
}

inline bool
route_map_t::operator!=(route_map_t const & other) const {
   return !operator==(other);
}

inline uint32_t
route_map_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
route_map_t::mix_me(hash_mix & h) const {
   for (auto it=map_entry_.cbegin(); it!=map_entry_.cend(); ++it) {
      h.mix(it->first); // route_map_sequence_number_t
      h.mix(it->second); // route_map_entry_t
   }
}

inline std::string
route_map_t::to_string() const {
   std::ostringstream ss;
   ss << "route_map_t(";
   ss << "map_entry=" <<"'";
   bool first_map_entry = true;
   for (auto it=map_entry_.cbegin(); it!=map_entry_.cend(); ++it) {
      if (first_map_entry) {
         ss << it->first << "=" << it->second;
         first_map_entry = false;
      } else {
         ss << "," << it->first << "=" << it->second;
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const route_map_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_ROUTE_MAP_H
