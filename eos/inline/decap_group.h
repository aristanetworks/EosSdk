// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_DECAP_GROUP_H
#define EOS_INLINE_DECAP_GROUP_H

#include <eos/panic.h>

namespace eos {

inline decap_group_t::decap_group_t()
      : group_name_(),
        destination_addr_(),
        protocol_type_(PROTOCOL_TYPE_NULL),
        persistent_(false) {
}

inline decap_group_t::decap_group_t(std::string group_name,
                                    ip_addr_t const &destination_ip,
                                    decap_protocol_type_t protocol)
   : group_name_(group_name),
     destination_addr_(destination_ip),
     protocol_type_(protocol),
     persistent_(false) {
   if(group_name.empty()) {
      panic("group_name must be a non-empty string");
   } else if(protocol == PROTOCOL_TYPE_NULL) {
      panic("must pass a tunnel protocol other than PROTOCOL_TYPE_NULL");
   }
}

inline bool
decap_group_t::operator==(decap_group_t const & other) const {
   return protocol_type_ == other.protocol_type_
      && destination_addr_ == other.destination_addr_
      && group_name_ == other.group_name_;
}

inline bool
decap_group_t::operator!=(decap_group_t const & other) const {
   return !(*this == other);
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

inline bool
decap_group_t::persistent() const {
   return persistent_;
}

inline void
decap_group_t::persistent_is(bool persistent) {
   persistent_ = persistent;
}

}

#endif // EOS_INLINE_DECAP_GROUP_H
