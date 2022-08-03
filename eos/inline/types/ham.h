// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_HAM_H
#define EOS_INLINE_TYPES_HAM_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const response_enum_t & enum_val) {
   if (enum_val==STATUS_OK) {
      os << "STATUS_OK";
   } else if (enum_val==STATUS_ERR_HW_NOT_PRESENT) {
      os << "STATUS_ERR_HW_NOT_PRESENT";
   } else if (enum_val==STATUS_ERR_HW_FAILURE) {
      os << "STATUS_ERR_HW_FAILURE";
   } else if (enum_val==STATUS_ERR_ARGS) {
      os << "STATUS_ERR_ARGS";
   } else if (enum_val==STATUS_ERR_COMM) {
      os << "STATUS_ERR_COMM";
   } else if (enum_val==STATUS_ERR_API_UNSUPPORTED) {
      os << "STATUS_ERR_API_UNSUPPORTED";
   } else if (enum_val==STATUS_ERR_INTERNAL) {
      os << "STATUS_ERR_INTERNAL";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline device_t::device_t() {
}

inline std::string
device_t::driver() {
   return driver_;
}

inline uint32_t
device_t::uid() {
   return uid_;
}

inline uint32_t
device_t::did() {
   return did_;
}

inline uint32_t
device_t::bus() {
   return bus_;
}

inline uint32_t
device_t::accelerator() {
   return accelerator_;
}

inline void
device_t::driver_is(std::string driver) {
   driver_ = driver;
}

inline void
device_t::uid_is(uint32_t uid) {
   uid_= uid;
}

inline void
device_t::did_is(uint32_t did) {
   did_ = did;
}

inline void
device_t::bus_is(uint32_t bus) {
   bus_=bus;
}

inline void
device_t::accelerator_is(uint32_t accelerator) {
   accelerator_ = accelerator;
}

inline bool
device_t::operator<(device_t const & other) const {
   return false;
}

inline uint32_t
device_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
device_t::mix_me(hash_mix & h) const {
}

inline std::string
device_t::to_string() const {
   std::ostringstream ss;
   ss << "device_t(";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const device_t& obj) {
   os << obj.to_string();
   return os;
}



inline eossdk_ham_t::eossdk_ham_t(device_t device_Args, uint32_t endpoint_Addr) :
      device_Args_(device_Args), endpoint_Addr_(endpoint_Addr) {
}

inline device_t
eossdk_ham_t::device_Args() const {
   return device_Args_;
}

inline void
eossdk_ham_t::device_Args_is(device_t device_Args) {
   device_Args_ = device_Args;
}

inline uint32_t
eossdk_ham_t::endpoint_Addr() const {
   return endpoint_Addr_;
}

inline void
eossdk_ham_t::endpoint_Addr_is(uint32_t endpoint_Addr) {
   endpoint_Addr_ = endpoint_Addr;
}

inline uint32_t
eossdk_ham_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
eossdk_ham_t::mix_me(hash_mix & h) const {
   h.mix(device_Args_); // device_t
   h.mix(endpoint_Addr_); // uint32_t
}

inline std::string
eossdk_ham_t::to_string() const {
   std::ostringstream ss;
   ss << "eossdk_ham_t(";
   ss << "device_Args=" << device_Args_;
   ss << ", endpoint_Addr=" << endpoint_Addr_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const eossdk_ham_t& obj) {
   os << obj.to_string();
   return os;
}



inline uint32_t
register_t::reg() const {
   return reg_;
}

inline void
register_t::reg_is(uint32_t reg) {
   reg_ = reg;
}

inline bool
register_t::operator==(register_t const & other) const {
   return reg_ == other.reg_;
}

inline bool
register_t::operator!=(register_t const & other) const {
   return !operator==(other);
}

inline bool
register_t::operator<(register_t const & other) const {
   if(reg_ != other.reg_) {
      return reg_ < other.reg_;
   }
   return false;
}

inline uint32_t
register_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
register_t::mix_me(hash_mix & h) const {
   h.mix(reg_); // uint32_t
}

inline std::string
register_t::to_string() const {
   std::ostringstream ss;
   ss << "register_t(";
   ss << "reg=" << reg_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const register_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_HAM_H
