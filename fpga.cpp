// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/fpga.h"
#include "impl.h"

namespace eos {

fpga_handler::fpga_handler(fpga_mgr * mgr) :
      base_handler<fpga_mgr, fpga_handler>(mgr) {
}

void
fpga_handler::watch_all_fpga_reservation_status(bool) {
}

void
fpga_handler::watch_fpga_reservation_status(const std::string &, bool) {
}

void
fpga_handler::on_fpga_reservation_status_set(std::string id) {
}

void
fpga_handler::on_fpga_reservation_status_del(std::string id) {
}

class fpga_mgr_impl : public fpga_mgr {
   public:
      fpga_mgr_impl() {
      }

      fpga_iter_t fpga_status_iter() const {
         fpga_iter_t * nop = 0;
         return *nop;
      }

      fpga_reservation_iter_t reservation_iter() const {
         fpga_reservation_iter_t * nop = 0;
         return *nop;
      }

      fpga_reservation_status_iter_t reservation_status_iter() const {
         fpga_reservation_status_iter_t * nop = 0;
         return *nop;
      }

      bool reservation_exists(const std::string&) const {
         return false;
      }

      bool reservation_status_exists(const std::string&) const {
         return false;
      }

      fpga_reservation_t reservation(const std::string&) const {
         fpga_reservation_t * nop = 0;
         return *nop;
      }

      fpga_reservation_status_t reservation_status(const std::string&) const {
         fpga_reservation_status_t * nop = 0;
         return *nop;
      }

      void reservation_set(const fpga_reservation_t&) {
      }

      void reservation_del(const std::string&) {
      }
};

DEFINE_STUB_MGR_CTOR(fpga_mgr)

} // end namespace eos
