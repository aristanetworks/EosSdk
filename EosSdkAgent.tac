// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

<<= TacModule("Agent::CAgent");
<<= TacModule("EthIntf::EthIntf");
<<= TacModule("Sysdb::EntityManager");

<<= TacModule("SdkSm");

// Fwd.h contains forward declarations for non-TACC types.
<<= CppInlineInclude("Fwd.h");

EOS : Tac::Namespace {

Agent : Tac::Type( name ) : AgentBase::CAgent {
   `allowsNotifiee=false;
   `hasFactoryFunction;
   `allowsDirInstantiation;

   ethIntfConfigDir : Interface::EthIntfConfigDir::Ptr;
   ethIntfStatusDir : Interface::EthIntfStatusDir::PtrConst;
   ethPhyIntfConfigDir : Interface::EthPhyIntfConfigDir::Ptr;
   ethPhyIntfStatusDir : Interface::EthPhyIntfStatusDir::PtrConst;

   sdk : SDK::RawPtr;
   sdkSm : SdkSm[name];

   doInit : extern invasive overriding void();
   doMountsComplete : extern invasive overriding void(
         mountStatus : Sysdb::MountStatus,
         em : Sysdb::EntityManager::Ptr);
}

}  // namespace EOS

<<= CppBlock("EosSdkAgent.tin");
