// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_HAM_H
#define EOS_TYPES_HAM_H

#include <eos/hash_mix.h>
#include <eos/utility.h>
#include <sstream>

namespace eos {

/** The response_enum_t is the return value of any read or write with the ham. */
enum response_enum_t {
   /** Ok. */
   STATUS_OK,
   /** Hardware not present. */
   STATUS_ERR_HW_NOT_PRESENT,
   /** General hardware failure. */
   STATUS_ERR_HW_FAILURE,
   /** Invalid parameter arguments. */
   STATUS_ERR_ARGS,
   /** Communication error. Possible to retry later. */
   STATUS_ERR_COMM,
   /** API not supported. */
   STATUS_ERR_API_UNSUPPORTED,
   /** Internal error. */
   STATUS_ERR_INTERNAL,
};
/** Appends a string representation of enum response_enum_t value to the ostream. */
std::ostream& operator<<(std::ostream& os, const response_enum_t & enum_val);

/** The device_t type is passed to the ctor of the eossdk_ham_t type. */
class EOS_SDK_PUBLIC device_t {
 public:
   /** Default constructor. */
   device_t();

   /** Getter for 'driver name'. */
   std::string driver();
   /** Getter for 'uid', the unique ID for the component.. */
   uint32_t uid();
   /**
    * Getter for 'did', the unique topology ID for the device responsible for the
    * component.
    */
   uint32_t did();
   /** Getter for 'bus' attribute. */
   uint32_t bus();
   /** Getter for 'accelerator' attribute. */
   uint32_t accelerator();
   void driver_is(std::string driver);
   void uid_is(uint32_t uid);
   void did_is(uint32_t did);
   void bus_is(uint32_t bus);
   void accelerator_is(uint32_t accelerator);
   bool operator<(device_t const & other) const;
   /** The hash function for type device_t. */
   uint32_t hash() const;
   /** The hash mix function for type device_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of device_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const device_t& obj);

 private:
   std::string driver_;
   uint32_t uid_;
   uint32_t did_;
   uint32_t bus_;
   uint32_t accelerator_;
};

/** Hardware access method. */
class EOS_SDK_PUBLIC eossdk_ham_t {
 public:
   /**
    * Default constructor, where deviceArgs and endpointAddr are passed in from the
    * EosSdk FPGA module.
    */
   eossdk_ham_t(device_t device_Args, uint32_t endpoint_Addr);

   device_t device_Args() const;
   void device_Args_is(device_t device_Args);

   uint32_t endpoint_Addr() const;
   void endpoint_Addr_is(uint32_t endpoint_Addr);

   /** The hash function for type eossdk_ham_t. */
   uint32_t hash() const;
   /** The hash mix function for type eossdk_ham_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of eossdk_ham_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const eossdk_ham_t& obj);

 private:
   device_t device_Args_;
   uint32_t endpoint_Addr_;
};

/** Register type, from which the HAM will read from/write to. */
class EOS_SDK_PUBLIC register_t {
 public:

   uint32_t reg() const;
   void reg_is(uint32_t reg);

   bool operator==(register_t const & other) const;
   bool operator!=(register_t const & other) const;
   bool operator<(register_t const & other) const;
   /** The hash function for type register_t. */
   uint32_t hash() const;
   /** The hash mix function for type register_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of register_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const register_t& obj);

 private:
   uint32_t reg_;
};
}

#include <eos/inline/types/ham.h>

#endif // EOS_TYPES_HAM_H
