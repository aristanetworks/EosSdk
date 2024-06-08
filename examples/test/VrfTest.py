#!/usr/bin/env python3
# Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

# pylint: disable=consider-using-f-string

import argparse
import socket

import EosSdkGenericTestLib

NORMAL_SOCKET_PORT = 50032
VRF_SOCKET_PORT = 50078

# Test the VrfTest agent.
#
# Note, the EosSdk extension needs to be installed already on switch before you
# run this test script.

VRF_YELLOW = 'vrfYellow'
VRF_BLUE = 'vrfBlue'


class VrfTest:
   def __init__(self, test_lib, switch_ip, intf, intf_ip,
                agent_name, agent_binary_path, args=None):
      self.switch_ip = switch_ip
      self.intf = intf
      self.intf_ip = intf_ip
      self.test_lib = test_lib
      self.agent_name = agent_name
      self.agent_binary_path = agent_binary_path
      self.args = args

   def run(self):
      with EosSdkGenericTestLib.AgentLib(
              self.test_lib, self.agent_name,
              self.agent_binary_path, self.args) as al:
         # First create the vrf
         self.test_lib.run_cmds( [ 'enable',
                                   'configure',
                                   'vrf instance %s' % VRF_YELLOW,
                                   'rd 11:12' ] )
         # Now add intf in the vrf
         self.test_lib.run_cmds( [ 'enable',
                                   'configure',
                                   'interface %s' % self.intf,
                                   'no switchport',
                                   'vrf %s' % VRF_YELLOW,
                                   'ip address %s/24' % self.intf_ip,
                                   'no shutdown' ] )

         al.start_agent()
         al.wait_for_status( "vrf_test", "ready" )
         print( "Agent %s started." % self.agent_name )

         al.agent_option_is( "socket_check_ready", "true" )
         al.wait_for_status( "socket_test", "started" )

         def testHandler():
            self.test_lib.run_cmds( [ 'enable',
                                      'configure',
                                      'vrf instance %s' % VRF_BLUE,
                                      'rd 21:22' ] )
            al.wait_for_status( "on_vrf_state0", "initializing" )
            al.wait_for_status( "on_vrf_state1", "active" )

            self.test_lib.run_cmds( [ 'enable',
                                      'configure',
                                      'no vrf instance %s' % VRF_BLUE ] )
            al.wait_for_status( "on_vrf_state2", "deleting" )
            al.wait_for_status( "on_vrf_state3", "deleted" )

         def testSocket( vrf=True ):
            if vrf:
               server_address = ( self.intf_ip, VRF_SOCKET_PORT )
            else:
               server_address = ( self.switch_ip, NORMAL_SOCKET_PORT )

            vrf_socket = socket.socket( socket.AF_INET, socket.SOCK_STREAM, 0 )

            vrf_socket.connect( server_address )
            try:
               vrf_socket.sendall( b"hello" )
               data = vrf_socket.recv( 1024 )
               assert data == b"how are you", "Unexpected return %s" % data
            finally:
               vrf_socket.close()

         testSocket( vrf=True )
         al.wait_for_status( "socket_test", "vrf socket test succeeded" )

         testSocket( vrf=False )
         al.wait_for_status( "socket_test", "normal socket test succeeded" )

         testHandler()

         al.stop_agent()
         al.remove_agent()

if __name__ == "__main__":
   # The EosSdk extension needs be installed already on switch,
   # and the agent executable VrfTest needs to be copied to /mnt/flash
   # on the device before running this test.
   # also the 'intf' is an interface on the switch and it needs to be accessible
   # from where you are running this script, we are openning a socket from this
   # script to the agent.
   #
   # ./VrfTest.py 172.24.17.12 Et2 10.0.0.9
   #
   parser = argparse.ArgumentParser()
   parser.add_argument( "switch_ip", help="the ip of the switch" )
   parser.add_argument( "intf",
                        help="the name of the interface that will be put in VRF" )
   parser.add_argument( "intf_ip", help="the ip of the interface" )
   parser.add_argument( "username", default='admin',
                        help="the switch credential, username", nargs='?' )
   parser.add_argument( "password", default='',
                        help="the switch credential, password", nargs='?' )
   args_ = parser.parse_args()
   switch_ip_ = args_.switch_ip
   switch_intf_ = args_.intf
   switch_intf_ip_ = args_.intf_ip
   user_ = args_.username
   pw_ = args_.password
   generic_test_lib = EosSdkGenericTestLib.TestLib( switch_ip_, user_, pw_ )
   vrf_test = VrfTest( generic_test_lib, switch_ip_,
                       switch_intf_, switch_intf_ip_,
                       "VrfTest", "/mnt/flash/VrfTest" )
   vrf_test.run()
   print( "VrfTest passed." )
