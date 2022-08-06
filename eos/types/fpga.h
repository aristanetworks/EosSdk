// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_FPGA_H
#define EOS_TYPES_FPGA_H

#include <eos/hash_mix.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

class fpga_impl_t;
/**
 * This data structure is used to describe
 * an application FPGA on a switch.
 */
class EOS_SDK_PUBLIC fpga_t {
 public:
   /** Default constructor. */
   fpga_t();
   fpga_t(std::string board_standard, std::string part_number);
   fpga_t(const fpga_t& other);
   fpga_t& operator=(
      fpga_t const & other);


   /** Getter for 'board_standard': The board standard of the FPGA. */
   std::string board_standard() const;

   /** Getter for 'part_number': The part number of the FPGA. */
   std::string part_number() const;

   bool operator==(fpga_t const & other) const;
   bool operator!=(fpga_t const & other) const;
   bool operator<(fpga_t const & other) const;
   /** The hash function for type fpga_t. */
   uint32_t hash() const;
   /** The hash mix function for type fpga_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of fpga_t to the
    * ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const fpga_t& obj);

 private:
   std::shared_ptr<fpga_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const fpga_t& obj);
}

#endif // EOS_TYPES_FPGA_H
