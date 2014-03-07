// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

namespace eos {

class neighbor_table_mgr_impl : public neighbor_table_mgr {
 public:
   intf_mgr_impl() {
   }
};

neighbor_table_mgr *
get_neighbor_table_mgr() {
   static intf_mgr_impl impl;
   return &impl;
}

neighbor_table_mgr::neighbor_table_mgr() {
}

neighbor_entry_t
neighbor_table_mgr::neighbor_entry(intf_id_t intf, ip_addr_t addr) {
   return neighbor_entry_t();
}

}
