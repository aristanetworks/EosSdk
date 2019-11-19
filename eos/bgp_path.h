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

#include <eos/types/bgp_path.h>
#include <eos/iterator.h>

namespace eos {
class bgp_path_iter_impl;

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
 * A manager of BGP RIB paths.
 */
class EOS_SDK_PUBLIC bgp_path_mgr {
  public:
   virtual ~bgp_path_mgr();

   /**
    * Returns an iterator over IPv6 Unicast BGP paths in Adj-RIB-In, which
    * contains unprocessed routing information that has been advertised to the
    * local BGP speaker by its peers.
    */
   virtual bgp_path_iter_t ipv6_unicast_path_iter(bgp_path_options_t &) const = 0;

  protected:
   bgp_path_mgr() EOS_SDK_PRIVATE;

  private:
   EOS_SDK_DISALLOW_COPY_CTOR(bgp_path_mgr);
};

} // namespace eos

#endif // EOS_BGP_PATH_H
