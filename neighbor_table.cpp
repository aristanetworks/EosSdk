// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/neighbor_table.h"
#include "impl.h"

namespace eos {

class neighbor_table_mgr_impl : public neighbor_table_mgr {
 public:
   neighbor_table_mgr_impl() {
   }

   neighbor_table_iter_t neighbor_table_iter() const {
      neighbor_table_iter_t * nop = 0;
      return *nop;
   }

   virtual neighbor_entry_t neighbor_entry_status(neighbor_key_t const & key) const {
      return neighbor_entry_t();
   }

   virtual void neighbor_entry_set(neighbor_entry_t const & entry) {}
   virtual void neighbor_entry_del(neighbor_key_t const & key) {}

   virtual neighbor_entry_t neighbor_entry(
                               neighbor_key_t const & key) const {
      return neighbor_entry_t();
   }


};

DEFINE_STUB_MGR_CTOR(neighbor_table_mgr)

neighbor_table_handler::neighbor_table_handler(neighbor_table_mgr *mgr) :
                              base_handler(mgr) {
}
void neighbor_table_handler::watch_all_neighbor_entries(bool interest) {
}
void neighbor_table_handler::watch_neighbor_entry(neighbor_key_t const & key,
                                                   bool interest) {
}
void neighbor_table_handler::on_neighbor_entry_del(neighbor_key_t const & key) {
}
void neighbor_table_handler::on_neighbor_entry_set(neighbor_entry_t const & entry) {
}

} // end eos namespace
