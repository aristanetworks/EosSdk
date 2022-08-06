// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_XCVR_H
#define EOS_XCVR_H

#include <eos/base.h>
#include <eos/types/intf.h>

/**
 * @file
 * Xcvr management module.
 *
 * This module provide APIs to set and get transceiver transmit and receive
 * laser frequencies.
 */

namespace eos {

/**
 * The xcvr manager.
 * This class configures a transceiver for an interface.  If this is a multilane
 * interface, the configuration must be specified for the first lane (eg,
 * Ethernet1/1).
 */
class EOS_SDK_PUBLIC xcvr_mgr {
   public:
      virtual ~xcvr_mgr();

      /**
       * Configures both transmit and receive laser frequencies.  For modules which
       * support concurrent tuning, using this call will cause the module to tune
       * rx and tx lasers concurrently.  The frequency is specified in GHz.
       *
       * For modules which do not support concurrent tuning, the rx tuning is done
       * first, then the tx.
       */
      virtual void frequency_is( intf_id_t intf_id, uint32_t rx,
                                 uint32_t tx ) = 0;
      /**
       * Configures the receive laser fine frequency.  The frequency is specified
       * in GHz.
       */
      virtual void rx_fine_frequency_is( intf_id_t intf_id, float freq ) = 0;

      /**
       * Configures the receive laser frequency.  The frequency is specified
       * in GHz.
       */
      virtual void rx_frequency_is( intf_id_t intf_id, uint32_t freq ) = 0;

      /**
       * Configures the transmit laser frequency.  The frequency is specified
       * in GHz.
       */
      virtual void tx_frequency_is( intf_id_t intf_id, uint32_t freq ) = 0;

      /**
       * Configures the transmit laser disable.
       */
      virtual void tx_disabled_is( intf_id_t intf_id, bool disable ) = 0;

      /**
       * Returns the currently active receive laser fine frequency.  The frequency
       * is in GHz.
       */
      virtual float rx_fine_frequency( intf_id_t intf_id ) const = 0;

      /**
       * Returns the currently active receive laser frequency.  The frequency
       * is in GHz.
       */
      virtual uint32_t rx_frequency( intf_id_t intf_id ) const = 0;

      /**
       * Returns the currently active transmit laser frequency.  The frequency
       * is in GHz.
       */
      virtual uint32_t tx_frequency( intf_id_t intf_id ) const = 0;

      /**
       * Returns the transmit laser disable.
       */
      virtual bool tx_disabled( intf_id_t intf_id ) const = 0;
   protected:
      xcvr_mgr() EOS_SDK_PRIVATE;

   private:
      EOS_SDK_DISALLOW_COPY_CTOR( xcvr_mgr );
};

} // end namespace eos

#endif // EOS_XCVR_H
