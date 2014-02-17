// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_DIRECTFLOW_H
#define EOS_INLINE_DIRECTFLOW_H

namespace eos {

//
// flow_match_field_set_t method implementation
//

inline flow_match_field_set_t::flow_match_field_set_t() : match_bitset_() {
}

//
// flow_match_t method implementation
//

inline flow_match_t::flow_match_t()
   : match_field_set_(),
     input_intfs_(),
     eth_src_(),
     eth_dst_(),
     eth_type_(),
     vlan_id_(),
     vlan_id_mask_(),
     cos_(),
     ip_src_(),
     ip_src_mask_(),
     ip_dst_(),
     ip_dst_mask_() {
}

inline void
flow_match_t::match_field_set_is(flow_match_field_set_t const & field_set) {
   match_field_set_ = field_set;
}

inline flow_match_field_set_t
flow_match_t::match_field_set() const {
   return match_field_set_;
}

inline void
flow_match_t::input_intfs_is(std::set<intf_id_t> const & input_intfs) {
   input_intfs_ = input_intfs;
}

inline void
flow_match_t::input_intf_set(intf_id_t intf_id) {
   input_intfs_.insert(intf_id);
}

inline void
flow_match_t::input_intf_del(intf_id_t intf_id) {
   input_intfs_.erase(intf_id);
}

inline std::set<intf_id_t>
flow_match_t::input_intfs() const {
   return input_intfs_;
}

inline void
flow_match_t::eth_src_is(eth_addr_t src, eth_addr_t mask) {
   eth_src_ = src;
   eth_src_mask_ = mask;
}

inline eth_addr_t
flow_match_t::eth_src() const {
   return eth_src_;
}

inline eth_addr_t
flow_match_t::eth_src_mask() const {
   return eth_src_mask_;
}

inline void
flow_match_t::eth_dst_is(eth_addr_t dst, eth_addr_t mask) {
   eth_dst_ = dst;
   eth_dst_mask_ = mask;
}

inline eth_addr_t
flow_match_t::eth_dst() const {
   return eth_dst_;
}

inline eth_addr_t
flow_match_t::eth_dst_mask() const {
   return eth_dst_mask_;
}

inline void
flow_match_t::eth_type_is(eth_type_t eth_type) {
   eth_type_ = eth_type;
}

inline eth_type_t
flow_match_t::eth_type() const {
   return eth_type_;
}

inline void
flow_match_t::vlan_id_is(vlan_id_t vlan_id, uint16_t mask) {
   vlan_id_ = vlan_id;
   vlan_id_mask_ = mask;
}

inline vlan_id_t
flow_match_t::vlan_id() const {
   return vlan_id_;
}

inline uint16_t
flow_match_t::vlan_id_mask() const {
   return vlan_id_mask_;
}

inline void
flow_match_t::cos_is(cos_t cos) {
   cos_ = cos;
}

inline cos_t
flow_match_t::cos() const {
   return cos_;
}

inline void
flow_match_t::ip_src_is(ip_addr_t const & src, ip_addr_t const & mask) {
   ip_src_ = src;
   ip_src_mask_ = mask;
}

inline ip_addr_t
flow_match_t::ip_src() const {
   return ip_src_;
}

inline ip_addr_t
flow_match_t::ip_src_mask() const {
   return ip_src_mask_;
}

inline void
flow_match_t::ip_dst_is(ip_addr_t const & dst, ip_addr_t const & mask) {
   ip_dst_ = dst;
   ip_dst_mask_ = mask;
}

inline ip_addr_t
flow_match_t::ip_dst() const {
   return ip_dst_;
}

inline ip_addr_t
flow_match_t::ip_dst_mask() const {
   return ip_dst_mask_;
}

//
// flow_action_set_t method implementation
//

inline flow_action_set_t::flow_action_set_t() : action_bitset_() {
}


//
// flow_action_t method implementation
//

inline flow_action_t::flow_action_t()
   : action_set_(),
     output_intfs_(),
     vlan_id_(),
     cos_(),
     eth_src_(),
     eth_dst_(),
     ip_src_(),
     ip_dst_() {
}


inline void
flow_action_t::action_set_is(flow_action_set_t const & action_set) {
   action_set_ = action_set;
}

inline flow_action_set_t
flow_action_t::action_set() const {
   return action_set_;
}

inline void
flow_action_t::output_intfs_is(const std::set<intf_id_t> & output_intfs) {
   output_intfs_ = output_intfs;
}

inline void
flow_action_t::output_intf_set(intf_id_t intf_id) {
   output_intfs_.insert(intf_id);
}

inline void
flow_action_t::output_intf_del(intf_id_t intf_id) {
   output_intfs_.erase(intf_id);
}

inline std::set<intf_id_t>
flow_action_t::output_intfs() const {
   return output_intfs_;
}

inline void
flow_action_t::vlan_id_is(vlan_id_t vlan_id) {
   vlan_id_ = vlan_id;
}

inline vlan_id_t
flow_action_t::vlan_id() const {
   return vlan_id_;
}

inline void
flow_action_t::cos_is(cos_t cos) {
   cos_ = cos;
}

inline cos_t
flow_action_t::cos() const {
   return cos_;
}

inline void
flow_action_t::eth_src_is(eth_addr_t src) {
   eth_src_ = src;
}

inline eth_addr_t
flow_action_t::eth_src() const {
   return eth_src_;
}

inline void
flow_action_t::eth_dst_is(eth_addr_t dst) {
   eth_dst_ = dst;
}

inline eth_addr_t
flow_action_t::eth_dst() const {
   return eth_dst_;
}

inline void
flow_action_t::ip_src_is(ip_addr_t const & src) {
   ip_src_ = src;
}

inline ip_addr_t
flow_action_t::ip_src() const {
   return ip_src_;
}

inline void
flow_action_t::ip_dst_is(ip_addr_t const & dst) {
   ip_dst_ = dst;
}

inline ip_addr_t
flow_action_t::ip_dst() const {
   return ip_dst_;
}

//
// flow_entry_t method implementation
//

inline flow_entry_t::flow_entry_t()
   : name_(), match_(), action_(), priority_() {
}

inline flow_entry_t::flow_entry_t(std::string const & name, flow_match_t match,
                                  flow_action_t action, flow_priority_t priority)
   : name_(name), match_(match), action_(action), priority_(priority) {
}

inline std::string
flow_entry_t::name() const {
   return name_;
}

inline flow_match_t
flow_entry_t::match() const {
   return match_;
}

inline flow_action_t
flow_entry_t::action() const {
   return action_;
}

inline flow_priority_t
flow_entry_t::priority() const {
   return priority_;
}

//
// flow_counter_t method implementation
//

inline flow_counters_t::flow_counters_t() : bytes_(0), packets_(0) {
}

inline uint64_t
flow_counters_t::bytes() const {
   return bytes_;
}

inline uint64_t
flow_counters_t::packets() const {
   return packets_;
}

}

#endif // EOS_INLINE_DIRECTFLOW_H
