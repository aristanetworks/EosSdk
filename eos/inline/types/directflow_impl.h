// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_DIRECTFLOW_IMPL_H
#define EOS_INLINE_TYPES_DIRECTFLOW_IMPL_H

namespace eos {



flow_match_impl_t::flow_match_impl_t() :
      match_field_set_(), input_intfs_(), eth_src_(), eth_src_mask_(), eth_dst_(),
      eth_dst_mask_(), eth_type_(), vlan_id_(), vlan_id_mask_(), cos_(), ip_src_(),
      ip_src_mask_(), ip_dst_(), ip_dst_mask_() {
}

flow_match_field_set_t
flow_match_impl_t::match_field_set() const {
   return match_field_set_;
}

void
flow_match_impl_t::match_field_set_is(flow_match_field_set_t match_field_set) {
   match_field_set_ = match_field_set;
}

std::set<intf_id_t> const &
flow_match_impl_t::input_intfs() const {
   return input_intfs_;
}

void
flow_match_impl_t::input_intfs_is(std::set<intf_id_t> const & input_intfs) {
   input_intfs_ = input_intfs;
}

void
flow_match_impl_t::input_intf_set(intf_id_t const & value) {
   input_intfs_.insert(value);
}

void
flow_match_impl_t::input_intf_del(intf_id_t const & value) {
   input_intfs_.erase(value);
}

eth_addr_t
flow_match_impl_t::eth_src() const {
   return eth_src_;
}

void
flow_match_impl_t::eth_src_is(eth_addr_t eth_src) {
   eth_src_ = eth_src;
}

void
flow_match_impl_t::eth_src_is(eth_addr_t src, eth_addr_t mask) {
   eth_src_ = src;
   eth_src_mask_ = mask;
}

eth_addr_t
flow_match_impl_t::eth_src_mask() const {
   return eth_src_mask_;
}

void
flow_match_impl_t::eth_src_mask_is(eth_addr_t eth_src_mask) {
   eth_src_mask_ = eth_src_mask;
}

eth_addr_t
flow_match_impl_t::eth_dst() const {
   return eth_dst_;
}

void
flow_match_impl_t::eth_dst_is(eth_addr_t eth_dst) {
   eth_dst_ = eth_dst;
}

void
flow_match_impl_t::eth_dst_is(eth_addr_t dst, eth_addr_t mask) {
   eth_dst_ = dst;
   eth_dst_mask_ = mask;
}

eth_addr_t
flow_match_impl_t::eth_dst_mask() const {
   return eth_dst_mask_;
}

void
flow_match_impl_t::eth_dst_mask_is(eth_addr_t eth_dst_mask) {
   eth_dst_mask_ = eth_dst_mask;
}

eth_type_t
flow_match_impl_t::eth_type() const {
   return eth_type_;
}

void
flow_match_impl_t::eth_type_is(eth_type_t eth_type) {
   eth_type_ = eth_type;
}

vlan_id_t
flow_match_impl_t::vlan_id() const {
   return vlan_id_;
}

void
flow_match_impl_t::vlan_id_is(vlan_id_t vlan_id) {
   vlan_id_ = vlan_id;
}

void
flow_match_impl_t::vlan_id_is(vlan_id_t vlan_id, uint16_t mask) {
   vlan_id_ = vlan_id;
   vlan_id_mask_ = mask;
}

vlan_id_t
flow_match_impl_t::vlan_id_mask() const {
   return vlan_id_mask_;
}

void
flow_match_impl_t::vlan_id_mask_is(vlan_id_t vlan_id_mask) {
   vlan_id_mask_ = vlan_id_mask;
}

cos_t
flow_match_impl_t::cos() const {
   return cos_;
}

void
flow_match_impl_t::cos_is(cos_t cos) {
   cos_ = cos;
}

ip_addr_t
flow_match_impl_t::ip_src() const {
   return ip_src_;
}

void
flow_match_impl_t::ip_src_is(ip_addr_t const & ip_src) {
   ip_src_ = ip_src;
}

void
flow_match_impl_t::ip_src_is(ip_addr_t const & src, ip_addr_t const & mask) {
   ip_src_ = src;
   ip_src_mask_ = mask;
}

ip_addr_t
flow_match_impl_t::ip_src_mask() const {
   return ip_src_mask_;
}

void
flow_match_impl_t::ip_src_mask_is(ip_addr_t const & ip_src_mask) {
   ip_src_mask_ = ip_src_mask;
}

ip_addr_t
flow_match_impl_t::ip_dst() const {
   return ip_dst_;
}

void
flow_match_impl_t::ip_dst_is(ip_addr_t const & ip_dst) {
   ip_dst_ = ip_dst;
}

void
flow_match_impl_t::ip_dst_is(ip_addr_t const & dst, ip_addr_t const & mask) {
   ip_dst_ = dst;
   ip_dst_mask_ = mask;
}

ip_addr_t
flow_match_impl_t::ip_dst_mask() const {
   return ip_dst_mask_;
}

void
flow_match_impl_t::ip_dst_mask_is(ip_addr_t const & ip_dst_mask) {
   ip_dst_mask_ = ip_dst_mask;
}

bool
flow_match_impl_t::operator==(flow_match_impl_t const & other) const {
   return match_field_set_ == other.match_field_set_ &&
          input_intfs_ == other.input_intfs_ &&
          eth_src_ == other.eth_src_ &&
          eth_src_mask_ == other.eth_src_mask_ &&
          eth_dst_ == other.eth_dst_ &&
          eth_dst_mask_ == other.eth_dst_mask_ &&
          eth_type_ == other.eth_type_ &&
          vlan_id_ == other.vlan_id_ &&
          vlan_id_mask_ == other.vlan_id_mask_ &&
          cos_ == other.cos_ &&
          ip_src_ == other.ip_src_ &&
          ip_src_mask_ == other.ip_src_mask_ &&
          ip_dst_ == other.ip_dst_ &&
          ip_dst_mask_ == other.ip_dst_mask_;
}

bool
flow_match_impl_t::operator!=(flow_match_impl_t const & other) const {
   return !operator==(other);
}

bool
flow_match_impl_t::operator<(flow_match_impl_t const & other) const {
   if(match_field_set_ != other.match_field_set_) {
      return match_field_set_ < other.match_field_set_;
   } else if(input_intfs_ != other.input_intfs_) {
      return input_intfs_ < other.input_intfs_;
   } else if(eth_src_ != other.eth_src_) {
      return eth_src_ < other.eth_src_;
   } else if(eth_src_mask_ != other.eth_src_mask_) {
      return eth_src_mask_ < other.eth_src_mask_;
   } else if(eth_dst_ != other.eth_dst_) {
      return eth_dst_ < other.eth_dst_;
   } else if(eth_dst_mask_ != other.eth_dst_mask_) {
      return eth_dst_mask_ < other.eth_dst_mask_;
   } else if(eth_type_ != other.eth_type_) {
      return eth_type_ < other.eth_type_;
   } else if(vlan_id_ != other.vlan_id_) {
      return vlan_id_ < other.vlan_id_;
   } else if(vlan_id_mask_ != other.vlan_id_mask_) {
      return vlan_id_mask_ < other.vlan_id_mask_;
   } else if(cos_ != other.cos_) {
      return cos_ < other.cos_;
   } else if(ip_src_ != other.ip_src_) {
      return ip_src_ < other.ip_src_;
   } else if(ip_src_mask_ != other.ip_src_mask_) {
      return ip_src_mask_ < other.ip_src_mask_;
   } else if(ip_dst_ != other.ip_dst_) {
      return ip_dst_ < other.ip_dst_;
   } else if(ip_dst_mask_ != other.ip_dst_mask_) {
      return ip_dst_mask_ < other.ip_dst_mask_;
   }
   return false;
}

uint32_t
flow_match_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
flow_match_impl_t::mix_me(hash_mix & h) const {
   h.mix(match_field_set_); // flow_match_field_set_t
   for (auto it=input_intfs_.cbegin();
        it!=input_intfs_.cend(); ++it) {
      h.mix(*it); // intf_id_t
   }
   h.mix(eth_src_); // eth_addr_t
   h.mix(eth_src_mask_); // eth_addr_t
   h.mix(eth_dst_); // eth_addr_t
   h.mix(eth_dst_mask_); // eth_addr_t
   h.mix(eth_type_); // eth_type_t
   h.mix(vlan_id_); // vlan_id_t
   h.mix(vlan_id_mask_); // vlan_id_t
   h.mix(cos_); // cos_t
   h.mix(ip_src_); // ip_addr_t
   h.mix(ip_src_mask_); // ip_addr_t
   h.mix(ip_dst_); // ip_addr_t
   h.mix(ip_dst_mask_); // ip_addr_t
}

std::string
flow_match_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "flow_match_t(";
   ss << "match_field_set=" << match_field_set_;
   ss << ", input_intfs=" <<"'";
   bool first_input_intfs = true;
   for (auto it=input_intfs_.cbegin();
        it!=input_intfs_.cend(); ++it) {
      if (first_input_intfs) {
         ss << (*it);
         first_input_intfs = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", eth_src=" << eth_src_;
   ss << ", eth_src_mask=" << eth_src_mask_;
   ss << ", eth_dst=" << eth_dst_;
   ss << ", eth_dst_mask=" << eth_dst_mask_;
   ss << ", eth_type=" << eth_type_;
   ss << ", vlan_id=" << vlan_id_;
   ss << ", vlan_id_mask=" << vlan_id_mask_;
   ss << ", cos=" << cos_;
   ss << ", ip_src=" << ip_src_;
   ss << ", ip_src_mask=" << ip_src_mask_;
   ss << ", ip_dst=" << ip_dst_;
   ss << ", ip_dst_mask=" << ip_dst_mask_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const flow_match_impl_t& obj) {
   os << obj.to_string();
   return os;
}





flow_action_impl_t::flow_action_impl_t() :
      action_set_(), output_intfs_(), vlan_id_(), cos_(), eth_src_(), eth_dst_(),
      ip_src_(), ip_dst_() {
}

flow_action_set_t
flow_action_impl_t::action_set() const {
   return action_set_;
}

void
flow_action_impl_t::action_set_is(flow_action_set_t action_set) {
   action_set_ = action_set;
}

std::set<intf_id_t> const &
flow_action_impl_t::output_intfs() const {
   return output_intfs_;
}

void
flow_action_impl_t::output_intfs_is(std::set<intf_id_t> const & output_intfs) {
   output_intfs_ = output_intfs;
}

void
flow_action_impl_t::output_intf_set(intf_id_t const & value) {
   output_intfs_.insert(value);
}

void
flow_action_impl_t::output_intf_del(intf_id_t const & value) {
   output_intfs_.erase(value);
}

vlan_id_t
flow_action_impl_t::vlan_id() const {
   return vlan_id_;
}

void
flow_action_impl_t::vlan_id_is(vlan_id_t vlan_id) {
   if (vlan_id == 0 || vlan_id == 4095) {
     panic(
        invalid_argument_error(
           "vlan_id",
           "vlan_id cannot be 0 or 4095."));
   }
   vlan_id_ = vlan_id;
}

cos_t
flow_action_impl_t::cos() const {
   return cos_;
}

void
flow_action_impl_t::cos_is(cos_t cos) {
   cos_ = cos;
}

eth_addr_t
flow_action_impl_t::eth_src() const {
   return eth_src_;
}

void
flow_action_impl_t::eth_src_is(eth_addr_t eth_src) {
   eth_src_ = eth_src;
}

eth_addr_t
flow_action_impl_t::eth_dst() const {
   return eth_dst_;
}

void
flow_action_impl_t::eth_dst_is(eth_addr_t eth_dst) {
   eth_dst_ = eth_dst;
}

ip_addr_t
flow_action_impl_t::ip_src() const {
   return ip_src_;
}

void
flow_action_impl_t::ip_src_is(ip_addr_t const & ip_src) {
   ip_src_ = ip_src;
}

ip_addr_t
flow_action_impl_t::ip_dst() const {
   return ip_dst_;
}

void
flow_action_impl_t::ip_dst_is(ip_addr_t const & ip_dst) {
   ip_dst_ = ip_dst;
}

bool
flow_action_impl_t::operator==(flow_action_impl_t const & other) const {
   return action_set_ == other.action_set_ &&
          output_intfs_ == other.output_intfs_ &&
          vlan_id_ == other.vlan_id_ &&
          cos_ == other.cos_ &&
          eth_src_ == other.eth_src_ &&
          eth_dst_ == other.eth_dst_ &&
          ip_src_ == other.ip_src_ &&
          ip_dst_ == other.ip_dst_;
}

bool
flow_action_impl_t::operator!=(flow_action_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
flow_action_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
flow_action_impl_t::mix_me(hash_mix & h) const {
   h.mix(action_set_); // flow_action_set_t
   for (auto it=output_intfs_.cbegin();
        it!=output_intfs_.cend(); ++it) {
      h.mix(*it); // intf_id_t
   }
   h.mix(vlan_id_); // vlan_id_t
   h.mix(cos_); // cos_t
   h.mix(eth_src_); // eth_addr_t
   h.mix(eth_dst_); // eth_addr_t
   h.mix(ip_src_); // ip_addr_t
   h.mix(ip_dst_); // ip_addr_t
}

std::string
flow_action_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "flow_action_t(";
   ss << "action_set=" << action_set_;
   ss << ", output_intfs=" <<"'";
   bool first_output_intfs = true;
   for (auto it=output_intfs_.cbegin();
        it!=output_intfs_.cend(); ++it) {
      if (first_output_intfs) {
         ss << (*it);
         first_output_intfs = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", vlan_id=" << vlan_id_;
   ss << ", cos=" << cos_;
   ss << ", eth_src=" << eth_src_;
   ss << ", eth_dst=" << eth_dst_;
   ss << ", ip_src=" << ip_src_;
   ss << ", ip_dst=" << ip_dst_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const flow_action_impl_t& obj) {
   os << obj.to_string();
   return os;
}



flow_entry_impl_t::flow_entry_impl_t() :
      name_(), match_(), action_(), priority_() {
}

flow_entry_impl_t::flow_entry_impl_t(std::string const & name,
                                            flow_match_t match,
                                            flow_action_t action,
                                            flow_priority_t priority) :
      name_(name), match_(match), action_(action), priority_(priority) {
}

std::string
flow_entry_impl_t::name() const {
   return name_;
}

flow_match_t
flow_entry_impl_t::match() const {
   return match_;
}

flow_action_t
flow_entry_impl_t::action() const {
   return action_;
}

flow_priority_t
flow_entry_impl_t::priority() const {
   return priority_;
}

bool
flow_entry_impl_t::operator==(flow_entry_impl_t const & other) const {
   return name_ == other.name_ &&
          match_ == other.match_ &&
          action_ == other.action_ &&
          priority_ == other.priority_;
}

bool
flow_entry_impl_t::operator!=(flow_entry_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
flow_entry_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
flow_entry_impl_t::mix_me(hash_mix & h) const {
   h.mix(name_); // std::string
   h.mix(match_); // flow_match_t
   h.mix(action_); // flow_action_t
   h.mix(priority_); // flow_priority_t
}

std::string
flow_entry_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "flow_entry_t(";
   ss << "name='" << name_ << "'";
   ss << ", match=" << match_;
   ss << ", action=" << action_;
   ss << ", priority=" << priority_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const flow_entry_impl_t& obj) {
   os << obj.to_string();
   return os;
}



flow_counters_impl_t::flow_counters_impl_t() :
      bytes_(0), packets_(0) {
}

uint64_t
flow_counters_impl_t::bytes() const {
   return bytes_;
}

uint64_t
flow_counters_impl_t::packets() const {
   return packets_;
}

bool
flow_counters_impl_t::operator==(flow_counters_impl_t const & other) const {
   return bytes_ == other.bytes_ &&
          packets_ == other.packets_;
}

bool
flow_counters_impl_t::operator!=(flow_counters_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
flow_counters_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
flow_counters_impl_t::mix_me(hash_mix & h) const {
   h.mix(bytes_); // uint64_t
   h.mix(packets_); // uint64_t
}

std::string
flow_counters_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "flow_counters_t(";
   ss << "bytes=" << bytes_;
   ss << ", packets=" << packets_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const flow_counters_impl_t& obj) {
   os << obj.to_string();
   return os;
}






}

#include <eos/inline/types/directflow.h>

#endif // EOS_INLINE_TYPES_DIRECTFLOW_IMPL_H
