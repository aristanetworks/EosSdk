// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_BGP_PATH_IMPL_H
#define EOS_INLINE_TYPES_BGP_PATH_IMPL_H

namespace eos {





bgp_path_attr_fields_impl_t::bgp_path_attr_fields_impl_t() :
      next_hop_(), community_list_() {
}

bgp_path_attr_fields_impl_t::bgp_path_attr_fields_impl_t(bool next_hop) :
      next_hop_(next_hop), community_list_() {
}

bool
bgp_path_attr_fields_impl_t::next_hop() const {
   return next_hop_;
}

void
bgp_path_attr_fields_impl_t::next_hop_is(bool next_hop) {
   next_hop_ = next_hop;
}

bool
bgp_path_attr_fields_impl_t::community_list() const {
   return community_list_;
}

void
bgp_path_attr_fields_impl_t::community_list_is(bool community_list) {
   community_list_ = community_list;
}

bool
bgp_path_attr_fields_impl_t::operator==(bgp_path_attr_fields_impl_t const & other)
       const {
   return next_hop_ == other.next_hop_ &&
          community_list_ == other.community_list_;
}

bool
bgp_path_attr_fields_impl_t::operator!=(bgp_path_attr_fields_impl_t const & other)
       const {
   return !operator==(other);
}

uint32_t
bgp_path_attr_fields_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
bgp_path_attr_fields_impl_t::mix_me(hash_mix & h) const {
   h.mix(next_hop_); // bool
   h.mix(community_list_); // bool
}

std::string
bgp_path_attr_fields_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "bgp_path_attr_fields_t(";
   ss << "next_hop=" << next_hop_;
   ss << ", community_list=" << community_list_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const bgp_path_attr_fields_impl_t& obj) {
   os << obj.to_string();
   return os;
}



bgp_path_options_impl_t::bgp_path_options_impl_t() :
      receive_route_stage_(), path_attr_fields_() {
}

bgp_path_options_impl_t::bgp_path_options_impl_t(
         bgp_receive_route_stage_t receive_route_stage) :
      receive_route_stage_(receive_route_stage), path_attr_fields_() {
}

bgp_receive_route_stage_t
bgp_path_options_impl_t::receive_route_stage() const {
   return receive_route_stage_;
}

void
bgp_path_options_impl_t::receive_route_stage_is(
         bgp_receive_route_stage_t receive_route_stage) {
   receive_route_stage_ = receive_route_stage;
}

bgp_path_attr_fields_t
bgp_path_options_impl_t::path_attr_fields() const {
   return path_attr_fields_;
}

void
bgp_path_options_impl_t::path_attr_fields_is(
         bgp_path_attr_fields_t const & path_attr_fields) {
   path_attr_fields_ = path_attr_fields;
}

bool
bgp_path_options_impl_t::operator==(bgp_path_options_impl_t const & other) const {
   return receive_route_stage_ == other.receive_route_stage_ &&
          path_attr_fields_ == other.path_attr_fields_;
}

bool
bgp_path_options_impl_t::operator!=(bgp_path_options_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
bgp_path_options_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
bgp_path_options_impl_t::mix_me(hash_mix & h) const {
   h.mix(receive_route_stage_); // bgp_receive_route_stage_t
   h.mix(path_attr_fields_); // bgp_path_attr_fields_t
}

std::string
bgp_path_options_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "bgp_path_options_t(";
   ss << "receive_route_stage=" << receive_route_stage_;
   ss << ", path_attr_fields=" << path_attr_fields_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const bgp_path_options_impl_t& obj) {
   os << obj.to_string();
   return os;
}



bgp_path_attr_impl_t::bgp_path_attr_impl_t() :
      next_hop_(), origin_(), med_(), local_pref_(), community_list_() {
}

bgp_path_attr_impl_t::bgp_path_attr_impl_t(uint8_t origin, uint32_t med,
                                                  uint32_t local_pref) :
      next_hop_(), origin_(origin), med_(med), local_pref_(local_pref),
      community_list_() {
}

ip_addr_t
bgp_path_attr_impl_t::next_hop() const {
   return next_hop_;
}

void
bgp_path_attr_impl_t::next_hop_is(ip_addr_t const & next_hop) {
   next_hop_ = next_hop;
}

uint8_t
bgp_path_attr_impl_t::origin() const {
   return origin_;
}

void
bgp_path_attr_impl_t::origin_is(uint8_t origin) {
   origin_ = origin;
}

uint32_t
bgp_path_attr_impl_t::med() const {
   return med_;
}

void
bgp_path_attr_impl_t::med_is(uint32_t med) {
   med_ = med;
}

uint32_t
bgp_path_attr_impl_t::local_pref() const {
   return local_pref_;
}

void
bgp_path_attr_impl_t::local_pref_is(uint32_t local_pref) {
   local_pref_ = local_pref;
}

std::unordered_set<uint32_t> const &
bgp_path_attr_impl_t::community_list() const {
   return community_list_;
}

void
bgp_path_attr_impl_t::community_list_is(
         std::unordered_set<uint32_t> const & community_list) {
   community_list_ = community_list;
}

void
bgp_path_attr_impl_t::community_list_set(uint32_t const & value) {
   community_list_.insert(value);
}

void
bgp_path_attr_impl_t::community_list_del(uint32_t const & value) {
   community_list_.erase(value);
}

bool
bgp_path_attr_impl_t::operator==(bgp_path_attr_impl_t const & other) const {
   return next_hop_ == other.next_hop_ &&
          origin_ == other.origin_ &&
          med_ == other.med_ &&
          local_pref_ == other.local_pref_ &&
          community_list_ == other.community_list_;
}

bool
bgp_path_attr_impl_t::operator!=(bgp_path_attr_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
bgp_path_attr_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
bgp_path_attr_impl_t::mix_me(hash_mix & h) const {
   h.mix(next_hop_); // ip_addr_t
   h.mix(origin_); // uint8_t
   h.mix(med_); // uint32_t
   h.mix(local_pref_); // uint32_t
   for (auto it=community_list_.cbegin();
        it!=community_list_.cend(); ++it) {
      h.mix(*it); // uint32_t
   }
}

std::string
bgp_path_attr_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "bgp_path_attr_t(";
   ss << "next_hop=" << next_hop_;
   ss << ", origin=" << origin_;
   ss << ", med=" << med_;
   ss << ", local_pref=" << local_pref_;
   ss << ", community_list=" <<"'";
   bool first_community_list = true;
   for (auto it=community_list_.cbegin();
        it!=community_list_.cend(); ++it) {
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

std::ostream&
operator<<(std::ostream& os, const bgp_path_attr_impl_t& obj) {
   os << obj.to_string();
   return os;
}



bgp_path_key_impl_t::bgp_path_key_impl_t() :
      prefix_(), peer_addr_(), vrf_name_() {
}

bgp_path_key_impl_t::bgp_path_key_impl_t(ip_prefix_t const & prefix,
                                                ip_addr_t const & peer_addr,
                                                std::string const & vrf_name) :
      prefix_(prefix), peer_addr_(peer_addr), vrf_name_(vrf_name) {
}

ip_prefix_t
bgp_path_key_impl_t::prefix() const {
   return prefix_;
}

void
bgp_path_key_impl_t::prefix_is(ip_prefix_t const & prefix) {
   prefix_ = prefix;
}

ip_addr_t
bgp_path_key_impl_t::peer_addr() const {
   return peer_addr_;
}

void
bgp_path_key_impl_t::peer_addr_is(ip_addr_t const & peer_addr) {
   peer_addr_ = peer_addr;
}

std::string
bgp_path_key_impl_t::vrf_name() const {
   return vrf_name_;
}

void
bgp_path_key_impl_t::vrf_name_is(std::string const & vrf_name) {
   vrf_name_ = vrf_name;
}

bool
bgp_path_key_impl_t::operator==(bgp_path_key_impl_t const & other) const {
   return prefix_ == other.prefix_ &&
          peer_addr_ == other.peer_addr_ &&
          vrf_name_ == other.vrf_name_;
}

bool
bgp_path_key_impl_t::operator!=(bgp_path_key_impl_t const & other) const {
   return !operator==(other);
}

bool
bgp_path_key_impl_t::operator<(bgp_path_key_impl_t const & other) const {
   if(prefix_ != other.prefix_) {
      return prefix_ < other.prefix_;
   } else if(peer_addr_ != other.peer_addr_) {
      return peer_addr_ < other.peer_addr_;
   } else if(vrf_name_ != other.vrf_name_) {
      return vrf_name_ < other.vrf_name_;
   }
   return false;
}

uint32_t
bgp_path_key_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
bgp_path_key_impl_t::mix_me(hash_mix & h) const {
   h.mix(prefix_); // ip_prefix_t
   h.mix(peer_addr_); // ip_addr_t
   h.mix(vrf_name_); // std::string
}

std::string
bgp_path_key_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "bgp_path_key_t(";
   ss << "prefix=" << prefix_;
   ss << ", peer_addr=" << peer_addr_;
   ss << ", vrf_name='" << vrf_name_ << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const bgp_path_key_impl_t& obj) {
   os << obj.to_string();
   return os;
}



bgp_path_impl_t::bgp_path_impl_t() :
      path_key_(), path_attr_() {
}

bgp_path_impl_t::bgp_path_impl_t(bgp_path_key_t const & path_key) :
      path_key_(path_key), path_attr_() {
}

bgp_path_key_t
bgp_path_impl_t::path_key() const {
   return path_key_;
}

void
bgp_path_impl_t::path_key_is(bgp_path_key_t const & path_key) {
   path_key_ = path_key;
}

bgp_path_attr_t
bgp_path_impl_t::path_attr() const {
   return path_attr_;
}

void
bgp_path_impl_t::path_attr_is(bgp_path_attr_t const & path_attr) {
   path_attr_ = path_attr;
}

bool
bgp_path_impl_t::operator==(bgp_path_impl_t const & other) const {
   return path_key_ == other.path_key_ &&
          path_attr_ == other.path_attr_;
}

bool
bgp_path_impl_t::operator!=(bgp_path_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
bgp_path_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
bgp_path_impl_t::mix_me(hash_mix & h) const {
   h.mix(path_key_); // bgp_path_key_t
   h.mix(path_attr_); // bgp_path_attr_t
}

std::string
bgp_path_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "bgp_path_t(";
   ss << "path_key=" << path_key_;
   ss << ", path_attr=" << path_attr_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const bgp_path_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/bgp_path.h>

#endif // EOS_INLINE_TYPES_BGP_PATH_IMPL_H
