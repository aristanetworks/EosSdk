// Copyright (c) 2017 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/macsec.h"
#include "impl.h"

namespace eos{

// macsec_handler methods
macsec_handler::macsec_handler(macsec_mgr * mgr) :
      base_handler<macsec_mgr, macsec_handler>(mgr) {
}

void macsec_handler::watch_all_intfs(bool interest) {
   // TODO: No op impl.
}

void macsec_handler::watch_intf(intf_id_t intf_id, bool interest) {
   // TODO: No op impl.
}

void macsec_handler::on_intf_status(intf_id_t intf_id,
                                    macsec_intf_status_t const & status) {
}

// macsec_mgr methods
class macsec_mgr_impl : public macsec_mgr {
 public:
   macsec_mgr_impl() {
   }

   bool exists(macsec_profile_name_t const & profile_name) const {
      return false;
   }

   macsec_profile_t profile(macsec_profile_name_t const & profile_name) const {
      macsec_profile_t * nop = 0;
      return *nop; // TODO: No op impl
   }

   void profile_set(macsec_profile_t const & profile) {
      return; // TODO: No op impl
   }

   void profile_del(macsec_profile_name_t const & profile_name) {
      return; // TODO: No op impl
   }

   macsec_profile_name_t intf_profile(intf_id_t intf_id) const {
      macsec_profile_name_t * nop = 0;
      return *nop; // TODO: No op impl
   }

   void intf_profile_is(intf_id_t intf_id,
                        macsec_profile_name_t const & profile_name) {
      return; // TODO: No op impl
   }

   macsec_intf_status_t intf_status(intf_id_t intf_id) const {
      macsec_intf_status_t * nop = 0;
      return *nop; // TODO: No op impl
   }

   bool macsec_capable(intf_id_t intf_id) const {
      return false; // TODO: No op impl
   }

   macsec_intf_counters_t intf_counters(intf_id_t intf_id) {
      macsec_intf_counters_t * nop = 0;
      return *nop; // TODO: No op impl
   }

   macsec_profile_iter_t macsec_profile_iter() const {
      macsec_profile_iter_t *nop = 0;
      return *nop; // TODO: No op impl
   }

   macsec_intf_status_iter_t macsec_intf_status_iter() const {
      macsec_intf_status_iter_t *nop = 0;
      return *nop; // TODO: No op impl
   }
};

DEFINE_STUB_MGR_CTOR(macsec_mgr)

}
