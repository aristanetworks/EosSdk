// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_HAM_IMPL_H
#define EOS_TYPES_HAM_IMPL_H

#include <eos/hash_mix.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

/** The device_t type is passed to the ctor of the eossdk_ham_t type. */
class EOS_SDK_PUBLIC device_impl_t {
 public:
   /** Default constructor. */
   device_impl_t();

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

   bool operator==(device_impl_t const & other) const;
   bool operator!=(device_impl_t const & other) const;
   bool operator<(device_impl_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os, const device_impl_t& obj);

 private:
   std::string driver_;
   uint32_t uid_;
   uint32_t did_;
   uint32_t bus_;
   uint32_t accelerator_;
};

/**
 * The pci_address_t type is passed to the ctor of the eossdk_ham_t type. The HAM
 * should use the PCI address of the SCD. If zero, the CPUs SMBuses are used.
 */
class EOS_SDK_PUBLIC pci_address_impl_t {
 public:
   /** Default constructor. */
   pci_address_impl_t();

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

   bool operator==(pci_address_impl_t const & other) const;
   bool operator!=(pci_address_impl_t const & other) const;
   bool operator<(pci_address_impl_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os, const pci_address_impl_t& obj);

 private:
   uint32_t domain_;
   uint32_t bus_;
   uint32_t device_;
   uint32_t function_;
};

/**
 * The aham_address_t type is passed to the ctor of the eossdk_ham_t type. It holds
 * the bus Id, the accelerator,and the endpoint address.
 */
class EOS_SDK_PUBLIC aham_address_impl_t {
 public:
   /** Default constructor. */
   aham_address_impl_t();

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

   bool operator==(aham_address_impl_t const & other) const;
   bool operator!=(aham_address_impl_t const & other) const;
   bool operator<(aham_address_impl_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os,
                                   const aham_address_impl_t& obj);

 private:
   uint32_t bus_;
   uint32_t accelerator_;
   uint32_t address_;
};

/** Hardware access method. */
class EOS_SDK_PUBLIC eossdk_ham_impl_t {
 public:
   /**
    * Default constructor, where deviceArgs and endpointAddr are passed in from the
    * EosSdk FPGA module.
    */
   eossdk_ham_impl_t(device_t device_Args, uint32_t endpoint_Addr);
   /**
    * Constructor specifying the AhamAddress for the ham device, where the
    * AhamAddress contains the endpoint address, the bus Id, and the accelerator
    * for the ham. Also specifies PCI Address.
    */
   eossdk_ham_impl_t(aham_address_t aham_address, pci_address_t pci_address);

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
   friend std::ostream& operator<<(std::ostream& os, const eossdk_ham_impl_t& obj);

 private:
   device_t device_Args_;
   uint32_t endpoint_Addr_;
   aham_address_t aham_address_;
   pci_address_t pci_address_;
};

/** Register type, from which the HAM will read from/write to. */
class EOS_SDK_PUBLIC register_impl_t {
 public:
   register_impl_t();

   uint32_t reg() const;
   void reg_is(uint32_t reg);

   bool operator==(register_impl_t const & other) const;
   bool operator!=(register_impl_t const & other) const;
   bool operator<(register_impl_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os, const register_impl_t& obj);

 private:
   uint32_t reg_;
};
}

#endif // EOS_TYPES_HAM_IMPL_H
