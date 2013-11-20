// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <Agent/CAgent.h>
#include <Agent/AgentBaseLib.h>

namespace eos {

void agent_main_loop( const char *agent_name, int argc, char ** argv ) {
   auto container = agentContainerIs( "AgentContainer", argc, argv );
   container->doAddAgent( agent_name, "eos::Agent", "" );
   container->doRunAgents();
   assert( !"why did doRunAgents return?" );
   for(;;) {
      abort();
   }
}

};
