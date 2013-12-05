// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <EosSdk/eth.h>
#include <EosSdk/panic.h>

namespace eos {

eth_addr_t::eth_addr_t() : ethAddr_(0, 0, 0) {
}

eth_addr_t::eth_addr_t(char const * addr) {
   try {
      Tac::Expect exception(Tac::Exception::rangeException_);
      ethAddr_.stringValueIs( addr );
   } catch(Tac::RangeException e) {
      panic("Invalid MAC address");
   }
}

eth_addr_t::eth_addr_t(const Arnet::EthAddr & ethAddr) {
   ethAddr_ = ethAddr;
}

bool
eth_addr_t::operator !() const {
   return !ethAddr_;
}

bool
eth_addr_t::operator==(eth_addr_t const & other) {
   return (ethAddr_ == other.ethAddr_);
}

bool
eth_addr_t::operator!=(eth_addr_t const & other) {
   return (ethAddr_ != other.ethAddr_);
}

std::string
eth_addr_t::to_string() const {
   return ethAddr_.stringValue().stdString();
}

}
