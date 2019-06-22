// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MPLS_H
#define EOS_INLINE_TYPES_MPLS_H

#include <eos/exception.h>
#include <eos/panic.h>

namespace eos {

invalid_range_error invalid_mpls_label(uint32_t label) EOS_SDK_INTERNAL;


inline std::ostream&
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



inline std::ostream&
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



inline std::ostream&
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



inline mpls_label_t::mpls_label_t(uint32_t label) :
      label_(label) {
   if (label > INVALID) {
      panic(invalid_mpls_label(label));
   }
}

inline uint32_t
mpls_label_t::label() const {
   return label_;
}

inline void
mpls_label_t::label_is(uint32_t label) {
   if (label > INVALID) {
      panic(invalid_mpls_label(label));
   }
   label_ = label;
}

inline bool
mpls_label_t::operator==(mpls_label_t const & other) const {
   return label_ == other.label_;
}

inline bool
mpls_label_t::operator!=(mpls_label_t const & other) const {
   return !operator==(other);
}

inline bool
mpls_label_t::operator<(mpls_label_t const & other) const {
   if(label_ != other.label_) {
      return label_ < other.label_;
   }
   return false;
}

inline uint32_t
mpls_label_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&label_,
              sizeof(uint32_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
mpls_label_t::to_string() const {
   std::ostringstream ss;
   ss << "mpls_label_t(";
   ss << "label=" << label_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const mpls_label_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_MPLS_H
