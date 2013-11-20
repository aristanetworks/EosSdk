// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <EosSdk/Mount.h>
#include <EosSdk/panic.h>

namespace eos {

static std::list<mount_handler *> mount_handler_list;
static bool initialization_complete;

mount_handler::mount_handler() {
   if( initialization_complete ) {
      panic("attempt to manage additional state after agent initialization");
   }
   mount_handler_list.push_front( this );   
}

void askAllMountHandlersToDoTheirMounts( const Sysdb::MountGroup::Ptr & mg ) {
   initialization_complete = true;
   for (auto i = mount_handler_list.begin(); i!=mount_handler_list.end(); ++i) {
      (*i)->doMounts( mg );
   }
}

void notifyAllMountHandlersThatAllMountsAreComplete(
      const Sysdb::EntityManager::Ptr & em ) {
   for( auto i = mount_handler_list.begin(); i!=mount_handler_list.end(); ++i) {
      (*i)->onMountsComplete( em );
   }
}

};
