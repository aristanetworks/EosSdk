// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/mac_table.h"

namespace eos {

class mac_table_mgr_impl : public mac_table_mgr {
 public:
   mac_table_mgr_impl() {
   }
};

mac_table_mgr *
get_mac_table_mgr() {
   static mac_table_mgr_impl impl;
   return &impl;
}

mac_table_mgr::mac_table_mgr() {
}

mac_entry_t
mac_table_mgr::mac_entry(vlan_id_t vlan, eth_addr_t mac) const {
   return mac_entry_t();
}

}
