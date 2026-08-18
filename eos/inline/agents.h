// Copyright (c) 2026 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_AGENTS_H
#define INLINE_AGENTS_H

namespace eos {

inline agents_mgr *agents_handler::get_agents_mgr() const {
      return mgr_;
}

} // end namespace eos

#endif // INLINE_AGENTS_H
