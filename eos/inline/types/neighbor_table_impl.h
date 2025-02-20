// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_NEIGHBOR_TABLE_IMPL_H
#define EOS_INLINE_TYPES_NEIGHBOR_TABLE_IMPL_H

namespace eos {



// Default constructor.
neighbor_key_impl_t::neighbor_key_impl_t() :
      ip_addr_(), intf_id_() {
}

neighbor_key_impl_t::neighbor_key_impl_t(ip_addr_t const & ip_addr) :
      ip_addr_(ip_addr), intf_id_() {
}

neighbor_key_impl_t::neighbor_key_impl_t(ip_addr_t const & ip_addr,
                                                intf_id_t intf_id) :
      ip_addr_(ip_addr), intf_id_(intf_id) {
}

ip_addr_t
neighbor_key_impl_t::ip_addr() const {
   return ip_addr_;
}

intf_id_t
neighbor_key_impl_t::intf_id() const {
   return intf_id_;
}

bool
neighbor_key_impl_t::operator==(neighbor_key_impl_t const & other) const {
   return ip_addr_ == other.ip_addr_ &&
          intf_id_ == other.intf_id_;
}

bool
neighbor_key_impl_t::operator!=(neighbor_key_impl_t const & other) const {
   return !operator==(other);
}

bool
neighbor_key_impl_t::operator<(neighbor_key_impl_t const & other) const {
   if(ip_addr_ != other.ip_addr_) {
      return ip_addr_ < other.ip_addr_;
   } else if(intf_id_ != other.intf_id_) {
      return intf_id_ < other.intf_id_;
   }
   return false;
}

uint32_t
neighbor_key_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
neighbor_key_impl_t::mix_me(hash_mix & h) const {
   h.mix(ip_addr_); // ip_addr_t
   h.mix(intf_id_); // intf_id_t
}

std::string
neighbor_key_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "neighbor_key_t(";
   ss << "ip_addr=" << ip_addr_;
   ss << ", intf_id=" << intf_id_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const neighbor_key_impl_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
neighbor_entry_impl_t::neighbor_entry_impl_t() :
      neighbor_key_(), eth_addr_(), entry_type_(NEIGHBOR_ENTRY_TYPE_DYNAMIC) {
}

neighbor_entry_impl_t::neighbor_entry_impl_t(
         neighbor_key_t const & neighbor_key, eth_addr_t eth_addr,
         neighbor_entry_type_t entry_type) :
      neighbor_key_(neighbor_key), eth_addr_(eth_addr), entry_type_(entry_type) {
}

neighbor_key_t
neighbor_entry_impl_t::neighbor_key() const {
   return neighbor_key_;
}

eth_addr_t
neighbor_entry_impl_t::eth_addr() const {
   return eth_addr_;
}

neighbor_entry_type_t
neighbor_entry_impl_t::entry_type() const {
   return entry_type_;
}

bool
neighbor_entry_impl_t::operator==(neighbor_entry_impl_t const & other) const {
   return neighbor_key_ == other.neighbor_key_ &&
          eth_addr_ == other.eth_addr_ &&
          entry_type_ == other.entry_type_;
}

bool
neighbor_entry_impl_t::operator!=(neighbor_entry_impl_t const & other) const {
   return !operator==(other);
}

bool
neighbor_entry_impl_t::operator<(neighbor_entry_impl_t const & other) const {
   if(neighbor_key_ != other.neighbor_key_) {
      return neighbor_key_ < other.neighbor_key_;
   } else if(eth_addr_ != other.eth_addr_) {
      return eth_addr_ < other.eth_addr_;
   } else if(entry_type_ != other.entry_type_) {
      return entry_type_ < other.entry_type_;
   }
   return false;
}

uint32_t
neighbor_entry_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
neighbor_entry_impl_t::mix_me(hash_mix & h) const {
   h.mix(neighbor_key_); // neighbor_key_t
   h.mix(eth_addr_); // eth_addr_t
   h.mix(entry_type_); // neighbor_entry_type_t
}

std::string
neighbor_entry_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "neighbor_entry_t(";
   ss << "neighbor_key=" << neighbor_key_;
   ss << ", eth_addr=" << eth_addr_;
   ss << ", entry_type=" << entry_type_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const neighbor_entry_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/neighbor_table.h>

#endif // EOS_INLINE_TYPES_NEIGHBOR_TABLE_IMPL_H
