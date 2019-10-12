// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/nexthop_group.h"
#include "impl.h"

namespace eos {

class nexthop_group_mgr_impl : public nexthop_group_mgr {
 public:
   nexthop_group_mgr_impl() {
   }

   void resync_init() {
      // TODO: No op impl
   }

   void resync_complete() {
      // TODO: No op impl
   }

   nexthop_group_iter_t nexthop_group_iter() const {
      nexthop_group_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   nexthop_group_t nexthop_group(std::string const & nexthop_group_name) const {
      return nexthop_group_t();
   }

   nexthop_group_entry_counter_t counter(std::string const & nexthop_group_name, 
                             uint16_t entry) const {
      return nexthop_group_entry_counter_t();
   }

   bool exists(std::string const & nexthop_group_name) const {
      return false;
   }

   bool active(std::string const & nexthop_group_name) const {
      return true;
   }

   void nexthop_group_set(nexthop_group_t const &group) {
      // TODO: No op impl.
   }

   void nexthop_group_del(std::string const & group_name) {
      // TODO: No op impl.
   }

   programmed_nexthop_group_iter_t programmed_nexthop_group_iter() const {
      programmed_nexthop_group_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   nexthop_group_t programmed_nexthop_group(
         std::string const & nexthop_group_name) const {
      return nexthop_group_t();
   }

};

DEFINE_STUB_MGR_CTOR(nexthop_group_mgr);

nexthop_group_handler::nexthop_group_handler(nexthop_group_mgr * mgr) :
      base_handler<nexthop_group_mgr, nexthop_group_handler>(mgr) {
}

void
nexthop_group_handler::watch_all_nexthop_groups(bool interest) {
   // TODO: No op impl.
}

void
nexthop_group_handler::watch_nexthop_group(std::string const & group_name,
                                           bool interest) {
   // TODO: No op impl.
}

void
nexthop_group_handler::on_nexthop_group_active(std::string const & group_name,
                                               bool active) {
   // TODO: No op impl.
}

void
nexthop_group_handler::on_nexthop_group_programmed(std::string const & group_name) {
   // TODO: No op impl.
}

}
