// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_ACL_H
#define EOS_INLINE_ACL_H

namespace eos {

enum {
   ALL_ICMP = 65535,
};

inline void 
acl_ttl_spec_t::oper(acl_range_operator_t a) {_oper = a;}

inline void 
acl_ttl_spec_t::ttl(uint8_t u) {_ttl = u;}

inline void 
acl_port_spec_t::oper(acl_range_operator_t a) {_oper = a;}

inline std::list<uint16_t> 
acl_port_spec_t::ports() const{return _ports;}

inline void
acl_port_spec_t::ports(std::list<uint16_t> l) {_ports = l;}

inline bool
acl_key_t::operator() (acl_key_t const & lhs, acl_key_t const & rhs) const {
   return lhs.acl_name_ < rhs.acl_name_;
}

inline void 
acl_rule_base_t::log(bool l) {_log = l;}

inline bool
acl_rule_base_t::log() const {return _log;}

inline void
acl_rule_base_t::tracked(bool t) {_tracked = t;}

inline bool 
acl_rule_base_t::tracked() const {return _tracked;}

inline void 
acl_rule_base_t::action(acl_action_t a) {_action = a;}

inline acl_action_t
acl_rule_base_t::action() const {return _action;}

inline void 
acl_rule_ip_t::vlan(vlan_id_t v) {_vlan = v;}
inline vlan_id_t 
acl_rule_ip_t::vlan() const {return _vlan;}
inline void 
acl_rule_ip_t::vlan_mask(vlan_id_t v) {_vlan_mask = v;}
inline vlan_id_t 
acl_rule_ip_t::vlan_mask() const {return _vlan_mask;}
inline void 
acl_rule_ip_t::inner_vlan(vlan_id_t v) {_inner_vlan = v;}
inline vlan_id_t 
acl_rule_ip_t::inner_vlan() const {return _inner_vlan;}
inline void 
acl_rule_ip_t::inner_vlan_mask(vlan_id_t v) {_inner_vlan_mask = v;}
inline vlan_id_t 
acl_rule_ip_t::inner_vlan_mask() const {return _inner_vlan_mask;}

inline void 
acl_rule_ip_t::ip_protocol(uint8_t ip) {_ip_protocol = ip;}
inline uint8_t
acl_rule_ip_t::ip_protocol() const {return _ip_protocol;}

inline void 
acl_rule_ip_t::ttl(acl_ttl_spec_t t) {_ttl = t;}
inline acl_ttl_spec_t 
acl_rule_ip_t::ttl() const {return _ttl;}

inline void 
acl_rule_ip_t::source_addr(ip_addr_mask_t ip) {_source_addr = ip;}
inline void 
acl_rule_ip_t::destination_addr(ip_addr_mask_t ip) {_destination_addr = ip;}
inline ip_addr_mask_t
acl_rule_ip_t::source_addr() const {return _source_addr;}
inline ip_addr_mask_t
acl_rule_ip_t::destination_addr() const {return _destination_addr;}
inline acl_port_spec_t 
acl_rule_ip_t::source_port() const {return _source_port;}
inline acl_port_spec_t
acl_rule_ip_t::destination_port() const {return _destination_port;}
inline void 
acl_rule_ip_t::source_port(acl_port_spec_t a) {_source_port = a;}
inline void 
acl_rule_ip_t::destination_port(acl_port_spec_t a) {_destination_port = a;}

inline void 
acl_rule_ip_t::tcp_flags(uint16_t n) {_tcp_flags = n;}
inline uint16_t 
acl_rule_ip_t::tcp_flags() const {return _tcp_flags;}

inline void 
acl_rule_ip_t::established(bool b) {_established = b;}
inline bool 
acl_rule_ip_t::established() const {return _established;}

inline void 
acl_rule_ip_t::icmp_type(uint16_t n) {_icmp_type = n;}
inline void
acl_rule_ip_t::icmp_code(uint16_t n) {_icmp_code = n;}
inline uint16_t
acl_rule_ip_t::icmp_type() const {return _icmp_type;}
inline uint16_t 
acl_rule_ip_t::icmp_code() const {return _icmp_code;}

inline void 
acl_rule_ip_t::priority_value(uint8_t n) {_priority_value = n;}
inline void 
acl_rule_ip_t::priority_mask(uint8_t n) {_priority_mask = n;}
inline void 
acl_rule_ip_t::match_fragments(bool b) {_match_fragments = b;}
inline void 
acl_rule_ip_t::match_ip_priority(bool b) {_match_ip_priority = b;}
inline uint8_t
acl_rule_ip_t::priority_value() const {return _priority_value;}
inline uint8_t 
acl_rule_ip_t::priority_mask() const {return _priority_mask;}
inline bool 
acl_rule_ip_t::match_fragments() const {return _match_fragments;}
inline bool 
acl_rule_ip_t::match_ip_priority() const {return _match_ip_priority;}

inline void 
acl_rule_eth_t::vlan(vlan_id_t v) {_vlan = v;}
inline void 
acl_rule_eth_t::vlan_mask(vlan_id_t v) {_vlan_mask = v;}
inline void 
acl_rule_eth_t::inner_vlan(vlan_id_t v) {_inner_vlan = v;}
inline void 
acl_rule_eth_t::inner_vlan_mask(vlan_id_t v) {_inner_vlan_mask = v;}
inline vlan_id_t 
acl_rule_eth_t::vlan() const{return _vlan;}
inline vlan_id_t 
acl_rule_eth_t::vlan_mask() const{return _vlan_mask;}
inline vlan_id_t 
acl_rule_eth_t::inner_vlan() const{return _inner_vlan;}
inline vlan_id_t 
acl_rule_eth_t::inner_vlan_mask() const{return _inner_vlan_mask;}

inline void 
acl_rule_eth_t::source_addr(eth_addr_t e) {_source_addr = e;}
inline void 
acl_rule_eth_t::source_mask(eth_addr_t e) {_source_mask = e;}
inline void 
acl_rule_eth_t::destination_addr(eth_addr_t e) {_destination_addr = e;}
inline void 
acl_rule_eth_t::destination_mask(eth_addr_t e) {_destination_mask = e;}
inline eth_addr_t 
acl_rule_eth_t::source_addr() const{return _source_addr;}
inline eth_addr_t 
acl_rule_eth_t::source_mask() const{return _source_mask;}
inline eth_addr_t 
acl_rule_eth_t::destination_addr() const{return _destination_addr;}
inline eth_addr_t 
acl_rule_eth_t::destination_mask() const{return _destination_mask;}

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

inline acl_ttl_spec_t::acl_ttl_spec_t() : _oper(ACL_RANGE_ANY), _ttl(0) {
}

inline acl_ttl_spec_lt_t::acl_ttl_spec_lt_t(uint8_t ttl) {
   _oper = ACL_RANGE_LT;
   _ttl = ttl;
}

inline acl_ttl_spec_gt_t::acl_ttl_spec_gt_t(uint8_t ttl) {
   _oper = ACL_RANGE_GT;
   _ttl = ttl;
}

inline acl_ttl_spec_eq_t::acl_ttl_spec_eq_t(uint8_t ttl) {
   _oper = ACL_RANGE_EQ;
   _ttl = ttl;
}

inline acl_ttl_spec_neq_t::acl_ttl_spec_neq_t(uint8_t ttl) {
   _oper = ACL_RANGE_NEQ;
   _ttl = ttl;
}

inline acl_ttl_spec_any_t::acl_ttl_spec_any_t() {
   _oper = ACL_RANGE_ANY;
   _ttl = 0;
}

inline acl_port_spec_t::acl_port_spec_t() : _oper(ACL_RANGE_ANY), _ports() {
}

inline acl_port_spec_eq_t::acl_port_spec_eq_t(uint16_t port) {
   _oper = ACL_RANGE_EQ;
   _ports.push_back(port);
}

inline acl_port_spec_eq_t::acl_port_spec_eq_t(std::list<uint16_t> ports) {
   for (std::list<uint16_t>::const_iterator pit = ports.begin(); pit != ports.end();
         ++pit) {
      _ports.push_back(*pit);
   }
}

inline acl_port_spec_neq_t::acl_port_spec_neq_t(uint16_t port) {
   _oper = ACL_RANGE_NEQ;
   _ports.push_back(port);
}

inline acl_port_spec_lt_t::acl_port_spec_lt_t(uint16_t port) {
   _oper = ACL_RANGE_LT;
   _ports.push_back(port);
}

inline acl_port_spec_gt_t::acl_port_spec_gt_t(uint16_t port) {
   _oper = ACL_RANGE_GT;
   _ports.push_back(port);
}

inline acl_port_spec_any_t::acl_port_spec_any_t() {
   _oper = ACL_RANGE_ANY;
}

inline acl_range_operator_t acl_port_spec_t::oper() const {
   return _oper;
}

inline acl_range_operator_t acl_ttl_spec_t::oper() const {
   return _oper;
}

inline uint8_t acl_ttl_spec_t::ttl() const {
   return _ttl;
}

// Constructors for ACL rule base types.

// Default values match internal TACC type default values
inline acl_rule_base_t::acl_rule_base_t() :
      _action(ACL_PERMIT), _log(false), _tracked(false) {
}

// Constructors for concrete rule types passed to acl_add_rule() variants

inline acl_rule_ip_t::acl_rule_ip_t() : _vlan(), _vlan_mask(0xFFF),
                                        _inner_vlan(), _inner_vlan_mask(0xFFF),
                                        _ip_protocol(),
                                        _source_addr(), _destination_addr(),
                                        _source_port(), _destination_port(),
                                        _tcp_flags(),
                                        _established(),
                                        _icmp_type(ALL_ICMP), _icmp_code(ALL_ICMP),
                                        _priority_value(), _priority_mask(),
                                        _match_fragments(), _match_ip_priority() {
}

inline acl_rule_eth_t::acl_rule_eth_t() : _vlan(), _vlan_mask(0xFFF),
                                          _inner_vlan(), _inner_vlan_mask(0xFFF),
                                          _source_addr(), _source_mask(),
                                          _destination_addr(), _destination_mask() {
}

inline acl_mgr * acl_handler::get_acl_mgr() const {
   return mgr_;
}

}  // end namespace eos

#endif // EOS_INLINE_ACL_H
