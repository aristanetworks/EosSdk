// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/neighbor_table.h"

namespace eos {

class neighbor_table_mgr_impl : public neighbor_table_mgr {
 public:
   neighbor_table_mgr_impl() {
   }

   virtual neighbor_entry_t neighbor_entry(intf_id_t intf, ip_addr_t addr) const {
      return neighbor_entry_t();
   }
};

neighbor_table_mgr::neighbor_table_mgr() {
}

neighbor_table_mgr::~neighbor_table_mgr() {
}

}
