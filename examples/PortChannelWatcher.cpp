// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/eth.h>
#include <eos/eth_intf.h>
#include <eos/eth_lag_intf.h>
#include <eos/intf.h>
#include <eos/sdk.h>
#include <eos/timer.h>
#include <eos/tracing.h>

/**
 * @file
 * An example agent reacting to PortChannel interface events.
 *
 * Run this agent, and then make configuration changes (in the CLI or
 * via eAPI) to port channels. The agent will react and display
 * messages depending on the types of events received.
 *
 * In addition, every 30 seconds, the LAG iterators are exercised.
 * Each configured LAG interface, its configured members and the
 * current status of each member are traced.
 *
 * How to run the example:
 *
 * $ TRACE="PortChannelWatcher" ./PortChannelWatcher
 */

static const int TIMEOUT_SCAN_ITERATORS = 30;

class port_channel_watcher : public eos::agent_handler,
                             public eos::intf_handler,
                             public eos::eth_lag_intf_handler,
                             public eos::eth_intf_handler,
                             public eos::timeout_handler {
 public:
   explicit port_channel_watcher(eos::sdk & sdk)
         : eos::agent_handler(sdk.get_agent_mgr()),
           eos::intf_handler(sdk.get_intf_mgr()),
           eos::eth_lag_intf_handler(sdk.get_eth_lag_intf_mgr()),
           eos::eth_intf_handler(sdk.get_eth_intf_mgr()),
           eos::timeout_handler(sdk.get_timeout_mgr()),
           t("PortChannelWatcher") {
      t.trace0("Agent constructed");
      // This eth_lag_intf_handler receives notifications for all LAGs
      // as well as Ethernet specific interface state via the eth_intf_handler.
      watch_all_eth_lag_intfs(true);
      watch_all_eth_intfs(true);
      watch_all_intfs(true);
   }

   void on_initialized() {
      t.trace0("Initialized");
      // Kick off the iterator scanner
      timeout_time_is(eos::now() + 1);
   }

   void on_timeout() {
      scan_iterators();
      timeout_time_is(eos::now() + TIMEOUT_SCAN_ITERATORS);
   }

   void scan_iterators() {
      auto mgr = get_eth_lag_intf_mgr();
      for (auto lag = mgr->eth_lag_intf_iter(); lag; ++lag) {
         t.trace2("Found configured LAG: %s", lag->to_string().c_str());
         // Emit its member interfaces
         for (auto memb = mgr->eth_lag_intf_member_iter(*lag);
              memb; ++memb) {
            t.trace2("  member: %s", memb->to_string().c_str());
            t.trace2(
                  "    %s",
                  mgr->eth_lag_intf_membership_status(*memb).to_string().c_str());
         }
      }
   }

   void on_lag_member_set(eos::intf_id_t lag, eos::intf_id_t member) {
      t.trace2("Member interface %s added to LAG %s",
               member.to_string().c_str(), lag.to_string().c_str());
   }

   void on_lag_member_del(eos::intf_id_t lag, eos::intf_id_t member) {
      t.trace2("Member interface %s removed from LAG %s",
               member.to_string().c_str(), lag.to_string().c_str());
   }

   void on_oper_status(eos::intf_id_t intf, eos::oper_status_t status) {
      if (intf.intf_type() == eos::INTF_TYPE_LAG) {
         t.trace2("Interface %s oper status is now %s",
                  intf.to_string().c_str(),
                  status == eos::INTF_OPER_UP ? "up" : "down");
      }
   }

   void on_intf_create(eos::intf_id_t intf) {
      if (intf.intf_type() == eos::INTF_TYPE_LAG) {
         t.trace2("Interface %s created", intf.to_string().c_str());
      }
   }

   void on_intf_delete(eos::intf_id_t intf) {
      if (intf.intf_type() == eos::INTF_TYPE_LAG) {
         t.trace2("Interface %s deleted", intf.to_string().c_str());
      }
   }

   void on_eth_addr(eos::intf_id_t intf, eos::eth_addr_t mac_addr) {
      if (intf.intf_type() == eos::INTF_TYPE_LAG) {
         t.trace2("Interface %s MAC address is now %s",
                  intf.to_string().c_str(), mac_addr.to_string().c_str());
      }
   }

   void on_agent_enabled(bool enabled) {
      if (!enabled) {
         t.trace0("Shutting down");
         get_agent_mgr()->agent_shutdown_complete_is(true);
      }
   }

 private:
   eos::tracer t;
   eos::intf_id_t thisIntf;
};

int main(int argc, char ** argv) {
   eos::sdk sdk;
   port_channel_watcher agent(sdk);
   sdk.main_loop(argc, argv);
}
