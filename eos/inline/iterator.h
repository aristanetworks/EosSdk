// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_ITERATOR_H
#define EOS_INLINE_ITERATOR_H

namespace eos {

template <typename T, typename Impl>
inline bool
iter_base<T, Impl>::operator!=(iter_base<T, Impl> const & rhs) const {
   return !(*this == rhs);
}

}

#endif // EOS_INLINE_ITERATOR_H
