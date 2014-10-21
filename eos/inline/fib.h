// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_FIB_H
#define INLINE_FIB_H

inline fib_mgr * fib_handler::get_fib_mgr() const {
   return mgr_;
}

#endif // INLINE_FIB_H

