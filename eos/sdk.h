// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_SDK_H
#define EOS_SDK_H

#include <eos/base.h>

namespace eos {

class directflow_mgr;
class eth_intf_mgr;
class eth_phy_intf_mgr;
class intf_mgr;

/**
 * Manages the differents managers of the SDK. One manager of each type can be
 * linked to a SDK object.
 * As managers must be initialized at the beginning of the program, the init_*_mgr()
 * functions should be called for any managers you plan to use.
 * Since the get_*_mgr() functions also call their respective init_*_mgr() functions
 * if necessary, accessing the managers at the beginning of the code (before the
 * agent_loop is called) is enough to initialize them.
 */
class EOS_SDK_PUBLIC sdk {
 public:
    sdk();
    ~sdk();

    void init_directflow_mgr();
    void init_eth_intf_mgr();
    void init_eth_phy_intf_mgr();
    void init_intf_mgr();

    directflow_mgr * get_directflow_mgr();
    eth_intf_mgr * get_eth_intf_mgr();
    eth_phy_intf_mgr * get_eth_phy_intf_mgr();
    intf_mgr * get_intf_mgr();

 private:
    EOS_SDK_DISALLOW_COPY_CTOR(sdk);
    directflow_mgr * directflow_mgr_;
    eth_intf_mgr * eth_intf_mgr_;
    eth_phy_intf_mgr * eth_phy_intf_mgr_;
    intf_mgr * intf_mgr_;
};

}

#include <eos/inline/sdk.h>

#endif // EOS_SDK_H
