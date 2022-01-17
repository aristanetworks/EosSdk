// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_FPGA_H
#define EOS_INLINE_TYPES_FPGA_H

namespace eos {

inline fpga_t::fpga_t() :
      board_standard_(), part_number_() {
}

inline fpga_t::fpga_t(std::string board_standard, std::string part_number) :
      board_standard_(board_standard), part_number_(part_number) {
}

inline std::string
fpga_t::board_standard() const {
   return board_standard_;
}

inline std::string
fpga_t::part_number() const {
   return part_number_;
}

inline bool
fpga_t::operator==(fpga_t const & other) const {
   return board_standard_ == other.board_standard_ &&
          part_number_ == other.part_number_;
}

inline bool
fpga_t::operator!=(fpga_t const & other) const {
   return !operator==(other);
}

inline bool
fpga_t::operator<(fpga_t const & other) const {
   if(board_standard_ != other.board_standard_) {
      return board_standard_ < other.board_standard_;
   } else if(part_number_ != other.part_number_) {
      return part_number_ < other.part_number_;
   }
   return false;
}

inline uint32_t
fpga_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

inline void
fpga_t::mix_me(hash_mix & h) const {
   h.mix(board_standard_); // std::string
   h.mix(part_number_); // std::string
}

inline std::string
fpga_t::to_string() const {
   std::ostringstream ss;
   ss << "fpga_t(";
   ss << "board_standard='" << board_standard_ << "'";
   ss << ", part_number='" << part_number_ << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const fpga_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_FPGA_H
