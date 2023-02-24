// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ACL_H
#define EOS_INLINE_TYPES_ACL_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const acl_type_t & enum_val) {
   if (enum_val==ACL_TYPE_NULL) {
      os << "ACL_TYPE_NULL";
   } else if (enum_val==ACL_TYPE_IPV4) {
      os << "ACL_TYPE_IPV4";
   } else if (enum_val==ACL_TYPE_IPV6) {
      os << "ACL_TYPE_IPV6";
   } else if (enum_val==ACL_TYPE_ETH) {
      os << "ACL_TYPE_ETH";
   } else if (enum_val==ACL_TYPE_MPLS) {
      os << "ACL_TYPE_MPLS";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const acl_direction_t & enum_val) {
   if (enum_val==ACL_DIRECTION_NULL) {
      os << "ACL_DIRECTION_NULL";
   } else if (enum_val==ACL_IN) {
      os << "ACL_IN";
   } else if (enum_val==ACL_OUT) {
      os << "ACL_OUT";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const acl_range_operator_t & enum_val) {
   if (enum_val==ACL_RANGE_NULL) {
      os << "ACL_RANGE_NULL";
   } else if (enum_val==ACL_RANGE_ANY) {
      os << "ACL_RANGE_ANY";
   } else if (enum_val==ACL_RANGE_EQ) {
      os << "ACL_RANGE_EQ";
   } else if (enum_val==ACL_RANGE_GT) {
      os << "ACL_RANGE_GT";
   } else if (enum_val==ACL_RANGE_LT) {
      os << "ACL_RANGE_LT";
   } else if (enum_val==ACL_RANGE_NEQ) {
      os << "ACL_RANGE_NEQ";
   } else if (enum_val==ACL_RANGE_BETWEEN) {
      os << "ACL_RANGE_BETWEEN";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const acl_action_t & enum_val) {
   if (enum_val==ACL_ACTION_NULL) {
      os << "ACL_ACTION_NULL";
   } else if (enum_val==ACL_PERMIT) {
      os << "ACL_PERMIT";
   } else if (enum_val==ACL_DENY) {
      os << "ACL_DENY";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const acl_tcp_flag_t & enum_val) {
   if (enum_val==ACL_TCP_NULL) {
      os << "ACL_TCP_NULL";
   } else if (enum_val==ACL_TCP_FIN) {
      os << "ACL_TCP_FIN";
   } else if (enum_val==ACL_TCP_SYN) {
      os << "ACL_TCP_SYN";
   } else if (enum_val==ACL_TCP_RST) {
      os << "ACL_TCP_RST";
   } else if (enum_val==ACL_TCP_PSH) {
      os << "ACL_TCP_PSH";
   } else if (enum_val==ACL_TCP_ACK) {
      os << "ACL_TCP_ACK";
   } else if (enum_val==ACL_TCP_URG) {
      os << "ACL_TCP_URG";
   } else if (enum_val==ACL_TCP_ECE) {
      os << "ACL_TCP_ECE";
   } else if (enum_val==ACL_TCP_CWR) {
      os << "ACL_TCP_CWR";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const acl_ip_type_t & enum_val) {
   if (enum_val==ACL_IP_TYPE_ANY) {
      os << "ACL_IP_TYPE_ANY";
   } else if (enum_val==ACL_IP_TYPE_IP) {
      os << "ACL_IP_TYPE_IP";
   } else if (enum_val==ACL_IP_TYPE_MPLS) {
      os << "ACL_IP_TYPE_MPLS";
   } else {
      os << "Unknown value";
   }
   return os;
}


// Default constructor.
acl_ttl_spec_t::acl_ttl_spec_t() {
   pimpl = std::shared_ptr<acl_ttl_spec_impl_t>(
      new acl_ttl_spec_impl_t()
   );
}
// Constructor for different ttl specs, note if oper is ACL_RANGE_ANY, the ttl
// should be set to 0.
acl_ttl_spec_t::acl_ttl_spec_t(acl_range_operator_t oper, uint8_t ttl) {
   pimpl = std::shared_ptr<acl_ttl_spec_impl_t>(
      new acl_ttl_spec_impl_t(
         oper,
         ttl
      )
   );
}
acl_ttl_spec_t::acl_ttl_spec_t(
   const acl_ttl_spec_t& other)
{
   pimpl = std::make_unique<acl_ttl_spec_impl_t>(
      acl_ttl_spec_impl_t(*other.pimpl));
}
acl_ttl_spec_t&
acl_ttl_spec_t::operator=(
   acl_ttl_spec_t const & other)
{
   pimpl = std::shared_ptr<acl_ttl_spec_impl_t>(
      new acl_ttl_spec_impl_t(*other.pimpl));
   return *this;
}

acl_range_operator_t
acl_ttl_spec_t::oper() const {
   return pimpl->oper();
}
void
acl_ttl_spec_t::oper_is(acl_range_operator_t oper) {
   pimpl->oper_is(oper);
}
uint8_t
acl_ttl_spec_t::ttl() const {
   return pimpl->ttl();
}
void
acl_ttl_spec_t::ttl_is(uint8_t ttl) {
   pimpl->ttl_is(ttl);
}
bool
acl_ttl_spec_t::operator==(acl_ttl_spec_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
acl_ttl_spec_t::operator!=(acl_ttl_spec_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
acl_ttl_spec_t::operator<(acl_ttl_spec_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
acl_ttl_spec_t::hash() const {
   return pimpl->hash();
}
void
acl_ttl_spec_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
acl_ttl_spec_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const acl_ttl_spec_t& obj) {
   return operator<<(os, *obj.pimpl);
}


acl_port_spec_t::acl_port_spec_t() {
   pimpl = std::shared_ptr<acl_port_spec_impl_t>(
      new acl_port_spec_impl_t()
   );
}
acl_port_spec_t::acl_port_spec_t(acl_range_operator_t oper,
                                        std::list<uint16_t> const & ports) {
   pimpl = std::shared_ptr<acl_port_spec_impl_t>(
      new acl_port_spec_impl_t(
         oper,
         ports
      )
   );
}
acl_port_spec_t::acl_port_spec_t(
   const acl_port_spec_t& other)
{
   pimpl = std::make_unique<acl_port_spec_impl_t>(
      acl_port_spec_impl_t(*other.pimpl));
}
acl_port_spec_t&
acl_port_spec_t::operator=(
   acl_port_spec_t const & other)
{
   pimpl = std::shared_ptr<acl_port_spec_impl_t>(
      new acl_port_spec_impl_t(*other.pimpl));
   return *this;
}

acl_range_operator_t
acl_port_spec_t::oper() const {
   return pimpl->oper();
}
void
acl_port_spec_t::oper_is(acl_range_operator_t oper) {
   pimpl->oper_is(oper);
}
std::list<uint16_t> const &
acl_port_spec_t::ports() const {
   return pimpl->ports();
}
void
acl_port_spec_t::ports_is(std::list<uint16_t> const & ports) {
   pimpl->ports_is(ports);
}
void
acl_port_spec_t::port_set(uint16_t const & ports) {
   pimpl->port_set(ports);
}
void
acl_port_spec_t::port_del(uint16_t const & ports) {
   pimpl->port_del(ports);
}
bool
acl_port_spec_t::operator==(acl_port_spec_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
acl_port_spec_t::operator!=(acl_port_spec_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
acl_port_spec_t::operator<(acl_port_spec_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
acl_port_spec_t::hash() const {
   return pimpl->hash();
}
void
acl_port_spec_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
acl_port_spec_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const acl_port_spec_t& obj) {
   return operator<<(os, *obj.pimpl);
}


















acl_key_t::acl_key_t() :
      acl_name_(), acl_type_(ACL_TYPE_NULL) {
}

acl_key_t::acl_key_t(std::string const & acl_name, acl_type_t acl_type) :
      acl_name_(acl_name), acl_type_(acl_type) {
}

std::string
acl_key_t::acl_name() const {
   return acl_name_;
}

acl_type_t
acl_key_t::acl_type() const {
   return acl_type_;
}

bool
acl_key_t::operator()(acl_key_t const & lhs, acl_key_t const & rhs) const {
   return lhs.acl_name_ < rhs.acl_name_;
}

bool
acl_key_t::operator==(acl_key_t const & other) const {
   return acl_name_ == other.acl_name_ &&
          acl_type_ == other.acl_type_;
}

bool
acl_key_t::operator!=(acl_key_t const & other) const {
   return !operator==(other);
}

uint32_t
acl_key_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
acl_key_t::mix_me(hash_mix & h) const {
   h.mix(acl_name_); // std::string
   h.mix(acl_type_); // acl_type_t
}

std::string
acl_key_t::to_string() const {
   std::ostringstream ss;
   ss << "acl_key_t(";
   ss << "acl_name='" << acl_name_ << "'";
   ss << ", acl_type=" << acl_type_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const acl_key_t& obj) {
   os << obj.to_string();
   return os;
}



acl_rule_base_t::acl_rule_base_t() {
   pimpl = std::shared_ptr<acl_rule_base_impl_t>(
      new acl_rule_base_impl_t()
   );
}
acl_rule_base_t::acl_rule_base_t(
   const acl_rule_base_t& other)
{
   pimpl = std::make_unique<acl_rule_base_impl_t>(
      acl_rule_base_impl_t(*other.pimpl));
}
acl_rule_base_t&
acl_rule_base_t::operator=(
   acl_rule_base_t const & other)
{
   pimpl = std::shared_ptr<acl_rule_base_impl_t>(
      new acl_rule_base_impl_t(*other.pimpl));
   return *this;
}

acl_action_t
acl_rule_base_t::action() const {
   return pimpl->action();
}
void
acl_rule_base_t::action_is(acl_action_t action) {
   pimpl->action_is(action);
}
bool
acl_rule_base_t::log() const {
   return pimpl->log();
}
void
acl_rule_base_t::log_is(bool log) {
   pimpl->log_is(log);
}
bool
acl_rule_base_t::tracked() const {
   return pimpl->tracked();
}
void
acl_rule_base_t::tracked_is(bool tracked) {
   pimpl->tracked_is(tracked);
}
uint32_t
acl_rule_base_t::hash() const {
   return pimpl->hash();
}
void
acl_rule_base_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
acl_rule_base_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const acl_rule_base_t& obj) {
   return operator<<(os, *obj.pimpl);
}


// Constructor for concrete rule ip type passed to acl_add_rule() variants.
acl_rule_ip_t::acl_rule_ip_t(): acl_rule_base_t() {
   pimpl = std::shared_ptr<acl_rule_ip_impl_t>(
      new acl_rule_ip_impl_t()
   );
}
acl_rule_ip_t::acl_rule_ip_t(
   const acl_rule_ip_t& other): acl_rule_base_t(other)
{
   pimpl = std::make_unique<acl_rule_ip_impl_t>(
      acl_rule_ip_impl_t(*other.pimpl));
}
acl_rule_ip_t&
acl_rule_ip_t::operator=(
   acl_rule_ip_t const & other)
{
   acl_rule_base_t::operator=(other);
   pimpl = std::shared_ptr<acl_rule_ip_impl_t>(
      new acl_rule_ip_impl_t(*other.pimpl));
   return *this;
}

vlan_id_t
acl_rule_ip_t::vlan() const {
   return pimpl->vlan();
}
void
acl_rule_ip_t::vlan_is(vlan_id_t vlan) {
   pimpl->vlan_is(vlan);
}
vlan_id_t
acl_rule_ip_t::vlan_mask() const {
   return pimpl->vlan_mask();
}
void
acl_rule_ip_t::vlan_mask_is(vlan_id_t vlan_mask) {
   pimpl->vlan_mask_is(vlan_mask);
}
vlan_id_t
acl_rule_ip_t::inner_vlan() const {
   return pimpl->inner_vlan();
}
void
acl_rule_ip_t::inner_vlan_is(vlan_id_t inner_vlan) {
   pimpl->inner_vlan_is(inner_vlan);
}
vlan_id_t
acl_rule_ip_t::inner_vlan_mask() const {
   return pimpl->inner_vlan_mask();
}
void
acl_rule_ip_t::inner_vlan_mask_is(vlan_id_t inner_vlan_mask) {
   pimpl->inner_vlan_mask_is(inner_vlan_mask);
}
uint8_t
acl_rule_ip_t::ip_protocol() const {
   return pimpl->ip_protocol();
}
void
acl_rule_ip_t::ip_protocol_is(uint8_t ip_protocol) {
   pimpl->ip_protocol_is(ip_protocol);
}
acl_ttl_spec_t
acl_rule_ip_t::ttl() const {
   return pimpl->ttl();
}
void
acl_rule_ip_t::ttl_is(acl_ttl_spec_t ttl) {
   pimpl->ttl_is(ttl);
}
ip_addr_mask_t
acl_rule_ip_t::source_addr() const {
   return pimpl->source_addr();
}
void
acl_rule_ip_t::source_addr_is(ip_addr_mask_t const & source_addr) {
   pimpl->source_addr_is(source_addr);
}
ip_addr_mask_t
acl_rule_ip_t::destination_addr() const {
   return pimpl->destination_addr();
}
void
acl_rule_ip_t::destination_addr_is(ip_addr_mask_t const & destination_addr) {
   pimpl->destination_addr_is(destination_addr);
}
acl_port_spec_t
acl_rule_ip_t::source_port() const {
   return pimpl->source_port();
}
void
acl_rule_ip_t::source_port_is(acl_port_spec_t source_port) {
   pimpl->source_port_is(source_port);
}
acl_port_spec_t
acl_rule_ip_t::destination_port() const {
   return pimpl->destination_port();
}
void
acl_rule_ip_t::destination_port_is(acl_port_spec_t destination_port) {
   pimpl->destination_port_is(destination_port);
}
std::string
acl_rule_ip_t::nexthop_group() const {
   return pimpl->nexthop_group();
}
void
acl_rule_ip_t::nexthop_group_is(std::string nexthop_group) {
   pimpl->nexthop_group_is(nexthop_group);
}
uint16_t
acl_rule_ip_t::tcp_flags() const {
   return pimpl->tcp_flags();
}
void
acl_rule_ip_t::tcp_flags_is(uint16_t tcp_flags) {
   pimpl->tcp_flags_is(tcp_flags);
}
acl_ip_type_t
acl_rule_ip_t::ip_type() const {
   return pimpl->ip_type();
}
void
acl_rule_ip_t::ip_type_is(acl_ip_type_t ip_type) {
   pimpl->ip_type_is(ip_type);
}
bool
acl_rule_ip_t::established() const {
   return pimpl->established();
}
void
acl_rule_ip_t::established_is(bool established) {
   pimpl->established_is(established);
}
uint16_t
acl_rule_ip_t::icmp_type() const {
   return pimpl->icmp_type();
}
void
acl_rule_ip_t::icmp_type_is(uint16_t icmp_type) {
   pimpl->icmp_type_is(icmp_type);
}
uint16_t
acl_rule_ip_t::icmp_code() const {
   return pimpl->icmp_code();
}
void
acl_rule_ip_t::icmp_code_is(uint16_t icmp_code) {
   pimpl->icmp_code_is(icmp_code);
}
uint8_t
acl_rule_ip_t::priority_value() const {
   return pimpl->priority_value();
}
void
acl_rule_ip_t::priority_value_is(uint8_t priority_value) {
   pimpl->priority_value_is(priority_value);
}
uint8_t
acl_rule_ip_t::priority_mask() const {
   return pimpl->priority_mask();
}
void
acl_rule_ip_t::priority_mask_is(uint8_t priority_mask) {
   pimpl->priority_mask_is(priority_mask);
}
bool
acl_rule_ip_t::match_fragments() const {
   return pimpl->match_fragments();
}
void
acl_rule_ip_t::match_fragments_is(bool match_fragments) {
   pimpl->match_fragments_is(match_fragments);
}
bool
acl_rule_ip_t::match_ip_priority() const {
   return pimpl->match_ip_priority();
}
void
acl_rule_ip_t::match_ip_priority_is(bool match_ip_priority) {
   pimpl->match_ip_priority_is(match_ip_priority);
}
bool
acl_rule_ip_t::operator==(acl_rule_ip_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
acl_rule_ip_t::operator!=(acl_rule_ip_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
acl_rule_ip_t::operator<(acl_rule_ip_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
acl_rule_ip_t::hash() const {
   return pimpl->hash();
}
void
acl_rule_ip_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
acl_rule_ip_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const acl_rule_ip_t& obj) {
   return operator<<(os, *obj.pimpl);
}


acl_rule_eth_t::acl_rule_eth_t(): acl_rule_base_t() {
   pimpl = std::shared_ptr<acl_rule_eth_impl_t>(
      new acl_rule_eth_impl_t()
   );
}
acl_rule_eth_t::acl_rule_eth_t(
   const acl_rule_eth_t& other): acl_rule_base_t(other)
{
   pimpl = std::make_unique<acl_rule_eth_impl_t>(
      acl_rule_eth_impl_t(*other.pimpl));
}
acl_rule_eth_t&
acl_rule_eth_t::operator=(
   acl_rule_eth_t const & other)
{
   acl_rule_base_t::operator=(other);
   pimpl = std::shared_ptr<acl_rule_eth_impl_t>(
      new acl_rule_eth_impl_t(*other.pimpl));
   return *this;
}

vlan_id_t
acl_rule_eth_t::vlan() const {
   return pimpl->vlan();
}
void
acl_rule_eth_t::vlan_is(vlan_id_t vlan) {
   pimpl->vlan_is(vlan);
}
vlan_id_t
acl_rule_eth_t::vlan_mask() const {
   return pimpl->vlan_mask();
}
void
acl_rule_eth_t::vlan_mask_is(vlan_id_t vlan_mask) {
   pimpl->vlan_mask_is(vlan_mask);
}
vlan_id_t
acl_rule_eth_t::inner_vlan() const {
   return pimpl->inner_vlan();
}
void
acl_rule_eth_t::inner_vlan_is(vlan_id_t inner_vlan) {
   pimpl->inner_vlan_is(inner_vlan);
}
vlan_id_t
acl_rule_eth_t::inner_vlan_mask() const {
   return pimpl->inner_vlan_mask();
}
void
acl_rule_eth_t::inner_vlan_mask_is(vlan_id_t inner_vlan_mask) {
   pimpl->inner_vlan_mask_is(inner_vlan_mask);
}
eth_addr_t
acl_rule_eth_t::source_addr() const {
   return pimpl->source_addr();
}
void
acl_rule_eth_t::source_addr_is(eth_addr_t source_addr) {
   pimpl->source_addr_is(source_addr);
}
eth_addr_t
acl_rule_eth_t::destination_addr() const {
   return pimpl->destination_addr();
}
void
acl_rule_eth_t::destination_addr_is(eth_addr_t destination_addr) {
   pimpl->destination_addr_is(destination_addr);
}
eth_addr_t
acl_rule_eth_t::source_mask() const {
   return pimpl->source_mask();
}
void
acl_rule_eth_t::source_mask_is(eth_addr_t source_mask) {
   pimpl->source_mask_is(source_mask);
}
eth_addr_t
acl_rule_eth_t::destination_mask() const {
   return pimpl->destination_mask();
}
void
acl_rule_eth_t::destination_mask_is(eth_addr_t destination_mask) {
   pimpl->destination_mask_is(destination_mask);
}
uint32_t
acl_rule_eth_t::eth_protocol() const {
   return pimpl->eth_protocol();
}
void
acl_rule_eth_t::eth_protocol_is(uint32_t eth_protocol) {
   pimpl->eth_protocol_is(eth_protocol);
}
bool
acl_rule_eth_t::operator==(acl_rule_eth_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
acl_rule_eth_t::operator!=(acl_rule_eth_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
acl_rule_eth_t::hash() const {
   return pimpl->hash();
}
void
acl_rule_eth_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
acl_rule_eth_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const acl_rule_eth_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_ACL_H
