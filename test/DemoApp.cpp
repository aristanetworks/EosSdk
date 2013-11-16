// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <iostream>

#include <EosSdk/EosSdk.h>

class MyIntfHandler : public EosSdk::IntfHandler {
   virtual void onDescription(const EosSdk::IntfId& intfId,
                              const std::string& descr) {
      std::cout << "New description for " << intfId.name()
         << " is " << descr << std::endl;
   }
};

class MyHandlers : public EosSdk::Handlers {
   virtual MyIntfHandler* handleIntfCreation(const EosSdk::IntfStatus& status) {
      return new MyIntfHandler();
   }
};

extern "C" {
void EosSdkInit(EosSdk::SDK* sdk) {
   std::cout << "Hello world!" << std::endl;
   sdk->registerHandlers("myHandler", new MyHandlers());
}
}
