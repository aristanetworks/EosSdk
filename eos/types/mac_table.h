// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_MAC_TABLE_H
#define EOS_TYPES_MAC_TABLE_H

#include <eos/eth.h>
#include <eos/intf.h>
#include <eos/utility.h>
#include <sstream>

namespace eos {

/**
 * An entry from the MAC address table.
 * TODO: add entry type, number of moves, last move time.
 */
class EOS_SDK_PUBLIC mac_entry_t {
 public:
   mac_entry_t();
   mac_entry_t(eth_addr_t eth_addr, intf_id_t intf);

   /** Getter for 'eth_addr': the MAC address that was learned. */
   eth_addr_t eth_addr() const;

   /** Getter for 'intf': the interface from which the MAC address was learned. */
   intf_id_t intf() const;

   /** Non-existent entries are effectively false (so this returns true). */
   bool operator!() const;

   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of mac_entry_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const mac_entry_t& obj);

 private:
   eth_addr_t eth_addr_;
   intf_id_t intf_;
};

}

#include <eos/inline/types/mac_table.h>

#endif // EOS_TYPES_MAC_TABLE_H
