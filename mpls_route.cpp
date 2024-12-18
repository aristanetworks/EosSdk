// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/mpls_route.h"
#include "impl.h"

namespace eos {

class mpls_route_mgr_impl : public mpls_route_mgr {
 public:
   mpls_route_mgr_impl() {
   }

   void resync_init() {
      // TODO: No op impl
   }

   void resync_complete() {
      // TODO: No op impl
   }

   mpls_route_iter_t mpls_route_iter() const {
      mpls_route_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   mpls_route_status_iter_t mpls_route_status_iter() const {
      mpls_route_status_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   bool exists(mpls_route_key_t const & route_key) const {
      return false;  // TODO: No op impl.
   }

   bool exists(mpls_route_via_t const & route_via) const {
      return false;  // TODO: No op impl.
   }

   void mpls_route_set(mpls_route_t const & route) {
      // TODO: No op impl.
   }

   void mpls_route_via_set(mpls_route_via_t const & route_via) {
      // TODO: No op impl.
   }

   void mpls_route_backup_via_set(mpls_route_via_t const & route_via) {
      // TODO: No op impl.
   }

   void mpls_route_del(mpls_route_key_t const & route_key) {
      // TODO: No op impl.
   }

   void mpls_route_via_del(mpls_route_via_t const & route_via) {
      // TODO: No op impl.
   }

   void mpls_route_backup_via_del(mpls_route_via_t const & route_via) {
      // TODO: No op impl.
   }

   mpls_route_via_iter_t mpls_route_via_iter(mpls_route_key_t const & key) const {
      mpls_route_via_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   mpls_route_via_iter_t mpls_route_backup_via_iter(
         mpls_route_key_t const & key ) const {
      mpls_route_via_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   mpls_route_via_status_iter_t mpls_route_via_status_iter(
         mpls_label_t const label) const {
      mpls_route_via_status_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   mpls_route_via_status_iter_t
   mpls_route_via_status_iter(mpls_route_key_t const & route_key) const {
      mpls_route_via_status_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   mpls_route_via_status_iter_t
   mpls_route_via_status_iter(mpls_fec_id_t) const {
      mpls_route_via_status_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   mpls_fec_id_t
   fec_id(mpls_label_t label) const {
      return mpls_fec_id_t();
   }

   mpls_fec_id_t
   fec_id(mpls_route_key_t const & route_key) const {
      return mpls_fec_id_t();
   }

   mpls_route_metric_t
   metric(mpls_label_t label) const {
      return 0;
   }

   mpls_route_metric_t
   metric(mpls_route_key_t const & route_key) const {
      return 0;
   }
};

// -- pimpl wrappers to mpls_route_backup functions

mpls_route_via_iter_t mpls_route_mgr::mpls_route_backup_via_iter(
    mpls_route_key_t const& route_key) {
   return static_cast<mpls_route_mgr_impl*>(this)->mpls_route_backup_via_iter(
       route_key);
}

void mpls_route_mgr::mpls_route_backup_via_set(mpls_route_via_t const& via) {
   return static_cast<mpls_route_mgr_impl*>(this)->mpls_route_backup_via_set(via);
}

void mpls_route_mgr::mpls_route_backup_via_del(mpls_route_via_t const& via) {
   return static_cast<mpls_route_mgr_impl*>(this)->mpls_route_backup_via_del(via);
}

// -- end of wrappers

DEFINE_STUB_MGR_CTOR(mpls_route_mgr)

mpls_route_handler::mpls_route_handler(mpls_route_mgr *mgr) : base_handler(mgr) {
}

void mpls_route_handler::watch_all_mpls_routes(bool) {}
void mpls_route_handler::watch_mpls_route(mpls_label_t const &label, bool) {}
void mpls_route_handler::watch_mpls_route(mpls_route_key_t const & route_key,
                                          bool) {}

void mpls_route_handler::on_mpls_route_set(mpls_label_t label, mpls_fec_id_t) {}
void mpls_route_handler::on_mpls_route_set(mpls_route_key_t const & route_key,
                                           mpls_fec_id_t) {}

void mpls_route_handler::on_mpls_route_del(mpls_label_t label) {}
void mpls_route_handler::on_mpls_route_del(mpls_route_key_t const & route_key) {}

void mpls_route_handler::on_mpls_fec_set(mpls_fec_id_t) {}
void mpls_route_handler::on_mpls_fec_del(mpls_fec_id_t) {}

}  // end namespace eos
