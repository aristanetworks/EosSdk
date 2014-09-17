// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/sdk.h>
#include <eos/tracing.h>

// This simple agent says "hi" to a user when the user configures his
// or her name, and demonstrates how to use the various components of
// the SDK. To run this agent, first build this agent and copy the
// resulting binary to switch. Then, from the CLI, run:

//    switch# configure
//    switch(conf)# daemon HelloAgent
//    switch(conf-daemon-HelloAgent)# exec /path/to/HelloWorldBinary
//    switch(conf-daemon-HelloAgent)# no shutdown

// At this point, you can run 'show daemon HelloAgent' and observe the
// agent's operational status (which will transition from
// 'initializing' to 'running'), along with the custom status message
// it sets: 'greeting: Welcome, what is your name?'

// You can now tell the agent your name:
//    switch(conf-daemon-HelloAgent)# option name value Bruce Wayne

// After setting the name option, running the 'show daemon' command
// again will display the updated status:
//   'greeting - Hello Bruce Wayne!'

// Although a trivial example, this agent helps demonstrate some of
// the key properties of writing EOS SDK agents. First, all activities
// are asynchronous and triggered from the event loop. At no point
// does this agent poll or block on an activity - instead we implement
// the callbacks provided by agent_handler to be notified when we are
// initialized and when options are updated.

// Secondly, this agent illustrates the uses of a mgr
// class. <module>_mgr's are used to get and set state from
// Sysdb. Here we read state from Sysdb in order to get the current
// option, and change state in Sysdb so we can update our status. This
// change is propagated to other Agents that have requested our status
// as an input, which, in this case, are only the CLI and eAPI agents.

// Finally, this example illustrates an agent's lifecycle. Upon running
// the "no shutdown" from the CLI, this program's main function is
// executed. When the program calls sdk.main_loop, the agent begins
// its initialization, at which point it will synchronize with Sysdb
// and can handle any initial state. The agent then runs
// continuously: mostly idling in the underlying event loop, but
// occasionally reacting to system events (i.e. a user entering their
// name). When you run "shutdown" from the CLI, the agent can perform
// any necessary cleanup before being disabled.

// A python version of this program can be found at HelloWorld.py


class hello_world_agent : public eos::agent_handler {
 public:
   eos::tracer t;

   explicit hello_world_agent(eos::sdk & sdk)
         : eos::agent_handler(sdk.get_agent_mgr()),
           t("HelloWorldCppAgent") {
      t.trace0("Agent constructed");
   }

   void on_initialized() {
      t.trace0("Initialized");
      std::string name = get_agent_mgr()->agent_option("name");
      if(name.empty()) {
         // No name initially set.
         get_agent_mgr()->status_set("greeting", "Welcome! What is your name?");
      } else {
         // Handle initial state.
         on_agent_option("name", name);
      }
   }

   void on_agent_option(std::string const & option_name,
                        std::string const & value) {
      if(option_name == "name") {
         if(value.empty()) {
            // User deleted the 'name' option
            t.trace3("Name deleted");
            get_agent_mgr()->status_set("greeting", "Goodbye!");
         } else {
            // Now *this* is what social networking is all
            // about. Somebody set, or changed, the name option. Let's
            // do some salutations!
            t.trace3("Saying hi to %s", value.c_str());
            get_agent_mgr()->status_set("greeting", "Hello " + value + "!");
         }
      }
   }

   void on_agent_enabled(bool enabled) {
      if (!enabled) {
         t.trace0("Shutting down");
         get_agent_mgr()->status_set("greeting", "Adios!");
         get_agent_mgr()->agent_shutdown_complete_is(true);
      }
   }
};

int main(int argc, char ** argv) {
   eos::sdk sdk;
   hello_world_agent agent(sdk);
   sdk.main_loop(argc, argv);
}
