// Copyright (c) 2018 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/nexthop_group_tunnel.h"
#include "impl.h"

namespace eos {

class nexthop_group_tunnel_mgr_impl : public nexthop_group_tunnel_mgr {
 public:
   nexthop_group_tunnel_mgr_impl() {
   }

   void resync_init() {
      // TODO: No op impl
   }

   void resync_complete() {
      // TODO: No op impl
   }

   nexthop_group_tunnel_iter_t nexthop_group_tunnel_iter() const {
      nexthop_group_tunnel_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   nexthop_group_tunnel_t nexthop_group_tunnel(
                           ip_prefix_t const & tunnel_endpoint) const {
      return nexthop_group_tunnel_t();
   }

   bool exists(ip_prefix_t const & tunnel_endpoint) const {
      return false;
   }

   void nexthop_group_tunnel_set(nexthop_group_tunnel_t const & tunnel) {
      // TODO: No op impl.
   }

   void nexthop_group_tunnel_del(ip_prefix_t const & tunnel_endpoint) {
      // TODO: No op impl.
   }
};

DEFINE_STUB_MGR_CTOR(nexthop_group_tunnel_mgr);

nexthop_group_tunnel_handler::nexthop_group_tunnel_handler(
                                             nexthop_group_tunnel_mgr *mgr) : 
   base_handler(mgr) {
}

}
