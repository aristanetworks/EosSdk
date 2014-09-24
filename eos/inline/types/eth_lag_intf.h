// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
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
operator<<(std::ostream& os, 
           const eth_lag_intf_member_lacp_timeout_t & enum_val) {
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

inline void
eth_lag_intf_membership_t::active_is(bool active) {
   active_ = active;
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

inline void
eth_lag_intf_membership_t::member_time_is(double member_time) {
   member_time_ = member_time;
}

inline eth_lag_intf_member_lacp_mode_t
eth_lag_intf_membership_t::mode() const {
   return mode_;
}

inline void
eth_lag_intf_membership_t::mode_is(eth_lag_intf_member_lacp_mode_t mode) {
   mode_ = mode;
}

inline std::string
eth_lag_intf_membership_t::to_string() const {
   std::ostringstream ss;
   ss << "eth_lag_intf_membership_t(";
   ss << "eth_lag_intf_id=" << eth_lag_intf_id_.to_string();
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

inline intf_id_t
eth_lag_intf_t::intf() const {
   return intf_;
}

inline void
eth_lag_intf_t::intf_is(intf_id_t intf) {
   intf_ = intf;
}

inline double
eth_lag_intf_t::speed() const {
   return speed_;
}

inline void
eth_lag_intf_t::speed_is(double speed) {
   speed_ = speed;
}

inline uint32_t
eth_lag_intf_t::min_links() const {
   return min_links_;
}

inline void
eth_lag_intf_t::min_links_is(uint32_t min_links) {
   min_links_ = min_links;
}

inline eth_lag_intf_fallback_type_t
eth_lag_intf_t::fallback_type() const {
   return fallback_type_;
}

inline void
eth_lag_intf_t::fallback_type_is(eth_lag_intf_fallback_type_t fallback_type) {
   fallback_type_ = fallback_type;
}

inline uint16_t
eth_lag_intf_t::fallback_timeout() const {
   return fallback_timeout_;
}

inline void
eth_lag_intf_t::fallback_timeout_is(uint16_t fallback_timeout) {
   fallback_timeout_ = fallback_timeout;
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

inline uint32_t
eth_lag_intf_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&intf_,
              sizeof(intf_id_t), ret);
   ret = hash_mix::mix((uint8_t *)&speed_,
              sizeof(double), ret);
   ret = hash_mix::mix((uint8_t *)&min_links_,
              sizeof(uint32_t), ret);
   ret = hash_mix::mix((uint8_t *)&fallback_type_,
              sizeof(eth_lag_intf_fallback_type_t), ret);
   ret = hash_mix::mix((uint8_t *)&fallback_timeout_,
              sizeof(uint16_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
eth_lag_intf_t::to_string() const {
   std::ostringstream ss;
   ss << "eth_lag_intf_t(";
   ss << "intf=" << intf_.to_string();
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
