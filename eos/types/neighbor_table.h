// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_NEIGHBOR_TABLE_H
#define EOS_TYPES_NEIGHBOR_TABLE_H

#include <eos/eth.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <sstream>

namespace eos {

/** Neighbor entry types. */
enum neighbor_entry_type_t {
   NEIGHBOR_ENTRY_TYPE_DYNAMIC,
   NEIGHBOR_ENTRY_TYPE_STATIC,
};
/**
 * Appends a string representation of enum neighbor_entry_type_t value to the
 * ostream.
 */
std::ostream& operator<<(std::ostream& os, 
                         const neighbor_entry_type_t & enum_val);

/**
 * The neighbor entry class.
 * Maps an IP address to its associated MAC address.
 */
class EOS_SDK_PUBLIC neighbor_entry_t {
 public:
   neighbor_entry_t();
   neighbor_entry_t(ip_addr_t ip_addr, eth_addr_t eth_addr, 
                    neighbor_entry_type_t entry_type);

   /** Getter for 'ip_addr': the ip address of neighbor entry. */
   ip_addr_t ip_addr() const;

   /** Getter for 'eth_addr': the Ethernet address of neighbor entry. */
   eth_addr_t eth_addr() const;

   /**
    * Getter for 'entry_type': the type of neighbor entry, it will be either STATIC
    * or DYNAMIC.
    */
   neighbor_entry_type_t entry_type() const;

   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * neighbor_entry_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, 
                                   const neighbor_entry_t& obj);

 private:
   ip_addr_t ip_addr_;
   eth_addr_t eth_addr_;
   neighbor_entry_type_t entry_type_;
};
}

#include <eos/inline/types/neighbor_table.h>

#endif // EOS_TYPES_NEIGHBOR_TABLE_H
