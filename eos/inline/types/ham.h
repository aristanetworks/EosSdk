// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_HAM_H
#define EOS_INLINE_TYPES_HAM_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
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


device_t::device_t() {
   pimpl = std::shared_ptr<device_impl_t>(
      new device_impl_t()
   );
}
device_t::device_t(
   const device_t& other)
{
   pimpl = std::make_unique<device_impl_t>(
      device_impl_t(*other.pimpl));
}
device_t&
device_t::operator=(
   device_t const & other)
{
   pimpl = std::shared_ptr<device_impl_t>(
      new device_impl_t(*other.pimpl));
   return *this;
}

std::string
device_t::driver() const {
   return pimpl->driver();
}
void
device_t::driver_is(std::string driver) {
   pimpl->driver_is(driver);
}
uint32_t
device_t::uid() const {
   return pimpl->uid();
}
void
device_t::uid_is(uint32_t uid) {
   pimpl->uid_is(uid);
}
uint32_t
device_t::did() const {
   return pimpl->did();
}
void
device_t::did_is(uint32_t did) {
   pimpl->did_is(did);
}
uint32_t
device_t::bus() const {
   return pimpl->bus();
}
void
device_t::bus_is(uint32_t bus) {
   pimpl->bus_is(bus);
}
uint32_t
device_t::accelerator() const {
   return pimpl->accelerator();
}
void
device_t::accelerator_is(uint32_t accelerator) {
   pimpl->accelerator_is(accelerator);
}
bool
device_t::operator==(device_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
device_t::operator!=(device_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
device_t::operator<(device_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
device_t::hash() const {
   return pimpl->hash();
}
void
device_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
device_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const device_t& obj) {
   return operator<<(os, *obj.pimpl);
}


pci_address_t::pci_address_t() {
   pimpl = std::shared_ptr<pci_address_impl_t>(
      new pci_address_impl_t()
   );
}
pci_address_t::pci_address_t(
   const pci_address_t& other)
{
   pimpl = std::make_unique<pci_address_impl_t>(
      pci_address_impl_t(*other.pimpl));
}
pci_address_t&
pci_address_t::operator=(
   pci_address_t const & other)
{
   pimpl = std::shared_ptr<pci_address_impl_t>(
      new pci_address_impl_t(*other.pimpl));
   return *this;
}

uint32_t
pci_address_t::domain() const {
   return pimpl->domain();
}
void
pci_address_t::domain_is(uint32_t domain) {
   pimpl->domain_is(domain);
}
uint32_t
pci_address_t::bus() const {
   return pimpl->bus();
}
void
pci_address_t::bus_is(uint32_t bus) {
   pimpl->bus_is(bus);
}
uint32_t
pci_address_t::device() const {
   return pimpl->device();
}
void
pci_address_t::device_is(uint32_t device) {
   pimpl->device_is(device);
}
uint32_t
pci_address_t::function() const {
   return pimpl->function();
}
void
pci_address_t::function_is(uint32_t function) {
   pimpl->function_is(function);
}
bool
pci_address_t::operator==(pci_address_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
pci_address_t::operator!=(pci_address_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
pci_address_t::operator<(pci_address_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
pci_address_t::hash() const {
   return pimpl->hash();
}
void
pci_address_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
pci_address_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const pci_address_t& obj) {
   return operator<<(os, *obj.pimpl);
}


aham_address_t::aham_address_t() {
   pimpl = std::shared_ptr<aham_address_impl_t>(
      new aham_address_impl_t()
   );
}
aham_address_t::aham_address_t(
   const aham_address_t& other)
{
   pimpl = std::make_unique<aham_address_impl_t>(
      aham_address_impl_t(*other.pimpl));
}
aham_address_t&
aham_address_t::operator=(
   aham_address_t const & other)
{
   pimpl = std::shared_ptr<aham_address_impl_t>(
      new aham_address_impl_t(*other.pimpl));
   return *this;
}

uint32_t
aham_address_t::bus() const {
   return pimpl->bus();
}
void
aham_address_t::bus_is(uint32_t bus) {
   pimpl->bus_is(bus);
}
uint32_t
aham_address_t::accelerator() const {
   return pimpl->accelerator();
}
void
aham_address_t::accelerator_is(uint32_t accelerator) {
   pimpl->accelerator_is(accelerator);
}
uint32_t
aham_address_t::address() const {
   return pimpl->address();
}
void
aham_address_t::address_is(uint32_t address) {
   pimpl->address_is(address);
}
bool
aham_address_t::operator==(aham_address_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
aham_address_t::operator!=(aham_address_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
aham_address_t::operator<(aham_address_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
aham_address_t::hash() const {
   return pimpl->hash();
}
void
aham_address_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
aham_address_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const aham_address_t& obj) {
   return operator<<(os, *obj.pimpl);
}


eossdk_ham_t::eossdk_ham_t(device_t device_Args, uint32_t endpoint_Addr) {
   pimpl = std::shared_ptr<eossdk_ham_impl_t>(
      new eossdk_ham_impl_t(
         device_Args,
         endpoint_Addr
      )
   );
}
eossdk_ham_t::eossdk_ham_t(aham_address_t aham_address,
                                  pci_address_t pci_address) {
   pimpl = std::shared_ptr<eossdk_ham_impl_t>(
      new eossdk_ham_impl_t(
         aham_address,
         pci_address
      )
   );
}
eossdk_ham_t::eossdk_ham_t(
   const eossdk_ham_t& other)
{
   pimpl = std::make_unique<eossdk_ham_impl_t>(
      eossdk_ham_impl_t(*other.pimpl));
}
eossdk_ham_t&
eossdk_ham_t::operator=(
   eossdk_ham_t const & other)
{
   pimpl = std::shared_ptr<eossdk_ham_impl_t>(
      new eossdk_ham_impl_t(*other.pimpl));
   return *this;
}

device_t
eossdk_ham_t::device_Args() const {
   return pimpl->device_Args();
}
uint32_t
eossdk_ham_t::endpoint_Addr() const {
   return pimpl->endpoint_Addr();
}
aham_address_t
eossdk_ham_t::aham_address() const {
   return pimpl->aham_address();
}
pci_address_t
eossdk_ham_t::pci_address() const {
   return pimpl->pci_address();
}
uint32_t
eossdk_ham_t::hash() const {
   return pimpl->hash();
}
void
eossdk_ham_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
eossdk_ham_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const eossdk_ham_t& obj) {
   return operator<<(os, *obj.pimpl);
}


register_t::register_t() {
   pimpl = std::shared_ptr<register_impl_t>(
      new register_impl_t()
   );
}
register_t::register_t(
   const register_t& other)
{
   pimpl = std::make_unique<register_impl_t>(
      register_impl_t(*other.pimpl));
}
register_t&
register_t::operator=(
   register_t const & other)
{
   pimpl = std::shared_ptr<register_impl_t>(
      new register_impl_t(*other.pimpl));
   return *this;
}

uint32_t
register_t::reg() const {
   return pimpl->reg();
}
void
register_t::reg_is(uint32_t reg) {
   pimpl->reg_is(reg);
}
bool
register_t::operator==(register_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
register_t::operator!=(register_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
register_t::operator<(register_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
register_t::hash() const {
   return pimpl->hash();
}
void
register_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
register_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const register_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_HAM_H
