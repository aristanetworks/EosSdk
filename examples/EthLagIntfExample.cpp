// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <assert.h>

#include <eos/agent.h>
#include <eos/eth_intf.h>
#include <eos/eth_lag_intf.h>
#include <eos/exception.h>
#include <eos/panic.h>
#include <eos/sdk.h>
#include <eos/tracing.h>

/**
 * This example agent program shows how to make use of EosSdk eth_lag_intf APIs.
 * It demonstrates how to create new port channels and adding member interfaces
 * to port channels.
 *
 * To run this example:
 *
 * $ scp EthLagIntfExample switch:/mnt/flash/
 * $ ssh switch
 * switch# bash
 * Arista Networks EOS shell
 *
 * $ TRACE="EthLagIntfExample*" /mnt/flash/EthLagIntfExample
 *
 * Note, on_lag_member_set will only be called when the member interface becomes
 * active in the port channel.
 */


class ApplicationAgent : public eos::agent_handler,
                         public eos::eth_lag_intf_handler,
                         public eos::eth_intf_handler,
                         public eos::intf_handler {
 public:
   eos::eth_lag_intf_mgr *eth_lag_intf_mgr_;
   eos::tracer t;

   explicit ApplicationAgent(eos::sdk & sdk) :
            eos::agent_handler(sdk.get_agent_mgr()),
            eos::eth_lag_intf_handler(sdk.get_eth_lag_intf_mgr()),
            eos::eth_intf_handler(sdk.get_eth_intf_mgr()),
            eos::intf_handler(sdk.get_intf_mgr()),
            eth_lag_intf_mgr_(sdk.get_eth_lag_intf_mgr()),
            t("EthLagIntfExample") {
      watch_intf(eos::intf_id_t("Port-Channel23"), true);
      watch_eth_lag_intf(eos::intf_id_t("Port-Channel23"), true);
   }

   // Called when all agents are initialized
   void on_initialized() {
      // Creates LAG 23, no mode specified
      eth_lag_intf_mgr_->eth_lag_intf_is(eos::intf_id_t("Port-Channel23"));
      t.trace8("ApplicationAgent initialized.");
   }

   // Handler for LAG interface creation
   void on_intf_create(eos::intf_id_t lag) {
      t.trace8("ApplicationAgent on_intf_create, for interface: %s.",
               lag.to_string().c_str());
      if (lag == eos::intf_id_t("Port-Channel23")) {
         t.trace8("ApplicationAgent Port-Channel23 created.");

         // Application logic goes here, such as creating more LAG interfaces
         // or adding member interfaces to it.
         eth_lag_intf_mgr_->membership_set(eos::intf_id_t("Ethernet1"),
                  lag,
                  eos::ETH_LAG_INTF_MEMBER_LACP_MODE_PASSIVE);
         t.trace8("ApplicationAgent: added Ethernet1 to %s.",
                  lag.to_string().c_str());
      }
      return;
   }

   // Handler called when a physical interface becomes active in a LAG.
   // In the case of LACP managed interfaces, members do not become
   // active until LACP negotiation is complete.
   void on_lag_member_set(eos::intf_id_t lag, eos::intf_id_t member) {
      t.trace8("ApplicationAgent on_lag_member_set: %s added to %s",
                member.to_string().c_str(), lag.to_string().c_str());
      // Perform some relevant action, such as reporting to a monitoring
      // system or provisioning workflow manager.
   }

   // Handler called when a physical interface is no longer active in a LAG.
   void on_lag_member_del(eos::intf_id_t lag, eos::intf_id_t member) {
      // Custom application code to react to a physical interface
      // leaving a LAG for any reason. For example, to get the reason:
      auto stat = eth_lag_intf_mgr_->eth_lag_intf_membership_status(member);
      std::string reason(stat.reason());  // e.g., 'not link up'
      t.trace8("ApplicationAgent on_lag_member_del: %s deleted from %s",
                member.to_string().c_str(), lag.to_string().c_str());
   }

};

int main(int argc, char **argv) {
   eos::sdk sdk;
   ApplicationAgent agent(sdk);
   sdk.main_loop(argc, argv);
}
