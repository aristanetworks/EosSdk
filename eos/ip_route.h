// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_IP_ROUTE_H
#define EOS_IP_ROUTE_H

#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/iterator.h>

namespace eos {

typedef uint32_t ip_route_tag_t;
typedef uint32_t ip_route_metric_t;
typedef uint8_t ip_route_preference_t;

class EOS_SDK_PUBLIC ip_route_key_t {
 public:
   ip_route_key_t();
   explicit ip_route_key_t(ip_prefix_t const &);
   ip_route_key_t(ip_prefix_t const &, ip_route_preference_t);

   ip_prefix_t prefix;                // IP v4/v6 network prefix
   ip_route_preference_t preference;  // 0..255 only, defaults to 1
   ip_route_metric_t metric;
};

// An IP v4/v6 static route.
// Nexthop "via" for this route are stored separately
class EOS_SDK_PUBLIC ip_route_t {
 public:
   ip_route_t();
   explicit ip_route_t(ip_route_key_t const & route_key);

   ip_route_key_t key;

   ip_route_tag_t tag;       // A numbered tag, useful for classifying routes
   bool persistent;          // If true, the route is stored to startup-config
};

// A via entry, describing nexthop information
class EOS_SDK_PUBLIC ip_route_via_t {
 public:
   ip_route_via_t();
   explicit ip_route_via_t(ip_route_key_t const & route_key);

   ip_route_key_t route_key; // Key for the route this via is attached to
   ip_addr_t hop;            // IP v4/v6 nexthop address
   intf_id_t intf;           // Use the named interface if not a default intf_id_t
   // using intf Null0 installs a 'drop' route for the given prefix and preference
};


class ip_route_iter_impl;

class EOS_SDK_PUBLIC ip_route_iter_t : public iter_base<ip_route_t,
                                                        ip_route_iter_impl> {
 private:
   friend class ip_route_iter_impl;
   explicit ip_route_iter_t(ip_route_iter_impl * const) EOS_SDK_PRIVATE;
};


class ip_route_via_iter_impl;

class EOS_SDK_PUBLIC ip_route_via_iter_t : public iter_base<ip_route_via_t,
                                                            ip_route_via_iter_impl> {
 private:
   friend class ip_route_via_iter_impl;
   explicit ip_route_via_iter_t(ip_route_via_iter_impl * const) EOS_SDK_PRIVATE;
};


// Manages IP static route configuration
class EOS_SDK_PUBLIC ip_route_mgr {
 public:
   // Set the manager to only interact with routes with the given
   // tag. If this tag is set to a non-zero number, then methods on
   // this class will only affect or expose routes with the given tag.
   void tag_is(uint32_t);
   // Returns the current tag, or 0 if no tag is set.
   uint32_t tag() const;

   // Resync provides a mechanism to set the static routing table to a
   // known state. To start a resync, call resync_init() and then use
   // ip_route_set() and ip_route_via_set() to populate the static
   // routing table with the known entries. After all entries have
   // been set, call resync_complete(), which will delete all existing
   // routes and vias that were not added or modified during resync.
   // If a tag is set, resync will only delete routes and vias
   // corresponding to the current tag.
   // During resync, this manager will act like it is referencing a
   // temporary table that starts off empty. Thus, methods like exist,
   // _del, and getters will act only on that temporary table,
   // regardless of the real values in Sysdb. The one exception is
   // iteration; they will traverse the table stored in Sysdb,
   // regardless of whether or not the manager is in resync mode.
   void resync_init();    
   void resync_complete();

   typedef bool (*callback_func_route)(ip_route_t const &, void * context);
   typedef bool (*callback_func_via)(ip_route_via_t const &, void * context);

   // Iterate across all configured static routes. If a tag is set,
   // only return routes that have match the current tag.
   ip_route_iter_t ip_route_iter() const;
   void ip_route_foreach(callback_func_route handler, void * context);
   void ip_route_foreach(callback_func_route handler, void * context,
                         ip_route_t const & bookmark);

   // Iterate across configured nexthops for a given route key, i.e.,
   // emit all ip_route_via_t's for a given route key. If a tag is
   // set, only return vias on routes that match the current tag.
   ip_route_via_iter_t ip_route_via_iter(ip_route_key_t const &) const;
   void ip_route_via_foreach(ip_route_key_t const &,
                             callback_func_via handler, void * context);

   // Tests for existence of any routes matching the route key in the
   // switch config. If a tag is set and the route belongs to a
   // different tag, this function returns false.
   bool exists(ip_route_key_t const &) const;
   // Tests if the given via exists.
   bool exists(ip_route_via_t const &) const;

   // Route management functions

   // Gets a static route, or panics if the route key does not exist.
   ip_route_t ip_route(ip_route_key_t const &);
   // Inserts or updates a static route into the switch configuration.
   void ip_route_set(ip_route_t const &);
   // Removes all ECMP vias matching the route key, and the route itself. 
   void ip_route_del(ip_route_key_t const &);

   // Adds a via to an ip_route_t. Will panic if the corresponding route
   // does not match the currently configured tag.
   void ip_route_via_set(ip_route_via_t const &);
   // Removes a via from an ip_route_t. When all vias are removed,
   // the route still exists with no nexthop information.
   void ip_route_via_del(ip_route_via_t const &);

 protected:
   ip_route_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(ip_route_mgr);
};

ip_route_mgr * get_ip_route_mgr() EOS_SDK_PUBLIC;

}  // end namespace eos

#include <eos/inline/ip_route.h>

#endif // EOS_IP_ROUTE_H
