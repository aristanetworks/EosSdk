#!/usr/bin/env python
# Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

from __future__ import absolute_import, division, print_function
import eossdk
import argparse
import sys


class XcvrAgent( eossdk.AgentHandler ):
   def __init__( self, agentMgr, xcvrMgr, interfaceNames,
                 rxFreq, rxFineFreq, txFreq, txDisabled, txOutputPower ):
      self.agentMgr_ = agentMgr
      self.xcvrMgr_ = xcvrMgr
      self.intfs_ = interfaceNames
      eossdk.AgentHandler.__init__( self, agentMgr )
      self.rxFreq = rxFreq
      self.rxFineFreq = rxFineFreq
      self.txFreq = txFreq
      self.txDisabled = txDisabled
      self.txOutputPower = txOutputPower

   def on_initialized( self ):
      for intf in self.intfs_:
         intfId = eossdk.IntfId( intf )
         if self.rxFreq and self.txFreq:
            self.xcvrMgr_.frequency_is( intfId, self.rxFreq, self.txFreq )
         elif self.rxFreq:
            self.xcvrMgr_.rx_frequency_is( intfId, self.rxFreq )
         elif self.txFreq:
            self.xcvrMgr_.tx_frequency_is( intfId, self.txFreq )
         if self.rxFineFreq is not None:
            self.xcvrMgr_.rx_fine_frequency_is( intfId, self.rxFineFreq )
         if self.txDisabled is not None:
            self.xcvrMgr_.tx_disabled_is( intfId, self.txDisabled )
         if self.txOutputPower is not None:
            self.xcvrMgr_.tx_output_power_is( intfId, self.txOutputPower )
         print( "New settings for %s:" % intf )
         print( "   rx frequency: %d" % self.xcvrMgr_.rx_frequency( intfId ) )
         print( "   rx fine frequency: %f" %
                self.xcvrMgr_.rx_fine_frequency( intfId ) )
         print( "   tx frequency: %d" % self.xcvrMgr_.tx_frequency( intfId ) )
         print( "   tx disabled: %s" % self.xcvrMgr_.tx_disabled( intfId ) )
         print( "   tx output power: %s" % self.xcvrMgr_.tx_output_power( intfId ) )

      self.agentMgr_.exit()


def main( args ):
   parser = argparse.ArgumentParser()
   parser.add_argument( "-i" "--intf", dest="intfs", action="append",
                        default=None, help="Interfaces to set.  May be specified "
                        "multiple times." )
   parser.add_argument( "-r", "--receiveFrequency", dest="rxFreq", type=int,
                        default=None, help="Receive frequency" )
   parser.add_argument( "-t", "--transmitFrequency", dest="txFreq", type=int,
                        default=None, help="Transmit frequency" )
   parser.add_argument( "-f", "--fineFrequency", dest="rxFineFreq", type=float,
                        default=None, help="Fine rx frequency" )
   parser.add_argument( "-d", "--txDisabled", dest="txDisabled", action="store_true",
                        default=False, help="Disable transmitter (omit to enable)" )
   parser.add_argument( "-p", "--txOutputPower", dest="txOutputPower", type=float,
                        default=False, help="Set transmitter output power" )
   parseArgs = parser.parse_args()
   sdk = eossdk.Sdk( 'XcvrMgr' )
   _ = XcvrAgent( sdk.get_agent_mgr(), sdk.get_xcvr_mgr(), parseArgs.intfs,
                  parseArgs.rxFreq, parseArgs.rxFineFreq, parseArgs.txFreq,
                  parseArgs.txDisabled, parseArgs.txOutputPower )
   sdk.main_loop( [ 'XcvrMgr' ] )

if __name__ == '__main__':
   sys.exit( main( sys.argv ) )
