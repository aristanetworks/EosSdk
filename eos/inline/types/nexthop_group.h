// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_NEXTHOP_GROUP_H
#define EOS_INLINE_TYPES_NEXTHOP_GROUP_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const nexthop_group_encap_t & enum_val) {
   if (enum_val==NEXTHOP_GROUP_TYPE_NULL) {
      os << "NEXTHOP_GROUP_TYPE_NULL";
   } else if (enum_val==NEXTHOP_GROUP_IP_IN_IP) {
      os << "NEXTHOP_GROUP_IP_IN_IP";
   } else if (enum_val==NEXTHOP_GROUP_GRE) {
      os << "NEXTHOP_GROUP_GRE";
   } else if (enum_val==NEXTHOP_GROUP_MPLS) {
      os << "NEXTHOP_GROUP_MPLS";
   } else if (enum_val==NEXTHOP_GROUP_MPLS_OVER_GRE) {
      os << "NEXTHOP_GROUP_MPLS_OVER_GRE";
   } else if (enum_val==NEXTHOP_GROUP_IP) {
      os << "NEXTHOP_GROUP_IP";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const nexthop_group_gre_key_t & enum_val) {
   if (enum_val==NEXTHOP_GROUP_GRE_KEY_NULL) {
      os << "NEXTHOP_GROUP_GRE_KEY_NULL";
   } else if (enum_val==NEXTHOP_GROUP_GRE_KEY_INGRESS_INTF) {
      os << "NEXTHOP_GROUP_GRE_KEY_INGRESS_INTF";
   } else {
      os << "Unknown value";
   }
   return os;
}


mpls_action_t
nexthop_group_mpls_action_t::action_type() const {
   return pimpl->action_type();
}
void
nexthop_group_mpls_action_t::action_type_is(mpls_action_t action_type) {
   pimpl->action_type_is(action_type);
}
std::forward_list<mpls_label_t> const &
nexthop_group_mpls_action_t::label_stack() const {
   return pimpl->label_stack();
}
void
nexthop_group_mpls_action_t::label_stack_is(
         std::forward_list<mpls_label_t> const & label_stack) {
   pimpl->label_stack_is(label_stack);
}
void
nexthop_group_mpls_action_t::label_stack_is(
         std::forward_list<mpls_label_t> && label_stack) {
   pimpl->label_stack_is(std::move(label_stack));
}
void
nexthop_group_mpls_action_t::label_stack_set(mpls_label_t const & label_stack) {
   pimpl->label_stack_set(label_stack);
}
void
nexthop_group_mpls_action_t::label_stack_set(mpls_label_t && label_stack) {
   pimpl->label_stack_set(std::move(label_stack));
}
void
nexthop_group_mpls_action_t::label_stack_del(mpls_label_t const & label_stack) {
   pimpl->label_stack_del(label_stack);
}
bool
nexthop_group_mpls_action_t::operator==(nexthop_group_mpls_action_t const & other)
       const {
   return pimpl->operator==(*other.pimpl);
}
bool
nexthop_group_mpls_action_t::operator!=(nexthop_group_mpls_action_t const & other)
       const {
   return pimpl->operator!=(*other.pimpl);
}
bool
nexthop_group_mpls_action_t::operator<(nexthop_group_mpls_action_t const & other)
       const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
nexthop_group_mpls_action_t::hash() const {
   return pimpl->hash();
}
void
nexthop_group_mpls_action_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
nexthop_group_mpls_action_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const nexthop_group_mpls_action_t& obj) {
   return operator<<(os, *obj.pimpl);
}


uint64_t
nexthop_group_entry_counter_t::packets() const {
   return pimpl->packets();
}
uint64_t
nexthop_group_entry_counter_t::bytes() const {
   return pimpl->bytes();
}
bool
nexthop_group_entry_counter_t::valid() const {
   return pimpl->valid();
}
bool
nexthop_group_entry_counter_t::operator==(
         nexthop_group_entry_counter_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
nexthop_group_entry_counter_t::operator!=(
         nexthop_group_entry_counter_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
nexthop_group_entry_counter_t::operator<(
         nexthop_group_entry_counter_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
nexthop_group_entry_counter_t::hash() const {
   return pimpl->hash();
}
void
nexthop_group_entry_counter_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
nexthop_group_entry_counter_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const nexthop_group_entry_counter_t& obj) {
   return operator<<(os, *obj.pimpl);
}


nexthop_group_mpls_action_t
nexthop_group_entry_t::mpls_action() const {
   return pimpl->mpls_action();
}
void
nexthop_group_entry_t::mpls_action_is(
         nexthop_group_mpls_action_t const & mpls_action) {
   pimpl->mpls_action_is(mpls_action);
}
void
nexthop_group_entry_t::mpls_action_is(nexthop_group_mpls_action_t && mpls_action) {
   pimpl->mpls_action_is(std::move(mpls_action));
}
ip_addr_t
nexthop_group_entry_t::nexthop() const {
   return pimpl->nexthop();
}
void
nexthop_group_entry_t::nexthop_is(ip_addr_t const & nexthop) {
   pimpl->nexthop_is(nexthop);
}
void
nexthop_group_entry_t::nexthop_is(ip_addr_t && nexthop) {
   pimpl->nexthop_is(std::move(nexthop));
}
intf_id_t
nexthop_group_entry_t::intf() const {
   return pimpl->intf();
}
void
nexthop_group_entry_t::intf_is(intf_id_t const & intf) {
   pimpl->intf_is(intf);
}
void
nexthop_group_entry_t::intf_is(intf_id_t && intf) {
   pimpl->intf_is(std::move(intf));
}
sbfd_echo_session_key_t
nexthop_group_entry_t::sbfd_session_key() const {
   return pimpl->sbfd_session_key();
}
void
nexthop_group_entry_t::sbfd_session_key_is(
         sbfd_echo_session_key_t const & sbfd_session_key) {
   pimpl->sbfd_session_key_is(sbfd_session_key);
}
void
nexthop_group_entry_t::sbfd_session_key_is(
         sbfd_echo_session_key_t && sbfd_session_key) {
   pimpl->sbfd_session_key_is(std::move(sbfd_session_key));
}
std::string
nexthop_group_entry_t::child_nexthop_group() const {
   return pimpl->child_nexthop_group();
}
void
nexthop_group_entry_t::child_nexthop_group_is(
         std::string const & child_nexthop_group) {
   pimpl->child_nexthop_group_is(child_nexthop_group);
}
void
nexthop_group_entry_t::child_nexthop_group_is(std::string && child_nexthop_group) {
   pimpl->child_nexthop_group_is(std::move(child_nexthop_group));
}
bool
nexthop_group_entry_t::operator==(nexthop_group_entry_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
nexthop_group_entry_t::operator!=(nexthop_group_entry_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
nexthop_group_entry_t::operator<(nexthop_group_entry_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
nexthop_group_entry_t::hash() const {
   return pimpl->hash();
}
void
nexthop_group_entry_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
nexthop_group_entry_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const nexthop_group_entry_t& obj) {
   return operator<<(os, *obj.pimpl);
}


std::string
nexthop_group_t::name() const {
   return pimpl->name();
}
nexthop_group_encap_t
nexthop_group_t::type() const {
   return pimpl->type();
}
nexthop_group_gre_key_t
nexthop_group_t::gre_key_type() const {
   return pimpl->gre_key_type();
}
uint16_t
nexthop_group_t::ttl() const {
   return pimpl->ttl();
}
void
nexthop_group_t::ttl_is(uint16_t ttl) {
   pimpl->ttl_is(ttl);
}
ip_addr_t
nexthop_group_t::source_ip() const {
   return pimpl->source_ip();
}
void
nexthop_group_t::source_ip_is(ip_addr_t const & source_ip) {
   pimpl->source_ip_is(source_ip);
}
void
nexthop_group_t::source_ip_is(ip_addr_t && source_ip) {
   pimpl->source_ip_is(std::move(source_ip));
}
intf_id_t
nexthop_group_t::source_intf() const {
   return pimpl->source_intf();
}
void
nexthop_group_t::source_intf_is(intf_id_t source_intf) {
   pimpl->source_intf_is(source_intf);
}
bool
nexthop_group_t::autosize() const {
   return pimpl->autosize();
}
void
nexthop_group_t::autosize_is(bool autosize) {
   pimpl->autosize_is(autosize);
}
uint16_t
nexthop_group_t::size() const {
   return pimpl->size();
}
uint16_t
nexthop_group_t::backup_size() const {
   return pimpl->backup_size();
}
std::map<uint16_t, nexthop_group_entry_t> const &
nexthop_group_t::nexthops() const {
   return pimpl->nexthops();
}
void
nexthop_group_t::nexthops_is(
         std::map<uint16_t, nexthop_group_entry_t> const & nexthops) {
   pimpl->nexthops_is(nexthops);
}
void
nexthop_group_t::nexthops_is(std::map<uint16_t, nexthop_group_entry_t> && nexthops)
       {
   pimpl->nexthops_is(std::move(nexthops));
}
void
nexthop_group_t::nexthop_set(uint16_t key, nexthop_group_entry_t const & value) {
   pimpl->nexthop_set(key, value);
}
void
nexthop_group_t::nexthop_set(uint16_t key, nexthop_group_entry_t && value) {
   pimpl->nexthop_set(key, std::move(value));
}
void
nexthop_group_t::nexthop_del(uint16_t key) {
   pimpl->nexthop_del(key);
}
std::map<uint16_t, nexthop_group_entry_t> const &
nexthop_group_t::backup_nexthops() const {
   return pimpl->backup_nexthops();
}
void
nexthop_group_t::backup_nexthops_is(
         std::map<uint16_t, nexthop_group_entry_t> const & backup_nexthops) {
   pimpl->backup_nexthops_is(backup_nexthops);
}
void
nexthop_group_t::backup_nexthops_is(
         std::map<uint16_t, nexthop_group_entry_t> && backup_nexthops) {
   pimpl->backup_nexthops_is(std::move(backup_nexthops));
}
void
nexthop_group_t::backup_nexthop_set(uint16_t key,
                                    nexthop_group_entry_t const & value) {
   pimpl->backup_nexthop_set(key, value);
}
void
nexthop_group_t::backup_nexthop_set(uint16_t key, nexthop_group_entry_t && value) {
   pimpl->backup_nexthop_set(key, std::move(value));
}
void
nexthop_group_t::backup_nexthop_del(uint16_t key) {
   pimpl->backup_nexthop_del(key);
}
std::map<uint16_t, ip_addr_t> const &
nexthop_group_t::destination_ips() const {
   return pimpl->destination_ips();
}
void
nexthop_group_t::destination_ips_is(
         std::map<uint16_t, ip_addr_t> const & destination_ips) {
   pimpl->destination_ips_is(destination_ips);
}
void
nexthop_group_t::destination_ips_is(
         std::map<uint16_t, ip_addr_t> && destination_ips) {
   pimpl->destination_ips_is(std::move(destination_ips));
}
void
nexthop_group_t::destination_ip_set(uint16_t key, ip_addr_t const & value) {
   pimpl->destination_ip_set(key, value);
}
void
nexthop_group_t::destination_ip_set(uint16_t key, ip_addr_t && value) {
   pimpl->destination_ip_set(key, std::move(value));
}
void
nexthop_group_t::destination_ip_del(uint16_t key) {
   pimpl->destination_ip_del(key);
}
bool
nexthop_group_t::counters_unshared() const {
   return pimpl->counters_unshared();
}
void
nexthop_group_t::counters_unshared_is(bool counters_unshared) {
   pimpl->counters_unshared_is(counters_unshared);
}
bool
nexthop_group_t::hierarchical_fecs_enabled() const {
   return pimpl->hierarchical_fecs_enabled();
}
void
nexthop_group_t::hierarchical_fecs_enabled_is(bool hierarchical_fecs_enabled) {
   pimpl->hierarchical_fecs_enabled_is(hierarchical_fecs_enabled);
}
bool
nexthop_group_t::counters_persistent() const {
   return pimpl->counters_persistent();
}
void
nexthop_group_t::counters_persistent_is(bool counters_persistent) {
   pimpl->counters_persistent_is(counters_persistent);
}
uint16_t
nexthop_group_t::version_id() const {
   return pimpl->version_id();
}
void
nexthop_group_t::version_id_is(uint16_t version_id) {
   pimpl->version_id_is(version_id);
}
bool
nexthop_group_t::per_entry_backups() const {
   return pimpl->per_entry_backups();
}
void
nexthop_group_t::per_entry_backups_is(bool per_entry_backups) {
   pimpl->per_entry_backups_is(per_entry_backups);
}
bool
nexthop_group_t::operator==(nexthop_group_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
nexthop_group_t::operator!=(nexthop_group_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
nexthop_group_t::operator<(nexthop_group_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
nexthop_group_t::hash() const {
   return pimpl->hash();
}
void
nexthop_group_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
nexthop_group_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const nexthop_group_t& obj) {
   return operator<<(os, *obj.pimpl);
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const nexthop_group_counter_state_t & enum_val) {
   if (enum_val==NEXTHOP_GROUP_COUNTER_INACTIVE) {
      os << "0";
   } else if (enum_val==NEXTHOP_GROUP_COUNTER_PROGRAMMING_FAILED) {
      os << "1";
   } else if (enum_val==NEXTHOP_GROUP_COUNTER_PROGRAMMING_COMPLETE) {
      os << "2";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const nexthop_group_programmed_hw_state_t & enum_val) {
   if (enum_val==NEXTHOP_GROUP_HW_DROP) {
      os << "0";
   } else if (enum_val==NEXTHOP_GROUP_HW_PARTIALLY_PROGRAMMED) {
      os << "1";
   } else if (enum_val==NEXTHOP_GROUP_HW_ALL_PROGRAMMED) {
      os << "2";
   } else {
      os << "Unknown value";
   }
   return os;
}


nexthop_group_counter_state_t
nexthop_group_programmed_status_t::counter_state() const {
   return pimpl->counter_state();
}
nexthop_group_programmed_hw_state_t
nexthop_group_programmed_status_t::hw_state() const {
   return pimpl->hw_state();
}
bool
nexthop_group_programmed_status_t::operator==(
         nexthop_group_programmed_status_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
nexthop_group_programmed_status_t::operator!=(
         nexthop_group_programmed_status_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
nexthop_group_programmed_status_t::operator<(
         nexthop_group_programmed_status_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
nexthop_group_programmed_status_t::hash() const {
   return pimpl->hash();
}
void
nexthop_group_programmed_status_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
nexthop_group_programmed_status_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const nexthop_group_programmed_status_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_NEXTHOP_GROUP_H
