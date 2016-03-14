// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/nexthop_group.h>
#include <eos/sdk.h>
#include <eos/tracing.h>
#include <eos/timer.h>

#include <stdio.h>
#include <sstream>

// This agent displays the counters for all configured nexthop
// groups on the switch. To use, first build this agent and transfer
// the resulting binary to the switch. Then, configure the daemon
// from the cli:                                                    
//    (config)# daemon NhgCounterAgent
//    (config-daemon-NhgCounterAgent)# exec <path to agent binary>
//    (config-daemon-NhgCounterAgent)# no shutdown

// Then, to see the counters for all configured nexthop groups, run
//    (config)# show daemon NhgCounterAgent
//    Agent: NhgCounterAgent (running)
//    No configuration options stored.
//
//    Status:
//    Data         Value
//    ------------ ----------------------
//    mygroup - 0       0 packets, 0 bytes
//    mygroup - 1       101 packets, 8686 bytes
//

// Display nexthop group counters every 2 secs
static int nexthop_counter_interval = 2;

class nexthop_counter_agent : public eos::agent_handler,
                              public eos::timeout_handler {
 public:
   explicit nexthop_counter_agent(eos::sdk & sdk)
         : eos::agent_handler(sdk.get_agent_mgr()),
           eos::timeout_handler(sdk.get_timeout_mgr()),
           nhgMgr(sdk.get_nexthop_group_mgr()),
           t("NexthopCounterAgent") {
      t.trace0("Agent constructed");
   }

   void on_initialized() {
      t.trace0("Initialized");
      timeout_time_is(eos::now() + nexthop_counter_interval);
   }

   void display_counters() {
      // Clear all status
      for (auto iter = get_agent_mgr()->status_iter(); iter; ++iter) {
         get_agent_mgr()->status_del(*iter);
      }

      // Display counters for all nexthop groups
      for (auto nhIter = nhgMgr->nexthop_group_iter(); nhIter; ++nhIter) {
         auto read_nhg = nhgMgr->nexthop_group(nhIter->name());
         auto entries = read_nhg.nexthops();
         for (uint16_t i = 0; i < read_nhg.size(); ++i) {

            if (!entries[ i ].nexthop() == eos::ip_addr_t()) {
               std::stringstream nhgkey, nhgvalue;
               auto counter = nhgMgr->counter(read_nhg.name(), i);

               nhgkey << read_nhg.name() << " - " << i;
               nhgvalue << counter.packets() << " packets, ";
               nhgvalue << counter.bytes() << " bytes";
               get_agent_mgr()->status_set(nhgkey.str(), nhgvalue.str());
            }
         }
      }
   }

   void on_timeout() {
      display_counters();
      timeout_time_is(eos::now() + nexthop_counter_interval);
   }

   void on_agent_option(std::string const & option_name,
                        std::string const & value) {
      t.trace0("on_agent_option");
      if (option_name == "timeout" && !value.empty()) {
         nexthop_counter_interval = atoi(value.c_str());
      }
   }

 private:
   eos::tracer t;
   eos::nexthop_group_mgr * nhgMgr;
};

int main(int argc, char ** argv) {
   eos::sdk sdk;
   nexthop_counter_agent agent(sdk);
   sdk.main_loop(argc, argv);
}

