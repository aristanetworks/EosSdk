// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/fib.h"


namespace eos {

class fib_mgr_impl : public fib_mgr {
   public:
      fib_mgr_impl() {
      }
};

static fib_mgr_impl *
impl() {
   static fib_mgr_impl impl;
   return &impl;
}

fib_mgr *
get_fib_mgr() {
   return impl();
}

fib_mgr::fib_mgr() {
}

bool
fib_mgr::fib_fec_set(fib_fec_t const & fec) {
   // TODO: add/replace the fec
   return true;
}

void
fib_mgr::fib_fec_del(uint64_t const & fec_id) {
   // TODO: delete the fec from status
   return;
}

bool
fib_mgr::fib_fec_exists(uint64_t const & fec_id) {
   // TODO: check if fec exists
   return true;
}

fib_fec_t
fib_mgr::fib_fec(uint64_t const & fec_id) {
   // TODO: return fec from the status
   fib_fec_t fec;
   return fec;
}

bool
fib_mgr::fib_route_set(fib_route_t const & route) {
   // TODO: add/replace the route
   return true;
}

void
fib_mgr::fib_route_del(ip_prefix_t const & prefix) {
   // TODO: delete the route from status
   return;
}

bool
fib_mgr::fib_route_exists(ip_prefix_t const & prefix) {
   // TODO: check if route exists
   return true;
}

fib_route_t
fib_mgr::fib_route(ip_prefix_t const & prefix) {
   // TODO: return route from the status
   fib_route_t route;
   return route;
}

fib_route_iter_t
fib_mgr::fib_route_iter() const {
   fib_route_iter_t *nop = 0;
   return *nop;
}

fib_fec_iter_t
fib_mgr::fib_fec_iter() const {
   fib_fec_iter_t *nop = 0;
   return *nop;
}

} // namespace eos
