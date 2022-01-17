// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_SUBINTF_H
#define EOS_INLINE_TYPES_SUBINTF_H

namespace eos {

// Default constructor.
inline subintf_t::subintf_t() :
      intf_id_(intf_id_t()), vlan_id_(vlan_id_t()) {
}

inline subintf_t::subintf_t(intf_id_t intf_id, vlan_id_t vlan_id) :
      intf_id_(intf_id), vlan_id_(vlan_id) {
}

inline intf_id_t
subintf_t::intf_id() const {
   return intf_id_;
}

inline vlan_id_t
subintf_t::vlan_id() const {
   return vlan_id_;
}

inline void
subintf_t::vlan_id_is(vlan_id_t vlan_id) {
   vlan_id_ = vlan_id;
}

inline bool
subintf_t::operator==(subintf_t const & other) const {
   return intf_id_ == other.intf_id_ &&
          vlan_id_ == other.vlan_id_;
}

inline bool
subintf_t::operator!=(subintf_t const & other) const {
   return !operator==(other);
}

inline uint32_t
subintf_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
subintf_t::mix_me(hash_mix & h) const {
   h.mix(intf_id_); // intf_id_t
   h.mix(vlan_id_); // vlan_id_t
}

inline std::string
subintf_t::to_string() const {
   std::ostringstream ss;
   ss << "subintf_t(";
   ss << "intf_id=" << intf_id_;
   ss << ", vlan_id=" << vlan_id_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const subintf_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_SUBINTF_H
