// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_MPLS_ROUTE_H
#define EOS_MPLS_ROUTE_H

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/iterator.h>

#include <eos/types/mpls_route.h>

namespace eos {

class mpls_route_mgr;

/**
 * The MPLS route handler.
 *
 * This class provides handler APIs to react to a MPLS route's addition/deletion
 * in the hardware.
 **/
class EOS_SDK_PUBLIC mpls_route_handler : public base_handler<mpls_route_mgr,
                                                              mpls_route_handler> {
 public:
   explicit mpls_route_handler(mpls_route_mgr *mgr);
   mpls_route_mgr *get_mpls_route_mgr() const;

   /**
    * Register to receive notification when any MPLS route in the hardware gets
    * deleted or added.
    */
   void watch_all_mpls_routes(bool);

   /**
    * Register to receive notification when a particular MPLS route is added to or
    * removed from hardware.
    */
   void watch_mpls_route(mpls_label_t const &label, bool);

   /**
    * Handler when a MPLS route is deleted from hardware.
    */
   virtual void on_mpls_route_del(mpls_label_t label);

   /**
    * Handler when a MPLS route is added in hardware.
    */
   virtual void on_mpls_route_set(mpls_label_t label);

   /**
    * Handler when a MPLS route best metric is changed, due to adjacency change.
    * The new best metric is returned.
    */
   virtual void on_mpls_route_bestmetric(mpls_label_t, mpls_route_metric_t);

   /**
    * Handler when a MPLS route adjacency is added or updated. The adjacency's 
    * metric is returned.
    */
   virtual void on_mpls_route_adjacency_set(mpls_label_t, mpls_route_metric_t);

   /**
    * Handler when a MPLS route adjacency is removed. The adjacency's metric 
    * is returned.
    */
   virtual void on_mpls_route_adjacency_del(mpls_label_t, mpls_route_metric_t);
};

class mpls_route_iter_impl;

/// An iterator over configured MPLS routes
class EOS_SDK_PUBLIC mpls_route_iter_t : public iter_base<mpls_route_t,
                                                          mpls_route_iter_impl> {
 private:
   friend class mpls_route_iter_impl;
   explicit mpls_route_iter_t(mpls_route_iter_impl * const) EOS_SDK_PRIVATE;
};

class mpls_route_via_iter_impl;

/// An iterator over configured MPLS route vias
class EOS_SDK_PUBLIC mpls_route_via_iter_t :
   public iter_base<mpls_route_via_t, mpls_route_via_iter_impl> {
 private:
   friend class mpls_route_via_iter_impl;
   explicit mpls_route_via_iter_t(mpls_route_via_iter_impl * const) EOS_SDK_PRIVATE;
};

class mpls_route_status_iter_impl;

/// An iterator over MPLS routes in hardware
class EOS_SDK_PUBLIC mpls_route_status_iter_t : public iter_base<mpls_route_key_t,
                                                       mpls_route_status_iter_impl> {
 private:
   friend class mpls_route_status_iter_impl;
   explicit mpls_route_status_iter_t(
         mpls_route_status_iter_impl * const) EOS_SDK_PRIVATE;
};

class mpls_route_via_status_iter_impl;

/// An iterator over MPLS route vias in hardware
class EOS_SDK_PUBLIC mpls_route_via_status_iter_t :
   public iter_base<mpls_route_via_t, mpls_route_via_status_iter_impl> {
  private:
    friend class mpls_route_via_status_iter_impl;
    explicit mpls_route_via_status_iter_t(
          mpls_route_via_status_iter_impl * const) EOS_SDK_PRIVATE;
 };

/// The IP static route manager
class EOS_SDK_PUBLIC mpls_route_mgr : public base_mgr<mpls_route_handler, 
                                                     mpls_label_t> {
  public:
   virtual ~mpls_route_mgr();

   /// Begin resync mode.
   virtual void resync_init() = 0;
   /// Complete resync mode, ready for regular updates.
   virtual void resync_complete() = 0;

   /// Returns an iterator over configured MPLS routes.
   virtual mpls_route_iter_t mpls_route_iter() const = 0;

   /// Returns an iterator for MPLS routes in hardware.
   virtual mpls_route_status_iter_t mpls_route_status_iter() const = 0;

   /// Returns a configured MPLS vias iterator for a given route (key).
   virtual mpls_route_via_iter_t mpls_route_via_iter(mpls_route_key_t const &)
      const = 0;

   /// Returns an iterator for MPLS vias in hardware for a given route (key).
   virtual mpls_route_via_status_iter_t mpls_route_via_status_iter(
          mpls_route_key_t const &) const = 0;

   /// Tests for existence of any routes matching the route key in the switch config
   virtual bool exists(mpls_route_key_t const &) const = 0;
   /// Tests if the given via exists in the switch config
   virtual bool exists(mpls_route_via_t const &) const = 0;

   virtual mpls_route_status_t mpls_route_status(mpls_label_t) const = 0;

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
   friend class mpls_route_handler;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(mpls_route_mgr);
};

} // end namespace eos

#include <eos/inline/mpls_route.h>

#endif // EOS_MPLS_ROUTE_H
