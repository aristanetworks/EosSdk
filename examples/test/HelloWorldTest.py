#!/usr/bin/env pychooser
# Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

from __future__ import absolute_import, division, print_function
import argparse
import EosSdkGenericTestLib
from EosSdkGenericTestLib import AgentLib

# Test the HelloWorld tutorial agent. Can run against both the HelloWorld.py and
# HelloWorld.cpp agent sources.
#
# Note, the EosSdk extension needs to be installed already on switch before you
# run this test script.


class HelloWorldTest(object):
   def __init__(self, test_lib, agent_name, agent_binary_path, args=None):
      self.test_lib = test_lib
      self.agent_name = agent_name
      self.agent_binary_path = agent_binary_path
      self.args = args

   def run(self):
      with AgentLib(self.test_lib, self.agent_name,
                    self.agent_binary_path, args=self.args) as al:
         al.start_agent()
         al.wait_for(al.pid, "agent pid")
         print( "Agent PID is %s" % al.pid() )

         al.wait_for_status("greeting",
                            "Welcome! What is your name?")
         print( "Agent %s started." % self.agent_name )

         al.agent_option_is("name", "Robert Metcalfe")
         al.wait_for_status("greeting",
                            "Hello Robert Metcalfe!")
         print( "Greeted Robert Metcalfe." )

         al.agent_option_is("name", "Tim Berners-Lee")
         al.wait_for_status("greeting",
                            "Hello Tim Berners-Lee!")
         print( "Greeted Tim Berners-Lee." )

         al.agent_option_del("name")
         al.wait_for_status("greeting", "Goodbye!")
         print( "Removed name." )

         al.stop_agent()
         al.wait_for_status("greeting", "Adios!")
         print( "Stopped agent %s." % self.agent_name )
         al.remove_agent()

if __name__ == "__main__":
   # The EosSdk extension and the agent executable need to be installed
   # on the device before running this test.
   # Usage: ./HelloWorldTest.py switch_ip [username password]

   parser = argparse.ArgumentParser()
   parser.add_argument("switch_ip", help="the ip of the switch")
   parser.add_argument("username", default='admin',
                       help="the switch credential, username", nargs='?')
   parser.add_argument("password", default='',
                       help="the switch credential, password", nargs='?')
   args_ = parser.parse_args()
   switch_ip_ = args_.switch_ip
   user_ = args_.username
   pw_ = args_.password

   generic_test_lib = EosSdkGenericTestLib.TestLib(switch_ip_, user_, pw_)
   hello_world_test = HelloWorldTest(generic_test_lib,
                                     "HelloWorldTest",
                                     "/mnt/flash/HelloWorld.py")
   hello_world_test.run()
