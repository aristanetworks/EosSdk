// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ACL_IMPL_H
#define EOS_INLINE_TYPES_ACL_IMPL_H

namespace eos {











// Default constructor.
acl_ttl_spec_impl_t::acl_ttl_spec_impl_t() :
      oper_(ACL_RANGE_ANY), ttl_(0) {
}

// Constructor for different ttl specs, note if oper is ACL_RANGE_ANY, the ttl
// should be set to 0.
acl_ttl_spec_impl_t::acl_ttl_spec_impl_t(acl_range_operator_t oper,
                                                uint8_t ttl) :
      oper_(oper), ttl_(ttl) {
}

acl_range_operator_t
acl_ttl_spec_impl_t::oper() const {
   return oper_;
}

void
acl_ttl_spec_impl_t::oper_is(acl_range_operator_t oper) {
   oper_ = oper;
}

uint8_t
acl_ttl_spec_impl_t::ttl() const {
   return ttl_;
}

void
acl_ttl_spec_impl_t::ttl_is(uint8_t ttl) {
   ttl_ = ttl;
}

bool
acl_ttl_spec_impl_t::operator==(acl_ttl_spec_impl_t const & other) const {
   return oper_ == other.oper_ &&
          ttl_ == other.ttl_;
}

bool
acl_ttl_spec_impl_t::operator!=(acl_ttl_spec_impl_t const & other) const {
   return !operator==(other);
}

bool
acl_ttl_spec_impl_t::operator<(acl_ttl_spec_impl_t const & other) const {
   if(oper_ != other.oper_) {
      return oper_ < other.oper_;
   } else if(ttl_ != other.ttl_) {
      return ttl_ < other.ttl_;
   }
   return false;
}

uint32_t
acl_ttl_spec_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
acl_ttl_spec_impl_t::mix_me(hash_mix & h) const {
   h.mix(oper_); // acl_range_operator_t
   h.mix(ttl_); // uint8_t
}

std::string
acl_ttl_spec_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "acl_ttl_spec_t(";
   ss << "oper=" << oper_;
   ss << ", ttl=" << ttl_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const acl_ttl_spec_impl_t& obj) {
   os << obj.to_string();
   return os;
}



acl_port_spec_impl_t::acl_port_spec_impl_t() :
      oper_(ACL_RANGE_ANY), ports_() {
}

acl_port_spec_impl_t::acl_port_spec_impl_t(
         acl_range_operator_t oper, std::list<uint16_t> const & ports) :
      oper_(oper) {
   for (std::list<uint16_t>::const_iterator pit = ports.cbegin();
        pit != ports.cend(); ++pit) {
        ports_.push_back(*pit);
   }

}

acl_range_operator_t
acl_port_spec_impl_t::oper() const {
   return oper_;
}

void
acl_port_spec_impl_t::oper_is(acl_range_operator_t oper) {
   oper_ = oper;
}

std::list<uint16_t> const &
acl_port_spec_impl_t::ports() const {
   return ports_;
}

void
acl_port_spec_impl_t::ports_is(std::list<uint16_t> const & ports) {
   ports_ = ports;
}

void
acl_port_spec_impl_t::port_set(uint16_t const & ports) {
   ports_.push_front(ports);
}

void
acl_port_spec_impl_t::port_del(uint16_t const & ports) {
   ports_.remove(ports);
}

bool
acl_port_spec_impl_t::operator==(acl_port_spec_impl_t const & other) const {
   return oper_ == other.oper_ &&
          ports_ == other.ports_;
}

bool
acl_port_spec_impl_t::operator!=(acl_port_spec_impl_t const & other) const {
   return !operator==(other);
}

bool
acl_port_spec_impl_t::operator<(acl_port_spec_impl_t const & other) const {
   if(oper_ != other.oper_) {
      return oper_ < other.oper_;
   } else if(ports_ != other.ports_) {
      return ports_ < other.ports_;
   }
   return false;
}

uint32_t
acl_port_spec_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
acl_port_spec_impl_t::mix_me(hash_mix & h) const {
   h.mix(oper_); // acl_range_operator_t
   for (auto it=ports_.cbegin(); it!=ports_.cend(); ++it) {
      h.mix(*it); // uint16_t
   }
}

std::string
acl_port_spec_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "acl_port_spec_t(";
   ss << "oper=" << oper_;
   ss << ", ports=" <<"'";
   bool first_ports = true;
   for (auto it=ports_.cbegin(); it!=ports_.cend(); ++it) {
      if (first_ports) {
         ss << (*it);
         first_ports = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const acl_port_spec_impl_t& obj) {
   os << obj.to_string();
   return os;
}



acl_port_spec_t
get_acl_port_spec_eq(uint16_t port) {
   std::list<uint16_t> l = { port };
   return acl_port_spec_t( ACL_RANGE_EQ, l );
}


acl_port_spec_t
get_acl_port_spec_eq(std::list<uint16_t> const & ports) {
   return acl_port_spec_t( ACL_RANGE_EQ, ports );
}


acl_port_spec_t
get_acl_port_spec_neq(uint16_t port) {
   std::list<uint16_t> l = { port };
   return acl_port_spec_t( ACL_RANGE_NEQ, l );
}


acl_port_spec_t
get_acl_port_spec_neq(std::list<uint16_t> const & ports) {
   return acl_port_spec_t( ACL_RANGE_NEQ, ports );
}


acl_port_spec_t
get_acl_port_spec_between(uint16_t low, uint16_t high) {
   std::list<uint16_t> l = { low, high };
   return acl_port_spec_t( ACL_RANGE_BETWEEN, l );
}


acl_port_spec_t
get_acl_port_spec_gt(uint16_t port) {
   std::list<uint16_t> l = { port };
   return acl_port_spec_t( ACL_RANGE_GT, l );
}


acl_port_spec_t
get_acl_port_spec_lt(uint16_t port) {
   std::list<uint16_t> l = { port };
   return acl_port_spec_t( ACL_RANGE_LT, l );
}


acl_port_spec_t
get_acl_port_spec_any() {
   return acl_port_spec_t();
}




acl_rule_base_impl_t::acl_rule_base_impl_t() :
      action_(ACL_PERMIT), log_(false), tracked_(false) {
}

acl_action_t
acl_rule_base_impl_t::action() const {
   return action_;
}

void
acl_rule_base_impl_t::action_is(acl_action_t action) {
   action_ = action;
}

bool
acl_rule_base_impl_t::log() const {
   return log_;
}

void
acl_rule_base_impl_t::log_is(bool log) {
   log_ = log;
}

bool
acl_rule_base_impl_t::tracked() const {
   return tracked_;
}

void
acl_rule_base_impl_t::tracked_is(bool tracked) {
   tracked_ = tracked;
}

uint32_t
acl_rule_base_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
acl_rule_base_impl_t::mix_me(hash_mix & h) const {
   h.mix(action_); // acl_action_t
   h.mix(log_); // bool
   h.mix(tracked_); // bool
}

std::string
acl_rule_base_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "acl_rule_base_t(";
   ss << "action=" << action_;
   ss << ", log=" << log_;
   ss << ", tracked=" << tracked_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const acl_rule_base_impl_t& obj) {
   os << obj.to_string();
   return os;
}



// Constructor for concrete rule ip type passed to acl_add_rule() variants.
acl_rule_ip_impl_t::acl_rule_ip_impl_t() :
      vlan_(), vlan_mask_(0xFFF), inner_vlan_(), inner_vlan_mask_(0xFFF),
      ip_protocol_(), ttl_(), source_addr_(), destination_addr_(), source_port_(),
      destination_port_(), nexthop_group_(), tcp_flags_(), established_(),
      icmp_type_(ALL_ICMP), icmp_code_(ALL_ICMP), priority_value_(),
      priority_mask_(), match_fragments_(), match_ip_priority_() {
}

vlan_id_t
acl_rule_ip_impl_t::vlan() const {
   return vlan_;
}

void
acl_rule_ip_impl_t::vlan_is(vlan_id_t vlan) {
   vlan_ = vlan;
}

vlan_id_t
acl_rule_ip_impl_t::vlan_mask() const {
   return vlan_mask_;
}

void
acl_rule_ip_impl_t::vlan_mask_is(vlan_id_t vlan_mask) {
   vlan_mask_ = vlan_mask;
}

vlan_id_t
acl_rule_ip_impl_t::inner_vlan() const {
   return inner_vlan_;
}

void
acl_rule_ip_impl_t::inner_vlan_is(vlan_id_t inner_vlan) {
   inner_vlan_ = inner_vlan;
}

vlan_id_t
acl_rule_ip_impl_t::inner_vlan_mask() const {
   return inner_vlan_mask_;
}

void
acl_rule_ip_impl_t::inner_vlan_mask_is(vlan_id_t inner_vlan_mask) {
   inner_vlan_mask_ = inner_vlan_mask;
}

uint8_t
acl_rule_ip_impl_t::ip_protocol() const {
   return ip_protocol_;
}

void
acl_rule_ip_impl_t::ip_protocol_is(uint8_t ip_protocol) {
   ip_protocol_ = ip_protocol;
}

acl_ttl_spec_t
acl_rule_ip_impl_t::ttl() const {
   return ttl_;
}

void
acl_rule_ip_impl_t::ttl_is(acl_ttl_spec_t ttl) {
   ttl_ = ttl;
}

ip_addr_mask_t
acl_rule_ip_impl_t::source_addr() const {
   return source_addr_;
}

void
acl_rule_ip_impl_t::source_addr_is(ip_addr_mask_t const & source_addr) {
   source_addr_ = source_addr;
}

ip_addr_mask_t
acl_rule_ip_impl_t::destination_addr() const {
   return destination_addr_;
}

void
acl_rule_ip_impl_t::destination_addr_is(ip_addr_mask_t const & destination_addr) {
   destination_addr_ = destination_addr;
}

acl_port_spec_t
acl_rule_ip_impl_t::source_port() const {
   return source_port_;
}

void
acl_rule_ip_impl_t::source_port_is(acl_port_spec_t source_port) {
   source_port_ = source_port;
}

acl_port_spec_t
acl_rule_ip_impl_t::destination_port() const {
   return destination_port_;
}

void
acl_rule_ip_impl_t::destination_port_is(acl_port_spec_t destination_port) {
   destination_port_ = destination_port;
}

std::string
acl_rule_ip_impl_t::nexthop_group() const {
   return nexthop_group_;
}

void
acl_rule_ip_impl_t::nexthop_group_is(std::string nexthop_group) {
   nexthop_group_ = nexthop_group;
}

uint16_t
acl_rule_ip_impl_t::tcp_flags() const {
   return tcp_flags_;
}

void
acl_rule_ip_impl_t::tcp_flags_is(uint16_t tcp_flags) {
   tcp_flags_ = tcp_flags;
}

bool
acl_rule_ip_impl_t::established() const {
   return established_;
}

void
acl_rule_ip_impl_t::established_is(bool established) {
   established_ = established;
}

uint16_t
acl_rule_ip_impl_t::icmp_type() const {
   return icmp_type_;
}

void
acl_rule_ip_impl_t::icmp_type_is(uint16_t icmp_type) {
   icmp_type_ = icmp_type;
}

uint16_t
acl_rule_ip_impl_t::icmp_code() const {
   return icmp_code_;
}

void
acl_rule_ip_impl_t::icmp_code_is(uint16_t icmp_code) {
   icmp_code_ = icmp_code;
}

uint8_t
acl_rule_ip_impl_t::priority_value() const {
   return priority_value_;
}

void
acl_rule_ip_impl_t::priority_value_is(uint8_t priority_value) {
   priority_value_ = priority_value;
}

uint8_t
acl_rule_ip_impl_t::priority_mask() const {
   return priority_mask_;
}

void
acl_rule_ip_impl_t::priority_mask_is(uint8_t priority_mask) {
   priority_mask_ = priority_mask;
}

bool
acl_rule_ip_impl_t::match_fragments() const {
   return match_fragments_;
}

void
acl_rule_ip_impl_t::match_fragments_is(bool match_fragments) {
   match_fragments_ = match_fragments;
}

bool
acl_rule_ip_impl_t::match_ip_priority() const {
   return match_ip_priority_;
}

void
acl_rule_ip_impl_t::match_ip_priority_is(bool match_ip_priority) {
   match_ip_priority_ = match_ip_priority;
}

bool
acl_rule_ip_impl_t::operator==(acl_rule_ip_impl_t const & other) const {
   return vlan_ == other.vlan_ &&
          vlan_mask_ == other.vlan_mask_ &&
          inner_vlan_ == other.inner_vlan_ &&
          inner_vlan_mask_ == other.inner_vlan_mask_ &&
          ip_protocol_ == other.ip_protocol_ &&
          ttl_ == other.ttl_ &&
          source_addr_ == other.source_addr_ &&
          destination_addr_ == other.destination_addr_ &&
          source_port_ == other.source_port_ &&
          destination_port_ == other.destination_port_ &&
          nexthop_group_ == other.nexthop_group_ &&
          tcp_flags_ == other.tcp_flags_ &&
          established_ == other.established_ &&
          icmp_type_ == other.icmp_type_ &&
          icmp_code_ == other.icmp_code_ &&
          priority_value_ == other.priority_value_ &&
          priority_mask_ == other.priority_mask_ &&
          match_fragments_ == other.match_fragments_ &&
          match_ip_priority_ == other.match_ip_priority_;
}

bool
acl_rule_ip_impl_t::operator!=(acl_rule_ip_impl_t const & other) const {
   return !operator==(other);
}

bool
acl_rule_ip_impl_t::operator<(acl_rule_ip_impl_t const & other) const {
   if(vlan_ != other.vlan_) {
      return vlan_ < other.vlan_;
   } else if(vlan_mask_ != other.vlan_mask_) {
      return vlan_mask_ < other.vlan_mask_;
   } else if(inner_vlan_ != other.inner_vlan_) {
      return inner_vlan_ < other.inner_vlan_;
   } else if(inner_vlan_mask_ != other.inner_vlan_mask_) {
      return inner_vlan_mask_ < other.inner_vlan_mask_;
   } else if(ip_protocol_ != other.ip_protocol_) {
      return ip_protocol_ < other.ip_protocol_;
   } else if(ttl_ != other.ttl_) {
      return ttl_ < other.ttl_;
   } else if(source_addr_ != other.source_addr_) {
      return source_addr_ < other.source_addr_;
   } else if(destination_addr_ != other.destination_addr_) {
      return destination_addr_ < other.destination_addr_;
   } else if(source_port_ != other.source_port_) {
      return source_port_ < other.source_port_;
   } else if(destination_port_ != other.destination_port_) {
      return destination_port_ < other.destination_port_;
   } else if(nexthop_group_ != other.nexthop_group_) {
      return nexthop_group_ < other.nexthop_group_;
   } else if(tcp_flags_ != other.tcp_flags_) {
      return tcp_flags_ < other.tcp_flags_;
   } else if(established_ != other.established_) {
      return established_ < other.established_;
   } else if(icmp_type_ != other.icmp_type_) {
      return icmp_type_ < other.icmp_type_;
   } else if(icmp_code_ != other.icmp_code_) {
      return icmp_code_ < other.icmp_code_;
   } else if(priority_value_ != other.priority_value_) {
      return priority_value_ < other.priority_value_;
   } else if(priority_mask_ != other.priority_mask_) {
      return priority_mask_ < other.priority_mask_;
   } else if(match_fragments_ != other.match_fragments_) {
      return match_fragments_ < other.match_fragments_;
   } else if(match_ip_priority_ != other.match_ip_priority_) {
      return match_ip_priority_ < other.match_ip_priority_;
   }
   return false;
}

uint32_t
acl_rule_ip_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
acl_rule_ip_impl_t::mix_me(hash_mix & h) const {
   h.mix(vlan_); // vlan_id_t
   h.mix(vlan_mask_); // vlan_id_t
   h.mix(inner_vlan_); // vlan_id_t
   h.mix(inner_vlan_mask_); // vlan_id_t
   h.mix(ip_protocol_); // uint8_t
   h.mix(ttl_); // acl_ttl_spec_t
   h.mix(source_addr_); // ip_addr_mask_t
   h.mix(destination_addr_); // ip_addr_mask_t
   h.mix(source_port_); // acl_port_spec_t
   h.mix(destination_port_); // acl_port_spec_t
   h.mix(nexthop_group_); // std::string
   h.mix(tcp_flags_); // uint16_t
   h.mix(established_); // bool
   h.mix(icmp_type_); // uint16_t
   h.mix(icmp_code_); // uint16_t
   h.mix(priority_value_); // uint8_t
   h.mix(priority_mask_); // uint8_t
   h.mix(match_fragments_); // bool
   h.mix(match_ip_priority_); // bool
}

std::string
acl_rule_ip_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "acl_rule_ip_t(";
   ss << "vlan=" << vlan_;
   ss << ", vlan_mask=" << vlan_mask_;
   ss << ", inner_vlan=" << inner_vlan_;
   ss << ", inner_vlan_mask=" << inner_vlan_mask_;
   ss << ", ip_protocol=" << ip_protocol_;
   ss << ", ttl=" << ttl_;
   ss << ", source_addr=" << source_addr_;
   ss << ", destination_addr=" << destination_addr_;
   ss << ", source_port=" << source_port_;
   ss << ", destination_port=" << destination_port_;
   ss << ", nexthop_group='" << nexthop_group_ << "'";
   ss << ", tcp_flags=" << tcp_flags_;
   ss << ", established=" << established_;
   ss << ", icmp_type=" << icmp_type_;
   ss << ", icmp_code=" << icmp_code_;
   ss << ", priority_value=" << priority_value_;
   ss << ", priority_mask=" << priority_mask_;
   ss << ", match_fragments=" << match_fragments_;
   ss << ", match_ip_priority=" << match_ip_priority_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const acl_rule_ip_impl_t& obj) {
   os << obj.to_string();
   return os;
}



acl_rule_eth_impl_t::acl_rule_eth_impl_t() :
      vlan_(), vlan_mask_(0xFFF), inner_vlan_(), inner_vlan_mask_(0xFFF),
      source_addr_(), destination_addr_(), source_mask_(), destination_mask_(),
      eth_protocol_(0xFFFFFFFF) {
}

vlan_id_t
acl_rule_eth_impl_t::vlan() const {
   return vlan_;
}

void
acl_rule_eth_impl_t::vlan_is(vlan_id_t vlan) {
   vlan_ = vlan;
}

vlan_id_t
acl_rule_eth_impl_t::vlan_mask() const {
   return vlan_mask_;
}

void
acl_rule_eth_impl_t::vlan_mask_is(vlan_id_t vlan_mask) {
   vlan_mask_ = vlan_mask;
}

vlan_id_t
acl_rule_eth_impl_t::inner_vlan() const {
   return inner_vlan_;
}

void
acl_rule_eth_impl_t::inner_vlan_is(vlan_id_t inner_vlan) {
   inner_vlan_ = inner_vlan;
}

vlan_id_t
acl_rule_eth_impl_t::inner_vlan_mask() const {
   return inner_vlan_mask_;
}

void
acl_rule_eth_impl_t::inner_vlan_mask_is(vlan_id_t inner_vlan_mask) {
   inner_vlan_mask_ = inner_vlan_mask;
}

eth_addr_t
acl_rule_eth_impl_t::source_addr() const {
   return source_addr_;
}

void
acl_rule_eth_impl_t::source_addr_is(eth_addr_t source_addr) {
   source_addr_ = source_addr;
}

eth_addr_t
acl_rule_eth_impl_t::destination_addr() const {
   return destination_addr_;
}

void
acl_rule_eth_impl_t::destination_addr_is(eth_addr_t destination_addr) {
   destination_addr_ = destination_addr;
}

eth_addr_t
acl_rule_eth_impl_t::source_mask() const {
   return source_mask_;
}

void
acl_rule_eth_impl_t::source_mask_is(eth_addr_t source_mask) {
   source_mask_ = source_mask;
}

eth_addr_t
acl_rule_eth_impl_t::destination_mask() const {
   return destination_mask_;
}

void
acl_rule_eth_impl_t::destination_mask_is(eth_addr_t destination_mask) {
   destination_mask_ = destination_mask;
}

uint32_t
acl_rule_eth_impl_t::eth_protocol() const {
   return eth_protocol_;
}

void
acl_rule_eth_impl_t::eth_protocol_is(uint32_t eth_protocol) {
   eth_protocol_ = eth_protocol;
}

bool
acl_rule_eth_impl_t::operator==(acl_rule_eth_impl_t const & other) const {
   return vlan_ == other.vlan_ &&
          vlan_mask_ == other.vlan_mask_ &&
          inner_vlan_ == other.inner_vlan_ &&
          inner_vlan_mask_ == other.inner_vlan_mask_ &&
          source_addr_ == other.source_addr_ &&
          destination_addr_ == other.destination_addr_ &&
          source_mask_ == other.source_mask_ &&
          destination_mask_ == other.destination_mask_ &&
          eth_protocol_ == other.eth_protocol_;
}

bool
acl_rule_eth_impl_t::operator!=(acl_rule_eth_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
acl_rule_eth_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
acl_rule_eth_impl_t::mix_me(hash_mix & h) const {
   h.mix(vlan_); // vlan_id_t
   h.mix(vlan_mask_); // vlan_id_t
   h.mix(inner_vlan_); // vlan_id_t
   h.mix(inner_vlan_mask_); // vlan_id_t
   h.mix(source_addr_); // eth_addr_t
   h.mix(destination_addr_); // eth_addr_t
   h.mix(source_mask_); // eth_addr_t
   h.mix(destination_mask_); // eth_addr_t
   h.mix(eth_protocol_); // uint32_t
}

std::string
acl_rule_eth_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "acl_rule_eth_t(";
   ss << "vlan=" << vlan_;
   ss << ", vlan_mask=" << vlan_mask_;
   ss << ", inner_vlan=" << inner_vlan_;
   ss << ", inner_vlan_mask=" << inner_vlan_mask_;
   ss << ", source_addr=" << source_addr_;
   ss << ", destination_addr=" << destination_addr_;
   ss << ", source_mask=" << source_mask_;
   ss << ", destination_mask=" << destination_mask_;
   ss << ", eth_protocol=" << eth_protocol_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const acl_rule_eth_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/acl.h>

#endif // EOS_INLINE_TYPES_ACL_IMPL_H
