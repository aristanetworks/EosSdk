// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

/**
 * @file
 * BGP path management module.
 *
 * Border Gateway Protocol (BGP) is a standardized exterior gateway routing protocol
 * designed to exchange routing and reachability information among autonomous
 * systems (AS). In EOS, BGP follows RFC4271.
 *
 * This module provides APIs to query BGP paths in the Adj-RIB-In.
 *
 * An example of the API usage is in examples/BgpPathAgent.cpp.
 *
 */

#ifndef EOS_BGP_PATH_H
#define EOS_BGP_PATH_H

#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/types/bgp_path.h>
#include <eos/iterator.h>

namespace eos {
class bgp_path_iter_impl;
class bgp_path_mgr;

/**
 * An iterator that yields an bgp_path_t for each BGP path in Adj-RIB-In.
 */
class EOS_SDK_PUBLIC bgp_path_iter_t
   : public iter_base<bgp_path_t, bgp_path_iter_impl> {

  private:
   friend class bgp_path_iter_impl;
   explicit bgp_path_iter_t(bgp_path_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * The BGP path handler.
 *
 * This class provides handler APIs to react to BGP path changes in Adj-RIB-In.
 * New path updates are notified once BGP has converged.
 * An iterator must be used to retreive the existing paths after BGP convergence.
 *
 */
class EOS_SDK_PUBLIC bgp_path_handler : public base_handler<bgp_path_mgr,
                                                            bgp_path_handler> {
  public:
   explicit bgp_path_handler(bgp_path_mgr *mgr);
   bgp_path_mgr * get_bgp_path_mgr() const;

   /// Register to receive notifications when any path has changed.
   void watch_all_paths(bool);

   /// Register to receive notifications when any IPv4 unicast path has changed.
   void watch_ipv4_unicast_paths(bool);

   /// Register to receive notifications when any IPv6 unicast path has changed.
   void watch_ipv6_unicast_paths(bool);

   /// Handler called when a BGP IPv4 unicast path has changed in Adj-RIB-In.
   virtual void on_ipv4_unicast_path(bgp_path_key_t path_key);

   /**
    * Handler called when BGP convergence has changed in
    * IPv4 unicast address family.
    */
   virtual void on_ipv4_unicast_bgp_converged(bool converged);

   /// Handler called when a BGP IPv6 unicast path has changed in Adj-RIB-In.
   virtual void on_ipv6_unicast_path(bgp_path_key_t path_key);

   /**
    * Handler called when BGP convergence has changed in
    * IPv6 unicast address family.
    */
   virtual void on_ipv6_unicast_bgp_converged(bool converged);

};

/**
 * A manager of BGP RIB paths.
 */
class EOS_SDK_PUBLIC bgp_path_mgr: public base_mgr<bgp_path_handler,
                                                   bgp_afi_safi_t> {
  public:
   virtual ~bgp_path_mgr();

   /**
    * Returns an iterator over IPv4 Unicast BGP paths in Adj-RIB-In, which
    * contains unprocessed routing information that has been advertised to the
    * local BGP speaker by its peers.
    */
   virtual bgp_path_iter_t ipv4_unicast_path_iter(bgp_path_options_t &) const = 0;

   /**
    * Returns an IPv4 Unicast BGP path in Adj-RIB-In with the corresponding
    * path key. Returns an empty bgp_path_t if no matching path was found.
    */
   virtual bgp_path_t ipv4_unicast_path(bgp_path_key_t const &,
                                        bgp_path_options_t &) = 0;

   /**
    * Returns true if bgp is converged for IPv4 Unicast address family
    */
   virtual bool ipv4_unicast_bgp_convergence() = 0;

   /**
    * Returns an iterator over IPv6 Unicast BGP paths in Adj-RIB-In, which
    * contains unprocessed routing information that has been advertised to the
    * local BGP speaker by its peers.
    */
   virtual bgp_path_iter_t ipv6_unicast_path_iter(bgp_path_options_t &) const = 0;

   /**
    * Returns an IPv6 Unicast BGP path in Adj-RIB-In with the corresponding
    * path key. Returns an empty bgp_path_t if no matching path was found.
    */
   virtual bgp_path_t ipv6_unicast_path(bgp_path_key_t const &,
                                        bgp_path_options_t &) = 0;

   /**
    * Returns true if bgp is converged for IPv6 Unicast address family
    */
   virtual bool ipv6_unicast_bgp_convergence() = 0;


  protected:
   bgp_path_mgr() EOS_SDK_PRIVATE;
   friend class bgp_path_handler;

  private:
   EOS_SDK_DISALLOW_COPY_CTOR(bgp_path_mgr);
};

} // namespace eos
#include <eos/inline/bgp_path.h>

#endif // EOS_BGP_PATH_H
