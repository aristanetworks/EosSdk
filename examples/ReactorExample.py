#!/usr/bin/env python
# Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import eossdk

class MyIntfHandler( eossdk.AgentHandler, eossdk.IntfHandler ):
   def __init__( self, intfMgr, agentMgr ):
      eossdk.AgentHandler.__init__( self, agentMgr )
      eossdk.IntfHandler.__init__( self, intfMgr )
      self.numIntfChanges = 0
      print "Initialized"

   # Callback provided by AgentHandler when all state is synchronized
   def on_initialized( self ):
      print "We are initialized!"
      self.watch_all_intfs( True )

   # Callback provided by IntfHandler when an interface's configuration changes
   def on_admin_enabled( self, intfId, operState ):
      intfState = 'up' if operState == eossdk.INTF_OPER_ENABLED else 'down'
      print "The state of", intfId.to_string(), "is now", intfState
      self.numIntfChanges += 1
      print "   We have seen", self.numIntfChanges, "state changes"

sdk = eossdk.Sdk()
mta = MyIntfHandler( sdk.get_intf_mgr(), sdk.get_agent_mgr() )
sdk.main_loop( "MyIntfAgent", [] )
