// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_MPLS_ROUTE_H
#define EOS_TYPES_MPLS_ROUTE_H

#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/mpls.h>
#include <eos/utility.h>
#include <sstream>

namespace eos {

/** 1..255; default/null is 0. */
typedef uint8_t mpls_route_metric_t;


/** An MPLS route key is used for MPLS RIB configuration. */
class EOS_SDK_PUBLIC mpls_route_key_t {
 public:
   mpls_route_key_t();
   /**
    * Constructor taking an ingress MPLS route label and a metric.
    *  @param mpls_label_t The MPLS label to match on ingress for this route.
    * @param mpls_route_metric_t A metric value between 1 and 255.
    */
   mpls_route_key_t(mpls_label_t const & top_label, mpls_route_metric_t metric);

   /**
    * Getter for 'top_label': the label to match on ingress route lookup.
    * 0 is the null metric; valid MPLS routes must have a metric in range 1..255.
    */
   mpls_label_t top_label() const;
   /** Setter for 'top_label'. */
   void top_label_is(mpls_label_t const & top_label);

   /**
    * Getter for 'metric': the MPLS route metric. Lower metric routes are
    * preferred.
    */
   mpls_route_metric_t metric() const;
   /** Setter for 'metric'. */
   void metric_is(mpls_route_metric_t metric);

   bool operator==(mpls_route_key_t const & other) const;
   bool operator!=(mpls_route_key_t const & other) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * mpls_route_key_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, 
                                   const mpls_route_key_t& obj);

 private:
   mpls_label_t top_label_;
   mpls_route_metric_t metric_;
};


/** An MPLS v4/v6 static route. */
class EOS_SDK_PUBLIC mpls_route_t {
 public:
   /** Default value constructor. */
   mpls_route_t();
   /** MPLS route constructor taking an MPLS route key. */
   explicit mpls_route_t(mpls_route_key_t const & key);

   /** Getter for 'key': the MPLS route key. */
   mpls_route_key_t key() const;
   /** Setter for 'key'. */
   void key_is(mpls_route_key_t const & key);

   /**
    * Getter for 'persistent': if true, this route is persisted in the startup-
    * config.
    */
   bool persistent() const;
   /** Setter for 'persistent'. */
   void persistent_is(bool persistent);

   bool operator==(mpls_route_t const & other) const;
   bool operator!=(mpls_route_t const & other) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of mpls_route_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const mpls_route_t& obj);

 private:
   mpls_route_key_t key_;
   bool persistent_;
};


/** An MPLS route via, defining the action to take for a given MPLS route. */
class EOS_SDK_PUBLIC mpls_route_via_t {
 public:
   mpls_route_via_t();
   explicit mpls_route_via_t(mpls_route_key_t const & route_key);

   mpls_route_key_t route_key() const;
   void route_key_is(mpls_route_key_t const & route_key);

   /** Getter for 'hop': IP v4/v6 nexthop address (for decap and IP forward). */
   ip_addr_t hop() const;
   /** Setter for 'hop'. */
   void hop_is(ip_addr_t const & hop);

   /**
    * Getter for 'intf': sets the nexthop interface.
    * Use the named interface if not a default intf_id_t.
    */
   intf_id_t intf() const;
   /** Setter for 'intf'. */
   void intf_is(intf_id_t const & intf);

   /** Getter for 'pushswap_label': push or swap this label. */
   mpls_label_t pushswap_label() const;
   /** Setter for 'pushswap_label'. */
   void pushswap_label_is(mpls_label_t pushswap_label);

   /** Getter for 'label_action': perform this MPLS operation. */
   mpls_action_t label_action() const;
   /** Setter for 'label_action'. */
   void label_action_is(mpls_action_t label_action);

   /** Getter for 'ttl_mode': applies to push and pop. */
   mpls_ttl_mode_t ttl_mode() const;
   /** Setter for 'ttl_mode'. */
   void ttl_mode_is(mpls_ttl_mode_t ttl_mode);

   /** Getter for 'payload_type': used to assign ethertype after final pop. */
   mpls_payload_type_t payload_type() const;
   /** Setter for 'payload_type'. */
   void payload_type_is(mpls_payload_type_t payload_type);

   bool operator==(mpls_route_via_t const & other) const;
   bool operator!=(mpls_route_via_t const & other) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * mpls_route_via_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, 
                                   const mpls_route_via_t& obj);

 private:
   mpls_route_key_t route_key_;
   ip_addr_t hop_;
   intf_id_t intf_;
   mpls_label_t pushswap_label_;
   mpls_action_t label_action_;
   mpls_ttl_mode_t ttl_mode_;
   mpls_payload_type_t payload_type_;
};

}

#include <eos/inline/types/mpls_route.h>

#endif // EOS_TYPES_MPLS_ROUTE_H
