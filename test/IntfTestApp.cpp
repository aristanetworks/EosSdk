// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <iostream>
#include <sstream>

#include <EosSdk/EosSdk.h>

class IntfHandler : public EOS::IntfHandler {
 public:
   IntfHandler(EOS::SDK *sdk) : sdk_(sdk) {
   }

   void onAdminEnabled(const EOS::IntfId& intfId, bool adminEnabled) {
      std::cout << "onAdminEnabled( " << intfId << " ), adminEnabled is "
                << adminEnabled << std::endl;
      std::ostringstream desc;
      desc << "Admin enabled is " << adminEnabled;
      sdk_->intfConfig(intfId).descriptionIs( desc.str() );
   }
   
   void onAdminDisabledReason(const EOS::IntfId& intfId,
                              EOS::AdminDisabledReason reason) {
      std::cout << "onAdminDisabledReason( " << intfId
                << " ), adminDisabledReason is " << reason << std::endl;
   }

   void onOperStatus(const EOS::IntfId & intfId, EOS::OperStatus status) {
      std::cout << "onOperStatus( " << intfId << " ), operStatus is "
                << status << std::endl;
      std::ostringstream desc;
      desc << "Oper status is " << status;
      sdk_->intfConfig(intfId).descriptionIs( desc.str() );
   }
   
   void onDeletion(const EOS::IntfId & intfId) {
      std::cout << "onDeletion( " << intfId << " )" << std::endl;
   }

 private:
   EOS::SDK *sdk_;
};

class Handlers : public EOS::Handlers {
 public:
   Handlers(EOS::SDK *sdk) : sdk_(sdk), intfHandler_(NULL) {
   }
   
   IntfHandler* handleIntfCreation(const EOS::IntfStatus& status) {
      std::cout << "handleIntfCreation " << status.intfId() << std::endl;
      if( !intfHandler_ ) {
         intfHandler_ = new IntfHandler(sdk_);
      }
      intfHandler_->onOperStatus( status.intfId(), status.operStatus() );
      return intfHandler_;
   }

 private:
   EOS::SDK *sdk_;
   IntfHandler *intfHandler_;
};


extern "C" {
void EosSdkInit(EOS::SDK* sdk) {
   sdk->registerHandlers( "IntfTest", new Handlers(sdk) );
}
}
