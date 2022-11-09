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

      /**
       * Configures the transmit laser output power.
       */
      virtual void tx_output_power_is( intf_id_t intf_id, float power ) = 0;

      /**
       * Returns the transmit laser power.
       */
      virtual float tx_output_power( intf_id_t intf_id ) const = 0;

      /**
       * Get the turn up state of a coherent transmit laser. Note that currently,
       * only CFP2 transceivers are supported.
       * Parameters:
       *    intf_id: The name of an Ethernet interface associated with the
       * Returns: The value of the turnUp state as of the last polling interval.  If
       *    the transceiver is not a supported type, or the transceiver is not a
       *    coherent optic, returns -1.
       */
      virtual int32_t tx_turnup_state( intf_id_t intf_id ) const = 0;

      /**
       * Get the turn up state of a coherent transmit laser. Note that currently,
       * only CFP2 transceivers are supported.
       * Parameters:
       *    intf_id: The name of an Ethernet interface associated with the
       * Returns: The value of the turnUp state as of the last polling interval.  If
       *    the transceiver is not a supported type, or the transceiver is not a
       *    coherent optic, returns -1.
       */
      virtual int32_t rx_turnup_state( intf_id_t intf_id ) const = 0;

      /**
       * Returns the data in the register/EEPROM address space of the transceiver.
       * Note that currently, only CFP2 transceivers are supported.
       * Parameters:
       *    intf_id: The name of an Ethernet interface associated with the
       *       transceiver.
       *    addr: Specifies the address of the register if the transceiver has
       *       a flat address space (such as CFP2).  Specifies the offset of
       *       the register if the transceiver has a paged address space.
       *    location: Specifies the technology specific page/bank of the register if
       *       the transceiver has a paged address space.  Not used if the
       *       transceiver has a flat address space.
       * Returns: The value of the register as of the last polling interval.  If the
       *    transceiver is not a supported type, or the register requested is not
       *    available, returns -1.
       */
      virtual int32_t register_read( intf_id_t intf_id, uint16_t addr,
                                     std::string location = "" ) const = 0;
   protected:
      xcvr_mgr() EOS_SDK_PRIVATE;

   private:
      EOS_SDK_DISALLOW_COPY_CTOR( xcvr_mgr );
};

} // end namespace eos

#endif // EOS_XCVR_H
