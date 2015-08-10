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


#define BUF_SIZE 1024

// Our agent! This program listens to stdin, and when a MAC entry is
// entered, applies (or removes) it as a static MAC entry on a given interface (or
// set of interfaces). Additionally, MAC table handlers will print MAC entry
// information to stdout whenever a unicast MAC entry is added or removed.


class simple_mac_agent : public eos::agent_handler,
                   public eos::fd_handler,
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
      printf(
            "Input format should be: [no] <MAC address> <VLAN ID> [<interface>,]\n");
      printf("Ctrl-D or \"exit\" to exit\n");
      fflush(stdout);
      // All state has been sync'd with Sysdb. We're good to go!
      // Watch stdin:
      watch_readable(0, true);
      watch_all_mac_entries(true);
   }

   void on_mac_entry_set(eos::mac_entry_t const &entry) {
      t.trace9(__PRETTY_FUNCTION__);
      printf("Unicast MAC entry set: %s\n", entry.to_string().c_str());
      fflush(stdout);
   }

   void on_mac_entry_del(eos::mac_key_t const &key) {
      t.trace9(__PRETTY_FUNCTION__);
      printf("Unicast MAC entry with key %s deleted.\n", key.to_string().c_str());
      fflush(stdout);
   }

   void on_readable(int fd) {
      printf("Stdin (fd %d) is readable\n", fd);
      assert(fd == 0);
      char buf[BUF_SIZE];
      int bytes = read(0, buf, BUF_SIZE - 1);
      buf[bytes] = '\0';
      std::string input(buf, bytes-1);
      if (bytes <= 0 || next_token(input) == "exit") {
         printf("Goodbye!\n");
         agent_mgr_->exit();
         return;
      }
      bool is_add = parse_is_add(input);

      eos::eth_addr_t eth_addr;
      eos::vlan_id_t vlan_id;
      std::set<eos::intf_id_t> intfs;
      try {
         eth_addr = parse_eth_addr(input);
         vlan_id = parse_vlan_id(input);
         intfs = parse_intf_ids(input);
      } catch (...) {
         return;
      }

      // Build a mac_key_t object from an Ethernet address and a VLAN id.
      eos::mac_key_t mac_key = eos::mac_key_t(vlan_id, eth_addr);
      if (is_add) {
         // Add interface (interfaces if multicast).
         eos::mac_entry_t mac_entry = eos::mac_entry_t(mac_key, intfs);
         // Set the MAC entry as persistent.
         mac_entry.persistent_is(true);

         // Add the MAC entry to the table!
         get_mac_table_mgr()->mac_entry_set(mac_entry);
      } else {
         // Remove the MAC entry with this mac_key_t from the table.
         get_mac_table_mgr()->mac_entry_del(mac_key);
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
