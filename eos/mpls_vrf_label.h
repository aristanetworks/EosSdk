// Copyright (c) 2018 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_MPLS_VRF_LABEL_H
#define EOS_MPLS_VRF_LABEL_H

#include <string>

#include <eos/base.h>
#include <eos/iterator.h>

#include <eos/types/mpls_route.h>
#include <eos/types/mpls_vrf_label.h>

/**
 * @file
 * MPLS Static VRF label management.
 *
 * This module manages VRF label decapsulation for traffic arriving at
 * the switch (on any interface).
 *
 * In this example, a static VRF label route is configured for MPLS traffic
 * arriving at the switch with a top label of 16. This label is mapped to
 * a corresponding VRF "foo".
 *
 * @code
 * // Configures a static VRF label route
 * eos::mpls_vrf_label_t vrf_label(mpls_label_t(16), "foo");
 * mgr->mpls_vrf_label_set(vrf_label);
 * @endcode
 *
 * By configuring a static VRF label route, the switch will decapsulate
 * traffic matching the specified top label and forward normally based
 * on the inner protocol headers and the routes within the specified VRF.
 * IPv4, IPv6, and MPLS are the only inner protocols presently supported.
 * Static MPLS routes are only available within the 'default' VRF --
 * when the inner protocol is MPLS, the specified VRF is ignored.
 */
namespace eos {

class mpls_vrf_label_iter_impl;

/// An iterator that yields a `mpls_vrf_label_t` for each configured VRF label route.
class EOS_SDK_PUBLIC mpls_vrf_label_iter_t : public iter_base<
   mpls_vrf_label_t, mpls_vrf_label_iter_impl> {
 private:
   friend class mpls_vrf_label_iter_impl;
   explicit mpls_vrf_label_iter_t(mpls_vrf_label_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * A manager of 'mpls static vrf-label' configurations.
 *
 * Create one of these via sdk object prior to starting the agent main loop. When
 * your eos::agent_handler::on_initialized virtual function is called, the manager
 * is valid for use.
 */
class EOS_SDK_PUBLIC mpls_vrf_label_mgr {
 public:
   virtual ~mpls_vrf_label_mgr();

   /**
    * Enter resync mode.
    *
    * At this point the mpls_vrf_label_mgr will start tracking which
    * routes you've added.
    */
   virtual void resync_init() = 0;

   /**
    * Exit resync mode.
    *
    * All VRF label routes in Sysdb that you haven't re-added during this
    * resync period will now be deleted.
    */
   virtual void resync_complete() = 0;


   /**
    * Iterates over all the VRF label routes currently configured.
    */
   virtual mpls_vrf_label_iter_t mpls_vrf_label_iter() const = 0;

   /**
    * Returns the current configuration of a VRF label route
    *
    * If no VRF label route exists, this returns an empty `mpls_vrf_label_t()`
    */
   virtual mpls_vrf_label_t mpls_vrf_label(mpls_label_t const &) const = 0;

   /**
    * Adds the specified VRF label route to the system configuration.
    *
    * Either creates or updates a VRF label route (keyed by the label).
    */
   virtual void mpls_vrf_label_set(mpls_vrf_label_t const &) = 0;

   /**
    * Removes the VRF label route from the configuration.
    *
    * If the specified label does not exist, no action is taken.
    */
   virtual void mpls_vrf_label_del(mpls_label_t const &) = 0;
 protected:
   mpls_vrf_label_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(mpls_vrf_label_mgr);
};

}

#endif // EOS_MPLS_VRF_LABEL_H
