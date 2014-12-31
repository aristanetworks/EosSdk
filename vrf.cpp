// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/vrf.h>
#include <impl.h>

namespace eos {

/// The manager for Vrf
class vrf_mgr_impl : public vrf_mgr {
 public:
   ~vrf_mgr_impl() {
   }

   vrf_iter_t vrf_iter() const {
      vrf_iter_t * nop = 0;
      return *nop;
   }

   vrf_t vrf(std::string const & vrf_name) const {
      return vrf_t();
   }

   int socket_at(int domain, int type, int protocol, std::string const & vrf_name) {
      return 0;
   }

};

DEFINE_STUB_MGR_CTOR(vrf_mgr)

} // end namespace eos
