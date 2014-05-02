// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_NEXTHOP_GROUP_H
#define EOS_NEXTHOP_GROUP_H

#include <map>

#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/iterator.h>

namespace eos {

/**
 * The type of encapsulation to use for this nexthop group.
 *
 * By default, nexthop_group_t are in NEXTHOP_GROUP_IP_IN_IP mode.
 */
enum nexthop_group_encap_t {
   NEXTHOP_GROUP_TYPE_NULL,
   NEXTHOP_GROUP_IP_IN_IP,   ///< IP in IP encapsulation
   NEXTHOP_GROUP_GRE,        ///< GRE encapsulation
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
   /// Constructs a nexthop group given a name and nexthop group type.
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
    */
   void source_ip_is(ip_addr_t const &);
   /// The source IP for frames sent on this group.
   ip_addr_t const & source_ip() const;

   /**
    * Sets a source interface.
    * Setting this value causes previous calls source_ip() to lose effect.
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
    * @param uint8_t Index into the destination IP array.
    * @param ip_addr_t The IP address to set at the index. This must
    * be an IPv4 address.
    */
   void destination_ip_is(uint8_t, ip_addr_t const &);
   /// Returns a reference to the current destination address list.
   std::map<uint8_t, ip_addr_t> const & destination_address() const;

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
   std::map<uint8_t, ip_addr_t> destination_ip_;
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
