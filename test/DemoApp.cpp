// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <iostream>

#include <EosSdk/EosSdk.h>

extern "C" {
void EosSdkInit(EosSdk::SDK* sdk) {
   std::cout << "Hello world!" << std::endl;
}
}
