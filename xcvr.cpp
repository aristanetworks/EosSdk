// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/xcvr.h"
#include "impl.h"

namespace eos {

class xcvr_mgr_impl : public xcvr_mgr {
   public:
      xcvr_mgr_impl() {
      }

      void frequency_is( intf_id_t intf_id, uint32_t rx, uint32_t tx ) {
      }

      void rx_fine_frequency_is( intf_id_t intf_id, float freq ) {
      }

      void rx_frequency_is( intf_id_t intf_id, uint32_t freq ) {
      }

      void tx_frequency_is( intf_id_t intf_id, uint32_t freq ) {
      }

      void tx_disabled_is( intf_id_t intf_id, bool disabled ) {
      }

      void tx_output_power_is( intf_id_t intf_id, float power ) {
      }

      int32_t tx_turnup_state( intf_id_t intf_id ) const {
         return 0;
      }
      int32_t rx_turnup_state( intf_id_t intf_id ) const {
         return 0;
      }
       int32_t register_read( intf_id_t intf_id, uint16_t addr,
                              std::string location = "" ) const {
         return 0;
      }

      float rx_fine_frequency( intf_id_t intf_id ) const {
         return 0.0;
      }
      uint32_t rx_frequency( intf_id_t intf_id ) const {
         return 0;
      }
      uint32_t tx_frequency( intf_id_t intf_id ) const {
         return 0;
      }
      bool tx_disabled( intf_id_t intf_id ) const {
         return false;
      }
      float tx_output_power( intf_id_t intf_id ) const {
         return 0.0;
      }

};

DEFINE_STUB_MGR_CTOR( xcvr_mgr )

} // end namespace eos
