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
 */

#ifndef EOS_BGP_H
#define EOS_BGP_H

#include <eos/types/sdk.h>
#include <eos/iterator.h>

namespace eos {

/**
 * A manager of BGP configurations.
 */
class EOS_SDK_PUBLIC bgp_mgr {
 public:
    virtual ~bgp_mgr();

 protected:
   bgp_mgr() EOS_SDK_PRIVATE;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(bgp_mgr);

};

} // namespace eos

#endif // EOS_BGP_H

