// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_MAC_TABLE_H
#define INLINE_MAC_TABLE_H

inline mac_table_mgr * mac_table_handler::get_mac_table_mgr() const {
   return mgr_;
}

#endif // INLINE_MAC_TABLE_H
