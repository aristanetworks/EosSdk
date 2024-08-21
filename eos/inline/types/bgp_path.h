// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_BGP_PATH_H
#define EOS_INLINE_TYPES_BGP_PATH_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const bgp_afi_safi_t & enum_val) {
   if (enum_val==BGP_IPV4_UNICAST) {
      os << "BGP_IPV4_UNICAST";
   } else if (enum_val==BGP_IPV6_UNICAST) {
      os << "BGP_IPV6_UNICAST";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
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


bool
bgp_path_attr_fields_t::next_hop() const {
   return pimpl->next_hop();
}
void
bgp_path_attr_fields_t::next_hop_is(bool next_hop) {
   pimpl->next_hop_is(next_hop);
}
bool
bgp_path_attr_fields_t::community_list() const {
   return pimpl->community_list();
}
void
bgp_path_attr_fields_t::community_list_is(bool community_list) {
   pimpl->community_list_is(community_list);
}
bool
bgp_path_attr_fields_t::operator==(bgp_path_attr_fields_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
bgp_path_attr_fields_t::operator!=(bgp_path_attr_fields_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
bgp_path_attr_fields_t::hash() const {
   return pimpl->hash();
}
void
bgp_path_attr_fields_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
bgp_path_attr_fields_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const bgp_path_attr_fields_t& obj) {
   return operator<<(os, *obj.pimpl);
}


bgp_receive_route_stage_t
bgp_path_options_t::receive_route_stage() const {
   return pimpl->receive_route_stage();
}
void
bgp_path_options_t::receive_route_stage_is(
         bgp_receive_route_stage_t receive_route_stage) {
   pimpl->receive_route_stage_is(receive_route_stage);
}
bgp_path_attr_fields_t
bgp_path_options_t::path_attr_fields() const {
   return pimpl->path_attr_fields();
}
void
bgp_path_options_t::path_attr_fields_is(
         bgp_path_attr_fields_t const & path_attr_fields) {
   pimpl->path_attr_fields_is(path_attr_fields);
}
void
bgp_path_options_t::path_attr_fields_is(bgp_path_attr_fields_t && path_attr_fields)
       {
   pimpl->path_attr_fields_is(std::move(path_attr_fields));
}
bool
bgp_path_options_t::operator==(bgp_path_options_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
bgp_path_options_t::operator!=(bgp_path_options_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
bgp_path_options_t::hash() const {
   return pimpl->hash();
}
void
bgp_path_options_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
bgp_path_options_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const bgp_path_options_t& obj) {
   return operator<<(os, *obj.pimpl);
}


ip_addr_t
bgp_path_attr_t::next_hop() const {
   return pimpl->next_hop();
}
void
bgp_path_attr_t::next_hop_is(ip_addr_t const & next_hop) {
   pimpl->next_hop_is(next_hop);
}
void
bgp_path_attr_t::next_hop_is(ip_addr_t && next_hop) {
   pimpl->next_hop_is(std::move(next_hop));
}
uint8_t
bgp_path_attr_t::origin() const {
   return pimpl->origin();
}
void
bgp_path_attr_t::origin_is(uint8_t origin) {
   pimpl->origin_is(origin);
}
uint32_t
bgp_path_attr_t::med() const {
   return pimpl->med();
}
void
bgp_path_attr_t::med_is(uint32_t med) {
   pimpl->med_is(med);
}
uint32_t
bgp_path_attr_t::local_pref() const {
   return pimpl->local_pref();
}
void
bgp_path_attr_t::local_pref_is(uint32_t local_pref) {
   pimpl->local_pref_is(local_pref);
}
std::unordered_set<uint32_t> const &
bgp_path_attr_t::community_list() const {
   return pimpl->community_list();
}
void
bgp_path_attr_t::community_list_is(
         std::unordered_set<uint32_t> const & community_list) {
   pimpl->community_list_is(community_list);
}
void
bgp_path_attr_t::community_list_is(std::unordered_set<uint32_t> && community_list) {
   pimpl->community_list_is(std::move(community_list));
}
void
bgp_path_attr_t::community_list_set(uint32_t const & value) {
   pimpl->community_list_set(value);
}
void
bgp_path_attr_t::community_list_set(uint32_t && value) {
   pimpl->community_list_set(std::move(value));
}
void
bgp_path_attr_t::community_list_del(uint32_t const & value) {
   pimpl->community_list_del(value);
}
bool
bgp_path_attr_t::operator==(bgp_path_attr_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
bgp_path_attr_t::operator!=(bgp_path_attr_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
bgp_path_attr_t::hash() const {
   return pimpl->hash();
}
void
bgp_path_attr_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
bgp_path_attr_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const bgp_path_attr_t& obj) {
   return operator<<(os, *obj.pimpl);
}


ip_prefix_t
bgp_path_key_t::prefix() const {
   return pimpl->prefix();
}
void
bgp_path_key_t::prefix_is(ip_prefix_t const & prefix) {
   pimpl->prefix_is(prefix);
}
void
bgp_path_key_t::prefix_is(ip_prefix_t && prefix) {
   pimpl->prefix_is(std::move(prefix));
}
ip_addr_t
bgp_path_key_t::peer_addr() const {
   return pimpl->peer_addr();
}
void
bgp_path_key_t::peer_addr_is(ip_addr_t const & peer_addr) {
   pimpl->peer_addr_is(peer_addr);
}
void
bgp_path_key_t::peer_addr_is(ip_addr_t && peer_addr) {
   pimpl->peer_addr_is(std::move(peer_addr));
}
std::string
bgp_path_key_t::vrf_name() const {
   return pimpl->vrf_name();
}
void
bgp_path_key_t::vrf_name_is(std::string const & vrf_name) {
   pimpl->vrf_name_is(vrf_name);
}
void
bgp_path_key_t::vrf_name_is(std::string && vrf_name) {
   pimpl->vrf_name_is(std::move(vrf_name));
}
bool
bgp_path_key_t::operator==(bgp_path_key_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
bgp_path_key_t::operator!=(bgp_path_key_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
bgp_path_key_t::operator<(bgp_path_key_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
bgp_path_key_t::hash() const {
   return pimpl->hash();
}
void
bgp_path_key_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
bgp_path_key_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const bgp_path_key_t& obj) {
   return operator<<(os, *obj.pimpl);
}


bgp_path_key_t
bgp_path_t::path_key() const {
   return pimpl->path_key();
}
void
bgp_path_t::path_key_is(bgp_path_key_t const & path_key) {
   pimpl->path_key_is(path_key);
}
void
bgp_path_t::path_key_is(bgp_path_key_t && path_key) {
   pimpl->path_key_is(std::move(path_key));
}
bgp_path_attr_t
bgp_path_t::path_attr() const {
   return pimpl->path_attr();
}
void
bgp_path_t::path_attr_is(bgp_path_attr_t const & path_attr) {
   pimpl->path_attr_is(path_attr);
}
void
bgp_path_t::path_attr_is(bgp_path_attr_t && path_attr) {
   pimpl->path_attr_is(std::move(path_attr));
}
bool
bgp_path_t::operator==(bgp_path_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
bgp_path_t::operator!=(bgp_path_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
bgp_path_t::hash() const {
   return pimpl->hash();
}
void
bgp_path_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
bgp_path_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const bgp_path_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_BGP_PATH_H
