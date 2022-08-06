// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/ip_route.h>
#include <eos/nexthop_group.h>
#include <eos/sdk.h>
#include <eos/timer.h>
#include <eos/tracing.h>


// Program a bunch of routes, and then reprogram over them using resync.
// After re-inserting IPv4 routes, this will remove them and repeat for IPv6.
//
// Make the agent using a 32-bit linux build environment:
//    bash# g++ -leos -std=gnu++14 examples/IpRouteBulkUpdater.cpp -o route_updater
// Now you can transfer the binary to flash: on an EOS instance with
// EosSdk.i686.rpm installed and run the agent from bash:
//    bash# TRACE=EosSdk*/0-5,route_updater/* /mnt/flash/route_updater
// or from the CLI
// (conf)# daemon route_updater
// (conf-daemon-route_updater)# exec /mnt/flash/route_updater
// (conf-daemon-route_updater)# no shutdown


#define INITIAL_ROUTES 28000
#define TOTAL_ROUTES   200000

class route_updater : public eos::agent_handler,
                      public eos::timeout_handler {
 public:
   explicit route_updater(eos::sdk & sdk) 
         : eos::agent_handler(sdk.get_agent_mgr()),
           eos::timeout_handler(sdk.get_timeout_mgr()),
           phase(0), is_v6_phase(false), is_new_api(false),
           t("route_updater"), 
           agent_mgr(sdk.get_agent_mgr()),
           nhg_mgr(sdk.get_nexthop_group_mgr()),
           tag(42) {
      t.trace0("Constructed agent");
      ip_mgr = sdk.get_ip_route_mgr();
      ip_mgr->tag_is(tag);
   }

   void clean_status() {
      agent_mgr->status_del("clear_routes");
      agent_mgr->status_del("insert_initial_routes");
      agent_mgr->status_del("re_insert_routes");

      agent_mgr->status_del("clear_routes_v6");
      agent_mgr->status_del("insert_initial_routes_v6");
      agent_mgr->status_del("re_insert_routes_v6");

      agent_mgr->status_del("clear_routes_new_api");
      agent_mgr->status_del("insert_initial_routes_new_api");
      agent_mgr->status_del("re_insert_routes_new_api");

      agent_mgr->status_del("clear_routes_v6_new_api");
      agent_mgr->status_del("insert_initial_routes_v6_new_api");
      agent_mgr->status_del("re_insert_routes_v6_new_api");
   }

   void on_initialized() {
      t.trace0("Initialized agent");
      clean_status();
      set_nexthop_group();
      handle_phase();
   }

   void on_timeout() {
      t.trace0("Got a timer event.");
      handle_phase();
   }

   void on_agent_option(std::string const & name,
                        std::string const & value) {
      t.trace3("%s key=%s, value=%s", __PRETTY_FUNCTION__,
                    name.c_str(), value.c_str());
      if(name == "insert_vrf_routes") {
         if(value == "ip") {
            insert_routes_vrf(0, INITIAL_ROUTES, "blue");
         } else if(value == "ipv6") {
            insert_v6_routes_vrf(0, INITIAL_ROUTES, "blue");
         }
         return;
      }

      if(name == "delete_vrf_routes") {
         if(value == "ip") {
            delete_routes_vrf(0, INITIAL_ROUTES, "blue");
         } else if(value == "ipv6") {
            delete_v6_routes_vrf(0, INITIAL_ROUTES, "blue");
         }
         return;
      }

      if ((name == "cleanup" || name == "cleanup_v6" ||
            name == "cleanup_new_api" ||
            name == "cleanup_v6_new_api") && value == "start") {
         clear_routes();
         return;
      }

      if ((name == "cleanup"  ||
            name == "cleanup_new_api") && value == "done") {
         is_v6_phase = true;
         phase = 0;
         timeout_time_is(eos::now() + 5);
         return;
      }

      if (name == "cleanup_v6" && value == "done") {
         is_v6_phase = false;
         is_new_api = true;
         phase = 0;
         timeout_time_is(eos::now() + 5);
      }
   }

   void handle_phase() {
      t.trace0("Starting phase %d", phase);
      switch(phase) {
       case 0:
         clear_routes();
         timeout_time_is(eos::now() + 20);
         break;
       case 1:
         insert_initial_routes();
         timeout_time_is(eos::now() + 65);
         break;
       case 2:
         re_insert_routes();
         break;
       default:
         //get_agent_mgr()->exit();
         break;
      }
      t.trace0("Finished phase %d", phase);
      ++phase;
   }
   

   void clear_routes() {
      t.trace1("Clearing all routes");
      ip_mgr->resync_init();
      t.trace1("  clearing...");
      ip_mgr->resync_complete();
      t.trace1("  Finished clearing");
      if (!is_v6_phase) {
         if (!is_new_api) {
            agent_mgr->status_set("clear_routes", "done");
         } else {
            agent_mgr->status_set("clear_routes_new_api", "done");
         }
      } else {
         if (!is_new_api) {
            agent_mgr->status_set("clear_routes_v6", "done");
         } else {
            agent_mgr->status_set("clear_routes_v6_new_api", "done");
         }
      }
   }


   void insert_initial_routes() {
      t.trace1("Programming addresses");
      if (!is_v6_phase) {
         if (!is_new_api) {
            insert_routes(0, INITIAL_ROUTES, false);
            agent_mgr->status_set("insert_initial_routes", "done");
         } else {
            insert_routes(0, INITIAL_ROUTES, true);
            agent_mgr->status_set("insert_initial_routes_new_api", "done");
         }
      } else {
         if (!is_new_api) {
            insert_v6_routes(0, INITIAL_ROUTES, false);
            agent_mgr->status_set("insert_initial_routes_v6", "done");
         } else {
            insert_v6_routes(0, INITIAL_ROUTES, true);
            agent_mgr->status_set("insert_initial_routes_v6_new_api", "done");
         }   
      }
      t.trace0("Finished!");
   }

   void re_insert_routes() {
      t.trace1("Re-Programming addresses");
      ip_mgr->resync_init();
      // Use insert_routes(INITIAL_ROUTES, TOTAL_ROUTES); if you only want to
      // add new routes and not the initial routes.
      if ( !is_v6_phase ) {
         if (!is_new_api) {
            insert_routes(0, TOTAL_ROUTES, false);
         } else {
            insert_routes(0, TOTAL_ROUTES, true);
         }
      } else {
         if (!is_new_api) {
            insert_v6_routes(0, TOTAL_ROUTES, false);
         } else {
            insert_v6_routes(0, TOTAL_ROUTES, true);
         }
      }
      t.trace1("  finishing resync...");
      ip_mgr->resync_complete();
      t.trace1("  resync complete");
      t.trace0("Finished!");
      if ( !is_v6_phase ) {
         if (!is_new_api) {
            agent_mgr->status_set("re_insert_routes", "done");
         } else {
            agent_mgr->status_set("re_insert_routes_new_api", "done");
         }
      } else {
         if (!is_new_api) {
            agent_mgr->status_set("re_insert_routes_v6", "done");
         } else {
            agent_mgr->status_set("re_insert_routes_v6_new_api", "done");
         }
      }
   }

   void insert_routes(uint32_t start, uint32_t end, bool new_api) {
      t.trace1("Starting to insert %d routes, starting at route# %d", end, start);
      for(eos::uint32_be_t i = start; i < end; i++) {
         eos::uint32_be_t addr_num = i%65536;
         addr_num = addr_num << 8;
         addr_num = addr_num ^ (eos::uint32_be_t)(200 + i/65536);
         eos::ip_prefix_t prefix(eos::ip_addr_t(addr_num), 24);
         if(i%2550 == 0) t.trace3("Adding prefix %s", prefix.to_string().c_str());
         eos::ip_route_key_t rkey(prefix);
         eos::ip_route_t route(rkey);
         route.tag_is(tag);
         eos::ip_route_via_t via(rkey);
         via.nexthop_group_is("mpls_nhg");
         if (!new_api) {
            ip_mgr->ip_route_set(route);
         } else {
            ip_mgr->ip_route_set(route, eos::IP_ROUTE_ACTION_NEXTHOP_GROUP);
         }
         ip_mgr->ip_route_via_set(via);
      }
      t.trace1("Finished inserting %d routes, starting at route# %d", end, start);
   }

   void insert_v6_routes(uint32_t start, uint32_t end, bool new_api) {
      t.trace1("Starting to insert %d v6_routes, starting at route# %d", end, start);
      char buf[256];
      for(eos::uint32_be_t i = start; i < end; i++) {
         eos::uint32_be_t first = (i/65536)%65536;
         eos::uint32_be_t second = i%65536;
         snprintf(buf, 256, "%04x:%04x::", first, second);
         eos::ip_addr_t ip(buf);
         eos::ip_prefix_t prefix6(ip, 64);
         eos::ip_route_key_t rkey6(prefix6);
         eos::ip_route_t route6(rkey6);
         route6.tag_is(tag);
         eos::ip_route_via_t via6(rkey6);
         via6.nexthop_group_is("mpls_nhg");
         if (!new_api) {
            ip_mgr->ip_route_set(route6);
         } else {
            ip_mgr->ip_route_set(route6, eos::IP_ROUTE_ACTION_NEXTHOP_GROUP);
         }
         ip_mgr->ip_route_via_set(via6);
      }
      t.trace1("Finished inserting %d routes, starting at route# %d", end, start);
   }

   void set_nexthop_group() {
      t.trace1("Setting nexthop group");
      // Create a nexthop-group mpls_nhg:
      //     nexthop-group mpls_nhg type mpls
      //        size 256
      //        entry 0 push label-stack 16 nexthop 10.0.0.8
      std::string nhg_name = "mpls_nhg";
      int label = 16;
      int entry = 0;
      std::string ip_addr_str = "10.0.0.8";
      eos::nexthop_group_t nhg = eos::nexthop_group_t(nhg_name, 
                                                      eos::NEXTHOP_GROUP_MPLS);
      eos::nexthop_group_entry_t nhge(eos::ip_addr_t(ip_addr_str.c_str()));
      eos::nexthop_group_mpls_action_t mpls_action(eos::MPLS_ACTION_PUSH,
                                                   {eos::mpls_label_t(label)});
      nhge.mpls_action_is(mpls_action);
      nhg.nexthop_set(entry, nhge);
      nhg_mgr->nexthop_group_set(nhg);
   }
 
   eos::ip_route_key_t create_ip_route_key (eos::uint32_be_t i) {
      eos::uint32_be_t addr_num = i%65536;
      addr_num = addr_num << 8;
      addr_num = addr_num ^ (eos::uint32_be_t)(200 + i/65536);
      eos::ip_prefix_t prefix(eos::ip_addr_t(addr_num), 24);
      if(i%2550 == 0) t.trace3("Adding prefix %s", prefix.to_string().c_str());
      eos::ip_route_key_t rkey(prefix);
      return rkey;
   }

   eos::ip_route_key_t create_ip_v6_route_key (eos::uint32_be_t i) {
      char buf[256];
      eos::uint32_be_t first = (i/65536)%65536;
      eos::uint32_be_t second = i%65536;
      snprintf(buf, 256, "%04x:%04x::", first, second);
      eos::ip_addr_t ip(buf);
      eos::ip_prefix_t prefix6(ip, 64);
      eos::ip_route_key_t rkey6(prefix6);
      return rkey6;
   }

   void insert_routes_vrf(uint32_t start, uint32_t end, std::string vrf) {
      t.trace1("Insert %d routes into vrf %s, \
            starting at route %d", end, vrf.c_str(), start);
      for(eos::uint32_be_t i = start; i < end; i++) {
         eos::ip_route_key_t rkey = create_ip_route_key(i);
         eos::ip_route_t route(rkey);
         route.tag_is(tag);
         ip_mgr->ip_route_set(route, vrf);
      }
      t.trace1("Finished inserting %d routes into vrf %s, \
            starting at route %d", end, vrf.c_str(), start);
   }

   void delete_routes_vrf(uint32_t start, uint32_t end, std::string vrf) {
      t.trace1("Starting to delete %d routes from vrf %s, \
            starting at route %d", end, vrf.c_str(), start);
      for(eos::uint32_be_t i = start; i < end; i++) {
         eos::ip_route_key_t rkey = create_ip_route_key(i);
         ip_mgr->ip_route_del(rkey, vrf);
      }
      t.trace1("Finished deleting %d routes into vrf %s, \
            starting at route %d", end, vrf.c_str(), start);  
   }

   void insert_v6_routes_vrf(uint32_t start, uint32_t end, std::string vrf) {
      t.trace1("Starting to insert %d v6_routes into vrf %s, \
            starting at route %d", end, vrf.c_str(), start);
      for(eos::uint32_be_t i = start; i < end; i++) {
         eos::ip_route_key_t rkey6 = create_ip_v6_route_key(i); 
         eos::ip_route_t route6(rkey6);
         route6.tag_is(tag);
         ip_mgr->ip_route_set(route6, vrf);
      }
      t.trace1("Finished inserting %d routes into vrf %s, \
            starting at route %d", end, vrf.c_str(), start);
   }
    
   void delete_v6_routes_vrf(uint32_t start, uint32_t end, std::string vrf) {
      t.trace1("Starting to delete %d routes from vrf %s, \
            starting at route %d", end, vrf.c_str(), start);
      for(eos::uint32_be_t i = start; i < end; i++) {
         eos::ip_route_key_t rkey6 = create_ip_v6_route_key(i);
         ip_mgr->ip_route_del(rkey6, vrf);
      }
      t.trace1("Finished deleting %d routes into vrf %s, \
            starting at route %d", end, vrf.c_str(), start);  
   }

   // <other handlers>

 private:
   uint8_t phase;
   bool is_v6_phase;
   bool is_new_api;

   eos::tracer t;
   eos::agent_mgr *agent_mgr;
   eos::nexthop_group_mgr * nhg_mgr;
   eos::ip_route_mgr * ip_mgr;
   uint32_t tag;
};

int main(int argc, char ** argv) {
   eos::sdk sdk;
   route_updater ex(sdk);
   sdk.main_loop(argc, argv);
}

