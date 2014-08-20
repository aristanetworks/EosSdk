// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_MPLS_ROUTE_H
#define EOS_MPLS_ROUTE_H


#include <eos/base.h>
#include <eos/iterator.h>

#include <eos/types/mpls_route.h>

namespace eos {

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

   /// Returns an MPLS via iterator for a given route (key).
   virtual mpls_route_via_iter_t mpls_route_via_iter(mpls_route_key_t const &)
      const = 0;

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

#endif // EOS_MPLS_ROUTE_H
