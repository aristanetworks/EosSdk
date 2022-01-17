// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MPLS_VRF_LABEL_H
#define EOS_INLINE_TYPES_MPLS_VRF_LABEL_H

namespace eos {

// Default constructor.
inline mpls_vrf_label_t::mpls_vrf_label_t() :
      label_(), vrf_name_() {
}

inline mpls_vrf_label_t::mpls_vrf_label_t(mpls_label_t label, std::string vrf_name) :
      label_(label), vrf_name_(vrf_name) {
}

inline mpls_label_t
mpls_vrf_label_t::label() const {
   return label_;
}

inline std::string
mpls_vrf_label_t::vrf_name() const {
   return vrf_name_;
}

inline bool
mpls_vrf_label_t::operator==(mpls_vrf_label_t const & other) const {
   return label_ == other.label_ &&
          vrf_name_ == other.vrf_name_;
}

inline bool
mpls_vrf_label_t::operator!=(mpls_vrf_label_t const & other) const {
   return !operator==(other);
}

inline bool
mpls_vrf_label_t::operator<(mpls_vrf_label_t const & other) const {
   if(label_ != other.label_) {
      return label_ < other.label_;
   } else if(vrf_name_ != other.vrf_name_) {
      return vrf_name_ < other.vrf_name_;
   }
   return false;
}

inline uint32_t
mpls_vrf_label_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
mpls_vrf_label_t::mix_me(hash_mix & h) const {
   h.mix(label_); // mpls_label_t
   h.mix(vrf_name_); // std::string
}

inline std::string
mpls_vrf_label_t::to_string() const {
   std::ostringstream ss;
   ss << "mpls_vrf_label_t(";
   ss << "label=" << label_;
   ss << ", vrf_name='" << vrf_name_ << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const mpls_vrf_label_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_MPLS_VRF_LABEL_H
