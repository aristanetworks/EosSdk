// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

/**
 * @file
 * Route Map management module.
 */

#ifndef EOS_ROUTE_MAP_H
#define EOS_ROUTE_MAP_H

#include <eos/sdk.h>
#include <eos/types/route_map.h>

namespace eos {

class EOS_SDK_PUBLIC route_map_mgr {
 public:
   virtual ~route_map_mgr();

#if !GUARD_ROUTE_MAP_SUPPORT
   virtual uint8_t priority() const = 0;
   virtual void priority_is(uint8_t) = 0;

   virtual route_map_t route_map(route_map_name_t const &) const = 0;
   virtual route_map_entry_t
      route_map_entry(route_map_name_t const &,
                      route_map_sequence_number_t const &) const = 0;

   virtual void route_map_set(route_map_t const &) = 0;
   virtual void route_map_entry_set(route_map_name_t const &,
                                    route_map_entry_t const &) = 0;

   virtual void route_map_del(route_map_name_t const &) = 0;
   virtual void route_map_entry_del(route_map_name_t const &,
                                    route_map_sequence_number_t const &) = 0;
#endif

 protected:
    route_map_mgr() EOS_SDK_PRIVATE;

 private:
    EOS_SDK_DISALLOW_COPY_CTOR(route_map_mgr);
};

} // namespace eos

#endif // EOS_ROUTE_MAP_H
