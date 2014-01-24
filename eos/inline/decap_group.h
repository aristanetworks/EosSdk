// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_DECAP_GROUP_H
#define EOS_INLINE_DECAP_GROUP_H

#include <eos/panic.h>

namespace eos {

inline decap_group_t::decap_group_t() {
}

inline decap_group_t::decap_group_t(std::string group_name,
                                    ip_addr_t const &destination_ip,
                                    decap_protocol_type_t protocol)
   : group_name_(group_name),
     destination_addr_(destination_ip),
     protocol_type_(protocol) {
   if(group_name.empty()) {
      panic("group_name must be a non-empty string");
   } else if(protocol == PROTOCOL_TYPE_NULL) {
      panic("must pass a tunnel protocol other than PROTOCOL_TYPE_NULL");
   }
}

// Accessors and mutators on decap_group_t

inline std::string
decap_group_t::group_name() const {
   return group_name_;
}

inline ip_addr_t const &
decap_group_t::destination_addr() const {
   return destination_addr_;
}

inline void
decap_group_t::destination_addr_is(ip_addr_t const & addr) {
   destination_addr_ = addr;
}

inline decap_protocol_type_t
decap_group_t::protocol_type() const {
   return protocol_type_;
}

inline void
decap_group_t::protocol_type_is(decap_protocol_type_t protocol_type) {
   protocol_type_ = protocol_type;
}

}

#endif // EOS_INLINE_DECAP_GROUP_H
