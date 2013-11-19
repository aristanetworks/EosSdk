// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

<<= TacModule("Arnet::IntfId");
<<= TacModule("EthIntf::EthIntf");
<<= TacModule("Lag::EthLagIntf");

<<= TacModule("EthIntfSm");

// Fwd.h contains forward declarations for non-TACC types.
<<= CppInlineInclude("Fwd.h");

EOS : Tac::Namespace {

SDK : extern Tac::Type {
   `allowsIndirectRef;
}

Handlers : extern Tac::Type {
   `allowsIndirectRef;
}

SdkSm : Tac::Type(sdk,
                  name,
                  handlers,
                  ethIntfConfigDir,
                  ethIntfStatusDir,
                  ethPhyIntfConfigDir,
                  ethPhyIntfStatusDir,
                  ethLagIntfConfigDir,
                  ethLagIntfStatusDir) : Tac::Constrainer {
   tacFwkActivity = 0;

   sdk : SDK::RawPtr;
   name : Tac::Name;
   handlers : Handlers::RawPtr;

   ethIntfConfigDir : inout Interface::EthIntfConfigDir::Ptr;
   handleEthIntfConfigDir : extern invasive void(intfId : Arnet::IntfId);
   ethIntfConfigDir::intfConfig[intfId] => handleEthIntfConfigDir(intfId);
   ethIntfConfigSm : EthIntfConfigSm[intfId];

   ethIntfStatusDir : in Interface::EthIntfStatusDir::PtrConst;
   handleEthIntfStatusDir : extern invasive void(intfId : Arnet::IntfId);
   ethIntfStatusDir::intfStatus[intfId] => handleEthIntfStatusDir(intfId);
   ethIntfStatusSm : EthIntfStatusSm[intfId];

   ethPhyIntfConfigDir : inout Interface::EthPhyIntfConfigDir::Ptr;
   handleEthPhyIntfConfigDir : extern invasive void(intfId : Arnet::IntfId);
   ethPhyIntfConfigDir::intfConfig[intfId] => handleEthPhyIntfConfigDir(intfId);
   ethPhyIntfConfigSm : EthPhyIntfConfigSm[intfId];

   ethPhyIntfStatusDir : in Interface::EthPhyIntfStatusDir::PtrConst;
   handleEthPhyIntfStatusDir : extern invasive void(intfId : Arnet::IntfId);
   ethPhyIntfStatusDir::intfStatus[intfId] => handleEthPhyIntfStatusDir(intfId);
   ethPhyIntfStatusSm : EthPhyIntfStatusSm[intfId];

   ethLagIntfConfigDir : inout Interface::EthLagIntfConfigDir::Ptr;
   handleEthLagIntfConfigDir : extern invasive void(intfId : Arnet::IntfId);
   ethLagIntfConfigDir::intfConfig[intfId] => handleEthLagIntfConfigDir(intfId);
   ethLagIntfConfigSm : EthLagIntfConfigSm[intfId];

   ethLagIntfStatusDir : in Interface::EthLagIntfStatusDir::PtrConst;
   handleEthLagIntfStatusDir : extern invasive void(intfId : Arnet::IntfId);
   ethLagIntfStatusDir::intfStatus[intfId] => handleEthLagIntfStatusDir(intfId);
   ethLagIntfStatusSm : EthLagIntfStatusSm[intfId];
}

}  // namespace EOS

<<= CppBlock("SdkSm.tin");
