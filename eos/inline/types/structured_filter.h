// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_STRUCTURED_FILTER_H
#define EOS_INLINE_TYPES_STRUCTURED_FILTER_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const tp_max_values_t & enum_val) {
   if (enum_val==TP_MAX_PROTO) {
      os << "TP_MAX_PROTO";
   } else if (enum_val==TP_MAX_L4PORT) {
      os << "TP_MAX_L4PORT";
   } else {
      os << "Unknown value";
   }
   return os;
}


uint32_t
protocol_range_t::range_start() const {
   return pimpl->range_start();
}
void
protocol_range_t::range_start_is(uint32_t range_start) {
   pimpl->range_start_is(range_start);
}
uint32_t
protocol_range_t::range_end() const {
   return pimpl->range_end();
}
void
protocol_range_t::range_end_is(uint32_t range_end) {
   pimpl->range_end_is(range_end);
}
bool
protocol_range_t::operator==(protocol_range_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
protocol_range_t::operator!=(protocol_range_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
protocol_range_t::operator<(protocol_range_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
protocol_range_t::hash() const {
   return pimpl->hash();
}
void
protocol_range_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
protocol_range_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const protocol_range_t& obj) {
   return operator<<(os, *obj.pimpl);
}


uint32_t
port_range_t::range_start() const {
   return pimpl->range_start();
}
void
port_range_t::range_start_is(uint32_t range_start) {
   pimpl->range_start_is(range_start);
}
uint32_t
port_range_t::range_end() const {
   return pimpl->range_end();
}
void
port_range_t::range_end_is(uint32_t range_end) {
   pimpl->range_end_is(range_end);
}
bool
port_range_t::operator==(port_range_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
port_range_t::operator!=(port_range_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
port_range_t::operator<(port_range_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
port_range_t::hash() const {
   return pimpl->hash();
}
void
port_range_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
port_range_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const port_range_t& obj) {
   return operator<<(os, *obj.pimpl);
}


std::set<port_range_t> const &
port_field_t::src_ports() const {
   return pimpl->src_ports();
}
void
port_field_t::src_ports_is(std::set<port_range_t> const & src_ports) {
   pimpl->src_ports_is(src_ports);
}
void
port_field_t::src_port_set(port_range_t const & value) {
   pimpl->src_port_set(value);
}
void
port_field_t::src_port_del(port_range_t const & value) {
   pimpl->src_port_del(value);
}
std::set<port_range_t> const &
port_field_t::dst_ports() const {
   return pimpl->dst_ports();
}
void
port_field_t::dst_ports_is(std::set<port_range_t> const & dst_ports) {
   pimpl->dst_ports_is(dst_ports);
}
void
port_field_t::dst_port_set(port_range_t const & value) {
   pimpl->dst_port_set(value);
}
void
port_field_t::dst_port_del(port_range_t const & value) {
   pimpl->dst_port_del(value);
}
std::unordered_set<std::string> const &
port_field_t::src_port_field_sets() const {
   return pimpl->src_port_field_sets();
}
void
port_field_t::src_port_field_sets_is(
         std::unordered_set<std::string> const & src_port_field_sets) {
   pimpl->src_port_field_sets_is(src_port_field_sets);
}
void
port_field_t::src_port_field_set_set(std::string const & value) {
   pimpl->src_port_field_set_set(value);
}
void
port_field_t::src_port_field_set_del(std::string const & value) {
   pimpl->src_port_field_set_del(value);
}
std::unordered_set<std::string> const &
port_field_t::dst_port_field_sets() const {
   return pimpl->dst_port_field_sets();
}
void
port_field_t::dst_port_field_sets_is(
         std::unordered_set<std::string> const & dst_port_field_sets) {
   pimpl->dst_port_field_sets_is(dst_port_field_sets);
}
void
port_field_t::dst_port_field_set_set(std::string const & value) {
   pimpl->dst_port_field_set_set(value);
}
void
port_field_t::dst_port_field_set_del(std::string const & value) {
   pimpl->dst_port_field_set_del(value);
}
bool
port_field_t::operator==(port_field_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
port_field_t::operator!=(port_field_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
port_field_t::operator<(port_field_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
port_field_t::hash() const {
   return pimpl->hash();
}
void
port_field_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
port_field_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const port_field_t& obj) {
   return operator<<(os, *obj.pimpl);
}


std::map<uint32_t, port_field_t> const &
protocol_field_t::ports() const {
   return pimpl->ports();
}
void
protocol_field_t::ports_is(std::map<uint32_t, port_field_t> const & ports) {
   pimpl->ports_is(ports);
}
void
protocol_field_t::port_set(uint32_t key, port_field_t const & value) {
   pimpl->port_set(key, value);
}
void
protocol_field_t::port_del(uint32_t key) {
   pimpl->port_del(key);
}
bool
protocol_field_t::operator==(protocol_field_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
protocol_field_t::operator!=(protocol_field_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
protocol_field_t::operator<(protocol_field_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
protocol_field_t::hash() const {
   return pimpl->hash();
}
void
protocol_field_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
protocol_field_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const protocol_field_t& obj) {
   return operator<<(os, *obj.pimpl);
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const traffic_policy_rule_type_t & enum_val) {
   if (enum_val==TRAFFIC_POLICY_RULE_TYPE_NULL) {
      os << "TRAFFIC_POLICY_RULE_TYPE_NULL";
   } else if (enum_val==TRAFFIC_POLICY_RULE_TYPE_IPV4) {
      os << "TRAFFIC_POLICY_RULE_TYPE_IPV4";
   } else if (enum_val==TRAFFIC_POLICY_RULE_TYPE_IPV6) {
      os << "TRAFFIC_POLICY_RULE_TYPE_IPV6";
   } else {
      os << "Unknown value";
   }
   return os;
}










std::set<ip_addr_mask_t> const &
tp_rule_filter_t::src_addrs() const {
   return pimpl->src_addrs();
}
std::unordered_set<std::string> const &
tp_rule_filter_t::src_addr_field_sets() const {
   return pimpl->src_addr_field_sets();
}
std::set<ip_addr_mask_t> const &
tp_rule_filter_t::dst_addrs() const {
   return pimpl->dst_addrs();
}
std::unordered_set<std::string> const &
tp_rule_filter_t::dst_addr_field_sets() const {
   return pimpl->dst_addr_field_sets();
}
std::map<protocol_range_t, protocol_field_t> const &
tp_rule_filter_t::protocols() const {
   return pimpl->protocols();
}
void
tp_rule_filter_t::protocols_is(
         std::map<protocol_range_t, protocol_field_t> const & protocols) {
   pimpl->protocols_is(protocols);
}
void
tp_rule_filter_t::protocol_set(protocol_range_t key,
                               protocol_field_t const & value) {
   pimpl->protocol_set(key, value);
}
void
tp_rule_filter_t::protocol_del(protocol_range_t key) {
   pimpl->protocol_del(key);
}
traffic_policy_rule_type_t
tp_rule_filter_t::filter_type() const {
   return pimpl->filter_type();
}
void
tp_rule_filter_t::src_addr_set(ip_addr_mask_t const & value) {
   pimpl->src_addr_set(value);
}
void
tp_rule_filter_t::src_addr_del(ip_addr_mask_t const & value) {
   pimpl->src_addr_del(value);
}
void
tp_rule_filter_t::src_addrs_is(std::set<ip_addr_mask_t> const & src_addrs) {
   pimpl->src_addrs_is(src_addrs);
}
void
tp_rule_filter_t::dst_addr_set(ip_addr_mask_t const & value) {
   pimpl->dst_addr_set(value);
}
void
tp_rule_filter_t::dst_addr_del(ip_addr_mask_t const & value) {
   pimpl->dst_addr_del(value);
}
void
tp_rule_filter_t::dst_addrs_is(std::set<ip_addr_mask_t> const & dst_addrs) {
   pimpl->dst_addrs_is(dst_addrs);
}
void
tp_rule_filter_t::src_addr_field_set_set(std::string const & value) {
   pimpl->src_addr_field_set_set(value);
}
void
tp_rule_filter_t::src_addr_field_set_del(std::string const & value) {
   pimpl->src_addr_field_set_del(value);
}
void
tp_rule_filter_t::src_addr_field_sets_is(
         std::unordered_set<std::string> const & src_addr_field_sets) {
   pimpl->src_addr_field_sets_is(src_addr_field_sets);
}
void
tp_rule_filter_t::dst_addr_field_set_set(std::string const & value) {
   pimpl->dst_addr_field_set_set(value);
}
void
tp_rule_filter_t::dst_addr_field_set_del(std::string const & value) {
   pimpl->dst_addr_field_set_del(value);
}
void
tp_rule_filter_t::dst_addr_field_sets_is(
         std::unordered_set<std::string> const & dst_addr_field_sets) {
   pimpl->dst_addr_field_sets_is(dst_addr_field_sets);
}
bool
tp_rule_filter_t::operator==(tp_rule_filter_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
tp_rule_filter_t::operator!=(tp_rule_filter_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
tp_rule_filter_t::operator<(tp_rule_filter_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
tp_rule_filter_t::hash() const {
   return pimpl->hash();
}
void
tp_rule_filter_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
tp_rule_filter_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const tp_rule_filter_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_STRUCTURED_FILTER_H
