// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_BRIDGING_H
#define EOS_BRIDGING_H

namespace eos {

class bridging_mgr {
 public:

   // Attribute accessors
   eth_addr bride_mac_addr();
   
 //=> private:
   bridging_mgr();

 private:
   bridging_mgr(bridging_mgr const &);
};

bridging_mgr * get_bridging_mgr();

}

#endif // EOS_BRIDGING_H
