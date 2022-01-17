// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/fpga.h"
#include "impl.h"

namespace eos {

fpga_handler::fpga_handler(fpga_mgr * mgr) :
      base_handler<fpga_mgr, fpga_handler>(mgr) {
}

void
fpga_handler::watch_all_fpga(bool interest) {
}

void
fpga_handler::watch_fpga(const fpga_t & fpga, bool interest) {
}

void
fpga_handler::on_fpga_load_image(const fpga_t & fpga) {
}

void
fpga_handler::on_fpga_load_image_failed(const fpga_t & fpga) {
}

void
fpga_handler::on_fpga_unload_image(const fpga_t & fpga) {
}

class fpga_mgr_impl : public fpga_mgr {
   public:
      fpga_mgr_impl() {
      }

      fpga_iter_t fpga_status_iter() const {
         fpga_iter_t * nop = 0;
         return *nop;
      }
};

DEFINE_STUB_MGR_CTOR(fpga_mgr)

} // end namespace eos
