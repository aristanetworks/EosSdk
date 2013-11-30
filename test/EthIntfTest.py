#!/usr/bin/env python
# Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import EosSdkTestLib
import Tac
import Tracing

import unittest

traceHandle = Tracing.Handle( 'EthIntfApiTests' )
t0 = traceHandle.trace0
t1 = traceHandle.trace1
Tracing.traceSettingIs( "EthIntfApiTests/01,EthIntfTestAgent,EosSdk*" )

AGENT_NAME = "EthIntfTestAgent"
SYSDB_PORT = 9631 # Pick a hopefully unused Sysdb port
agentManager = EosSdkTestLib.AgentManager( sysname="IntfTest", sysdbPort=SYSDB_PORT )
sysdb = agentManager.startAgent( "Sysdb" )


class EthIntfApiTest( unittest.TestCase ):
   # Ignore attributes defined outside the __init__
   # pylint: disable-msg=W0201
   def setUp( self ):
      self.config = sysdb[ "interface" ][ "config" ][ "eth" ][ "phy" ]
      self.status = sysdb[ "interface" ][ "status" ][ "eth" ][ "phy" ]
      self.et1Config, self.et1Status = self._createInterface()
      agentManager.startAgent( AGENT_NAME )

   def tearDown( self ):
      agentManager.stopAgent( AGENT_NAME )
      self.config.clear()
      self.status.clear()

   def _createInterface( self, name="Ethernet1", mac="00:11:22:33:44:55" ):
      intfStatus = self.status.intfStatus.newMember( name, None, 0, mac )
      intfStatus.addr = mac
      intfConfig = self.config.intfConfig[ name ]
      return intfConfig, intfStatus

   def testEthAddrHandler( self ):
      t0( "Testing the eth_addr handler" )
      def testEthAddr( intfConfig, intfStatus ):
         # Check handling the initial state
         Tac.waitFor(
            lambda: intfConfig.description == "Eth addr is now %s" %(
               intfStatus.addr ) )
         
         intfStatus.addr = "55:44:33:22:11:00"
         Tac.waitFor(
            lambda: intfConfig.description == "Eth addr is now 55:44:33:22:11:00" )
         
         intfStatus.addr = "00:11:22:33:44:55"
         Tac.waitFor(
            lambda: intfConfig.description == "Eth addr is now 00:11:22:33:44:55" )

      t1( "Ensure that our handler fires for pre-existing interfaces" )
      testEthAddr( self.et1Config, self.et1Status )
      t1( "Now react to an interface that was added after agent initialization" )
      et2Config, et2Status = self._createInterface( "Ethernet2",
                                                    "00:aa:bb:cc:dd:ee" )
      testEthAddr( et2Config, et2Status )

if __name__ == '__main__':
   unittest.longMessage = True
   unittest.main( buffer=False )
