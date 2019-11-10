// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/bgp_path.h"
#include "impl.h"

namespace eos {

class bgp_path_mgr_impl : public bgp_path_mgr {
 public:
   bgp_path_iter_t ipv6_unicast_path_iter(bgp_path_options_t & options) const {
      bgp_path_iter_t *nop = 0;
      return *nop;
   }
};

DEFINE_STUB_MGR_CTOR(bgp_path_mgr)

} // namespace eos
