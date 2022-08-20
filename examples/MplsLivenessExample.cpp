// Copyright (c) 2017 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "MplsTunnelLivenessAgent.hpp" // MplsTunnelLivenessAgent definition

struct MplsLivenessExample : public MplsTunnelLivenessAgent {
   eos::agent_mgr *agent_mgr_;

   explicit MplsLivenessExample(eos::sdk & sdk, const char *src_ip)
         : MplsTunnelLivenessAgent(sdk), agent_mgr_(sdk.get_agent_mgr()) {
      set_src_ip(src_ip);
   }

   virtual void on_initialized() {
      MplsTunnelLivenessAgent::on_initialized();

      agent_mgr_->status_set("on_initialized", "SUCCESS");
   }

   virtual void on_tunnel_status(uint32_t tunnel_key, tl_status_t status) {
      MplsTunnelLivenessAgent::on_tunnel_status(tunnel_key, status);

      // ADD YOUR CODE HERE
      std::cout << "Inherited on_tunnel_status!" << std::endl;
   }
};

// The main() function's command-line arguments are to simplify testing. Using this
// agent correctly is done via the add_session, remove_session, and on_tunnel_status
// functions.
//
// Usage: ./MplsLivenessExample <src_ip>
int main(int argc, char **argv) {
   const char *src_ip;
   if (argc == 2) {
      src_ip = argv[1];
   } else {
      std::cout << "Usage: " << argv[0] << " <src_ip>" << std::endl;
      std::cout << "Using default src_ip" << std::endl;
      src_ip = "0.0.0.0";
   }

   // Print welcome message.
   std::cout << "----------------------------------" << std::endl;
   std::cout << "Running MPLS Tunnel Liveness Agent" << std::endl;
   std::cout << "----------------------------------" << std::endl;
   std::cout << std::endl;
   std::cout << "src_ip:      " << src_ip << std::endl;
   std::cout << std::endl;

   eos::sdk sdk;
   MplsLivenessExample agent(sdk, src_ip);

   sdk.main_loop(argc, argv);
}
