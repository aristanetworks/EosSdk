// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_BGP_IMPL_H
#define EOS_TYPES_BGP_IMPL_H

#include <eos/hash_mix.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

/** The BGP peer key which consists of the peer address and the VRF itresides in. */
class EOS_SDK_PUBLIC bgp_peer_key_impl_t {
 public:
   bgp_peer_key_impl_t();
   explicit bgp_peer_key_impl_t(std::string const & vrf_name,
                                ip_addr_t const & peer_addr);

   /** Getter for 'vrf_name': VRF name. */
   std::string vrf_name() const;
   /** Setter for 'vrf_name'. */
   void vrf_name_is(std::string const & vrf_name);

   /** Getter for 'peer_addr': BGP peer address. */
   ip_addr_t peer_addr() const;
   /** Setter for 'peer_addr'. */
   void peer_addr_is(ip_addr_t const & peer_addr);

   bool operator==(bgp_peer_key_impl_t const & other) const;
   bool operator!=(bgp_peer_key_impl_t const & other) const;
   bool operator<(bgp_peer_key_impl_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os,
                                   const bgp_peer_key_impl_t& obj);

 private:
   std::string vrf_name_;
   ip_addr_t peer_addr_;
};
}

#endif // EOS_TYPES_BGP_IMPL_H
