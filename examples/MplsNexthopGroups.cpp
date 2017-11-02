// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/ip.h>
#include <eos/ip_route.h>
#include <eos/mpls.h>
#include <eos/nexthop_group.h>
#include <eos/sdk.h>

#include <stdio.h>

class my_agent : public eos::agent_handler {
 public:
   eos::agent_mgr * agentMgr_;
   eos::ip_route_mgr * ipMgr_;
   eos::nexthop_group_mgr * nhgMgr_;

   explicit my_agent(eos::sdk & sdk)
         : eos::agent_handler(sdk.get_agent_mgr()),
           agentMgr_(sdk.get_agent_mgr()),
           ipMgr_(sdk.get_ip_route_mgr()),
           nhgMgr_(sdk.get_nexthop_group_mgr()) {
      printf("Constructing my agent...\n");
   }

   void create_nexthop_group(std::string name) {
      printf("Creating nexthop group\n");
      eos::nexthop_group_t nhg = eos::nexthop_group_t(name,
                                                      eos::NEXTHOP_GROUP_MPLS);

      eos::nexthop_group_mpls_action_t mplsActionA(
            eos::MPLS_ACTION_PUSH, {eos::mpls_label_t(30), eos::mpls_label_t(31)});
      eos::nexthop_group_mpls_action_t mplsActionB(
            eos::MPLS_ACTION_PUSH, {eos::mpls_label_t(40), eos::mpls_label_t(41)});

      // Send 2/3rds of traffic to nexthop 10.0.0.33 with the [30, 31]
      // label stack:

      eos::nexthop_group_entry_t nhe1(eos::ip_addr_t("10.0.0.33"));
      nhe1.mpls_action_is(mplsActionA);
      nhg.nexthop_set(1, nhe1);
      nhg.nexthop_set(2, nhe1);

      // Send 1/3rd of traffic to nexthop 10.0.0.44 with the [40, 41]
      // label stack:
      eos::nexthop_group_entry_t nhe2(eos::ip_addr_t("10.0.0.44"));
      nhe2.mpls_action_is(mplsActionB);
      nhg.nexthop_set(3, nhe2);

      // And commit it to Sysdb!
      nhgMgr_->nexthop_group_set(nhg);
   }

   void on_initialized() {
      printf("Initializing my agent...\n");

      create_nexthop_group("MplsNhg1");
      eos::ip_route_key_t routeKey(
            eos::ip_prefix_t(eos::ip_addr_t("172.1.1.4"), 32));
      eos::ip_route_t route(routeKey);
      eos::ip_route_via_t via(routeKey);
      via.nexthop_group_is("MplsNhg1");

      ipMgr_->ip_route_set(route);
      ipMgr_->ip_route_via_set(via);

      printf("Done!\n");
      agentMgr_->exit(); // (we'll just exit after this demo)
   }
};

int main(int argc, char ** argv) {
   eos::sdk sdk;
   my_agent agent(sdk);
   sdk.main_loop(argc, argv);
}
