#!/usr/bin/env python
# Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import AgentDirectory
import ManagedSubprocess
import PyClient
import Tac
import Tracing
import socket

import os

traceHandle = Tracing.Handle( 'EosSdkTestLib' )
t0 = traceHandle.trace0
t1 = traceHandle.trace1

class EosSdkException( Exception ):
   pass

class AgentAlreadyRunningException( EosSdkException ):
   def __init__( self, agent ):
      self.agent = agent
      EosSdkException.__init__( self, "Agent %s is already running (pid %d)" %
                          (agent["name"], agent["pid"]) )

class AgentNotRunningException( EosSdkException ):
   def __init__( self, agentName ):
      EosSdkException.__init__( self, "Agent %s is not running" % agentName )

class UnknownAgentException( EosSdkException ):
   def __init__( self, agent ):
      EosSdkException.__init__( self, "Agent %s exists (pid %d) but is not owned "
                                "by this manager" % (agent["name"], agent["pid"]) )


class AgentManager( object ):
   def __init__( self, sysname='ar', logdir=None ):
      self.sysname_ = sysname
      if logdir and not os.path.isdir( logdir ):
         raise ValueError( "No existing directory at %s" % logdir )
      self.logdir_ = logdir
      self.agentProcesses_ = {} # Mapping from agent name to managed subprocess

   def startAgent( self, agentName, asRoot=True, argv=None,
                   sysdbPort=None, sysdbSockname=None ):
      """ Start a named agent and return an entity at the agent's
      root. If a logdir was set for this manager, output from this
      agent will be stored in a file with this agent's name in that
      directory. """
      Tac.sysnameIs( self.sysname_ )
      agent = AgentDirectory.agent( self.sysname_, agentName )
      if agent:
         raise AgentAlreadyRunningException( agent )
      t0( "Starting agent %s with sysname %s" % (agentName, self.sysname_) )
      cmd = [ agentName , "--sysname=%s" % self.sysname_ ] + (argv or [])
      if asRoot:
         cmd.insert( 0, 'arsudo' )
      env = dict( os.environ )
      if sysdbPort:
         env[ 'SYSDBPORT' ] = str( sysdbPort )
      if sysdbSockname:
         env[ 'SYSDBSOCKNAME' ] = sysdbSockname
      outfile = None
      if self.logdir_:
         outfile = file( getLogfileName( agentName ), 'w' )
      p = ManagedSubprocess.Popen( argv=cmd, verbose=True, env=env,
                                   stdout=outfile, stderr=outfile )
      self.agentProcesses_[ agentName ] = p
      return self.getAgentRoot( agentName )


   def stopAgent( self, agentName ):
      t1( "Stopping agent %s" % agentName )
      agent = AgentDirectory.agent( self.sysname_, agentName )
      if not agent:
         raise AgentNotRunningException( agentName )
      if agentName not in self.agentProcesses_:
         raise UnknownAgentException( agent )
      self.agentProcesses_[ agentName ].kill()
      def _agentIsGone():
         return AgentDirectory.agent( self.sysname_, agentName ) is None
      Tac.waitFor( _agentIsGone, timeout=60, sleep=True,
                   description="Agent to go away" )

   def getAgentRoot( self, agentName ):
      t1( "Getting the agent root for %s" % agentName )
      try:
         pyClient = PyClient.PyClient( self.sysname_, agentName, reconnect=False )
      except ( socket.error, PyClient.RpcConnectionError ), e:
         # If the agent starts enough to accept a pyclient connection, and
         # then dies, we're likely to end up here.  If we have the
         # ManagedSubprocess, then cat the log file.
         filename = self.getLogfileName( agentName )
         if self.logdir_ and os.path.exists( filename ):
            print file( filename ).read()
         print 'Exception: ', e
         raise AgentNotRunningException( agentName )
   
      entity = pyClient.root()[self.sysname_][agentName]
      return entity

   def getLogfileName( self, agentName ):
      return os.path.join( self.logdir_, agentName )
