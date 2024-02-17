// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/eth.h"
#include <assert.h>
#include <impl.h>
#include <string.h>

namespace eos {

eth_addr_t::eth_addr_t(char const * addr) :
      bytes_{} {
   eos::eth_addr_t_to_bytes(addr, bytes_);
}

eth_addr_t::eth_addr_t(std::string const & addr) :
      bytes_{} {
   eos::eth_addr_t_to_bytes(addr.c_str(), bytes_);
}

bool
eth_addr_t::operator<(eth_addr_t other) const {
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

bool
eth_addr_t::is_unicast() const {
   return ((bytes_[0] & 0x01) == 0);
}

bool
eth_addr_t::is_multicast() const {
   return (!is_unicast() && !is_broadcast());
}

bool
eth_addr_t::is_broadcast() const {
   
   return (bytes_[0] == 0xff && bytes_[1] == 0xff &&
           bytes_[2] == 0xff && bytes_[3] == 0xff &&
           bytes_[4] == 0xff && bytes_[5] == 0xff);
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
