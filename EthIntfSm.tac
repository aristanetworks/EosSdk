// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

<<= TacModule("EthIntf::EthIntf");

// Fwd.h contains forward declarations for non-TACC types.
<<= CppInlineInclude("Fwd.h");

EOS : Tac::Namespace {

IntfHandler : extern Tac::Type {
   `allowsIndirectRef;
}

EthPhyIntfHandler : extern Tac::Type {
   `allowsIndirectRef;
}

EthIntfConfigSm : Tac::Type(handler, intfId, ethIntfConfig) : Tac::Constrainer {
   tacFwkActivity = 0;
   handler : IntfHandler::RawPtr;
   intfId : Arnet::IntfId;
   ethIntfConfig : in Interface::EthIntfConfig::PtrConst;

   handleDescription : extern invasive void();
   ethIntfConfig::description => handleDescription();
   handleAdminEnabled : extern invasive void();
   ethIntfConfig::adminEnabledStateLocal => handleAdminEnabled();
   handleAdminDisabledReason : extern invasive void();
   ethIntfConfig::enabledStateReason => handleAdminDisabledReason();
}

EthIntfStatusSm : Tac::Type(handler, intfId, ethIntfStatus) : Tac::Constrainer {
   tacFwkActivity = 0;
   handler : IntfHandler::RawPtr;
   intfId : Arnet::IntfId;
   ethIntfStatus : in Interface::EthIntfStatus::PtrConst;

   handleOperStatus : extern invasive void();
   ethIntfStatus::operStatus => handleOperStatus();
   // TBD
}

EthPhyIntfConfigSm : Tac::Type(handler, intfId,
                               ethPhyIntfConfig) : Tac::Constrainer {
   tacFwkActivity = 0;
   handler : EthPhyIntfHandler::RawPtr;
   intfId : Arnet::IntfId;
   ethPhyIntfConfig : in Interface::EthPhyIntfConfig::PtrConst;
   // TBD
}

EthPhyIntfStatusSm : Tac::Type(handler, intfId,
                               ethPhyIntfStatus) : Tac::Constrainer {
   tacFwkActivity = 0;
   handler : EthPhyIntfHandler::RawPtr;
   intfId : Arnet::IntfId;
   ethPhyIntfStatus : in Interface::EthPhyIntfStatus::PtrConst;
   // TBD
}

}

<<= CppBlock("EthIntfSm.tin");
