// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_BFD_IMPL_H
#define EOS_INLINE_TYPES_BFD_IMPL_H

namespace eos {





// Default constructor.
bfd_session_key_impl_t::bfd_session_key_impl_t() :
      ip_addr_(), vrf_(), type_(), intf_(),
      src_ip_addr_(eos::ip_addr_t("0.0.0.0")), tunnel_id_() {
}

bfd_session_key_impl_t::bfd_session_key_impl_t(ip_addr_t ip_addr,
                                                      std::string vrf,
                                                      bfd_session_type_t type,
                                                      intf_id_t intf) :
      ip_addr_(ip_addr), vrf_(vrf), type_(type), intf_(intf),
      src_ip_addr_(eos::ip_addr_t("0.0.0.0")), tunnel_id_() {
}

bfd_session_key_impl_t::bfd_session_key_impl_t(ip_addr_t ip_addr,
                                                      std::string vrf,
                                                      bfd_session_type_t type,
                                                      intf_id_t intf,
                                                      ip_addr_t src_ip_addr) :
      ip_addr_(ip_addr), vrf_(vrf), type_(type), intf_(intf),
      src_ip_addr_(src_ip_addr), tunnel_id_() {
}

// Sbfd session constructor.
bfd_session_key_impl_t::bfd_session_key_impl_t(ip_addr_t ip_addr,
                                                      std::string vrf,
                                                      bfd_session_type_t type,
                                                      uint64_t tunnel_id) :
      ip_addr_(ip_addr), vrf_(vrf), type_(type), intf_(),
      src_ip_addr_(eos::ip_addr_t("0.0.0.0")), tunnel_id_(tunnel_id) {
}

// Constructor with complete argument list.
bfd_session_key_impl_t::bfd_session_key_impl_t(ip_addr_t ip_addr,
                                                      std::string vrf,
                                                      bfd_session_type_t type,
                                                      intf_id_t intf,
                                                      ip_addr_t src_ip_addr,
                                                      uint64_t tunnel_id) :
      ip_addr_(ip_addr), vrf_(vrf), type_(type), intf_(intf),
      src_ip_addr_(src_ip_addr), tunnel_id_(tunnel_id) {
}

ip_addr_t
bfd_session_key_impl_t::ip_addr() const {
   return ip_addr_;
}

std::string
bfd_session_key_impl_t::vrf() const {
   return vrf_;
}

bfd_session_type_t
bfd_session_key_impl_t::type() const {
   return type_;
}

intf_id_t
bfd_session_key_impl_t::intf() const {
   return intf_;
}

ip_addr_t
bfd_session_key_impl_t::src_ip_addr() const {
   return src_ip_addr_;
}

uint64_t
bfd_session_key_impl_t::tunnel_id() const {
   return tunnel_id_;
}

bool
bfd_session_key_impl_t::operator==(bfd_session_key_impl_t const & other) const {
   return ip_addr_ == other.ip_addr_ &&
          vrf_ == other.vrf_ &&
          type_ == other.type_ &&
          intf_ == other.intf_ &&
          src_ip_addr_ == other.src_ip_addr_ &&
          tunnel_id_ == other.tunnel_id_;
}

bool
bfd_session_key_impl_t::operator!=(bfd_session_key_impl_t const & other) const {
   return !operator==(other);
}

bool
bfd_session_key_impl_t::operator<(bfd_session_key_impl_t const & other) const {
   if(ip_addr_ != other.ip_addr_) {
      return ip_addr_ < other.ip_addr_;
   } else if(vrf_ != other.vrf_) {
      return vrf_ < other.vrf_;
   } else if(type_ != other.type_) {
      return type_ < other.type_;
   } else if(intf_ != other.intf_) {
      return intf_ < other.intf_;
   } else if(src_ip_addr_ != other.src_ip_addr_) {
      return src_ip_addr_ < other.src_ip_addr_;
   } else if(tunnel_id_ != other.tunnel_id_) {
      return tunnel_id_ < other.tunnel_id_;
   }
   return false;
}

uint32_t
bfd_session_key_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
bfd_session_key_impl_t::mix_me(hash_mix & h) const {
   h.mix(ip_addr_); // ip_addr_t
   h.mix(vrf_); // std::string
   h.mix(type_); // bfd_session_type_t
   h.mix(intf_); // intf_id_t
   h.mix(src_ip_addr_); // ip_addr_t
   h.mix(tunnel_id_); // uint64_t
}

std::string
bfd_session_key_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "bfd_session_key_t(";
   ss << "ip_addr=" << ip_addr_;
   ss << ", vrf='" << vrf_ << "'";
   ss << ", type=" << type_;
   ss << ", intf=" << intf_;
   ss << ", src_ip_addr=" << src_ip_addr_;
   ss << ", tunnel_id=" << tunnel_id_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const bfd_session_key_impl_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
bfd_interval_impl_t::bfd_interval_impl_t() :
      tx_(300), rx_(300), mult_(3) {
}

bfd_interval_impl_t::bfd_interval_impl_t(uint16_t tx, uint16_t rx,
                                                uint8_t mult) :
      tx_(tx), rx_(rx), mult_(mult) {
}

uint16_t
bfd_interval_impl_t::tx() const {
   return tx_;
}

uint16_t
bfd_interval_impl_t::rx() const {
   return rx_;
}

uint8_t
bfd_interval_impl_t::mult() const {
   return mult_;
}

bool
bfd_interval_impl_t::operator==(bfd_interval_impl_t const & other) const {
   return tx_ == other.tx_ &&
          rx_ == other.rx_ &&
          mult_ == other.mult_;
}

bool
bfd_interval_impl_t::operator!=(bfd_interval_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
bfd_interval_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
bfd_interval_impl_t::mix_me(hash_mix & h) const {
   h.mix(tx_); // uint16_t
   h.mix(rx_); // uint16_t
   h.mix(mult_); // uint8_t
}

std::string
bfd_interval_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "bfd_interval_t(";
   ss << "tx=" << tx_;
   ss << ", rx=" << rx_;
   ss << ", mult=" << mult_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const bfd_interval_impl_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
bfd_session_impl_t::bfd_session_impl_t() :
      peer_(), status_(BFD_SESSION_STATUS_NULL) {
}

bfd_session_impl_t::bfd_session_impl_t(bfd_session_key_t peer,
                                              bfd_session_status_t status) :
      peer_(peer), status_(status) {
}

bfd_session_key_t
bfd_session_impl_t::peer() const {
   return peer_;
}

bfd_session_status_t
bfd_session_impl_t::status() const {
   return status_;
}

bool
bfd_session_impl_t::operator==(bfd_session_impl_t const & other) const {
   return peer_ == other.peer_ &&
          status_ == other.status_;
}

bool
bfd_session_impl_t::operator!=(bfd_session_impl_t const & other) const {
   return !operator==(other);
}

bool
bfd_session_impl_t::operator<(bfd_session_impl_t const & other) const {
   if(peer_ != other.peer_) {
      return peer_ < other.peer_;
   } else if(status_ != other.status_) {
      return status_ < other.status_;
   }
   return false;
}

uint32_t
bfd_session_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
bfd_session_impl_t::mix_me(hash_mix & h) const {
   h.mix(peer_); // bfd_session_key_t
   h.mix(status_); // bfd_session_status_t
}

std::string
bfd_session_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "bfd_session_t(";
   ss << "peer=" << peer_;
   ss << ", status=" << status_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const bfd_session_impl_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
sbfd_echo_session_key_impl_t::sbfd_echo_session_key_impl_t() :
      nexthop_(), nexthop_intf_(), labels_(), ip_dscp_(), mpls_exp_() {
}

sbfd_echo_session_key_impl_t::sbfd_echo_session_key_impl_t(
         ip_addr_t nexthop, intf_id_t nexthop_intf,
         std::forward_list<mpls_label_t> const & labels, uint8_t ip_dscp,
         uint8_t mpls_exp) :
      nexthop_(nexthop), nexthop_intf_(nexthop_intf), labels_(labels),
      ip_dscp_(ip_dscp), mpls_exp_(mpls_exp) {
}

sbfd_echo_session_key_impl_t::sbfd_echo_session_key_impl_t(
         ip_addr_t nexthop, intf_id_t nexthop_intf,
         std::forward_list<mpls_label_t> const & labels) :
      nexthop_(nexthop), nexthop_intf_(nexthop_intf), labels_(labels),
      ip_dscp_(0xc0 /* CS6 */), mpls_exp_(6) {
}

ip_addr_t
sbfd_echo_session_key_impl_t::nexthop() const {
   return nexthop_;
}

intf_id_t
sbfd_echo_session_key_impl_t::nexthop_intf() const {
   return nexthop_intf_;
}

std::forward_list<mpls_label_t> const &
sbfd_echo_session_key_impl_t::labels() const {
   return labels_;
}

uint8_t
sbfd_echo_session_key_impl_t::ip_dscp() const {
   return ip_dscp_;
}

uint8_t
sbfd_echo_session_key_impl_t::mpls_exp() const {
   return mpls_exp_;
}

bool
sbfd_echo_session_key_impl_t::operator==(
         sbfd_echo_session_key_impl_t const & other) const {
   return nexthop_ == other.nexthop_ &&
          nexthop_intf_ == other.nexthop_intf_ &&
          labels_ == other.labels_ &&
          ip_dscp_ == other.ip_dscp_ &&
          mpls_exp_ == other.mpls_exp_;
}

bool
sbfd_echo_session_key_impl_t::operator!=(
         sbfd_echo_session_key_impl_t const & other) const {
   return !operator==(other);
}

bool
sbfd_echo_session_key_impl_t::operator<(sbfd_echo_session_key_impl_t const & other)
       const {
   if(nexthop_ != other.nexthop_) {
      return nexthop_ < other.nexthop_;
   } else if(nexthop_intf_ != other.nexthop_intf_) {
      return nexthop_intf_ < other.nexthop_intf_;
   } else if(labels_ != other.labels_) {
      return labels_ < other.labels_;
   } else if(ip_dscp_ != other.ip_dscp_) {
      return ip_dscp_ < other.ip_dscp_;
   } else if(mpls_exp_ != other.mpls_exp_) {
      return mpls_exp_ < other.mpls_exp_;
   }
   return false;
}

uint32_t
sbfd_echo_session_key_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
sbfd_echo_session_key_impl_t::mix_me(hash_mix & h) const {
   h.mix(nexthop_); // ip_addr_t
   h.mix(nexthop_intf_); // intf_id_t
   for (auto it=labels_.cbegin();
        it!=labels_.cend(); ++it) {
      h.mix(*it); // mpls_label_t
   }
   h.mix(ip_dscp_); // uint8_t
   h.mix(mpls_exp_); // uint8_t
}

std::string
sbfd_echo_session_key_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "sbfd_echo_session_key_t(";
   ss << "nexthop=" << nexthop_;
   ss << ", nexthop_intf=" << nexthop_intf_;
   ss << ", labels=" <<"'";
   bool first_labels = true;
   for (auto it=labels_.cbegin();
        it!=labels_.cend(); ++it) {
      if (first_labels) {
         ss << (*it);
         first_labels = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", ip_dscp=" << ip_dscp_;
   ss << ", mpls_exp=" << mpls_exp_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const sbfd_echo_session_key_impl_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
sbfd_interval_impl_t::sbfd_interval_impl_t() :
      tx_(300), mult_(3) {
}

sbfd_interval_impl_t::sbfd_interval_impl_t(uint16_t tx, uint8_t mult) :
      tx_(tx), mult_(mult) {
}

uint16_t
sbfd_interval_impl_t::tx() const {
   return tx_;
}

uint8_t
sbfd_interval_impl_t::mult() const {
   return mult_;
}

bool
sbfd_interval_impl_t::operator==(sbfd_interval_impl_t const & other) const {
   return tx_ == other.tx_ &&
          mult_ == other.mult_;
}

bool
sbfd_interval_impl_t::operator!=(sbfd_interval_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
sbfd_interval_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
sbfd_interval_impl_t::mix_me(hash_mix & h) const {
   h.mix(tx_); // uint16_t
   h.mix(mult_); // uint8_t
}

std::string
sbfd_interval_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "sbfd_interval_t(";
   ss << "tx=" << tx_;
   ss << ", mult=" << mult_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const sbfd_interval_impl_t& obj) {
   os << obj.to_string();
   return os;
}



sbfd_echo_session_rtt_stats_impl_t::sbfd_echo_session_rtt_stats_impl_t(
         uint32_t last_rtt, uint32_t min_rtt, uint32_t avg_rtt, uint32_t max_rtt,
         uint32_t snapshot_min_rtt, uint32_t snapshot_avg_rtt,
         uint32_t snapshot_max_rtt) :
      last_rtt_(last_rtt), min_rtt_(min_rtt), avg_rtt_(avg_rtt), max_rtt_(max_rtt),
      snapshot_min_rtt_(snapshot_min_rtt), snapshot_avg_rtt_(snapshot_avg_rtt),
      snapshot_max_rtt_(snapshot_max_rtt) {
}

uint32_t
sbfd_echo_session_rtt_stats_impl_t::last_rtt() const {
   return last_rtt_;
}

uint32_t
sbfd_echo_session_rtt_stats_impl_t::min_rtt() const {
   return min_rtt_;
}

uint32_t
sbfd_echo_session_rtt_stats_impl_t::avg_rtt() const {
   return avg_rtt_;
}

uint32_t
sbfd_echo_session_rtt_stats_impl_t::max_rtt() const {
   return max_rtt_;
}

uint32_t
sbfd_echo_session_rtt_stats_impl_t::snapshot_min_rtt() const {
   return snapshot_min_rtt_;
}

uint32_t
sbfd_echo_session_rtt_stats_impl_t::snapshot_avg_rtt() const {
   return snapshot_avg_rtt_;
}

uint32_t
sbfd_echo_session_rtt_stats_impl_t::snapshot_max_rtt() const {
   return snapshot_max_rtt_;
}

bool
sbfd_echo_session_rtt_stats_impl_t::operator==(
         sbfd_echo_session_rtt_stats_impl_t const & other) const {
   return last_rtt_ == other.last_rtt_ &&
          min_rtt_ == other.min_rtt_ &&
          avg_rtt_ == other.avg_rtt_ &&
          max_rtt_ == other.max_rtt_ &&
          snapshot_min_rtt_ == other.snapshot_min_rtt_ &&
          snapshot_avg_rtt_ == other.snapshot_avg_rtt_ &&
          snapshot_max_rtt_ == other.snapshot_max_rtt_;
}

bool
sbfd_echo_session_rtt_stats_impl_t::operator!=(
         sbfd_echo_session_rtt_stats_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
sbfd_echo_session_rtt_stats_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
sbfd_echo_session_rtt_stats_impl_t::mix_me(hash_mix & h) const {
   h.mix(last_rtt_); // uint32_t
   h.mix(min_rtt_); // uint32_t
   h.mix(avg_rtt_); // uint32_t
   h.mix(max_rtt_); // uint32_t
   h.mix(snapshot_min_rtt_); // uint32_t
   h.mix(snapshot_avg_rtt_); // uint32_t
   h.mix(snapshot_max_rtt_); // uint32_t
}

std::string
sbfd_echo_session_rtt_stats_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "sbfd_echo_session_rtt_stats_t(";
   ss << "last_rtt=" << last_rtt_;
   ss << ", min_rtt=" << min_rtt_;
   ss << ", avg_rtt=" << avg_rtt_;
   ss << ", max_rtt=" << max_rtt_;
   ss << ", snapshot_min_rtt=" << snapshot_min_rtt_;
   ss << ", snapshot_avg_rtt=" << snapshot_avg_rtt_;
   ss << ", snapshot_max_rtt=" << snapshot_max_rtt_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const sbfd_echo_session_rtt_stats_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/bfd.h>

#endif // EOS_INLINE_TYPES_BFD_IMPL_H
