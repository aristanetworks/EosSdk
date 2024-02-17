// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MAC_TABLE_IMPL_H
#define EOS_INLINE_TYPES_MAC_TABLE_IMPL_H

namespace eos {



mac_key_impl_t::mac_key_impl_t() :
      vlan_id_(), eth_addr_() {
}

mac_key_impl_t::mac_key_impl_t(vlan_id_t vlan_id,
                                      eth_addr_t const & eth_addr) :
      vlan_id_(vlan_id), eth_addr_(eth_addr) {
}

vlan_id_t
mac_key_impl_t::vlan_id() const {
   return vlan_id_;
}

eth_addr_t
mac_key_impl_t::eth_addr() const {
   return eth_addr_;
}

bool
mac_key_impl_t::operator!() const {
   return !vlan_id_ && !eth_addr_;
}

bool
mac_key_impl_t::operator==(mac_key_impl_t const & other) const {
   return vlan_id_ == other.vlan_id_ &&
          eth_addr_ == other.eth_addr_;
}

bool
mac_key_impl_t::operator!=(mac_key_impl_t const & other) const {
   return !operator==(other);
}

bool
mac_key_impl_t::operator<(mac_key_impl_t const & other) const {
   if(vlan_id_ != other.vlan_id_) {
      return vlan_id_ < other.vlan_id_;
   } else if(eth_addr_ != other.eth_addr_) {
      return eth_addr_ < other.eth_addr_;
   }
   return false;
}

uint32_t
mac_key_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
mac_key_impl_t::mix_me(hash_mix & h) const {
   h.mix(vlan_id_); // vlan_id_t
   h.mix(eth_addr_); // eth_addr_t
}

std::string
mac_key_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "mac_key_t(";
   ss << "vlan_id=" << vlan_id_;
   ss << ", eth_addr=" << eth_addr_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const mac_key_impl_t& obj) {
   os << obj.to_string();
   return os;
}



mac_entry_impl_t::mac_entry_impl_t() :
      mac_key_(), intfs_() {
}

mac_entry_impl_t::mac_entry_impl_t(mac_key_t const & mac_key) :
      mac_key_(mac_key), intfs_() {
}

mac_entry_impl_t::mac_entry_impl_t(mac_key_t const & mac_key,
                                          intf_id_t intf) :
      mac_key_(mac_key), intfs_{intf} {
}

mac_entry_impl_t::mac_entry_impl_t(mac_key_t const & mac_key,
                                          std::set<intf_id_t> const & intfs) :
      mac_key_(mac_key), intfs_(intfs) {
}

mac_entry_impl_t::mac_entry_impl_t(vlan_id_t vlan_id, eth_addr_t eth_addr) :
      mac_key_(mac_key_t(vlan_id, eth_addr)), intfs_() {
}

mac_entry_impl_t::mac_entry_impl_t(eth_addr_t eth_addr, intf_id_t intf) :
      mac_key_(mac_key_t(vlan_id_t(), eth_addr)), intfs_{intf} {
}

mac_key_t
mac_entry_impl_t::mac_key() const {
   return mac_key_;
}

void
mac_entry_impl_t::mac_key_is(mac_key_t const & mac_key) {
   mac_key_ = mac_key;
}

std::set<intf_id_t> const &
mac_entry_impl_t::intfs() const {
   return intfs_;
}

void
mac_entry_impl_t::intfs_is(std::set<intf_id_t> const & intfs) {
   intfs_ = intfs;
}

void
mac_entry_impl_t::intf_set(intf_id_t const & value) {
   intfs_.insert(value);
}

void
mac_entry_impl_t::intf_del(intf_id_t const & value) {
   intfs_.erase(value);
}

bool
mac_entry_impl_t::operator!() const {
   return !mac_key_;
}

vlan_id_t
mac_entry_impl_t::vlan_id() const {
   return mac_key_.vlan_id();
}

eth_addr_t
mac_entry_impl_t::eth_addr() const {
   return mac_key_.eth_addr();
}

intf_id_t
mac_entry_impl_t::intf() const {
   return intfs_.size() ? *intfs_.begin(): intf_id_t();
}

void
mac_entry_impl_t::intf_is(intf_id_t intf) {
   intfs_ = {intf};
}

bool
mac_entry_impl_t::operator==(mac_entry_impl_t const & other) const {
   return mac_key_ == other.mac_key_ &&
          intfs_ == other.intfs_;
}

bool
mac_entry_impl_t::operator!=(mac_entry_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
mac_entry_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
mac_entry_impl_t::mix_me(hash_mix & h) const {
   h.mix(mac_key_); // mac_key_t
   for (auto it=intfs_.cbegin();
        it!=intfs_.cend(); ++it) {
      h.mix(*it); // intf_id_t
   }
}

std::string
mac_entry_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "mac_entry_t(";
   ss << "mac_key=" << mac_key_;
   ss << ", intfs=" <<"'";
   bool first_intfs = true;
   for (auto it=intfs_.cbegin();
        it!=intfs_.cend(); ++it) {
      if (first_intfs) {
         ss << (*it);
         first_intfs = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const mac_entry_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/mac_table.h>

#endif // EOS_INLINE_TYPES_MAC_TABLE_IMPL_H
