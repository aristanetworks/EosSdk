// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_NEXTHOP_GROUP_H
#define EOS_NEXTHOP_GROUP_H

#include <list>
#include <map>

#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/iterator.h>
#include <eos/mpls.h>

namespace eos {

/**
 * The type of encapsulation to use for this nexthop group.
 *
 * The present nexthop group types are all tunnel encapsulations. Each
 * causes a variety of packet headers for packets using the group to
 * be changed to appropriately encapsulate the frame.
 */
enum nexthop_group_encap_t {
   NEXTHOP_GROUP_TYPE_NULL,
   NEXTHOP_GROUP_IP_IN_IP,   ///< IP in IP encapsulation
   NEXTHOP_GROUP_GRE,        ///< GRE encapsulation
   NEXTHOP_GROUP_MPLS,       ///< MPLS encapsulation
};

/**
 * An MPLS nexthop group switching operation.
 *
 * This structure combines a stack of labels and an MPLS operation
 * using those labels, such as eos::MPLS_ACTION_PUSH.
 */

class EOS_SDK_PUBLIC nexthop_group_mpls_action_t {
 public:
   /// Constructs an empty MPLS nexthop group action.
   nexthop_group_mpls_action_t();
   /// Constructs an empty MPLS label stack for a specific switching action.
   explicit nexthop_group_mpls_action_t(mpls_action_t action_type);
   /// Constructs a populated MPLS label stack for some switching action.
   nexthop_group_mpls_action_t(mpls_action_t mpls_action,
                               std::list<mpls_label_t> const & mpls_labels);

   /**
    * Set the MPLS switching operation for this nexthop group action.
    *
    * Presently, only MPLS_ACTION_PUSH is supported for up to two
    * labels.
    */
   void action_type_is(mpls_action_t action_type);

   /**
    * The type of MPLS switching action to perform with label_stack().
    */
   mpls_action_t action_type() const;

   /**
    * Sets the MPLS label(s) to push onto this nexthop group.
    *
    * When providing multiple MPLS labels, the top of the label stack
    * is the beginning of the list and the bottom of the label stack
    * is the end of the list. Labels are listed in the same
    * order they would finally appear in the MPLS frame. This means
    * that you place the outermost label at the beginning of the list.
    *
    * This method can only be used when the type() is NEXTHOP_GROUP_MPLS,
    * otherwise a panic will occur.
    *
    * @param label_stack The MPLS label(s) to add to egress packets for this group.
    */
   void label_stack_is(std::list<mpls_label_t> const & label_stack);

   /**
    * Returns a reference to the list of MPLS label(s) currently set.
    *
    * @returns The MPLS label stack used on this nexthop group. If no
    * MPLS label stack is set, an empty list is returned.
    */
   std::list<mpls_label_t> const & label_stack() const;

 private:
   mpls_action_t action_type_;
   std::list<mpls_label_t> label_stack_;
};

/**
 * A nexthop group.
 *
 * A nexthop group represents encapsulation and IP addressing
 * information to be used with a policy routing application.
 */
class EOS_SDK_PUBLIC nexthop_group_t {
 public:
   /// Constructs an empty nexthop group
   nexthop_group_t();
   /// Constructs a nexthop group given a name and encapsulation type.
   nexthop_group_t(std::string const &, nexthop_group_encap_t);

   /// The name of the nexthop group
   std::string const & name() const;

   /// Returns the encapsulation type
   nexthop_group_encap_t type() const;

   /// Sets the TTL to set on frames sent via this nexthop group.
   void ttl_is(uint8_t);  // default TTL is 64
   /// The current TTL for frames sent via this nexthop group.
   uint8_t ttl() const;

   /**
    * Sets the source IP address to use for frames sent on this group.
    * source_intf() will be cleared after the source IP is set. This
    * must be an IPv4 address.
    *
    * This method will panic if the type() is NEXTHOP_GROUP_MPLS.
    */
   void source_ip_is(ip_addr_t const &);
   /// The source IP for frames sent on this group.
   ip_addr_t const & source_ip() const;

   /**
    * Sets a source interface.
    * source_ip() will be cleared after the source interface is set.
    */
   void source_intf_is(intf_id_t const &);
   /// Returns the current source interface ID. If not used, returns the default ID.
   intf_id_t const source_intf() const;

   /**
    * Sets an entry in the nexthop group's destination IP address array.
    *
    * Use duplicate addresses in different sequence numbers to perform
    * unequal cost multipath.
    *
    * @param uint16_t Index into the destination IP array.
    * @param ip_addr_t The IP address to set at the index. This must
    * be an IPv4 address.
    */
   void destination_ip_set(uint16_t, ip_addr_t const &);

   /**
    * Deletes an entry in the nexthop group's destination IP address array.
    *
    * @param uint8_t Index into the destination IP array.
    */
   void destination_ip_del(uint16_t);

   /// Returns the current nexthop group destination IP address
   std::map<uint16_t, ip_addr_t> const & destination_ips() const;

   /**
    * Replaces the entire MPLS switching action colection.
    *
    * @param mpls_actions The std::map collection of mpls_actions to use.
    */
   void mpls_actions_is(
         std::map<uint16_t, nexthop_group_mpls_action_t> const & mpls_actions);

   /**
    * Sets an MPLS label stack for an MPLS switching operation.
    *
    * An nexthop_group_mpls_action_t is a stack or list of MPLS labels
    * with the MPLS switching operation (push, pop, swap) to be performed.
    * The stacks are processed from lowest to highest integer in the map.
    *
    * @param seq The sequence number, valid in the range 1..65534
    * @param mpls_action The label stack to set at the sequence number.
    */
   void mpls_actions_set(uint16_t seq,
                         nexthop_group_mpls_action_t const & mpls_action);

   /// Deletes an MPLS label stack at a specific sequence.
   void mpls_actions_del(uint16_t seq);

   /**
    * Returns the entire MPLS switching action collection.
    */
   std::map<uint16_t, nexthop_group_mpls_action_t> const & mpls_actions() const;

   /// Returns the number of destination IP addresses in this nexthop group.
   uint16_t size() const;

   /// Sets the config persistence for this nexthop group (defaults to false).
   void persistent_is(bool);
   /// The persistence state for this nexthop group.
   bool persistent() const;

 private:
   std::string name_;
   uint8_t ttl_;
   ip_addr_t source_ip_;
   intf_id_t source_intf_;
   nexthop_group_encap_t encap_type_;
   std::map<uint16_t, ip_addr_t> destination_ips_;
   std::map<uint16_t, nexthop_group_mpls_action_t> mpls_actions_;
   bool persistent_;
};

class nexthop_group_iter_impl;

class EOS_SDK_PUBLIC nexthop_group_iter_t :
      public iter_base<nexthop_group_t, nexthop_group_iter_impl> {
 private:
   friend class nexthop_group_iter_impl;
   explicit nexthop_group_iter_t(nexthop_group_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * A manager of 'nexthop-group' configurations.
 *
 * Create one of these via an sdk object prior to starting the agent main loop.
 * When your eos::agent_handler::on_initialized virtual function is called, the
 * manager is valid for use.
 */
class EOS_SDK_PUBLIC nexthop_group_mgr {
 public:
   virtual ~nexthop_group_mgr();

   virtual void resync_init() = 0;
   virtual void resync_complete() = 0;

   /// Iterates over all the nexthop groups currently configured.
   virtual nexthop_group_iter_t nexthop_group_iter() const = 0;

   /// Creates or updates a nexthop group.
   virtual void nexthop_group_set(nexthop_group_t const &) = 0;
   /// Removes the named nexthop group from the configuration if it exists
   virtual void nexthop_group_del(std::string const & nexthop_group_name) = 0;
 protected:
   nexthop_group_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(nexthop_group_mgr);
};

} // end namespace eos

#include <eos/inline/nexthop_group.h>

#endif // EOS_NEXTHOP_GROUP_H
