// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <EosSdk/eth.h>
#include <EosSdk/panic.h>

#include <Arnet/EthAddr.h>

#include "Conversions.h"

namespace eos {

eth_addr_t::eth_addr_t() : words_({ 0, 0, 0 }) {
}

template <typename T>
static Arnet::EthAddr init_from_string(T mac) {
   try {
      Tac::Expect exception(Tac::Exception::rangeException_);
      Arnet::EthAddr addr;
      addr.stringValueIs(mac);
      return addr;
   } catch(Tac::RangeException e) {
      panic("Invalid MAC address");
   }
}

eth_addr_t::eth_addr_t(char const * addr) {
   *this = convert(init_from_string(addr));
}

eth_addr_t::eth_addr_t(const std::string & addr) {
   // TODO: Remove this code duplication by using a delegating constructor.
   // Apparently our >3 year old version of g++ (4.5.1 now) doesn't parse
   // those, we need at least 4.7.
   *this = convert(init_from_string(addr));
}

eth_addr_t::eth_addr_t(uint16_t word0, uint16_t word1, uint16_t word2)
   : words_({ word0, word1, word2 }) {
}

bool
eth_addr_t::operator!() const {
   return !words_[0] && !words_[1] && !words_[2];
}

bool
eth_addr_t::operator==(eth_addr_t const & other) const {
   return words_[0] == other.words_[0]
      && words_[1] == other.words_[1]
      && words_[2] == other.words_[2];
}

bool
eth_addr_t::operator!=(eth_addr_t const & other) const {
   return !(*this == other);
}

std::string
eth_addr_t::to_string() const {
   return convert(*this).stringValue().stdString();
}

}
