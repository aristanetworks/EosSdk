// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOSSDK_FWD_H
#define EOSSDK_FWD_H

// From Tac/PtrInterface.h
namespace Tac {
   class PtrInterface;
}

namespace EosSdk {
   class SDK;
   class Handlers;
   class IntfHandler;
   class EthPhyIntfHandler;

   typedef double Seconds;
   typedef uint32_t U32;
   typedef uint16_t U16;

   typedef void (*EosSdkInitFunc)(SDK*);
}

#endif // EOSSDK_FWD_H
