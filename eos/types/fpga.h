// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_FPGA_H
#define EOS_TYPES_FPGA_H

#include <eos/hash_mix.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

class fpga_impl_t;
/** Describes an application FPGA on a switch. */
class EOS_SDK_PUBLIC fpga_t {
 public:
   /** Default constructor. */
   fpga_t();
   fpga_t(std::string const & name, std::string const & board_standard,
          std::string const & part_number);
   fpga_t(const fpga_t& other);
   fpga_t& operator=(
      fpga_t const & other);


   /** Getter for 'name': The name of the FPGA. */
   std::string name() const;

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

class fpga_reservation_impl_t;
/** Describes an FPGA reservation on the switch. */
class EOS_SDK_PUBLIC fpga_reservation_t {
 public:
   fpga_reservation_t();
   explicit fpga_reservation_t(std::string const & id);
   fpga_reservation_t(const fpga_reservation_t& other);
   fpga_reservation_t& operator=(
      fpga_reservation_t const & other);


   /** Getter for 'id': The ID of the reservation. */
   std::string id() const;

   /** Getter for 'board_standard': The target FPGA board standard. */
   std::string board_standard() const;
   /** Setter for 'board_standard'. */
   void board_standard_is(std::string const & board_standard);

   /** Getter for 'fpga_name': The target FPGA name for the reservation. */
   std::string fpga_name() const;
   /** Setter for 'fpga_name'. */
   void fpga_name_is(std::string const & fpga_name);

   /**
    * Getter for 'bitfile': The file to be programmed. Empty string means to clear
    * the FPGA.
    */
   std::string bitfile() const;
   /** Setter for 'bitfile'. */
   void bitfile_is(std::string const & bitfile);

   bool operator==(fpga_reservation_t const & other) const;
   bool operator!=(fpga_reservation_t const & other) const;
   bool operator<(fpga_reservation_t const & other) const;
   /** The hash function for type fpga_reservation_t. */
   uint32_t hash() const;
   /** The hash mix function for type fpga_reservation_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * fpga_reservation_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const fpga_reservation_t& obj);

 private:
   std::shared_ptr<fpga_reservation_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const fpga_reservation_t& obj);

enum fpga_reservation_result_t {
   /** The request is invalid. */
   FRR_INVALID,
   /** The request is pending. */
   FRR_PENDING,
   /** The request has succeeded. */
   FRR_SUCCESS,
   /** The request failed; no matching FPGA was found. */
   FRR_FAILED_TO_MATCH_FPGA,
   /** The request failed; an FPGA could not be reserved. */
   FRR_FAILED_TO_RESERVE,
   /** The request failed; the FPGA could not be programmed. */
   FRR_FAILED_TO_PROGRAM,
   /** The request failed; the FPGA could not be cleared. */
   FRR_FAILED_TO_CLEAR,
};
/**
 * Appends a string representation of enum fpga_reservation_result_t value to the
 * ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const fpga_reservation_result_t & enum_val);

class fpga_reservation_status_impl_t;
/** Describes an FPGA reservation status on the switch. */
class EOS_SDK_PUBLIC fpga_reservation_status_t {
 public:
   fpga_reservation_status_t();
   fpga_reservation_status_t(std::string const & id,
                             fpga_reservation_result_t result,
                             std::string fpga_name);
   fpga_reservation_status_t(const fpga_reservation_status_t& other);
   fpga_reservation_status_t& operator=(
      fpga_reservation_status_t const & other);


   /** Getter for 'id': The ID of the reservation status. */
   std::string id() const;

   /** Getter for 'result': The result of the reservation. */
   fpga_reservation_result_t result() const;

   /** Getter for 'fpga_name': The name of the reserved FPGA. */
   std::string fpga_name() const;

   bool operator==(fpga_reservation_status_t const & other) const;
   bool operator!=(fpga_reservation_status_t const & other) const;
   bool operator<(fpga_reservation_status_t const & other) const;
   /** The hash function for type fpga_reservation_status_t. */
   uint32_t hash() const;
   /** The hash mix function for type fpga_reservation_status_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * fpga_reservation_status_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const fpga_reservation_status_t& obj);

 private:
   std::shared_ptr<fpga_reservation_status_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const fpga_reservation_status_t& obj);
}

#endif // EOS_TYPES_FPGA_H
