// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <Agent/AgentBaseLib.h>

int
main( int argc, char **argv ) {
   ExtraOption_t extraOpt = { "load", "", "SDK extension library to load" };

   auto ac = agentContainerIs( "EosSdkAgentContainer", argc, argv, false, 1,
                               &extraOpt );

   ac->doAddAgent( "EosSdk", "EosSdk::Agent", "" );
   ac->doRunAgents();

   return 0;
}
