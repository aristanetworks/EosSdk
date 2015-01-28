// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/intf.h"

namespace eos {

intf_id_t::intf_id_t() {
   
}

intf_id_t::intf_id_t(char const * name) :
      intfId_() {
   
}

intf_id_t::intf_id_t(std::string const & name) :
      intfId_() {
   
}

bool
intf_id_t::is_null0() const {
   return false;
}

bool
intf_id_t::is_subintf() const {
   return false;
}

intf_type_t
intf_id_t::intf_type() const {
   return INTF_TYPE_NULL;
}

std::string
intf_id_t::to_string() const {
   return NULL;
}

bool
intf_id_t::operator!() const {
   return false;
}


}
