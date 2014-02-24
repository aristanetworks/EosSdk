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

// Defines an MPLS route key for MPLS RIB configuration
class EOS_SDK_PUBLIC mpls_route_key_t {
 public:
   mpls_route_key_t();
   mpls_route_key_t(mpls_label_t const &, mpls_route_metric_t metric);

   bool operator==(mpls_route_key_t const & other) const;
   bool operator!=(mpls_route_key_t const & other) const;

   mpls_label_t top_label;      // the label to match on ingress route lookup
   // 0 is the null metric; valid MPLS routes must have a metric in range 1..255
   mpls_route_metric_t metric;
};

// An MPLS v4/v6 static route.
class EOS_SDK_PUBLIC mpls_route_t {
 public:
   mpls_route_t();
   explicit mpls_route_t(mpls_route_key_t const & route_key);

   bool operator==(mpls_route_t const & other) const;
   bool operator!=(mpls_route_t const & other) const;

   mpls_route_key_t key;

   bool persistent;         // If true, the route is stored to startup-config
};

class EOS_SDK_PUBLIC mpls_route_via_t {
  public:
   mpls_route_via_t();
   explicit mpls_route_via_t(mpls_route_key_t const & route_key);

   mpls_route_key_t route_key;

   // Use these fields to determine the nexthop
   ip_addr_t hop;           // IP v4/v6 nexthop address (for decap and IP forward)
   intf_id_t intf;          // Use the named interface if not a default intf_id_t

   mpls_label_t pushswap_label;  // Push or swap this label
   mpls_action_t label_action;  // Perform this MPLS operation
   mpls_ttl_mode_t ttl_mode;    // Applies to push and pop
   mpls_payload_type_t payload_type;  // Used to assign ethertype after final pop
};

class mpls_route_iter_impl;

class EOS_SDK_PUBLIC mpls_route_iter_t : public iter_base<mpls_route_t,
                                                          mpls_route_iter_impl> {
 private:
   friend class mpls_route_iter_impl;
   explicit mpls_route_iter_t(mpls_route_iter_impl * const) EOS_SDK_PRIVATE;
};


class mpls_route_via_iter_impl;

class EOS_SDK_PUBLIC mpls_route_via_iter_t :
   public iter_base<mpls_route_via_t, mpls_route_via_iter_impl> {
 private:
   friend class mpls_route_via_iter_impl;
   explicit mpls_route_via_iter_t(mpls_route_via_iter_impl * const) EOS_SDK_PRIVATE;
};


class EOS_SDK_PUBLIC mpls_route_mgr {
  public:
   void resync_init();
   void resync_complete();

   mpls_route_iter_t mpls_route_iter() const;

   typedef bool (*callback_func_route)(mpls_route_t const &, void * context);
   typedef bool (*callback_func_via)(mpls_route_via_t const &, void * context);

   // Iterate across all MPLS static routes.
   void mpls_route_foreach(callback_func_route handler, void * context);
   void mpls_route_foreach(callback_func_route handler, void * context,
                           mpls_route_t const & bookmark);

   mpls_route_via_iter_t mpls_route_via_iter(mpls_route_key_t const &) const;
   // Iterate across configured nexthops for a given MPLS route, i.e.,
   // emits all mpls_route_via_t's for a given mpls_route_t.
   void mpls_route_via_foreach(mpls_route_key_t const &,
                               callback_func_via handler, void * context);

   // Tests for existence of any routes matching the route key in the switch config
   bool exists(mpls_route_key_t const &) const;
   // Tests if the given via exists
   bool exists(mpls_route_via_t const &) const;

   // MPLS route management functions

   // Inserts or updates MPLS static route in the switch configuration
   void mpls_route_set(mpls_route_t const &);

   // Removes the MPLS route and all vias matching the route key
   void mpls_route_del(mpls_route_key_t const &);

   // Adds a via to an mpls_route_t
   void mpls_route_via_set(mpls_route_via_t const &);
   // Removes a via from an mpls_route_t. When all vias are removed,
   // the route still exists with no nexthop information.
   void mpls_route_via_del(mpls_route_via_t const &);

 protected:
   mpls_route_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(mpls_route_mgr);
};

mpls_route_mgr * get_mpls_route_mgr() EOS_SDK_PUBLIC;

}

#include <eos/inline/mpls_route.h>

#endif // EOS_MPLS_ROUTE_H
