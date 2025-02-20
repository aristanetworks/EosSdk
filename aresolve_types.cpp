// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
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


}
