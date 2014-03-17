// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>
#include <cstring>

#include "eos/eth.h"

namespace eos {

eth_addr_t::eth_addr_t(char const *) : bytes_() {
   // TODO: No op impl.
}

eth_addr_t::eth_addr_t(const std::string &) : bytes_() {
   // TODO: No op impl.
}

std::string
eth_addr_t::to_string() const {
   return "not.implemented";  // TODO: No op impl.
}

uint8_t
eth_addr_t::byte(int index) const {
   if (0 <= index && index <= 5) {
      return bytes_[index];
   }
   assert(!"invalid byte index, must be in [0; 5].");
}

void
eth_addr_t::bytes(void *arr) const {
   memcpy( arr, bytes_, sizeof( bytes_ ) );
}

bool
eth_addr_t::operator<(eth_addr_t const & other) const {
   return memcmp(bytes_, other.bytes_, 6) < 0;
}

};
