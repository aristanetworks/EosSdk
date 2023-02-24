// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_VRF_H
#define EOS_TYPES_VRF_H

#include <eos/hash_mix.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

/** VRF state. */
enum vrf_state_t {
   /** VRF does not exist. */
   VRF_NULL,
   /** VRF is being initialized. */
   VRF_INITIALIZING,
   /** VRF is active. */
   VRF_ACTIVE,
   /** VRF is being deleted. */
   VRF_DELETING,
};
/** Appends a string representation of enum vrf_state_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const vrf_state_t & enum_val);

class vrf_impl_t;
/** @deprecated. This data structure is used to describe a VRF on a switch. */
class EOS_SDK_PUBLIC vrf_t {
 public:
   vrf_t();
   vrf_t(std::string name, vrf_state_t state, uint64_t rd);
   vrf_t(const vrf_t& other);
   vrf_t& operator=(
      vrf_t const & other);


   /** Getter for 'name': the name of the VRF. */
   std::string name() const;

   /** Getter for 'state': the state of this VRF. */
   vrf_state_t state() const;

   /** Getter for 'rd': the route distinguisher of the VRF. */
   uint64_t rd() const;

   bool operator==(vrf_t const & other) const;
   bool operator!=(vrf_t const & other) const;
   bool operator<(vrf_t const & other) const;
   /** The hash function for type vrf_t. */
   uint32_t hash() const;
   /** The hash mix function for type vrf_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of vrf_t to the
    * ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const vrf_t& obj);

 private:
   std::shared_ptr<vrf_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const vrf_t& obj);
}

#endif // EOS_TYPES_VRF_H
