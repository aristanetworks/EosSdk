// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_FPGA_IMPL_H
#define EOS_INLINE_TYPES_FPGA_IMPL_H

namespace eos {

fpga_impl_t::fpga_impl_t() :
      name_(), board_standard_(), part_number_() {
}

fpga_impl_t::fpga_impl_t(std::string const & name,
                                std::string const & board_standard,
                                std::string const & part_number) :
      name_(name), board_standard_(board_standard), part_number_(part_number) {
}

std::string
fpga_impl_t::name() const {
   return name_;
}

std::string
fpga_impl_t::board_standard() const {
   return board_standard_;
}

std::string
fpga_impl_t::part_number() const {
   return part_number_;
}

bool
fpga_impl_t::operator==(fpga_impl_t const & other) const {
   return name_ == other.name_ &&
          board_standard_ == other.board_standard_ &&
          part_number_ == other.part_number_;
}

bool
fpga_impl_t::operator!=(fpga_impl_t const & other) const {
   return !operator==(other);
}

bool
fpga_impl_t::operator<(fpga_impl_t const & other) const {
   if(name_ != other.name_) {
      return name_ < other.name_;
   } else if(board_standard_ != other.board_standard_) {
      return board_standard_ < other.board_standard_;
   } else if(part_number_ != other.part_number_) {
      return part_number_ < other.part_number_;
   }
   return false;
}

uint32_t
fpga_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
fpga_impl_t::mix_me(hash_mix & h) const {
   h.mix(name_); // std::string
   h.mix(board_standard_); // std::string
   h.mix(part_number_); // std::string
}

std::string
fpga_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "fpga_t(";
   ss << "name='" << name_ << "'";
   ss << ", board_standard='" << board_standard_ << "'";
   ss << ", part_number='" << part_number_ << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const fpga_impl_t& obj) {
   os << obj.to_string();
   return os;
}



fpga_reservation_impl_t::fpga_reservation_impl_t() :
      id_(), board_standard_(), fpga_name_(), bitfile_() {
}

fpga_reservation_impl_t::fpga_reservation_impl_t(std::string const & id) :
      id_(id), board_standard_(), fpga_name_(), bitfile_() {
}

std::string
fpga_reservation_impl_t::id() const {
   return id_;
}

std::string
fpga_reservation_impl_t::board_standard() const {
   return board_standard_;
}

void
fpga_reservation_impl_t::board_standard_is(std::string const & board_standard) {
   board_standard_ = board_standard;
}

std::string
fpga_reservation_impl_t::fpga_name() const {
   return fpga_name_;
}

void
fpga_reservation_impl_t::fpga_name_is(std::string const & fpga_name) {
   fpga_name_ = fpga_name;
}

std::string
fpga_reservation_impl_t::bitfile() const {
   return bitfile_;
}

void
fpga_reservation_impl_t::bitfile_is(std::string const & bitfile) {
   bitfile_ = bitfile;
}

bool
fpga_reservation_impl_t::operator==(fpga_reservation_impl_t const & other) const {
   return id_ == other.id_ &&
          board_standard_ == other.board_standard_ &&
          fpga_name_ == other.fpga_name_ &&
          bitfile_ == other.bitfile_;
}

bool
fpga_reservation_impl_t::operator!=(fpga_reservation_impl_t const & other) const {
   return !operator==(other);
}

bool
fpga_reservation_impl_t::operator<(fpga_reservation_impl_t const & other) const {
   if(id_ != other.id_) {
      return id_ < other.id_;
   } else if(board_standard_ != other.board_standard_) {
      return board_standard_ < other.board_standard_;
   } else if(fpga_name_ != other.fpga_name_) {
      return fpga_name_ < other.fpga_name_;
   } else if(bitfile_ != other.bitfile_) {
      return bitfile_ < other.bitfile_;
   }
   return false;
}

uint32_t
fpga_reservation_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
fpga_reservation_impl_t::mix_me(hash_mix & h) const {
   h.mix(id_); // std::string
   h.mix(board_standard_); // std::string
   h.mix(fpga_name_); // std::string
   h.mix(bitfile_); // std::string
}

std::string
fpga_reservation_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "fpga_reservation_t(";
   ss << "id='" << id_ << "'";
   ss << ", board_standard='" << board_standard_ << "'";
   ss << ", fpga_name='" << fpga_name_ << "'";
   ss << ", bitfile='" << bitfile_ << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const fpga_reservation_impl_t& obj) {
   os << obj.to_string();
   return os;
}





fpga_reservation_status_impl_t::fpga_reservation_status_impl_t() :
      id_(), result_(), fpga_name_() {
}

fpga_reservation_status_impl_t::fpga_reservation_status_impl_t(
         std::string const & id, fpga_reservation_result_t result,
         std::string fpga_name) :
      id_(id), result_(result), fpga_name_(fpga_name) {
}

std::string
fpga_reservation_status_impl_t::id() const {
   return id_;
}

fpga_reservation_result_t
fpga_reservation_status_impl_t::result() const {
   return result_;
}

std::string
fpga_reservation_status_impl_t::fpga_name() const {
   return fpga_name_;
}

bool
fpga_reservation_status_impl_t::operator==(
         fpga_reservation_status_impl_t const & other) const {
   return id_ == other.id_ &&
          result_ == other.result_ &&
          fpga_name_ == other.fpga_name_;
}

bool
fpga_reservation_status_impl_t::operator!=(
         fpga_reservation_status_impl_t const & other) const {
   return !operator==(other);
}

bool
fpga_reservation_status_impl_t::operator<(
         fpga_reservation_status_impl_t const & other) const {
   if(id_ != other.id_) {
      return id_ < other.id_;
   } else if(result_ != other.result_) {
      return result_ < other.result_;
   } else if(fpga_name_ != other.fpga_name_) {
      return fpga_name_ < other.fpga_name_;
   }
   return false;
}

uint32_t
fpga_reservation_status_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
fpga_reservation_status_impl_t::mix_me(hash_mix & h) const {
   h.mix(id_); // std::string
   h.mix(result_); // fpga_reservation_result_t
   h.mix(fpga_name_); // std::string
}

std::string
fpga_reservation_status_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "fpga_reservation_status_t(";
   ss << "id='" << id_ << "'";
   ss << ", result=" << result_;
   ss << ", fpga_name='" << fpga_name_ << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const fpga_reservation_status_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/fpga.h>

#endif // EOS_INLINE_TYPES_FPGA_IMPL_H
