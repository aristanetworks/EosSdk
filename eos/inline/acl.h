// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_ACL_H
#define EOS_INLINE_ACL_H

namespace eos {

enum {
   ALL_ICMP = 65535,
};

// ACL TTL spec constructors and getters/setters

inline acl_ttl_spec_t::acl_ttl_spec_t() : oper_(ACL_RANGE_ANY), ttl_(0) {
}

inline acl_range_operator_t acl_ttl_spec_t::oper() const {
   return oper_;
}

inline uint8_t acl_ttl_spec_t::ttl() const {
   return ttl_;
}

inline void acl_ttl_spec_t::oper_is(acl_range_operator_t a) {
  oper_ = a;
}

inline void acl_ttl_spec_t::ttl_is(uint8_t u) {
  ttl_ = u;
}

inline acl_ttl_spec_eq_t::acl_ttl_spec_eq_t(uint8_t ttl) {
   oper_ = ACL_RANGE_EQ;
   ttl_ = ttl;
}

inline acl_ttl_spec_neq_t::acl_ttl_spec_neq_t(uint8_t ttl) {
   oper_ = ACL_RANGE_NEQ;
   ttl_ = ttl;
}

inline acl_ttl_spec_gt_t::acl_ttl_spec_gt_t(uint8_t ttl) {
   oper_ = ACL_RANGE_GT;
   ttl_ = ttl;
}

inline acl_ttl_spec_lt_t::acl_ttl_spec_lt_t(uint8_t ttl) {
   oper_ = ACL_RANGE_LT;
   ttl_ = ttl;
}

inline acl_ttl_spec_any_t::acl_ttl_spec_any_t() {
   oper_ = ACL_RANGE_ANY;
   ttl_ = 0;
}

// ACL port spec constructors and getters/setters

inline acl_port_spec_t::acl_port_spec_t() : oper_(ACL_RANGE_ANY), ports_() {
}

inline acl_range_operator_t acl_port_spec_t::oper() const {
   return oper_;
}

inline std::list<uint16_t> const & acl_port_spec_t::ports() const{
  return ports_;
}

inline void acl_port_spec_t::oper_is(acl_range_operator_t a) {
  oper_ = a;
}

inline void acl_port_spec_t::ports_is(std::list<uint16_t> const & l) {
  ports_ = l;
}

inline acl_port_spec_eq_t::acl_port_spec_eq_t(uint16_t port) {
   oper_ = ACL_RANGE_EQ;
   ports_.push_back(port);
}

inline acl_port_spec_eq_t::acl_port_spec_eq_t(std::list<uint16_t> const & ports) {
   oper_ = ACL_RANGE_EQ;
   for (std::list<uint16_t>::const_iterator pit = ports.cbegin(); 
        pit != ports.cend(); ++pit) {
      ports_.push_back(*pit);
   }
}

inline acl_port_spec_neq_t::acl_port_spec_neq_t(uint16_t port) {
   oper_ = ACL_RANGE_NEQ;
   ports_.push_back(port);
}

inline acl_port_spec_neq_t::acl_port_spec_neq_t(std::list<uint16_t> const & ports) {
   oper_ = ACL_RANGE_NEQ;
   for (std::list<uint16_t>::const_iterator pit = ports.cbegin();
        pit != ports.cend(); ++pit) {
      ports_.push_back(*pit);
   }
}

inline acl_port_spec_between_t::acl_port_spec_between_t(uint16_t low,
                                                        uint16_t high) {
   oper_ = ACL_RANGE_BETWEEN;
   ports_.push_back(low);
   ports_.push_back(high);
}

inline acl_port_spec_gt_t::acl_port_spec_gt_t(uint16_t port) {
   oper_ = ACL_RANGE_GT;
   ports_.push_back(port);
}

inline acl_port_spec_lt_t::acl_port_spec_lt_t(uint16_t port) {
   oper_ = ACL_RANGE_LT;
   ports_.push_back(port);
}

inline acl_port_spec_any_t::acl_port_spec_any_t() {
   oper_ = ACL_RANGE_ANY;
}

// ACL Key constructors and getters

inline acl_key_t::acl_key_t() : acl_name_(), acl_type_(ACL_TYPE_NULL) {
}

inline acl_key_t::acl_key_t(std::string const & acl_name, acl_type_t acl_type)
   : acl_name_(acl_name), acl_type_(acl_type) {
}

inline std::string const acl_key_t::acl_name() const {
   return acl_name_;
}

inline acl_type_t acl_key_t::acl_type() const {
   return acl_type_;
}

inline bool
acl_key_t::operator() (acl_key_t const & lhs, acl_key_t const & rhs) const {
   return lhs.acl_name_ < rhs.acl_name_;
}

inline bool acl_key_t::operator==(acl_key_t const & other) const {
   return acl_name_ == other.acl_name_ &&
      acl_type_ == other.acl_type_;
}

// ACL Rule Base constructors and getters/setters

// Default values match internal TACC type default values
inline acl_rule_base_t::acl_rule_base_t() :
      action_(ACL_PERMIT), log_(false), tracked_(false) {
}

inline bool acl_rule_base_t::log() const {
  return log_;
}

inline bool acl_rule_base_t::tracked() const {
  return tracked_;
}

inline acl_action_t acl_rule_base_t::action() const {
  return action_;
}

inline void acl_rule_base_t::log_is(bool l) {
  log_ = l;
}

inline void acl_rule_base_t::tracked_is(bool t) {
  tracked_ = t;
}

inline void acl_rule_base_t::action_is(acl_action_t a) {
  action_ = a;
}

// ACL Rule Ip constructors and getters/setters

// Constructor for concrete rule ip type passed to acl_add_rule() variants
inline acl_rule_ip_t::acl_rule_ip_t() : vlan_(), vlan_mask_(0xFFF),
                                        inner_vlan_(), inner_vlan_mask_(0xFFF),
                                        ip_protocol_(),
                                        source_addr_(), destination_addr_(),
                                        source_port_(), destination_port_(),
                                        tcp_flags_(),
                                        established_(),
                                        icmp_type_(ALL_ICMP), icmp_code_(ALL_ICMP),
                                        priority_value_(), priority_mask_(),
                                        match_fragments_(), match_ip_priority_() {
}

inline vlan_id_t acl_rule_ip_t::inner_vlan() const {
  return inner_vlan_;
}

inline vlan_id_t acl_rule_ip_t::vlan() const {
  return vlan_;
}

inline vlan_id_t acl_rule_ip_t::vlan_mask() const {
  return vlan_mask_;
}

inline vlan_id_t acl_rule_ip_t::inner_vlan_mask() const {
  return inner_vlan_mask_;
}

inline ip_addr_mask_t acl_rule_ip_t::source_addr() const {
  return source_addr_;
}

inline ip_addr_mask_t acl_rule_ip_t::destination_addr() const {
  return destination_addr_;
}

inline acl_port_spec_t acl_rule_ip_t::source_port() const {
  return source_port_;
}

inline acl_port_spec_t acl_rule_ip_t::destination_port() const {
  return destination_port_;
}

inline acl_ttl_spec_t acl_rule_ip_t::ttl() const {
  return ttl_;
}

inline uint8_t acl_rule_ip_t::ip_protocol() const {
  return ip_protocol_;
}

inline uint16_t acl_rule_ip_t::tcp_flags() const {
  return tcp_flags_;
}

inline bool acl_rule_ip_t::established() const {
  return established_;
}

inline uint16_t acl_rule_ip_t::icmp_type() const {
  return icmp_type_;
}

inline uint16_t acl_rule_ip_t::icmp_code() const {
  return icmp_code_;
}

inline uint8_t acl_rule_ip_t::priority_value() const {
  return priority_value_;
}

inline uint8_t acl_rule_ip_t::priority_mask() const {
  return priority_mask_;
}

inline bool acl_rule_ip_t::match_fragments() const {
  return match_fragments_;
}

inline bool acl_rule_ip_t::match_ip_priority() const {
  return match_ip_priority_;
}

inline void acl_rule_ip_t::vlan_is(vlan_id_t v) {
  vlan_ = v;
}

inline void acl_rule_ip_t::inner_vlan_is(vlan_id_t v) {
  inner_vlan_ = v;
}

inline void acl_rule_ip_t::vlan_mask_is(vlan_id_t v) {
  vlan_mask_ = v;
}

inline void acl_rule_ip_t::inner_vlan_mask_is(vlan_id_t v) {
  inner_vlan_mask_ = v;
}

inline void acl_rule_ip_t::source_addr_is(ip_addr_mask_t const & ip) {
  source_addr_ = ip;
}

inline void acl_rule_ip_t::destination_addr_is(ip_addr_mask_t const & ip) {
  destination_addr_ = ip;
}

inline void acl_rule_ip_t::source_port_is(acl_port_spec_t const & a) {
  source_port_ = a;
}

inline void acl_rule_ip_t::destination_port_is(acl_port_spec_t const & a) {
  destination_port_ = a;
}

inline void acl_rule_ip_t::ttl_is(acl_ttl_spec_t t) {
  ttl_ = t;
}

inline void acl_rule_ip_t::ip_protocol_is(uint8_t ip) {
  ip_protocol_ = ip;
}

inline void acl_rule_ip_t::tcp_flags_is(uint16_t n) {
  tcp_flags_ = n;
}

inline void acl_rule_ip_t::established_is(bool b) {
  established_ = b;
}

inline void acl_rule_ip_t::icmp_type_is(uint16_t n) {
  icmp_type_ = n;
}

inline void acl_rule_ip_t::icmp_code_is(uint16_t n) {
  icmp_code_ = n;
}

inline void acl_rule_ip_t::priority_value_is(uint8_t n) {
  priority_value_ = n;
}

inline void acl_rule_ip_t::priority_mask_is(uint8_t n) {
  priority_mask_ = n;
}

inline void acl_rule_ip_t::match_fragments_is(bool b) {
  match_fragments_ = b;
}

inline void acl_rule_ip_t::match_ip_priority_is(bool b) {
  match_ip_priority_ = b;
}

// ACL Rule Eth constructors and getters/setters

// Constructor for concrete rule eth type passed to acl_add_rule() variants
inline acl_rule_eth_t::acl_rule_eth_t() : vlan_(), vlan_mask_(0xFFF),
                                          inner_vlan_(), inner_vlan_mask_(0xFFF),
                                          source_addr_(), source_mask_(),
                                          destination_addr_(), destination_mask_() {
}

inline vlan_id_t acl_rule_eth_t::vlan() const {
  return vlan_;
}

inline vlan_id_t acl_rule_eth_t::vlan_mask() const {
  return vlan_mask_;
}

inline vlan_id_t acl_rule_eth_t::inner_vlan() const {
  return inner_vlan_;
}

inline vlan_id_t acl_rule_eth_t::inner_vlan_mask() const {
  return inner_vlan_mask_;
}

inline eth_addr_t acl_rule_eth_t::source_addr() const {
  return source_addr_;
}

inline eth_addr_t acl_rule_eth_t::source_mask() const {
  return source_mask_;
}

inline eth_addr_t acl_rule_eth_t::destination_addr() const {
  return destination_addr_;
}

inline eth_addr_t acl_rule_eth_t::destination_mask() const{
  return destination_mask_;
}

inline void acl_rule_eth_t::vlan_is(vlan_id_t v) {
  vlan_ = v;
}

inline void acl_rule_eth_t::vlan_mask_is(vlan_id_t v) {
  vlan_mask_ = v;
}

inline void acl_rule_eth_t::inner_vlan_is(vlan_id_t v) {
  inner_vlan_ = v;
}

inline void acl_rule_eth_t::inner_vlan_mask_is(vlan_id_t v) {
  inner_vlan_mask_ = v;
}

inline void acl_rule_eth_t::source_addr_is(eth_addr_t const & e) {
  source_addr_ = e;
}

inline void acl_rule_eth_t::source_mask_is(eth_addr_t const & e) {
  source_mask_ = e;
}

inline void acl_rule_eth_t::destination_addr_is(eth_addr_t const & e) {
  destination_addr_ = e;
}

inline void acl_rule_eth_t::destination_mask_is(eth_addr_t const & e) {
  destination_mask_ = e;
}


inline acl_mgr * acl_handler::get_acl_mgr() const {
   return mgr_;
}

}  // end namespace eos

#endif // EOS_INLINE_ACL_H
