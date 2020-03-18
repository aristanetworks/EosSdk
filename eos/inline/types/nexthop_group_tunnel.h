// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_NEXTHOP_GROUP_TUNNEL_H
#define EOS_INLINE_TYPES_NEXTHOP_GROUP_TUNNEL_H

namespace eos {

inline nexthop_group_tunnel_t::nexthop_group_tunnel_t() :
      tunnel_endpoint_(), nhg_name_(), igp_pref_(), igp_metric_() {
}

inline nexthop_group_tunnel_t::nexthop_group_tunnel_t(
         ip_prefix_t const & tunnel_endpoint, std::string const & nhg_name) :
      tunnel_endpoint_(tunnel_endpoint), nhg_name_(nhg_name), igp_pref_(),
      igp_metric_() {
}

inline ip_prefix_t
nexthop_group_tunnel_t::tunnel_endpoint() const {
   return tunnel_endpoint_;
}

inline void
nexthop_group_tunnel_t::tunnel_endpoint_is(ip_prefix_t const & tunnel_endpoint) {
   tunnel_endpoint_ = tunnel_endpoint;
}

inline std::string
nexthop_group_tunnel_t::nhg_name() const {
   return nhg_name_;
}

inline void
nexthop_group_tunnel_t::nhg_name_is(std::string const & nhg_name) {
   nhg_name_ = nhg_name;
}

inline uint8_t
nexthop_group_tunnel_t::igp_pref() const {
   return igp_pref_;
}

inline void
nexthop_group_tunnel_t::igp_pref_is(uint8_t igp_pref) {
   igp_pref_ = igp_pref;
}

inline uint32_t
nexthop_group_tunnel_t::igp_metric() const {
   return igp_metric_;
}

inline void
nexthop_group_tunnel_t::igp_metric_is(uint32_t igp_metric) {
   igp_metric_ = igp_metric;
}

inline bool
nexthop_group_tunnel_t::operator==(nexthop_group_tunnel_t const & other) const {
   return tunnel_endpoint_ == other.tunnel_endpoint_ &&
          nhg_name_ == other.nhg_name_ &&
          igp_pref_ == other.igp_pref_ &&
          igp_metric_ == other.igp_metric_;
}

inline bool
nexthop_group_tunnel_t::operator!=(nexthop_group_tunnel_t const & other) const {
   return !operator==(other);
}

inline uint32_t
nexthop_group_tunnel_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&tunnel_endpoint_,
              sizeof(ip_prefix_t), ret);
   ret ^= std::hash<std::string>()(nhg_name_);
   ret = hash_mix::mix((uint8_t *)&igp_pref_,
              sizeof(uint8_t), ret);
   ret = hash_mix::mix((uint8_t *)&igp_metric_,
              sizeof(uint32_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
nexthop_group_tunnel_t::to_string() const {
   std::ostringstream ss;
   ss << "nexthop_group_tunnel_t(";
   ss << "tunnel_endpoint=" << tunnel_endpoint_;
   ss << ", nhg_name='" << nhg_name_ << "'";
   ss << ", igp_pref=" << igp_pref_;
   ss << ", igp_metric=" << igp_metric_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const nexthop_group_tunnel_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_NEXTHOP_GROUP_TUNNEL_H
