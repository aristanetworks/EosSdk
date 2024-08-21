// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MAC_TABLE_H
#define EOS_INLINE_TYPES_MAC_TABLE_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const mac_entry_type_t & enum_val) {
   if (enum_val==MAC_ENTRY_NULL) {
      os << "MAC_ENTRY_NULL";
   } else if (enum_val==MAC_ENTRY_LEARNED_DYNAMIC) {
      os << "MAC_ENTRY_LEARNED_DYNAMIC";
   } else if (enum_val==MAC_ENTRY_LEARNED_SECURE) {
      os << "MAC_ENTRY_LEARNED_SECURE";
   } else if (enum_val==MAC_ENTRY_CONFIGURED_DYNAMIC) {
      os << "MAC_ENTRY_CONFIGURED_DYNAMIC";
   } else if (enum_val==MAC_ENTRY_CONFIGURED_SECURE) {
      os << "MAC_ENTRY_CONFIGURED_SECURE";
   } else if (enum_val==MAC_ENTRY_CONFIGURED_STATIC) {
      os << "MAC_ENTRY_CONFIGURED_STATIC";
   } else if (enum_val==MAC_ENTRY_PEER_DYNAMIC) {
      os << "MAC_ENTRY_PEER_DYNAMIC";
   } else if (enum_val==MAC_ENTRY_PEER_STATIC) {
      os << "MAC_ENTRY_PEER_STATIC";
   } else if (enum_val==MAC_ENTRY_PEER_SECURE) {
      os << "MAC_ENTRY_PEER_SECURE";
   } else if (enum_val==MAC_ENTRY_LEARNED_REMOTE) {
      os << "MAC_ENTRY_LEARNED_REMOTE";
   } else if (enum_val==MAC_ENTRY_CONFIGURED_REMOTE) {
      os << "MAC_ENTRY_CONFIGURED_REMOTE";
   } else if (enum_val==MAC_ENTRY_RECEIVED_REMOTE) {
      os << "MAC_ENTRY_RECEIVED_REMOTE";
   } else if (enum_val==MAC_ENTRY_PEER_LEARNED_REMOTE) {
      os << "MAC_ENTRY_PEER_LEARNED_REMOTE";
   } else if (enum_val==MAC_ENTRY_PEER_CONFIGURED_REMOTE) {
      os << "MAC_ENTRY_PEER_CONFIGURED_REMOTE";
   } else if (enum_val==MAC_ENTRY_PEER_RECEIVED_REMOTE) {
      os << "MAC_ENTRY_PEER_RECEIVED_REMOTE";
   } else if (enum_val==MAC_ENTRY_EVPN_DYNAMIC_REMOTE) {
      os << "MAC_ENTRY_EVPN_DYNAMIC_REMOTE";
   } else if (enum_val==MAC_ENTRY_EVPN_CONFIGURED_REMOTE) {
      os << "MAC_ENTRY_EVPN_CONFIGURED_REMOTE";
   } else if (enum_val==MAC_ENTRY_PEER_EVPN_REMOTE) {
      os << "MAC_ENTRY_PEER_EVPN_REMOTE";
   } else if (enum_val==MAC_ENTRY_CONFIGURED_ROUTER) {
      os << "MAC_ENTRY_CONFIGURED_ROUTER";
   } else if (enum_val==MAC_ENTRY_PEER_ROUTER) {
      os << "MAC_ENTRY_PEER_ROUTER";
   } else if (enum_val==MAC_ENTRY_EVPN_INTF) {
      os << "MAC_ENTRY_EVPN_INTF";
   } else if (enum_val==MAC_ENTRY_EVPN_REMOTE_MAC) {
      os << "MAC_ENTRY_EVPN_REMOTE_MAC";
   } else if (enum_val==MAC_ENTRY_PEER_EVPN_REMOTE_MAC) {
      os << "MAC_ENTRY_PEER_EVPN_REMOTE_MAC";
   } else if (enum_val==MAC_ENTRY_EVPN_INTF_DYNAMIC) {
      os << "MAC_ENTRY_EVPN_INTF_DYNAMIC";
   } else if (enum_val==MAC_ENTRY_EVPN_INTF_STATIC) {
      os << "MAC_ENTRY_EVPN_INTF_STATIC";
   } else if (enum_val==MAC_ENTRY_AUTHENTICATED) {
      os << "MAC_ENTRY_AUTHENTICATED";
   } else if (enum_val==MAC_ENTRY_PEER_AUTHENTICATED) {
      os << "MAC_ENTRY_PEER_AUTHENTICATED";
   } else if (enum_val==MAC_ENTRY_PENDING_SECURE) {
      os << "MAC_ENTRY_PENDING_SECURE";
   } else if (enum_val==MAC_ENTRY_VPLS_DYNAMIC_REMOTE) {
      os << "MAC_ENTRY_VPLS_DYNAMIC_REMOTE";
   } else if (enum_val==MAC_ENTRY_SOFTWARE_LEARNED_DYNAMIC) {
      os << "MAC_ENTRY_SOFTWARE_LEARNED_DYNAMIC";
   } else {
      os << "Unknown value";
   }
   return os;
}


vlan_id_t
mac_key_t::vlan_id() const {
   return pimpl->vlan_id();
}
eth_addr_t
mac_key_t::eth_addr() const {
   return pimpl->eth_addr();
}
bool
mac_key_t::operator!() const {
   return pimpl->operator!();
}
bool
mac_key_t::operator==(mac_key_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
mac_key_t::operator!=(mac_key_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
mac_key_t::operator<(mac_key_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
mac_key_t::hash() const {
   return pimpl->hash();
}
void
mac_key_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
mac_key_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const mac_key_t& obj) {
   return operator<<(os, *obj.pimpl);
}


mac_key_t
mac_entry_t::mac_key() const {
   return pimpl->mac_key();
}
void
mac_entry_t::mac_key_is(mac_key_t const & mac_key) {
   pimpl->mac_key_is(mac_key);
}
void
mac_entry_t::mac_key_is(mac_key_t && mac_key) {
   pimpl->mac_key_is(std::move(mac_key));
}
std::set<intf_id_t> const &
mac_entry_t::intfs() const {
   return pimpl->intfs();
}
void
mac_entry_t::intfs_is(std::set<intf_id_t> const & intfs) {
   pimpl->intfs_is(intfs);
}
void
mac_entry_t::intfs_is(std::set<intf_id_t> && intfs) {
   pimpl->intfs_is(std::move(intfs));
}
void
mac_entry_t::intf_set(intf_id_t const & value) {
   pimpl->intf_set(value);
}
void
mac_entry_t::intf_set(intf_id_t && value) {
   pimpl->intf_set(std::move(value));
}
void
mac_entry_t::intf_del(intf_id_t const & value) {
   pimpl->intf_del(value);
}
bool
mac_entry_t::operator!() const {
   return pimpl->operator!();
}
vlan_id_t
mac_entry_t::vlan_id() const {
   return pimpl->vlan_id();
}
eth_addr_t
mac_entry_t::eth_addr() const {
   return pimpl->eth_addr();
}
intf_id_t
mac_entry_t::intf() const {
   return pimpl->intf();
}
void
mac_entry_t::intf_is(intf_id_t intf) {
   pimpl->intf_is(intf);
}
bool
mac_entry_t::operator==(mac_entry_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
mac_entry_t::operator!=(mac_entry_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
mac_entry_t::hash() const {
   return pimpl->hash();
}
void
mac_entry_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
mac_entry_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const mac_entry_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_MAC_TABLE_H
