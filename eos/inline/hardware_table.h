// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_HARDWARE_TABLE_H
#define INLINE_HARDWARE_TABLE_H

namespace eos {

inline hardware_table_mgr *hardware_table_handler::get_hardware_table_mgr() const {
      return mgr_;
}

} // end namespace eos

#endif // INLINE_HARDWARE_TABLE_H

