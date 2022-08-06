// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/l1_source.h"
#include "impl.h"

namespace eos {

l1_source_handler::l1_source_handler(l1_source_mgr * mgr) :
         base_handler<l1_source_mgr, l1_source_handler>(mgr) {
}

void
l1_source_handler::watch_all_l1_source(bool interest) {
}

void
l1_source_handler::watch_l1_source(intf_id_t intf_id, bool interest) {
}

void
l1_source_handler::on_l1_source_set(intf_id_t intf_id) {
}

void
l1_source_handler::on_l1_source_del(intf_id_t intf_id) {
}

class l1_source_mgr_impl : public l1_source_mgr {
   public:
      l1_source_mgr_impl() {
      }

      void l1_source_is(intf_id_t intf_id, l1_source_t source) {
      }

      void l1_source_del(intf_id_t intf_id) {
      }

      bool exists(intf_id_t) const {
         return false;
      }

      l1_source_t l1_source_config(intf_id_t intf_id) {
         l1_source_t * nop = 0;
         return *nop;
      }

      l1_source_t l1_source_status(intf_id_t intf_id) {
         l1_source_t * nop = 0;
         return *nop;
      }

      l1_source_iter_t l1_source_config_iter() const {
         l1_source_iter_t * nop = 0;
         return *nop;
      }

      l1_source_iter_t l1_source_status_iter() const {
         l1_source_iter_t * nop = 0;
         return *nop;
      }
      
      void app_description_is(intf_id_t intf_id, std::string description) {
      }
      
      void app_description_del(intf_id_t intf_id) {
      }
};

DEFINE_STUB_MGR_CTOR(l1_source_mgr)

} // end namespace eos
