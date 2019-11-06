#!/usr/bin/python3
# Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

from __future__ import absolute_import, division, print_function
import eossdk
import sys

# This is the python version of the IpRouteBulkUpdater.cpp program.
# This agent configures and deletes ip routes in 3 phases.
# Phase 0: Clear routes
# Phase 1: Insert initial set of routes
# Phase 2: Re-insert "initial routes" and more routes
# The agent goes through these phases independently with hardcoded pauses between
# them and updates its status once each phase is done.
#
# The agent will run the above phases for the following combinations:
# ipv4, old api
# ipv6, old api
# ipv4, new api
# ipv6, new api
#
# NOTE
# old api: Routes are configured using API
#          'void ip_route_set(ip_route_t const &)'
# new api: Routes are configured using API
#          'void ip_route_set(ip_route_t const &, ip_route_action_t expected_type)'
#
# The transition from ipv4 to ipv6 and old to new api phase happens when the agent
# receives the various "cleanup" options "cleanup<v4|v6><old|new-api>" with value
# "done".
# "cleanup" options "cleanup<v4|v6><old|new-api>" with value "start" will clear
# the routes.
#
# In addition to the above, the agent also provides options "insert_vrf_routes" and
# "delete_vrf_routes" to configure and delete ipv4|ipv6 routes in vrf.


INITIAL_ROUTES = 28000
TOTAL_ROUTES = 200000


class RouteUpdater(eossdk.AgentHandler, eossdk.TimeoutHandler):
   def __init__(self, sdk):
      self.agentMgr = sdk.get_agent_mgr()
      self.timeoutMgr = sdk.get_timeout_mgr()
      eossdk.AgentHandler.__init__(self, self.agentMgr)
      eossdk.TimeoutHandler.__init__(self, self.timeoutMgr)

      self.tracer = eossdk.Tracer("RouteUpdaterPythonAgent")
      self.ipMgr = sdk.get_ip_route_mgr()
      self.nhgMgr = sdk.get_nexthop_group_mgr()
      self.phase = 0
      self.isV6Phase = False
      self.isNewApi = False
      self.tag = 42
      self.ipMgr.tag_is(self.tag)

      self.tracer.trace0("Constructed agent")

   def clean_status(self):
      self.agentMgr.status_del("clear_routes")
      self.agentMgr.status_del("insert_initial_routes")
      self.agentMgr.status_del("re_insert_routes")

      self.agentMgr.status_del("clear_routes_v6")
      self.agentMgr.status_del("insert_initial_routes_v6")
      self.agentMgr.status_del("re_insert_routes_v6")

      self.agentMgr.status_del("clear_routes_new_api")
      self.agentMgr.status_del("insert_initial_routes_new_api")
      self.agentMgr.status_del("re_insert_routes_new_api")

      self.agentMgr.status_del("clear_routes_v6_new_api")
      self.agentMgr.status_del("insert_initial_routes_v6_new_api")
      self.agentMgr.status_del("re_insert_routes_v6_new_api")

   def on_initialized(self):
      self.tracer.trace0("Initialized agent")
      self.clean_status()
      self.set_nexthop_group()
      self.handle_phase()

   def on_timeout(self):
      self.tracer.trace0("Got a timer event.")
      self.handle_phase()

   def on_agent_option(self, name, value):
      self.tracer.trace3("on_agent_option: key={}, value={}".format(name, value))
      if name == "insert_vrf_routes":
         if value == "ip":
            self.insert_routes_vrf(0, INITIAL_ROUTES, "blue")
         elif value == "ipv6":
            self.insert_v6_routes_vrf(0, INITIAL_ROUTES, "blue")

      elif name == "delete_vrf_routes":
         if value == "ip":
            self.delete_routes_vrf(0, INITIAL_ROUTES, "blue")
         elif value == "ipv6":
            self.delete_v6_routes_vrf(0, INITIAL_ROUTES, "blue")

      elif ((name == "cleanup" or name == "cleanup_v6" or
             name == "cleanup_new_api" or
             name == "cleanup_v6_new_api") and value == "start"):
         self.clear_routes()

      elif ((name == "cleanup" or
             name == "cleanup_new_api") and value == "done"):
         self.isV6Phase = True
         self.phase = 0
         self.timeout_time_is(eossdk.now() + 5)

      elif name == "cleanup_v6" and value == "done":
         self.isV6Phase = False
         self.isNewApi = True
         self.phase = 0
         self.timeout_time_is(eossdk.now() + 5)

   def handle_phase(self):
      self.tracer.trace0("Starting phase {}".format(self.phase))

      if self.phase == 0:
         self.clear_routes()
         self.timeout_time_is(eossdk.now() + 20)
      elif self.phase == 1:
         self.insert_initial_routes()
         self.timeout_time_is(eossdk.now() + 65)
      elif self.phase == 2:
         self.re_insert_routes()

      self.tracer.trace0("Finished phase {}".format(self.phase))
      self.phase += 1

   def clear_routes(self):
      self.tracer.trace1("Clearing all routes")
      self.ipMgr.resync_init()
      self.tracer.trace1("  clearing...")
      self.ipMgr.resync_complete()
      self.tracer.trace1("  Finished clearing")
      if not self.isV6Phase:
         if not self.isNewApi:
            self.agentMgr.status_set("clear_routes", "done")
         else:
            self.agentMgr.status_set("clear_routes_new_api", "done")
      else:
         if not self.isNewApi:
            self.agentMgr.status_set("clear_routes_v6", "done")
         else:
            self.agentMgr.status_set("clear_routes_v6_new_api", "done")

   def insert_initial_routes(self):
      self.tracer.trace1("Programming addresses")
      if not self.isV6Phase:
         if not self.isNewApi:
            self.insert_routes(0, INITIAL_ROUTES, False)
            self.agentMgr.status_set("insert_initial_routes", "done")
         else:
            self.insert_routes(0, INITIAL_ROUTES, True)
            self.agentMgr.status_set("insert_initial_routes_new_api", "done")
      else:
         if not self.isNewApi:
            self.insert_v6_routes(0, INITIAL_ROUTES, False)
            self.agentMgr.status_set("insert_initial_routes_v6", "done")
         else:
            self.insert_v6_routes(0, INITIAL_ROUTES, True)
            self.agentMgr.status_set("insert_initial_routes_v6_new_api", "done")

      self.tracer.trace0("Finished!")

   def re_insert_routes(self):
      self.tracer.trace1("Re-Programming addresses")
      self.ipMgr.resync_init()
      # Use insert_routes(INITIAL_ROUTES, TOTAL_ROUTES); if you only want to
      # add new routes and not the initial routes.
      if not self.isV6Phase:
         if not self.isNewApi:
            self.insert_routes(0, TOTAL_ROUTES, False)
         else:
            self.insert_routes(0, TOTAL_ROUTES, True)
      else:
         if not self.isNewApi:
            self.insert_v6_routes(0, TOTAL_ROUTES, False)
         else:
            self.insert_v6_routes(0, TOTAL_ROUTES, True)

      self.tracer.trace1("  finishing resync...")
      self.ipMgr.resync_complete()
      self.tracer.trace1("  resync complete")
      self.tracer.trace0("Finished!")
      if not self.isV6Phase:
         if not self.isNewApi:
            self.agentMgr.status_set("re_insert_routes", "done")
         else:
            self.agentMgr.status_set("re_insert_routes_new_api", "done")
      else:
         if not self.isNewApi:
            self.agentMgr.status_set("re_insert_routes_v6", "done")
         else:
            self.agentMgr.status_set("re_insert_routes_v6_new_api", "done")

   def insert_routes(self, start, end, newApi):
      self.tracer.trace1("Starting to insert {} routes, \
                          starting at route# {}".format(end, start))
      for i in range(start, end):
         first = 200 + (i / 65536)
         second = (i / 256) % 256
         third = i % 256
         addrStr = "%d.%d.%d.0" % (first, second, third)
         prefix = eossdk.IpPrefix(eossdk.IpAddr(addrStr), 24)
         if i % 2550 == 0:
            self.tracer.trace3("Adding prefix " + prefix.to_string())
         rkey = eossdk.IpRouteKey(prefix)
         route = eossdk.IpRoute(rkey)
         route.tag_is(self.tag)
         via = eossdk.IpRouteVia(rkey)
         via.nexthop_group_is("mpls_nhg")
         if not newApi:
            self.ipMgr.ip_route_set(route)
         else:
            self.ipMgr.ip_route_set(route, eossdk.IP_ROUTE_ACTION_NEXTHOP_GROUP)

         self.ipMgr.ip_route_via_set(via)

      self.tracer.trace1("Finished inserting {} routes, \
                          starting at route# {}".format(end, start))

   def insert_v6_routes(self, start, end, newApi):
      self.tracer.trace1("Starting to insert {} v6_routes, \
                          starting at route# {}".format(end, start))
      for i in range(start, end):
         first = (i / 65536) % 65536
         second = i % 65536
         addrStr = "%04x:%04x::" % (first, second)
         ip = eossdk.IpAddr(addrStr)
         prefix6 = eossdk.IpPrefix(ip, 64)
         rkey6 = eossdk.IpRouteKey(prefix6)
         route6 = eossdk.IpRoute(rkey6)
         route6.tag_is(self.tag)
         via6 = eossdk.IpRouteVia(rkey6)
         via6.nexthop_group_is("mpls_nhg")
         if not newApi:
            self.ipMgr.ip_route_set(route6)
         else:
            self.ipMgr.ip_route_set(route6, eossdk.IP_ROUTE_ACTION_NEXTHOP_GROUP)

         self.ipMgr.ip_route_via_set(via6)

      self.tracer.trace1("Finished inserting {} routes, \
                          starting at route# {}".format(end, start))

   def set_nexthop_group(self):
      self.tracer.trace1("Setting nexthop group")
      # Create a nexthop-group mpls_nhg:
      #     nexthop-group mpls_nhg type mpls
      #        size 256
      #        entry 0 push label-stack 16 nexthop 10.0.0.8
      nhgName = "mpls_nhg"
      label = 16
      entry = 0
      addrStr = "10.0.0.8"
      nhg = eossdk.NexthopGroup(nhgName, eossdk.NEXTHOP_GROUP_MPLS)
      nhge = eossdk.NexthopGroupEntry(eossdk.IpAddr(addrStr))
      mplsAction = eossdk.NexthopGroupMplsAction(eossdk.MPLS_ACTION_PUSH,
                                                 (eossdk.MplsLabel(label),))
      nhge.mpls_action_is(mplsAction)
      nhg.nexthop_set(entry, nhge)
      self.nhgMgr.nexthop_group_set(nhg)

   def create_ip_route_key(self, i):
      first = 200 + (i / 65536)
      second = (i / 256) % 256
      third = i % 256
      addrStr = "%d.%d.%d.0" % (first, second, third)
      prefix = eossdk.IpPrefix(eossdk.IpAddr(addrStr), 24)
      if i % 2550 == 0:
         self.tracer.trace3("Adding prefix %s" % prefix.to_string())
      rkey = eossdk.IpRouteKey(prefix)
      return rkey

   def create_ip_v6_route_key(self, i):
      first = (i / 65536) % 65536
      second = i % 65536
      addrStr = "%04x:%04x::" % (first, second)
      ip = eossdk.IpAddr(addrStr)
      prefix6 = eossdk.IpPrefix(ip, 64)
      rkey6 = eossdk.IpRouteKey(prefix6)
      return rkey6

   def insert_routes_vrf(self, start, end, vrf):
      self.tracer.trace1("Insert {} routes into vrf {}, \
                          starting at route {}".format(end, vrf, start))
      for i in range(start, end):
         rkey = self.create_ip_route_key(i)
         route = eossdk.IpRoute(rkey)
         route.tag_is(self.tag)
         self.ipMgr.ip_route_set(route, vrf)

      self.tracer.trace1("Finished inserting {} routes into vrf {}, \
                          starting at route {}".format(end, vrf, start))

   def delete_routes_vrf(self, start, end, vrf):
      self.tracer.trace1("Starting to delete {} routes from vrf {}, \
                          starting at route {}".format(end, vrf, start))
      for i in range(start, end):
         rkey = self.create_ip_route_key(i)
         self.ipMgr.ip_route_del(rkey, vrf)

      self.tracer.trace1("Finished deleting {} routes into vrf {}, \
                          starting at route {}".format(end, vrf, start))

   def insert_v6_routes_vrf(self, start, end, vrf):
      self.tracer.trace1("Starting to insert {} v6_routes into vrf {}, \
                          starting at route {}".format(end, vrf, start))
      for i in range(start, end):
         rkey6 = self.create_ip_v6_route_key(i)
         route6 = eossdk.IpRoute(rkey6)
         route6.tag_is(self.tag)
         self.ipMgr.ip_route_set(route6, vrf)

      self.tracer.trace1("Finished inserting {} routes into vrf {}, \
                          starting at route {}".format(end, vrf, start))

   def delete_v6_routes_vrf(self, start, end, vrf):
      self.tracer.trace1("Starting to delete {} routes from vrf {}, \
                          starting at route {}".format(end, vrf, start))
      for i in range(start, end):
         rkey6 = self.create_ip_v6_route_key(i)
         self.ipMgr.ip_route_del(rkey6, vrf)

      self.tracer.trace1("Finished deleting {} routes into vrf {}, \
                          starting at route {}".format(end, vrf, start))

if __name__ == "__main__":
   sdk_ = eossdk.Sdk()
   # Assign the agent instance to a variable so it remains in scope and
   # is not deleted:
   _ = RouteUpdater(sdk_)
   sdk_.main_loop(sys.argv)
