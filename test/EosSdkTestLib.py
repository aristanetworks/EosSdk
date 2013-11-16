#!/usr/bin/env python
# Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import Artest
import Tac

def startEosSdk( entityManager, appLibPath ):
   agent = Tac.newInstance( "EOS::Agent", "EosSdk" )
   agent.entityManager = entityManager.cEntityManager()
   agent.extraArg = Tac.newInstance( "AgentBase::ExtraArg", "args" )
   agent.extraArg.extraArg[ "app" ] = appLibPath
   agent.initialized = True
   return agent

def testAppPath( app ):
   return Artest.findBldDir() + "/.libs/lib%s.so" % app
