#!/usr/bin/env python
# Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import EntityManager
import EosSdkTestLib
import Tac

sysname = "IntfTest"

em = EntityManager.Local( sysname )

agent = EosSdkTestLib.startEosSdk( em, EosSdkTestLib.testAppPath( "IntfTestApp" ) )

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
