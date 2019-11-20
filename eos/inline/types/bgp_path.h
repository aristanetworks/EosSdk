// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_BGP_PATH_H
#define EOS_INLINE_TYPES_BGP_PATH_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const bgp_receive_route_stage_t & enum_val) {
   if (enum_val==BGP_PATH_PRE_POLICY) {
      os << "BGP_PATH_PRE_POLICY";
   } else if (enum_val==BGP_PATH_POST_POLICY) {
      os << "BGP_PATH_POST_POLICY";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline bgp_path_attr_fields_t::bgp_path_attr_fields_t() :
      next_hop_(), community_list_() {
}

inline bgp_path_attr_fields_t::bgp_path_attr_fields_t(bool next_hop) :
      next_hop_(next_hop), community_list_() {
}

inline bool
bgp_path_attr_fields_t::next_hop() const {
   return next_hop_;
}

inline void
bgp_path_attr_fields_t::next_hop_is(bool next_hop) {
   next_hop_ = next_hop;
}

inline bool
bgp_path_attr_fields_t::community_list() const {
   return community_list_;
}

inline void
bgp_path_attr_fields_t::community_list_is(bool community_list) {
   community_list_ = community_list;
}

inline bool
bgp_path_attr_fields_t::operator==(bgp_path_attr_fields_t const & other) const {
   return next_hop_ == other.next_hop_ &&
          community_list_ == other.community_list_;
}

inline bool
bgp_path_attr_fields_t::operator!=(bgp_path_attr_fields_t const & other) const {
   return !operator==(other);
}

inline uint32_t
bgp_path_attr_fields_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&next_hop_,
              sizeof(bool), ret);
   ret = hash_mix::mix((uint8_t *)&community_list_,
              sizeof(bool), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
bgp_path_attr_fields_t::to_string() const {
   std::ostringstream ss;
   ss << "bgp_path_attr_fields_t(";
   ss << "next_hop=" << next_hop_;
   ss << ", community_list=" << community_list_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const bgp_path_attr_fields_t& obj) {
   os << obj.to_string();
   return os;
}



inline bgp_path_options_t::bgp_path_options_t() :
      receive_route_stage_(), path_attr_fields_() {
}

inline bgp_path_options_t::bgp_path_options_t(
         bgp_receive_route_stage_t receive_route_stage) :
      receive_route_stage_(receive_route_stage), path_attr_fields_() {
}

inline bgp_receive_route_stage_t
bgp_path_options_t::receive_route_stage() const {
   return receive_route_stage_;
}

inline void
bgp_path_options_t::receive_route_stage_is(
         bgp_receive_route_stage_t receive_route_stage) {
   receive_route_stage_ = receive_route_stage;
}

inline bgp_path_attr_fields_t
bgp_path_options_t::path_attr_fields() const {
   return path_attr_fields_;
}

inline void
bgp_path_options_t::path_attr_fields_is(
         bgp_path_attr_fields_t const & path_attr_fields) {
   path_attr_fields_ = path_attr_fields;
}

inline bool
bgp_path_options_t::operator==(bgp_path_options_t const & other) const {
   return receive_route_stage_ == other.receive_route_stage_ &&
          path_attr_fields_ == other.path_attr_fields_;
}

inline bool
bgp_path_options_t::operator!=(bgp_path_options_t const & other) const {
   return !operator==(other);
}

inline uint32_t
bgp_path_options_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&receive_route_stage_,
              sizeof(bgp_receive_route_stage_t), ret);
   ret = hash_mix::mix((uint8_t *)&path_attr_fields_,
              sizeof(bgp_path_attr_fields_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
bgp_path_options_t::to_string() const {
   std::ostringstream ss;
   ss << "bgp_path_options_t(";
   ss << "receive_route_stage=" << receive_route_stage_;
   ss << ", path_attr_fields=" << path_attr_fields_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const bgp_path_options_t& obj) {
   os << obj.to_string();
   return os;
}



inline bgp_path_attr_t::bgp_path_attr_t() :
      next_hop_(), origin_(), med_(), local_pref_(), community_list_() {
}

inline bgp_path_attr_t::bgp_path_attr_t(uint8_t origin, uint32_t med,
                                        uint32_t local_pref) :
      next_hop_(), origin_(origin), med_(med), local_pref_(local_pref),
      community_list_() {
}

inline ip_addr_t
bgp_path_attr_t::next_hop() const {
   return next_hop_;
}

inline void
bgp_path_attr_t::next_hop_is(ip_addr_t const & next_hop) {
   next_hop_ = next_hop;
}

inline uint8_t
bgp_path_attr_t::origin() const {
   return origin_;
}

inline void
bgp_path_attr_t::origin_is(uint8_t origin) {
   origin_ = origin;
}

inline uint32_t
bgp_path_attr_t::med() const {
   return med_;
}

inline void
bgp_path_attr_t::med_is(uint32_t med) {
   med_ = med;
}

inline uint32_t
bgp_path_attr_t::local_pref() const {
   return local_pref_;
}

inline void
bgp_path_attr_t::local_pref_is(uint32_t local_pref) {
   local_pref_ = local_pref;
}

inline std::unordered_set<uint32_t> const &
bgp_path_attr_t::community_list() const {
   return community_list_;
}

inline void
bgp_path_attr_t::community_list_is(
         std::unordered_set<uint32_t> const & community_list) {
   community_list_ = community_list;
}

inline void
bgp_path_attr_t::community_list_set(uint32_t const & value) {
   community_list_.insert(value);
}

inline void
bgp_path_attr_t::community_list_del(uint32_t const & value) {
   community_list_.erase(value);
}

inline bool
bgp_path_attr_t::operator==(bgp_path_attr_t const & other) const {
   return next_hop_ == other.next_hop_ &&
          origin_ == other.origin_ &&
          med_ == other.med_ &&
          local_pref_ == other.local_pref_ &&
          community_list_ == other.community_list_;
}

inline bool
bgp_path_attr_t::operator!=(bgp_path_attr_t const & other) const {
   return !operator==(other);
}

inline uint32_t
bgp_path_attr_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&next_hop_,
              sizeof(ip_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&origin_,
              sizeof(uint8_t), ret);
   ret = hash_mix::mix((uint8_t *)&med_,
              sizeof(uint32_t), ret);
   ret = hash_mix::mix((uint8_t *)&local_pref_,
              sizeof(uint32_t), ret);
   for (auto it=community_list_.cbegin(); it!=community_list_.cend(); ++it) {
      ret = hash_mix::mix((uint8_t *)&(*it),
            sizeof(uint32_t), ret);
   }
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
bgp_path_attr_t::to_string() const {
   std::ostringstream ss;
   ss << "bgp_path_attr_t(";
   ss << "next_hop=" << next_hop_;
   ss << ", origin=" << origin_;
   ss << ", med=" << med_;
   ss << ", local_pref=" << local_pref_;
   ss << ", community_list=" <<"'";
   bool first_community_list = true;
   for (auto it=community_list_.cbegin(); it!=community_list_.cend(); ++it) {
      if (first_community_list) {
         ss << (*it);
         first_community_list = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const bgp_path_attr_t& obj) {
   os << obj.to_string();
   return os;
}



inline bgp_path_key_t::bgp_path_key_t() :
      prefix_(), peer_addr_(), vrf_name_() {
}

inline bgp_path_key_t::bgp_path_key_t(ip_prefix_t const & prefix,
                                      ip_addr_t const & peer_addr,
                                      std::string const & vrf_name) :
      prefix_(prefix), peer_addr_(peer_addr), vrf_name_(vrf_name) {
}

inline ip_prefix_t
bgp_path_key_t::prefix() const {
   return prefix_;
}

inline void
bgp_path_key_t::prefix_is(ip_prefix_t const & prefix) {
   prefix_ = prefix;
}

inline ip_addr_t
bgp_path_key_t::peer_addr() const {
   return peer_addr_;
}

inline void
bgp_path_key_t::peer_addr_is(ip_addr_t const & peer_addr) {
   peer_addr_ = peer_addr;
}

inline std::string
bgp_path_key_t::vrf_name() const {
   return vrf_name_;
}

inline void
bgp_path_key_t::vrf_name_is(std::string const & vrf_name) {
   vrf_name_ = vrf_name;
}

inline bool
bgp_path_key_t::operator==(bgp_path_key_t const & other) const {
   return prefix_ == other.prefix_ &&
          peer_addr_ == other.peer_addr_ &&
          vrf_name_ == other.vrf_name_;
}

inline bool
bgp_path_key_t::operator!=(bgp_path_key_t const & other) const {
   return !operator==(other);
}

inline uint32_t
bgp_path_key_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&prefix_,
              sizeof(ip_prefix_t), ret);
   ret = hash_mix::mix((uint8_t *)&peer_addr_,
              sizeof(ip_addr_t), ret);
   ret ^= std::hash<std::string>()(vrf_name_);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
bgp_path_key_t::to_string() const {
   std::ostringstream ss;
   ss << "bgp_path_key_t(";
   ss << "prefix=" << prefix_;
   ss << ", peer_addr=" << peer_addr_;
   ss << ", vrf_name='" << vrf_name_ << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const bgp_path_key_t& obj) {
   os << obj.to_string();
   return os;
}



inline bgp_path_t::bgp_path_t() :
      path_key_(), path_attr_() {
}

inline bgp_path_t::bgp_path_t(bgp_path_key_t const & path_key) :
      path_key_(path_key), path_attr_() {
}

inline bgp_path_key_t
bgp_path_t::path_key() const {
   return path_key_;
}

inline void
bgp_path_t::path_key_is(bgp_path_key_t const & path_key) {
   path_key_ = path_key;
}

inline bgp_path_attr_t
bgp_path_t::path_attr() const {
   return path_attr_;
}

inline void
bgp_path_t::path_attr_is(bgp_path_attr_t const & path_attr) {
   path_attr_ = path_attr;
}

inline bool
bgp_path_t::operator==(bgp_path_t const & other) const {
   return path_key_ == other.path_key_ &&
          path_attr_ == other.path_attr_;
}

inline bool
bgp_path_t::operator!=(bgp_path_t const & other) const {
   return !operator==(other);
}

inline uint32_t
bgp_path_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&path_key_,
              sizeof(bgp_path_key_t), ret);
   ret = hash_mix::mix((uint8_t *)&path_attr_,
              sizeof(bgp_path_attr_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
bgp_path_t::to_string() const {
   std::ostringstream ss;
   ss << "bgp_path_t(";
   ss << "path_key=" << path_key_;
   ss << ", path_attr=" << path_attr_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const bgp_path_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_BGP_PATH_H
