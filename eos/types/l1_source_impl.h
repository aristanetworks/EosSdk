// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_L1_SOURCE_IMPL_H
#define EOS_TYPES_L1_SOURCE_IMPL_H

#include <eos/hash_mix.h>
#include <eos/intf.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

/**
 * L1 source class.
 *
 * The interface id "port" should be defined only if l1 source type is port.
 */
class EOS_SDK_PUBLIC l1_source_impl_t {
 public:
   /** Default constructor. */
   l1_source_impl_t();
   /** Constructor specifying only l1 source type. */
   explicit l1_source_impl_t(l1_source_type_t l1_source_type);
   /** Constructor specifying both l1 source type and interface id. */
   l1_source_impl_t(l1_source_type_t l1_source_type, intf_id_t port);

   l1_source_type_t l1_source_type() const;
   void l1_source_type_is(l1_source_type_t l1_source_type);

   intf_id_t port() const;
   void port_is(intf_id_t port);

   bool operator==(l1_source_impl_t const & other) const;
   bool operator!=(l1_source_impl_t const & other) const;
   bool operator<(l1_source_impl_t const & other) const;
   /** The hash function for type l1_source_t. */
   uint32_t hash() const;
   /** The hash mix function for type l1_source_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of l1_source_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const l1_source_impl_t& obj);

 private:
   l1_source_type_t l1_source_type_;
   intf_id_t port_;
};
}

#endif // EOS_TYPES_L1_SOURCE_IMPL_H
