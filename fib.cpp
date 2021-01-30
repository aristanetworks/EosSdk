// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/fib.h"
#include "impl.h"

namespace eos {

class fib_mgr_impl : public fib_mgr {
 public:

   void set_routeinit_task( int const ratio ) {
      return;
   }

   void set_route6init_task( int const ratio ) {
      return;
   }

   void set_fecinit_task( int const ratio ) {
      return;
   }

   void set_fec6init_task( int const ratio ) {
      return;
   }

   bool fib_fec_set(fib_fec_t const & fec) {
      // TODO: add/replace the fec
      return true;
   }

   void fib_fec_del(fib_fec_key_t const & fec_key) {
      // TODO: delete the fec from status
      return;
   }

   bool fib_fec_exists(fib_fec_key_t const & fec_key) {
      // TODO: check if fec exists
      return true;
   }

   fib_fec_t fib_fec(fib_fec_key_t const & fec_key) {
      // TODO: return fec from the status
      fib_fec_t fec;
      return fec;
   }

   bool fib_route_set(fib_route_t const & route) {
      // TODO: add/replace the route
      return true;
   }

   void fib_route_del(fib_route_key_t const & route_key) {
      // TODO: delete the route from status
      return;
   }

   bool fib_route_exists(fib_route_key_t const & route_key) {
      // TODO: check if route exists
      return true;
   }

   fib_route_t fib_route(fib_route_key_t const & route_key) {
      // TODO: return route from the status
      fib_route_t route;
      return route;
   }

   bool register_vrf(std::string const & vrf_name, bool set_vrf) {
      return true;
   }

   fib_route_iter_t fib_route_iter() const {
      fib_route_iter_t *nop = 0;
      return *nop;
   }

   fib_fec_iter_t fib_fec_iter() const {
      fib_fec_iter_t *nop = 0;
      return *nop;
   }

   mgr_mode_type_t mode_type() {
      return MODE_TYPE_READ_ONLY;
   }
};

DEFINE_STUB_MGR_CTOR(fib_mgr)

fib_handler::fib_handler(fib_mgr *mgr) : 
      base_handler<fib_mgr, fib_handler>(mgr) {
}

void fib_handler::on_route_set(fib_route_t const&) {
}

void fib_handler::on_route_del(fib_route_key_t const &) {
}

void fib_handler::on_fec_set(fib_fec_t const&) {
}

void fib_handler::on_fec_del(fib_fec_key_t const&) {
}

} // namespace eos
