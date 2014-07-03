// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_MPLS_H
#define INLINE_MPLS_H

#include <eos/exception.h>
#include <eos/panic.h>

namespace eos {

inline bool mpls_label_t::operator==(mpls_label_t const & other) const {
   return (label_ == other.label_);
}

inline bool mpls_label_t::operator!=(mpls_label_t const & other) const {
   return (label_ != other.label_);
}

inline bool mpls_label_t::operator<(mpls_label_t const & other) const {
   return (label_ < other.label_);
}

inline uint32_t mpls_label_t::label() const {
   return label_;
}

invalid_range_error invalid_mpls_label(uint32_t label) EOS_SDK_INTERNAL;

inline void mpls_label_t::label_is(uint32_t label) {
   if (label >= MAX) {
      panic(invalid_mpls_label(label));
   }
   label_ = label;
}

inline mpls_label_t::mpls_label_t(uint32_t label) {
   label_is(label);
}

}

#endif // INLINE_MPLS_H
