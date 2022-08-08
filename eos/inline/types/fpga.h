// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_FPGA_H
#define EOS_INLINE_TYPES_FPGA_H

namespace eos {

fpga_t::fpga_t() {
   pimpl = std::shared_ptr<fpga_impl_t>(
      new fpga_impl_t()
   );
}
fpga_t::fpga_t(std::string const & name, std::string const & board_standard,
                      std::string const & part_number) {
   pimpl = std::shared_ptr<fpga_impl_t>(
      new fpga_impl_t(
         name,
         board_standard,
         part_number
      )
   );
}
fpga_t::fpga_t(
   const fpga_t& other)
{
   pimpl = std::make_unique<fpga_impl_t>(
      fpga_impl_t(*other.pimpl));
}
fpga_t&
fpga_t::operator=(
   fpga_t const & other)
{
   pimpl = std::shared_ptr<fpga_impl_t>(
      new fpga_impl_t(*other.pimpl));
   return *this;
}

std::string
fpga_t::name() const {
   return pimpl->name();
}
std::string
fpga_t::board_standard() const {
   return pimpl->board_standard();
}
std::string
fpga_t::part_number() const {
   return pimpl->part_number();
}
bool
fpga_t::operator==(fpga_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
fpga_t::operator!=(fpga_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
fpga_t::operator<(fpga_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
fpga_t::hash() const {
   return pimpl->hash();
}
void
fpga_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
fpga_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const fpga_t& obj) {
   return operator<<(os, *obj.pimpl);
}


fpga_reservation_t::fpga_reservation_t() {
   pimpl = std::shared_ptr<fpga_reservation_impl_t>(
      new fpga_reservation_impl_t()
   );
}
fpga_reservation_t::fpga_reservation_t(std::string const & id) {
   pimpl = std::shared_ptr<fpga_reservation_impl_t>(
      new fpga_reservation_impl_t(
         id
      )
   );
}
fpga_reservation_t::fpga_reservation_t(
   const fpga_reservation_t& other)
{
   pimpl = std::make_unique<fpga_reservation_impl_t>(
      fpga_reservation_impl_t(*other.pimpl));
}
fpga_reservation_t&
fpga_reservation_t::operator=(
   fpga_reservation_t const & other)
{
   pimpl = std::shared_ptr<fpga_reservation_impl_t>(
      new fpga_reservation_impl_t(*other.pimpl));
   return *this;
}

std::string
fpga_reservation_t::id() const {
   return pimpl->id();
}
std::string
fpga_reservation_t::board_standard() const {
   return pimpl->board_standard();
}
void
fpga_reservation_t::board_standard_is(std::string const & board_standard) {
   pimpl->board_standard_is(board_standard);
}
std::string
fpga_reservation_t::fpga_name() const {
   return pimpl->fpga_name();
}
void
fpga_reservation_t::fpga_name_is(std::string const & fpga_name) {
   pimpl->fpga_name_is(fpga_name);
}
std::string
fpga_reservation_t::bitfile() const {
   return pimpl->bitfile();
}
void
fpga_reservation_t::bitfile_is(std::string const & bitfile) {
   pimpl->bitfile_is(bitfile);
}
bool
fpga_reservation_t::operator==(fpga_reservation_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
fpga_reservation_t::operator!=(fpga_reservation_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
fpga_reservation_t::operator<(fpga_reservation_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
fpga_reservation_t::hash() const {
   return pimpl->hash();
}
void
fpga_reservation_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
fpga_reservation_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const fpga_reservation_t& obj) {
   return operator<<(os, *obj.pimpl);
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const fpga_reservation_result_t & enum_val) {
   if (enum_val==FRR_INVALID) {
      os << "FRR_INVALID";
   } else if (enum_val==FRR_PENDING) {
      os << "FRR_PENDING";
   } else if (enum_val==FRR_SUCCESS) {
      os << "FRR_SUCCESS";
   } else if (enum_val==FRR_FAILED_TO_MATCH_FPGA) {
      os << "FRR_FAILED_TO_MATCH_FPGA";
   } else if (enum_val==FRR_FAILED_TO_RESERVE) {
      os << "FRR_FAILED_TO_RESERVE";
   } else if (enum_val==FRR_FAILED_TO_PROGRAM) {
      os << "FRR_FAILED_TO_PROGRAM";
   } else if (enum_val==FRR_FAILED_TO_CLEAR) {
      os << "FRR_FAILED_TO_CLEAR";
   } else {
      os << "Unknown value";
   }
   return os;
}


fpga_reservation_status_t::fpga_reservation_status_t() {
   pimpl = std::shared_ptr<fpga_reservation_status_impl_t>(
      new fpga_reservation_status_impl_t()
   );
}
fpga_reservation_status_t::fpga_reservation_status_t(
         std::string const & id, fpga_reservation_result_t result,
         std::string fpga_name) {
   pimpl = std::shared_ptr<fpga_reservation_status_impl_t>(
      new fpga_reservation_status_impl_t(
         id,
         result,
         fpga_name
      )
   );
}
fpga_reservation_status_t::fpga_reservation_status_t(
   const fpga_reservation_status_t& other)
{
   pimpl = std::make_unique<fpga_reservation_status_impl_t>(
      fpga_reservation_status_impl_t(*other.pimpl));
}
fpga_reservation_status_t&
fpga_reservation_status_t::operator=(
   fpga_reservation_status_t const & other)
{
   pimpl = std::shared_ptr<fpga_reservation_status_impl_t>(
      new fpga_reservation_status_impl_t(*other.pimpl));
   return *this;
}

std::string
fpga_reservation_status_t::id() const {
   return pimpl->id();
}
fpga_reservation_result_t
fpga_reservation_status_t::result() const {
   return pimpl->result();
}
std::string
fpga_reservation_status_t::fpga_name() const {
   return pimpl->fpga_name();
}
bool
fpga_reservation_status_t::operator==(fpga_reservation_status_t const & other)
       const {
   return pimpl->operator==(*other.pimpl);
}
bool
fpga_reservation_status_t::operator!=(fpga_reservation_status_t const & other)
       const {
   return pimpl->operator!=(*other.pimpl);
}
bool
fpga_reservation_status_t::operator<(fpga_reservation_status_t const & other)
       const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
fpga_reservation_status_t::hash() const {
   return pimpl->hash();
}
void
fpga_reservation_status_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
fpga_reservation_status_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const fpga_reservation_status_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_FPGA_H
