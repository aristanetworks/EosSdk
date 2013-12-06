// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_BRIDGING_H
#define EOS_BRIDGING_H

#include <eos/base.h>

namespace eos {

class EOS_SDK_PUBLIC bridging_mgr {
 public:

   // Attribute accessors
   eth_addr bride_mac_addr();

 //=> private:
   bridging_mgr();

 private:
   bridging_mgr(bridging_mgr const &) EOS_SDK_PRIVATE;
};

bridging_mgr * get_bridging_mgr() EOS_SDK_PUBLIC;

}

#endif // EOS_BRIDGING_H
