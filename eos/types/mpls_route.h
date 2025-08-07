// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_MPLS_ROUTE_H
#define EOS_TYPES_MPLS_ROUTE_H

#include <eos/hash_mix.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/mpls.h>
#include <eos/utility.h>
#include <forward_list>
#include <memory>
#include <sstream>
#include <vector>

#ifdef SWIG
%ignore eos::mpls_route_key_t(eos::mpls_route_key_t &&) noexcept;
%ignore eos::mpls_route_key_t::operator=(eos::mpls_route_key_t &&) noexcept;
%ignore eos::mpls_route_key_t::labels_is(std::vector<eos::mpls_label_t> &&);
%ignore eos::label_set(uint32_t, eos::mpls_label_t &&);
%ignore eos::mpls_route_t(eos::mpls_route_t &&) noexcept;
%ignore eos::mpls_route_t::operator=(eos::mpls_route_t &&) noexcept;
%ignore eos::mpls_route_via_t(eos::mpls_route_via_t &&) noexcept;
%ignore eos::mpls_route_via_t::operator=(eos::mpls_route_via_t &&) noexcept;
%ignore eos::mpls_route_via_t::hop_is(eos::ip_addr_t &&);
%ignore eos::mpls_route_via_t::intf_is(intf_id_t &&);
%ignore eos::mpls_route_via_t::pushswap_label_stack_is(
         std::forward_list<eos::mpls_label_t> &&);
%ignore eos::pushswap_label_stack_set(eos::mpls_label_t &&);
%ignore eos::mpls_fec_id_t(eos::mpls_fec_id_t &&) noexcept;
%ignore eos::mpls_fec_id_t::operator=(eos::mpls_fec_id_t &&) noexcept;
#endif

namespace eos {

/** 1..255; default/null is 0. */
typedef uint8_t mpls_route_metric_t;

class mpls_route_key_impl_t;
/** An MPLS route key is used for MPLS RIB configuration. */
class EOS_SDK_PUBLIC mpls_route_key_t {
 public:
   mpls_route_key_t();
   /**
    * Constructor taking an ingress MPLS route label and a metric.
    * @param mpls_label_t The MPLS label to match on ingress for this route.
    * @param mpls_route_metric_t A metric value between 0 and 255. If it is set to
    * 0, the routing agent will assume a default metric value of 100.
    */
   mpls_route_key_t(mpls_label_t top_label, mpls_route_metric_t metric);
   /**
    * Constructor taking a list of ingress MPLS route labels and a metric.
    * @param const std::vector<mpls_label_t> The MPLS labels to match on ingress
    * for this route.
    * @param mpls_route_metric_t A metric value between 0 and 255. If it is set to
    * 0, the routing agent will assume a default metric value of 100.
    */
   mpls_route_key_t(std::vector<mpls_label_t> const & labels,
                    mpls_route_metric_t metric);
   mpls_route_key_t(const mpls_route_key_t& other);
   mpls_route_key_t& operator=(
      mpls_route_key_t const & other);

   mpls_route_key_t(mpls_route_key_t && other) noexcept;
   mpls_route_key_t & operator=(mpls_route_key_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /**
    * Getter for 'labels': a list of labels ( [ TOP, ..., BOT ] ) to match on
    * ingress route lookup.
    * 0 is the null metric; valid MPLS routes must have a metric in range 1..255.
    */
   std::vector<mpls_label_t> const & labels() const;
   /** Setter for 'labels'. */
   void labels_is(std::vector<mpls_label_t> const & labels);
   /** Moving Setter for 'labels'. */
   void labels_is(std::vector<mpls_label_t> && labels);
   void label_set(uint32_t index, mpls_label_t const & value);
   void label_set(uint32_t index, mpls_label_t && value);
   void label_del(uint32_t index);

   /**
    * Getter for 'metric': the MPLS route metric. Lower metric routes are
    * preferred.
    */
   mpls_route_metric_t metric() const;
   /** Setter for 'metric'. */
   void metric_is(mpls_route_metric_t metric);

   /**
    * Getter for the label to match on ingress route lookup. This API exists for
    * legacy reasons, from when only one label could be matched.
    */
   mpls_label_t top_label() const;
   /**
    * Replaces the label stack with a new vector only containing the given
    * top_label.
    */
   void top_label_is(mpls_label_t top_label);
   bool operator==(mpls_route_key_t const & other) const;
   bool operator!=(mpls_route_key_t const & other) const;
   bool operator<(mpls_route_key_t const & other) const;
   /** The hash function for type mpls_route_key_t. */
   uint32_t hash() const;
   /** The hash mix function for type mpls_route_key_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * mpls_route_key_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const mpls_route_key_t& obj);

 private:
   std::shared_ptr<mpls_route_key_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const mpls_route_key_t& obj);

class mpls_route_impl_t;
/** An MPLS v4/v6 static route. */
class EOS_SDK_PUBLIC mpls_route_t {
 public:
   /** Default value constructor. */
   mpls_route_t();
   /** MPLS route constructor taking an MPLS route key. */
   explicit mpls_route_t(mpls_route_key_t key);
   /** MPLS route constructor taking an MPLS route key and a version. */
   explicit mpls_route_t(mpls_route_key_t key, uint32_t version_id);
   mpls_route_t(const mpls_route_t& other);
   mpls_route_t& operator=(
      mpls_route_t const & other);

   mpls_route_t(mpls_route_t && other) noexcept;
   mpls_route_t & operator=(mpls_route_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /** Getter for 'key': the MPLS route key. */
   mpls_route_key_t key() const;
   /** Setter for 'key'. */
   void key_is(mpls_route_key_t key);

   /** Getter for 'version_id': the MPLS route version. */
   uint32_t version_id() const;
   /** Setter for 'version_id'. */
   void version_id_is(uint32_t version_id);

   bool operator==(mpls_route_t const & other) const;
   bool operator!=(mpls_route_t const & other) const;
   /** The hash function for type mpls_route_t. */
   uint32_t hash() const;
   /** The hash mix function for type mpls_route_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of mpls_route_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const mpls_route_t& obj);

 private:
   std::shared_ptr<mpls_route_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const mpls_route_t& obj);

class mpls_route_via_impl_t;
/** An MPLS route via, defining the action to take for a given MPLS route. */
class EOS_SDK_PUBLIC mpls_route_via_t {
 public:
   mpls_route_via_t();
   explicit mpls_route_via_t(mpls_route_key_t route_key);
   explicit mpls_route_via_t(mpls_route_key_t route_key,
                             mpls_action_t label_action);
   mpls_route_via_t(const mpls_route_via_t& other);
   mpls_route_via_t& operator=(
      mpls_route_via_t const & other);

   mpls_route_via_t(mpls_route_via_t && other) noexcept;
   mpls_route_via_t & operator=(mpls_route_via_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   mpls_route_key_t route_key() const;
   void route_key_is(mpls_route_key_t route_key);

   /** Getter for 'hop': IP v4/v6 nexthop address (for decap and IP forward). */
   ip_addr_t hop() const;
   /** Setter for 'hop'. */
   void hop_is(ip_addr_t const & hop);
   /** Moving Setter for 'hop'. */
   void hop_is(ip_addr_t && hop);

   /**
    * Getter for 'intf': sets the nexthop interface.
    * Use the named interface if not a default intf_id_t.
    */
   intf_id_t intf() const;
   /** Setter for 'intf'. */
   void intf_is(intf_id_t const & intf);
   /** Moving Setter for 'intf'. */
   void intf_is(intf_id_t && intf);

   /** Getter for "pushswap_label": deprecated in favor of "pushswap_label_stack". */
   mpls_label_t pushswap_label() const;
   /** Setter for "pushswap_label": Deprecated in favor of "pushswap_label_stack". */
   void pushswap_label_is(mpls_label_t top_label);
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

   /**
    * Getter for 'skip_egress_acl': set if matching packets should ignore the
    * egress ACL.
    */
   bool skip_egress_acl() const;
   /** Setter for 'skip_egress_acl'. */
   void skip_egress_acl_is(bool skip_egress_acl);

   /**
    * Getter for 'nexthop_group': set when packets are forwarded into a nexthop-
    * group.
    */
   std::string nexthop_group() const;
   /** Setter for 'nexthop_group'. */
   void nexthop_group_is(std::string nexthop_group);

   /** Getter for 'weight': the weight for this via. */
   uint32_t weight() const;
   /** Setter for 'weight'. */
   void weight_is(uint32_t weight);

   /** Getter for 'pushswap_label_stack': push or swap this label stack. */
   std::forward_list<mpls_label_t> const & pushswap_label_stack() const;
   /** Setter for 'pushswap_label_stack'. */
   void pushswap_label_stack_is(
         std::forward_list<mpls_label_t> const & pushswap_label_stack);
   /** Moving Setter for 'pushswap_label_stack'. */
   void pushswap_label_stack_is(
         std::forward_list<mpls_label_t> && pushswap_label_stack);
   /** Prepend one pushswap_label_stack to the list. */
   void pushswap_label_stack_set(mpls_label_t const & pushswap_label_stack);
   /** Prepend one pushswap_label_stack to the list. */
   void pushswap_label_stack_set(mpls_label_t && pushswap_label_stack);
   /** Remove all matching pushswap_label_stack elements. */
   void pushswap_label_stack_del(mpls_label_t const & pushswap_label_stack);

   bool operator==(mpls_route_via_t const & other) const;
   bool operator!=(mpls_route_via_t const & other) const;
   /** The hash function for type mpls_route_via_t. */
   uint32_t hash() const;
   /** The hash mix function for type mpls_route_via_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * mpls_route_via_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const mpls_route_via_t& obj);

 private:
   std::shared_ptr<mpls_route_via_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const mpls_route_via_t& obj);

class mpls_fec_id_impl_t;
/**
 * Represents a forward equivalency class (FEC) for an MPLS route. One or more
 * routes points to a FEC, and the FEC corresponds to a
 * set of MPLS vias that are programmed into hardware.
 */
class EOS_SDK_PUBLIC mpls_fec_id_t {
 public:
   mpls_fec_id_t();
   explicit mpls_fec_id_t(uint64_t id);
   mpls_fec_id_t(const mpls_fec_id_t& other);
   mpls_fec_id_t& operator=(
      mpls_fec_id_t const & other);

   mpls_fec_id_t(mpls_fec_id_t && other) noexcept;
   mpls_fec_id_t & operator=(mpls_fec_id_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /**
    * Getter for 'id': the internal ID of this FEC.
    * A value of 0 denotes that the FEC ID is not set.
    */
   uint64_t id() const;
   /** Setter for 'id'. */
   void id_is(uint64_t id);

   bool operator==(mpls_fec_id_t const & other) const;
   bool operator!=(mpls_fec_id_t const & other) const;
   bool operator<(mpls_fec_id_t const & other) const;
   /** The hash function for type mpls_fec_id_t. */
   uint32_t hash() const;
   /** The hash mix function for type mpls_fec_id_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of mpls_fec_id_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const mpls_fec_id_t& obj);

 private:
   std::shared_ptr<mpls_fec_id_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const mpls_fec_id_t& obj);
}

#endif // EOS_TYPES_MPLS_ROUTE_H
