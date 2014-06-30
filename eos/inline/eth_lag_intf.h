// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_ETH_LAG_INTF_H
#define EOS_INLINE_ETH_LAG_INTF_H

namespace eos {

inline eth_lag_intf_membership_t::eth_lag_intf_membership_t() :
                       eth_lag_intf_id(intf_id_t()),
                       active(false), reason(""),
                       memberTime(0), mode(ETH_LAG_INTF_MEMBER_LACP_MODE_NULL) {
}

inline eth_lag_intf_t::eth_lag_intf_t() : intf_(intf_id_t()),
                       min_links_(0),
                       fallback_type_(ETH_LAG_INTF_FALLBACK_NONE),
                       fallback_timeout_(90) {
}

inline eth_lag_intf_t::eth_lag_intf_t(intf_id_t id) : intf_(id),
                       min_links_(0),
                       fallback_type_(ETH_LAG_INTF_FALLBACK_NONE),
                       fallback_timeout_(90) {
}

inline bool eth_lag_intf_t::operator==(eth_lag_intf_t const & other) const {
   return intf_==other.intf_;
}

inline bool eth_lag_intf_t::operator!=(eth_lag_intf_t const & other) const {
   return !(intf_==other.intf_);
}

inline double eth_lag_intf_t::speed() const {
   return speed_;
}

inline  void eth_lag_intf_t::speed_is(double s) {
   speed_ = s;
}

inline void eth_lag_intf_t::min_links_is( uint32_t min_links) {
   min_links_ = min_links;
}

inline uint32_t eth_lag_intf_t::min_links() const {
   return min_links_;
}

inline void eth_lag_intf_t::fallback_type_is( eth_lag_intf_fallback_type_t type) {
   fallback_type_ = type;
}

inline eth_lag_intf_fallback_type_t eth_lag_intf_t::fallback_type() const {
   return fallback_type_;
}

inline uint16_t eth_lag_intf_t::fallback_timeout_default() const {
   return ETH_LAG_INTF_FALLBACK_TIMEOUT_DEFAULT;
}

inline void eth_lag_intf_t::fallback_timeout_is( uint16_t timeout) {
   fallback_timeout_ = timeout;
}

inline uint16_t eth_lag_intf_t::fallback_timeout() const {
   return fallback_timeout_;
}

inline void eth_lag_intf_t::eth_lag_intf_id_is(intf_id_t eth_lag_intf_id) {
   intf_ = eth_lag_intf_id;
}

inline intf_id_t eth_lag_intf_t::eth_lag_intf_id() const {
   return intf_;
}

}

#endif // EOS_INLINE_ETH_LAG_INTF_H
