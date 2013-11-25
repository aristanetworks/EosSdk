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
   for( auto i = mountHandlerList.begin(); i!=mountHandlerList.end(); ++i) {
      (*i)->onMountsComplete( em );
   }
}

};
