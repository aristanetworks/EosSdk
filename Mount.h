// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOSSDK_MOUNT_H
#define EOSSDK_MOUNT_H

#include <list>
#include <Sysdb/EntityManager.h>

#include <eos/base.h>

namespace eos {

class EOS_SDK_INTERNAL MountHandler {
 public:
   // This constructor shouldn't be public, but it's accessed from the
   // GOpenFlow SDK implementation.
   MountHandler();
   virtual void doMounts( const Sysdb::MountGroup::Ptr & mg ) = 0;
   virtual void onMountsComplete( const Sysdb::EntityManager::Ptr & em ) = 0;
   virtual void handleInitialized() = 0;
   bool initialized;
};

// Implementation function called during agent startup.
void askAllMountHandlersToDoTheirMounts( const Sysdb::MountGroup::Ptr & mg );
void notifyAllMountHandlersThatAllMountsAreComplete(
      const Sysdb::EntityManager::Ptr & em );

};

#endif // EOSSDK_MOUNT_H
