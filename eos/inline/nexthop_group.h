// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_NEXTHOP_GROUP_H
#define INLINE_NEXTHOP_GROUP_H

#include <map>

#include <eos/mpls.h>
#include <eos/panic.h>
#include <eos/exception.h>

namespace eos {

inline nexthop_group_mpls_action_t::nexthop_group_mpls_action_t() :
      action_type_(MPLS_ACTION_NULL),
      label_stack_() {
}

inline nexthop_group_mpls_action_t::nexthop_group_mpls_action_t(
      mpls_action_t action_type) :
      action_type_(action_type),
      label_stack_() {
}

inline nexthop_group_mpls_action_t::nexthop_group_mpls_action_t(
      mpls_action_t action_type, std::list<mpls_label_t> const & label_stack) :
      action_type_(action_type),
      label_stack_(label_stack) {
}

inline nexthop_group_t::nexthop_group_t() :
      name_(""), ttl_(64),
      source_ip_(), source_intf_(),
      encap_type_(NEXTHOP_GROUP_TYPE_NULL),
      destination_ips_(),
      mpls_actions_(),
      persistent_(false) {
}

inline nexthop_group_t::nexthop_group_t(std::string const & name,
                                        nexthop_group_encap_t type) :
      name_(name), ttl_(64),
      source_ip_(), source_intf_(),
      encap_type_(type),
      destination_ips_(),
      mpls_actions_(),
      persistent_(false) {
}

inline void
nexthop_group_mpls_action_t::action_type_is(mpls_action_t action_type) {
   action_type_ = action_type;
}

inline mpls_action_t nexthop_group_mpls_action_t::action_type() const {
   return action_type_;
}

inline void
nexthop_group_mpls_action_t::label_stack_is(
      std::list<mpls_label_t> const & label_stack) {
   label_stack_ = label_stack;
}

inline std::list<mpls_label_t> const &
nexthop_group_mpls_action_t::label_stack() const {
   return label_stack_;
}

inline std::string const &
nexthop_group_t::name() const {
   return name_;
}

inline nexthop_group_encap_t
nexthop_group_t::type() const {
   return encap_type_;
}

inline void
nexthop_group_t::ttl_is(uint8_t ttl) {
   ttl_ = ttl;
}

inline uint8_t
nexthop_group_t::ttl() const {
   return ttl_;
}

inline void
nexthop_group_t::source_ip_is(ip_addr_t const & src_ip) {
   source_ip_ = src_ip;
   if (encap_type_ == NEXTHOP_GROUP_MPLS) {
      panic(invalid_argument_error(
                  "source_ip",
                  "MPLS nexthop_group_type cannot specify source_ip"));
   } else if (!!source_ip_) {
      // If we're setting a source ip, clear any
      // source interface configuration
      source_intf_is(intf_id_t());
   }
}

inline ip_addr_t const &
nexthop_group_t::source_ip() const {
   return source_ip_;
}

inline void
nexthop_group_t::source_intf_is(intf_id_t const & src_intf) {
   source_intf_ = src_intf;
   if(!!source_intf_) {
      // If we're setting a source interface, clear any
      // source ip configuration
      source_ip_is(ip_addr_t());
   }
}

inline intf_id_t const
nexthop_group_t::source_intf() const {
   return source_intf_;
}

inline std::map<uint16_t, ip_addr_t> const &
nexthop_group_t::destination_ips() const {
   return destination_ips_;
}

inline void
nexthop_group_t::mpls_actions_is(
      std::map<uint16_t, nexthop_group_mpls_action_t> const & mpls_actions) {
   if (encap_type_ != NEXTHOP_GROUP_MPLS) {
      panic(
            invalid_argument_error(
                  "mpls_actions",
                  "can only set MPLS labels when type is eos::NEXTHOP_GROUP_MPLS"));
   }
   mpls_actions_ = mpls_actions;
}

inline void
nexthop_group_t::mpls_actions_set(uint16_t seq,
                                  nexthop_group_mpls_action_t const & mpls_action) {
   if (encap_type_ != NEXTHOP_GROUP_MPLS) {
      panic(
            invalid_argument_error(
                  "mpls_actions",
                  "can only set MPLS labels when type is eos::NEXTHOP_GROUP_MPLS"));
   }
   mpls_actions_[seq] = mpls_action;
}

inline void
nexthop_group_t::mpls_actions_del(uint16_t seq) {
   if (encap_type_ != NEXTHOP_GROUP_MPLS) {
      panic(
            invalid_argument_error(
                  "mpls_actions",
                  "can only set MPLS labels when type is eos::NEXTHOP_GROUP_MPLS"));
   }
   mpls_actions_.erase(seq);
}

inline std::map<uint16_t, nexthop_group_mpls_action_t> const &
nexthop_group_t::mpls_actions() const {
   return mpls_actions_;
}

inline uint16_t
nexthop_group_t::size() const {
   // "size" really means "the index of the last non-zero entry in the
   // 'destinationIp' array of the
   // NexthopGroup::NexthopGroupConfigEntry in Ira/Routing.tac".
   //
   // We want the *index* of the last element in "destination_ips_",
   // not the "size" of the data structure, which tells you the number
   // of entries, to handle the case where "destination_ips_" is
   // sparse.
   if(destination_ips_.empty()) {
      return 0;
   }
   return destination_ips_.rbegin()->first + 1;
}

inline void
nexthop_group_t::persistent_is(bool persistent) {
   persistent_ = persistent;
}

inline bool
nexthop_group_t::persistent() const {
   return persistent_;
}

}

#endif // INLINE_NEXTHOP_GROUP_H
