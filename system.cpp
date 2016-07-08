// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/system.h"
#include "impl.h"

namespace eos {

//
// system_mgr implementation
//

class system_mgr_impl : public system_mgr {
 public:
   system_mgr_impl() {
   }

   std::string hostname() const {
      return "localhost";
   }

   std::string fqdn() const {
      return "localhost";
   }

   std::string serial_number() const {
      return "None";
   }

   std::string model_name() const {
      return "None";
   }

   std::string hardware_revision() const {
      return "None";
   }

   std::string software_revision() const {
      return "None";
   }

   eth_addr_t system_mac() const {
      return eth_addr_t();
   }
};

DEFINE_STUB_MGR_CTOR(system_mgr)

system_handler::system_handler(system_mgr * mgr) : 
      base_handler<system_mgr, system_handler>(mgr) {
}

void system_handler::on_hostname(std::string const & hostname) {
}

void system_handler::on_fqdn(std::string const & fqdn) {
}

void system_handler::on_system_info_initialized() {
}

} // end eos namespace
