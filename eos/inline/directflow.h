// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_DIRECTFLOW_H
#define EOS_INLINE_DIRECTFLOW_H

#include <eos/panic.h>
#include <eos/exception.h>

namespace eos {

inline directflow_mgr * flow_handler::get_directflow_mgr() const {
   return mgr_;
}

}

#endif // EOS_INLINE_DIRECTFLOW_H
