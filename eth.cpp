// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <EosSdk/eth.h>

namespace eos {

eth_addr_t::eth_addr_t() : ethAddr_(0, 0, 0) {
}

eth_addr_t::eth_addr_t(char const * addr) {
   ethAddr_.stringValueIs( addr );
   validate();
   // todo
}

eth_addr_t::eth_addr_t(const Arnet::EthAddr & ethAddr) {
   ethAddr_ = ethAddr;
}

bool
eth_addr_t::operator==(eth_addr_t const & other) {
   return (ethAddr_ == other.ethAddr_);
}

bool
eth_addr_t::operator!=(eth_addr_t const & other) {
   return (ethAddr_ != other.ethAddr_);
}

void
eth_addr_t::validate() {
   // Make sure this is a valid MAC address.
   // If not, call panic().
}

void
eth_addr_t::to_string(char *namebuf, size_t namebuf_size) {
   Tac::String name = ethAddr_.stringValue();
   char const * ptr = name.charPtr();
   strncpy( namebuf, ptr, namebuf_size );
   namebuf[namebuf_size - 1] = 0;
}

}
