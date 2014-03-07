// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_NEIGHBOR_TABLE_H
#define EOS_NEIGHBOR_TABLE_H

#include <eos/eth.h>
#include <eos/intf.h>
#include <eos/ip.h>

namespace eos {

enum neighbor_entry_type_t {
   NEIGHBOR_ENTRY_TYPE_DYNAMIC,
   NEIGHBOR_ENTRY_TYPE_STATIC,
};

/**
 * The neighbor entry class.
 *
 * Maps an IP address to its associated MAC address
 */
class EOS_SDK_PUBLIC neighbor_entry_t {
  public:
   neighbor_entry_t();
   neighbor_entry_t(ip_addr_t, eth_addr_t, neighbor_entry_type_t);

   ip_addr_t ip_addr() const;
   eth_addr_t eth_addr() const;
   neighbor_entry_type_t entry_type() const;
   
  private:
   ip_addr_t ip_addr_;
   eth_addr_t eth_addr_;
   neighbor_entry_type_t entry_type_;
};

/**
 * The neighbor table manager.
 *
 * This class provides access to the resolved MAC address for a
 * given IP address off of an L3 interface (aka the ARP table for
 * IPv4 addresses and the Neighbor Discovery table for IPv6 addresses)
*/
class EOS_SDK_PUBLIC neighbor_table_mgr {
  public:

   // Attribute accessors

   /// Lookup an neighbor entry for a given L3 interface and IP address
   neighbor_entry_t neighbor_entry(intf_id_t, ip_addr_t) const;

 protected:
   neighbor_table_mgr() EOS_SDK_PRIVATE;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(neighbor_table_mgr);
};

/// Returns the neighbor table manager.
neighbor_table_mgr * get_neighbor_table_mgr() EOS_SDK_PUBLIC;

} // end namespace eos

#include <eos/inline/neighbor_table.h>

#endif // EOS_NEIGHBOR_TABLE_H
