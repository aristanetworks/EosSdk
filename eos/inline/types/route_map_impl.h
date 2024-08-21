// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ROUTE_MAP_IMPL_H
#define EOS_INLINE_TYPES_ROUTE_MAP_IMPL_H

namespace eos {



link_bandwidth_impl_t::link_bandwidth_impl_t(float value,
                                                    bandwidth_unit_t unit) :
      value_(value), unit_(unit) {
}

link_bandwidth_impl_t::link_bandwidth_impl_t(float value) :
      value_(value), unit_(LINK_BANDWIDTH_UNIT_BIT) {
}

link_bandwidth_impl_t::link_bandwidth_impl_t() :
      value_(0), unit_(LINK_BANDWIDTH_UNIT_BIT) {
}

float
link_bandwidth_impl_t::value() const {
   return value_;
}

void
link_bandwidth_impl_t::value_is(float value) {
   value_ = value;
}

bandwidth_unit_t
link_bandwidth_impl_t::unit() const {
   return unit_;
}

void
link_bandwidth_impl_t::unit_is(bandwidth_unit_t unit) {
   unit_ = unit;
}

bool
link_bandwidth_impl_t::operator==(link_bandwidth_impl_t const & other) const {
   return value_ == other.value_ &&
          unit_ == other.unit_;
}

bool
link_bandwidth_impl_t::operator!=(link_bandwidth_impl_t const & other) const {
   return !operator==(other);
}

bool
link_bandwidth_impl_t::operator<(link_bandwidth_impl_t const & other) const {
   if(value_ != other.value_) {
      return value_ < other.value_;
   } else if(unit_ != other.unit_) {
      return unit_ < other.unit_;
   }
   return false;
}

uint32_t
link_bandwidth_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
link_bandwidth_impl_t::mix_me(hash_mix & h) const {
   h.mix(value_); // float
   h.mix(unit_); // bandwidth_unit_t
}

std::string
link_bandwidth_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "link_bandwidth_t(";
   ss << "value=" << value_;
   ss << ", unit=" << unit_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const link_bandwidth_impl_t& obj) {
   os << obj.to_string();
   return os;
}





route_map_link_bandwidth_impl_t::route_map_link_bandwidth_impl_t() :
      operation_(), asn_(), bandwidth_() {
}

route_map_operation_type_t
route_map_link_bandwidth_impl_t::operation() const {
   return operation_;
}

bgp_asn_t
route_map_link_bandwidth_impl_t::asn() const {
   return asn_;
}

link_bandwidth_t
route_map_link_bandwidth_impl_t::bandwidth() const {
   return bandwidth_;
}

void
route_map_link_bandwidth_impl_t::route_map_operation_type_set_is(
         link_bandwidth_t bandwidth) {
   operation_ = OPERATION_TYPE_SET;
   bandwidth_ = bandwidth;
   asn_ = 0;
}

void
route_map_link_bandwidth_impl_t::route_map_operation_type_delete_is(
         link_bandwidth_t bandwidth, bgp_asn_t asn) {
   operation_ = OPERATION_TYPE_DELETE;
   bandwidth_ = bandwidth;
   asn_ = asn;
}

bool
route_map_link_bandwidth_impl_t::operator==(
         route_map_link_bandwidth_impl_t const & other) const {
   return operation_ == other.operation_ &&
          asn_ == other.asn_ &&
          bandwidth_ == other.bandwidth_;
}

bool
route_map_link_bandwidth_impl_t::operator!=(
         route_map_link_bandwidth_impl_t const & other) const {
   return !operator==(other);
}

bool
route_map_link_bandwidth_impl_t::operator<(
         route_map_link_bandwidth_impl_t const & other) const {
   if(operation_ != other.operation_) {
      return operation_ < other.operation_;
   } else if(asn_ != other.asn_) {
      return asn_ < other.asn_;
   } else if(bandwidth_ != other.bandwidth_) {
      return bandwidth_ < other.bandwidth_;
   }
   return false;
}

uint32_t
route_map_link_bandwidth_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
route_map_link_bandwidth_impl_t::mix_me(hash_mix & h) const {
   h.mix(operation_); // route_map_operation_type_t
   h.mix(asn_); // bgp_asn_t
   h.mix(bandwidth_); // link_bandwidth_t
}

std::string
route_map_link_bandwidth_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "route_map_link_bandwidth_t(";
   ss << "operation=" << operation_;
   ss << ", asn=" << asn_;
   ss << ", bandwidth=" << bandwidth_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const route_map_link_bandwidth_impl_t& obj) {
   os << obj.to_string();
   return os;
}



route_map_entry_impl_t::route_map_entry_impl_t() :
      permit_(true), continue_sequence_(), link_bandwidth_() {
}

route_map_entry_impl_t::route_map_entry_impl_t(bool permit) :
      permit_(permit), continue_sequence_(), link_bandwidth_() {
}

bool
route_map_entry_impl_t::permit() const {
   return permit_;
}

void
route_map_entry_impl_t::permit_is(bool permit) {
   permit_ = permit;
}

route_map_sequence_number_t
route_map_entry_impl_t::continue_sequence() const {
   return continue_sequence_;
}

void
route_map_entry_impl_t::continue_sequence_is(
         route_map_sequence_number_t continue_sequence) {
   continue_sequence_ = continue_sequence;
}

route_map_link_bandwidth_t
route_map_entry_impl_t::link_bandwidth() const {
   return link_bandwidth_;
}

void
route_map_entry_impl_t::link_bandwidth_is(
         route_map_link_bandwidth_t const & link_bandwidth) {
   link_bandwidth_ = link_bandwidth;
}

void
route_map_entry_impl_t::link_bandwidth_is(
         route_map_link_bandwidth_t && link_bandwidth) {
   link_bandwidth_ = std::move(link_bandwidth);
}

void
route_map_entry_impl_t::link_bandwidth_del() {
   link_bandwidth_ = route_map_link_bandwidth_t();
}

bool
route_map_entry_impl_t::operator==(route_map_entry_impl_t const & other) const {
   return permit_ == other.permit_ &&
          continue_sequence_ == other.continue_sequence_ &&
          link_bandwidth_ == other.link_bandwidth_;
}

bool
route_map_entry_impl_t::operator!=(route_map_entry_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
route_map_entry_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
route_map_entry_impl_t::mix_me(hash_mix & h) const {
   h.mix(permit_); // bool
   h.mix(continue_sequence_); // route_map_sequence_number_t
   h.mix(link_bandwidth_); // route_map_link_bandwidth_t
}

std::string
route_map_entry_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "route_map_entry_t(";
   ss << "permit=" << permit_;
   ss << ", continue_sequence=" << continue_sequence_;
   ss << ", link_bandwidth=" << link_bandwidth_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const route_map_entry_impl_t& obj) {
   os << obj.to_string();
   return os;
}



route_map_impl_t::route_map_impl_t() :
      map_entry_() {
}

std::map<route_map_sequence_number_t, route_map_entry_t> const &
route_map_impl_t::map_entry() const {
   return map_entry_;
}

void
route_map_impl_t::map_entry_is(
         
         std::map<route_map_sequence_number_t, route_map_entry_t> const &
         map_entry) {
   map_entry_ = map_entry;
}

void
route_map_impl_t::map_entry_is(
         std::map<route_map_sequence_number_t, route_map_entry_t> && map_entry) {
   map_entry_ = std::move(map_entry);
}

void
route_map_impl_t::map_entry_set(route_map_sequence_number_t const & key,
                                route_map_entry_t const & value) {
   map_entry_[key] = value;
}

void
route_map_impl_t::map_entry_set(route_map_sequence_number_t const & key,
                                route_map_entry_t && value) {
   map_entry_[key] = std::move(value);
}

void
route_map_impl_t::map_entry_del(route_map_sequence_number_t const & key) {
   map_entry_.erase(key);
}

void
route_map_impl_t::map_entry_set(route_map_sequence_number_t && key,
                                route_map_entry_t const & value) {
   map_entry_[std::move(key)] = value;
}

void
route_map_impl_t::map_entry_set(route_map_sequence_number_t && key,
                                route_map_entry_t && value) {
   map_entry_[std::move(key)] = std::move(value);
}

bool
route_map_impl_t::operator==(route_map_impl_t const & other) const {
   return map_entry_ == other.map_entry_;
}

bool
route_map_impl_t::operator!=(route_map_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
route_map_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
route_map_impl_t::mix_me(hash_mix & h) const {
   for (auto it=map_entry_.cbegin();
        it!=map_entry_.cend(); ++it) {
      h.mix(it->first); // route_map_sequence_number_t
      h.mix(it->second); // route_map_entry_t
   }
}

std::string
route_map_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "route_map_t(";
   ss << "map_entry=" <<"'";
   bool first_map_entry = true;
   for (auto it=map_entry_.cbegin();
        it!=map_entry_.cend(); ++it) {
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

std::ostream&
operator<<(std::ostream& os, const route_map_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/route_map.h>

#endif // EOS_INLINE_TYPES_ROUTE_MAP_IMPL_H
