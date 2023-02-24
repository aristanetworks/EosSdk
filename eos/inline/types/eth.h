// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ETH_H
#define EOS_INLINE_TYPES_ETH_H

namespace eos {



eth_addr_t::eth_addr_t() :
      bytes_{} {
}

eth_addr_t::eth_addr_t(uint8_t byte0, uint8_t byte1, uint8_t byte2,
                              uint8_t byte3, uint8_t byte4, uint8_t byte5) :
      bytes_{ byte0, byte1, byte2, byte3, byte4, byte5 } {
}

eth_addr_t::eth_addr_t(uint8_t const bytes[6]) :
      bytes_{ bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5] } {
}

std::string
eth_addr_t::to_string() const {

   char buf[128];
   int rv;
   rv = snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
                 bytes_[0],bytes_[1],bytes_[2],bytes_[3],bytes_[4],bytes_[5]);
   assert(rv>0);
   return std::string(buf);

}

bool
eth_addr_t::operator!() const {
   return !bytes_[0] && !bytes_[1] && !bytes_[2]
      && !bytes_[3] && !bytes_[4] && !bytes_[5];
}

bool
eth_addr_t::operator==(eth_addr_t other) const {
   return bytes_[0] == other.bytes_[0]
      && bytes_[1] == other.bytes_[1]
      && bytes_[2] == other.bytes_[2]
      && bytes_[3] == other.bytes_[3]
      && bytes_[4] == other.bytes_[4]
      && bytes_[5] == other.bytes_[5];
}

bool
eth_addr_t::operator!=(eth_addr_t other) const {
   return !(*this == other);
}


eth_addr_t::operator bool() const {
   return !!(*this);
}

uint32_t
eth_addr_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
eth_addr_t::mix_me(hash_mix & h) const {
   h.mix_bytes((uint8_t const*)&bytes_[0], sizeof(bytes_));
}

std::ostream&
operator<<(std::ostream& os, const eth_addr_t& obj) {
   os << obj.to_string();
   return os;
}





invalid_vlan_error::invalid_vlan_error(vlan_id_t vlan) noexcept :
      error("0 and 4095 are reserved VLAN IDs"), vlan_(vlan) {

}


invalid_vlan_error::~invalid_vlan_error() noexcept {

}

vlan_id_t
invalid_vlan_error::vlan() const noexcept {
   return vlan_;
}

void
invalid_vlan_error::raise() const {
   throw *this;
}

uint32_t
invalid_vlan_error::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
invalid_vlan_error::mix_me(hash_mix & h) const {
   h.mix(vlan_); // vlan_id_t
}

std::string
invalid_vlan_error::to_string() const {
   std::ostringstream ss;
   ss << "invalid_vlan_error(";
   ss << "vlan=" << vlan_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const invalid_vlan_error& obj) {
   os << obj.to_string();
   return os;
}




internal_vlan_error::~internal_vlan_error() noexcept {

}

vlan_id_t
internal_vlan_error::vlan() const noexcept {
   return vlan_;
}

void
internal_vlan_error::raise() const {
   throw *this;
}

uint32_t
internal_vlan_error::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
internal_vlan_error::mix_me(hash_mix & h) const {
   h.mix(vlan_); // vlan_id_t
}

std::string
internal_vlan_error::to_string() const {
   std::ostringstream ss;
   ss << "internal_vlan_error(";
   ss << "vlan=" << vlan_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const internal_vlan_error& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_ETH_H
