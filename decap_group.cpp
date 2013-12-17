// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>

#include "eos/decap_group.h"

namespace eos {

decap_group_t::decap_group_t() {
}

decap_group_t::decap_group_t(std::string group_name,
                             ip_addr_t const &destination_ip,
                             decap_protocol_type_t protocol)
   : group_name_(group_name),
     destination_addr_(destination_ip),
     protocol_type_(protocol) {
   assert(!group_name.empty() && "group_name must be a non-empty string");
   assert(protocol != PROTOCOL_TYPE_NULL
          && "must pass a tunnel protocol other than PROTOCOL_TYPE_NULL");
}

// Accessors and mutators on decap_group_t

std::string
decap_group_t::group_name() const {
   return group_name_;
}

ip_addr_t const &
decap_group_t::destination_addr() const {
   return destination_addr_;
}

void
decap_group_t::destination_addr_is(ip_addr_t const & addr) {
   destination_addr_ = addr;
}

decap_protocol_type_t
decap_group_t::protocol_type() const {
   return protocol_type_;
}

void
decap_group_t::protocol_type_is(decap_protocol_type_t protocol_type) {
   protocol_type_ = protocol_type;
}

decap_group_mgr::decap_group_mgr() {
}

class decap_group_mgr_impl : public decap_group_mgr {
 public:
   decap_group_mgr_impl() {
   }
};

void
decap_group_mgr::decap_group_foreach(callback_func_decap_group handler,
                                     void *context) {
   // TODO: No op impl.
}

void
decap_group_mgr::decap_group_foreach(callback_func_decap_group handler,
                                     void * context,
                                     decap_group_t const &bookmark) {
   // TODO: No op impl.
}

void
decap_group_mgr::decap_group_set(decap_group_t const &group) {
   // TODO: No op impl.
}

void
decap_group_mgr::decap_group_del(std::string const & group_name) {
   // TODO: No op impl.
}

decap_group_mgr *
get_decap_group_mgr() {
   static decap_group_mgr_impl impl;
   return &impl;
}

};  // end namespace eos
