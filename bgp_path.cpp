// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/bgp_path.h"
#include "impl.h"

namespace eos {

class bgp_path_mgr_impl : public bgp_path_mgr {
 public:
   bgp_path_iter_t ipv4_unicast_path_iter(bgp_path_options_t & options) const {
      bgp_path_iter_t *nop = 0;
      return *nop;
   }

   bgp_path_t ipv4_unicast_path(bgp_path_key_t const & path_key,
                                bgp_path_options_t & options) {
      return bgp_path_t();
   }

   bool ipv4_unicast_bgp_convergence() {
      return false;
   }

   bgp_path_iter_t ipv6_unicast_path_iter(bgp_path_options_t & options) const {
      bgp_path_iter_t *nop = 0;
      return *nop;
   }

   bgp_path_t ipv6_unicast_path(bgp_path_key_t const & path_key,
                                bgp_path_options_t & options) {
      return bgp_path_t();
   }

   bool ipv6_unicast_bgp_convergence() {
      return false;
   }
};

DEFINE_STUB_MGR_CTOR(bgp_path_mgr)

bgp_path_handler::bgp_path_handler(bgp_path_mgr * mgr) :
      base_handler<bgp_path_mgr, bgp_path_handler>(mgr) {
}

void bgp_path_handler::watch_all_paths(bool) {}

void bgp_path_handler::on_ipv4_unicast_path(bgp_path_key_t path_key) {}

void bgp_path_handler::on_ipv4_unicast_bgp_converged(bool converged) {}

void bgp_path_handler::on_ipv6_unicast_path(bgp_path_key_t path_key) {}

void bgp_path_handler::on_ipv6_unicast_bgp_converged(bool converged) {}

} // namespace eos
