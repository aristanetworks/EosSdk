// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/aresolve.h"

namespace eos {

aresolve_record_host::aresolve_record_host() {
   addr_v4_.push_back(ip_addr_t("1.2.3.4"));
   addr_v6_.push_back(ip_addr_t("dead::beef:1"));
}

aresolve_record_host::~aresolve_record_host() {
   addr_v4_.clear();
   addr_v6_.clear();
}

aresolve_handler::aresolve_handler(aresolve_mgr * mgr) : base_handler(mgr) {
}

void aresolve_handler::watch_host(std::string const &, bool) {
}

void aresolve_handler::on_aresolve_host(aresolve_record_host const & record) {
}

class aresolve_mgr_impl : public aresolve_mgr {
 public:
   aresolve_mgr_impl() {
   }

   uint32_t aresolve_short_time() const {
      return 1;
   }

   uint32_t aresolve_long_time() const {
      return 300;
   }

   void aresolve_short_time_is(uint32_t time) {
   }

   void aresolve_long_time_is(uint32_t time) {
   }

   void on_aresolve_host(aresolve_record_host const &) {
   }

};

aresolve_mgr::~aresolve_mgr() {
}

}
