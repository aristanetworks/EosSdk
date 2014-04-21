// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_BASE_HANDLER_H
#define EOS_BASE_HANDLER_H

#include <eos/base.h>

namespace eos {

template <typename Mgr, typename Handler>
class EOS_SDK_PRIVATE base_handler {
 protected:
    explicit base_handler(Mgr * mgr) : mgr_(mgr) {
    }

    virtual ~base_handler() {
       if (mgr_) {
          // The add_handler has to remove every interface-specific handler...
          mgr_->add_handler(static_cast<Handler*>(this));
          mgr_->remove_handler(static_cast<Handler*>(this));
       }
    }

    void unregister_mgr() {
       mgr_ = 0;
    }

    template <typename T, typename Key> friend class base_mgr;
    Mgr * mgr_;
};

}

#endif // EOS_BASE_HANDLER_H
