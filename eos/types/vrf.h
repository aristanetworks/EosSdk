// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_VRF_H
#define EOS_TYPES_VRF_H

#include <eos/utility.h>
#include <sstream>

namespace eos {

/** This data structure is used to describe an VRF on a switch. */
class EOS_SDK_PUBLIC vrf_t {
 public:
   vrf_t();
   vrf_t(std::string name, uint64_t rd, bool af_ipv4, bool af_ipv6);

   /** Getter for 'name': the name of the vrf. */
   std::string name() const;

   /** Getter for 'rd': the route distinguisher of the vrf. */
   uint64_t rd() const;

   /** Getter for 'af_ipv4': IPV4 address family. */
   bool af_ipv4() const;

   /** Getter for 'af_ipv6': IPV6 address family. */
   bool af_ipv6() const;

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
   uint64_t rd_;
   bool af_ipv4_;
   bool af_ipv6_;
};
}

#include <eos/inline/types/vrf.h>

#endif // EOS_TYPES_VRF_H
