// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_STRUCTURED_FILTER_IMPL_H
#define EOS_INLINE_TYPES_STRUCTURED_FILTER_IMPL_H

namespace eos {



protocol_range_impl_t::protocol_range_impl_t() :
      range_start_(), range_end_() {
}

uint32_t
protocol_range_impl_t::range_start() const {
   return range_start_;
}

void
protocol_range_impl_t::range_start_is(uint32_t range_start) {
   range_start_ = range_start;
}

uint32_t
protocol_range_impl_t::range_end() const {
   return range_end_;
}

void
protocol_range_impl_t::range_end_is(uint32_t range_end) {
   if (range_end > TP_MAX_PROTO) {
      panic(invalid_range_error(
         "range_end",
         0,
         TP_MAX_PROTO));
   }
   range_end_ = range_end;
}

bool
protocol_range_impl_t::operator==(protocol_range_impl_t const & other) const {
   return range_start_ == other.range_start_ &&
          range_end_ == other.range_end_;
}

bool
protocol_range_impl_t::operator!=(protocol_range_impl_t const & other) const {
   return !operator==(other);
}

bool
protocol_range_impl_t::operator<(protocol_range_impl_t const & other) const {
   if(range_start_ != other.range_start_) {
      return range_start_ < other.range_start_;
   } else if(range_end_ != other.range_end_) {
      return range_end_ < other.range_end_;
   }
   return false;
}

uint32_t
protocol_range_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
protocol_range_impl_t::mix_me(hash_mix & h) const {
   h.mix(range_start_); // uint32_t
   h.mix(range_end_); // uint32_t
}

std::string
protocol_range_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "protocol_range_t(";
   ss << "range_start=" << range_start_;
   ss << ", range_end=" << range_end_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const protocol_range_impl_t& obj) {
   os << obj.to_string();
   return os;
}



port_range_impl_t::port_range_impl_t() :
      range_start_(), range_end_() {
}

uint32_t
port_range_impl_t::range_start() const {
   return range_start_;
}

void
port_range_impl_t::range_start_is(uint32_t range_start) {
   range_start_ = range_start;
}

uint32_t
port_range_impl_t::range_end() const {
   return range_end_;
}

void
port_range_impl_t::range_end_is(uint32_t range_end) {
   if (range_end > TP_MAX_L4PORT) {
      panic(invalid_range_error(
         "range_end",
         0,
         TP_MAX_L4PORT));
   }
   range_end_ = range_end;
}

bool
port_range_impl_t::operator==(port_range_impl_t const & other) const {
   return range_start_ == other.range_start_ &&
          range_end_ == other.range_end_;
}

bool
port_range_impl_t::operator!=(port_range_impl_t const & other) const {
   return !operator==(other);
}

bool
port_range_impl_t::operator<(port_range_impl_t const & other) const {
   if(range_start_ != other.range_start_) {
      return range_start_ < other.range_start_;
   } else if(range_end_ != other.range_end_) {
      return range_end_ < other.range_end_;
   }
   return false;
}

uint32_t
port_range_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
port_range_impl_t::mix_me(hash_mix & h) const {
   h.mix(range_start_); // uint32_t
   h.mix(range_end_); // uint32_t
}

std::string
port_range_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "port_range_t(";
   ss << "range_start=" << range_start_;
   ss << ", range_end=" << range_end_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const port_range_impl_t& obj) {
   os << obj.to_string();
   return os;
}



port_field_impl_t::port_field_impl_t() :
      src_ports_(), dst_ports_(), src_port_field_sets_(), dst_port_field_sets_() {
}

std::set<port_range_t> const &
port_field_impl_t::src_ports() const {
   return src_ports_;
}

void
port_field_impl_t::src_ports_is(std::set<port_range_t> const & src_ports) {
   src_ports_ = src_ports;
}

void
port_field_impl_t::src_port_set(port_range_t const & value) {
   src_ports_.insert(value);
}

void
port_field_impl_t::src_port_del(port_range_t const & value) {
   src_ports_.erase(value);
}

std::set<port_range_t> const &
port_field_impl_t::dst_ports() const {
   return dst_ports_;
}

void
port_field_impl_t::dst_ports_is(std::set<port_range_t> const & dst_ports) {
   dst_ports_ = dst_ports;
}

void
port_field_impl_t::dst_port_set(port_range_t const & value) {
   dst_ports_.insert(value);
}

void
port_field_impl_t::dst_port_del(port_range_t const & value) {
   dst_ports_.erase(value);
}

std::unordered_set<std::string> const &
port_field_impl_t::src_port_field_sets() const {
   return src_port_field_sets_;
}

void
port_field_impl_t::src_port_field_sets_is(
         std::unordered_set<std::string> const & src_port_field_sets) {
   src_port_field_sets_ = src_port_field_sets;
}

void
port_field_impl_t::src_port_field_set_set(std::string const & value) {
   src_port_field_sets_.insert(value);
}

void
port_field_impl_t::src_port_field_set_del(std::string const & value) {
   src_port_field_sets_.erase(value);
}

std::unordered_set<std::string> const &
port_field_impl_t::dst_port_field_sets() const {
   return dst_port_field_sets_;
}

void
port_field_impl_t::dst_port_field_sets_is(
         std::unordered_set<std::string> const & dst_port_field_sets) {
   dst_port_field_sets_ = dst_port_field_sets;
}

void
port_field_impl_t::dst_port_field_set_set(std::string const & value) {
   dst_port_field_sets_.insert(value);
}

void
port_field_impl_t::dst_port_field_set_del(std::string const & value) {
   dst_port_field_sets_.erase(value);
}

bool
port_field_impl_t::operator==(port_field_impl_t const & other) const {
   return src_ports_ == other.src_ports_ &&
          dst_ports_ == other.dst_ports_ &&
          src_port_field_sets_ == other.src_port_field_sets_ &&
          dst_port_field_sets_ == other.dst_port_field_sets_;
}

bool
port_field_impl_t::operator!=(port_field_impl_t const & other) const {
   return !operator==(other);
}

bool
port_field_impl_t::operator<(port_field_impl_t const & other) const {
   if(src_ports_ != other.src_ports_) {
      return src_ports_ < other.src_ports_;
   } else if(dst_ports_ != other.dst_ports_) {
      return dst_ports_ < other.dst_ports_;
   }
   return false;
}

uint32_t
port_field_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
port_field_impl_t::mix_me(hash_mix & h) const {
   for (auto it=src_ports_.cbegin();
        it!=src_ports_.cend(); ++it) {
      h.mix(*it); // port_range_t
   }
   for (auto it=dst_ports_.cbegin();
        it!=dst_ports_.cend(); ++it) {
      h.mix(*it); // port_range_t
   }
   for (auto it=src_port_field_sets_.cbegin();
        it!=src_port_field_sets_.cend(); ++it) {
      h.mix(*it); // std::string
   }
   for (auto it=dst_port_field_sets_.cbegin();
        it!=dst_port_field_sets_.cend(); ++it) {
      h.mix(*it); // std::string
   }
}

std::string
port_field_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "port_field_t(";
   ss << "src_ports=" <<"'";
   bool first_src_ports = true;
   for (auto it=src_ports_.cbegin();
        it!=src_ports_.cend(); ++it) {
      if (first_src_ports) {
         ss << (*it);
         first_src_ports = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", dst_ports=" <<"'";
   bool first_dst_ports = true;
   for (auto it=dst_ports_.cbegin();
        it!=dst_ports_.cend(); ++it) {
      if (first_dst_ports) {
         ss << (*it);
         first_dst_ports = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", src_port_field_sets=" <<"'";
   bool first_src_port_field_sets = true;
   for (auto it=src_port_field_sets_.cbegin();
        it!=src_port_field_sets_.cend(); ++it) {
      if (first_src_port_field_sets) {
         ss << (*it);
         first_src_port_field_sets = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", dst_port_field_sets=" <<"'";
   bool first_dst_port_field_sets = true;
   for (auto it=dst_port_field_sets_.cbegin();
        it!=dst_port_field_sets_.cend(); ++it) {
      if (first_dst_port_field_sets) {
         ss << (*it);
         first_dst_port_field_sets = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const port_field_impl_t& obj) {
   os << obj.to_string();
   return os;
}



protocol_field_impl_t::protocol_field_impl_t() :
      ports_() {
}

std::map<uint32_t, port_field_t> const &
protocol_field_impl_t::ports() const {
   return ports_;
}

void
protocol_field_impl_t::ports_is(std::map<uint32_t, port_field_t> const & ports) {
   ports_ = ports;
}

void
protocol_field_impl_t::port_set(uint32_t key, port_field_t const & value) {
   ports_[key] = value;
}

void
protocol_field_impl_t::port_del(uint32_t key) {
   ports_.erase(key);
}

bool
protocol_field_impl_t::operator==(protocol_field_impl_t const & other) const {
   return ports_ == other.ports_;
}

bool
protocol_field_impl_t::operator!=(protocol_field_impl_t const & other) const {
   return !operator==(other);
}

bool
protocol_field_impl_t::operator<(protocol_field_impl_t const & other) const {
   if(ports_ != other.ports_) {
      return ports_ < other.ports_;
   }
   return false;
}

uint32_t
protocol_field_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
protocol_field_impl_t::mix_me(hash_mix & h) const {
   for (auto it=ports_.cbegin();
        it!=ports_.cend(); ++it) {
      h.mix(it->first); // uint32_t
      h.mix(it->second); // port_field_t
   }
}

std::string
protocol_field_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "protocol_field_t(";
   ss << "ports=" <<"'";
   bool first_ports = true;
   for (auto it=ports_.cbegin();
        it!=ports_.cend(); ++it) {
      if (first_ports) {
         ss << it->first << "=" << it->second;
         first_ports = false;
      } else {
         ss << "," << it->first << "=" << it->second;
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const protocol_field_impl_t& obj) {
   os << obj.to_string();
   return os;
}






EOS_SDK_PRIVATE void addr_type_check( traffic_policy_rule_type_t filter_type,
                                      ip_addr_mask_t const & value ) {
   std::string const TP_FILTER_TYPE_CONFIG_ERROR_ = \
      "Traffic-policy raw rule type should be either v4 or v6";
   std::string const TP_ADDRESS_TYPE_CONFIG_ERROR_ = \
      "Configured ip address type does not match the traffic-policy filter type";
   af_t expected_af;
   if( filter_type == TRAFFIC_POLICY_RULE_TYPE_IPV4 ) {
      expected_af = AF_IPV4;
   } else if( filter_type == TRAFFIC_POLICY_RULE_TYPE_IPV6 ) {
      expected_af = AF_IPV6;
   } else {
      panic( configuration_error( TP_FILTER_TYPE_CONFIG_ERROR_ ) );
   }
   if( value.af() != expected_af ) {
         panic( configuration_error( TP_ADDRESS_TYPE_CONFIG_ERROR_ ) );
   }
}
   



std::string const TP_PREFIX_FIELDSET_CONFLICT_CONFIG_ERROR_ = \
   "Configure prefixes along with prefix field-set is not allowed";




EOS_SDK_PRIVATE void addr_field_sets_check(
   std::unordered_set<std::string> const & addr_field_sets) {
   if(!addr_field_sets.empty()) {
      panic(configuration_error(TP_PREFIX_FIELDSET_CONFLICT_CONFIG_ERROR_));
   }
}




EOS_SDK_PRIVATE void prefixes_check(
   std::set<ip_addr_mask_t> const & prefixes) {
   if(!prefixes.empty()) {
      panic(configuration_error(TP_PREFIX_FIELDSET_CONFLICT_CONFIG_ERROR_));
   }
}



tp_rule_filter_impl_t::tp_rule_filter_impl_t() :
      src_addrs_(), src_addr_field_sets_(), dst_addrs_(), dst_addr_field_sets_(),
      protocols_(), filter_type_() {
}

tp_rule_filter_impl_t::tp_rule_filter_impl_t(
         traffic_policy_rule_type_t filter_type) :
      src_addrs_(), src_addr_field_sets_(), dst_addrs_(), dst_addr_field_sets_(),
      protocols_(), filter_type_(filter_type) {
}

std::set<ip_addr_mask_t> const &
tp_rule_filter_impl_t::src_addrs() const {
   return src_addrs_;
}

std::unordered_set<std::string> const &
tp_rule_filter_impl_t::src_addr_field_sets() const {
   return src_addr_field_sets_;
}

std::set<ip_addr_mask_t> const &
tp_rule_filter_impl_t::dst_addrs() const {
   return dst_addrs_;
}

std::unordered_set<std::string> const &
tp_rule_filter_impl_t::dst_addr_field_sets() const {
   return dst_addr_field_sets_;
}

std::map<protocol_range_t, protocol_field_t> const &
tp_rule_filter_impl_t::protocols() const {
   return protocols_;
}

void
tp_rule_filter_impl_t::protocols_is(
         std::map<protocol_range_t, protocol_field_t> const & protocols) {
   protocols_ = protocols;
}

void
tp_rule_filter_impl_t::protocol_set(protocol_range_t key,
                                    protocol_field_t const & value) {
   protocols_[key] = value;
}

void
tp_rule_filter_impl_t::protocol_del(protocol_range_t key) {
   protocols_.erase(key);
}

traffic_policy_rule_type_t
tp_rule_filter_impl_t::filter_type() const {
   return filter_type_;
}

void
tp_rule_filter_impl_t::src_addr_set(ip_addr_mask_t const & value) {

      addr_field_sets_check(src_addr_field_sets_);
      addr_type_check(filter_type_, value);
      src_addrs_.insert(value);
                
}

void
tp_rule_filter_impl_t::src_addr_del(ip_addr_mask_t const & value) {
   src_addrs_.erase(value);
}

void
tp_rule_filter_impl_t::src_addrs_is(std::set<ip_addr_mask_t> const & src_addrs) {

      src_addrs_.clear();
      for(auto it = src_addrs.cbegin(); it != src_addrs.cend(); ++it) {
         src_addr_set(*it);
      }
                
}

void
tp_rule_filter_impl_t::dst_addr_set(ip_addr_mask_t const & value) {

      addr_field_sets_check(dst_addr_field_sets_);
      addr_type_check(filter_type_, value);
      dst_addrs_.insert(value);
                
}

void
tp_rule_filter_impl_t::dst_addr_del(ip_addr_mask_t const & value) {
   dst_addrs_.erase(value);
}

void
tp_rule_filter_impl_t::dst_addrs_is(std::set<ip_addr_mask_t> const & dst_addrs) {

      dst_addrs_.clear();
      for(auto it = dst_addrs.cbegin(); it != dst_addrs.cend(); ++it) {
         dst_addr_set(*it);
      }
                
}

void
tp_rule_filter_impl_t::src_addr_field_set_set(std::string const & value) {

      prefixes_check(src_addrs_);
      src_addr_field_sets_.insert(value);
                
}

void
tp_rule_filter_impl_t::src_addr_field_set_del(std::string const & value) {

      src_addr_field_sets_.erase(value);
                
}

void
tp_rule_filter_impl_t::src_addr_field_sets_is(
         std::unordered_set<std::string> const & src_addr_field_sets) {

      if(!src_addr_field_sets.empty()) {
         prefixes_check(src_addrs_);
      }
      src_addr_field_sets_ = src_addr_field_sets;
                
}

void
tp_rule_filter_impl_t::dst_addr_field_set_set(std::string const & value) {

      prefixes_check(dst_addrs_);
      dst_addr_field_sets_.insert(value);
                
}

void
tp_rule_filter_impl_t::dst_addr_field_set_del(std::string const & value) {

      dst_addr_field_sets_.erase(value);
                
}

void
tp_rule_filter_impl_t::dst_addr_field_sets_is(
         std::unordered_set<std::string> const & dst_addr_field_sets) {

      if(!dst_addr_field_sets.empty()) {
         prefixes_check(dst_addrs_);
      }
      dst_addr_field_sets_ = dst_addr_field_sets;
                
}

bool
tp_rule_filter_impl_t::operator==(tp_rule_filter_impl_t const & other) const {
   return src_addrs_ == other.src_addrs_ &&
          src_addr_field_sets_ == other.src_addr_field_sets_ &&
          dst_addrs_ == other.dst_addrs_ &&
          dst_addr_field_sets_ == other.dst_addr_field_sets_ &&
          protocols_ == other.protocols_ &&
          filter_type_ == other.filter_type_;
}

bool
tp_rule_filter_impl_t::operator!=(tp_rule_filter_impl_t const & other) const {
   return !operator==(other);
}

bool
tp_rule_filter_impl_t::operator<(tp_rule_filter_impl_t const & other) const {
   if(src_addrs_ != other.src_addrs_) {
      return src_addrs_ < other.src_addrs_;
   } else if(dst_addrs_ != other.dst_addrs_) {
      return dst_addrs_ < other.dst_addrs_;
   } else if(protocols_ != other.protocols_) {
      return protocols_ < other.protocols_;
   } else if(filter_type_ != other.filter_type_) {
      return filter_type_ < other.filter_type_;
   }
   return false;
}

uint32_t
tp_rule_filter_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
tp_rule_filter_impl_t::mix_me(hash_mix & h) const {
   for (auto it=src_addrs_.cbegin();
        it!=src_addrs_.cend(); ++it) {
      h.mix(*it); // ip_addr_mask_t
   }
   for (auto it=src_addr_field_sets_.cbegin();
        it!=src_addr_field_sets_.cend(); ++it) {
      h.mix(*it); // std::string
   }
   for (auto it=dst_addrs_.cbegin();
        it!=dst_addrs_.cend(); ++it) {
      h.mix(*it); // ip_addr_mask_t
   }
   for (auto it=dst_addr_field_sets_.cbegin();
        it!=dst_addr_field_sets_.cend(); ++it) {
      h.mix(*it); // std::string
   }
   for (auto it=protocols_.cbegin();
        it!=protocols_.cend(); ++it) {
      h.mix(it->first); // protocol_range_t
      h.mix(it->second); // protocol_field_t
   }
   h.mix(filter_type_); // traffic_policy_rule_type_t
}

std::string
tp_rule_filter_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "tp_rule_filter_t(";
   ss << "src_addrs=" <<"'";
   bool first_src_addrs = true;
   for (auto it=src_addrs_.cbegin();
        it!=src_addrs_.cend(); ++it) {
      if (first_src_addrs) {
         ss << (*it);
         first_src_addrs = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", src_addr_field_sets=" <<"'";
   bool first_src_addr_field_sets = true;
   for (auto it=src_addr_field_sets_.cbegin();
        it!=src_addr_field_sets_.cend(); ++it) {
      if (first_src_addr_field_sets) {
         ss << (*it);
         first_src_addr_field_sets = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", dst_addrs=" <<"'";
   bool first_dst_addrs = true;
   for (auto it=dst_addrs_.cbegin();
        it!=dst_addrs_.cend(); ++it) {
      if (first_dst_addrs) {
         ss << (*it);
         first_dst_addrs = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", dst_addr_field_sets=" <<"'";
   bool first_dst_addr_field_sets = true;
   for (auto it=dst_addr_field_sets_.cbegin();
        it!=dst_addr_field_sets_.cend(); ++it) {
      if (first_dst_addr_field_sets) {
         ss << (*it);
         first_dst_addr_field_sets = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", protocols=" <<"'";
   bool first_protocols = true;
   for (auto it=protocols_.cbegin();
        it!=protocols_.cend(); ++it) {
      if (first_protocols) {
         ss << it->first << "=" << it->second;
         first_protocols = false;
      } else {
         ss << "," << it->first << "=" << it->second;
      }
   }
   ss << "'";
   ss << ", filter_type=" << filter_type_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const tp_rule_filter_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/structured_filter.h>

#endif // EOS_INLINE_TYPES_STRUCTURED_FILTER_IMPL_H
