// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_NEXTHOP_GROUP_IMPL_H
#define EOS_INLINE_TYPES_NEXTHOP_GROUP_IMPL_H

namespace eos {





nexthop_group_mpls_action_impl_t::nexthop_group_mpls_action_impl_t() :
      action_type_(), label_stack_() {
}

nexthop_group_mpls_action_impl_t::nexthop_group_mpls_action_impl_t(
         mpls_action_t action_type) :
      action_type_(action_type), label_stack_() {
}

nexthop_group_mpls_action_impl_t::nexthop_group_mpls_action_impl_t(
         mpls_action_t action_type,
         std::forward_list<mpls_label_t> const & label_stack) :
      action_type_(action_type), label_stack_(label_stack) {
}

mpls_action_t
nexthop_group_mpls_action_impl_t::action_type() const {
   return action_type_;
}

void
nexthop_group_mpls_action_impl_t::action_type_is(mpls_action_t action_type) {
   action_type_ = action_type;
}

std::forward_list<mpls_label_t> const &
nexthop_group_mpls_action_impl_t::label_stack() const {
   return label_stack_;
}

void
nexthop_group_mpls_action_impl_t::label_stack_is(
         std::forward_list<mpls_label_t> const & label_stack) {
   label_stack_ = label_stack;
}

void
nexthop_group_mpls_action_impl_t::label_stack_set(mpls_label_t const & label_stack)
       {
   label_stack_.push_front(label_stack);
}

void
nexthop_group_mpls_action_impl_t::label_stack_del(mpls_label_t const & label_stack)
       {
   label_stack_.remove(label_stack);
}

bool
nexthop_group_mpls_action_impl_t::operator==(
         nexthop_group_mpls_action_impl_t const & other) const {
   return action_type_ == other.action_type_ &&
          label_stack_ == other.label_stack_;
}

bool
nexthop_group_mpls_action_impl_t::operator!=(
         nexthop_group_mpls_action_impl_t const & other) const {
   return !operator==(other);
}

bool
nexthop_group_mpls_action_impl_t::operator<(
         nexthop_group_mpls_action_impl_t const & other) const {
   if(action_type_ != other.action_type_) {
      return action_type_ < other.action_type_;
   } else if(label_stack_ != other.label_stack_) {
      return label_stack_ < other.label_stack_;
   }
   return false;
}

uint32_t
nexthop_group_mpls_action_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
nexthop_group_mpls_action_impl_t::mix_me(hash_mix & h) const {
   h.mix(action_type_); // mpls_action_t
   for (auto it=label_stack_.cbegin();
        it!=label_stack_.cend(); ++it) {
      h.mix(*it); // mpls_label_t
   }
}

std::string
nexthop_group_mpls_action_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "nexthop_group_mpls_action_t(";
   ss << "action_type=" << action_type_;
   ss << ", label_stack=" <<"'";
   bool first_label_stack = true;
   for (auto it=label_stack_.cbegin();
        it!=label_stack_.cend(); ++it) {
      if (first_label_stack) {
         ss << (*it);
         first_label_stack = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const nexthop_group_mpls_action_impl_t& obj) {
   os << obj.to_string();
   return os;
}



nexthop_group_entry_counter_impl_t::nexthop_group_entry_counter_impl_t() :
      packets_(0), bytes_(0), valid_(false) {
}

nexthop_group_entry_counter_impl_t::nexthop_group_entry_counter_impl_t(
         uint64_t packets, uint64_t bytes, bool valid) :
      packets_(packets), bytes_(bytes), valid_(valid) {
}

uint64_t
nexthop_group_entry_counter_impl_t::packets() const {
   return packets_;
}

uint64_t
nexthop_group_entry_counter_impl_t::bytes() const {
   return bytes_;
}

bool
nexthop_group_entry_counter_impl_t::valid() const {
   return valid_;
}

bool
nexthop_group_entry_counter_impl_t::operator==(
         nexthop_group_entry_counter_impl_t const & other) const {
   return packets_ == other.packets_ &&
          bytes_ == other.bytes_ &&
          valid_ == other.valid_;
}

bool
nexthop_group_entry_counter_impl_t::operator!=(
         nexthop_group_entry_counter_impl_t const & other) const {
   return !operator==(other);
}

bool
nexthop_group_entry_counter_impl_t::operator<(
         nexthop_group_entry_counter_impl_t const & other) const {
   if(packets_ != other.packets_) {
      return packets_ < other.packets_;
   } else if(bytes_ != other.bytes_) {
      return bytes_ < other.bytes_;
   } else if(valid_ != other.valid_) {
      return valid_ < other.valid_;
   }
   return false;
}

uint32_t
nexthop_group_entry_counter_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
nexthop_group_entry_counter_impl_t::mix_me(hash_mix & h) const {
   h.mix(packets_); // uint64_t
   h.mix(bytes_); // uint64_t
   h.mix(valid_); // bool
}

std::string
nexthop_group_entry_counter_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "nexthop_group_entry_counter_t(";
   ss << "packets=" << packets_;
   ss << ", bytes=" << bytes_;
   ss << ", valid=" << valid_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const nexthop_group_entry_counter_impl_t& obj) {
   os << obj.to_string();
   return os;
}



nexthop_group_entry_impl_t::nexthop_group_entry_impl_t() :
      mpls_action_(), nexthop_(), intf_(), sbfd_session_key_(),
      child_nexthop_group_() {
}

nexthop_group_entry_impl_t::nexthop_group_entry_impl_t(
         ip_addr_t const & nexthop) :
      mpls_action_(), nexthop_(nexthop), intf_(), sbfd_session_key_(),
      child_nexthop_group_() {
}

nexthop_group_entry_impl_t::nexthop_group_entry_impl_t(
         ip_addr_t const & nexthop, intf_id_t const & intf) :
      mpls_action_(), nexthop_(nexthop), intf_(intf), sbfd_session_key_(),
      child_nexthop_group_() {
}

nexthop_group_entry_impl_t::nexthop_group_entry_impl_t(
         std::string const & child_nexthop_group) :
      mpls_action_(), nexthop_(), intf_(), sbfd_session_key_(),
      child_nexthop_group_(child_nexthop_group) {
}

nexthop_group_mpls_action_t
nexthop_group_entry_impl_t::mpls_action() const {
   return mpls_action_;
}

void
nexthop_group_entry_impl_t::mpls_action_is(
         nexthop_group_mpls_action_t const & mpls_action) {
   mpls_action_ = mpls_action;
}

ip_addr_t
nexthop_group_entry_impl_t::nexthop() const {
   return nexthop_;
}

void
nexthop_group_entry_impl_t::nexthop_is(ip_addr_t const & nexthop) {
   if (!!nexthop && !child_nexthop_group_.empty()) {
      panic(invalid_argument_error(
        "child_nexthop_group", 
        "Next level nexthop group name and nexthop ip "
        "cannot be set together"));
   }
   nexthop_ = nexthop;
}

intf_id_t
nexthop_group_entry_impl_t::intf() const {
   return intf_;
}

void
nexthop_group_entry_impl_t::intf_is(intf_id_t const & intf) {
   if (!!intf && !child_nexthop_group_.empty()) {
      panic(invalid_argument_error(
        "child_nexthop_group", 
        "Next level nexthop group name and interface "
        "cannot be set together"));
   }
   intf_ = intf;
}

sbfd_echo_session_key_t
nexthop_group_entry_impl_t::sbfd_session_key() const {
   return sbfd_session_key_;
}

void
nexthop_group_entry_impl_t::sbfd_session_key_is(
         sbfd_echo_session_key_t const & sbfd_session_key) {
   sbfd_session_key_ = sbfd_session_key;
}

std::string
nexthop_group_entry_impl_t::child_nexthop_group() const {
   return child_nexthop_group_;
}

void
nexthop_group_entry_impl_t::child_nexthop_group_is(
         std::string const & child_nexthop_group) {
   if ((!!nexthop_ || !!intf_) && !child_nexthop_group.empty()) {
      panic(invalid_argument_error(
        "child_nexthop_group", 
        "Next level nexthop group name and nexthop ip "
        "(or interface) cannot be set together"));
   }
   child_nexthop_group_ = child_nexthop_group;
}

bool
nexthop_group_entry_impl_t::operator==(nexthop_group_entry_impl_t const & other)
       const {
   return mpls_action_ == other.mpls_action_ &&
          nexthop_ == other.nexthop_ &&
          intf_ == other.intf_ &&
          sbfd_session_key_ == other.sbfd_session_key_ &&
          child_nexthop_group_ == other.child_nexthop_group_;
}

bool
nexthop_group_entry_impl_t::operator!=(nexthop_group_entry_impl_t const & other)
       const {
   return !operator==(other);
}

bool
nexthop_group_entry_impl_t::operator<(nexthop_group_entry_impl_t const & other)
       const {
   if(mpls_action_ != other.mpls_action_) {
      return mpls_action_ < other.mpls_action_;
   } else if(nexthop_ != other.nexthop_) {
      return nexthop_ < other.nexthop_;
   } else if(intf_ != other.intf_) {
      return intf_ < other.intf_;
   } else if(sbfd_session_key_ != other.sbfd_session_key_) {
      return sbfd_session_key_ < other.sbfd_session_key_;
   } else if(child_nexthop_group_ != other.child_nexthop_group_) {
      return child_nexthop_group_ < other.child_nexthop_group_;
   }
   return false;
}

uint32_t
nexthop_group_entry_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
nexthop_group_entry_impl_t::mix_me(hash_mix & h) const {
   h.mix(mpls_action_); // nexthop_group_mpls_action_t
   h.mix(nexthop_); // ip_addr_t
   h.mix(intf_); // intf_id_t
   h.mix(sbfd_session_key_); // sbfd_echo_session_key_t
   h.mix(child_nexthop_group_); // std::string
}

std::string
nexthop_group_entry_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "nexthop_group_entry_t(";
   ss << "mpls_action=" << mpls_action_;
   ss << ", nexthop=" << nexthop_;
   ss << ", intf=" << intf_;
   ss << ", sbfd_session_key=" << sbfd_session_key_;
   ss << ", child_nexthop_group='" << child_nexthop_group_ << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const nexthop_group_entry_impl_t& obj) {
   os << obj.to_string();
   return os;
}



nexthop_group_impl_t::nexthop_group_impl_t() :
      name_(), type_(), gre_key_type_(NEXTHOP_GROUP_GRE_KEY_NULL), ttl_(64),
      source_ip_(), source_intf_(), autosize_(false), nexthops_(),
      destination_ips_(), counters_unshared_(), hierarchical_fecs_enabled_(false),
      counters_persistent_(), version_id_() {
}

nexthop_group_impl_t::nexthop_group_impl_t(std::string name,
                                                  nexthop_group_encap_t type) :
      name_(name), type_(type), gre_key_type_(NEXTHOP_GROUP_GRE_KEY_NULL),
      ttl_(64), source_ip_(), source_intf_(), autosize_(false), nexthops_(),
      destination_ips_(), counters_unshared_(), hierarchical_fecs_enabled_(false),
      counters_persistent_(), version_id_() {
}

nexthop_group_impl_t::nexthop_group_impl_t(
         std::string name, nexthop_group_encap_t type,
         nexthop_group_gre_key_t gre_key_type) :
      name_(name), type_(type), gre_key_type_(gre_key_type), ttl_(64),
      source_ip_(), source_intf_(), autosize_(false), nexthops_(),
      destination_ips_(), counters_unshared_(), hierarchical_fecs_enabled_(false),
      counters_persistent_(), version_id_() {
}

nexthop_group_impl_t::nexthop_group_impl_t(std::string name,
                                                  ip_addr_t const & source_ip) :
      name_(name), type_(), gre_key_type_(), ttl_(), source_ip_(source_ip),
      source_intf_(), autosize_(), nexthops_(), destination_ips_(),
      counters_unshared_(), hierarchical_fecs_enabled_(false),
      counters_persistent_(), version_id_() {
}

nexthop_group_impl_t::nexthop_group_impl_t(
         std::string name, ip_addr_t const & source_ip,
         std::map<uint16_t, nexthop_group_entry_t> const & nexthops) :
      name_(name), type_(), gre_key_type_(), ttl_(), source_ip_(source_ip),
      source_intf_(), autosize_(), nexthops_(nexthops), destination_ips_(),
      counters_unshared_(), hierarchical_fecs_enabled_(false),
      counters_persistent_(), version_id_() {
}

std::string
nexthop_group_impl_t::name() const {
   return name_;
}

nexthop_group_encap_t
nexthop_group_impl_t::type() const {
   return type_;
}

nexthop_group_gre_key_t
nexthop_group_impl_t::gre_key_type() const {
   return gre_key_type_;
}

uint16_t
nexthop_group_impl_t::ttl() const {
   return ttl_;
}

void
nexthop_group_impl_t::ttl_is(uint16_t ttl) {
   ttl_ = ttl;
}

ip_addr_t
nexthop_group_impl_t::source_ip() const {
   return source_ip_;
}

void
nexthop_group_impl_t::source_ip_is(ip_addr_t const & source_ip) {
   if (type_ == NEXTHOP_GROUP_MPLS && !!source_ip) {
      panic(invalid_argument_error(
                  "source_ip",
                  "MPLS nexthop group cannot specify a source IP"));
   } else if (!!source_ip) {
      // If we're setting a source ip, clear any
      // source interface configuration
      source_intf_is(intf_id_t());
   }
   source_ip_ = source_ip;
}

intf_id_t
nexthop_group_impl_t::source_intf() const {
   return source_intf_;
}

void
nexthop_group_impl_t::source_intf_is(intf_id_t source_intf) {
   if (!!source_intf) {
      // If we're setting a source interface, clear any
      // source ip configuration
      source_ip_is(ip_addr_t());
   }
   source_intf_ = source_intf;
}

bool
nexthop_group_impl_t::autosize() const {
   return autosize_;
}

void
nexthop_group_impl_t::autosize_is(bool autosize) {
   autosize_ = autosize;
}

uint16_t
nexthop_group_impl_t::size() const {

   if (nexthops_.empty()) {
      return 0;
   }
   return nexthops_.rbegin()->first + 1;
}

std::map<uint16_t, nexthop_group_entry_t> const &
nexthop_group_impl_t::nexthops() const {
   return nexthops_;
}

void
nexthop_group_impl_t::nexthops_is(
         std::map<uint16_t, nexthop_group_entry_t> const & nexthops) {
   nexthops_ = nexthops;
}

void
nexthop_group_impl_t::nexthop_set(uint16_t key,
                                  nexthop_group_entry_t const & value) {
   nexthops_[key] = value;
}

void
nexthop_group_impl_t::nexthop_del(uint16_t key) {
   nexthops_.erase(key);
}

std::map<uint16_t, ip_addr_t> const &
nexthop_group_impl_t::destination_ips() const {
   return destination_ips_;
}

void
nexthop_group_impl_t::destination_ips_is(
         std::map<uint16_t, ip_addr_t> const & destination_ips) {
   destination_ips_ = destination_ips;
}

void
nexthop_group_impl_t::destination_ip_set(uint16_t key, ip_addr_t const & value) {
   destination_ips_[key] = value;
}

void
nexthop_group_impl_t::destination_ip_del(uint16_t key) {
   destination_ips_.erase(key);
}

bool
nexthop_group_impl_t::counters_unshared() const {
   return counters_unshared_;
}

void
nexthop_group_impl_t::counters_unshared_is(bool counters_unshared) {
   counters_unshared_ = counters_unshared;
}

bool
nexthop_group_impl_t::hierarchical_fecs_enabled() const {
   return hierarchical_fecs_enabled_;
}

void
nexthop_group_impl_t::hierarchical_fecs_enabled_is(bool hierarchical_fecs_enabled) {
   hierarchical_fecs_enabled_ = hierarchical_fecs_enabled;
}

bool
nexthop_group_impl_t::counters_persistent() const {
   return counters_persistent_;
}

void
nexthop_group_impl_t::counters_persistent_is(bool counters_persistent) {
   counters_persistent_ = counters_persistent;
}

uint16_t
nexthop_group_impl_t::version_id() const {
   return version_id_;
}

void
nexthop_group_impl_t::version_id_is(uint16_t version_id) {
   version_id_ = version_id;
}

bool
nexthop_group_impl_t::operator==(nexthop_group_impl_t const & other) const {
   return name_ == other.name_ &&
          type_ == other.type_ &&
          gre_key_type_ == other.gre_key_type_ &&
          ttl_ == other.ttl_ &&
          source_ip_ == other.source_ip_ &&
          source_intf_ == other.source_intf_ &&
          autosize_ == other.autosize_ &&
          nexthops_ == other.nexthops_ &&
          destination_ips_ == other.destination_ips_ &&
          counters_unshared_ == other.counters_unshared_ &&
          hierarchical_fecs_enabled_ == other.hierarchical_fecs_enabled_ &&
          counters_persistent_ == other.counters_persistent_ &&
          version_id_ == other.version_id_;
}

bool
nexthop_group_impl_t::operator!=(nexthop_group_impl_t const & other) const {
   return !operator==(other);
}

bool
nexthop_group_impl_t::operator<(nexthop_group_impl_t const & other) const {
   if(name_ != other.name_) {
      return name_ < other.name_;
   } else if(type_ != other.type_) {
      return type_ < other.type_;
   } else if(gre_key_type_ != other.gre_key_type_) {
      return gre_key_type_ < other.gre_key_type_;
   } else if(ttl_ != other.ttl_) {
      return ttl_ < other.ttl_;
   } else if(source_ip_ != other.source_ip_) {
      return source_ip_ < other.source_ip_;
   } else if(source_intf_ != other.source_intf_) {
      return source_intf_ < other.source_intf_;
   } else if(autosize_ != other.autosize_) {
      return autosize_ < other.autosize_;
   } else if(nexthops_ != other.nexthops_) {
      return nexthops_ < other.nexthops_;
   } else if(destination_ips_ != other.destination_ips_) {
      return destination_ips_ < other.destination_ips_;
   } else if(counters_unshared_ != other.counters_unshared_) {
      return counters_unshared_ < other.counters_unshared_;
   } else if(hierarchical_fecs_enabled_ != other.hierarchical_fecs_enabled_) {
      return hierarchical_fecs_enabled_ < other.hierarchical_fecs_enabled_;
   } else if(counters_persistent_ != other.counters_persistent_) {
      return counters_persistent_ < other.counters_persistent_;
   } else if(version_id_ != other.version_id_) {
      return version_id_ < other.version_id_;
   }
   return false;
}

uint32_t
nexthop_group_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
nexthop_group_impl_t::mix_me(hash_mix & h) const {
   h.mix(name_); // std::string
   h.mix(type_); // nexthop_group_encap_t
   h.mix(gre_key_type_); // nexthop_group_gre_key_t
   h.mix(ttl_); // uint16_t
   h.mix(source_ip_); // ip_addr_t
   h.mix(source_intf_); // intf_id_t
   h.mix(autosize_); // bool
   for (auto it=nexthops_.cbegin();
        it!=nexthops_.cend(); ++it) {
      h.mix(it->first); // uint16_t
      h.mix(it->second); // nexthop_group_entry_t
   }
   for (auto it=destination_ips_.cbegin();
        it!=destination_ips_.cend(); ++it) {
      h.mix(it->first); // uint16_t
      h.mix(it->second); // ip_addr_t
   }
   h.mix(counters_unshared_); // bool
   h.mix(hierarchical_fecs_enabled_); // bool
   h.mix(counters_persistent_); // bool
   h.mix(version_id_); // uint16_t
}

std::string
nexthop_group_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "nexthop_group_t(";
   ss << "name='" << name_ << "'";
   ss << ", type=" << type_;
   ss << ", gre_key_type=" << gre_key_type_;
   ss << ", ttl=" << ttl_;
   ss << ", source_ip=" << source_ip_;
   ss << ", source_intf=" << source_intf_;
   ss << ", autosize=" << autosize_;
   ss << ", nexthops=" <<"'";
   bool first_nexthops = true;
   for (auto it=nexthops_.cbegin();
        it!=nexthops_.cend(); ++it) {
      if (first_nexthops) {
         ss << it->first << "=" << it->second;
         first_nexthops = false;
      } else {
         ss << "," << it->first << "=" << it->second;
      }
   }
   ss << "'";
   ss << ", destination_ips=" <<"'";
   bool first_destination_ips = true;
   for (auto it=destination_ips_.cbegin();
        it!=destination_ips_.cend(); ++it) {
      if (first_destination_ips) {
         ss << it->first << "=" << it->second;
         first_destination_ips = false;
      } else {
         ss << "," << it->first << "=" << it->second;
      }
   }
   ss << "'";
   ss << ", counters_unshared=" << counters_unshared_;
   ss << ", hierarchical_fecs_enabled=" << hierarchical_fecs_enabled_;
   ss << ", counters_persistent=" << counters_persistent_;
   ss << ", version_id=" << version_id_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const nexthop_group_impl_t& obj) {
   os << obj.to_string();
   return os;
}





nexthop_group_programmed_status_impl_t::nexthop_group_programmed_status_impl_t()
       :
      counter_state_(NEXTHOP_GROUP_COUNTER_INACTIVE) {
}

nexthop_group_programmed_status_impl_t::nexthop_group_programmed_status_impl_t(
         nexthop_group_counter_state_t counter_state) :
      counter_state_(counter_state) {
}

nexthop_group_counter_state_t
nexthop_group_programmed_status_impl_t::counter_state() const {
   return counter_state_;
}

bool
nexthop_group_programmed_status_impl_t::operator==(
         nexthop_group_programmed_status_impl_t const & other) const {
   return counter_state_ == other.counter_state_;
}

bool
nexthop_group_programmed_status_impl_t::operator!=(
         nexthop_group_programmed_status_impl_t const & other) const {
   return !operator==(other);
}

bool
nexthop_group_programmed_status_impl_t::operator<(
         nexthop_group_programmed_status_impl_t const & other) const {
   if(counter_state_ != other.counter_state_) {
      return counter_state_ < other.counter_state_;
   }
   return false;
}

uint32_t
nexthop_group_programmed_status_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
nexthop_group_programmed_status_impl_t::mix_me(hash_mix & h) const {
   h.mix(counter_state_); // nexthop_group_counter_state_t
}

std::string
nexthop_group_programmed_status_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "nexthop_group_programmed_status_t(";
   ss << "counter_state=" << counter_state_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const nexthop_group_programmed_status_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/nexthop_group.h>

#endif // EOS_INLINE_TYPES_NEXTHOP_GROUP_IMPL_H
