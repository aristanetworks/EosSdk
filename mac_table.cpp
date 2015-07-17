// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/mac_table.h"
#include "impl.h"

namespace eos {

class mac_table_mgr_impl : public mac_table_mgr {
 public:
   mac_table_mgr_impl() {
   }

   virtual mac_table_iter_t mac_table_iter() const {
      mac_table_iter_t * nop = 0;
      return *nop;
   }

   virtual mac_table_status_iter_t mac_table_status_iter() const {
      mac_table_status_iter_t * nop = 0;
      return *nop;
   }

   virtual mac_entry_t mac_entry_status(mac_key_t const & key) const {
      return mac_entry_t();
   }
   
   virtual mac_entry_t mac_entry(mac_key_t const & key) const {
      return mac_entry_t();
   }

   virtual mac_entry_t mac_entry(vlan_id_t vlan, eth_addr_t mac) const {
      return mac_entry_t();
   }

   virtual mac_entry_type_t type(mac_key_t const & key) const {
      return mac_entry_type_t();
   }

   virtual seconds_t last_move_time(mac_key_t const & key) const {
      return 0;
   }

   virtual uint32_t moves(mac_key_t const & key) const {
      return 0;
   }

   virtual void mac_entry_set(mac_entry_t const & entry) {}
   virtual void mac_entry_del(mac_key_t const & key) {}


};

DEFINE_STUB_MGR_CTOR(mac_table_mgr)

mac_table_handler::mac_table_handler(mac_table_mgr *mgr) :
   base_handler(mgr) {
}
void mac_table_handler::watch_all_mac_entries(bool all) {}
void mac_table_handler::watch_mac_entry(mac_key_t const & key, bool interest) {}

void mac_table_handler::on_mac_entry_set(mac_entry_t const & entry) {}
void mac_table_handler::on_mac_entry_del(mac_key_t const & key) {}

} // end namespace eos
