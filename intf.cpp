// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/intf.h"
#include "impl.h"

namespace eos {

intf_handler::intf_handler(intf_mgr * mgr) : 
      base_handler<intf_mgr, intf_handler>(mgr) {
}

void
intf_handler::watch_all_intfs(bool all) {
   // TODO: No op impl.
}

void
intf_handler::watch_intf(intf_id_t, bool) {
   // TODO: No op impl.
}

void
intf_handler::on_intf_create(intf_id_t) {
   // TODO: No op impl.
}

void
intf_handler::on_intf_delete(intf_id_t) {
   // TODO: No op impl.
}

void
intf_handler::on_oper_status(intf_id_t, oper_status_t) {
   // TODO: No op impl.
}

void
intf_handler::on_admin_enabled(intf_id_t, bool) {
   // TODO: No op impl.
}

void
intf_handler::on_intf_description(intf_id_t, const std::string &) {
   // TODO: No op impl.
}

class intf_mgr_impl : public intf_mgr {
 public:
   intf_mgr_impl() {
   }

   void counters_accessible_is(bool accessible) {
      // TODO: No op impl.
   }
   
   intf_iter_t intf_iter() const {
      intf_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   bool exists(intf_id_t) const {
      return false;  // TODO: No op impl.
   }

   bool admin_enabled(intf_id_t id) const {
      return false;  // TODO: No op impl.
   }

   void admin_enabled_is(intf_id_t id, bool enabled) {
      // TODO: No op impl.
   }
   
   std::string description(intf_id_t) const {
      // TODO: No op impl.
      return "";
   }
   
   void description_is(intf_id_t, char const *) {
      // TODO: No op impl.
   }

   void description_is(intf_id_t, const std::string &) {
      // TODO: No op impl.
   }

   oper_status_t oper_status(intf_id_t) const {
      return INTF_OPER_NULL;  // TODO: No op impl.
   }
};

DEFINE_STUB_MGR_CTOR(intf_mgr)

class intf_counter_mgr_impl : public intf_counter_mgr {
 public:
   intf_counter_mgr_impl() {
   }
   
   intf_counters_t counters(intf_id_t) const {
      return intf_counters_t();
   }
   
   intf_traffic_rates_t traffic_rates(intf_id_t) const {
      return intf_traffic_rates_t();
   }
};

DEFINE_STUB_MGR_CTOR(intf_counter_mgr)

}
