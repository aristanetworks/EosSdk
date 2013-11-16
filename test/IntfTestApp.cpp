// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <iostream>

#include <EosSdk/EosSdk.h>

class IntfHandler : public EOS::IntfHandler {
 public:
   void onOperStatus(const EOS::IntfId & intfId, EOS::OperStatus status) {
      std::cout << "onOperStatus( " << intfId << " ), operStatus is "
                << status << std::endl;
   }

   void onDeletion(const EOS::IntfId & intfId) {
      std::cout << "onDeletion( " << intfId << " )" << std::endl;
   }
};

class Handlers : public EOS::Handlers {
 public:
   IntfHandler* handleIntfCreation(const EOS::IntfStatus& status) {
      std::cout << "handleIntfCreation " << status.intfId() << std::endl;
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
void EosSdkInit(EOS::SDK* sdk) {
   sdk->registerHandlers( "IntfTest", new Handlers() );
}
}
