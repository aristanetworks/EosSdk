// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_ACL_H
#define EOS_INLINE_ACL_H

namespace eos {

enum {
   ALL_ICMP = 65535,
};

inline bool
acl_key_t::operator() (acl_key_t const & lhs, acl_key_t const & rhs) const {
   return lhs.acl_name_ < rhs.acl_name_;
}

inline bool
acl_key_t::operator==(acl_key_t const & other) const {
   return acl_name_ == other.acl_name_ &&
      acl_type_ == other.acl_type_;
}

inline std::string const
acl_key_t::acl_name() const {
   return acl_name_;
}

inline acl_type_t
acl_key_t::acl_type() const {
   return acl_type_;
}

// Constructors for ACL keys and port/TTL specifiers

inline acl_key_t::acl_key_t() : acl_name_(), acl_type_(ACL_TYPE_NULL) {
}

inline acl_key_t::acl_key_t(std::string const & acl_name, acl_type_t acl_type)
   : acl_name_(acl_name), acl_type_(acl_type) {
}

inline acl_ttl_spec_t::acl_ttl_spec_t() : oper_(ACL_RANGE_ANY), ttl_(0) {
}

inline acl_ttl_spec_lt_t::acl_ttl_spec_lt_t(uint8_t ttl) {
   oper_ = ACL_RANGE_LT;
   ttl_ = ttl;
}

inline acl_ttl_spec_gt_t::acl_ttl_spec_gt_t(uint8_t ttl) {
   oper_ = ACL_RANGE_GT;
   ttl_ = ttl;
}

inline acl_ttl_spec_eq_t::acl_ttl_spec_eq_t(uint8_t ttl) {
   oper_ = ACL_RANGE_EQ;
   ttl_ = ttl;
}

inline acl_ttl_spec_neq_t::acl_ttl_spec_neq_t(uint8_t ttl) {
   oper_ = ACL_RANGE_NEQ;
   ttl_ = ttl;
}

inline acl_ttl_spec_any_t::acl_ttl_spec_any_t() {
   oper_ = ACL_RANGE_ANY;
   ttl_ = 0;
}

inline acl_port_spec_t::acl_port_spec_t() : oper_(ACL_RANGE_ANY), ports_() {
}

inline acl_port_spec_eq_t::acl_port_spec_eq_t(uint16_t port) {
   oper_ = ACL_RANGE_EQ;
   ports_.push_back(port);
}

inline acl_port_spec_eq_t::acl_port_spec_eq_t(std::list<uint16_t> ports) {
   for (std::list<uint16_t>::const_iterator pit = ports.begin(); pit != ports.end();
         ++pit) {
      ports_.push_back(*pit);
   }
}

inline acl_port_spec_neq_t::acl_port_spec_neq_t(uint16_t port) {
   oper_ = ACL_RANGE_NEQ;
   ports_.push_back(port);
}

inline acl_port_spec_lt_t::acl_port_spec_lt_t(uint16_t port) {
   oper_ = ACL_RANGE_LT;
   ports_.push_back(port);
}

inline acl_port_spec_gt_t::acl_port_spec_gt_t(uint16_t port) {
   oper_ = ACL_RANGE_GT;
   ports_.push_back(port);
}

inline acl_port_spec_any_t::acl_port_spec_any_t() {
   oper_ = ACL_RANGE_ANY;
}

inline acl_range_operator_t acl_port_spec_t::oper() const {
   return oper_;
}

inline acl_range_operator_t acl_ttl_spec_t::oper() const {
   return oper_;
}

inline uint8_t acl_ttl_spec_t::ttl() const {
   return ttl_;
}

// Constructors for ACL rule base types.

// Default values match internal TACC type default values
inline acl_rule_base_t::acl_rule_base_t() :
      action(ACL_PERMIT), log(false), tracked(false) {
}

// Constructors for concrete rule types passed to acl_add_rule() variants

inline acl_rule_ip_t::acl_rule_ip_t() : vlan(), vlan_mask(0xFFF),
                                        inner_vlan(), inner_vlan_mask(0xFFF),
                                        ip_protocol(),
                                        source_addr(), destination_addr(),
                                        source_port(), destination_port(),
                                        tcp_flags(),
                                        established(),
                                        icmp_type(ALL_ICMP), icmp_code(ALL_ICMP),
                                        priority_value(), priority_mask(),
                                        match_fragments(), match_ip_priority() {
}

inline acl_rule_eth_t::acl_rule_eth_t() : vlan(), vlan_mask(0xFFF),
                                          inner_vlan(), inner_vlan_mask(0xFFF),
                                          source_addr(), source_mask(),
                                          destination_addr(), destination_mask() {
}

inline acl_mgr * acl_handler::get_acl_mgr() const {
   return mgr_;
}

}  // end namespace eos

#endif // EOS_INLINE_ACL_H
