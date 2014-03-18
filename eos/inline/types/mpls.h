// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MPLS_H
#define EOS_INLINE_TYPES_MPLS_H

#include <eos/exception.h>
#include <eos/panic.h>

namespace eos {

invalid_range_error invalid_mpls_label(uint32_t label) EOS_SDK_INTERNAL;


inline mpls_label_t::mpls_label_t(uint32_t label) :
      label_(label) {
}

inline uint32_t
mpls_label_t::label() const {
   return label_;
}

inline void
mpls_label_t::label_is(uint32_t label) {
   if (label >= MAX) {
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
