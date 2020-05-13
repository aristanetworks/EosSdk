// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/bgp.h>
#include <impl.h>

namespace eos {

class bgp_mgr_impl : public bgp_mgr {
 public:
   ~bgp_mgr_impl() {
   }

   bool exists(bgp_peer_key_t const & peer_key) const {
      return false;
   }

   bgp_peer_state_t peer_state(bgp_peer_key_t const & peer_key) const {
      bgp_peer_state_t *nop = 0;
      return *nop;
   }

};

DEFINE_STUB_MGR_CTOR(bgp_mgr)

bgp_peer_handler::bgp_peer_handler(bgp_mgr * mgr) : base_handler(mgr) {
}

void bgp_peer_handler::watch_all_peers(bool) {}

void bgp_peer_handler::watch_peer(bgp_peer_key_t const & peer_key, bool) {}

void bgp_peer_handler::on_peer_state(bgp_peer_key_t const & peer_key,
                                     bgp_peer_state_t peer_state) {}
void bgp_peer_handler::on_peer_set(bgp_peer_key_t const & peer_key) {}
void bgp_peer_handler::on_peer_del(bgp_peer_key_t const & peer_key) {}


} // namespace eos
