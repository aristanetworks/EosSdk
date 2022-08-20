# Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

from __future__ import absolute_import, division, print_function
import EosSdkGenericTestLib


class FibTestAgent( object ):

   def __init__( self, test_lib, switch_ip, intf, intf_ip, intf2, intf2_ip,
                 agent_name, agent_binary_path, args=None ):
      self.test_lib = test_lib
      self.switch_ip = switch_ip
      self.intf = intf
      self.intf_ip = intf_ip
      self.intf2 = intf2
      self.intf2_ip = intf2_ip
      self.agent_name = agent_name
      self.agent_binary_path = agent_binary_path
      self.args = args

   def run(self):
      with EosSdkGenericTestLib.AgentLib(
         self.test_lib, self.agent_name,
         self.agent_binary_path, self.args) as al:
         # Common config for test cases. An interface needs to be configured
         # for these tests to run
         self.test_lib.run_cmds( [ 'enable',
                                   'configure',
                                   'interface %s' % self.intf,
                                   'no switchport',
                                   'ip address %s/24' % self.intf_ip,
                                   'arp 10.0.0.9 000.111.222 arpa' ] )
         al.start_agent()
         al.wait_for_status( "FibTestAgent", "true" )
         print( "Agent %s started." % self.agent_name )

         def delIpRoute( prefix, nh="", localPref="" ):
            # delete the ip route for the given prefix
            self.test_lib.run_cmds( [ 'enable',
                                      'configure',
                                      'no ip route %s %s %s' %
                                      ( prefix, nh, localPref ) ] )

         def addIpRoute( prefix, nh, localPref=1 ):
            # add a static route to the dut and ensure that is is associated
            # with a fec Id. Return the fecId for this route
            self.test_lib.run_cmds( [ 'enable',
                                      'configure',
                                      'ip route %s %s %d' % ( prefix, nh, localPref )
                                      ] )

         def getFecIdForPrefix( prefix, invalidFec='' ):
            fecId = invalidFec
            while fecId == '' or fecId == invalidFec:
               fecId = self.test_lib.run_cmds( [ 'enable',
                                                 'configure',
                                                 "show ip route %s fec | "
                                                 "awk -v RS=[0-9]+"
                                                 " '{print RT;exit}'" % prefix ],
                                               data_format='text')[ 2 ][ 'output' ]
               fecId = fecId.rstrip()
            return fecId

         def verifyFec( fecId, fecCounter='0', present=True ):
            if present:
               al.wait_for_status_exists( 'fib_fec_key_t(fec_id=%s)' % fecId )
            else:
               al.wait_for_status( 'fib_fec_key_t(fec_id=%s)' % fecId, 'deleted' )
            al.wait_for_status( 'fib_fec_key_t(fec_id=%s) fec_counter='
                                % fecId, fecCounter )

         def verifyRoute( prefix, fecId, rtCounter, localPref=1,
                          metric=0, present=True ):
            if present:
               al.wait_for_status( 'fib_route_key_t(prefix=%s)' % prefix,
                                   'fib_route_t(route_key=fib_route_key_t('
                                   'prefix=%s), preference=%d, metric=%s, '
                                   'route_type=ROUTE_TYPE_STATIC_CONFIG, fec_id=%s)'
                                   % ( prefix, localPref, metric, fecId ) )
            else:
               al.wait_for_status( 'fib_route_key_t(prefix=%s)' % prefix,
                                   'deleted' )
            al.wait_for_status( 'fib_route_key_t(prefix=%s) route_counter='
                                % prefix, rtCounter )

         ############################################################################
         # Test that on_route_set/delete notifications are generated when static
         # routes are added/deleted. Test that on_fec_set/del notifications are
         # generated when a new fec is added and when all routes have been deleted
         # from that fec
         ############################################################################
         addIpRoute( '2.2.2.0/24', '10.0.0.9' )
         fecId1 = getFecIdForPrefix( '2.2.2.0/24' )
         verifyRoute( '2.2.2.0/24', fecId1, '1' )
         verifyFec( fecId1, fecCounter='1' )
         addIpRoute( '3.3.3.0/24', '10.0.0.9' )
         fecId2 = getFecIdForPrefix( '3.3.3.0/24' )
         verifyRoute( '3.3.3.0/24', fecId2, '1' )
         verifyFec( fecId2, fecCounter='1' )
         assert fecId2 == fecId1
         delIpRoute( '2.2.2.0/24' )
         verifyRoute( '2.2.2.0/24', fecId1, '0', present=False )
         verifyFec( fecId1, fecCounter='1' )  # ensure fec has yet to be deleted
         delIpRoute( '3.3.3.0/24' )
         verifyRoute( '3.3.3.0/24', fecId1, '0', present=False )
         # Ensure that the FEC is deleted after both routes have been removed
         verifyFec( fecId1, present=False )

         ############################################################################
         # Test that a new on_route_set is generated when the local pref is changed
         ############################################################################
         addIpRoute( '2.2.2.0/24', '10.0.0.9', localPref=55 )
         fecId1 = getFecIdForPrefix( '2.2.2.0/24' )
         verifyRoute( '2.2.2.0/24', fecId1, '1', localPref=55 )
         verifyFec( fecId1, fecCounter='1' )

         addIpRoute( '2.2.2.0/24', '10.0.0.9' )
         fecId2 = getFecIdForPrefix( '2.2.2.0/24' )
         verifyRoute( '2.2.2.0/24', fecId2, '2' )
         verifyFec( fecId2, fecCounter='1' )
         assert fecId1 == fecId2

         delIpRoute( '2.2.2.0/24' )
         verifyFec( fecId1, present=False )
         verifyRoute( '2.2.2.0/24', fecId1, '0', present=False )

         ############################################################################
         # Test that we generate a new fec for an existing route. Helper functions
         # not applicable to this more complicated test case
         ############################################################################
         self.test_lib.run_cmds( [ 'enable',
                                   'configure',
                                   'interface %s' % self.intf2,
                                   'no switchport',
                                   'ip address 4.4.4.4/24',
                                   'arp 4.4.4.5 000.444.444 arpa' ] )

         addIpRoute( '2.2.2.0/24', '10.0.0.9', localPref=10 )
         fecId1 = getFecIdForPrefix( '2.2.2.0/24' )
         verifyRoute( '2.2.2.0/24', fecId1, '1', localPref=10 )
         verifyFec( fecId1, fecCounter='1' )

         # test for new recursive routes
         addIpRoute( '2.2.2.0/24', '4.4.4.5', localPref=2 )
         fecId2 = getFecIdForPrefix( '2.2.2.0/24', invalidFec=fecId1 )
         # check that the route has changed
         verifyRoute( '2.2.2.0/24', fecId2, '2', localPref=2 )

         addIpRoute( '3.3.3.0/24', '2.2.2.2' )
         # check that the new route points to the new fec
         getFecIdForPrefix( '3.3.3.0/24' )
         verifyRoute( '3.3.3.0/24', fecId2, '1' )

         # test that the deletion of the lower preference route results in
         # the fec + route changing for 2.2.2.0/24 and the fec for 3.3.3.0/24
         delIpRoute('2.2.2.0/24', '4.4.4.5', '2')
         verifyRoute( '2.2.2.0/24', fecId1, '3', localPref=10 )
         verifyRoute( '3.3.3.0/24', fecId1, '2' )

         # delete the route 2.2.2.0/24 and ensure that 3.3.3.0/24 is del as well
         delIpRoute( '2.2.2.0/24' )
         verifyRoute( '2.2.2.0/24', fecId1, '0', present=False )
         # deleting 2.2.2.0/24 causes 3.3.3.0/24 to get deleted
         verifyRoute( '3.3.3.0/24', fecId1, '0', present=False )
         # with all routes deleted the fec goes away
         verifyFec( fecId1, present=False )

         al.stop_agent()
         al.remove_agent()
         print( "Agent %s stopped and removed." % self.agent_name )
