// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_SUBINTF_H
#define EOS_TYPES_SUBINTF_H

#include <eos/hash_mix.h>
#include <eos/types/eth.h>
#include <eos/types/intf.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

#ifdef SWIG
%ignore eos::subintf_t(eos::subintf_t &&) noexcept;
%ignore eos::subintf_t::operator=(eos::subintf_t &&) noexcept;
#endif

namespace eos {

class subintf_impl_t;
/** This data structure defines a subinterface. */
class EOS_SDK_PUBLIC subintf_t {
 public:
   subintf_t();
   subintf_t(intf_id_t intf_id, vlan_id_t vlan_id);
   subintf_t(const subintf_t& other);
   subintf_t& operator=(
      subintf_t const & other);

   subintf_t(subintf_t && other) noexcept;
   subintf_t & operator=(subintf_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /** Getter for 'intf_id': the interface ID of this subinterface. */
   intf_id_t intf_id() const;

   /** Getter for 'vlan_id': the VLAN tag of this subinterface. */
   vlan_id_t vlan_id() const;
   /** Setter for 'vlan_id'. */
   void vlan_id_is(vlan_id_t vlan_id);

   bool operator==(subintf_t const & other) const;
   bool operator!=(subintf_t const & other) const;
   /** The hash function for type subintf_t. */
   uint32_t hash() const;
   /** The hash mix function for type subintf_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of subintf_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const subintf_t& obj);

 private:
   std::shared_ptr<subintf_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const subintf_t& obj);
}

#endif // EOS_TYPES_SUBINTF_H
