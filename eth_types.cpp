// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/eth.h"
#include <assert.h>
#include <string.h>

namespace eos {

eth_addr_t::eth_addr_t(char const * addr) :
      bytes_({}) {
   // TODO: No op impl.
}

eth_addr_t::eth_addr_t(std::string const & addr) :
      bytes_({}) {
   // TODO: No op impl.
}

bool
eth_addr_t::operator<(eth_addr_t const & other) const {
   return memcmp(bytes_, other.bytes_, 6) < 0;
}

uint8_t
eth_addr_t::byte(int index) const {
   
   if (0 <= index && index <= 5) {
      return bytes_[index];
   }
   assert(!"invalid byte index, must be in [0; 5].");
   
}

void
eth_addr_t::bytes(void * arr) const {
   memcpy(arr, bytes_, sizeof(bytes_));
}




static inline std::string
internal_vlan_error_msg(vlan_id_t vlan) {
   std::stringstream str;
   str << "VLAN " << vlan << "is an internal VLAN and cannot be used on"
      " a trunk port";
   return str.str();
}



internal_vlan_error::internal_vlan_error(vlan_id_t vlan) noexcept :
      configuration_error(internal_vlan_error_msg(vlan)), vlan_(vlan) {
   
}


}
