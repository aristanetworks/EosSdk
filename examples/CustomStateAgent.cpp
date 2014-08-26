// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/ip.h>
#include <eos/sdk.h>
#include <eos/tracing.h>

// Note that the AGENT_NAME must match the name passed to the daemon
// configuration CLI.
static const std::string AGENT_NAME = "custom_state_agent";

static const std::string CONTROLLER_OPTION_NAME = "controller-ip";
static const std::string CONTROLLER_STATUS_NAME = "controller-status";
static const std::string CONTROLLER_STATUS_DETAIL_NAME = "controller-status-detail";

class custom_state_agent : public eos::agent_handler {
 public:
   eos::agent_mgr * agent_mgr;
   eos::tracer t;
   
   explicit custom_state_agent(eos::sdk & sdk)
         : eos::agent_handler(sdk.get_agent_mgr()),
           agent_mgr(sdk.get_agent_mgr()),
           t(AGENT_NAME.c_str()) {
      t.trace0("Constructed");
   }

   // Overridden method from agent_handler.
   // This method is the main entry point to this agent's
   // lifecycle. At this point we can use the agent_mgr and start our
   // activities. In this example, we will connect to some centralized
   // server which we call the "controller"
   void on_initialized() {
      t.trace0("Initialized");
      // Handle initial state.
      std::string controller_ip = agent_mgr->agent_option(CONTROLLER_OPTION_NAME);
      on_agent_option(CONTROLLER_OPTION_NAME, controller_ip);
   }

   // Overridden method from agent_handler.
   // Called when the agent is disabled, for example from the CLI:
   //    switch(config)# daemon custom_state_agent
   //    switch(config-daemon-custom_state_agent)# shutdown
   void on_agent_enabled(bool enabled) {
      if (!enabled) {
         t.trace0("Disabled");
         disconnect_from_controller();
         get_agent_mgr()->agent_shutdown_complete_is(true);
      }
   }

   // Overridden method from agent_handler.
   // Called when an an option changes. For example, when a user runs
   // from the CLI:
   //    switch(config)# daemon custom_state_agent
   //    switch(config-daemon-custom_state_agent)# option controller-ip 168.33.0.4
   void on_agent_option(std::string const & option_name,
                        std::string const & value) {
      if(option_name == CONTROLLER_OPTION_NAME) {
         t.trace4("Controller IP address changed");
         if(value != "") {
            connect_to_controller(value);
         } else {
            // IP address deleted from configuration
            disconnect_from_controller();
         }
      }
   }

   // Disconnect from the controller, update the controller-status and
   // delete the controller-health status element.
   void disconnect_from_controller() {
      t.trace5("Disconnecting from controller");

      // <disconnection code would go here>

      agent_mgr->status_set(CONTROLLER_STATUS_NAME, "disconnected");
      agent_mgr->status_del(CONTROLLER_STATUS_DETAIL_NAME);      
   }
   
   // Connect to some external server based on
   // the ip_str parameter and update the controller-status and
   // controller-health status elements.
   void connect_to_controller(std::string const & ip_str) {
      eos::ip_addr_t address;
      bool valid = eos::parse_ip_addr(ip_str.c_str(), &address);
      if(!valid) {
         agent_mgr->status_set(CONTROLLER_STATUS_NAME, "error");
         agent_mgr->status_set(CONTROLLER_STATUS_DETAIL_NAME, "invalid IP address");
         return;
      }
      t.trace5("Connecting to controller at %s", address.to_string().c_str());
      bool success = true;

      // <actual connection implementation would go here>

      if(success) {
         agent_mgr->status_set(CONTROLLER_STATUS_NAME, "connected");
         agent_mgr->status_set(CONTROLLER_STATUS_DETAIL_NAME, "healthy");
      } else {
         agent_mgr->status_set(CONTROLLER_STATUS_NAME, "error");
         agent_mgr->status_set(CONTROLLER_STATUS_DETAIL_NAME, "bad connection");
      }
   }
};

int main(int argc, char ** argv) {
   eos::sdk sdk(AGENT_NAME);
   custom_state_agent agent(sdk);
   sdk.main_loop(argc, argv);
}
