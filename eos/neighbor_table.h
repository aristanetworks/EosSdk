// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_NEIGHBOR_TABLE_H
#define EOS_NEIGHBOR_TABLE_H

#include <eos/eth.h>
#include <eos/intf.h>
#include <eos/ip.h>

#include <eos/types/neighbor_table.h>

namespace eos {

/**
 * The neighbor table manager.
 *
 * This class provides access to the resolved MAC address for a
 * given IP address off of an L3 interface (aka the ARP table for
 * IPv4 addresses and the Neighbor Discovery table for IPv6 addresses).
*/
class EOS_SDK_PUBLIC neighbor_table_mgr {
 public:
   virtual ~neighbor_table_mgr();

   // Attribute accessors

   /// Lookup an neighbor entry for a given L3 interface and IP address.
   virtual neighbor_entry_t neighbor_entry(intf_id_t, ip_addr_t) const = 0;

 protected:
   neighbor_table_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(neighbor_table_mgr);
};

} // end namespace eos

#endif // EOS_NEIGHBOR_TABLE_H
