// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <iostream>

#include <eos/event_loop.h>
#include <eos/ip.h>
#include <eos/ip_route.h>
#include <eos/mpls.h>
#include <eos/nexthop_group.h>
#include <eos/sdk.h>
#include <eos/tracing.h>

#include <eos/types/ip_route.h>
#include <eos/types/mpls.h>

// This is a simple script (not an agent) that creates (or deletes)
// `NUM_ROUTES` IPv6 routes, each pointing to a unique nexthop
// group. These nexthop groups tunnel traffic into an MPLS tunnel that
// pushes a single label onto the packet before forwarding it to some
// preset destination IP. This script demonstrates how to use the
// event_loop infrastructure, as well as basic NHG/IP route
// programming.

// Build using:
//    g++ -std=gnu++0x -leos examples/NexthopGroupModifierScript.cpp -o NhgScript
// Usage: "./NhgScript add" or "./NhgScript delete"

// Number of routes and NHG to add:
#define NUM_ROUTES 20

int main(int argc, char** argv) {
   if (argc < 2 || (strcmp(argv[1], "add") != 0 &&
                    strcmp(argv[1], "delete") != 0)) {
      std::cout << "Please specify either 'add' or 'delete'." << std::endl;
      return 1;
   }

   eos::sdk sdk;
   eos::ip_route_mgr * ipMgr = sdk.get_ip_route_mgr();
   eos::nexthop_group_mgr * nhgMgr = sdk.get_nexthop_group_mgr();
   eos::event_loop * loop = sdk.get_event_loop();
   loop->wait_for_initialized();
   // Now we're initialized and our managers can be used!

   bool should_add = (strcmp(argv[1], "add") == 0);

   std::cout << "Starting the test, " << 
      (should_add ? "adding" : "deleting") << " routes" << std::endl;

   std::string nhgNamePfx = "sdk-nhg-";
   int size = 8;
   int labelstart = 1000000;
   std::string name;
   std::string nh[4] = {
      "2000:10:13::1",
      "2000:10:13::3",
      "2000:10:13::5",
      "2000:10:13::7",
   };
   size_t nhlen = sizeof(nh)/sizeof(0);
   std::string v6start = "2500::";

   char v6pfx[128];
   for (int nhgn = 1; nhgn <= NUM_ROUTES; nhgn++) {
      // Create a NHG with `size` entries, equally split across each
      // `nh` entry. All entries are tunneled into an MPLS tunnel.
      int rn = nhgn - 1;
      int label = labelstart + nhgn;
      name = nhgNamePfx;
      name += std::to_string(nhgn);

      if (should_add) {
         eos::nexthop_group_t nhg(name, eos::NEXTHOP_GROUP_MPLS);
         eos::nexthop_group_mpls_action_t mplsActionA(eos::MPLS_ACTION_PUSH,
                                                      {eos::mpls_label_t(label)});
         for (int i = 0; i < size; i++) {
            eos::nexthop_group_entry_t nhe(eos::ip_addr_t(nh[i % nhlen]));
            nhe.mpls_action_is(mplsActionA);
            nhg.nexthop_set(i, nhe);
         }

         std::cout << "Creating nhg " << name.c_str() << " using label "
                   << label << std::endl;
         nhgMgr->nexthop_group_set(nhg);
      } else {
         std::cout << "Removing nhg " << name.c_str() << std::endl;
         nhgMgr->nexthop_group_del(name);
      }
 
      // Now create the IPv6 route key.
      int v6len = sprintf(v6pfx, "%s%04x", v6start.c_str(), rn);
      assert(v6len > 0 && "sprintf failed");
      std::string v6str = v6pfx;
      eos::ip_route_key_t ip_route_key(
            eos::ip_prefix_t(eos::ip_addr_t(v6str), 128));

      if (should_add) {
         eos::ip_route_t ip_route(ip_route_key);
         eos::ip_route_via_t ip_route_via(ip_route_key);
         ip_route_via.nexthop_group_is(name);

         std::cout << "Creating route " << v6str << std::endl;
         ipMgr->ip_route_set(ip_route);
         ipMgr->ip_route_via_set(ip_route_via);
      } else {
         ipMgr->ip_route_del(ip_route_key);
      }
   }

   loop->flush();
   return 0;
}
