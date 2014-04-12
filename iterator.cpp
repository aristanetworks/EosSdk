// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/acl.h"
#include "eos/decap_group.h"
#include "eos/directflow.h"
#include "eos/eth_intf.h"
#include "eos/eth_phy_intf.h"
#include "eos/intf.h"
#include "eos/ip_route.h"
#include "eos/iterator.h"
#include "eos/mpls_route.h"
#include "eos/nexthop_group.h"
#include "eos/policy.h"

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
inline T
iter_base<T, Impl>::operator*() const {
   return T();
}

template <typename T, typename Impl>
inline T const *
iter_base<T, Impl>::operator->() const {
   return 0;
}

template <typename T, typename Impl>
inline T *
iter_base<T, Impl>::operator->() {
   return 0;
}

template <typename T, typename Impl>
inline iter_base<T, Impl>::operator bool() const {
   return false;
}

template class iter_base<acl_key_t, acl_iter_impl>;
template class iter_base<acl_rule_eth_entry_t, acl_rule_eth_iter_impl>;
template class iter_base<acl_rule_ip_entry_t, acl_rule_ip_iter_impl>;
template class iter_base<intf_id_t, intf_iter_impl>;
template class iter_base<intf_id_t, eth_intf_iter_impl>;
template class iter_base<intf_id_t, eth_phy_intf_iter_impl>;
template class iter_base<ip_route_t, ip_route_iter_impl>;
template class iter_base<ip_route_via_t, ip_route_via_iter_impl>;
template class iter_base<decap_group_t, decap_group_iter_impl>;
template class iter_base<nexthop_group_t, nexthop_group_iter_impl>;
template class iter_base<flow_entry_t, flow_entry_iter_impl>;
template class iter_base<mpls_route_t, mpls_route_iter_impl>;
template class iter_base<mpls_route_via_t, mpls_route_via_iter_impl>;
template class iter_base<policy_map_t, policy_map_iter_impl>;
template class iter_base<std::pair<uint32_t, policy_map_rule_t>,
                         policy_map_rule_iter_impl>;

}
