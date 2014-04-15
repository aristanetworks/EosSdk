// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_SDK_H
#define EOS_SDK_H

#include <eos/base.h>

namespace eos {

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

    /**
     * This function should be called at the beginning of your code if you plan to
     * use the intf_mgr.
     */
    void init_intf_mgr();
    /**
     * Returns the intf_mgr linked to this sdk object. If no intf_mgr object has
     * been initialized, this function will call init_intf_mgr().
     * As a the
     */
    intf_mgr * get_intf_mgr();

 private:
    EOS_SDK_DISALLOW_COPY_CTOR(sdk);
    intf_mgr * intf_mgr_;
};

}

#include <eos/inline/sdk.h>

#endif // EOS_SDK_H
