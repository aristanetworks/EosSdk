// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ROUTE_MAP_H
#define EOS_INLINE_TYPES_ROUTE_MAP_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
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


float
link_bandwidth_t::value() const {
   return pimpl->value();
}
void
link_bandwidth_t::value_is(float value) {
   pimpl->value_is(value);
}
bandwidth_unit_t
link_bandwidth_t::unit() const {
   return pimpl->unit();
}
void
link_bandwidth_t::unit_is(bandwidth_unit_t unit) {
   pimpl->unit_is(unit);
}
bool
link_bandwidth_t::operator==(link_bandwidth_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
link_bandwidth_t::operator!=(link_bandwidth_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
link_bandwidth_t::operator<(link_bandwidth_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
link_bandwidth_t::hash() const {
   return pimpl->hash();
}
void
link_bandwidth_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
link_bandwidth_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const link_bandwidth_t& obj) {
   return operator<<(os, *obj.pimpl);
}


EOS_SDK_PUBLIC std::ostream&
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


route_map_operation_type_t
route_map_link_bandwidth_t::operation() const {
   return pimpl->operation();
}
bgp_asn_t
route_map_link_bandwidth_t::asn() const {
   return pimpl->asn();
}
link_bandwidth_t
route_map_link_bandwidth_t::bandwidth() const {
   return pimpl->bandwidth();
}
void
route_map_link_bandwidth_t::route_map_operation_type_set_is(
         link_bandwidth_t bandwidth) {
   pimpl->route_map_operation_type_set_is(bandwidth);
}
void
route_map_link_bandwidth_t::route_map_operation_type_delete_is(
         link_bandwidth_t bandwidth, bgp_asn_t asn) {
   pimpl->route_map_operation_type_delete_is(bandwidth, asn);
}
bool
route_map_link_bandwidth_t::operator==(route_map_link_bandwidth_t const & other)
       const {
   return pimpl->operator==(*other.pimpl);
}
bool
route_map_link_bandwidth_t::operator!=(route_map_link_bandwidth_t const & other)
       const {
   return pimpl->operator!=(*other.pimpl);
}
bool
route_map_link_bandwidth_t::operator<(route_map_link_bandwidth_t const & other)
       const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
route_map_link_bandwidth_t::hash() const {
   return pimpl->hash();
}
void
route_map_link_bandwidth_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
route_map_link_bandwidth_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const route_map_link_bandwidth_t& obj) {
   return operator<<(os, *obj.pimpl);
}


bool
route_map_entry_t::permit() const {
   return pimpl->permit();
}
void
route_map_entry_t::permit_is(bool permit) {
   pimpl->permit_is(permit);
}
route_map_sequence_number_t
route_map_entry_t::continue_sequence() const {
   return pimpl->continue_sequence();
}
void
route_map_entry_t::continue_sequence_is(
         route_map_sequence_number_t continue_sequence) {
   pimpl->continue_sequence_is(continue_sequence);
}
route_map_link_bandwidth_t
route_map_entry_t::link_bandwidth() const {
   return pimpl->link_bandwidth();
}
void
route_map_entry_t::link_bandwidth_is(
         route_map_link_bandwidth_t const & link_bandwidth) {
   pimpl->link_bandwidth_is(link_bandwidth);
}
void
route_map_entry_t::link_bandwidth_del() {
   pimpl->link_bandwidth_del();
}
bool
route_map_entry_t::operator==(route_map_entry_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
route_map_entry_t::operator!=(route_map_entry_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
route_map_entry_t::hash() const {
   return pimpl->hash();
}
void
route_map_entry_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
route_map_entry_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const route_map_entry_t& obj) {
   return operator<<(os, *obj.pimpl);
}


std::map<route_map_sequence_number_t, route_map_entry_t> const &
route_map_t::map_entry() const {
   return pimpl->map_entry();
}
void
route_map_t::map_entry_is(
         
         std::map<route_map_sequence_number_t, route_map_entry_t> const &
         map_entry) {
   pimpl->map_entry_is(map_entry);
}
void
route_map_t::map_entry_set(route_map_sequence_number_t const & key,
                           route_map_entry_t const & value) {
   pimpl->map_entry_set(key, value);
}
void
route_map_t::map_entry_del(route_map_sequence_number_t const & key) {
   pimpl->map_entry_del(key);
}
bool
route_map_t::operator==(route_map_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
route_map_t::operator!=(route_map_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
route_map_t::hash() const {
   return pimpl->hash();
}
void
route_map_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
route_map_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const route_map_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_ROUTE_MAP_H
