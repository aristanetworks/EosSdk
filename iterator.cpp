// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/iterator.h"
#include "eos/decap_group.h"
#include "eos/mpls_route.h"

namespace eos {

template <typename T, typename Impl>
inline iter_base<T, Impl>::iter_base(Impl * const impl)
   : impl(impl) {
}

template <typename T, typename Impl>
inline iter_base<T, Impl>::iter_base(iter_base<T, Impl> const & other)
   : impl(0) {
}

template <typename T, typename Impl>
inline iter_base<T, Impl>::~iter_base() {
}

template <typename T, typename Impl>
inline iter_base<T, Impl>&
iter_base<T, Impl>::operator++() {
   return *this;
}

template <typename T, typename Impl>
inline bool
iter_base<T, Impl>::operator==(const iter_base<T, Impl> & rhs) const {
   return impl == rhs.impl;
}

template <typename T, typename Impl>
inline bool
iter_base<T, Impl>::operator!=(const iter_base<T, Impl> & rhs) const {
   return impl != rhs.impl;
}

template <typename T, typename Impl>
inline T
iter_base<T, Impl>::operator*() {
   return T();
}

template <typename T, typename Impl>
inline iter_base<T, Impl>::operator bool() const {
   return false;
}

template class iter_base<decap_group_t, decap_group_iter_impl>;
template class iter_base<mpls_route_t, mpls_route_iter_impl>;

}
