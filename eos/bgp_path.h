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
 */

#ifndef EOS_BGP_PATH_H
#define EOS_BGP_PATH_H

#include <eos/types/sdk.h>
#include <eos/iterator.h>

namespace eos {

/**
 * A manager of BGP RIB paths.
 */
class EOS_SDK_PUBLIC bgp_path_mgr {
  public:
   virtual ~bgp_path_mgr();

  protected:
   bgp_path_mgr() EOS_SDK_PRIVATE;

  private:
   EOS_SDK_DISALLOW_COPY_CTOR(bgp_path_mgr);
};

} // namespace eos

#endif // EOS_BGP_PATH_H
