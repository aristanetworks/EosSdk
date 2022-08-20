# Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

from __future__ import absolute_import, division, print_function
import argparse
import EosSdkGenericTestLib
from EosSdkGenericTestLib import AgentLib

# Test the HardwareTableTest agent.
# Note, the EosSdk extension needs to be installed already on switch before you
# run this test script.


class HardwareTableTest(object):
   def __init__(self, test_lib, agent_name, agent_binary_path, args=None):
      self.test_lib = test_lib
      self.agent_name = agent_name
      self.agent_binary_path = agent_binary_path
      self.args = args

   def run(self):

      # Enable ip routing
      self.test_lib.run_cmds( [ 'enable',
                                'configure',
                                'ip routing' ] )

      with AgentLib(self.test_lib, self.agent_name,
                    self.agent_binary_path, args=self.args) as al:
         # Start agent
         al.start_agent()
         al.wait_for_status( "hardware_table_test", "initialized" )
         print( "Agent %s started." % self.agent_name )

         # Test iterator: get total number of table keys
         al.agent_option_is( "test_iterator", "count" )
         al.wait_for_status_exists( "number_of_keys" )
         print( "Iterated over %s table keys."
                % al.agent_data()[ "data" ][ "number_of_keys" ] )

         # Set nexthop group
         al.agent_option_is( "nexthop_group", "set" )
         al.wait_for_status( "set_nexthop_group", "done" )

         # Insert 10 ip routes
         al.agent_option_is( "insert_routes", "10" )
         al.wait_for_status( "insert_routes", "done" )

         # Get current number of used entries in hardware capacity table
         table_key = "Routing-RouteBank4-"
         al.wait_for_status_exists( table_key )
         initial_percentage = int( al.agent_data()[ "data" ][ table_key ] )

         # Keep inserting routes until percentage of used entries increases by 10%
         used_percentage = initial_percentage
         while used_percentage < initial_percentage + 10:
            al.agent_option_del("insert_routes")
            al.agent_option_is("insert_routes", "100")
            used_percentage = int( al.agent_data()[ "data" ][ table_key ] )

         # Clear ip routes
         al.agent_option_is( "clear_routes", "all" )
         al.wait_for_status( "clear_routes", "done" )

         # Delete nexthop group
         al.agent_option_is( "nexthop_group", "del" )
         al.wait_for_status( "del_nexthop_group", "done" )

         # Stop and remove agent
         al.stop_agent()
         al.remove_agent()
         print( "Agent %s stopped and removed." % self.agent_name )

if __name__ == "__main__":
   # The EosSdk extension needs be installed already on switch,
   # and the agent executable HardwareTableTest needs to be copied to
   # /mnt/flash on the device before running this test.
   # Usage: ./HardwareTableTest.py switch_ip [username password]

   parser = argparse.ArgumentParser()
   parser.add_argument( "switch_ip", help="the ip of the switch" )
   parser.add_argument( "username", default='admin',
                        help="the switch credential, username", nargs='?' )
   parser.add_argument( "password", default='',
                        help="the switch credential, password", nargs='?' )
   args_ = parser.parse_args()
   switch_ip_ = args_.switch_ip
   user_ = args_.username
   pw_ = args_.password

   generic_test_lib = EosSdkGenericTestLib.TestLib( switch_ip_, user_, pw_ )
   hardware_table_test = HardwareTableTest( generic_test_lib,
                                            "HardwareTableTest",
                                            "/mnt/flash/HardwareTableTest" )
   hardware_table_test.run()
   print( "HardwareTableTest passed." )
