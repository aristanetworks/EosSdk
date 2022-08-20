// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/intf.h>
#include <eos/ip_intf.h>
#include <eos/sdk.h>
#include <eos/tracing.h>

/**
 * This example agent program displays changes to the
 * internal VLAN ID mappings via tracing. Compile it
 * and copy it to a switch and run it, e.g.,;
 *
 * $ scp InternalVlan switch:/mnt/flash/
 * $ ssh switch
 * switch# bash
 * Arista Networks EOS shell
 *
 * $ TRACE="InternalVlanId*" /mnt/flash/InternalVlan
 */

class internal_vlan_id : public eos::agent_handler,
                         public eos::ip_intf_handler {
 public:
   eos::tracer t;

   explicit internal_vlan_id(eos::sdk & sdk)
         : eos::agent_handler(sdk.get_agent_mgr()),
           eos::ip_intf_handler(sdk.get_ip_intf_mgr()),
           t("InternalVlanId") {
      t.trace0("Agent constructed");
      watch_all_ip_intfs(true);
   }

   void on_initialized() {
      t.trace0("Initialized");
   }

   void on_internal_vlan_id(eos::intf_id_t const & i, eos::vlan_id_t vlan_id) {
      t.trace0("on_internal_vlan_id: intf %s vlan_id %d",
               i.to_string().c_str(), vlan_id);
   }
};

int main(int argc, char ** argv) {
   eos::sdk sdk;
   internal_vlan_id agent(sdk);
   sdk.main_loop(argc, argv);
}
