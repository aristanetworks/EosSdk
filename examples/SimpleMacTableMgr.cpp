// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/acl.h>
#include <eos/fd.h>
#include <eos/eth_intf.h>
#include <eos/intf.h>
#include <eos/mac_table.h>
#include <eos/sdk.h>
#include <eos/timer.h>
#include <eos/tracing.h>

#include <assert.h>
#include <ctime>
#include <stdio.h>
#include <unistd.h>

// This agent configures and deletes static MAC entries using daemon
// configurations. To run the agent, create a mount profile using the steps
// below.
// Step 1: Compile the example agent and move the binary to
// /mnt/flash/SimpleMacTableMgr

// Step 2: Create a mount profile on the router for the agent:
// # cd /usr/lib/SysdbMountProfiles/
// # cp EosSdkAll SimpleMacTableMgr
// # vi SimpleMacTableMgr
// Change first line to: agentName:SimpleMacTableMgr-%sliceId

// Step 3: Create the agent daemon:
// Enter config mode.
// To turn on tracing use the command:
// trace <binary_name>-<daemon_name> setting EosSdk*/*
// In this case: "trace SimpleMacTableMgr-SimpleMacTableMgr setting EosSdk*/*"
// (config)# daemon SimpleMacTableMgr
// (config-daemon-SimpleMacTableMgr)#exec /mnt/flash/SimpleMacTableMgr
// (config-daemon-SimpleMacTableMgr)#no shut
// This is an EosSdk application
// Full agent name is 'SimpleMacTableMgr-SimpleMacTableMgr'

// (config-daemon-SimpleMacTableMgr)#show daemon
// Agent: SimpleMacTableMgr (running)
// No configuration options stored.
//
// Status:
// Data               Value
// ------------------ -----
// initialized?       yes
//

// Step 4: Configure a new MAC entry
// (config-daemon-SimpleMacTableMgr)#option MAC value 10:11:22:33:44:55 1 Ethernet3

// (config-daemon-SimpleMacTableMgr)#show daemon
// Agent: SimpleMacTableMgr (running)
// Configuration:
// Option       Value
// ------------ -----------------------------
// MAC          10:11:22:33:44:55 1 Ethernet3
//
// Status:
// Data                    Value
// ----------------------- -----
// 10:11:22:33:44:55       1      <--- Status keeps all MAC<->vlan mappings
// initialized?            yes

// (config-daemon-SimpleMacTableMgr)#show mac address-table static
//           Mac Address Table
// ------------------------------------------------------------------
//
// Vlan    Mac Address       Type        Ports      Moves   Last Move
// ----    -----------       ----        -----      -----   ---------
//    1    1011.2233.4455    STATIC      Et3

// Step 5: Remove an existing MAC entry by configuring an empty vlan and interface.
// (config-daemon-SimpleMacTableMgr)#option MAC value 10:11:22:33:44:55
// (config-daemon-SimpleMacTableMgr)#sh daemon
// Agent: SimpleMacTableMgr (running)
// Configuration:
// Option       Value
// ------------ -----------------
// MAC          10:11:22:33:44:55    <--- most recent MAC config/un-config
//
// Status:
// Data               Value
// ------------------ -----------------
// Deleted MAC        10:11:22:33:44:55
// initialized?       yes
//
// (config-daemon-SimpleMacTableMgr)#sh mac address-table static
//           Mac Address Table
// ------------------------------------------------------------------
//
// Vlan    Mac Address       Type        Ports      Moves   Last Move
// ----    -----------       ----        -----      -----   ---------
// Total Mac Addresses for this criterion: 0

class simple_mac_agent : public eos::agent_handler,
                   public eos::acl_handler,
                   public eos::mac_table_handler {
 public:
    explicit simple_mac_agent(eos::sdk & sdk) :
       eos::agent_handler(sdk.get_agent_mgr()),
       eos::acl_handler(sdk.get_acl_mgr()),
       eos::mac_table_handler(sdk.get_mac_table_mgr()),
       agent_mgr_(sdk.get_agent_mgr()),
       t("SimpleMacAgent") {
          printf("Initializing the MAC agent...\n");
          fflush(stdout);
       }

   void on_initialized() {
      printf("... and we're initialized!\n");
      agent_mgr_->status_set("initialized?", "no");
      // Iterate through all the existing MAC entries in this agent's config
      // and delete them.
      for (eos::mac_table_iter_t key =
              get_mac_table_mgr()->mac_table_iter(); key; ++key) {
         get_mac_table_mgr()->mac_entry_del(*key);
      }
      watch_all_mac_entries(true);
      agent_mgr_->status_set("initialized?", "yes");
      t.trace9(__PRETTY_FUNCTION__);
      t.trace9("... and we're initialized!\n");
   }

   void on_mac_entry_set(eos::mac_entry_t const &entry) {
      t.trace9(__PRETTY_FUNCTION__);
      std::string vlan_id = std::to_string(int(entry.mac_key().vlan_id()));
      std::string eth_addr = entry.mac_key().eth_addr().to_string();
      agent_mgr_->status_set(eth_addr.c_str(),
                             vlan_id.c_str());
   }

   void on_mac_entry_del(eos::mac_key_t const &key) {
      t.trace9(__PRETTY_FUNCTION__);
      std::string vlan_id = std::to_string(int(key.vlan_id()));
      std::string eth_addr = key.eth_addr().to_string();
      agent_mgr_->status_del(eth_addr.c_str());
      agent_mgr_->status_set("Deleted MAC", eth_addr.c_str());
   }

   void on_agent_option(std::string const & name,
                        std::string const & value) {
      t.trace9("%s key=%s, value=%s", __PRETTY_FUNCTION__,
                    name.c_str(), value.c_str());

      std::string input = value;
      bool is_del = false;

      eos::eth_addr_t eth_addr;
      eos::vlan_id_t vlan_id;
      std::set<eos::intf_id_t> intfs;
      try {
         eth_addr = parse_eth_addr(input);
         vlan_id = parse_vlan_id(input);
         intfs = parse_intf_ids(input);

         std::string vlan_id_str = "";
         if (!vlan_id) {
            is_del = true;
            vlan_id_str = agent_mgr_->status(eth_addr.to_string());
            vlan_id = eos::vlan_id_t(stoi(vlan_id_str));
         }

      } catch (...) {
         return;
      }
      // Build a mac_key_t object from an Ethernet address and a VLAN id.
      eos::mac_key_t mac_key = eos::mac_key_t(vlan_id, eth_addr);

      if (is_del) {
         // Remove the MAC entry with this mac_key_t from the table.
         get_mac_table_mgr()->mac_entry_del(mac_key);
      } else {
         // Add interface (interfaces if multicast).
         eos::mac_entry_t mac_entry = eos::mac_entry_t(mac_key, intfs);
         // Add the MAC entry to the table!
         get_mac_table_mgr()->mac_entry_set(mac_entry);
      }
   }

   std::string next_token(std::string &inputLine) {
      while(inputLine[0] == ' ') { inputLine.erase(0,1); }
      return inputLine.substr(0, inputLine.find(' '));
   }

   bool parse_is_add(std::string &inputLine) {
      std::string substr = next_token(inputLine);
      if (substr == "no") {
         inputLine.erase(0, substr.length() + 1);
         return false;
      }
      return true;
   }

   eos::eth_addr_t parse_eth_addr(std::string &inputLine) {
      std::string substr = next_token(inputLine);
      try {
         eos::eth_addr_t eth_addr = eos::eth_addr_t(substr);
         inputLine.erase(0, substr.length() + 1);
         return eth_addr;
      } catch (...) {
         printf("! Invalid MAC address specified.\n");
         fflush(stdout);
         throw;
      }
      return eos::eth_addr_t();
   }

   eos::vlan_id_t parse_vlan_id(std::string &inputLine) {
      std::string substr = next_token(inputLine);
      if(substr.empty()) {
         eos::vlan_id_t vlan_id = eos::vlan_id_t();
         return vlan_id;
      }
      try {
         eos::vlan_id_t vlan_id = eos::vlan_id_t(stoi(substr));
         inputLine.erase(0, substr.length() + 1);
         return vlan_id;
      } catch (...) {
         printf("! Invalid Vlan Id specified.\n");
         fflush(stdout);
         throw;
      }
      return eos::vlan_id_t();
   }

   std::set<eos::intf_id_t> parse_intf_ids(std::string &inputLine) {
      std::set<eos::intf_id_t> interfaces;
      while (true) {
         if (inputLine.length() == 0) {
            return interfaces;
         }
         std::string substr = next_token(inputLine);
         try {
            eos::intf_id_t intf(substr);
            interfaces.insert(intf);
            inputLine.erase(0, substr.length() + 1);
         } catch (...) {
            printf("! Invalid interface specified.\n");
            fflush(stdout);
            throw;
         }
      }
      return interfaces;
   }


 private:
   eos::agent_mgr *agent_mgr_;
   eos::tracer t;
};

int main(int argc, char **argv) {
   eos::sdk sdk;
   simple_mac_agent sm(sdk);
   sdk.main_loop(argc, argv);
}
