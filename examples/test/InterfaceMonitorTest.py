#!/usr/bin/env pychooser
# Copyright (c) 2016 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

from __future__ import absolute_import, division, print_function
import EosSdkGenericTestLib
import six


class InterfaceMonitorTest(object):
   def __init__(self, test_lib, agent_name, sintfs, agent_binary_path, args=None):
      self.test_lib = test_lib
      self.agent_name = agent_name
      self.agent_binary_path = agent_binary_path
      self.args = args
      self.sintfs = [intf.name() for intf in sintfs]

   def find_connected_interface(self):
      # Return the name of an interface that is labeled as 'connected'.
      # also return 2 if the interface is a snake interface, meaning we expect
      # to receive two "on_oper_status" notifications. Otherwise 1 is returned.

      response = self.test_lib.run_cmds(["show interfaces status"])[0]
      for intf, status in six.iteritems( response[ "interfaceStatuses" ] ):
         if status["linkStatus"] == 'connected' and "Ma" not in intf:
            if intf in self.sintfs:
               return intf, 2
            else:
               return intf, 1
      assert False, "Could not find any connected interfaces"

   def check_intf_description(self, intf, expected_description):
      # Make sure the interface changed its description
      response = self.test_lib.run_cmds(["show interfaces status"])[0]
      desc = response["interfaceStatuses"][intf]["description"]
      assert desc == expected_description, "Wrong description: %s" % desc

   def run(self):
      with EosSdkGenericTestLib.AgentLib( self.test_lib, self.agent_name,
                                          self.agent_binary_path,
                                          args=self.args) as al:
         al.start_agent()
         al.wait_for_status("Total intf changes", "0")

         test_intf, changes = self.find_connected_interface()

         # Shut down an interface and make sure the agent notices
         self.test_lib.run_cmds(["enable", "configure", "interface %s" % test_intf,
                                 "shutdown"])
         if changes == 1:
            al.wait_for_status("Total intf changes", "1")
         else:
            al.wait_for_status("Total intf changes", "2")
         al.wait_for_status("Last change of " + test_intf, "down" )
         last_change_time = al.agent_data()['data']["Last change time of %s" %
                                                    test_intf]
         self.check_intf_description(test_intf,
                                     "Last status change at %s" % last_change_time)

         # Re-enable the interface!
         self.test_lib.run_cmds(["enable", "configure", "interface %s" % test_intf,
                                 "no shutdown"])
         if changes == 1:
            al.wait_for_status("Total intf changes", "2")
         else:
            al.wait_for_status("Total intf changes", "4")
         al.wait_for_status("Last change of " + test_intf, "up" )
         last_change_time2 = al.agent_data()['data']["Last change time of %s" %
                                                     test_intf]
         assert last_change_time != last_change_time2

if __name__ == "__main__":
   # The EosSdk extension and the agent executable need to be installed
   # on the device before running this test.
   generic_test_lib = EosSdkGenericTestLib.TestLib("localhost", "admin", "")
   intf_monitor_test = InterfaceMonitorTest(generic_test_lib,
                                            "InterfaceMonitorTest",
                                            "/mnt/flash/InterfaceMonitor.py")
   intf_monitor_test.run()
   print( "PASSED" )
