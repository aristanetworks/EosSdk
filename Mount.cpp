// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <EosSdk/Mount.h>
#include <EosSdk/panic.h>
#include <Tac/Tracing.h>
DEFAULT_TRACE_HANDLE( "EosSdkMount" )

namespace eos {

static std::list<MountHandler *> mountHandlerList;
static bool initializationComplete;

MountHandler::MountHandler() {
   if( initializationComplete ) {
      panic("attempt to manage additional state after agent initialization");
   }
   initialized = false;
   TRACE0( __PRETTY_FUNCTION__ << " registering new mount handler" );
   mountHandlerList.push_front( this );   
}

void askAllMountHandlersToDoTheirMounts( const Sysdb::MountGroup::Ptr & mg ) {
   TRACE0( __PRETTY_FUNCTION__ );
   initializationComplete = true;
   for (auto i = mountHandlerList.begin(); i!=mountHandlerList.end(); ++i) {
      (*i)->doMounts( mg );
   }
}

void notifyAllMountHandlersThatAllMountsAreComplete(
      const Sysdb::EntityManager::Ptr & em ) {
   TRACE0( __PRETTY_FUNCTION__ );
   // First let all MountHandlers setup their initial state now
   // that all mounts are complete
   for( auto i = mountHandlerList.begin(); i!=mountHandlerList.end(); ++i) {
      (*i)->onMountsComplete( em );
      (*i)->initialized = true;
   }
   // Second, notify all MountHandlers that they're initialized. This
   // has to happen in a second phase so that MountHandlers can call
   // each other once initialized.
   for( auto i = mountHandlerList.begin(); i!=mountHandlerList.end(); ++i) {
      (*i)->handleInitialized();
   }

}

};
