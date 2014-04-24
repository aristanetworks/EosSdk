// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_AGENT_H
#define EOS_INLINE_AGENT_H

namespace eos {

inline agent_mgr * agent_handler::get_agent_mgr() const {
   return mgr_;
}

}

#endif // EOS_INLINE_AGENT_H
