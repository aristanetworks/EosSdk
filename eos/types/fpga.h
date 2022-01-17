// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_FPGA_H
#define EOS_TYPES_FPGA_H

#include <eos/hash_mix.h>
#include <eos/utility.h>
#include <sstream>

namespace eos {

/**
 * This data structure is used to describe
 * an application FPGA on a switch.
 */
class EOS_SDK_PUBLIC fpga_t {
 public:
   /** Default constructor. */
   fpga_t();
   fpga_t(std::string board_standard, std::string part_number);

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
   std::string board_standard_;
   std::string part_number_;
};
}

#include <eos/inline/types/fpga.h>

#endif // EOS_TYPES_FPGA_H
