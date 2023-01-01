// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/ip_route.h"
#include "impl.h"

namespace eos {

class ip_route_mgr_impl : public ip_route_mgr {
 public:
   ip_route_mgr_impl() {
   }

   void resync_complete() {
      // TODO: No op impl.
   }

   void resync_init()  {
      // TODO: No op impl.
   }

   uint32_t tag() const {
      return 0; // TODO: No op impl.
   }

   void tag_is(uint32_t tag) {
      // TODO: No op impl.
   }

   ip_route_iter_t ip_route_iter() const {
      ip_route_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   virtual ip_route_iter_t ip_route_iter(std::string const & vrfName) const {
      ip_route_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   ip_route_via_iter_t ip_route_via_iter(ip_route_key_t const & key) const {
      ip_route_via_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   ip_route_via_iter_t ip_route_via_iter(ip_route_key_t const &,
                                         std::string vrfName) const {
      ip_route_via_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   bool exists(ip_route_key_t const &, std::string vrfName) const {
      return false;  // TODO: No op impl.
   }

   bool exists(const ip_route_key_t & route_key) const {
      return false;  // TODO: No op impl.
   }

   bool exists(const ip_route_via_t & route_via) const {
      return false;  // TODO: No op impl.
   }

   bool exists(const ip_route_via_t & route_via,
               std::string vrfName) const {
      return false;  // TODO: No op impl.
   }

   ip_route_t ip_route(ip_route_key_t const & route_key) {
      // TODO: No op impl.
      return ip_route_t();
   }
   virtual ip_route_t ip_route(ip_route_key_t const &,
                               std::string vrfName) {
       // TODO: No op impl.
      return ip_route_t();
   }

   void ip_route_set(const ip_route_t & route) {
      // TODO: No op impl.
   }

   void ip_route_set(const ip_route_t & route,
                     ip_route_action_t expected_type) {
      // TODO: No op impl.
   }

   void ip_route_set(ip_route_t const &,
                     std::string vrfName) {
      // TODO: No op impl.
   }

   void ip_route_del(ip_route_key_t const &,
                     std::string vrfName) {
      // TODO: No op impl.
   }

   void ip_route_del(const ip_route_key_t & route_key) {
      // TODO: No op impl.
   }

   void ip_route_via_set(const ip_route_via_t & route_via) {
      // TODO: No op impl.
   }

   void ip_route_via_del(const ip_route_via_t & route_via) {
      // TODO: No op impl.
   }

   void ip_route_via_set(const ip_route_via_t & route_via,
                         std::string vrfName) {
      // TODO: No op impl.
   }

   void ip_route_via_del(const ip_route_via_t & route_via,
                         std::string vrfName) {
      // TODO: No op impl.
   }

};

DEFINE_STUB_MGR_CTOR(ip_route_mgr)

ip_route_iter_t
ip_route_mgr::ip_route_iter( std::string vrf ) const {
   return static_cast<const ip_route_mgr_impl * >( this )->ip_route_iter( vrf );
}

}  // end namespace eos
