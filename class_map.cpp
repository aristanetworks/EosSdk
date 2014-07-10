// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/class_map.h"
#include "impl.h"

namespace eos {

class class_map_mgr_impl : public class_map_mgr {
 public:
   class_map_mgr_impl() {
   }

   void resync_init() {
   }

   void resync_complete() {
   }

   bool exists(class_map_key_t const & key) const {
      return true;
   }

   class_map_t class_map(class_map_key_t const & key) const {
      return class_map_t();
   }

   void class_map_is(class_map_t const & class_map) {
   }

   class_map_iter_t class_map_iter(policy_feature_t) const {
      class_map_iter_t * nop = 0;
      return *nop;
   }

   void class_map_del(class_map_key_t const & key) {
   }
};

DEFINE_STUB_MGR_CTOR(class_map_mgr)

}
