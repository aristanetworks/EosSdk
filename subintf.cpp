// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.


#include <cassert>
#include "eos/subintf.h"
#include "impl.h"

namespace eos {

class subintf_mgr_impl : public subintf_mgr {
 public:
   subintf_mgr_impl() {
   }

   subintf_iter_t subintf_iter() const {
      subintf_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   vlan_id_t vlan_tag(intf_id_t) const {
      return 0;  // TODO: No-op impl.
   }

   void vlan_tag_is(intf_id_t, vlan_id_t) {
      // TODO: No-op impl.
   }

   intf_id_t parent_intf(intf_id_t) const {
      return intf_id_t(); // TODO: No-op impl.
   }

   void subintf_is(intf_id_t) {
      // TODO: No-op impl.
   }

   void subintf_is(intf_id_t, vlan_id_t) {
      // TODO: No-op impl.
   }

   void subintf_del(intf_id_t) {
      return; // TODO: No-op impl.
   }

   subintf_t subintf(intf_id_t) const {
      subintf_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }
};

DEFINE_STUB_MGR_CTOR(subintf_mgr)

}
