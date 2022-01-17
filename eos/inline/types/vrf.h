// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_VRF_H
#define EOS_INLINE_TYPES_VRF_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const vrf_state_t & enum_val) {
   if (enum_val==VRF_NULL) {
      os << "VRF_NULL";
   } else if (enum_val==VRF_INITIALIZING) {
      os << "VRF_INITIALIZING";
   } else if (enum_val==VRF_ACTIVE) {
      os << "VRF_ACTIVE";
   } else if (enum_val==VRF_DELETING) {
      os << "VRF_DELETING";
   } else {
      os << "Unknown value";
   }
   return os;
}



// Default constructor.
inline vrf_t::vrf_t() :
      name_(""), state_(VRF_NULL), rd_(0) {
}

inline vrf_t::vrf_t(std::string name, vrf_state_t state, uint64_t rd) :
      name_(name), state_(state), rd_(rd) {
}

inline std::string
vrf_t::name() const {
   return name_;
}

inline vrf_state_t
vrf_t::state() const {
   return state_;
}

inline uint64_t
vrf_t::rd() const {
   return rd_;
}

inline bool
vrf_t::operator==(vrf_t const & other) const {
   return name_ == other.name_ &&
          state_ == other.state_ &&
          rd_ == other.rd_;
}

inline bool
vrf_t::operator!=(vrf_t const & other) const {
   return !operator==(other);
}

inline bool
vrf_t::operator<(vrf_t const & other) const {
   if(name_ != other.name_) {
      return name_ < other.name_;
   } else if(state_ != other.state_) {
      return state_ < other.state_;
   } else if(rd_ != other.rd_) {
      return rd_ < other.rd_;
   }
   return false;
}

inline uint32_t
vrf_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
vrf_t::mix_me(hash_mix & h) const {
   h.mix(name_); // std::string
   h.mix(state_); // vrf_state_t
   h.mix(rd_); // uint64_t
}

inline std::string
vrf_t::to_string() const {
   std::ostringstream ss;
   ss << "vrf_t(";
   ss << "name='" << name_ << "'";
   ss << ", state=" << state_;
   ss << ", rd=" << rd_;
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
