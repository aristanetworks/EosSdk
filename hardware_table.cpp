// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/hardware_table.h"
#include "impl.h"

namespace eos {

class hardware_table_mgr_impl : public hardware_table_mgr {
 public:
   hardware_table_mgr_impl() {
   }
   
   virtual bool exists(hardware_table_key_t const & key) const {
      return false;
   }

   virtual hardware_table_iter_t hardware_table_iter() const {
      hardware_table_iter_t * nop = 0;
      return *nop;
   }
   
   virtual hardware_table_usage_t usage(hardware_table_key_t const & key) const {
      return hardware_table_usage_t();
   }

   virtual uint32_t max_entries(hardware_table_key_t const & key) const {
      return 0;
   }

   virtual hardware_table_high_watermark_t
      high_watermark(hardware_table_key_t const & key) const {
      return hardware_table_high_watermark_t();
   }
};

DEFINE_STUB_MGR_CTOR(hardware_table_mgr)

hardware_table_handler::hardware_table_handler(hardware_table_mgr *mgr) :
                           base_handler(mgr) {}

void hardware_table_handler::watch_all_hardware_tables(bool enable) {}

void hardware_table_handler::watch_hardware_table(hardware_table_key_t const & key, 
                                                  bool enable) {}

void hardware_table_handler::on_hardware_table_entry_set(
                                 hardware_table_key_t const & key,
                                 hardware_table_entry_t const & entry) {}

void hardware_table_handler::on_hardware_table_entry_del(
                                 hardware_table_key_t const & key) {}

} // end eos namespace
