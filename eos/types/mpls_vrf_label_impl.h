// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_MPLS_VRF_LABEL_IMPL_H
#define EOS_TYPES_MPLS_VRF_LABEL_IMPL_H

#include <eos/hash_mix.h>
#include <eos/mpls.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

/** A static VRF label decap route configuration model. */
class EOS_SDK_PUBLIC mpls_vrf_label_impl_t {
 public:
   mpls_vrf_label_impl_t();
   mpls_vrf_label_impl_t(mpls_label_t label, std::string vrf_name);

   /** Getter for 'label': the decap label. */
   mpls_label_t label() const;

   /** Getter for 'vrf_name': the name of the VRF. */
   std::string vrf_name() const;

   bool operator==(mpls_vrf_label_impl_t const & other) const;
   bool operator!=(mpls_vrf_label_impl_t const & other) const;
   bool operator<(mpls_vrf_label_impl_t const & other) const;
   /** The hash function for type mpls_vrf_label_t. */
   uint32_t hash() const;
   /** The hash mix function for type mpls_vrf_label_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * mpls_vrf_label_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const mpls_vrf_label_impl_t& obj);

 private:
   mpls_label_t label_;
   std::string vrf_name_;
};
}

#endif // EOS_TYPES_MPLS_VRF_LABEL_IMPL_H
