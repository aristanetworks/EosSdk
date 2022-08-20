// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/route_map.h>
#include <eos/sdk.h>
#include <eos/tracing.h>

/* This example shows how to configure a route map, configure route map entry in
 * a specific route map, and access those configurations using EosSdk APIs.
 */
class RouteMapAgent : public eos::agent_handler {
 public:
   eos::tracer t;
   eos::route_map_mgr *route_map_mgr_;
    
   explicit RouteMapAgent(eos::sdk & sdk)
          : eos::agent_handler(sdk.get_agent_mgr()),
            t("RouteMapAgent"),
            route_map_mgr_(sdk.get_route_map_mgr()){
      t.trace0("Constructed");

   }

   void on_initialized() {
      t.trace0("Agent initialized");

      setup_route_map();
   }

   void setup_route_map() {
      // Configure route map with map entry seq 10, with rule "100G permit"
      eos::route_map_name_t map_name = "test-rm";
      eos::route_map_t route_map;

      eos::route_map_entry_t map_entry1(true);
      eos::route_map_link_bandwidth_t link_bandwidth1;
      eos::link_bandwidth_t bandwidth1(100, eos::LINK_BANDWIDTH_UNIT_GIGABIT);
      link_bandwidth1.route_map_operation_type_set_is(bandwidth1);
      map_entry1.link_bandwidth_is(link_bandwidth1);
      route_map.map_entry_set(10, map_entry1);
      
      // Commit the route map
      t.trace0("Commit the first initial route map");
      route_map_mgr_->route_map_set(map_name, route_map);
      
      // Configure a new route map entry
      eos::route_map_entry_t map_entry2(true);
      eos::route_map_link_bandwidth_t link_bandwidth2;
      eos::link_bandwidth_t bandwidth2(200, eos::LINK_BANDWIDTH_UNIT_MEGABIT);
      eos::bgp_asn_t asn = 22;
      link_bandwidth2.route_map_operation_type_delete_is(bandwidth2, asn);
      map_entry2.link_bandwidth_is(link_bandwidth2);

      // Commit the route map entry on previous configured route map
      t.trace0("Add another map entry into route map");
      route_map_mgr_->route_map_entry_set(map_name, 20, map_entry2);
      
      // Configure the priority value of EosSdk
      route_map_mgr_->priority_is(10);
      t.trace0("Set priority");

      // Delete map entry1 via config
      route_map_mgr_->route_map_entry_del(map_name, 10);

      // Delete route map via config
      route_map_mgr_->route_map_del(map_name);
   
      t.trace0("%s: Test route map basic finished", __FUNCTION__);
      
   }
};

int main(int argc, char ** argv) {
   eos::sdk sdk;
   RouteMapAgent agent(sdk);
   sdk.main_loop(argc, argv);
}
