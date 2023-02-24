// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ETH_LAG_INTF_IMPL_H
#define EOS_INLINE_TYPES_ETH_LAG_INTF_IMPL_H

namespace eos {











// Default constructor.
eth_lag_intf_membership_impl_t::eth_lag_intf_membership_impl_t() :
      eth_lag_intf_id_(intf_id_t()), active_(false), reason_(""), member_time_(0),
      mode_(ETH_LAG_INTF_MEMBER_LACP_MODE_NULL) {
}

eth_lag_intf_membership_impl_t::eth_lag_intf_membership_impl_t(
         intf_id_t eth_lag_intf_id, bool active, std::string const & reason,
         double member_time, eth_lag_intf_member_lacp_mode_t mode) :
      eth_lag_intf_id_(eth_lag_intf_id), active_(active), reason_(reason),
      member_time_(member_time), mode_(mode) {
}

intf_id_t
eth_lag_intf_membership_impl_t::eth_lag_intf_id() const {
   return eth_lag_intf_id_;
}

void
eth_lag_intf_membership_impl_t::eth_lag_intf_id_is(intf_id_t eth_lag_intf_id) {
   eth_lag_intf_id_ = eth_lag_intf_id;
}

bool
eth_lag_intf_membership_impl_t::active() const {
   return active_;
}

std::string
eth_lag_intf_membership_impl_t::reason() const {
   return reason_;
}

void
eth_lag_intf_membership_impl_t::reason_is(std::string const & reason) {
   reason_ = reason;
}

double
eth_lag_intf_membership_impl_t::member_time() const {
   return member_time_;
}

eth_lag_intf_member_lacp_mode_t
eth_lag_intf_membership_impl_t::mode() const {
   return mode_;
}

bool
eth_lag_intf_membership_impl_t::operator==(
         eth_lag_intf_membership_impl_t const & other) const {
   return eth_lag_intf_id_ == other.eth_lag_intf_id_ &&
          active_ == other.active_ &&
          reason_ == other.reason_ &&
          member_time_ == other.member_time_ &&
          mode_ == other.mode_;
}

bool
eth_lag_intf_membership_impl_t::operator!=(
         eth_lag_intf_membership_impl_t const & other) const {
   return !operator==(other);
}

bool
eth_lag_intf_membership_impl_t::operator<(
         eth_lag_intf_membership_impl_t const & other) const {
   if(eth_lag_intf_id_ != other.eth_lag_intf_id_) {
      return eth_lag_intf_id_ < other.eth_lag_intf_id_;
   } else if(active_ != other.active_) {
      return active_ < other.active_;
   } else if(reason_ != other.reason_) {
      return reason_ < other.reason_;
   } else if(member_time_ != other.member_time_) {
      return member_time_ < other.member_time_;
   } else if(mode_ != other.mode_) {
      return mode_ < other.mode_;
   }
   return false;
}

uint32_t
eth_lag_intf_membership_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
eth_lag_intf_membership_impl_t::mix_me(hash_mix & h) const {
   h.mix(eth_lag_intf_id_); // intf_id_t
   h.mix(active_); // bool
   h.mix(reason_); // std::string
   h.mix(member_time_); // double
   h.mix(mode_); // eth_lag_intf_member_lacp_mode_t
}

std::string
eth_lag_intf_membership_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "eth_lag_intf_membership_t(";
   ss << "eth_lag_intf_id=" << eth_lag_intf_id_;
   ss << ", active=" << active_;
   ss << ", reason='" << reason_ << "'";
   ss << ", member_time=" << member_time_;
   ss << ", mode=" << mode_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const eth_lag_intf_membership_impl_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
eth_lag_intf_impl_t::eth_lag_intf_impl_t() :
      intf_(intf_id_t()), speed_(0), min_links_(0),
      fallback_type_(ETH_LAG_INTF_FALLBACK_NONE), fallback_timeout_(90) {
}

eth_lag_intf_impl_t::eth_lag_intf_impl_t(intf_id_t intf) :
      intf_(intf), speed_(0), min_links_(0),
      fallback_type_(ETH_LAG_INTF_FALLBACK_NONE), fallback_timeout_(90) {
}

eth_lag_intf_impl_t::eth_lag_intf_impl_t(
         intf_id_t intf, uint32_t min_links, uint64_t speed,
         eth_lag_intf_fallback_type_t fallback_type, uint16_t fallback_timeout) :
      intf_(intf), speed_(speed), min_links_(min_links),
      fallback_type_(fallback_type), fallback_timeout_(fallback_timeout) {
}

intf_id_t
eth_lag_intf_impl_t::intf() const {
   return intf_;
}

uint64_t
eth_lag_intf_impl_t::speed() const {
   return speed_;
}

uint32_t
eth_lag_intf_impl_t::min_links() const {
   return min_links_;
}

eth_lag_intf_fallback_type_t
eth_lag_intf_impl_t::fallback_type() const {
   return fallback_type_;
}

uint16_t
eth_lag_intf_impl_t::fallback_timeout() const {
   return fallback_timeout_;
}

uint16_t
eth_lag_intf_impl_t::fallback_timeout_default() const {
   return ETH_LAG_INTF_FALLBACK_TIMEOUT_DEFAULT;
}

bool
eth_lag_intf_impl_t::operator==(eth_lag_intf_impl_t const & other) const {
   return intf_ == other.intf_ &&
          speed_ == other.speed_ &&
          min_links_ == other.min_links_ &&
          fallback_type_ == other.fallback_type_ &&
          fallback_timeout_ == other.fallback_timeout_;
}

bool
eth_lag_intf_impl_t::operator!=(eth_lag_intf_impl_t const & other) const {
   return !operator==(other);
}

bool
eth_lag_intf_impl_t::operator<(eth_lag_intf_impl_t const & other) const {
   if(intf_ != other.intf_) {
      return intf_ < other.intf_;
   } else if(speed_ != other.speed_) {
      return speed_ < other.speed_;
   } else if(min_links_ != other.min_links_) {
      return min_links_ < other.min_links_;
   } else if(fallback_type_ != other.fallback_type_) {
      return fallback_type_ < other.fallback_type_;
   } else if(fallback_timeout_ != other.fallback_timeout_) {
      return fallback_timeout_ < other.fallback_timeout_;
   }
   return false;
}

uint32_t
eth_lag_intf_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
eth_lag_intf_impl_t::mix_me(hash_mix & h) const {
   h.mix(intf_); // intf_id_t
   h.mix(speed_); // uint64_t
   h.mix(min_links_); // uint32_t
   h.mix(fallback_type_); // eth_lag_intf_fallback_type_t
   h.mix(fallback_timeout_); // uint16_t
}

std::string
eth_lag_intf_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "eth_lag_intf_t(";
   ss << "intf=" << intf_;
   ss << ", speed=" << speed_;
   ss << ", min_links=" << min_links_;
   ss << ", fallback_type=" << fallback_type_;
   ss << ", fallback_timeout=" << fallback_timeout_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const eth_lag_intf_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/eth_lag_intf.h>

#endif // EOS_INLINE_TYPES_ETH_LAG_INTF_IMPL_H
