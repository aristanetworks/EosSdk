// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_IP_IMPL_H
#define EOS_INLINE_TYPES_IP_IMPL_H

namespace eos {







ip_addr_mask_impl_t::ip_addr_mask_impl_t() :
      addr_(ip_addr_t()), mask_length_() {
}

ip_addr_mask_impl_t::ip_addr_mask_impl_t(ip_addr_t const & addr,
                                                uint8_t mask_length) {

   addr_ = addr;
   if (mask_length < 129) {
      mask_length_ = uint8_t(mask_length);
   } else {
      panic(invalid_argument_error("ip.ip_addr_mask_t",
                                   "mask_length must be between 0..128."));
   }

}

ip_addr_t
ip_addr_mask_impl_t::addr() const {
   return addr_;
}

uint8_t
ip_addr_mask_impl_t::mask_length() const {
   return mask_length_;
}

af_t
ip_addr_mask_impl_t::af() const {
   return addr_.af();
}

uint32_be_t
ip_addr_mask_impl_t::mask() const {

   if (mask_length_ == 0) {
      return 0;
   }
   uint32_be_t r = (0xFFFFFFFF << (32 - mask_length_)) & 0xFFFFFFFF;
   return r;

}

std::string
ip_addr_mask_impl_t::to_string() const {

   if (addr_.af() == AF_IPV6 || addr_.af() == AF_IPV4) {
      // Emit the address/mask_length for IPV6/IPV4 addresses
      char buf[128];
      int rv;
      rv = snprintf(buf, sizeof(buf), "%s/%d",
                    addr_.to_string().c_str(), mask_length_);
      assert(rv>0);
      return std::string(buf);
   } else {
      panic(
         invalid_argument_error(
            "ip.ip_addr_mask_t",
            "Must have a valid address family to convert to string."));
   }

}

bool
ip_addr_mask_impl_t::operator==(ip_addr_mask_impl_t const & other) const {
   return addr_ == other.addr_ &&
          mask_length_ == other.mask_length_;
}

bool
ip_addr_mask_impl_t::operator!=(ip_addr_mask_impl_t const & other) const {
   return !operator==(other);
}

bool
ip_addr_mask_impl_t::operator<(ip_addr_mask_impl_t const & other) const {
   if(addr_ != other.addr_) {
      return addr_ < other.addr_;
   } else if(mask_length_ != other.mask_length_) {
      return mask_length_ < other.mask_length_;
   }
   return false;
}

uint32_t
ip_addr_mask_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
ip_addr_mask_impl_t::mix_me(hash_mix & h) const {
   h.mix(addr_); // ip_addr_t
   h.mix(mask_length_); // uint8_t
}

std::ostream&
operator<<(std::ostream& os, const ip_addr_mask_impl_t& obj) {
   os << obj.to_string();
   return os;
}




}

#include <eos/inline/types/ip.h>

#endif // EOS_INLINE_TYPES_IP_IMPL_H
