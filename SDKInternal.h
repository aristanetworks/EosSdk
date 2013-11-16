// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOSSDK_SDKINTERNAL_H
#define EOSSDK_SDKINTERNAL_H

#include <Arnet/IntfId.h>
#include <EthIntf/EthIntf.h>

#include "EosSdk.h"
#include "EosSdkAgent.h"

// This file is not part of the public SDK.

namespace EOS {

static Arnet::IntfId convert(const IntfId& intfId) {
   return Arnet::IntfId(intfId.name());  // TODO use a U32 instead.
}

AdminDisabledReason convertAdminDisabledReason( const Tac::String& reason );

class SDKInternal {
 public:
   SDKInternal(Agent* const agent) : agent_(agent) {
   }

   SDK* createSDK() {
      return new SDK(this);
   }

   Interface::EthIntfConfig::PtrConst ethIntfConfig(const IntfId& intfId) {
      return agent_->ethIntfConfigDir()->intfConfig(convert(intfId));
   }

   Interface::EthIntfStatus::PtrConst ethIntfStatus(const IntfId& intfId) {
      return agent_->ethIntfStatusDir()->intfStatus(convert(intfId));
   }

   Interface::EthPhyIntfConfig::PtrConst ethPhyIntfConfig(const IntfId& intfId) {
      return agent_->ethPhyIntfConfigDir()->intfConfig(convert(intfId));
   }

   Interface::EthPhyIntfStatus::PtrConst ethPhyIntfStatus(const IntfId& intfId) {
      return agent_->ethPhyIntfStatusDir()->intfStatus(convert(intfId));
   }

   void registerHandlers(const std::string& name, Handlers* handlers) {
      SdkSm::Ptr sm = agent_->sdkSmIs( agent_->sdk(), Tac::Name( name ), handlers,
                                       agent_->ethIntfConfigDir(),
                                       agent_->ethIntfStatusDir(),
                                       agent_->ethPhyIntfConfigDir(),
                                       agent_->ethPhyIntfStatusDir() );
      for( auto intf = agent_->ethIntfConfigDir()->intfConfigIteratorConst();
           intf; ++intf ) {
         sm->handleEthIntfConfigDir( intf->intfId() );
      }
   }

   void unregisterHandlers(const std::string& name) {
      agent_->sdkSmDel( Tac::Name( name ) );
   }

 private:
   Agent* const agent_;

   // Disable copy constructor and assignment operator.
   SDKInternal(const SDKInternal&);
   SDKInternal& operator=(const SDKInternal&);
};

}

#endif // EOSSDK_SDKINTERNAL_H

