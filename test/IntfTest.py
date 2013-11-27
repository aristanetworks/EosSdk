#!/usr/bin/env python
# Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import EosSdkTestLib
import Tac
import Tracing

import unittest

traceHandle = Tracing.Handle( 'IntfApiTests' )
t0 = traceHandle.trace0
t1 = traceHandle.trace1
Tracing.traceSettingIs( "IntfApiTests/01,IntfTestAgent,EosSdk*" )

AGENT_NAME = "IntfTestAgent"
SYSDB_PORT = 9631 # Pick a hopefully unused Sysdb port
agentManager = EosSdkTestLib.AgentManager( sysname="IntfTest", sysdbPort=SYSDB_PORT )
sysdb = agentManager.startAgent( "Sysdb" )


class IntfApiTest( unittest.TestCase ):
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
      intfConfig = self.config.intfConfig[ name ]
      return intfConfig, intfStatus

   def testOperStatusReactor( self ):
      t0( "Testing the operStatus reactor" )
      def testIntfOperStatus( intfConfig, intfStatus ):
         intfStatus.operStatus = "intfOperDown"
         Tac.waitFor( lambda: intfConfig.description == "Oper status is 2" )
         
         intfStatus.operStatus = "intfOperUp"
         Tac.waitFor( lambda: intfConfig.description == "Oper status is 1" )

      t1( "Ensure that our handler fires for pre-existing interfaces" )
      testIntfOperStatus( self.et1Config, self.et1Status )
      t1( "Now react to an interface that was added after agent initialization" )
      et2Config, et2Status = self._createInterface( "Ethernet2",
                                                    "00:aa:bb:cc:dd:ee" )
      testIntfOperStatus( et2Config, et2Status )

if __name__ == '__main__':
   unittest.longMessage = True
   unittest.main( buffer=False )

