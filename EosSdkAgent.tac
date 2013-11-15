// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

<<= TacModule("Agent::CAgent");
<<= TacModule("EthIntf::EthIntf");
<<= TacModule("Sysdb::EntityManager");

// Fwd.h contains forward declarations for non-TACC types.
<<= CppInlineInclude("Fwd.h");

EosSdk : Tac::Namespace {

SDK : extern Tac::Type {
   `allowsIndirectRef;
}

Agent : Tac::Type( name ) : AgentBase::CAgent {
   `allowsNotifiee=false;
   `hasFactoryFunction;
   `allowsDirInstantiation;

   sdk : SDK::RawPtr;
   ethPhyIntfStatusDir : Interface::EthPhyIntfStatusDir::PtrConst;

   doInit : extern invasive overriding void();
   doMountsComplete : extern invasive overriding void(
         mountStatus : Sysdb::MountStatus,
         em : Sysdb::EntityManager::Ptr);
}

}  // namespace EosSdk

<<= CppBlock("EosSdkAgent.tin");
