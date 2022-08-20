#!/usr/bin/env pychooser
# Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

"""A sample custom CLI.

To create a custom CLI, user will need to define their CLI plugin as following:

@EosSdkCli.CustomCli(myCliName)
def Plugin(sdk):
   global mySdk, ipRouteMgr
   mySdk = sdk
   ipRouteMgr = mySdk.get_ip_route_mgr()

Note a manager, such as ipRouteMgr, needs to be obtained in this function and then
used by the CLI implementation, as shown in 'class ShowDynamicIpRoutesCmd'.

User can pass in a name to sdk binding in this CLI plugin via the decorator argument.

After creating the CLI file, such as CustomIpRouteCli.py, it needs to be installed at
/usr/lib/python2.7/site-packages/CliPlugin/ on switch, then user will need to issue
"killall FastCli" to reload all CLIs so the new CLI will take effect.
"""

from __future__ import absolute_import, division, print_function
import BasicCli
import CliMatcher
import eossdk
import EosSdkCli
import ShowCommand

ipRouteMgr = None
mySdk = None


class ShowDynamicIpRoutesCmd(ShowCommand.ShowCliCommandClass):
   syntax = """show dynamic-ip-routes [ tag TAG_NUM ]"""
   data = {
      'dynamic-ip-routes': 'Routes programmed by EOS SDK agents',
      'tag': 'Show only routes with this tag',
      'TAG_NUM': CliMatcher.IntegerMatcher(
          0, 100,
          helpdesc='The dynamic tag for which the routes will be shown'),
   }

   def handler(self, mode, args):
      tag = args.get('TAG_NUM', 0)
      numRoutes = 0
      totalRoutes = 0
      lock = eossdk.SdkScopedLock()
      routeFmt = "{} [preference {}, tag {}] has nexthops:"
      for route in ipRouteMgr.ip_route_iter():
         totalRoutes += 1
         if not tag or route.tag == tag:
            numRoutes += 1
            # Print the route line
            print(routeFmt.format(route.key().prefix().to_string(),
                                  route.key().preference(), route.tag()))

            # And now print all the vias for this route
            seen_vias = False
            for via in ipRouteMgr.ip_route_via_iter(route.key()):
               seen_vias = True
               # Only print out the relevant via information
               if via.hop() != eossdk.IpAddr():
                  output = "Nexthop " + via.hop().to_string()
               elif via.intf() != eossdk.IntfId():
                  if via.intf().is_null0():
                     output = "Drop route"
                  else:
                     output = "Interface " + via.intf.to_string
               elif via.nexthop_group():
                  output = "Nexthop group " + via.nexthop_group()
               else:
                  output = "Unknown via type"

               if via.mpls_label() != eossdk.MplsLabel():
                  output = " and push MPLS Label " + via.mpls_label().to_string()
               print("      -", output)

            if not seen_vias:
               print("      - no nexthops!")

      del lock

      # Print a nice footer
      print()
      print("Saw", numRoutes, "matching routes out of", totalRoutes, "total routes")
      print()

BasicCli.addShowCommandClass( ShowDynamicIpRoutesCmd )


@EosSdkCli.CustomCli("MyCustomIpRouteCli")
def Plugin(sdk):
   global mySdk, ipRouteMgr
   mySdk = sdk
   ipRouteMgr = mySdk.get_ip_route_mgr()
