// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/directflow.h"

namespace eos {

//
// flow_match_field_set_t
//

uint32_t
changebit(uint32_t value, uint32_t bit, bool enabled) {
   uint32_t mask = (enabled << bit);
   if(enabled) {
      return (value | mask);
   } else {
      return (value & ~mask);
   }
}

void
flow_match_field_set_t::eth_src_is(bool enabled) {
   match_bitset_ = changebit(match_bitset_, 0, enabled);
}

bool
flow_match_field_set_t::eth_src() const {
   uint32_t bit = 0;
   return (match_bitset_ & (1 << bit));
}

void
flow_match_field_set_t::eth_dst_is(bool enabled) {
   match_bitset_ = changebit(match_bitset_, 1, enabled);
}

bool
flow_match_field_set_t::eth_dst() const {
   uint32_t bit = 1;
   return (match_bitset_ & (1 << bit));
}

void
flow_match_field_set_t::eth_type_is(bool enabled) {
   match_bitset_ = changebit(match_bitset_, 2, enabled);
}

bool
flow_match_field_set_t::eth_type() const {
   uint32_t bit = 2;
   return (match_bitset_ & (1 << bit));
}

void
flow_match_field_set_t::vlan_id_is(bool enabled) {
   match_bitset_ = changebit(match_bitset_, 3, enabled);
}

bool
flow_match_field_set_t::vlan_id() const {
   uint32_t bit = 3;
   return (match_bitset_ & (1 << bit));
}

void
flow_match_field_set_t::cos_is(bool enabled) {
   match_bitset_ = changebit(match_bitset_, 4, enabled);
}

bool
flow_match_field_set_t::cos() const {
   uint32_t bit = 4;
   return (match_bitset_ & (1 << bit));
}

void
flow_match_field_set_t::ip_src_is(bool enabled) {
   match_bitset_ = changebit(match_bitset_, 5, enabled);
}

bool
flow_match_field_set_t::ip_src() const {
   uint32_t bit = 5;
   return (match_bitset_ & (1 << bit));
}

void
flow_match_field_set_t::ip_dst_is(bool enabled) {
   match_bitset_ = changebit(match_bitset_, 6, enabled);
}

bool
flow_match_field_set_t::ip_dst() const {
   uint32_t bit = 6;
   return (match_bitset_ & (1 << bit));
}

//
// flow_action_set_t
//

void
flow_action_set_t::set_output_intfs_is(bool enabled) {
   action_bitset_ = changebit(action_bitset_, 0, enabled);
}

bool
flow_action_set_t::set_output_intfs() const {
   uint32_t bit = 0;
   return (action_bitset_ & (1 << bit));
}

void
flow_action_set_t::set_vlan_id_is(bool enabled) {
   action_bitset_ = changebit(action_bitset_, 1, enabled);
}

bool
flow_action_set_t::set_vlan_id() const {
   uint32_t bit = 1;
   return (action_bitset_ & (1 << bit));
}

void
flow_action_set_t::set_cos_is(bool enabled) {
   action_bitset_ = changebit(action_bitset_, 2, enabled);
}

bool
flow_action_set_t::set_cos() const {
   uint32_t bit = 2;
   return (action_bitset_ & (1 << bit));
}

void
flow_action_set_t::set_eth_src_is(bool enabled) {
   action_bitset_ = changebit(action_bitset_, 3, enabled);
}

bool
flow_action_set_t::set_eth_src() const {
   uint32_t bit = 3;
   return (action_bitset_ & (1 << bit));
}

void
flow_action_set_t::set_eth_dst_is(bool enabled) {
   action_bitset_ = changebit(action_bitset_, 4, enabled);
}

bool
flow_action_set_t::set_eth_dst() const {
   uint32_t bit = 4;
   return (action_bitset_ & (1 << bit));
}

void
flow_action_set_t::set_ip_src_is(bool enabled) {
   action_bitset_ = changebit(action_bitset_, 5, enabled);
}

bool
flow_action_set_t::set_ip_src() const {
   uint32_t bit = 5;
   return (action_bitset_ & (1 << bit));
}

void
flow_action_set_t::set_ip_dst_is(bool enabled) {
   action_bitset_ = changebit(action_bitset_, 6, enabled);
}

bool
flow_action_set_t::set_ip_dst() const {
   uint32_t bit = 6;
   return (action_bitset_ & (1 << bit));
}

//
// flow_handler
//

flow_handler::flow_handler() {
   // TODO
}

flow_handler::~flow_handler() {
}

void
flow_handler::watch_all_flows(bool should_watch) {
}

void
flow_handler::on_flow_status(const std::string & name, flow_status_t status) {
}

//
// directflow_mgr
//

directflow_mgr::directflow_mgr() {
   // TODO: No op impl.
}

class directflow_mgr_impl : public directflow_mgr {
 public:
   directflow_mgr_impl() {
   }
};

directflow_mgr * get_directflow_mgr() {
   static directflow_mgr_impl impl;
   return &impl;
}

void
directflow_mgr::flow_entry_foreach(callback_func handler, void * context) {
}

void
directflow_mgr::flow_entry_foreach(callback_func handler, void * context,
                                   std::string const & bookmark ) {
}

bool
directflow_mgr::exists(std::string const & name) const {
   return false;
}

void
directflow_mgr::flow_entry_set(flow_entry_t const & flow_entry) {
}

void
directflow_mgr::flow_entry_del(std::string const & name) {
}

flow_status_t
directflow_mgr::flow_status(std::string const & name) const {
   return FLOW_STATUS_UNKNOWN;
}

flow_rejected_reason_t
directflow_mgr::flow_rejected_reason(std::string const & name) const {
   return FLOW_REJECTED_OTHER;
}

}
