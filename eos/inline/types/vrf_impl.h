// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_VRF_IMPL_H
#define EOS_INLINE_TYPES_VRF_IMPL_H

namespace eos {



// Default constructor.
vrf_impl_t::vrf_impl_t() :
      name_(""), state_(VRF_NULL), rd_(0) {
}

vrf_impl_t::vrf_impl_t(std::string name, vrf_state_t state, uint64_t rd) :
      name_(name), state_(state), rd_(rd) {
}

std::string
vrf_impl_t::name() const {
   return name_;
}

vrf_state_t
vrf_impl_t::state() const {
   return state_;
}

uint64_t
vrf_impl_t::rd() const {
   return rd_;
}

bool
vrf_impl_t::operator==(vrf_impl_t const & other) const {
   return name_ == other.name_ &&
          state_ == other.state_ &&
          rd_ == other.rd_;
}

bool
vrf_impl_t::operator!=(vrf_impl_t const & other) const {
   return !operator==(other);
}

bool
vrf_impl_t::operator<(vrf_impl_t const & other) const {
   if(name_ != other.name_) {
      return name_ < other.name_;
   } else if(state_ != other.state_) {
      return state_ < other.state_;
   } else if(rd_ != other.rd_) {
      return rd_ < other.rd_;
   }
   return false;
}

uint32_t
vrf_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
vrf_impl_t::mix_me(hash_mix & h) const {
   h.mix(name_); // std::string
   h.mix(state_); // vrf_state_t
   h.mix(rd_); // uint64_t
}

std::string
vrf_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "vrf_t(";
   ss << "name='" << name_ << "'";
   ss << ", state=" << state_;
   ss << ", rd=" << rd_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const vrf_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/vrf.h>

#endif // EOS_INLINE_TYPES_VRF_IMPL_H
