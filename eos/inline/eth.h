// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_ETH_H
#define EOS_INLINE_ETH_H

namespace eos {

inline eth_addr_t::eth_addr_t() : bytes_() {
}

inline eth_addr_t::eth_addr_t(uint8_t byte0, uint8_t byte1, uint8_t byte2,
                              uint8_t byte3, uint8_t byte4, uint8_t byte5)
   : bytes_{ byte0, byte1, byte2, byte3, byte4, byte5 } {
}

inline eth_addr_t::eth_addr_t(uint8_t const bytes[6])
   : bytes_{ bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5] } {
}

inline bool
eth_addr_t::operator!() const {
   return !bytes_[0] && !bytes_[1] && !bytes_[2]
      && !bytes_[3] && !bytes_[4] && !bytes_[5];
}

inline
eth_addr_t::operator bool() const {
   return !!(*this);
}

inline bool
eth_addr_t::operator==(eth_addr_t const & other) const {
   return bytes_[0] == other.bytes_[0]
      && bytes_[1] == other.bytes_[1]
      && bytes_[2] == other.bytes_[2]
      && bytes_[3] == other.bytes_[3]
      && bytes_[4] == other.bytes_[4]
      && bytes_[5] == other.bytes_[5];
}

inline bool
eth_addr_t::operator!=(eth_addr_t const & other) const {
   return !(*this == other);
}

}

#endif // EOS_INLINE_ETH_H
