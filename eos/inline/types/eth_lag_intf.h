// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ETH_LAG_INTF_H
#define EOS_INLINE_TYPES_ETH_LAG_INTF_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const eth_lag_intf_fallback_type_t & enum_val) {
   if (enum_val==ETH_LAG_INTF_FALLBACK_NULL) {
      os << "ETH_LAG_INTF_FALLBACK_NULL";
   } else if (enum_val==ETH_LAG_INTF_FALLBACK_NONE) {
      os << "ETH_LAG_INTF_FALLBACK_NONE";
   } else if (enum_val==ETH_LAG_INTF_FALLBACK_STATIC) {
      os << "ETH_LAG_INTF_FALLBACK_STATIC";
   } else if (enum_val==ETH_LAG_INTF_FALLBACK_INDIVIDUAL) {
      os << "ETH_LAG_INTF_FALLBACK_INDIVIDUAL";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline std::ostream&
operator<<(std::ostream& os,
           const eth_lag_intf_fallback_timeout_default_t & enum_val) {
   if (enum_val==ETH_LAG_INTF_FALLBACK_TIMEOUT_DEFAULT) {
      os << "ETH_LAG_INTF_FALLBACK_TIMEOUT_DEFAULT";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const eth_lag_intf_member_priority_t & enum_val) {
   if (enum_val==ETH_LAG_INTF_PORT_PRIORITY_DEFAULT) {
      os << "ETH_LAG_INTF_PORT_PRIORITY_DEFAULT";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const eth_lag_intf_member_lacp_mode_t & enum_val) {
   if (enum_val==ETH_LAG_INTF_MEMBER_LACP_MODE_NULL) {
      os << "ETH_LAG_INTF_MEMBER_LACP_MODE_NULL";
   } else if (enum_val==ETH_LAG_INTF_MEMBER_LACP_MODE_OFF) {
      os << "ETH_LAG_INTF_MEMBER_LACP_MODE_OFF";
   } else if (enum_val==ETH_LAG_INTF_MEMBER_LACP_MODE_PASSIVE) {
      os << "ETH_LAG_INTF_MEMBER_LACP_MODE_PASSIVE";
   } else if (enum_val==ETH_LAG_INTF_MEMBER_LACP_MODE_ACTIVE) {
      os << "ETH_LAG_INTF_MEMBER_LACP_MODE_ACTIVE";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const eth_lag_intf_member_lacp_timeout_t & enum_val) {
   if (enum_val==ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_NULL) {
      os << "ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_NULL";
   } else if (enum_val==ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_SHORT) {
      os << "ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_SHORT";
   } else if (enum_val==ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_LONG) {
      os << "ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_LONG";
   } else {
      os << "Unknown value";
   }
   return os;
}



// Default constructor.
inline eth_lag_intf_membership_t::eth_lag_intf_membership_t() :
      eth_lag_intf_id_(intf_id_t()), active_(false), reason_(""), member_time_(0),
      mode_(ETH_LAG_INTF_MEMBER_LACP_MODE_NULL) {
}

inline eth_lag_intf_membership_t::eth_lag_intf_membership_t(
         intf_id_t eth_lag_intf_id, bool active, std::string const & reason,
         double member_time, eth_lag_intf_member_lacp_mode_t mode) :
      eth_lag_intf_id_(eth_lag_intf_id), active_(active), reason_(reason),
      member_time_(member_time), mode_(mode) {
}

inline intf_id_t
eth_lag_intf_membership_t::eth_lag_intf_id() const {
   return eth_lag_intf_id_;
}

inline void
eth_lag_intf_membership_t::eth_lag_intf_id_is(intf_id_t eth_lag_intf_id) {
   eth_lag_intf_id_ = eth_lag_intf_id;
}

inline bool
eth_lag_intf_membership_t::active() const {
   return active_;
}

inline std::string
eth_lag_intf_membership_t::reason() const {
   return reason_;
}

inline void
eth_lag_intf_membership_t::reason_is(std::string const & reason) {
   reason_ = reason;
}

inline double
eth_lag_intf_membership_t::member_time() const {
   return member_time_;
}

inline eth_lag_intf_member_lacp_mode_t
eth_lag_intf_membership_t::mode() const {
   return mode_;
}

inline bool
eth_lag_intf_membership_t::operator==(eth_lag_intf_membership_t const & other)
       const {
   return eth_lag_intf_id_ == other.eth_lag_intf_id_ &&
          active_ == other.active_ &&
          reason_ == other.reason_ &&
          member_time_ == other.member_time_ &&
          mode_ == other.mode_;
}

inline bool
eth_lag_intf_membership_t::operator!=(eth_lag_intf_membership_t const & other)
       const {
   return !operator==(other);
}

inline bool
eth_lag_intf_membership_t::operator<(eth_lag_intf_membership_t const & other)
       const {
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

inline uint32_t
eth_lag_intf_membership_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
eth_lag_intf_membership_t::mix_me(hash_mix & h) const {
   h.mix(eth_lag_intf_id_); // intf_id_t
   h.mix(active_); // bool
   h.mix(reason_); // std::string
   h.mix(member_time_); // double
   h.mix(mode_); // eth_lag_intf_member_lacp_mode_t
}

inline std::string
eth_lag_intf_membership_t::to_string() const {
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

inline std::ostream&
operator<<(std::ostream& os, const eth_lag_intf_membership_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
inline eth_lag_intf_t::eth_lag_intf_t() :
      intf_(intf_id_t()), speed_(0), min_links_(0),
      fallback_type_(ETH_LAG_INTF_FALLBACK_NONE), fallback_timeout_(90) {
}

inline eth_lag_intf_t::eth_lag_intf_t(intf_id_t intf) :
      intf_(intf), speed_(0), min_links_(0),
      fallback_type_(ETH_LAG_INTF_FALLBACK_NONE), fallback_timeout_(90) {
}

inline eth_lag_intf_t::eth_lag_intf_t(intf_id_t intf, uint32_t min_links,
                                      uint64_t speed,
                                      eth_lag_intf_fallback_type_t fallback_type,
                                      uint16_t fallback_timeout) :
      intf_(intf), speed_(speed), min_links_(min_links),
      fallback_type_(fallback_type), fallback_timeout_(fallback_timeout) {
}

inline intf_id_t
eth_lag_intf_t::intf() const {
   return intf_;
}

inline uint64_t
eth_lag_intf_t::speed() const {
   return speed_;
}

inline uint32_t
eth_lag_intf_t::min_links() const {
   return min_links_;
}

inline eth_lag_intf_fallback_type_t
eth_lag_intf_t::fallback_type() const {
   return fallback_type_;
}

inline uint16_t
eth_lag_intf_t::fallback_timeout() const {
   return fallback_timeout_;
}

inline uint16_t
eth_lag_intf_t::fallback_timeout_default() const {
   return ETH_LAG_INTF_FALLBACK_TIMEOUT_DEFAULT;
}

inline bool
eth_lag_intf_t::operator==(eth_lag_intf_t const & other) const {
   return intf_ == other.intf_ &&
          speed_ == other.speed_ &&
          min_links_ == other.min_links_ &&
          fallback_type_ == other.fallback_type_ &&
          fallback_timeout_ == other.fallback_timeout_;
}

inline bool
eth_lag_intf_t::operator!=(eth_lag_intf_t const & other) const {
   return !operator==(other);
}

inline bool
eth_lag_intf_t::operator<(eth_lag_intf_t const & other) const {
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

inline uint32_t
eth_lag_intf_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
eth_lag_intf_t::mix_me(hash_mix & h) const {
   h.mix(intf_); // intf_id_t
   h.mix(speed_); // uint64_t
   h.mix(min_links_); // uint32_t
   h.mix(fallback_type_); // eth_lag_intf_fallback_type_t
   h.mix(fallback_timeout_); // uint16_t
}

inline std::string
eth_lag_intf_t::to_string() const {
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

inline std::ostream&
operator<<(std::ostream& os, const eth_lag_intf_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_ETH_LAG_INTF_H
