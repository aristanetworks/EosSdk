// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/bgp.h>
#include <eos/sdk.h>
#include <eos/tracing.h>

/**
 * This example agent reacts to bgp peer state change
 * and traces those events.
 *
 * To run this example:
 * $ Art scp BgpAgent <switch>:/mnt/flash/
 *
 *    bash# TRACE=BgpTestAgent /mnt/flash/BgpAgent
 * or from the CLI
 *   (conf)# daemon BgpAgent
 *   (conf-daemon-BgpAgent)# exe /mnt/flash/BgpAgent
 *   (conf-daemon-BgpAgent)# no shutdown
 *   (conf)# trace <agent>-<daemon> setting BgpTestAgent
 */


class BgpTestAgent : public eos::agent_handler,
                     public eos::bgp_peer_handler {
 public:
   eos::tracer t;

   explicit BgpTestAgent(eos::sdk & sdk)
      : eos::agent_handler(sdk.get_agent_mgr()),
        eos::bgp_peer_handler(sdk.get_bgp_mgr()),
        t("BgpTestAgent") {
      watch_all_peers(true);
      t.trace0("Constructed");
   }

   void on_initialized() {
      t.trace0("Agent initialized");
   }

   void on_peer_set(eos::bgp_peer_key_t const & peer_key) {
      t.trace0("peer %s created", peer_key.to_string().c_str());
   }

   void on_peer_del(eos::bgp_peer_key_t const & peer_key) {
      t.trace0("peer %s deleted", peer_key.to_string().c_str());
   }

   void on_peer_state(eos::bgp_peer_key_t const & peer_key,
                      eos::bgp_peer_state_t peer_state) {
      t.trace0("peer %s state change to %d", peer_key.to_string().c_str(),
               peer_state);
   }

   void on_agent_enabled(bool enabled) {
      if (!enabled) {
         t.trace0("Shutting down");
         get_agent_mgr()->agent_shutdown_complete_is(true);
      }
   }
};

int main(int argc, char **argv) {
   eos::sdk sdk;
   BgpTestAgent agent(sdk);
   sdk.main_loop(argc, argv);
}

