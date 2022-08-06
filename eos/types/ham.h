// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_HAM_H
#define EOS_TYPES_HAM_H

#include <eos/hash_mix.h>
#include <eos/utility.h>
#include <memory>
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
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const response_enum_t & enum_val);

class device_impl_t;
/** The device_t type is passed to the ctor of the eossdk_ham_t type. */
class EOS_SDK_PUBLIC device_t {
 public:
   /** Default constructor. */
   device_t();
   device_t(const device_t& other);
   device_t& operator=(
      device_t const & other);


   /** Getter for 'driver': Driver name. */
   std::string driver() const;
   /** Setter for 'driver'. */
   void driver_is(std::string driver);

   /** Getter for 'uid': The unique ID for the component. */
   uint32_t uid() const;
   /** Setter for 'uid'. */
   void uid_is(uint32_t uid);

   /** Getter for 'did': The unique topology ID for the device. */
   uint32_t did() const;
   /** Setter for 'did'. */
   void did_is(uint32_t did);

   /** Getter for 'bus': The Bus ID attribute. */
   uint32_t bus() const;
   /** Setter for 'bus'. */
   void bus_is(uint32_t bus);

   /** Getter for 'accelerator': The accelerator attribute. */
   uint32_t accelerator() const;
   /** Setter for 'accelerator'. */
   void accelerator_is(uint32_t accelerator);

   bool operator==(device_t const & other) const;
   bool operator!=(device_t const & other) const;
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
   std::shared_ptr<device_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const device_t& obj);

class pci_address_impl_t;
/**
 * The pci_address_t type is passed to the ctor of the eossdk_ham_t type. The HAM
 * should use the PCI address of the SCD. If zero, the CPUs SMBuses are used.
 */
class EOS_SDK_PUBLIC pci_address_t {
 public:
   /** Default constructor. */
   pci_address_t();
   pci_address_t(const pci_address_t& other);
   pci_address_t& operator=(
      pci_address_t const & other);


   /** Getter for 'domain': Domain of the pci address. */
   uint32_t domain() const;
   /** Setter for 'domain'. */
   void domain_is(uint32_t domain);

   /** Getter for 'bus': Bus identifier for pci address. */
   uint32_t bus() const;
   /** Setter for 'bus'. */
   void bus_is(uint32_t bus);

   /** Getter for 'device': Device identifier for pci address. */
   uint32_t device() const;
   /** Setter for 'device'. */
   void device_is(uint32_t device);

   /** Getter for 'function': Function identifier for pci address. */
   uint32_t function() const;
   /** Setter for 'function'. */
   void function_is(uint32_t function);

   bool operator==(pci_address_t const & other) const;
   bool operator!=(pci_address_t const & other) const;
   bool operator<(pci_address_t const & other) const;
   /** The hash function for type pci_address_t. */
   uint32_t hash() const;
   /** The hash mix function for type pci_address_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of pci_address_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const pci_address_t& obj);

 private:
   std::shared_ptr<pci_address_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const pci_address_t& obj);

class aham_address_impl_t;
/**
 * The aham_address_t type is passed to the ctor of the eossdk_ham_t type. It holds
 * the bus Id, the accelerator,and the endpoint address.
 */
class EOS_SDK_PUBLIC aham_address_t {
 public:
   /** Default constructor. */
   aham_address_t();
   aham_address_t(const aham_address_t& other);
   aham_address_t& operator=(
      aham_address_t const & other);


   /** Getter for 'bus': Bus attribute for aham address. */
   uint32_t bus() const;
   /** Setter for 'bus'. */
   void bus_is(uint32_t bus);

   /** Getter for 'accelerator': Accelerator for ahamaddress. */
   uint32_t accelerator() const;
   /** Setter for 'accelerator'. */
   void accelerator_is(uint32_t accelerator);

   /** Getter for 'address': Address field of the aham addressobject. */
   uint32_t address() const;
   /** Setter for 'address'. */
   void address_is(uint32_t address);

   bool operator==(aham_address_t const & other) const;
   bool operator!=(aham_address_t const & other) const;
   bool operator<(aham_address_t const & other) const;
   /** The hash function for type aham_address_t. */
   uint32_t hash() const;
   /** The hash mix function for type aham_address_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of aham_address_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const aham_address_t& obj);

 private:
   std::shared_ptr<aham_address_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const aham_address_t& obj);

class eossdk_ham_impl_t;
/** Hardware access method. */
class EOS_SDK_PUBLIC eossdk_ham_t {
 public:
   /**
    * Default constructor, where deviceArgs and endpointAddr are passed in from the
    * EosSdk FPGA module.
    */
   eossdk_ham_t(device_t device_Args, uint32_t endpoint_Addr);
   /**
    * Constructor specifying the AhamAddress for the ham device, where the
    * AhamAddress contains the endpoint address, the bus Id, and the accelerator
    * for the ham. Also specifies PCI Address.
    */
   eossdk_ham_t(aham_address_t aham_address, pci_address_t pci_address);
   eossdk_ham_t(const eossdk_ham_t& other);
   eossdk_ham_t& operator=(
      eossdk_ham_t const & other);


   device_t device_Args() const;

   uint32_t endpoint_Addr() const;

   aham_address_t aham_address() const;

   pci_address_t pci_address() const;

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
   std::shared_ptr<eossdk_ham_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const eossdk_ham_t& obj);

class register_impl_t;
/** Register type, from which the HAM will read from/write to. */
class EOS_SDK_PUBLIC register_t {
 public:
   register_t();
   register_t(const register_t& other);
   register_t& operator=(
      register_t const & other);


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
   std::shared_ptr<register_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const register_t& obj);
}

#endif // EOS_TYPES_HAM_H
