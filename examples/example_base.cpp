// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/sdk.h>
#include <eos/tracing.h>


// This file is a simple framework for constructing an agent. It does
// nothing (except to emit some tracing), but contains the common
// setup code that most agents will have in common.
//
// Make the agent using a 32-bit linux build environment:
//    bash# g++ -leos -std=gnu++14 examples/example_base.cpp -o exampleagent
// Now you can transfer the binary to flash: on an EOS instance with
// EosSdk.i686.rpm installed and run the agent from bash:
//    bash# TRACE=EosSdk* /mnt/flash/exampleagent
// or from the CLI
// (conf)# daemon example_agent
// (conf-daemon-example_agent)# exec /mnt/flash/exampleagent
// (conf-daemon-example_agent)# no shutdown


class example_agent : public eos::agent_handler {
 public:
   explicit example_agent(eos::sdk & sdk) 
         : t("example_agent"), 
           eos::agent_handler(sdk.get_agent_mgr()) {
      t.trace0("Constructed agent");
      // <any initial set up code>
   }

   void on_initialized() {
      t.trace0("Initialized agent");
      // <initialization code>
   }

   // <other handlers>

 private:
   eos::tracer t;

};

int main(int argc, char ** argv) {
   eos::sdk sdk;
   example_agent ex(sdk);
   sdk.main_loop(argc, argv);
}
