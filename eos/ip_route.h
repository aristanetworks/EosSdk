// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_IP_ROUTE_H
#define EOS_IP_ROUTE_H

#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/iterator.h>
#include <eos/mpls.h>

#include <eos/types/ip_route.h>

namespace eos {

class ip_route_iter_impl;

/// An IP route iterator
class EOS_SDK_PUBLIC ip_route_iter_t : public iter_base<ip_route_t,
                                                        ip_route_iter_impl> {
 private:
   friend class ip_route_iter_impl;
   explicit ip_route_iter_t(ip_route_iter_impl * const) EOS_SDK_PRIVATE;
};


class ip_route_via_iter_impl;

/// A route via iterator
class EOS_SDK_PUBLIC ip_route_via_iter_t : public iter_base<ip_route_via_t,
                                                            ip_route_via_iter_impl> {
 private:
   friend class ip_route_via_iter_impl;
   explicit ip_route_via_iter_t(ip_route_via_iter_impl * const) EOS_SDK_PRIVATE;
};

/// The manager for IP static route configuration
class EOS_SDK_PUBLIC ip_route_mgr {
 public:
    virtual ~ip_route_mgr();

   /**
    * Set the manager to only interact with routes with the given tag.
    *
    * If this tag is set to a non-zero number, then methods on this
    * class will only affect or expose routes with the given tag.
    */
   virtual void tag_is(uint32_t) = 0;

   /// Returns the current tag, or 0 if no tag is set.
   virtual uint32_t tag() const = 0;

   /**
    * Resync provides a mechanism to set routes to a known state.
    *
    * To start a resync, call resync_init() and then use
    * ip_route_set() and ip_route_via_set() to populate the static
    * routing table with the known entries. After all entries have
    * been set, call resync_complete(), which will delete all existing
    * routes and vias that were not added or modified during resync.
    * If a tag is set, resync will only delete routes and vias
    * corresponding to the current tag.
    *
    * During resync, this manager will act like it is referencing a
    * temporary table that starts off empty. Thus, methods like exist,
    * del, and getters will act only on that temporary table,
    * regardless of the real values in Sysdb. The one exception is
    * iteration; they will traverse the table stored in Sysdb,
    * regardless of whether or not the manager is in resync mode.
    */
   virtual void resync_init() = 0;
   /// Completes any underway resync operation.
   virtual void resync_complete() = 0;

   /**
    * Iterates across all configured static routes.
    * If a tag is set, only return routes that match the current tag.
    */
   virtual ip_route_iter_t ip_route_iter() const = 0;

   /**
    * Iterates across configured static routes in the specified VRF.
    * returns empty iterator if the VRF does not exist.
    * If a tag is set, only return routes that match the current tag.
    */
   ip_route_iter_t ip_route_iter( std::string vrf ) const;

   /**
    * Iterates across configured nexthops for a given route key,
    * i.e., emit all ip_route_via_t's for a given route key. If a tag
    * is set, only return vias on routes that match the current tag.
    */
   virtual ip_route_via_iter_t ip_route_via_iter(ip_route_key_t const &) const = 0;
   virtual ip_route_via_iter_t ip_route_via_iter(ip_route_key_t const &,
                                                 std::string vrfName) const = 0;

   /**
    * Tests for existence of any routes matching the route key in the config.
    * If a tag is set and the route belongs to a different tag, this
    * function returns false.
    */
   virtual bool exists(ip_route_key_t const &) const = 0;
   virtual bool exists(ip_route_key_t const &, std::string vrfName) const = 0;
   /// Tests if the given via exists.
   virtual bool exists(ip_route_via_t const &) const = 0;
   virtual bool exists(ip_route_via_t const &, std::string vrfName) const = 0;

   // Route management functions

   /**
    * Gets the IP route with the corresponding ip_route_key_t. Returns
    * an empty ip_route_t() if no matching route is found.
    */
   virtual ip_route_t ip_route(ip_route_key_t const &) = 0;
   virtual ip_route_t ip_route(ip_route_key_t const &, std::string vrfName) = 0;
   /**
    * Inserts or updates a static route into the switch configuration.
    */
   virtual void ip_route_set(ip_route_t const &) = 0;
   /**
    * Performs the same operation as `ip_route_set`, but lets an agent
    * hint what type of vias will be attached to this route. For
    * example, if the agent knows it will be adding nexthop group vias
    * to this route, it can pass `eos::IP_ROUTE_ACTION_NEXTHOP_GROUP`,
    * which allows EOS to more efficiently program routes. Routes are
    * created by 'forward' routes if no additional information is
    * provided.
    */
   virtual void ip_route_set(ip_route_t const &,
                             ip_route_action_t expected_type) = 0;
   /**
    * Inserts or updates a static route for a given vrf into the
    * switch configuration.
    */
   virtual void ip_route_set(ip_route_t const &,
                             std::string vrfName) = 0;
   /**
    * Delete an existing static route for a given vrf from the
    * switch configuration.
    */
   virtual void ip_route_del(ip_route_key_t const &,
                             std::string vrfName) = 0;
   /// Removes all ECMP vias matching the route key, and the route itself.
   virtual void ip_route_del(ip_route_key_t const &) = 0;

   /**
    * Adds a via to an ip_route_t.
    *
    * A via is associated with an ip_route_t by their `ip_route_key_t`
    * attributes. If an agent adds multiple vias with a hop or intf set,
    * EOS will ECMP across these "forward" routes. If it programs a
    * 'drop' via (by setting the intf attribute to Null0), all other
    * vias attached to this route will be removed, and all traffic on
    * this route will be dropped. Similarly, if the nexthop_group
    * attribute is set, all other vias with the same `ip_route_key_t`
    * will be removed, and the new nexthop group via will be
    * programmed in their place. This function will call panic() if the
    * route does not match the currently configured tag.
    *
    * @throws eos::invalid_argument_error If the passed via has no IP
    * address, interface or nexthop group set.
    */
   virtual void ip_route_via_set(ip_route_via_t const &) = 0;
   virtual void ip_route_via_set(ip_route_via_t const &, std::string vrfName) = 0;
   /**
    * Removes a via from an ip_route_t.
    * When all vias are removed, the route still exists with no
    * nexthop information.
    */
   virtual void ip_route_via_del(ip_route_via_t const &) = 0;
   virtual void ip_route_via_del(ip_route_via_t const &, std::string vrfName) = 0;

 protected:
   ip_route_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(ip_route_mgr);
};

}  // end namespace eos

#endif // EOS_IP_ROUTE_H
