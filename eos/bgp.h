// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

/**
 * @file
 * BGP management module.
 *
 * Border Gateway Protocol (BGP) is a standardized exterior gateway routing protocol
 * designed to exchange routing and reachability information among autonomous
 * systems (AS). In EOS, BGP follows RFC4271.
 *
 * This module provides APIs to query BGP information including BGP peer state.
 *
 * An example of the API usage is in examples/BgpAgent.cpp
 *
 */

#ifndef EOS_BGP_H
#define EOS_BGP_H

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/iterator.h>
#include <eos/types/bgp.h>

namespace eos {

class bgp_mgr;

/**
 * The BGP peer handler.
 *
 * This class provides handler APIs to react to a BGP peer's session state change.
 */
class EOS_SDK_PUBLIC bgp_peer_handler : public base_handler<bgp_mgr,
                                                            bgp_peer_handler> {
  public:
   explicit bgp_peer_handler(bgp_mgr *mgr);
   bgp_mgr * get_bgp_mgr() const;


   /// Register to receive notifications when any peer changes state.
   void watch_all_peers(bool);

   /// Register to receive notifications when the specified peer changes state.
   void watch_peer(bgp_peer_key_t const & peer_key, bool);

   /// Called when BGP peer state change
   virtual void on_peer_state(bgp_peer_key_t const & peer_key,
                              bgp_peer_state_t peer_state);

   /// Called when a BGP peer is created
   virtual void on_peer_set(bgp_peer_key_t const & peer_key);

   /// Called when a BGP peer is deleted
   virtual void on_peer_del(bgp_peer_key_t const & peer_key);
};

/**
 * A manager of BGP configurations.
 */
class EOS_SDK_PUBLIC bgp_mgr : public base_mgr<bgp_peer_handler, bgp_peer_key_t> {
 public:
   virtual ~bgp_mgr();

   /**
    * Test for existence of a BGP peer.
    */
   virtual bool exists(bgp_peer_key_t const & peer_key) const = 0;

   /**
    * Returns the state of a peer session.
    *
    * If the given peer does not have a valid status or it didn't match any peers
    * in the system, this would returns PEER_UNKNOWN;
    */
   virtual bgp_peer_state_t peer_state(bgp_peer_key_t const & peer_key) const = 0;

 protected:
   bgp_mgr() EOS_SDK_PRIVATE;
   friend class bgp_peer_handler;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(bgp_mgr);

};

} // namespace eos

#include <eos/inline/bgp.h>

#endif // EOS_BGP_H

