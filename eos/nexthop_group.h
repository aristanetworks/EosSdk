// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

/**
 * @file
 * Nexthop groups are a forwarding/tunneling abstraction in EOS.
 *
 * A nexthop group is comprised of a tunneling protocol (IP/GRE or
 * MPLS, for example) and a collection of nexthop (aka destination)
 * IP addresses and other forwarding information (such as MPLS stack
 * operations to apply for traffic sent to that nexthop). The same
 * IP address may be specified in more than one entry within the
 * group, allowing for unequal cost load balancing. By using distinct
 * addresses for each entry, equal cost load balancing can be achieved.
 *
 * The nexthop or destination IP is the tunnel (outer) destination IP
 * address for GRE and IP-in-IP. For MPLS, the nexthop address is used
 * to find (via ARP/ND) a MAC address for the MPLS next hop.
 *
 * Nexthop entries must be manually monitored and maintained by the
 * agent. If a tunnel destination (aka nexthop) becomes unreachable,
 * traffic hashed to that entry will be black-holed in the network
 * until a working entry is set in that index of the nexthop group, or
 * the entry is deleted.
 *
 * Presently, all nexthop groups encapsulate traffic directed to them,
 * either as an IP-in-IP (IP protocol 4) tunnel, a GRE (IP protocol
 * 47) tunnel encapsulating either IPv4, IPv6 or MPLS traffic, or as
 * pure MPLS frames. MPLS label switching operations are also
 * supported, see the nexthop_group_entry_t class for more
 * information.
 *
 * Presently, MPLS switching actions are only only supported when used
 * with PBR and cannot be used with IP routes.
 *
 * The following example creates a nexthop group called "nhg1" which
 * performs GRE encapsulation of traffic sent to it, sending traffic
 * to two different nexthop IP addresses unequally (at a 2/3 to 1/3
 * ratio). For a usage of a nexthop group with policy routing, see the
 * policy_map.h file.
 *
 * @code
 *   eos::nexthop_group_t nhg("nhg1", eos::NEXTHOP_GROUP_GRE);
 *   // Specify two destinations (nexthop group entries) for the traffic
 *   eos::nexthop_group_entry_t nhe1(eos::ip_addr_t("172.12.1.1"));
 *   eos::nexthop_group_entry_t nhe2(eos::ip_addr_t("172.12.1.2"));
 *   // Set the nexthop group entries on the group with unequal cost load balancing
 *   // Balance traffic 2/3 to 172.12.1.1, 1/3 to 172.12.1.2.
 *   nhg.nexthop_set(0, nhe1);
 *   nhg.nexthop_set(1, nhe1);
 *   nhg.nexthop_set(2, nhe2);
 * @endcode
 */

#ifndef EOS_NEXTHOP_GROUP_H
#define EOS_NEXTHOP_GROUP_H

#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/iterator.h>
#include <eos/mpls.h>

#include <eos/types/nexthop_group.h>

namespace eos {

class nexthop_group_mgr;

/// This class handles changes to a nexthop group's status
class EOS_SDK_PUBLIC nexthop_group_handler :
      public base_handler<nexthop_group_mgr, nexthop_group_handler> {
 public:
   explicit nexthop_group_handler(nexthop_group_mgr *);
   nexthop_group_mgr * get_nexthop_group_mgr() const;

   /**
    * Registers this class to receive change updates on all nexthop groups.
    *
    * Expects a boolean signifying whether notifications should be
    * propagated to this instance or not.
    */
   void watch_all_nexthop_groups(bool);

  /**
    * Registers this class to receive change updates on the given nexthop group.
    *
    * Expects the name of the corresponding nexthop group and a
    * boolean signifying whether notifications should be propagated to
    * this instance or not.
    */
   void watch_nexthop_group(std::string const & nexthop_group_name, bool);

   /// Handler called when the active status of a nexthop_group changes
   virtual void on_nexthop_group_active(std::string const & nexthop_group_name,
                                        bool active);

   /**
    * Handler called when the nexthop_group is programmed in response to a
    * configuration change.
    */
   virtual void on_nexthop_group_programmed(std::string const & nexthop_group_name);
};

class nexthop_group_iter_impl;

// An iterator that yields nexthop group for each configured nexthop group
class EOS_SDK_PUBLIC nexthop_group_iter_t :
      public iter_base<nexthop_group_t, nexthop_group_iter_impl> {
 private:
   friend class nexthop_group_iter_impl;
   explicit nexthop_group_iter_t(nexthop_group_iter_impl * const) EOS_SDK_PRIVATE;
};

class programmed_nexthop_group_iter_impl;

// An iterator that yields nexthop group name for each programmed nexthop group
class EOS_SDK_PUBLIC programmed_nexthop_group_iter_t :
      public iter_base<std::string, programmed_nexthop_group_iter_impl> {
 private:
   friend class programmed_nexthop_group_iter_impl;

   explicit programmed_nexthop_group_iter_t(
         programmed_nexthop_group_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * A manager of 'nexthop-group' configurations.
 *
 * Create one of these via an sdk object prior to starting the agent main loop.
 * When your eos::agent_handler::on_initialized virtual function is called, the
 * manager is valid for use.
 */
class EOS_SDK_PUBLIC nexthop_group_mgr :
      public base_mgr<nexthop_group_handler, std::string> {
 public:
   virtual ~nexthop_group_mgr();

   virtual void resync_init() = 0;
   virtual void resync_complete() = 0;

   /// Iterates over all the nexthop groups currently configured.
   virtual nexthop_group_iter_t nexthop_group_iter() const = 0;

   /** 
    * Retrieves an existing nexthop_group_t by name, if it exists.
    * Otherwise this returns an empty `nexthop_group_t()`
    */
   virtual nexthop_group_t nexthop_group(std::string const & 
                                         nexthop_group_name) const = 0;

   /** 
    * Returns the counter corresponding to the given nexthop group name and 
    * entry, if it exists. 
    * Otherwise this returns an empty 'nexthop_group_entry_counter_t()'
    *
    * Counters are reset whenever nexthop group entry configuration changes.
    */
   virtual nexthop_group_entry_counter_t counter(
         std::string const & nexthop_group_name, uint16_t entry) const = 0;

   /// Returns true if a nexthop group with the given name has been configured.
   virtual bool exists(std::string const & nexthop_group_name) const = 0;

   /**
    * Returns whether or not the given nexthop group is active.
    *
    * Nexthop groups are active if the FIB has prefixes using this
    * group. Deleting an active nexthop group will cause all prefixes
    * that point to that nexthop group to blackhole their traffic.
    *
    * In order to hitlessly delete a nexthop group, first delete all
    * prefixes that point to it, wait for the nexthop group to no
    * longer be active (using
    * nexthop_group_handler::on_nexthop_group_active), and then delete
    * the nexthop group.
    */
   virtual bool active(std::string const & nexthop_group_name) const = 0;

   /// Creates or updates a nexthop group.
   virtual void nexthop_group_set(nexthop_group_t const &) = 0;
   /// Removes the named nexthop group from the configuration if it exists
   virtual void nexthop_group_del(std::string const & nexthop_group_name) = 0;

   // Iterate over all successfully programmed nexthop groups.
   virtual programmed_nexthop_group_iter_t
      programmed_nexthop_group_iter() const = 0;

   // Returns the programmed nexthop group for a given nexthop group name.
   virtual nexthop_group_t
      programmed_nexthop_group(std::string const & nexthop_group_name)
      const = 0;
 protected:
   nexthop_group_mgr() EOS_SDK_PRIVATE;
   friend class nexthop_group_handler;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(nexthop_group_mgr);
};

} // end namespace eos

#include <eos/inline/nexthop_group.h>

#endif // EOS_NEXTHOP_GROUP_H
