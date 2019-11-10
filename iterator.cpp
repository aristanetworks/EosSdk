// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/acl.h"
#include "eos/agent.h"
#include "eos/bfd.h"
#include "eos/bgp_path.h"
#include "eos/class_map.h"
#include "eos/decap_group.h"
#include "eos/directflow.h"
#include "eos/eth_intf.h"
#include "eos/eth_lag_intf.h"
#include "eos/eth_phy_intf.h"
#include "eos/fib.h"
#include "eos/hardware_table.h"
#include "eos/intf.h"
#include "eos/ip_route.h"
#include "eos/iterator.h"
#include "eos/mac_table.h"
#include "eos/mpls_route.h"
#include "eos/mpls_vrf_label.h"
#include "eos/neighbor_table.h"
#include "eos/nexthop_group.h"
#include "eos/policy_map.h"
#include "eos/subintf.h"
#include "eos/vrf.h"
#include "eos/lldp.h"
#include "eos/nexthop_group_tunnel.h"

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
iter_base<T, Impl>::operator=(const iter_base<T, Impl> & other) {
   if (this != &other) {
      delete impl;
      impl = new Impl(*other.impl);
   }
   return *this;
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


/**
 * Helper macro to define iterator classes that wrap our internal iterators.
 * @param SdkIter Tke name of the SDK iterator (e.g. foo_iter_t).
 * @param IterClassImpl The name of the SDK wrapper class (e.g. foo_iter_impl).
 * TODO: Right now in the stubs the impl class is empty because iter_base does
 * not delegate anything to it yet.  We need to make iter_base delegate calls
 * to the impl class, and provide a stub implementation.
 * NOTE: The impl class needs to be marked with EOS_SDK_PUBLIC because as of
 * GCC 4.6, if a template parameter has hidden visibility, it contaminates the
 * template class, even if that class was marked as having default visibility.
 */
#define INSTANTIATE_ITERATOR(SdkIter, IterClassImpl)    \
  struct EOS_SDK_PUBLIC IterClassImpl {                 \
     virtual ~IterClassImpl() EOS_SDK_PRIVATE;          \
  };                                                    \
  IterClassImpl::~IterClassImpl() {}                    \
  template class iter_base<SdkIter, IterClassImpl>

INSTANTIATE_ITERATOR(acl_key_t, acl_iter_impl);
INSTANTIATE_ITERATOR(acl_rule_eth_entry_t, acl_rule_eth_iter_impl);
INSTANTIATE_ITERATOR(acl_rule_ip_entry_t, acl_rule_ip_iter_impl);
INSTANTIATE_ITERATOR(std::string, agent_option_iter_impl);
INSTANTIATE_ITERATOR(std::string, agent_status_iter_impl);
INSTANTIATE_ITERATOR(bfd_session_key_t, bfd_session_iter_impl);
INSTANTIATE_ITERATOR(bgp_path_t, bgp_path_iter_impl);
INSTANTIATE_ITERATOR(class_map_key_t, class_map_iter_impl);
INSTANTIATE_ITERATOR(decap_group_t, decap_group_iter_impl);
INSTANTIATE_ITERATOR(fib_fec_t, fib_fec_iter_impl);
INSTANTIATE_ITERATOR(fib_route_t, fib_route_iter_impl);
INSTANTIATE_ITERATOR(flow_entry_t, flow_entry_iter_impl);
INSTANTIATE_ITERATOR(hardware_table_key_t, hardware_table_iter_impl);
INSTANTIATE_ITERATOR(intf_id_t, intf_iter_impl);
INSTANTIATE_ITERATOR(intf_id_t, eth_intf_iter_impl);
INSTANTIATE_ITERATOR(intf_id_t, eth_lag_intf_iter_impl);
INSTANTIATE_ITERATOR(intf_id_t, eth_lag_intf_member_iter_impl);
INSTANTIATE_ITERATOR(intf_id_t, eth_phy_intf_iter_impl);
INSTANTIATE_ITERATOR(ip_route_t, ip_route_iter_impl);
INSTANTIATE_ITERATOR(ip_route_via_t, ip_route_via_iter_impl);
INSTANTIATE_ITERATOR(mac_key_t, mac_table_iter_impl);
INSTANTIATE_ITERATOR(mac_key_t, mac_table_status_iter_impl);
INSTANTIATE_ITERATOR(mpls_route_t, mpls_route_iter_impl);
INSTANTIATE_ITERATOR(mpls_route_key_t, mpls_route_status_iter_impl);
INSTANTIATE_ITERATOR(mpls_route_via_t, mpls_route_via_iter_impl);
INSTANTIATE_ITERATOR(mpls_route_via_t, mpls_route_via_status_iter_impl);
INSTANTIATE_ITERATOR(mpls_vrf_label_t, mpls_vrf_label_iter_impl);
INSTANTIATE_ITERATOR(neighbor_key_t, neighbor_table_iter_impl);
INSTANTIATE_ITERATOR(neighbor_key_t, neighbor_table_status_iter_impl);
INSTANTIATE_ITERATOR(nexthop_group_t, nexthop_group_iter_impl);
INSTANTIATE_ITERATOR(policy_map_key_t, policy_map_iter_impl);
INSTANTIATE_ITERATOR(intf_id_t, subintf_iter_impl);
INSTANTIATE_ITERATOR(std::string, vrf_iter_impl);
INSTANTIATE_ITERATOR(lldp_remote_system_t, lldp_remote_system_iter_impl);
INSTANTIATE_ITERATOR(intf_id_t, lldp_intf_iter_impl);
INSTANTIATE_ITERATOR(lldp_neighbor_t, lldp_neighbor_iter_impl);
INSTANTIATE_ITERATOR(nexthop_group_tunnel_t, nexthop_group_tunnel_iter_impl);
INSTANTIATE_ITERATOR(std::string, programmed_nexthop_group_iter_impl);

}
