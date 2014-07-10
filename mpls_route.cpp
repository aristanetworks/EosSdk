// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/mpls_route.h"
#include "impl.h"

namespace eos {

class mpls_route_mgr_impl : public mpls_route_mgr {
 public:
   mpls_route_mgr_impl() {
   }

   void resync_init() {
      // TODO: No op impl
   }

   void resync_complete() {
      // TODO: No op impl
   }

   mpls_route_iter_t mpls_route_iter() const {
      mpls_route_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   bool exists(mpls_route_key_t const & route_key) const {
      return false;  // TODO: No op impl.
   }

   bool exists(mpls_route_via_t const & route_via) const {
      return false;  // TODO: No op impl.
   }

   void mpls_route_set(mpls_route_t const & route) {
      // TODO: No op impl.
   }

   void mpls_route_via_set(mpls_route_via_t const & route_via) {
      // TODO: No op impl.
   }

   void mpls_route_del(mpls_route_key_t const & route_key) {
      // TODO: No op impl.
   }

   void mpls_route_via_del(mpls_route_via_t const & route_via) {
      // TODO: No op impl.
   }

   mpls_route_via_iter_t mpls_route_via_iter(mpls_route_key_t const & key) const {
      mpls_route_via_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

};

DEFINE_STUB_MGR_CTOR(mpls_route_mgr)

}  // end namespace eos
