#!/usr/bin/env python3
# Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import argparse
import sys
import eossdk


class BfdAgent( eossdk.AgentHandler, eossdk.BfdSessionHandler ):
   def __init__( self, agentMgr, bfdSessionMgr, peerIp, intf ):
      self.agentMgr = agentMgr
      self.bfdSessionMgr = bfdSessionMgr
      self.peerIp = peerIp
      self.intf = intf
      ipAddr = eossdk.IpAddr( self.peerIp )
      intfId = eossdk.IntfId( self.intf )
      self.peer = eossdk.BfdSessionKey(
         ipAddr, "default", eossdk.BFD_SESSION_TYPE_NORMAL, intfId )
      self.tracer = eossdk.Tracer( "BfdAgent" )
      eossdk.AgentHandler.__init__( self, self.agentMgr )
      eossdk.BfdSessionHandler.__init__( self, self.bfdSessionMgr )
      self.tracer.trace0( "Constructed" )

   def on_initialized( self ):
      self.tracer.trace0( "Initialized" )
      self.bfdSessionMgr.session_set( self.peer )
      self.watch_bfd_session( self.peer, True )
      self.tracer.trace0( "BFD session created" )

   def on_agent_enabled( self, enabled ):
      self.tracer.trace0( f"Agent enabled: {enabled}" )
      if not enabled:
         self.watch_bfd_session( self.peer, False )
         self.bfdSessionMgr.session_del( self.peer )
         self.tracer.trace0( "BFD session deleted" )
         self.agentMgr.agent_shutdown_complete_is( True )

   def on_bfd_session_status( self, key, status ):
      self.tracer.trace0( f"{key.to_string()} {status}" )

if __name__ == '__main__':
   parser = argparse.ArgumentParser()
   parser.add_argument( '--peer-ip', help="Peer's IP address", required=True )
   parser.add_argument( '--intf', help="Interface name", required=True )
   args, _ = parser.parse_known_args( sys.argv )
   sdk = eossdk.Sdk()
   _ = BfdAgent(
      sdk.get_agent_mgr(),
      sdk.get_bfd_session_mgr(),
      args.peer_ip,
      args.intf )
   sdk.main_loop( sys.argv )
