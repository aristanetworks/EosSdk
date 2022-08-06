// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_VRF_IMPL_H
#define EOS_TYPES_VRF_IMPL_H

#include <eos/hash_mix.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

/** @deprecated. This data structure is used to describe a VRF on a switch. */
class EOS_SDK_PUBLIC vrf_impl_t {
 public:
   vrf_impl_t();
   vrf_impl_t(std::string name, vrf_state_t state, uint64_t rd);

   /** Getter for 'name': the name of the VRF. */
   std::string name() const;

   /** Getter for 'state': the state of this VRF. */
   vrf_state_t state() const;

   /** Getter for 'rd': the route distinguisher of the VRF. */
   uint64_t rd() const;

   bool operator==(vrf_impl_t const & other) const;
   bool operator!=(vrf_impl_t const & other) const;
   bool operator<(vrf_impl_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os, const vrf_impl_t& obj);

 private:
   std::string name_;
   vrf_state_t state_;
   uint64_t rd_;
};
}

#endif // EOS_TYPES_VRF_IMPL_H
