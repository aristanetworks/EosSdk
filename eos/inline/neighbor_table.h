// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_NEIGHBOR_TABLE_H
#define INLINE_NEIGHBOR_TABLE_H

inline neighbor_table_mgr *neighbor_table_handler::get_neighbor_table_mgr() const {
   return mgr_;
}

#endif // INLINE_NEIGHBOR_TABLE_H
