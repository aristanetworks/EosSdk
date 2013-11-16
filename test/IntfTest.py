#!/usr/bin/env python
# Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import Artest
import EntityManager
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

sysname = "IntfTest"

em = EntityManager.Local( sysname )

agent = startEosSdk( em, testAppPath( "IntfTestApp" ) )

sysdb = em.root()
config = sysdb[ "interface" ][ "config" ][ "eth" ][ "phy" ]
status = sysdb[ "interface" ][ "status" ][ "eth" ][ "phy" ]

# Create Ethernet1
intfStatus = status.intfStatus.newMember( "Ethernet1", None, 0, "00:11:22:33:44:55" )
intfConfig = config.intfConfig[ "Ethernet1" ]

intfConfig.adminEnabled = False
Tac.waitFor( lambda: intfConfig.description == "Admin enabled is 0" )

intfStatus.operStatus = "intfOperDown"
Tac.waitFor( lambda: intfConfig.description == "Oper status is 2" )

intfConfig.adminEnabled = True
Tac.waitFor( lambda: intfConfig.description == "Admin enabled is 1" )

intfStatus.operStatus = "intfOperUp"
Tac.waitFor( lambda: intfConfig.description == "Oper status is 1" )

# Delete Ethernet1
del status.intfStatus[ "Ethernet1" ]

Tac.runActivities( 0 )
