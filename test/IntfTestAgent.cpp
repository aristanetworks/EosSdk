// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/intf.h>
#include <eos/types.h>

#include <stdio.h>

#include <Tac/Tracing.h>
DEFAULT_TRACE_HANDLE( "IntfTestAgent" )


eos::intf_mgr * intf_mgr;

class IntfTestHandler : public eos::intf_handler {
 public:
   IntfTestHandler(){
      TRACE0( __PRETTY_FUNCTION__ );  
      watch_all_intfs( true );
   }

   static bool handle_initial_intf( eos::intf_id_t i, void * me_void ){
      IntfTestHandler * me = (IntfTestHandler *) me_void;
      char name[eos::INTF_NAME_MAX];
      i.to_string(name, sizeof(name));
      TRACE1( "Handling initial interface " << name );
      me->on_oper_status( i, intf_mgr->oper_status( i ) );
      return true;
   }

   void on_initialized() {
      TRACE0( __PRETTY_FUNCTION__ );
      intf_mgr->intf_foreach( handle_initial_intf, this );
   }
   
   void on_create(eos::intf_id_t i) {
      char name[eos::INTF_NAME_MAX];
      i.to_string(name, sizeof(name));
      TRACE1("on_create: " << name << " showed up\n");
      on_oper_status(i, intf_mgr->oper_status(i));
   }

   void on_delete(eos::intf_id_t i) {
      char name[eos::INTF_NAME_MAX];
      i.to_string(name, sizeof(name));
      TRACE1("on_delete: " << name << " went away" );
   }

   void on_oper_status(eos::intf_id_t i, eos::oper_status_t status) {
      char name[eos::INTF_NAME_MAX];
      i.to_string(name, sizeof(name));
      TRACE1("on_oper_status: " << name << " is now " << status );
      char buf[100];
      snprintf(buf, sizeof(buf), "Oper status is %d", status);
      intf_mgr->description_is(i, buf);
   }

};

int main(int argc, char ** argv) {
   TRACE0( "Agent started" );
   intf_mgr = eos::get_intf_mgr();
   IntfTestHandler handler;
   TRACE0( "Handing over control of the main loop" );
   eos::agent_main_loop("IntfTestAgent", argc, argv);
}
