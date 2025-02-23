// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_BGP_H
#define EOS_TYPES_BGP_H

#include <eos/hash_mix.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

#ifdef SWIG
%ignore eos::bgp_peer_key_t(eos::bgp_peer_key_t &&) noexcept;
%ignore eos::bgp_peer_key_t::operator=(eos::bgp_peer_key_t &&) noexcept;
%ignore eos::bgp_peer_key_t::vrf_name_is(std::string &&);
%ignore eos::bgp_peer_key_t::peer_addr_is(eos::ip_addr_t &&);
#endif

namespace eos {

typedef uint32_t bgp_asn_t;

class bgp_peer_key_impl_t;
/** The BGP peer key which consists of the peer address and the VRF itresides in. */
class EOS_SDK_PUBLIC bgp_peer_key_t {
 public:
   bgp_peer_key_t();
   explicit bgp_peer_key_t(std::string const & vrf_name,
                           ip_addr_t const & peer_addr);
   bgp_peer_key_t(const bgp_peer_key_t& other);
   bgp_peer_key_t& operator=(
      bgp_peer_key_t const & other);

   bgp_peer_key_t(bgp_peer_key_t && other) noexcept;
   bgp_peer_key_t & operator=(bgp_peer_key_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /** Getter for 'vrf_name': VRF name. */
   std::string vrf_name() const;
   /** Setter for 'vrf_name'. */
   void vrf_name_is(std::string const & vrf_name);
   /** Moving Setter for 'vrf_name'. */
   void vrf_name_is(std::string && vrf_name);

   /** Getter for 'peer_addr': BGP peer address. */
   ip_addr_t peer_addr() const;
   /** Setter for 'peer_addr'. */
   void peer_addr_is(ip_addr_t const & peer_addr);
   /** Moving Setter for 'peer_addr'. */
   void peer_addr_is(ip_addr_t && peer_addr);

   bool operator==(bgp_peer_key_t const & other) const;
   bool operator!=(bgp_peer_key_t const & other) const;
   bool operator<(bgp_peer_key_t const & other) const;
   /** The hash function for type bgp_peer_key_t. */
   uint32_t hash() const;
   /** The hash mix function for type bgp_peer_key_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of bgp_peer_key_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const bgp_peer_key_t& obj);

 private:
   std::shared_ptr<bgp_peer_key_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const bgp_peer_key_t& obj);

/** The operational state of a BGP peer session. */
enum bgp_peer_state_t {
   PEER_UNKNOWN,
   PEER_IDLE,
   PEER_CONNECT,
   PEER_ACTIVE,
   PEER_OPENSENT,
   PEER_OPENCONFIRM,
   PEER_ESTABLISHED,
};
/** Appends a string representation of enum bgp_peer_state_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const bgp_peer_state_t & enum_val);
}

#endif // EOS_TYPES_BGP_H
