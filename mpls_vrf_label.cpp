// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/mpls_vrf_label.h"
#include "eos/panic.h"
#include "impl.h"

namespace eos {

class mpls_vrf_label_mgr_impl : public mpls_vrf_label_mgr {
 public:
    mpls_vrf_label_mgr_impl() {
    }

    void resync_init() {
       // TODO: No op impl
    }

    void resync_complete() {
       // TODO: No op impl
    }

    mpls_vrf_label_iter_t mpls_vrf_label_iter() const {
       mpls_vrf_label_iter_t * nop = 0;
       return *nop;  // TODO: No op impl.
    }

   mpls_vrf_label_t mpls_vrf_label(mpls_label_t const & label) const {
      return mpls_vrf_label_t();
   }

    void mpls_vrf_label_set(mpls_vrf_label_t const & vrf_label) {
       if(vrf_label.vrf_name().empty()) {
          panic("empty VRF name");
       // TODO: No op impl.
       }
    }

    void mpls_vrf_label_del(mpls_label_t const & label) {
       // TODO: No op impl.
    }
};

DEFINE_STUB_MGR_CTOR(mpls_vrf_label_mgr)

};  // end namespace eos
