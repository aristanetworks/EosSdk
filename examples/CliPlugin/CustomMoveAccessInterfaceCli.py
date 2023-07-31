#!/usr/bin/env python3
# Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

"""A sample custom CLI to change the default vlan of an interface in access mode.

To create a custom CLI, user will need to define their CLI plugin as following:

@EosSdkCli.CustomCli(myCliName)
def Plugin(sdk):
   global mySdk, ethIntfMgr
   mySdk = sdk
   ethIntfMgr = mySdk.get_eth_intf_mgr()

Note a manager, such as ethIntfMgr, needs to be obtained in this function and then
used by the CLI implementation, as shown in 'class MoveAccessInterfaceCmd'.

User can pass in a name to sdk binding in this CLI plugin via the decorator argument.

After creating the CLI file, such as CustomMoveAccessInterfaceCli.py, it needs to be
installed at /usr/lib/python2.7/site-packages/CliPlugin/ on switch, then user will
need to issue "killall FastCli" to reload all CLIs so the new CLI will take effect.
"""

import BasicCli
import CliMatcher
import CliCommand
import eossdk
import EosSdkCli

ethIntfMgr = None
mySdk = None


class MoveAccessInterfaceCmd(CliCommand.CliCommandClass):
   syntax = 'move access interfaces SRC_VLAN DST_VLAN'
   data = {
      'move': 'Move command',
      'access': 'Access interface',
      'interfaces': 'Interface',
      'SRC_VLAN': CliMatcher.IntegerMatcher(
          1, 4094,
          helpdesc='The original default VLAN ID to be moved'),
      'DST_VLAN': CliMatcher.IntegerMatcher(
          1, 4094,
          helpdesc='The new default VLAN ID to be moved to'),
   }

   @staticmethod
   def handler(mode, args):
      original_vlan_id = args['SRC_VLAN']
      new_vlan_id = args['DST_VLAN']
      lock = eossdk.SdkScopedLock()
      for intf in ethIntfMgr.eth_intf_iter():
         if (ethIntfMgr.switchport_mode(intf) == eossdk.SWITCHPORT_MODE_ACCESS and
                 ethIntfMgr.default_vlan(intf) == original_vlan_id):
            ethIntfMgr.default_vlan_is(intf, new_vlan_id)
            print("moved interface %s default VLAN from %s to %s." %
                  (intf.to_string(), original_vlan_id, new_vlan_id))
            return
      print("no default VLAN ID moved.")
      print()
      del lock

BasicCli.GlobalConfigMode.addCommandClass( MoveAccessInterfaceCmd )


@EosSdkCli.CustomCli("MyCustomMoveAccessInterfaceCli")
def Plugin(sdk):
   global mySdk, ethIntfMgr
   mySdk = sdk
   ethIntfMgr = mySdk.get_eth_intf_mgr()
