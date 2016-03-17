// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/fib.h>
#include <eos/ip_route.h>
#include <eos/sdk.h>
#include <eos/timer.h>
#include <eos/tracing.h>

#include <chrono>
#include <iomanip>
#include <sstream>

// Program a bunch of routes, and then reprogram over them using resync.
//
// Make the agent using a 32-bit linux build environment:
//    bash# g++ -leos -std=gnu++0x examples/RibToFibProfiler.cpp -o RouteProfiler
// Now you can transfer the binary to flash: on an EOS instance with
// EosSdk.i686.rpm installed and run the agent from bash:
//    bash# TRACE=EosSdk*/0-5,RouteProfiler/* /mnt/flash/RouteProfiler
// or from the CLI
// (conf)# daemon RouteProfiler
// (conf-daemon-RouteProfiler)# exec /mnt/flash/RouteProfiler
// (conf-daemon-RouteProfiler)# no shutdown


#define DEFAULT_NUM_ROUTES 1000
#define DEFAULT_NUM_NEXTHOP_GROUPS 1000

// Use "Ethernet#" (and #+1) as via nexthops for forward routes:
#define BASE_ETHERNET_NUM 3

#define HELP_STR                                                        \
   "This agent profiles various route insertion/deletion/setting "      \
   "operations. It can use the following CLI options: \n"               \
   "- option iter value <name>:\n"                                      \
   "    run a new iteration \n"                                         \
   "- option num_routes value <num>:\n"                                 \
   "    use this number of routes \n"                                   \
   ""

class RouteProfiler : public eos::agent_handler,
                      public eos::fib_handler,
                      public eos::timeout_handler {
 public:
   explicit RouteProfiler(eos::sdk & sdk) :
           eos::agent_handler(sdk.get_agent_mgr()),
           eos::fib_handler(sdk.get_fib_mgr(eos::MODE_TYPE_READ_NOTIFYING)),
           eos::timeout_handler(sdk.get_timeout_mgr()),
           phase_(0),
           tag_(42),
           num_routes_(DEFAULT_NUM_ROUTES),
           event_num_(0),
           num_fib_routes_seen_(0),
           num_fib_fecs_seen_(0),
           route_update_type_(eos::IP_ROUTE_ACTION_FORWARD),
           t("RouteProfiler") {
      t.trace0("Constructed agent");
      agent_mgr = sdk.get_agent_mgr();
      ip_mgr = sdk.get_ip_route_mgr();
      fib_mgr = sdk.get_fib_mgr();

      ip_mgr->tag_is(tag_);
   }

   void on_initialized() {
      t.trace0("Initialized agent");
      reset_statuses();
      t.trace1("Clearing initial routes");
      ip_mgr->resync_init();
      ip_mgr->resync_complete();
   }

   void on_agent_option(std::string const & key,
                        std::string const & value) {
      if (key == "iter") {
         if (!value.empty()) {
            run_iteration(value);
         }
      } else if (key == "num_routes") {
         num_routes_ = std::stoi(value);
      }
   }

   void on_route_set(eos::fib_route_t const & route) {
      num_fib_routes_seen_++;
      if (num_fib_routes_seen_ == 1) {
         profile("First route programmed");
      } else if (num_fib_routes_seen_ == num_routes_) {
         profile("All routes programmed");
         handle_next_phase();
      }
   }

   void on_route_del(eos::fib_route_key_t const & route) {
      num_fib_routes_seen_++;
      if (num_fib_routes_seen_ == 1) {
         profile("First route deleted");
      } else if (num_fib_routes_seen_ == num_routes_) {
         profile("All routes deleted");
         handle_next_phase();
      }
   }

   void on_timeout() {
      profile("Cooldown complete");
      handle_next_phase();
   }

   void run_iteration(std::string iteration_name) {
      reset_statuses();
      start_time_ = std::chrono::system_clock::now();
      last_event_time_ = start_time_;
      event_num_ = 0;
      num_fib_routes_seen_ = 0;
      num_fib_fecs_seen_ = 0;
      phase_ = 0;

      std::stringstream event_name;
      event_name << "Start " << iteration_name << " (" << num_routes_ << " routes)";
      profile(event_name.str());
      insert_routes();
   }

   void handle_next_phase() {
      t.trace1("Running phase %d", phase_);
      num_fib_routes_seen_ = 0;
      num_fib_fecs_seen_ = 0;
      switch(phase_) {
       case 0:
         timeout_time_is(eos::now() + 5);
         break;
       case 1:
         update_routes();
         break;
       case 2:
         timeout_time_is(eos::now() + 5);
         break;
       case 3:
         clear_routes();
         break;
       default:
         profile("Done!");
         break;
      }
      phase_++;
   }

   
   void insert_routes() {
      profile("Begin insertion");
      set_routes();
      profile("End insertion");
   }

   void update_routes() {
      profile("Begin update");
      set_routes(1); // Offset of 1 means we'll be updating a bunch of routes.
      profile("End update");
   }

   void clear_routes() {
      profile("Begin delete");
      ip_mgr->resync_init();
      t.trace1("  clearing...");
      ip_mgr->resync_complete();
      profile("End delete");
   }


   void set_routes(uint32_t modification=0) {
      t.trace1("Starting to insert %d routes (modification=%d)",
               num_routes_, modification);
      char buf[32];
      for(eos::uint32_be_t i = 0; i < num_routes_; i++) {
         // Create a unique IP prefix:
         eos::uint32_be_t addr_num = i;
         addr_num = addr_num << 8;
         addr_num = addr_num ^ (eos::uint32_be_t)200;
         eos::ip_prefix_t prefix(eos::ip_addr_t(addr_num), 24);
         if(i%2550 == 0) t.trace3("Adding prefix %s", prefix.to_string().c_str());

         eos::ip_route_key_t rkey(prefix);
         eos::ip_route_t route(rkey);
         route.tag_is(tag_);

         if (route_update_type_ == eos::IP_ROUTE_ACTION_NEXTHOP_GROUP) {
            sprintf(buf, "mpls_nhg%d",
                    (modification + i) % DEFAULT_NUM_NEXTHOP_GROUPS);
            eos::ip_route_via_t via(rkey);
            via.nexthop_group_is(std::string(buf));
            ip_mgr->ip_route_set(route, eos::IP_ROUTE_ACTION_NEXTHOP_GROUP);
            ip_mgr->ip_route_via_set(via);
         } else if (route_update_type_ == eos::IP_ROUTE_ACTION_FORWARD) {
            sprintf(buf, "Ethernet%d", (BASE_ETHERNET_NUM +  modification));
            eos::ip_route_via_t via(rkey);
            via.hop_is(eos::ip_addr_t("0.0.0.0"));
            via.intf_is(eos::intf_id_t(std::string(buf)));
            ip_mgr->ip_route_set(route, eos::IP_ROUTE_ACTION_FORWARD);
            ip_mgr->ip_route_via_set(via);
         } else {
            assert(false && "unknown route update type");
         }
      }
      t.trace1("Finished inserting %d routes", num_routes_);
   }

   void reset_statuses() {
      for (auto i = agent_mgr->status_iter(); i; i++) {
         agent_mgr->status_del(*i);
      }
      agent_mgr->status_set("help", HELP_STR);
   }

   void profile(std::string event, bool update_last_event=true) {
      auto now = std::chrono::system_clock::now();
      t.trace1("Profiling event %s", event.c_str());

      std::stringstream status_key;
      status_key << std::setfill('0') << std::setw(2) << event_num_ << " " << event;

      std::chrono::duration<double> time_since_start = now - start_time_;
      std::chrono::duration<double> time_since_last = now - last_event_time_;
      std::stringstream status_value;
      status_value << "Since start: " << time_since_start.count() << " sec";
      if (update_last_event) {
         status_value << "\n      last event: " << time_since_last.count() << " sec";
      }

      agent_mgr->status_set(status_key.str(), status_value.str());
      if (update_last_event) {
         last_event_time_ = std::chrono::system_clock::now();
      }
      event_num_++;
   }

 private:
   uint32_t phase_;
   uint32_t tag_;
   uint32_t num_routes_;
   uint32_t event_num_;
   std::chrono::time_point<std::chrono::system_clock> start_time_;
   std::chrono::time_point<std::chrono::system_clock> last_event_time_;

   uint32_t num_fib_routes_seen_;
   uint32_t num_fib_fecs_seen_;

   eos::ip_route_action_t route_update_type_;

   eos::tracer t;
   eos::agent_mgr * agent_mgr;
   eos::fib_mgr * fib_mgr;
   eos::ip_route_mgr * ip_mgr;

};

int main(int argc, char ** argv) {
   eos::sdk sdk;
   RouteProfiler ex(sdk);
   sdk.main_loop(argc, argv);
}
