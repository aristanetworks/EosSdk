/**
 * @file
 * The neighbor_table module manages ip/mac mapping tables, including IPV4 ARP table
 * and IPV6 neighbor table.
 *
 * This module provides APIs to create and delete static IPV4/IPV6 entries. It also
 * provides APIs to query the configured static entries and the learned
 * (both static/dynamic) entries on the system from IPV4 ARP table and IPV6 neighbor
 * table.
 *
 * Two handler APIs are provided to allow 3rd party agents to react to the addition
 * and deletion of entries in the learned ARP table or neighbor table on the system.
 */


// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_NEIGHBOR_TABLE_H
#define EOS_NEIGHBOR_TABLE_H

#include <eos/eth.h>
#include <eos/base_handler.h>
#include <eos/intf.h>
#include <eos/ip.h>

#include <eos/types/neighbor_table.h>

namespace eos {

class neighbor_table_mgr;

/**
 * The neighbor table handler.
 *
 * This class provides handler APIs to react to neighbor table entry deletion
 * and addition. It works for both v4 ARP table and v6 neighbor table.
 */
class EOS_SDK_PUBLIC neighbor_table_handler :
              public base_handler<neighbor_table_mgr, neighbor_table_handler> {
 public:
   explicit neighbor_table_handler(neighbor_table_mgr *mgr);
   neighbor_table_mgr * get_neighbor_table_mgr() const;

   virtual void on_neighbor_entry_set(neighbor_entry_t const & entry);
   virtual void on_neighbor_entry_del(neighbor_key_t const & key);
};

/**
 * The neighbor table manager.
 *
 * This class provides access to the resolved MAC address for a given IP address
 * off of an L3 interface (aka the ARP table for IPv4 addresses and the Neighbor
 * Discovery table for IPv6 addresses). It also provides APIs to delete/add v4
 * static ARP entry and v6 static neighbor table entries.
*/
class EOS_SDK_PUBLIC neighbor_table_mgr : public base_mgr<neighbor_table_handler> {
 public:
   virtual ~neighbor_table_mgr();

   // Attribute accessors

   /// Lookup a resolved neighbor entry for a given L3 interface and IP address.
   virtual neighbor_entry_t neighbor_entry_status(
                               neighbor_key_t const & key) const = 0;

   /**
    * Programmatically speciy neighbor table entries.
    *
    * Note "intf_id" is needed only for v6 case, since the ip/mac pair may not 
    * be unique. It's not needed for v4 case.
    */
   virtual void neighbor_entry_set(neighbor_entry_t const & entry) = 0;
   virtual void neighbor_entry_del(neighbor_key_t const & key) = 0;

   /// Lookup a configured neighbor entry for a given L3 interface and IP address.
   virtual neighbor_entry_t neighbor_entry(neighbor_key_t const & key) const = 0;

 protected:
   neighbor_table_mgr() EOS_SDK_PRIVATE;
   friend class neighbor_table_handler;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(neighbor_table_mgr);
};

#include <eos/inline/neighbor_table.h>

} // end namespace eos

#endif // EOS_NEIGHBOR_TABLE_H
