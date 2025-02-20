// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_BFD_H
#define EOS_INLINE_TYPES_BFD_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const bfd_session_status_t & enum_val) {
   if (enum_val==BFD_SESSION_STATUS_NULL) {
      os << "BFD_SESSION_STATUS_NULL";
   } else if (enum_val==BFD_SESSION_STATUS_DOWN) {
      os << "BFD_SESSION_STATUS_DOWN";
   } else if (enum_val==BFD_SESSION_STATUS_INIT) {
      os << "BFD_SESSION_STATUS_INIT";
   } else if (enum_val==BFD_SESSION_STATUS_UP) {
      os << "BFD_SESSION_STATUS_UP";
   } else if (enum_val==BFD_SESSION_STATUS_ADMIN_DOWN) {
      os << "BFD_SESSION_STATUS_ADMIN_DOWN";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const bfd_session_type_t & enum_val) {
   if (enum_val==BFD_SESSION_TYPE_NULL) {
      os << "BFD_SESSION_TYPE_NULL";
   } else if (enum_val==BFD_SESSION_TYPE_NORMAL) {
      os << "BFD_SESSION_TYPE_NORMAL";
   } else if (enum_val==BFD_SESSION_TYPE_MICRO) {
      os << "BFD_SESSION_TYPE_MICRO";
   } else if (enum_val==BFD_SESSION_TYPE_VXLANTUNNEL) {
      os << "BFD_SESSION_TYPE_VXLANTUNNEL";
   } else if (enum_val==BFD_SESSION_TYPE_LAGRFC7130) {
      os << "BFD_SESSION_TYPE_LAGRFC7130";
   } else if (enum_val==BFD_SESSION_TYPE_MICRORFC7130) {
      os << "BFD_SESSION_TYPE_MICRORFC7130";
   } else if (enum_val==BFD_SESSION_TYPE_MULTIHOP) {
      os << "BFD_SESSION_TYPE_MULTIHOP";
   } else if (enum_val==BFD_SESSION_TYPE_SBFD_INITIATOR) {
      os << "BFD_SESSION_TYPE_SBFD_INITIATOR";
   } else if (enum_val==BFD_SESSION_TYPE_SBFD_REFLECTOR) {
      os << "BFD_SESSION_TYPE_SBFD_REFLECTOR";
   } else {
      os << "Unknown value";
   }
   return os;
}


ip_addr_t
bfd_session_key_t::ip_addr() const {
   return pimpl->ip_addr();
}
std::string
bfd_session_key_t::vrf() const {
   return pimpl->vrf();
}
bfd_session_type_t
bfd_session_key_t::type() const {
   return pimpl->type();
}
intf_id_t
bfd_session_key_t::intf() const {
   return pimpl->intf();
}
ip_addr_t
bfd_session_key_t::src_ip_addr() const {
   return pimpl->src_ip_addr();
}
uint64_t
bfd_session_key_t::tunnel_id() const {
   return pimpl->tunnel_id();
}
bool
bfd_session_key_t::operator==(bfd_session_key_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
bfd_session_key_t::operator!=(bfd_session_key_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
bfd_session_key_t::operator<(bfd_session_key_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
bfd_session_key_t::hash() const {
   return pimpl->hash();
}
void
bfd_session_key_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
bfd_session_key_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const bfd_session_key_t& obj) {
   return operator<<(os, *obj.pimpl);
}


uint16_t
bfd_interval_t::tx() const {
   return pimpl->tx();
}
uint16_t
bfd_interval_t::rx() const {
   return pimpl->rx();
}
uint8_t
bfd_interval_t::mult() const {
   return pimpl->mult();
}
bool
bfd_interval_t::operator==(bfd_interval_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
bfd_interval_t::operator!=(bfd_interval_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
bfd_interval_t::hash() const {
   return pimpl->hash();
}
void
bfd_interval_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
bfd_interval_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const bfd_interval_t& obj) {
   return operator<<(os, *obj.pimpl);
}


bfd_session_key_t
bfd_session_t::peer() const {
   return pimpl->peer();
}
bfd_session_status_t
bfd_session_t::status() const {
   return pimpl->status();
}
bool
bfd_session_t::operator==(bfd_session_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
bfd_session_t::operator!=(bfd_session_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
bfd_session_t::operator<(bfd_session_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
bfd_session_t::hash() const {
   return pimpl->hash();
}
void
bfd_session_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
bfd_session_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const bfd_session_t& obj) {
   return operator<<(os, *obj.pimpl);
}


ip_addr_t
sbfd_echo_session_key_t::nexthop() const {
   return pimpl->nexthop();
}
intf_id_t
sbfd_echo_session_key_t::nexthop_intf() const {
   return pimpl->nexthop_intf();
}
std::forward_list<mpls_label_t> const &
sbfd_echo_session_key_t::labels() const {
   return pimpl->labels();
}
uint8_t
sbfd_echo_session_key_t::ip_dscp() const {
   return pimpl->ip_dscp();
}
uint8_t
sbfd_echo_session_key_t::mpls_exp() const {
   return pimpl->mpls_exp();
}
bool
sbfd_echo_session_key_t::operator==(sbfd_echo_session_key_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
sbfd_echo_session_key_t::operator!=(sbfd_echo_session_key_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
sbfd_echo_session_key_t::operator<(sbfd_echo_session_key_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
sbfd_echo_session_key_t::hash() const {
   return pimpl->hash();
}
void
sbfd_echo_session_key_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
sbfd_echo_session_key_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const sbfd_echo_session_key_t& obj) {
   return operator<<(os, *obj.pimpl);
}


uint16_t
sbfd_interval_t::tx() const {
   return pimpl->tx();
}
uint8_t
sbfd_interval_t::mult() const {
   return pimpl->mult();
}
bool
sbfd_interval_t::operator==(sbfd_interval_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
sbfd_interval_t::operator!=(sbfd_interval_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
sbfd_interval_t::hash() const {
   return pimpl->hash();
}
void
sbfd_interval_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
sbfd_interval_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const sbfd_interval_t& obj) {
   return operator<<(os, *obj.pimpl);
}


uint32_t
sbfd_echo_session_rtt_stats_t::last_rtt() const {
   return pimpl->last_rtt();
}
uint32_t
sbfd_echo_session_rtt_stats_t::min_rtt() const {
   return pimpl->min_rtt();
}
uint32_t
sbfd_echo_session_rtt_stats_t::avg_rtt() const {
   return pimpl->avg_rtt();
}
uint32_t
sbfd_echo_session_rtt_stats_t::max_rtt() const {
   return pimpl->max_rtt();
}
uint32_t
sbfd_echo_session_rtt_stats_t::snapshot_min_rtt() const {
   return pimpl->snapshot_min_rtt();
}
uint32_t
sbfd_echo_session_rtt_stats_t::snapshot_avg_rtt() const {
   return pimpl->snapshot_avg_rtt();
}
uint32_t
sbfd_echo_session_rtt_stats_t::snapshot_max_rtt() const {
   return pimpl->snapshot_max_rtt();
}
bool
sbfd_echo_session_rtt_stats_t::operator==(
         sbfd_echo_session_rtt_stats_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
sbfd_echo_session_rtt_stats_t::operator!=(
         sbfd_echo_session_rtt_stats_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
sbfd_echo_session_rtt_stats_t::hash() const {
   return pimpl->hash();
}
void
sbfd_echo_session_rtt_stats_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
sbfd_echo_session_rtt_stats_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const sbfd_echo_session_rtt_stats_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_BFD_H
