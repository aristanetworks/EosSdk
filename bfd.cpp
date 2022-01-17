// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/bfd.h>
#include <impl.h>

namespace eos {

/// The manager for Bfd
class bfd_session_mgr_impl : public bfd_session_mgr {
 public:
   ~bfd_session_mgr_impl() {
   }

   bfd_session_iter_t session_iter() const {
      bfd_session_iter_t * nop = 0;
      return *nop;
   }

   bool exists(bfd_session_key_t const & key) const {
      return false;
   }

   void session_set(bfd_session_key_t const & key) {
   }

   bfd_session_t session(bfd_session_key_t const & key) const {
      return eos::bfd_session_t();
   }

   void session_del(bfd_session_key_t const & key) {
   }

   void default_interval_is(bfd_interval_t const & cfg) {
   }

   bfd_interval_t default_interval() const {
      return eos::bfd_interval_t();
   }

   void interval_is(intf_id_t intf, bfd_interval_t const & cfg) {
   }

   bfd_interval_t interval(intf_id_t intf) const {
      return eos::bfd_interval_t();
   }

   void interval_reset(intf_id_t intf) {
   }

   bfd_session_status_t session_status(bfd_session_key_t const & key) const {
      return eos::BFD_SESSION_STATUS_NULL;
   }

   sbfd_echo_session_iter_t sbfd_echo_session_iter() const {
      sbfd_echo_session_iter_t * nop = nullptr;
      return *nop;
   }
   bool sbfd_echo_session_exists( sbfd_echo_session_key_t const & ) const {
      return false;
   }
   void sbfd_echo_session_set( sbfd_echo_session_key_t const & ) {}
   void sbfd_echo_session_del( sbfd_echo_session_key_t const & ) {}
   void sbfd_echo_default_interval_set( sbfd_interval_t const & ) {}
   sbfd_interval_t sbfd_echo_default_interval() const {
      return sbfd_interval_t();
   }
   void sbfd_echo_interval_set( sbfd_echo_session_key_t const &,
                                sbfd_interval_t const & ) {}
   sbfd_interval_t
   sbfd_echo_interval( sbfd_echo_session_key_t const & ) const {
      return sbfd_interval_t();
   }
   void sbfd_echo_interval_reset( sbfd_echo_session_key_t const & ) {}
   void sbfd_echo_rtt_enabled_set( sbfd_echo_session_key_t const &, bool ) {
   }
   bool sbfd_echo_rtt_enabled( sbfd_echo_session_key_t const & ) const {
      return false;
   }
   bfd_session_status_t
   sbfd_echo_session_status( sbfd_echo_session_key_t const & ) const {
      return eos::BFD_SESSION_STATUS_NULL;
   }
};

DEFINE_STUB_MGR_CTOR(bfd_session_mgr)

bfd_session_handler::bfd_session_handler(bfd_session_mgr *mgr) : base_handler(mgr) {
}

void bfd_session_handler::watch_all_bfd_sessions(bool) {}
void bfd_session_handler::watch_bfd_session(bfd_session_key_t const & key,
                                            bool watch) {}
void bfd_session_handler::on_bfd_session_status(bfd_session_key_t const & key, 
                                                bfd_session_status_t new_status) {}
void bfd_session_handler::on_bfd_session_set(bfd_session_key_t const & key) {}
void bfd_session_handler::on_bfd_session_del(bfd_session_key_t const & key) {}

void
bfd_session_handler::watch_all_sbfd_echo_sessions( bool ) {}
void
bfd_session_handler::watch_sbfd_echo_session( sbfd_echo_session_key_t const &,
                                              bool ) {}
void
bfd_session_handler::on_sbfd_echo_session_status( sbfd_echo_session_key_t const &,
                                                  bfd_session_status_t ) {}
void
bfd_session_handler::on_sbfd_echo_session_set( sbfd_echo_session_key_t const & ) {}
void
bfd_session_handler::on_sbfd_echo_session_del( sbfd_echo_session_key_t const & ) {}
void
bfd_session_handler::on_sbfd_echo_session_rtt(
   sbfd_echo_session_key_t const &, sbfd_echo_session_rtt_stats_t const & ) {}

} // end namespace eos
