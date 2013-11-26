#!/usr/bin/env python
# Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import EosSdkTestLib
import unittest
import socket
import time

DEFAULT_PORT = 10000
PREFIX = 'You said: '
SERVER_BUF_SIZE = 1024 -len(PREFIX)
CONNECTION_TIMEOUT = 10

agentManager = EosSdkTestLib.AgentManager( sysname="EchoBotTest" )
sysdb = agentManager.startAgent( "Sysdb" )

class EchoBotTests( unittest.TestCase ):
   def setUp( self ):
      agentManager.startAgent( "EchoBot" )

   def tearDown( self ):
      agentManager.stopAgent( "EchoBot" )

   def testConnectivity( self ):
      """ Basic test to make sure we can say something to the agent
      and get an echo'd response """
      client = self._createClientSocket()
      def testEcho( msg ):
         client.send( msg )
         ret = client.recv( len(msg) + len(PREFIX) )
         self.assertEqual( PREFIX + msg, ret )
      testEcho( 'Do you work?' )
      testEcho( 'Seems like you do!' )
      client.close()

   def testLongMessage( self ):
      """ Send a long message and get it all back (with two of the
      PREFIXes, because EchoBot isn't very smart). """
      client = self._createClientSocket()
      msg = 'A very long message: %r!' % ( '-'*1500 )
      client.send( msg )
      ret = client.recv( len(msg) + len(PREFIX)*2 )
      if len(ret) < len(msg):
         # recv still needs to get some more data, since tcp didn't
         # batch up the call
         ret += client.recv( len(msg) + len(PREFIX)*2 )
      self.assertEqual( PREFIX + msg[:SERVER_BUF_SIZE] + 
                        PREFIX + msg[SERVER_BUF_SIZE:],
                        ret )

   def testServerTimeout( self ):
      """ Connect to the server and then wait for the timeout to
      elapse. Check that the connection was closed. """
      client = self._createClientSocket()
      time.sleep( CONNECTION_TIMEOUT + 1 )
      client.send( 'Here is a message sent to a closed socket' )
      self.assertEqual( client.recv(SERVER_BUF_SIZE), '' )


   def _createClientSocket( self ):
      s = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
      s.setsockopt( socket.SOL_SOCKET, socket.SO_REUSEADDR, 1 )
      s.connect( ( 'localhost', DEFAULT_PORT ) )
      return s

if __name__ == '__main__':
   unittest.longMessage = True
   unittest.main( buffer=False )

