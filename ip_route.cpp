// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/ip_route.h"

namespace eos {

ip_route_key_t::ip_route_key_t() : prefix(), preference(1), metric(0) {
}

ip_route_key_t::ip_route_key_t(const ip_prefix_t & prefix) :
      prefix(prefix), preference(1), metric(0) {
}

ip_route_key_t::ip_route_key_t(const ip_prefix_t & prefix,
                               ip_route_preference_t preference) :
      prefix(prefix), preference(preference), metric(0) {
}

ip_route_t::ip_route_t() : key(), tag(0), persistent(false) {
}

ip_route_t::ip_route_t(const ip_route_key_t & route_key) :
      key(route_key), tag(0), persistent(false) {
}

ip_route_via_t::ip_route_via_t() : route_key(), hop(), intf() {
}

ip_route_via_t::ip_route_via_t(const ip_route_key_t & route_key)
      : route_key(route_key), hop(), intf() {
}

ip_route_mgr::ip_route_mgr() {
}

class ip_route_mgr_impl : public ip_route_mgr {
 public:
   ip_route_mgr_impl() {
   }
};

ip_route_mgr *
get_ip_route_mgr() {
   static ip_route_mgr_impl impl;
   return &impl;
}

void
ip_route_mgr::ip_route_foreach(callback_func_route handler, void *context) {
   // TODO: No op impl.
}

void
ip_route_mgr::ip_route_foreach(callback_func_route handler, void *context,
                               const ip_route_t & bookmark) {
   // TODO: No op impl.
}

void
ip_route_mgr::ip_route_via_foreach(const ip_route_key_t & route_key,
                                   callback_func_via handler, void *context) {
   // TODO: No op impl.
}

bool
ip_route_mgr::exists(const ip_route_key_t & route_key) const {
   return false;  // TODO: No op impl.
}

bool
ip_route_mgr::exists(const ip_route_via_t & route_via) const {
   return false;  // TODO: No op impl.
}

void
ip_route_mgr::ip_route_set(const ip_route_t & route) {
   // TODO: No op impl.
}

void
ip_route_mgr::ip_route_del(const ip_route_key_t & route_key) {
   // TODO: No op impl.
}

void
ip_route_mgr::ip_route_via_set(const ip_route_via_t & route_via) {
   // TODO: No op impl.
}

void
ip_route_mgr::ip_route_via_del(const ip_route_via_t & route_via) {
   // TODO: No op impl.
}

}  // end namespace eos
