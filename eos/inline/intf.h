// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_INTF_H
#define EOS_INLINE_INTF_H

#include <eos/panic.h>

namespace eos {

inline intf_id_t::intf_id_t(uint64_t id) {
   intfId_ = id;
   if (intf_type() == INTF_TYPE_OTHER) {
      panic("Invalid interface id");
   }
}

inline bool
intf_id_t::operator==(intf_id_t const & other) const {
   return intfId_ == other.intfId_;
}

inline bool
intf_id_t::operator!=(intf_id_t const & other) const {
   return intfId_ != other.intfId_;
}

inline bool
intf_id_t::operator<(intf_id_t const & other) const {
   return intfId_ < other.intfId_;
}

}

#endif // EOS_INLINE_INTF_H
