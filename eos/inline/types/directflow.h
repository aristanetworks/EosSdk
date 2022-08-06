// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_DIRECTFLOW_H
#define EOS_INLINE_TYPES_DIRECTFLOW_H

namespace eos {

flow_match_field_set_t::flow_match_field_set_t() :
      match_bitset_() {
}

bool
flow_match_field_set_t::operator==(flow_match_field_set_t const & other) const {
   return match_bitset_ == other.match_bitset_;
}

bool
flow_match_field_set_t::operator!=(flow_match_field_set_t const & other) const {
   return !operator==(other);
}

bool
flow_match_field_set_t::operator<(flow_match_field_set_t const & other) const {
   if(match_bitset_ != other.match_bitset_) {
      return match_bitset_ < other.match_bitset_;
   }
   return false;
}

uint32_t
flow_match_field_set_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
flow_match_field_set_t::mix_me(hash_mix & h) const {
   h.mix(match_bitset_); // uint32_t
}

std::string
flow_match_field_set_t::to_string() const {
   std::ostringstream ss;
   ss << "flow_match_field_set_t(";
   ss << "match_bitset=" << match_bitset_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const flow_match_field_set_t& obj) {
   os << obj.to_string();
   return os;
}



flow_match_t::flow_match_t() {
   pimpl = std::shared_ptr<flow_match_impl_t>(
      new flow_match_impl_t()
   );
}
flow_match_t::flow_match_t(
   const flow_match_t& other)
{
   pimpl = std::make_unique<flow_match_impl_t>(
      flow_match_impl_t(*other.pimpl));
}
flow_match_t&
flow_match_t::operator=(
   flow_match_t const & other)
{
   pimpl = std::shared_ptr<flow_match_impl_t>(
      new flow_match_impl_t(*other.pimpl));
   return *this;
}

flow_match_field_set_t
flow_match_t::match_field_set() const {
   return pimpl->match_field_set();
}
void
flow_match_t::match_field_set_is(flow_match_field_set_t match_field_set) {
   pimpl->match_field_set_is(match_field_set);
}
std::set<intf_id_t> const &
flow_match_t::input_intfs() const {
   return pimpl->input_intfs();
}
void
flow_match_t::input_intfs_is(std::set<intf_id_t> const & input_intfs) {
   pimpl->input_intfs_is(input_intfs);
}
void
flow_match_t::input_intf_set(intf_id_t const & value) {
   pimpl->input_intf_set(value);
}
void
flow_match_t::input_intf_del(intf_id_t const & value) {
   pimpl->input_intf_del(value);
}
eth_addr_t
flow_match_t::eth_src() const {
   return pimpl->eth_src();
}
void
flow_match_t::eth_src_is(eth_addr_t eth_src) {
   pimpl->eth_src_is(eth_src);
}
void
flow_match_t::eth_src_is(eth_addr_t src, eth_addr_t mask) {
   pimpl->eth_src_is(src, mask);
}
eth_addr_t
flow_match_t::eth_src_mask() const {
   return pimpl->eth_src_mask();
}
void
flow_match_t::eth_src_mask_is(eth_addr_t eth_src_mask) {
   pimpl->eth_src_mask_is(eth_src_mask);
}
eth_addr_t
flow_match_t::eth_dst() const {
   return pimpl->eth_dst();
}
void
flow_match_t::eth_dst_is(eth_addr_t eth_dst) {
   pimpl->eth_dst_is(eth_dst);
}
void
flow_match_t::eth_dst_is(eth_addr_t dst, eth_addr_t mask) {
   pimpl->eth_dst_is(dst, mask);
}
eth_addr_t
flow_match_t::eth_dst_mask() const {
   return pimpl->eth_dst_mask();
}
void
flow_match_t::eth_dst_mask_is(eth_addr_t eth_dst_mask) {
   pimpl->eth_dst_mask_is(eth_dst_mask);
}
eth_type_t
flow_match_t::eth_type() const {
   return pimpl->eth_type();
}
void
flow_match_t::eth_type_is(eth_type_t eth_type) {
   pimpl->eth_type_is(eth_type);
}
vlan_id_t
flow_match_t::vlan_id() const {
   return pimpl->vlan_id();
}
void
flow_match_t::vlan_id_is(vlan_id_t vlan_id) {
   pimpl->vlan_id_is(vlan_id);
}
void
flow_match_t::vlan_id_is(vlan_id_t vlan_id, uint16_t mask) {
   pimpl->vlan_id_is(vlan_id, mask);
}
vlan_id_t
flow_match_t::vlan_id_mask() const {
   return pimpl->vlan_id_mask();
}
void
flow_match_t::vlan_id_mask_is(vlan_id_t vlan_id_mask) {
   pimpl->vlan_id_mask_is(vlan_id_mask);
}
cos_t
flow_match_t::cos() const {
   return pimpl->cos();
}
void
flow_match_t::cos_is(cos_t cos) {
   pimpl->cos_is(cos);
}
ip_addr_t
flow_match_t::ip_src() const {
   return pimpl->ip_src();
}
void
flow_match_t::ip_src_is(ip_addr_t const & ip_src) {
   pimpl->ip_src_is(ip_src);
}
void
flow_match_t::ip_src_is(ip_addr_t const & src, ip_addr_t const & mask) {
   pimpl->ip_src_is(src, mask);
}
ip_addr_t
flow_match_t::ip_src_mask() const {
   return pimpl->ip_src_mask();
}
void
flow_match_t::ip_src_mask_is(ip_addr_t const & ip_src_mask) {
   pimpl->ip_src_mask_is(ip_src_mask);
}
ip_addr_t
flow_match_t::ip_dst() const {
   return pimpl->ip_dst();
}
void
flow_match_t::ip_dst_is(ip_addr_t const & ip_dst) {
   pimpl->ip_dst_is(ip_dst);
}
void
flow_match_t::ip_dst_is(ip_addr_t const & dst, ip_addr_t const & mask) {
   pimpl->ip_dst_is(dst, mask);
}
ip_addr_t
flow_match_t::ip_dst_mask() const {
   return pimpl->ip_dst_mask();
}
void
flow_match_t::ip_dst_mask_is(ip_addr_t const & ip_dst_mask) {
   pimpl->ip_dst_mask_is(ip_dst_mask);
}
bool
flow_match_t::operator==(flow_match_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
flow_match_t::operator!=(flow_match_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
flow_match_t::operator<(flow_match_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
flow_match_t::hash() const {
   return pimpl->hash();
}
void
flow_match_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
flow_match_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const flow_match_t& obj) {
   return operator<<(os, *obj.pimpl);
}


flow_action_set_t::flow_action_set_t() :
      action_bitset_() {
}

bool
flow_action_set_t::operator==(flow_action_set_t const & other) const {
   return action_bitset_ == other.action_bitset_;
}

bool
flow_action_set_t::operator!=(flow_action_set_t const & other) const {
   return !operator==(other);
}

uint32_t
flow_action_set_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
flow_action_set_t::mix_me(hash_mix & h) const {
   h.mix(action_bitset_); // uint32_t
}

std::string
flow_action_set_t::to_string() const {
   std::ostringstream ss;
   ss << "flow_action_set_t(";
   ss << "action_bitset=" << action_bitset_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const flow_action_set_t& obj) {
   os << obj.to_string();
   return os;
}



flow_action_t::flow_action_t() {
   pimpl = std::shared_ptr<flow_action_impl_t>(
      new flow_action_impl_t()
   );
}
flow_action_t::flow_action_t(
   const flow_action_t& other)
{
   pimpl = std::make_unique<flow_action_impl_t>(
      flow_action_impl_t(*other.pimpl));
}
flow_action_t&
flow_action_t::operator=(
   flow_action_t const & other)
{
   pimpl = std::shared_ptr<flow_action_impl_t>(
      new flow_action_impl_t(*other.pimpl));
   return *this;
}

flow_action_set_t
flow_action_t::action_set() const {
   return pimpl->action_set();
}
void
flow_action_t::action_set_is(flow_action_set_t action_set) {
   pimpl->action_set_is(action_set);
}
std::set<intf_id_t> const &
flow_action_t::output_intfs() const {
   return pimpl->output_intfs();
}
void
flow_action_t::output_intfs_is(std::set<intf_id_t> const & output_intfs) {
   pimpl->output_intfs_is(output_intfs);
}
void
flow_action_t::output_intf_set(intf_id_t const & value) {
   pimpl->output_intf_set(value);
}
void
flow_action_t::output_intf_del(intf_id_t const & value) {
   pimpl->output_intf_del(value);
}
vlan_id_t
flow_action_t::vlan_id() const {
   return pimpl->vlan_id();
}
void
flow_action_t::vlan_id_is(vlan_id_t vlan_id) {
   pimpl->vlan_id_is(vlan_id);
}
cos_t
flow_action_t::cos() const {
   return pimpl->cos();
}
void
flow_action_t::cos_is(cos_t cos) {
   pimpl->cos_is(cos);
}
eth_addr_t
flow_action_t::eth_src() const {
   return pimpl->eth_src();
}
void
flow_action_t::eth_src_is(eth_addr_t eth_src) {
   pimpl->eth_src_is(eth_src);
}
eth_addr_t
flow_action_t::eth_dst() const {
   return pimpl->eth_dst();
}
void
flow_action_t::eth_dst_is(eth_addr_t eth_dst) {
   pimpl->eth_dst_is(eth_dst);
}
ip_addr_t
flow_action_t::ip_src() const {
   return pimpl->ip_src();
}
void
flow_action_t::ip_src_is(ip_addr_t const & ip_src) {
   pimpl->ip_src_is(ip_src);
}
ip_addr_t
flow_action_t::ip_dst() const {
   return pimpl->ip_dst();
}
void
flow_action_t::ip_dst_is(ip_addr_t const & ip_dst) {
   pimpl->ip_dst_is(ip_dst);
}
bool
flow_action_t::operator==(flow_action_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
flow_action_t::operator!=(flow_action_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
flow_action_t::hash() const {
   return pimpl->hash();
}
void
flow_action_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
flow_action_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const flow_action_t& obj) {
   return operator<<(os, *obj.pimpl);
}


flow_entry_t::flow_entry_t() {
   pimpl = std::shared_ptr<flow_entry_impl_t>(
      new flow_entry_impl_t()
   );
}
flow_entry_t::flow_entry_t(std::string const & name, flow_match_t match,
                                  flow_action_t action, flow_priority_t priority) {
   pimpl = std::shared_ptr<flow_entry_impl_t>(
      new flow_entry_impl_t(
         name,
         match,
         action,
         priority
      )
   );
}
flow_entry_t::flow_entry_t(
   const flow_entry_t& other)
{
   pimpl = std::make_unique<flow_entry_impl_t>(
      flow_entry_impl_t(*other.pimpl));
}
flow_entry_t&
flow_entry_t::operator=(
   flow_entry_t const & other)
{
   pimpl = std::shared_ptr<flow_entry_impl_t>(
      new flow_entry_impl_t(*other.pimpl));
   return *this;
}

std::string
flow_entry_t::name() const {
   return pimpl->name();
}
flow_match_t
flow_entry_t::match() const {
   return pimpl->match();
}
flow_action_t
flow_entry_t::action() const {
   return pimpl->action();
}
flow_priority_t
flow_entry_t::priority() const {
   return pimpl->priority();
}
bool
flow_entry_t::operator==(flow_entry_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
flow_entry_t::operator!=(flow_entry_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
flow_entry_t::hash() const {
   return pimpl->hash();
}
void
flow_entry_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
flow_entry_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const flow_entry_t& obj) {
   return operator<<(os, *obj.pimpl);
}


flow_counters_t::flow_counters_t() {
   pimpl = std::shared_ptr<flow_counters_impl_t>(
      new flow_counters_impl_t()
   );
}
flow_counters_t::flow_counters_t(
   const flow_counters_t& other)
{
   pimpl = std::make_unique<flow_counters_impl_t>(
      flow_counters_impl_t(*other.pimpl));
}
flow_counters_t&
flow_counters_t::operator=(
   flow_counters_t const & other)
{
   pimpl = std::shared_ptr<flow_counters_impl_t>(
      new flow_counters_impl_t(*other.pimpl));
   return *this;
}

uint64_t
flow_counters_t::bytes() const {
   return pimpl->bytes();
}
uint64_t
flow_counters_t::packets() const {
   return pimpl->packets();
}
bool
flow_counters_t::operator==(flow_counters_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
flow_counters_t::operator!=(flow_counters_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
flow_counters_t::hash() const {
   return pimpl->hash();
}
void
flow_counters_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
flow_counters_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const flow_counters_t& obj) {
   return operator<<(os, *obj.pimpl);
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const flow_status_t & enum_val) {
   if (enum_val==FLOW_STATUS_UNKNOWN) {
      os << "FLOW_STATUS_UNKNOWN";
   } else if (enum_val==FLOW_CREATED) {
      os << "FLOW_CREATED";
   } else if (enum_val==FLOW_DELETED) {
      os << "FLOW_DELETED";
   } else if (enum_val==FLOW_REJECTED) {
      os << "FLOW_REJECTED";
   } else if (enum_val==FLOW_PENDING) {
      os << "FLOW_PENDING";
   } else if (enum_val==FLOW_HW_TABLE_PENDING) {
      os << "FLOW_HW_TABLE_PENDING";
   } else if (enum_val==FLOW_REQUEST_ACCEPTED) {
      os << "FLOW_REQUEST_ACCEPTED";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const flow_rejected_reason_t & enum_val) {
   if (enum_val==FLOW_REJECTED_BAD_MATCH) {
      os << "FLOW_REJECTED_BAD_MATCH";
   } else if (enum_val==FLOW_REJECTED_BAD_ACTION) {
      os << "FLOW_REJECTED_BAD_ACTION";
   } else if (enum_val==FLOW_REJECTED_HW_TABLE_FULL) {
      os << "FLOW_REJECTED_HW_TABLE_FULL";
   } else if (enum_val==FLOW_REJECTED_OTHER) {
      os << "FLOW_REJECTED_OTHER";
   } else if (enum_val==FLOW_REJECTED_ACTIONS_UNSUPPORTED) {
      os << "FLOW_REJECTED_ACTIONS_UNSUPPORTED";
   } else if (enum_val==FLOW_REJECTED_TIMEOUT_NOT_SUPPORTED) {
      os << "FLOW_REJECTED_TIMEOUT_NOT_SUPPORTED";
   } else {
      os << "Unknown value";
   }
   return os;
}

}

#endif // EOS_INLINE_TYPES_DIRECTFLOW_H
