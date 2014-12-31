// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_VRF_H
#define EOS_TYPES_VRF_H

#include <eos/utility.h>
#include <sstream>

namespace eos {

/** VRF state. */
enum vrf_state_t {
   /** Not a valid vrf type. */
   VRF_NULL,
   /** VRF being initialized. */
   VRF_INITIALIZING,
   /** VRF is active. */
   VRF_ACTIVE,
   /** VRF is being deleted. */
   VRF_DELETING,
   /** VRF is configured. */
   VRF_CONFIGURED,
};
/** Appends a string representation of enum vrf_state_t value to the ostream. */
std::ostream& operator<<(std::ostream& os, const vrf_state_t & enum_val);

/** This data structure is used to describe an VRF on a switch. */
class EOS_SDK_PUBLIC vrf_t {
 public:
   vrf_t();
   vrf_t(std::string name, vrf_state_t state, uint64_t rd);

   /** Getter for 'name': the name of the VRF. */
   std::string name() const;

   /** Getter for 'state': the state of this VRF. */
   vrf_state_t state() const;

   /** Getter for 'rd': the route distinguisher of the VRF. */
   uint64_t rd() const;

   bool operator==(vrf_t const & other) const;
   bool operator!=(vrf_t const & other) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of vrf_t to the
    * ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const vrf_t& obj);

 private:
   std::string name_;
   vrf_state_t state_;
   uint64_t rd_;
};
}

#include <eos/inline/types/vrf.h>

#endif // EOS_TYPES_VRF_H
