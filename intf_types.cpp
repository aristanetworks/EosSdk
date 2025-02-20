// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/intf.h"
#include <impl.h>

namespace eos {

intf_id_t::intf_id_t() {
   intfId_ = 0;  // real impl uses Arnet::IntfId::emptyIntfId = 0xffffffff
}

intf_id_t::intf_id_t(char const * name) :
      intfId_() {
   intfId_ = eos::intf_id_t_ctor(name);
}

intf_id_t::intf_id_t(std::string const & name) :
      intfId_() {
   intfId_ = eos::intf_id_t_ctor(name.c_str());
}

bool
intf_id_t::is_null0() const {
   return eos::intf_id_t_is_null0(intfId_);
}

bool
intf_id_t::is_subintf() const {
   return eos::intf_id_t_is_subintf(intfId_);
}

intf_type_t
intf_id_t::intf_type() const {
   return eos::intf_id_t_intf_type(intfId_);
}

std::string
intf_id_t::to_string() const {
   return eos::intf_id_t_to_string(intfId_);
}

bool
intf_id_t::operator!() const {
   return intfId_ == 0;
}


}
