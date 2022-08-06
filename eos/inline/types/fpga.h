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
fpga_t::fpga_t(std::string board_standard, std::string part_number) {
   pimpl = std::shared_ptr<fpga_impl_t>(
      new fpga_impl_t(
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

}

#endif // EOS_INLINE_TYPES_FPGA_H
