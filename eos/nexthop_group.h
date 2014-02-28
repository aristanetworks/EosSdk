// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_NEXTHOP_GROUP_H
#define EOS_NEXTHOP_GROUP_H

#include <forward_list>

#include <eos/intf.h>
#include <eos/ip.h>

namespace eos {

/// A nexthop destination IP array index number, an int 0..255
typedef enum {
   NEXTHOP_DESTINATION_IP_INDEX_MIN=0,
   NEXTHOP_DESTINATION_IP_INDEX_MAX=255,
} nexthop_destination_ip_index_t;

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
    * source_intf() will be cleared after the source IP is set.
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
    * Use in conjunction with size_is() to set the length of the list
    * to program upon policy_map_commit(). Use duplicate addresses in
    * different sequence numbers to perform unequal cost multipath.
    * Setting a value at an index beyond size() is undefined.
    *
    * @param nexthop_destination_ip_index_t Index into the destination IP array.
    * @param ip_addr_t The IP address to set at the index.
    */
   void destination_ip_is(nexthop_destination_ip_index_t, ip_addr_t const &);
   /// Returns a reference to the current destination address list.
   std::forward_list<ip_addr_t> const & destination_address() const;

   /**
    * Sets the size of the destination IP address list for this group.
    *
    * @param size The new length or size of the list
    */
   void size_is(uint8_t size);
   /// The number of destination IP addresses in this nexthop group.
   uint8_t size() const;

   /// Sets the config persistence for this nexthop group (defaults to false).
   void persistent_is(bool);
   /// The persistence state for this nexthop group.
   bool persistent() const;

 private:
   std::string name_;
   uint8_t ttl_;
   uint8_t size_;
   ip_addr_t const & source_ip_;
   std::forward_list<ip_addr_t> destination_ip_;
   intf_id_t source_intf_;
   nexthop_group_encap_t encap_type_;
   bool persistent_;
};

} // end namespace eos

#endif // EOS_NEXTHOP_GROUP_H
