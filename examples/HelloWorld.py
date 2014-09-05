#!/usr/bin/env python
# Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import eossdk
import sys

# This is the python version of the HelloWorld.cpp program. See the
# explanation there, or a more detailed walkthrough at the GitHub wiki.

class HelloWorldAgent(eossdk.AgentHandler):
   def __init__(self, sdk):
      self.agentMgr = sdk.get_agent_mgr()
      self.tracer = eossdk.Tracer("HelloWorldPythonAgent")
      eossdk.AgentHandler.__init__(self, self.agentMgr)
      self.tracer.trace0("Python agent constructed")

   def on_initialized(self):
      self.tracer.trace0("Initialized")
      name = self.agentMgr.agent_option("name")
      if not name:
         # No name initially set
         self.agentMgr.status_set("greeting", "Welcome! What is your name?")
      else:
         # Handle the initial state
         self.on_agent_option("name", name)

   def on_agent_option(self, optionName, value):
      if optionName == "name":
         if not value:
            self.tracer.trace3("Name deleted")
            self.agentMgr.status_set("greeting", "Goodbye!")
         else:
            # Time for some social networking!
            self.tracer.trace3("Saying hi to %s", value)
            self.agentMgr.status_set("greeting", "Hello %s!" % value)
   
   def on_agent_enabled(self, enabled):
      if not enabled:
         self.tracer.trace0("Shutting down")
         self.agentMgr.status_set("greeting", "Adios!")
         self.agentMgr.agent_shutdown_complete_is(True)      

if __name__ == "__main__":
   sdk_ = eossdk.Sdk()
   # Assign the agent instance to a variable so it remains in scope and
   # is not deleted:
   _ = HelloWorldAgent(sdk_)
   sdk_.main_loop(sys.argv)
