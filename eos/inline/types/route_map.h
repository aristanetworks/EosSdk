// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ROUTE_MAP_H
#define EOS_INLINE_TYPES_ROUTE_MAP_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const bandwidth_unit_t & enum_val) {
   if (enum_val==BIT) {
      os << "BIT";
   } else if (enum_val==KILOBIT) {
      os << "KILOBIT";
   } else if (enum_val==MEGABIT) {
      os << "MEGABIT";
   } else if (enum_val==GIGABIT) {
      os << "GIGABIT";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline link_bandwidth_t::link_bandwidth_t() :
      value_(), unit_() {
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
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&value_,
              sizeof(float), ret);
   ret = hash_mix::mix((uint8_t *)&unit_,
              sizeof(bandwidth_unit_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
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

inline uint32_t
route_map_link_bandwidth_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&operation_,
              sizeof(route_map_operation_type_t), ret);
   ret = hash_mix::mix((uint8_t *)&asn_,
              sizeof(bgp_asn_t), ret);
   ret ^= bandwidth_.hash();
   ret = hash_mix::final_mix(ret);
   return ret;
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
      sequence_number_(), permit_(true), link_bandwidth_() {
}

inline route_map_entry_t::route_map_entry_t(
         route_map_sequence_number_t sequence_number) :
      sequence_number_(sequence_number), permit_(true), link_bandwidth_() {
}

inline route_map_entry_t::route_map_entry_t(
         route_map_sequence_number_t sequence_number, bool permit) :
      sequence_number_(sequence_number), permit_(permit), link_bandwidth_() {
}

inline route_map_sequence_number_t
route_map_entry_t::sequence_number() const {
   return sequence_number_;
}

inline void
route_map_entry_t::sequence_number_is(route_map_sequence_number_t sequence_number) {
   sequence_number_ = sequence_number;
}

inline bool
route_map_entry_t::permit() const {
   return permit_;
}

inline void
route_map_entry_t::permit_is(bool permit) {
   permit_ = permit;
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

inline uint32_t
route_map_entry_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&sequence_number_,
               sizeof(route_map_sequence_number_t), ret);
   ret = hash_mix::mix((uint8_t *)&permit_,
               sizeof(bool), ret);
   ret ^= link_bandwidth_.hash();
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline bool
route_map_entry_t::operator==(route_map_entry_t const & other) const {
   return sequence_number_ == other.sequence_number_ &&
          permit_ == other.permit_ &&
          link_bandwidth_ == other.link_bandwidth_;
}

inline bool
route_map_entry_t::operator!=(route_map_entry_t const & other) const {
   return !operator==(other);
}

inline bool
route_map_entry_t::operator<(route_map_entry_t const & other) const {
   if(sequence_number_ != other.sequence_number_) {
      return sequence_number_ < other.sequence_number_;
   } else if(permit_ != other.permit_) {
      return permit_ < other.permit_;
   } else if(link_bandwidth_ != other.link_bandwidth_) {
      return link_bandwidth_ < other.link_bandwidth_;
   }
   return false;
}

inline std::string
route_map_entry_t::to_string() const {
   std::ostringstream ss;
   ss << "route_map_entry_t(";
   ss << "sequence_number=" << sequence_number_;
   ss << ", permit=" << permit_;
   ss << ", link_bandwidth=" << link_bandwidth_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const route_map_entry_t& obj) {
   os << obj.to_string();
   return os;
}



inline route_map_name_t
route_map_t::name() const {
   return name_;
}

inline void
route_map_t::name_is(route_map_name_t const & name) {
   name_ = name;
}

inline std::map<route_map_sequence_number_t, route_map_entry_t> const &
route_map_t::map_entry() const {
   return map_entry_;
}

inline void
route_map_t::map_entry_is(

         std::map<route_map_sequence_number_t, route_map_entry_t> const & map_entry)
       {
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
   return name_ == other.name_ &&
          map_entry_ == other.map_entry_;
}

inline bool
route_map_t::operator!=(route_map_t const & other) const {
   return !operator==(other);
}

inline bool
route_map_t::operator<(route_map_t const & other) const {
   if(name_ != other.name_) {
      return name_ < other.name_;
   } else if(map_entry_ != other.map_entry_) {
      return map_entry_ < other.map_entry_;
   }
   return false;
}

inline uint32_t
route_map_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&name_,
              sizeof(route_map_name_t), ret);
   for (auto it=map_entry_.cbegin(); it!=map_entry_.cend(); ++it) {
      ret = hash_mix::mix((uint8_t *)&it->first,
                 sizeof(route_map_sequence_number_t), ret);
      ret = hash_mix::mix((uint8_t *)&it->second,
                 sizeof(route_map_entry_t), ret);
   }
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
route_map_t::to_string() const {
   std::ostringstream ss;
   ss << "route_map_t(";
   ss << "name=" << name_;
   ss << ", map_entry=" <<"'";
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
