// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_DIRECTFLOW_H
#define EOS_INLINE_DIRECTFLOW_H

namespace eos {

//
// flow_match_field_set_t method implementation
//

flow_match_field_set_t::flow_match_field_set_t() : match_bitset_(0) {
}

//
// flow_match_t method implementation
//

flow_match_t::flow_match_t() : match_field_set_(),
                               input_intfs_(),
                               eth_src_(),
                               eth_dst_(),
                               eth_type_(0),
                               vlan_id_(0),
                               vlan_id_mask_(0),
                               cos_(0),
                               ip_src_(),
                               ip_src_mask_(),
                               ip_dst_(),
                               ip_dst_mask_() {
}

void
flow_match_t::input_intfs_is(const std::set<intf_id_t> & input_intfs) {
   input_intfs_ = input_intfs;
}

std::set<intf_id_t>
flow_match_t::input_intfs() const {
   return input_intfs_;
}

void
flow_match_t::eth_src_is(eth_addr_t src, eth_addr_t mask) {
   eth_src_ = src;
   eth_src_mask_ = mask;
}

eth_addr_t
flow_match_t::eth_src() const {
   return eth_src_;
}

eth_addr_t
flow_match_t::eth_src_mask() const {
   return eth_src_mask_;
}

void
flow_match_t::eth_dst_is(eth_addr_t dst, eth_addr_t mask) {
   eth_dst_ = dst;
   eth_dst_mask_ = mask;
}

eth_addr_t
flow_match_t::eth_dst() const {
   return eth_dst_;
}

eth_addr_t
flow_match_t::eth_dst_mask() const {
   return eth_dst_mask_;
}

void
flow_match_t::eth_type_is(eth_type_t eth_type) {
   eth_type_ = eth_type;
}

eth_type_t
flow_match_t::eth_type() const {
   return eth_type_;
}
   
void
flow_match_t::vlan_id_is(vlan_id_t vlan_id, uint16_t mask) {
   vlan_id_ = vlan_id;
   vlan_id_mask_ = mask;
}

vlan_id_t
flow_match_t::vlan_id() const {
   return vlan_id_;
}

uint16_t
flow_match_t::vlan_id_mask() const {
   return vlan_id_mask_;
}

void
flow_match_t::cos_is(cos_t cos) {
   cos_ = cos;
}

cos_t
flow_match_t::cos() const {
   return cos_;
}
   
void
flow_match_t::ip_src_is(const ip_addr_t & src, const ip_addr_mask_t & mask) {
   ip_src_ = src;
   ip_src_mask_ = mask;
}

ip_addr_t
flow_match_t::ip_src() const {
   return ip_src_;
}

ip_addr_mask_t
flow_match_t::ip_src_mask() const {
   return ip_src_mask_;
}

void
flow_match_t::ip_dst_is(const ip_addr_t & dst, const ip_addr_mask_t & mask) {
   ip_dst_ = dst;
   ip_dst_mask_ = mask;
}

ip_addr_t
flow_match_t::ip_dst() const {
   return ip_dst_;
}

ip_addr_mask_t
flow_match_t::ip_dst_mask() const {
   return ip_dst_mask_;
}

//
// flow_action_set_t method implementation
//

flow_action_set_t::flow_action_set_t() : action_bitset_(0) {
}


//
// flow_action_t method implementation
//

flow_action_t::flow_action_t() : action_set_(),
                                 output_intfs_(),
                                 vlan_id_(0),
                                 cos_(0),
                                 eth_src_(),
                                 eth_dst_(),
                                 ip_src_(),
                                 ip_dst_() {
}

void
flow_action_t::output_intfs_is(const std::set<intf_id_t> & output_intfs) {
   output_intfs_ = output_intfs;
}

std::set<intf_id_t>
flow_action_t::output_intfs() const {
   return output_intfs_;
}

void
flow_action_t::vlan_id_is(vlan_id_t vlan_id) {
   vlan_id_ = vlan_id;
}

vlan_id_t
flow_action_t::vlan_id() const {
   return vlan_id_;
}

void
flow_action_t::cos_is(cos_t cos) {
   cos_ = cos;
}

cos_t
flow_action_t::cos() const {
   return cos_;
}

void
flow_action_t::eth_src_is(eth_addr_t src) {
   eth_src_ = src;
}

eth_addr_t
flow_action_t::eth_src() const {
   return eth_src_;
}

void
flow_action_t::eth_dst_is(eth_addr_t dst) {
   eth_dst_ = dst;
}

eth_addr_t
flow_action_t::eth_dst() const {
   return eth_dst_;
}

void
flow_action_t::ip_src_is(const ip_addr_t & src) {
   ip_src_ = src;
}

ip_addr_t
flow_action_t::ip_src() const {
   return ip_src_;
}

void
flow_action_t::ip_dst_is(const ip_addr_t & dst) {
   ip_dst_ = dst;
}

ip_addr_t
flow_action_t::ip_dst() const {
   return ip_dst_;
}

//
// flow_entry_t method implementation
//

flow_entry_t::flow_entry_t() :
      name_(), match_(), action_(), priority_(0) {
}

flow_entry_t::flow_entry_t(const std::string & name, flow_match_t match,
                           flow_action_t action, flow_priority_t priority) :
      name_(name), match_(match), action_(action), priority_(priority) {
}

std::string
flow_entry_t::name() const {
   return name_;
}

flow_match_t
flow_entry_t::match() const {
   return match_;
}

flow_action_t
flow_entry_t::action() const {
   return action_;
}

flow_priority_t
flow_entry_t::priority() const {
   return priority_;
}

}

#endif // EOS_INLINE_DIRECTFLOW_H
