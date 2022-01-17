// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_FPGA_H
#define INLINE_FPGA_H

namespace eos {

inline fpga_mgr * fpga_handler::get_fpga_mgr() const {
   return mgr_;
}

} // end namespace eos

#endif // INLINE_FPGA_H
