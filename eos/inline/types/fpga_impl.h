// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_FPGA_IMPL_H
#define EOS_INLINE_TYPES_FPGA_IMPL_H

namespace eos {

fpga_impl_t::fpga_impl_t() :
      board_standard_(), part_number_() {
}

fpga_impl_t::fpga_impl_t(std::string board_standard,
                                std::string part_number) :
      board_standard_(board_standard), part_number_(part_number) {
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
   return board_standard_ == other.board_standard_ &&
          part_number_ == other.part_number_;
}

bool
fpga_impl_t::operator!=(fpga_impl_t const & other) const {
   return !operator==(other);
}

bool
fpga_impl_t::operator<(fpga_impl_t const & other) const {
   if(board_standard_ != other.board_standard_) {
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
   h.mix(board_standard_); // std::string
   h.mix(part_number_); // std::string
}

std::string
fpga_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "fpga_t(";
   ss << "board_standard='" << board_standard_ << "'";
   ss << ", part_number='" << part_number_ << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const fpga_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/fpga.h>

#endif // EOS_INLINE_TYPES_FPGA_IMPL_H
