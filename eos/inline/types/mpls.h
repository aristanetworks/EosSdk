// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MPLS_H
#define EOS_INLINE_TYPES_MPLS_H

#include <eos/exception.h>
#include <eos/panic.h>

namespace eos {



EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const mpls_action_t & enum_val) {
   if (enum_val==MPLS_ACTION_NULL) {
      os << "MPLS_ACTION_NULL";
   } else if (enum_val==MPLS_ACTION_PUSH) {
      os << "MPLS_ACTION_PUSH";
   } else if (enum_val==MPLS_ACTION_POP) {
      os << "MPLS_ACTION_POP";
   } else if (enum_val==MPLS_ACTION_SWAP) {
      os << "MPLS_ACTION_SWAP";
   } else if (enum_val==MPLS_ACTION_FORWARD) {
      os << "MPLS_ACTION_FORWARD";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const mpls_ttl_mode_t & enum_val) {
   if (enum_val==MPLS_TTLMODE_NULL) {
      os << "MPLS_TTLMODE_NULL";
   } else if (enum_val==MPLS_TTLMODE_PIPE) {
      os << "MPLS_TTLMODE_PIPE";
   } else if (enum_val==MPLS_TTLMODE_UNIFORM) {
      os << "MPLS_TTLMODE_UNIFORM";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const mpls_payload_type_t & enum_val) {
   if (enum_val==MPLS_PAYLOAD_TYPE_NULL) {
      os << "MPLS_PAYLOAD_TYPE_NULL";
   } else if (enum_val==MPLS_PAYLOAD_TYPE_MPLS) {
      os << "MPLS_PAYLOAD_TYPE_MPLS";
   } else if (enum_val==MPLS_PAYLOAD_TYPE_IPV4) {
      os << "MPLS_PAYLOAD_TYPE_IPV4";
   } else if (enum_val==MPLS_PAYLOAD_TYPE_IPV6) {
      os << "MPLS_PAYLOAD_TYPE_IPV6";
   } else if (enum_val==MPLS_PAYLOAD_TYPE_GUESS) {
      os << "MPLS_PAYLOAD_TYPE_GUESS";
   } else {
      os << "Unknown value";
   }
   return os;
}


mpls_label_t::mpls_label_t(uint32_t label) :
      label_(label) {
   if (label > INVALID) {
      panic(invalid_mpls_label(label));
   }
}

uint32_t
mpls_label_t::label() const {
   return label_;
}

void
mpls_label_t::label_is(uint32_t label) {
   if (label > INVALID) {
      panic(invalid_mpls_label(label));
   }
   label_ = label;
}

std::string
mpls_label_t::to_string() const {
   return std::to_string(label_);
}

bool
mpls_label_t::operator==(mpls_label_t const & other) const {
   return label_ == other.label_;
}

bool
mpls_label_t::operator!=(mpls_label_t const & other) const {
   return !operator==(other);
}

bool
mpls_label_t::operator<(mpls_label_t const & other) const {
   if(label_ != other.label_) {
      return label_ < other.label_;
   }
   return false;
}

uint32_t
mpls_label_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
mpls_label_t::mix_me(hash_mix & h) const {
   h.mix(label_); // uint32_t
}

std::ostream&
operator<<(std::ostream& os, const mpls_label_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_MPLS_H
