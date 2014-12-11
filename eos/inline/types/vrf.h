// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_VRF_H
#define EOS_INLINE_TYPES_VRF_H

namespace eos {

// Default constructor.
inline vrf_t::vrf_t() :
      name_(""), rd_(0), af_ipv4_(false), af_ipv6_(false) {
}

inline vrf_t::vrf_t(std::string name, uint64_t rd, bool af_ipv4, bool af_ipv6) :
      name_(name), rd_(rd), af_ipv4_(af_ipv4), af_ipv6_(af_ipv6) {
}

inline std::string
vrf_t::name() const {
   return name_;
}

inline uint64_t
vrf_t::rd() const {
   return rd_;
}

inline bool
vrf_t::af_ipv4() const {
   return af_ipv4_;
}

inline bool
vrf_t::af_ipv6() const {
   return af_ipv6_;
}

inline bool
vrf_t::operator==(vrf_t const & other) const {
   return name_ == other.name_ &&
          rd_ == other.rd_ &&
          af_ipv4_ == other.af_ipv4_ &&
          af_ipv6_ == other.af_ipv6_;
}

inline bool
vrf_t::operator!=(vrf_t const & other) const {
   return !operator==(other);
}

inline std::string
vrf_t::to_string() const {
   std::ostringstream ss;
   ss << "vrf_t(";
   ss << "name='" << name_ << "'";
   ss << ", rd=" << rd_;
   ss << ", af_ipv4=" << af_ipv4_;
   ss << ", af_ipv6=" << af_ipv6_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const vrf_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_VRF_H
