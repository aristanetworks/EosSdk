// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_IP_H
#define EOS_INLINE_TYPES_IP_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const af_t & enum_val) {
   if (enum_val==AF_NULL) {
      os << "AF_NULL";
   } else if (enum_val==AF_IPV4) {
      os << "AF_IPV4";
   } else if (enum_val==AF_IPV6) {
      os << "AF_IPV6";
   } else {
      os << "Unknown value";
   }
   return os;
}


// default constructor produces has AF_NULL, making it invalid to pass to many
// higher level constructors.
ip_addr_t::ip_addr_t() :
      af_(AF_NULL), addr_() {
   memset(&addr_, 0, sizeof(addr_));
}

ip_addr_t::ip_addr_t(std::string const & address_string) {

   memset(&addr_, 0, sizeof(addr_));
   if (!parse_ip_addr(address_string.c_str(), this)) {
      panic(invalid_argument_error("ip.ip_addr_t",
                                   "invalid IP address."));
   }

}

// Parse the IPv4 or IPv6 address string supplied. Calls panic() if the address is
// invalid, so if user input is provided, first validate with parse_ip_addr().
ip_addr_t::ip_addr_t(char const * address_string) {

   memset(&addr_, 0, sizeof(addr_));
   if (!parse_ip_addr(address_string, this)) {
      panic(invalid_argument_error("ip.ip_addr_t",
                                   "invalid IP address."));
   }

}

// IPv4 address (one word) in network byte order.
ip_addr_t::ip_addr_t(uint32_be_t addr_v4) :
      af_(AF_IPV4) {

   memset(&addr_, 0, sizeof(addr_));
   addr_.words[0] = addr_v4;
}

af_t
ip_addr_t::af() const {
   return af_;
}

bool
ip_addr_t::operator!=(ip_addr_t const & other) const {

   return !(*this == other);

}

// Returns the 16-byte address for the address, in network byte order IPv4
// addresses occupy the first word only; words 2-4 are empty.
uint8_t const *
ip_addr_t::addr() const {
   return static_cast<uint8_t const *>(addr_.bytes);
}

// The IPv4 address as a word in network byte order.
uint32_be_t
ip_addr_t::addr_v4() const {

   if(af_ != AF_IPV4) {
      panic("cannot call addr_v4() for non AF_IPV4 addresses");
   }
   return addr_.words[0];

}

std::string
ip_addr_t::to_string() const {

   if (af_ == AF_IPV4) {
      char buf[128];
      int rv;
      rv =snprintf(buf, sizeof(buf), "%d.%d.%d.%d",
                                     addr_.words[0] & 0xFF,
                                     (addr_.words[0] >> 8) & 0xFF,
                                     (addr_.words[0] >> 16) & 0xFF,
                                     (addr_.words[0] >> 24) & 0xFF);
      assert(rv>0);
      return std::string(buf);
   } else if (af_ == AF_IPV6) {
      struct sockaddr_in6 addr;
      char buf[INET6_ADDRSTRLEN];

      addr.sin6_family = AF_INET6;
      memcpy(&addr.sin6_addr.s6_addr, addr_.bytes, 16);
      if (!inet_ntop(addr.sin6_family, addr.sin6_addr.s6_addr,
                     buf, sizeof(buf))) {
         panic(invalid_argument_error("ip.ip_addr_t.to_string",
                                      "Can't convert IPV6 address to string."));
      }
      return std::string(buf);
   } else {
      return "Unknown IP address type.";
   }

}


ip_addr_t::operator bool() const {
   return (af_ != AF_NULL);
}

uint32_t
ip_addr_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
ip_addr_t::mix_me(hash_mix & h) const {
   h.mix(af_); // af_t
   h.mix_bytes((uint8_t const*)addr_.bytes,
               af_ == AF_IPV4 ? 4 : 16);
}

std::ostream&
operator<<(std::ostream& os, const ip_addr_t& obj) {
   os << obj.to_string();
   return os;
}



ip_prefix_t::ip_prefix_t() :
      prefix_length_() {

}

ip_prefix_t::ip_prefix_t(ip_addr_t const & addr, uint8_t prefix_length) :
      addr_(addr), prefix_length_(prefix_length) {
}

ip_prefix_t::ip_prefix_t(char const * prefix_string) :
      addr_(), prefix_length_() {

   if (!parse_ip_prefix(prefix_string, this)) {
      panic(invalid_argument_error("ip_prefix_t",
                                   "input is not an IPv4 or IPV6 prefix"));
   }

}

uint8_t
ip_prefix_t::prefix_length() const {
   return prefix_length_;
}

af_t
ip_prefix_t::af() const {
   return addr_.af();
}

ip_addr_t
ip_prefix_t::network() const {
   return addr_;
}

ip_addr_t
ip_prefix_t::mask() const {
   uint8_t addr[16] = {};
   int word;
   for(word = 0; word < prefix_length_ / 8; word++) {
      // Set any full words.
      addr[word] = 0xFF;
   }
   if(word < (af() == AF_IPV4 ? 4 : 16) && prefix_length_ % 8) {
      // There are remaining bits to set
      addr[word] = 0xFF;
      addr[word] <<= (8 - prefix_length_ % 8);
   }
   return ip_addr_t(af(), addr);

}

std::string
ip_prefix_t::to_string() const {

   char buf[128];
   int rv;
   rv = snprintf(buf, sizeof(buf), "%s/%d",
                 addr_.to_string().c_str(), prefix_length_);
   assert(rv>0);
   return std::string(buf);

}

bool
ip_prefix_t::operator==(ip_prefix_t const & other) const {
   return addr_ == other.addr_ &&
          prefix_length_ == other.prefix_length_;
}

bool
ip_prefix_t::operator!=(ip_prefix_t const & other) const {
   return !operator==(other);
}

bool
ip_prefix_t::operator<(ip_prefix_t const & other) const {
   if(addr_ != other.addr_) {
      return addr_ < other.addr_;
   } else if(prefix_length_ != other.prefix_length_) {
      return prefix_length_ < other.prefix_length_;
   }
   return false;
}

uint32_t
ip_prefix_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
ip_prefix_t::mix_me(hash_mix & h) const {
   h.mix(addr_); // ip_addr_t
   h.mix(prefix_length_); // uint8_t
}

std::ostream&
operator<<(std::ostream& os, const ip_prefix_t& obj) {
   os << obj.to_string();
   return os;
}



ip_addr_t
ip_addr_mask_t::addr() const {
   return pimpl->addr();
}
uint8_t
ip_addr_mask_t::mask_length() const {
   return pimpl->mask_length();
}
af_t
ip_addr_mask_t::af() const {
   return pimpl->af();
}
uint32_be_t
ip_addr_mask_t::mask() const {
   return pimpl->mask();
}
std::string
ip_addr_mask_t::to_string() const {
   return pimpl->to_string();
}
bool
ip_addr_mask_t::operator==(ip_addr_mask_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
ip_addr_mask_t::operator!=(ip_addr_mask_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
ip_addr_mask_t::operator<(ip_addr_mask_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
ip_addr_mask_t::hash() const {
   return pimpl->hash();
}
void
ip_addr_mask_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::ostream&
operator<<(std::ostream& os, const ip_addr_mask_t& obj) {
   return operator<<(os, *obj.pimpl);
}



address_overlap_error::~address_overlap_error() noexcept {

}

ip_addr_mask_t
address_overlap_error::addr() const noexcept {
   return addr_;
}

void
address_overlap_error::raise() const {
   throw *this;
}

uint32_t
address_overlap_error::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
address_overlap_error::mix_me(hash_mix & h) const {
   h.mix(addr_); // ip_addr_mask_t
}

std::string
address_overlap_error::to_string() const {
   std::ostringstream ss;
   ss << "address_overlap_error(";
   ss << "addr=" << addr_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const address_overlap_error& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_IP_H
