// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <iostream>

#include <EosSdk/EosSdk.h>

class IntfHandler : public EosSdk::IntfHandler {
 public:
   void onOperStatus(const EosSdk::IntfId & intfId, EosSdk::OperStatus status) {
      std::cout << "onOperStatus( " << intfId.name() << " ), operStatus is "
                << status;
   }
   
   void onDeletion(const EosSdk::IntfId & intfId) {
      std::cout << "onDeletion( " << intfId.name() << " )";
   }
};

class Handlers : public EosSdk::Handlers {
 public:
   IntfHandler* handleIntfCreation(const EosSdk::IntfStatus& status) {
      std::cout << "handleIntfCreation " << status.intfId().name();
      if( !intfHandler_ ) {
         intfHandler_ = new IntfHandler();
      }
      intfHandler_->onOperStatus( status.intfId(), status.operStatus() );
      return intfHandler_;
   }

 private:
   IntfHandler *intfHandler_;   
};


extern "C" {
void EosSdkInit(EosSdk::SDK* sdk) {
   sdk->registerHandlers( "IntfTest", new Handlers() );
}
}
