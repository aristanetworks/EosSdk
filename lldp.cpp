// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/lldp.h"
#include "impl.h"

namespace eos {

//
// lldp_mgr implementation
//

class lldp_mgr_impl : public lldp_mgr {
 public:
   lldp_mgr_impl() {
   }

   lldp_remote_system_iter_t lldp_remote_system_iter(intf_id_t intf) const {
      lldp_remote_system_iter_t * nop = 0;
      return *nop;
   }
   lldp_intf_iter_t lldp_intf_iter() const {
      lldp_intf_iter_t * nop = 0;
      return *nop;
   }
   lldp_neighbor_iter_t lldp_neighbor_iter() const {
      lldp_neighbor_iter_t * nop = 0;
      return *nop;
   }
   lldp_neighbor_iter_t lldp_neighbor_iter(intf_id_t intf) const {
      lldp_neighbor_iter_t * nop = 0;
      return *nop;
   }

   void enabled_is(bool enabled) { return; }
   bool enabled() const { return true; }
   void tx_timer_is(uint32_t seconds) { return; }
   int tx_timer() const { return 99; }
   void hold_time_is(uint32_t seconds) { return; }
   int hold_time() const { return 198; }

   void intf_enabled_is(intf_id_t intfId, lldp_intf_enabled_t enabled) { return; }
   lldp_intf_enabled_t intf_enabled(intf_id_t intf) const {
      return LLDP_INTF_ENABLE_BIDIR;
   }

   void
   tx_tlv_set(lldp_neighbor_t const & peer,  lldp_tlv_type_t tlv_type,
              std::string const & data) {
      return;
   }
   void tx_tlv_del(lldp_neighbor_t const & peer, lldp_tlv_type_t tlv_type) { 
      return; 
   }
   bool tlv_exists(lldp_neighbor_t const & peer, lldp_tlv_type_t tlv_type) const {
      return 1;
   }
   std::string tlv(lldp_neighbor_t const & peer, lldp_tlv_type_t tlv_type) const {
      return "";
   }

   lldp_chassis_id_t chassis_id(lldp_neighbor_t const & peer) const {
      return lldp_chassis_id_t(LLDP_CHASSIS_MAC_ADDR, "01:02:03:04:aa:bb");
   }
   lldp_intf_id_t intf_id(lldp_neighbor_t const & peer) const {
      return lldp_intf_id_t(LLDP_INTF_NAME, "Ethernet1");
   }
   std::string intf_description(lldp_neighbor_t const & peer) const {
      return "best interface ever";
   }
   std::string system_name(lldp_neighbor_t const & peer) const {
      return "some sysname";
   }
   std::string system_description(lldp_neighbor_t const & peer) const {
      return "some sysdescr"; }
   lldp_syscap_t system_capabilities(lldp_neighbor_t const & peer) const {
      return lldp_syscap_t(LLDP_SYSCAP_BRIDGE);
   }
   vlan_id_t default_vlan(lldp_neighbor_t const & peer) const { return 1; }
   vlan_id_t management_vlan(lldp_neighbor_t const & peer) const { return 2; }
   uint32_t max_frame_size(lldp_neighbor_t const & peer) const { return 1500; }
   lldp_lacp_t lacp(lldp_neighbor_t const & peer) const { return lldp_lacp_t(); }
   lldp_phy_t phy(lldp_neighbor_t const & peer) const { return lldp_phy_t(); }
   std::list<lldp_management_address_t> management_address(
                                                lldp_neighbor_t const & peer) const {
      return std::list<lldp_management_address_t>();
   }
   std::map<lldp_tlv_type_t, std::string> tlvs(lldp_neighbor_t const & peer) const {
      std::map<lldp_tlv_type_t, std::string> map;
      return map;
   }
};

DEFINE_STUB_MGR_CTOR(lldp_mgr)

lldp_handler::lldp_handler(lldp_mgr * mgr) :
      base_handler<lldp_mgr, lldp_handler>(mgr) {}

void lldp_handler::on_lldp_tx_timer(uint32_t seconds) {}
void lldp_handler::on_lldp_hold_time(uint32_t seconds) {}
void lldp_handler::on_lldp_intf_enabled(intf_id_t intf, lldp_intf_enabled_t) {}

void lldp_handler::on_lldp_intf_set(lldp_neighbor_t const & peer) {}
void lldp_handler::on_lldp_intf_del(lldp_neighbor_t const & peer) {}
void lldp_handler::on_lldp_intf_change(lldp_neighbor_t const & peer) {}

void lldp_handler::on_lldp_tlv_set(lldp_neighbor_t const & peer, lldp_tlv_type_t,
                                   std::string const &) {}
void lldp_handler::on_lldp_tlv_del(lldp_neighbor_t const & peer, lldp_tlv_type_t) {}
void lldp_handler::on_lldp_chassis_id(lldp_neighbor_t const & peer,
                                      lldp_chassis_id_t) {}
void lldp_handler::on_lldp_intf_id(lldp_neighbor_t const & peer, lldp_intf_id_t) {}
void lldp_handler::on_lldp_system_name(lldp_neighbor_t const & peer,
                                       std::string const &) {}
void lldp_handler::on_lldp_system_description(lldp_neighbor_t const & peer,
                                              std::string const &) {}
void lldp_handler::on_lldp_intf_description(lldp_neighbor_t const & peer,
                                            std::string const &) {}
void lldp_handler::on_lldp_default_vlan(lldp_neighbor_t const & peer, vlan_id_t) {}
void lldp_handler::on_lldp_management_vlan(lldp_neighbor_t const & peer, 
                                           vlan_id_t) {}
void lldp_handler::on_lldp_max_frame_size(lldp_neighbor_t const & peer, uint32_t) {}
void lldp_handler::on_lldp_management_address(lldp_neighbor_t const & peer,
                                     std::list<lldp_management_address_t> const &) {}
void lldp_handler::on_lldp_lacp(lldp_neighbor_t const & peer, lldp_lacp_t const &) {}
void lldp_handler::on_lldp_phy(lldp_neighbor_t const & peer, lldp_phy_t const &) {}

} // end eos namespace
