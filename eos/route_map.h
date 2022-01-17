// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

/**
 * @file
 * Route Map management module.
 *
 * Route map is a ordered set of route map entry statement that manage the
 * redistribution of IP routes into the protocol domain and modify the attrbutes of
 * routes.
 *
 * This module provides APIs to query Route Map information.
 *
 */

#ifndef EOS_ROUTE_MAP_H
#define EOS_ROUTE_MAP_H

#include <eos/sdk.h>
#include <eos/types/route_map.h>

namespace eos {

/**
 * A manager of route map configurations.
 *
 * A example of the API usage is in example/RouteMapAgent.cpp
 *
 */
class EOS_SDK_PUBLIC route_map_mgr {
 public:
   virtual ~route_map_mgr();

#if !GUARD_ROUTE_MAP_SUPPORT
   /// Returns the priority value of eossdk route map configuration.
   virtual uint8_t priority() const = 0;

   /// Configures the priority value of eossdk route map configuration.
   virtual void priority_is(uint8_t) = 0;

   /**
    * Returns a eossdk route map with corresponding route map name, which contains
    * route map entries. Returns an empty route_map_t if no matching route map was
    * found.
    */
   virtual route_map_t route_map(route_map_name_t const &) const = 0;

   /**
    * Returns a route map entry with the corresponding sequence number in
    * corresponding route map. Returns an empty route_map_entry_t if no matching
    * route map entry was found.
    */
   virtual route_map_entry_t
      route_map_entry(route_map_name_t const &,
                      route_map_sequence_number_t) const = 0;

   /// Creates or updates a route map.
   virtual void route_map_set(route_map_name_t const &,
                              route_map_t const &) = 0;

   /// Creates or updates a route map entry in corresponding route map.
   virtual void route_map_entry_set(route_map_name_t const &,
                                    route_map_sequence_number_t,
                                    route_map_entry_t const &) = 0;

   /// Removes the corresponding route map from the configuration if exists.
   virtual void route_map_del(route_map_name_t const &) = 0;

   /// Removes the corresponding route map entry from a given route map.
   virtual void route_map_entry_del(route_map_name_t const &,
                                    route_map_sequence_number_t) = 0;
#endif

 protected:
    route_map_mgr() EOS_SDK_PRIVATE;

 private:
    EOS_SDK_DISALLOW_COPY_CTOR(route_map_mgr);
};

} // namespace eos

#endif // EOS_ROUTE_MAP_H
