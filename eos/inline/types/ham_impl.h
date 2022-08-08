// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_HAM_IMPL_H
#define EOS_INLINE_TYPES_HAM_IMPL_H

namespace eos {



device_impl_t::device_impl_t() :
      driver_(), uid_(0xFFFFFFFF), did_(0xFFFFFFFF), bus_(0xFFFFFFFF),
      accelerator_(0xFFFFFFFF) {
}

std::string
device_impl_t::driver() const {
   return driver_;
}

void
device_impl_t::driver_is(std::string driver) {
   driver_ = driver;
}

uint32_t
device_impl_t::uid() const {
   return uid_;
}

void
device_impl_t::uid_is(uint32_t uid) {
   uid_ = uid;
}

uint32_t
device_impl_t::did() const {
   return did_;
}

void
device_impl_t::did_is(uint32_t did) {
   did_ = did;
}

uint32_t
device_impl_t::bus() const {
   return bus_;
}

void
device_impl_t::bus_is(uint32_t bus) {
   bus_ = bus;
}

uint32_t
device_impl_t::accelerator() const {
   return accelerator_;
}

void
device_impl_t::accelerator_is(uint32_t accelerator) {
   accelerator_ = accelerator;
}

bool
device_impl_t::operator==(device_impl_t const & other) const {
   return driver_ == other.driver_ &&
          uid_ == other.uid_ &&
          did_ == other.did_ &&
          bus_ == other.bus_ &&
          accelerator_ == other.accelerator_;
}

bool
device_impl_t::operator!=(device_impl_t const & other) const {
   return !operator==(other);
}

bool
device_impl_t::operator<(device_impl_t const & other) const {
   if(driver_ != other.driver_) {
      return driver_ < other.driver_;
   } else if(uid_ != other.uid_) {
      return uid_ < other.uid_;
   } else if(did_ != other.did_) {
      return did_ < other.did_;
   } else if(bus_ != other.bus_) {
      return bus_ < other.bus_;
   } else if(accelerator_ != other.accelerator_) {
      return accelerator_ < other.accelerator_;
   }
   return false;
}

uint32_t
device_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
device_impl_t::mix_me(hash_mix & h) const {
   h.mix(driver_); // std::string
   h.mix(uid_); // uint32_t
   h.mix(did_); // uint32_t
   h.mix(bus_); // uint32_t
   h.mix(accelerator_); // uint32_t
}

std::string
device_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "device_t(";
   ss << "driver='" << driver_ << "'";
   ss << ", uid=" << uid_;
   ss << ", did=" << did_;
   ss << ", bus=" << bus_;
   ss << ", accelerator=" << accelerator_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const device_impl_t& obj) {
   os << obj.to_string();
   return os;
}



pci_address_impl_t::pci_address_impl_t() :
      domain_(0xFFFFFFFF), bus_(0xFFFFFFFF), device_(0xFFFFFFFF),
      function_(0xFFFFFFFF) {
}

uint32_t
pci_address_impl_t::domain() const {
   return domain_;
}

void
pci_address_impl_t::domain_is(uint32_t domain) {
   domain_ = domain;
}

uint32_t
pci_address_impl_t::bus() const {
   return bus_;
}

void
pci_address_impl_t::bus_is(uint32_t bus) {
   bus_ = bus;
}

uint32_t
pci_address_impl_t::device() const {
   return device_;
}

void
pci_address_impl_t::device_is(uint32_t device) {
   device_ = device;
}

uint32_t
pci_address_impl_t::function() const {
   return function_;
}

void
pci_address_impl_t::function_is(uint32_t function) {
   function_ = function;
}

bool
pci_address_impl_t::operator==(pci_address_impl_t const & other) const {
   return domain_ == other.domain_ &&
          bus_ == other.bus_ &&
          device_ == other.device_ &&
          function_ == other.function_;
}

bool
pci_address_impl_t::operator!=(pci_address_impl_t const & other) const {
   return !operator==(other);
}

bool
pci_address_impl_t::operator<(pci_address_impl_t const & other) const {
   if(domain_ != other.domain_) {
      return domain_ < other.domain_;
   } else if(bus_ != other.bus_) {
      return bus_ < other.bus_;
   } else if(device_ != other.device_) {
      return device_ < other.device_;
   } else if(function_ != other.function_) {
      return function_ < other.function_;
   }
   return false;
}

uint32_t
pci_address_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
pci_address_impl_t::mix_me(hash_mix & h) const {
   h.mix(domain_); // uint32_t
   h.mix(bus_); // uint32_t
   h.mix(device_); // uint32_t
   h.mix(function_); // uint32_t
}

std::string
pci_address_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "pci_address_t(";
   ss << "domain=" << domain_;
   ss << ", bus=" << bus_;
   ss << ", device=" << device_;
   ss << ", function=" << function_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const pci_address_impl_t& obj) {
   os << obj.to_string();
   return os;
}



aham_address_impl_t::aham_address_impl_t() :
      bus_(0xFFFFFFFF), accelerator_(0xFFFFFFFF), address_(0xFFFFFFFF) {
}

uint32_t
aham_address_impl_t::bus() const {
   return bus_;
}

void
aham_address_impl_t::bus_is(uint32_t bus) {
   bus_ = bus;
}

uint32_t
aham_address_impl_t::accelerator() const {
   return accelerator_;
}

void
aham_address_impl_t::accelerator_is(uint32_t accelerator) {
   accelerator_ = accelerator;
}

uint32_t
aham_address_impl_t::address() const {
   return address_;
}

void
aham_address_impl_t::address_is(uint32_t address) {
   address_ = address;
}

bool
aham_address_impl_t::operator==(aham_address_impl_t const & other) const {
   return bus_ == other.bus_ &&
          accelerator_ == other.accelerator_ &&
          address_ == other.address_;
}

bool
aham_address_impl_t::operator!=(aham_address_impl_t const & other) const {
   return !operator==(other);
}

bool
aham_address_impl_t::operator<(aham_address_impl_t const & other) const {
   if(bus_ != other.bus_) {
      return bus_ < other.bus_;
   } else if(accelerator_ != other.accelerator_) {
      return accelerator_ < other.accelerator_;
   } else if(address_ != other.address_) {
      return address_ < other.address_;
   }
   return false;
}

uint32_t
aham_address_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
aham_address_impl_t::mix_me(hash_mix & h) const {
   h.mix(bus_); // uint32_t
   h.mix(accelerator_); // uint32_t
   h.mix(address_); // uint32_t
}

std::string
aham_address_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "aham_address_t(";
   ss << "bus=" << bus_;
   ss << ", accelerator=" << accelerator_;
   ss << ", address=" << address_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const aham_address_impl_t& obj) {
   os << obj.to_string();
   return os;
}



eossdk_ham_impl_t::eossdk_ham_impl_t(device_t device_Args,
                                            uint32_t endpoint_Addr) :
      device_Args_(device_Args), endpoint_Addr_(endpoint_Addr), aham_address_(),
      pci_address_() {
}

eossdk_ham_impl_t::eossdk_ham_impl_t(aham_address_t aham_address,
                                            pci_address_t pci_address) :
      device_Args_(), endpoint_Addr_(), aham_address_(aham_address),
      pci_address_(pci_address) {
}

device_t
eossdk_ham_impl_t::device_Args() const {
   return device_Args_;
}

uint32_t
eossdk_ham_impl_t::endpoint_Addr() const {
   return endpoint_Addr_;
}

aham_address_t
eossdk_ham_impl_t::aham_address() const {
   return aham_address_;
}

pci_address_t
eossdk_ham_impl_t::pci_address() const {
   return pci_address_;
}

uint32_t
eossdk_ham_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
eossdk_ham_impl_t::mix_me(hash_mix & h) const {
   h.mix(device_Args_); // device_t
   h.mix(endpoint_Addr_); // uint32_t
   h.mix(aham_address_); // aham_address_t
   h.mix(pci_address_); // pci_address_t
}

std::string
eossdk_ham_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "eossdk_ham_t(";
   ss << "device_Args=" << device_Args_;
   ss << ", endpoint_Addr=" << endpoint_Addr_;
   ss << ", aham_address=" << aham_address_;
   ss << ", pci_address=" << pci_address_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const eossdk_ham_impl_t& obj) {
   os << obj.to_string();
   return os;
}



read8_result_impl_t::read8_result_impl_t(response_enum_t status,
                                                uint8_t result) :
      status_(status), result_(result) {
}

response_enum_t
read8_result_impl_t::status() const {
   return status_;
}

void
read8_result_impl_t::status_is(response_enum_t status) {
   status_ = status;
}

uint8_t
read8_result_impl_t::result() const {
   return result_;
}

void
read8_result_impl_t::result_is(uint8_t result) {
   result_ = result;
}

bool
read8_result_impl_t::operator==(read8_result_impl_t const & other) const {
   return status_ == other.status_ &&
          result_ == other.result_;
}

bool
read8_result_impl_t::operator!=(read8_result_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
read8_result_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
read8_result_impl_t::mix_me(hash_mix & h) const {
   h.mix(status_); // response_enum_t
   h.mix(result_); // uint8_t
}

std::string
read8_result_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "read8_result_t(";
   ss << "status=" << status_;
   ss << ", result=" << result_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const read8_result_impl_t& obj) {
   os << obj.to_string();
   return os;
}



read16_result_impl_t::read16_result_impl_t(response_enum_t status,
                                                  uint16_t result) :
      status_(status), result_(result) {
}

response_enum_t
read16_result_impl_t::status() const {
   return status_;
}

void
read16_result_impl_t::status_is(response_enum_t status) {
   status_ = status;
}

uint16_t
read16_result_impl_t::result() const {
   return result_;
}

void
read16_result_impl_t::result_is(uint16_t result) {
   result_ = result;
}

bool
read16_result_impl_t::operator==(read16_result_impl_t const & other) const {
   return status_ == other.status_ &&
          result_ == other.result_;
}

bool
read16_result_impl_t::operator!=(read16_result_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
read16_result_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
read16_result_impl_t::mix_me(hash_mix & h) const {
   h.mix(status_); // response_enum_t
   h.mix(result_); // uint16_t
}

std::string
read16_result_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "read16_result_t(";
   ss << "status=" << status_;
   ss << ", result=" << result_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const read16_result_impl_t& obj) {
   os << obj.to_string();
   return os;
}



read_result_impl_t::read_result_impl_t(response_enum_t status,
                                              std::string result) :
      status_(status), result_(result) {
}

response_enum_t
read_result_impl_t::status() const {
   return status_;
}

void
read_result_impl_t::status_is(response_enum_t status) {
   status_ = status;
}

std::string
read_result_impl_t::result() const {
   return result_;
}

void
read_result_impl_t::result_is(std::string result) {
   result_ = result;
}

bool
read_result_impl_t::operator==(read_result_impl_t const & other) const {
   return status_ == other.status_ &&
          result_ == other.result_;
}

bool
read_result_impl_t::operator!=(read_result_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
read_result_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
read_result_impl_t::mix_me(hash_mix & h) const {
   h.mix(status_); // response_enum_t
   h.mix(result_); // std::string
}

std::string
read_result_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "read_result_t(";
   ss << "status=" << status_;
   ss << ", result='" << result_ << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const read_result_impl_t& obj) {
   os << obj.to_string();
   return os;
}



register_impl_t::register_impl_t() :
      reg_() {
}

uint32_t
register_impl_t::reg() const {
   return reg_;
}

void
register_impl_t::reg_is(uint32_t reg) {
   reg_ = reg;
}

bool
register_impl_t::operator==(register_impl_t const & other) const {
   return reg_ == other.reg_;
}

bool
register_impl_t::operator!=(register_impl_t const & other) const {
   return !operator==(other);
}

bool
register_impl_t::operator<(register_impl_t const & other) const {
   if(reg_ != other.reg_) {
      return reg_ < other.reg_;
   }
   return false;
}

uint32_t
register_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
register_impl_t::mix_me(hash_mix & h) const {
   h.mix(reg_); // uint32_t
}

std::string
register_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "register_t(";
   ss << "reg=" << reg_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const register_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/ham.h>

#endif // EOS_INLINE_TYPES_HAM_IMPL_H
