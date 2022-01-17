// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/route_map.h"
#include "impl.h"

namespace eos {

class route_map_mgr_impl : public route_map_mgr {
 public:
   route_map_mgr_impl() {
   }

   route_map_t route_map(route_map_name_t const & name) const {
      return route_map_t(); // TODO: No op impl.
   }

   route_map_entry_t route_map_entry(route_map_name_t const & name,
                                     route_map_sequence_number_t sequence) const {
      return route_map_entry_t(); // TODO: No op impl.
   }

   void route_map_set(route_map_name_t const & name,
                      route_map_t const & map) {
      // TODO: No op impl.
   }
   void route_map_entry_set(route_map_name_t const & name,
                            route_map_sequence_number_t sequence,
                            route_map_entry_t const & entry) {
      // TODO: No op impl.
   }

   void route_map_del(route_map_name_t const & name) {
      // TODO: No op impl.
   }

   void route_map_entry_del(route_map_name_t const & name,
                            route_map_sequence_number_t sequence) {
      // TODO: No op impl.
   }

   uint8_t priority() const {
      return 0; // TODO: No op impl.
   }

   void priority_is(uint8_t priority) {
      // TODO: No op impl.
   }
};

DEFINE_STUB_MGR_CTOR(route_map_mgr)

} // namespace eos
