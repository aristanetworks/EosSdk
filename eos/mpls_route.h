// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_MPLS_ROUTE_H
#define EOS_MPLS_ROUTE_H

#include <eos/base.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/iterator.h>
#include <eos/mpls.h>

namespace eos {

typedef uint8_t mpls_route_metric_t;  // 1..255; default/null is 0


/// An MPLS route key is used for MPLS RIB configuration.
class EOS_SDK_PUBLIC mpls_route_key_t {
 public:
   mpls_route_key_t();
   /**
    * Constructor taking an ingress MPLS route label and a metric.
    *
    * @param mpls_label_t The MPLS label to match on ingress for this route
    * @param mpls_route_metric_t A metric value between 1 and 255
    */
   mpls_route_key_t(mpls_label_t const &, mpls_route_metric_t metric);

   bool operator==(mpls_route_key_t const & other) const;
   bool operator!=(mpls_route_key_t const & other) const;

   /**
    * The label to match on ingress route lookup.
    *
    * 0 is the null metric; valid MPLS routes must have a metric in range 1..255
    */
   mpls_label_t top_label;
   /// The MPLS route metric. Lower metric routes are preferred.
   mpls_route_metric_t metric;
};

/// An MPLS v4/v6 static route.
class EOS_SDK_PUBLIC mpls_route_t {
 public:
   /// Default value constructor
   mpls_route_t();
   /// MPLS route constructor taking an MPLS route key.

   explicit mpls_route_t(mpls_route_key_t const & route_key);

   bool operator==(mpls_route_t const & other) const;
   bool operator!=(mpls_route_t const & other) const;

   /// The MPLS route key
   mpls_route_key_t key;

   /// If true, this route is persisted in the startup-config
   bool persistent;
};

/// An MPLS route via, defining the action to take for a given MPLS route.
class EOS_SDK_PUBLIC mpls_route_via_t {
  public:
   mpls_route_via_t();
   explicit mpls_route_via_t(mpls_route_key_t const & route_key);

   mpls_route_key_t route_key;

   /// Use these fields to determine the nexthop

   ip_addr_t hop;           ///< IP v4/v6 nexthop address (for decap and IP forward)
   intf_id_t intf;          ///< Use the named interface if not a default intf_id_t

   mpls_label_t pushswap_label;  ///< Push or swap this label
   mpls_action_t label_action;  ///< Perform this MPLS operation
   mpls_ttl_mode_t ttl_mode;    ///< Applies to push and pop
   mpls_payload_type_t payload_type;  ///< Used to assign ethertype after final pop
};

class mpls_route_iter_impl;

/// An iterator over MPLS routes
class EOS_SDK_PUBLIC mpls_route_iter_t : public iter_base<mpls_route_t,
                                                          mpls_route_iter_impl> {
 private:
   friend class mpls_route_iter_impl;
   explicit mpls_route_iter_t(mpls_route_iter_impl * const) EOS_SDK_PRIVATE;
};


class mpls_route_via_iter_impl;

/// An iterator over MPLS route via
class EOS_SDK_PUBLIC mpls_route_via_iter_t :
   public iter_base<mpls_route_via_t, mpls_route_via_iter_impl> {
 private:
   friend class mpls_route_via_iter_impl;
   explicit mpls_route_via_iter_t(mpls_route_via_iter_impl * const) EOS_SDK_PRIVATE;
};


/// The IP static route manager
class EOS_SDK_PUBLIC mpls_route_mgr {
  public:
   virtual ~mpls_route_mgr();

   /// Begin resync mode.
   virtual void resync_init() = 0;
   /// Complete resync mode, ready for regular updates.
   virtual void resync_complete() = 0;

   /// Returns an MPLS route iterator.
   virtual mpls_route_iter_t mpls_route_iter() const = 0;

   typedef bool (*callback_func_route)(mpls_route_t const &, void * context);
   typedef bool (*callback_func_via)(mpls_route_via_t const &, void * context);

   /// Iterate across all MPLS static routes.
   /// @deprecated Use mpls_route_iter() instead.
   virtual void mpls_route_foreach(callback_func_route handler, void * context)
      EOS_SDK_DEPRECATED = 0;
   /// Iterate across all MPLS static routes from a given bookmark.
   /// @deprecated Use mpls_route_iter() instead.
   virtual void mpls_route_foreach(callback_func_route handler, void * context,
                                   mpls_route_t const & bookmark)
      EOS_SDK_DEPRECATED = 0;

   /// Returns an MPLS via iterator for a given route (key).
   virtual mpls_route_via_iter_t mpls_route_via_iter(mpls_route_key_t const &)
      const = 0;
   /**
    * Iterates over configured nexthops for a given MPLS route.
    * emits all mpls_route_via_t's for a given mpls_route_t.
    * @deprecated Use mpls_route_iter() instead.
    */
   virtual void mpls_route_via_foreach(mpls_route_key_t const &,
                                       callback_func_via handler, void * context)
      EOS_SDK_DEPRECATED = 0;

   /// Tests for existence of any routes matching the route key in the switch config
   virtual bool exists(mpls_route_key_t const &) const = 0;
   /// Tests if the given via exists
   virtual bool exists(mpls_route_via_t const &) const = 0;

   /// MPLS route management functions

   /// Inserts or updates MPLS static route in the switch configuration
   virtual void mpls_route_set(mpls_route_t const &) = 0;

   /// Removes the MPLS route and all vias matching the route key
   virtual void mpls_route_del(mpls_route_key_t const &) = 0;

   /// Adds a via to an mpls_route_t
   virtual void mpls_route_via_set(mpls_route_via_t const &) = 0;
   /**
    * Removes a via from an mpls_route_t.
    * When all vias are removed, the route still exists with no
    * nexthop information.
    */
   virtual void mpls_route_via_del(mpls_route_via_t const &) = 0;

 protected:
   mpls_route_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(mpls_route_mgr);
};

}

#include <eos/inline/mpls_route.h>

#endif // EOS_MPLS_ROUTE_H
