// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/intf.h>
#include <eos/eth_intf.h>
#include <eos/types.h>

#include <stdio.h>

#include <Tac/Tracing.h>
DEFAULT_TRACE_HANDLE( "EthIntfTestAgent" )

eos::intf_mgr * intf_mgr;
eos::eth_intf_mgr * eth_intf_mgr;

class EthIntfTestHandler : public eos::eth_intf_handler {
 public:
   EthIntfTestHandler(){
      TRACE0( __PRETTY_FUNCTION__ );
      watch_all_intfs( true );
   }

   static bool handle_initial_eth_intf( eos::intf_id_t i, void * me_void ){
      EthIntfTestHandler * me = (EthIntfTestHandler *) me_void;
      TRACE1( "Handling initial interface " << i.to_string() );
      me->on_eth_addr( i, eth_intf_mgr->eth_addr( i ) );
      return true;
   }

   void on_initialized() {
      TRACE0( __PRETTY_FUNCTION__ );
      eth_intf_mgr->eth_intf_foreach( handle_initial_eth_intf, this );
   }

   void on_create(eos::intf_id_t i) {
      TRACE1("on_create: " << i.to_string() << " showed up\n");
      on_eth_addr(i, eth_intf_mgr->eth_addr(i));
   }

   void on_delete(eos::intf_id_t i) {
      TRACE1("on_delete: " << i.to_string() << " went away");
   }

   void on_eth_addr(eos::intf_id_t i, eos::eth_addr_t eth_addr) {
      std::string mac = eth_addr.to_string();
      TRACE1("on_eth_addr: " << i.to_string() << " is now " << mac);
      char buf[100];
      snprintf(buf, sizeof(buf), "Eth addr is now %s", mac.c_str());
      intf_mgr->description_is(i, buf);
   }

};

int main(int argc, char ** argv) {
   TRACE0( "Agent started" );
   intf_mgr = eos::get_intf_mgr();
   eth_intf_mgr = eos::get_eth_intf_mgr();
   EthIntfTestHandler handler;
   TRACE0( "Handing over control of the main loop" );
   eos::agent_main_loop("EthIntfTestAgent", argc, argv);
}
