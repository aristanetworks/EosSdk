// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_MPLS_H
#define INLINE_MPLS_H

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

}

#endif // INLINE_MPLS_H
