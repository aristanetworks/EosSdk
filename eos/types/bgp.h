// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_BGP_H
#define EOS_TYPES_BGP_H

#include <eos/hash_mix.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <sstream>

namespace eos {

/** The BGP peer key which consists of the peer address and the VRF itresides in. */
class EOS_SDK_PUBLIC bgp_peer_key_t {
 public:
   bgp_peer_key_t();
   explicit bgp_peer_key_t(std::string const & vrf_name,
                           ip_addr_t const & peer_addr);

   /** Getter for 'vrf_name': VRF name. */
   std::string vrf_name() const;
   /** Setter for 'vrf_name'. */
   void vrf_name_is(std::string const & vrf_name);

   /** Getter for 'peer_addr': BGP peer address. */
   ip_addr_t peer_addr() const;
   /** Setter for 'peer_addr'. */
   void peer_addr_is(ip_addr_t const & peer_addr);

   bool operator==(bgp_peer_key_t const & other) const;
   bool operator!=(bgp_peer_key_t const & other) const;
   bool operator<(bgp_peer_key_t const & other) const;
   /** The hash function for type bgp_peer_key_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of bgp_peer_key_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const bgp_peer_key_t& obj);

 private:
   std::string vrf_name_;
   ip_addr_t peer_addr_;
};

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
std::ostream& operator<<(std::ostream& os, const bgp_peer_state_t & enum_val);
}

#include <eos/inline/types/bgp.h>

#endif // EOS_TYPES_BGP_H
