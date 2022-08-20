// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/intf.h>
#include <eos/eth_intf.h>
#include <eos/eth_lag_intf.h>
#include <eos/eth_phy_intf.h>
#include <eos/ip.h>
#include <eos/ip_intf.h>
#include <eos/sdk.h>
#include <eos/tracing.h>
#include <eos/panic.h>


// This agent reacts to a variety of interface create/delete
// events and traces when one of these events happen. It helps
// understand how the various interface modules work together and in
// which order their events occur.
//
// Make the agent using a 32-bit linux build environment:
//    bash# g++ -leos -std=gnu++14 IntfReactor.cpp -o IntfReactor
// Now you can transfer the binary to flash: on an EOS instance with
// EosSdk.i686.rpm installed and run the agent from bash:
//    bash# TRACE=IntfReactor /mnt/flash/IntfReactor
// or from the CLI
//    (conf)# daemon IntfReactor
//    (conf-daemon-IntfReactor)# exec /mnt/flash/IntfReactor
//    (conf-daemon-IntfReactor)# no shutdown


#include <csignal>
static void panic_handler(eos::error const & exception) {
   // This custom panic handler lets us trigger gdb when if an
   // exception happens. If you'd like to test this out, introduce a
   // runtime error into one of the handler methods below, and then
   // run under GDB:
   //
   // bash# gdb ./MyAgent
   // (gdb) set environment TRACE=EosSdk*,IntfReactor
   // (gdb) run
   // 
   // For more info, see
   // https://github.com/aristanetworks/EosSdk/wiki/Debugging-an-SDK-Agent
   std::raise(SIGINT);
   exception.raise();
}

class IntfReactor :
   public eos::agent_handler, public eos::intf_handler,
   public eos::eth_intf_handler, public eos::eth_phy_intf_handler,
   public eos::eth_lag_intf_handler {
 public:
   eos::ip_intf_mgr * ip_intf_mgr;
   explicit IntfReactor(eos::sdk & sdk) 
         : t("IntfReactor"), 
           eos::agent_handler(sdk.get_agent_mgr()),
           eos::intf_handler(sdk.get_intf_mgr()),
           eos::eth_intf_handler(sdk.get_eth_intf_mgr()),
           eos::eth_phy_intf_handler(sdk.get_eth_phy_intf_mgr()),
           eos::eth_lag_intf_handler(sdk.get_eth_lag_intf_mgr()) {
      t.trace0("Constructed agent");
      ip_intf_mgr = sdk.get_ip_intf_mgr();
      watch_all_intfs(true);
      watch_all_eth_intfs(true);
      watch_all_eth_phy_intfs(true);
      watch_all_eth_lag_intfs(true);
      eos::exception_handler_is(panic_handler);
   }

   void on_initialized() {
      t.trace0("Agent initialized");
      update_visible_intfs();
   }

   void on_intf_create(eos::intf_id_t intf) {
      t.trace0("Interface %s created", intf.to_string().c_str());
      update_visible_intfs();
   }
   void on_eth_intf_create(eos::intf_id_t intf) {
      t.trace0("Ethernet interface created %s", intf.to_string().c_str());
      update_visible_intfs();
   }
   void on_eth_phy_intf_create(eos::intf_id_t intf) {
      t.trace0("Physical interface %s created", intf.to_string().c_str());
      update_visible_intfs();
   }
   void on_eth_lag_intf_create(eos::intf_id_t intf) {
      t.trace0("LAG %s created", intf.to_string().c_str());
      update_visible_intfs();
   }

   void on_intf_delete(eos::intf_id_t intf) {
      t.trace0("Interface %s deleted", intf.to_string().c_str());
      update_visible_intfs();
   }
   void on_eth_intf_delete(eos::intf_id_t intf) {
      t.trace0("Ethernet interface deleted %s", intf.to_string().c_str());
      update_visible_intfs();
   }
   void on_eth_phy_intf_delete(eos::intf_id_t intf) {
      t.trace0("Physical interface %s deleted", intf.to_string().c_str());
      update_visible_intfs();
   }
   void on_eth_lag_intf_delete(eos::intf_id_t intf) {
      t.trace0("LAG %s deleted", intf.to_string().c_str());
      update_visible_intfs();
   }

   void on_lag_member_set(eos::intf_id_t lag, eos::intf_id_t member) {
      t.trace0("LAG %s added member %s", lag.to_string().c_str(),
               member.to_string().c_str());
   }
   void on_lag_member_del(eos::intf_id_t lag, eos::intf_id_t member) {
      t.trace0("LAG %s removed member %s", lag.to_string().c_str(),
               member.to_string().c_str());
   }
   void on_lag_intf_speed(eos::intf_id_t lag, uint64_t speed) {
      t.trace0("LAG %s changed speed to %d", lag.to_string().c_str(),
               speed);
   }

   void on_oper_status(eos::intf_id_t intf, eos::oper_status_t status) {
      t.trace0("Oper status for %s is %s", intf.to_string().c_str(),
               status == eos::INTF_OPER_UP ? "up" : 
               status == eos::INTF_OPER_DOWN ? "down" : "null");
   }

   void on_hardware_present(eos::intf_id_t intf, bool present) {
      t.trace0("Hardware presence is %s for interface %s", present,
            intf.to_string().c_str());
   }

   void update_visible_intfs() {
      std::string intf_str;
      intf_str = concat_intf_iter(get_intf_mgr()->intf_iter());
      get_agent_mgr()->status_set("intf_mgr intfs", intf_str);
      t.trace9("intf_mgr intfs: %s", intf_str.c_str());

      intf_str = concat_intf_iter(get_eth_intf_mgr()->eth_intf_iter());
      get_agent_mgr()->status_set("eth_intf_mgr intfs", intf_str);
      t.trace9("eth_intf_mgr intfs: %s", intf_str.c_str());

      intf_str = concat_intf_iter(get_eth_phy_intf_mgr()->eth_phy_intf_iter());
      get_agent_mgr()->status_set("eth_phy_intf_mgr intfs", intf_str);
      t.trace9("eth_phy_intf_mgr intfs: %s", intf_str.c_str());

      intf_str = concat_intf_iter(get_eth_lag_intf_mgr()->eth_lag_intf_iter());
      get_agent_mgr()->status_set("eth_lag_intf_mgr intfs", intf_str);
      t.trace9("eth_lag_intf_mgr intfs: %s", intf_str.c_str());
   }
   
   template <typename IntfIter>
   std::string concat_intf_iter(IntfIter i) {
      // Given an iterator, concatenate all of its values into a
      // string separated by commas
      std::stringstream ss;
      bool first = true;
      for (; i; i++) {
         if (!first) {
            ss << ", ";
         }
         first = false;
         ss << i->to_string();
      }
      return ss.str();
   }

 private:
   eos::tracer t;
};

int main(int argc, char ** argv) {
   eos::sdk sdk;
   IntfReactor ir(sdk);
   sdk.main_loop(argc, argv);
}

