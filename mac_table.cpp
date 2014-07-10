// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/mac_table.h"
#include "impl.h"

namespace eos {

class mac_table_mgr_impl : public mac_table_mgr {
 public:
   mac_table_mgr_impl() {
   }

   mac_entry_t mac_entry(vlan_id_t vlan, eth_addr_t mac) const {
      return mac_entry_t();
   }
};

DEFINE_STUB_MGR_CTOR(mac_table_mgr)

}
