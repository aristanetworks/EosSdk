// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_MAC_TABLE_H
#define EOS_MAC_TABLE_H

#include <eos/base.h>
#include <eos/eth.h>
#include <eos/intf.h>

#include <eos/types/mac_table.h>

namespace eos {

/**
 * Manager for the MAC address table.
 */
class EOS_SDK_PUBLIC mac_table_mgr {
 public:
   virtual ~mac_table_mgr();
   /**
    * Returns the MAC table entry for the given VLAN and MAC address.
    * If the given MAC is not found, or if the VLAN queried doesn't exist,
    * an empty mac_entry_t is returned (use the operator!() to easily
    * determine whether that is the case).
    * @param vlan The VLAN in which to perform the look up.
    * @param mac The MAC address to look up.
    */
   virtual mac_entry_t mac_entry(vlan_id_t vlan, eth_addr_t mac) const = 0;

 protected:
   mac_table_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(mac_table_mgr);
};

}

#endif // EOS_MAC_TABLE_H
