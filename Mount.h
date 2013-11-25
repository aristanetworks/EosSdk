// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOSSDK_MOUNT_H
#define EOSSDK_MOUNT_H

#include <list>
#include <Sysdb/EntityManager.h>

namespace eos {

class MountHandler {
 public:
   MountHandler();
   virtual void doMounts( const Sysdb::MountGroup::Ptr & mg ) = 0;
   virtual void onMountsComplete( const Sysdb::EntityManager::Ptr & em ) = 0;
};

// Implementation function called during agent startup.
void askAllMountHandlersToDoTheirMounts( const Sysdb::MountGroup::Ptr & mg );
void notifyAllMountHandlersThatAllMountsAreComplete(
      const Sysdb::EntityManager::Ptr & em );

};

#endif // EOSSDK_MOUNT_H
