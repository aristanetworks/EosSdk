// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cerrno>
#include <cstring>
#include <unistd.h>

#include <iostream>

#include <Agent/AgentBaseLib.h>


static AgentBase::AgentContainer::Ptr
createAgentContainer( int argc, char **argv ) {
   ExtraOption_t extraOpt = { "app", "", "Path to the app to launch" };

   auto ac = agentContainerIs( "EosSdkAgentContainer", argc, argv, false, 1,
                               &extraOpt );
   Tac::String app = ac->extraArg()->extraArg("app");
   if ( app.empty() ) {
      std::cerr << "Invalid usage: please specify --app=/path/to/libFoo.so"
         << std::endl;
      return 0;
   }
   if ( access( app.charPtr(), R_OK ) ) {
      std::cerr << "Invalid --app path: " << strerror( errno ) << std::endl;
      return 0;
   }
   return ac;
}


int
main( int argc, char **argv ) {
   auto container = createAgentContainer( argc, argv );
   if (!container) {
      return 1;
   }
   container->doAddAgent( "EosSdk", "EosSdk::Agent", "" );
   container->doRunAgents();
   return 42;  // We should never get back here.
}
