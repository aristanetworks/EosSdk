// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_IP_ROUTE_H
#define EOS_INLINE_TYPES_IP_ROUTE_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const ip_route_action_t & enum_val) {
   if (enum_val==IP_ROUTE_ACTION_NULL) {
      os << "IP_ROUTE_ACTION_NULL";
   } else if (enum_val==IP_ROUTE_ACTION_FORWARD) {
      os << "IP_ROUTE_ACTION_FORWARD";
   } else if (enum_val==IP_ROUTE_ACTION_DROP) {
      os << "IP_ROUTE_ACTION_DROP";
   } else if (enum_val==IP_ROUTE_ACTION_NEXTHOP_GROUP) {
      os << "IP_ROUTE_ACTION_NEXTHOP_GROUP";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline ip_route_key_t::ip_route_key_t() :
      prefix_(), preference_(1) {
}

inline ip_route_key_t::ip_route_key_t(ip_prefix_t const & prefix) :
      prefix_(prefix), preference_(1) {
}

inline ip_route_key_t::ip_route_key_t(ip_prefix_t const & prefix,
                                      ip_route_preference_t preference) :
      prefix_(prefix), preference_(preference) {
}

inline ip_prefix_t
ip_route_key_t::prefix() const {
   return prefix_;
}

inline void
ip_route_key_t::prefix_is(ip_prefix_t const & prefix) {
   prefix_ = prefix;
}

inline ip_route_preference_t
ip_route_key_t::preference() const {
   return preference_;
}

inline void
ip_route_key_t::preference_is(ip_route_preference_t preference) {
   preference_ = preference;
}

inline bool
ip_route_key_t::operator==(ip_route_key_t const & other) const {
   return prefix_ == other.prefix_ &&
          preference_ == other.preference_;
}

inline bool
ip_route_key_t::operator!=(ip_route_key_t const & other) const {
   return !operator==(other);
}

inline uint32_t
ip_route_key_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&prefix_,
              sizeof(ip_prefix_t), ret);
   ret = hash_mix::mix((uint8_t *)&preference_,
              sizeof(ip_route_preference_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
ip_route_key_t::to_string() const {
   std::ostringstream ss;
   ss << "ip_route_key_t(";
   ss << "prefix=" << prefix_;
   ss << ", preference=" << preference_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const ip_route_key_t& obj) {
   os << obj.to_string();
   return os;
}



inline ip_route_t::ip_route_t() :
      key_(), tag_(0) {
}

inline ip_route_t::ip_route_t(ip_route_key_t const & key) :
      key_(key), tag_(0) {
}

inline ip_route_key_t
ip_route_t::key() const {
   return key_;
}

inline void
ip_route_t::key_is(ip_route_key_t const & key) {
   key_ = key;
}

inline ip_route_tag_t
ip_route_t::tag() const {
   return tag_;
}

inline void
ip_route_t::tag_is(ip_route_tag_t tag) {
   tag_ = tag;
}

inline bool
ip_route_t::operator==(ip_route_t const & other) const {
   return key_ == other.key_ &&
          tag_ == other.tag_;
}

inline bool
ip_route_t::operator!=(ip_route_t const & other) const {
   return !operator==(other);
}

inline uint32_t
ip_route_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&key_,
              sizeof(ip_route_key_t), ret);
   ret = hash_mix::mix((uint8_t *)&tag_,
              sizeof(ip_route_tag_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
ip_route_t::to_string() const {
   std::ostringstream ss;
   ss << "ip_route_t(";
   ss << "key=" << key_;
   ss << ", tag=" << tag_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const ip_route_t& obj) {
   os << obj.to_string();
   return os;
}



inline ip_route_via_t::ip_route_via_t() :
      route_key_(), hop_(), intf_(), nexthop_group_(), mpls_label_(), vni_(),
      vtep_addr_(), router_mac_(), egress_vrf_() {
}

inline ip_route_via_t::ip_route_via_t(ip_route_key_t const & route_key) :
      route_key_(route_key), hop_(), intf_(), nexthop_group_(), mpls_label_(),
      vni_(), vtep_addr_(), router_mac_(), egress_vrf_() {
}

inline ip_route_key_t
ip_route_via_t::route_key() const {
   return route_key_;
}

inline void
ip_route_via_t::route_key_is(ip_route_key_t const & route_key) {
   route_key_ = route_key;
}

inline ip_addr_t
ip_route_via_t::hop() const {
   return hop_;
}

inline void
ip_route_via_t::hop_is(ip_addr_t const & hop) {
   hop_ = hop;
}

inline intf_id_t
ip_route_via_t::intf() const {
   return intf_;
}

inline void
ip_route_via_t::intf_is(intf_id_t intf) {
   intf_ = intf;
}

inline std::string
ip_route_via_t::nexthop_group() const {
   return nexthop_group_;
}

inline void
ip_route_via_t::nexthop_group_is(std::string const & nexthop_group) {
   nexthop_group_ = nexthop_group;
}

inline mpls_label_t
ip_route_via_t::mpls_label() const {
   return mpls_label_;
}

inline void
ip_route_via_t::mpls_label_is(mpls_label_t mpls_label) {
   mpls_label_ = mpls_label;
}

inline vni_t
ip_route_via_t::vni() const {
   return vni_;
}

inline void
ip_route_via_t::vni_is(vni_t vni) {
   vni_ = vni;
}

inline ip_addr_t
ip_route_via_t::vtep_addr() const {
   return vtep_addr_;
}

inline void
ip_route_via_t::vtep_addr_is(ip_addr_t vtep_addr) {
   vtep_addr_ = vtep_addr;
}

inline eth_addr_t
ip_route_via_t::router_mac() const {
   return router_mac_;
}

inline void
ip_route_via_t::router_mac_is(eth_addr_t router_mac) {
   router_mac_ = router_mac;
}

inline std::string
ip_route_via_t::egress_vrf() const {
   return egress_vrf_;
}

inline void
ip_route_via_t::egress_vrf_is(std::string const & egress_vrf) {
   egress_vrf_ = egress_vrf;
}

inline bool
ip_route_via_t::operator==(ip_route_via_t const & other) const {
   return route_key_ == other.route_key_ &&
          hop_ == other.hop_ &&
          intf_ == other.intf_ &&
          nexthop_group_ == other.nexthop_group_ &&
          mpls_label_ == other.mpls_label_ &&
          vni_ == other.vni_ &&
          vtep_addr_ == other.vtep_addr_ &&
          router_mac_ == other.router_mac_ &&
          egress_vrf_ == other.egress_vrf_;
}

inline bool
ip_route_via_t::operator!=(ip_route_via_t const & other) const {
   return !operator==(other);
}

inline uint32_t
ip_route_via_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&route_key_,
              sizeof(ip_route_key_t), ret);
   ret = hash_mix::mix((uint8_t *)&hop_,
              sizeof(ip_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&intf_,
              sizeof(intf_id_t), ret);
   ret ^= std::hash<std::string>()(nexthop_group_);
   ret = hash_mix::mix((uint8_t *)&mpls_label_,
              sizeof(mpls_label_t), ret);
   ret = hash_mix::mix((uint8_t *)&vni_,
              sizeof(vni_t), ret);
   ret = hash_mix::mix((uint8_t *)&vtep_addr_,
              sizeof(ip_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&router_mac_,
              sizeof(eth_addr_t), ret);
   ret ^= std::hash<std::string>()(egress_vrf_);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
ip_route_via_t::to_string() const {
   std::ostringstream ss;
   ss << "ip_route_via_t(";
   ss << "route_key=" << route_key_;
   ss << ", hop=" << hop_;
   ss << ", intf=" << intf_;
   ss << ", nexthop_group='" << nexthop_group_ << "'";
   ss << ", mpls_label=" << mpls_label_;
   ss << ", vni=" << vni_;
   ss << ", vtep_addr=" << vtep_addr_;
   ss << ", router_mac=" << router_mac_;
   ss << ", egress_vrf='" << egress_vrf_ << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const ip_route_via_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_IP_ROUTE_H
