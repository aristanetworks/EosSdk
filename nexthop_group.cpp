// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/nexthop_group.h"

namespace eos {

void
nexthop_group_t::destination_ip_is(uint8_t i, ip_addr_t const & addr) {
   // TODO: no-op impl.
}

class nexthop_group_mgr_impl : public nexthop_group_mgr {
 public:
   nexthop_group_mgr_impl() {
   }
};

nexthop_group_mgr::nexthop_group_mgr() {
}

void
nexthop_group_mgr::resync_init() {
   // TODO: No op impl
}

void
nexthop_group_mgr::resync_complete() {
   // TODO: No op impl
}

nexthop_group_iter_t
nexthop_group_mgr::nexthop_group_iter() const {
   nexthop_group_iter_t * nop = 0;
   return *nop;  // TODO: No op impl.
}

void
nexthop_group_mgr::nexthop_group_set(nexthop_group_t const &group) {
   // TODO: No op impl.
}

void
nexthop_group_mgr::nexthop_group_del(std::string const & group_name) {
   // TODO: No op impl.
}

nexthop_group_mgr *
get_nexthop_group_mgr() {
   static nexthop_group_mgr_impl impl;
   return &impl;
}

}
