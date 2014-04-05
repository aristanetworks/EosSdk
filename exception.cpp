// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <string>
#include <sstream>

#include "eos/exception.h"

namespace eos {

// This file contains non-inlined constructors because the constructors
// contain literal strings.  Should they be inlined, there would be one
// copy of each string used in each translation unit, which contributes
// to increased binary size.

no_such_interface_error::no_such_interface_error(intf_id_t intf) noexcept
   : error(std::string("No such interface: ") + intf.to_string()),
     intf_(intf) {
}

no_such_interface_error::no_such_interface_error(std::string const & name)
   noexcept
   : error(std::string("Bad interface name: ") + name), intf_() {
}

not_switchport_eligible_error::not_switchport_eligible_error(intf_id_t i)
   noexcept
   : error(std::string("Interface cannot be used as a switchport: ")
               + i.to_string()),
     intf_(i) {
}

invalid_vlan_error::invalid_vlan_error(vlan_id_t vlan) noexcept
   : error("0 and 4095 aren't valid VLAN IDs"), vlan_(vlan) {
}

static inline std::string
internal_vlan_error_msg(vlan_id_t vlan) {
   std::stringstream str;
   str << "VLAN " << vlan << "is an internal VLAN and cannot be used on"
      " a trunk port";
   return str.str();
}

internal_vlan_error::internal_vlan_error(vlan_id_t vlan) noexcept
   : configuration_error(internal_vlan_error_msg(vlan)), vlan_(vlan) {
}

}
