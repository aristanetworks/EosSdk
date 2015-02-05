// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/eth_lag_intf.h>
#include <eos/intf.h>
#include <eos/sdk.h>
#include <eos/tracing.h>

/**
 * @file
 * An example agent reacting to PortChannel interface events.
 *
 * Run this agent, and then make changes (in the CLI) to
 * port channels. The agent will react and display messages
 * depending on the types of events received.
 */

class port_channel_watcher : public eos::agent_handler,
                             eos::eth_lag_intf_handler {
 public:
   explicit port_channel_watcher(eos::sdk & sdk)
         : eos::agent_handler(sdk.get_agent_mgr()),
           eos::eth_lag_intf_handler(sdk.get_eth_lag_intf_mgr()),
           t("PortChannelWatcher") {
      t.trace0("Agent constructed");
      // This eth_lag_intf_handler receives notifications for all LAGs
      watch_all_eth_lag_intfs(true);
   }

   void on_initialized() {
      t.trace0("Initialized");
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
         t.trace2("LAG %s became %s",
                  intf.to_string().c_str(),
                  status == eos::INTF_OPER_UP ? "up" : "down");
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
