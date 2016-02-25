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
    * Handler when a MPLS route is to be programmed into hardware or
    * when it is assigned a new FEC ID.
    */
   virtual void on_mpls_route_set(mpls_label_t label, mpls_fec_id_t fec);

   /**
    * Handler when a MPLS route is deleted from hardware.
    */
   virtual void on_mpls_route_del(mpls_label_t label);

   /**
    * Handler that describes when an MPLS FEC is created or updated in
    * hardware. This FEC represents a set of vias that one or more
    * routes points to.
    */
   virtual void on_mpls_fec_set(mpls_fec_id_t fec);

   /**
    * Handler called when an MPLS FEC is removed.
    */
   virtual void on_mpls_fec_del(mpls_fec_id_t fec);
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

   /// Returns an iterator for MPLS vias in hardware for a given route key.
   virtual mpls_route_via_status_iter_t mpls_route_via_status_iter(
          mpls_label_t const) const = 0;

   /// Returns an iterator for MPLS vias in hardware for a given MPLS FEC.
   /// The vias returned from this iterator are unbound, meaning they have an 
   /// empty mpls_route_key_t.
   virtual mpls_route_via_status_iter_t mpls_route_via_status_iter(
         mpls_fec_id_t) const = 0;

   /// Tests for existence of any routes matching the route key in the switch config
   virtual bool exists(mpls_route_key_t const &) const = 0;
   /// Tests if the given via exists in the switch config
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

   /**
    * Returns the FEC ID corresponding to the given MPLS label if this route 
    * is programmed in hardware, or an empty mpls_fec_id_t otherwise.
    */
   virtual mpls_fec_id_t fec_id(mpls_label_t) const = 0;

   /**
    * Given an MPLS label, this method returns the active metric that
    * is being used in hardware to forward traffic, or 0 if the given
    * label does not have any active vias programmed.
    */
   virtual mpls_route_metric_t metric(mpls_label_t) const = 0;

 protected:
   mpls_route_mgr() EOS_SDK_PRIVATE;
   friend class mpls_route_handler;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(mpls_route_mgr);
};

} // end namespace eos

#include <eos/inline/mpls_route.h>

#endif // EOS_MPLS_ROUTE_H
