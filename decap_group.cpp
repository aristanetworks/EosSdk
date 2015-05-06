// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>

#include "eos/decap_group.h"
#include "eos/panic.h"
#include "impl.h"

namespace eos {

class decap_group_mgr_impl : public decap_group_mgr {
 public:
    decap_group_mgr_impl() {
    }

    void resync_init() {
       // TODO: No op impl
    }

    void resync_complete() {
       // TODO: No op impl
    }

    decap_group_iter_t decap_group_iter() const {
       decap_group_iter_t * nop = 0;
       return *nop;  // TODO: No op impl.
    }

   decap_group_t decap_group(std::string const & decap_group_name) const {
      return decap_group_t();
   }

    void decap_group_set(decap_group_t const &group) {
       if(group.group_name().empty()) {
          panic("Empty decap group name");
       } else if(group.protocol_type() == PROTOCOL_TYPE_NULL) {
          panic("must pass a tunnel protocol other than PROTOCOL_TYPE_NULL");
       }
       // TODO: No op impl.
    }

    void decap_group_del(std::string const & group_name) {
       // TODO: No op impl.
    }
};

DEFINE_STUB_MGR_CTOR(decap_group_mgr)

};  // end namespace eos
