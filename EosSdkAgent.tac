// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

<<= TacModule("Agent::CAgent");
<<= TacModule("EthIntf::EthIntf");
<<= TacModule("Sysdb::EntityManager");

EosSdk : Tac::Namespace {

Agent : Tac::Type( name ) : AgentBase::CAgent {
   `allowsNotifiee=false;
   `hasFactoryFunction;
   `allowsDirInstantiation;

   ethPhyIntfStatusDir : Interface::EthPhyIntfStatusDir::PtrConst;

   doInit : extern invasive overriding void();
   doMountsComplete : extern invasive overriding void(
         mountStatus : Sysdb::MountStatus,
         em : Sysdb::EntityManager::Ptr);
}

}  // namespace EosSdk

<<= CppBlock("EosSdkAgent.tin");
