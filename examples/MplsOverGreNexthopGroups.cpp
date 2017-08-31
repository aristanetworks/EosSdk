// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/ip.h>
#include <eos/ip_route.h>
#include <eos/mpls.h>
#include <eos/nexthop_group.h>
#include <eos/sdk.h>
#include <eos/tracing.h>

// This is a Sample Agent code which demonstrates the following:
// 1) Create a nexthop group of type "Mpls over Gre".
// 2) Configure the source interface for the nexthop group.
// 3) Set nexthop group entries for the nexthop group with
//    tunnel destination id.
// 4) Create Mpls actions and set them for the nexthop group entries.
// 5) Create a route which point to the nexthop group.
// 6) Create an option where the route via is changed to a 
//    different nexthop group when a "use_backup" option is selected.
//
// Following are the steps to build and run the sample agent.
//
// Make the agent using a 32-bit linux build environment:
//    bash# g++ -leos -std=gnu++0x examples/MplsOverGreNexthopGroups.cpp 
//                                           -o MplsOverGreNexthopGroups
// Now you can transfer the binary to flash: on an EOS instance with
// EosSdk.i686.rpm installed and run the agent from bash:
//    bash# TRACE=EosSdk* /mnt/flash/MplsOverGreNexthopGroups
// or from the CLI
// (conf)#daemon MplsOverGreNexthopGroups
// (config-daemon-MplsOverGreNexthopGroups)#exec /mnt/flash/MplsOverGreNexthopGroups
// (config-daemon-MplsOverGreNexthopGroups)#no shutdown
// 
// The user can make the route to point to the backup nexthop group as follows.
// (config-daemon-MplsOverGreNexthopGroups)#option action value use_backup
// The user can make the route to point back to the primary nexthop group as follows 
// (config-daemon-MplsOverGreNexthopGroups)#option action value use_primary
//
// Steps: Prior to running the example agent.
// 1) Enable "ip routing"
// 2) Configure the Ethernet interfaces used for mplsOverGre tunnels (Ethenet3 and
//    Ethernet4 in the example given below).
// 3) Resolve the arps (or add static arp) entries for the tunnel-destination ip
//    addresses.
//
// Some useful logs captured:
// example configs:
//daemon MplsOverGreNexthopGroups
//   exec /mnt/flash/MplsOverGreNexthopGroups
//   option action value use_primary
//   no shutdown
//   
//#show running-config interfaces Ethernet 3
//interface Ethernet3
//   speed forced 10000full
//   no switchport
//   ip address 10.0.0.1/24
//#show running-config interfaces Ethernet 4
//interface Ethernet4
//   speed forced 10000full
//   no switchport
//   ip address 20.0.0.1/24
//
// After Initialization:
//#show nexthop-group
//MplsOverGreNhg1
//  Id         2
//  Type       mplsOverGre
//  Size       2
//  Ttl        64
//  Source Ip  10.0.0.1
//  Entries (left most label is the top of the stack)
//    0  push label-stack 30   tunnel-destination 10.0.0.33
//         Tunnel destination directly connected, Ethernet3
//         00:33:00:33:00:33, Ethernet3
//    1  push label-stack 40   tunnel-destination 10.0.0.44
//         Tunnel destination directly connected, Ethernet3
//         00:44:00:44:00:44, Ethernet3
//
//MplsOverGreNhg2
//  Unprogrammed nexthop group
//  Id         3
//  Type       mplsOverGre
//  Size       2
//  Ttl        64
//  Source Ip  20.0.0.1
//
// After switching the route to use the backup nexthop group:
//#show nexthop-group
//MplsOverGreNhg1
//  Unprogrammed nexthop group
//  Id         2
//  Type       mplsOverGre
//  Size       2
//  Ttl        64
//  Source Ip  10.0.0.1
//
//MplsOverGreNhg2
//  Id         3
//  Type       mplsOverGre
//  Size       2
//  Ttl        64
//  Source Ip  20.0.0.1
//  Entries (left most label is the top of the stack)
//    0  push label-stack 30   tunnel-destination 20.0.0.33
//         Tunnel destination directly connected, Ethernet4
//         00:33:00:33:00:35, Ethernet4
//    1  push label-stack 40   tunnel-destination 20.0.0.44
//         Tunnel destination directly connected, Ethernet4
//         00:44:00:44:00:45, Ethernet4

class mpls_over_gre_nhg_agent : public eos::agent_handler {
 public:
   eos::agent_mgr * agentMgr_;
   eos::ip_route_mgr * ipMgr_;
   eos::nexthop_group_mgr * nhgMgr_;
   eos::tracer t;
   eos::ip_route_key_t routeKey;

   explicit mpls_over_gre_nhg_agent(eos::sdk & sdk)
         : eos::agent_handler(sdk.get_agent_mgr()),
           agentMgr_(sdk.get_agent_mgr()),
           ipMgr_(sdk.get_ip_route_mgr()),
           nhgMgr_(sdk.get_nexthop_group_mgr()),
           t("MplsOverGreNextHopGroupsAgent") {
      t.trace0("Constructing Mpls over gre nexthop group agent");
   }

   void create_nexthop_group(const std::string & name,
                             const eos::ip_addr_t & src_ip,
                             eos::intf_id_t src_intf) {
      t.trace0("Creating nexthop group");
      eos::nexthop_group_t nhg = 
         eos::nexthop_group_t(name,
                              eos::NEXTHOP_GROUP_MPLS_OVER_GRE );
      if ( !!src_intf ) {
         nhg.source_intf_is(src_intf);
      } else {
         nhg.source_ip_is(src_ip);
      }
      // And commit it to Sysdb!
      nhgMgr_->nexthop_group_set(nhg);
   }

   void set_nexthop_group_entry(const std::string & name,
                                int entry_idx,
                                eos::mpls_label_t label,
                                const eos::ip_addr_t & dest_ip) {
      t.trace0("Set nexthop group entry");
      assert(nhgMgr_->exists(name));
      eos::nexthop_group_t nhg = nhgMgr_->nexthop_group(name); 
      eos::nexthop_group_mpls_action_t mpls_action(eos::MPLS_ACTION_PUSH);
      mpls_action.label_stack_set(label);
      eos::nexthop_group_entry_t nhe(dest_ip);
      nhe.mpls_action_is(mpls_action);
      nhg.nexthop_set(entry_idx, nhe);
      // And commit it to Sysdb!
      nhgMgr_->nexthop_group_set(nhg);
   }

   void del_nexthop_group_entry(const std::string & name,
                                int entry_idx) {
      t.trace0("Delete nexthop group entry");
      assert(nhgMgr_->exists(name));
      eos::nexthop_group_t nhg = nhgMgr_->nexthop_group(name); 
      nhg.nexthop_del(entry_idx);
      // And commit it to Sysdb!
      nhgMgr_->nexthop_group_set(nhg);
   }

   void on_initialized() {
      t.trace0("Initializing Mpls over gre nexthop group agent");
      // Handle initial state.
      // Active Nexthop group
      create_nexthop_group("MplsOverGreNhg1",
                           eos::ip_addr_t("10.0.0.1"),
                           eos::intf_id_t("Ethernet3") );
      set_nexthop_group_entry("MplsOverGreNhg1",
                              0, eos::mpls_label_t(30),
                              eos::ip_addr_t("10.0.0.33"));
      set_nexthop_group_entry("MplsOverGreNhg1",
                              1, eos::mpls_label_t(40),
                              eos::ip_addr_t("10.0.0.44"));
      // Standby Nexthop group
      create_nexthop_group("MplsOverGreNhg2",
                           eos::ip_addr_t("20.0.0.1"),
                           eos::intf_id_t("Ethernet4") );
      set_nexthop_group_entry("MplsOverGreNhg2",
                              0, eos::mpls_label_t(30),
                              eos::ip_addr_t("20.0.0.33"));
      set_nexthop_group_entry("MplsOverGreNhg2",
                              1, eos::mpls_label_t(40),
                              eos::ip_addr_t("20.0.0.44"));

      routeKey = eos::ip_route_key_t(eos::ip_prefix_t(
                                     eos::ip_addr_t("172.1.1.4"), 32));
      eos::ip_route_t route(routeKey);
      ipMgr_->ip_route_set(route);

      std::string option = get_agent_mgr()->agent_option("action");
      on_agent_option("action", option);

      t.trace0("Initialization done!");
   }

   void on_agent_option(std::string const & option_name,
                        std::string const & value) {
      t.trace0("on_agent_option");
      if ( option_name == "action" ) {
         eos::ip_route_via_t via(routeKey);
         if (value == "use_backup") {
            t.trace0("Setting via to backup");
            via.nexthop_group_is("MplsOverGreNhg2");
         } else {
            t.trace0("Setting via to primary");
            via.nexthop_group_is("MplsOverGreNhg1");
         }
         ipMgr_->ip_route_via_set(via);
      }
   }
};

int main(int argc, char ** argv) {
   eos::sdk sdk;
   mpls_over_gre_nhg_agent agent(sdk);
   sdk.main_loop(argc, argv);
}
