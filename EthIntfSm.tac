// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

<<= TacModule("EthIntf::EthIntf");
<<= TacModule("Lag::EthLagIntf");

// Fwd.h contains forward declarations for non-TACC types.
<<= CppInlineInclude("Fwd.h");

EOS : Tac::Namespace {

IntfHandler : extern Tac::Type {
   `allowsIndirectRef;
}

EthPhyIntfHandler : extern Tac::Type {
   `allowsIndirectRef;
}

EthLagIntfHandler : extern Tac::Type {
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
}

EthPhyIntfConfigSm : Tac::Type(handler, intfId,
                               ethPhyIntfConfig) : Tac::Constrainer {
   tacFwkActivity = 0;
   handler : EthPhyIntfHandler::RawPtr;
   intfId : Arnet::IntfId;
   ethPhyIntfConfig : in Interface::EthPhyIntfConfig::PtrConst;

   handleAddr : extern invasive void();
   ethPhyIntfConfig::addr => handleAddr();
   handleLinkModeLocal : extern invasive void();
   ethPhyIntfConfig::linkModeLocal => handleLinkModeLocal();
   handleLoopbackMode : extern invasive void();
   ethPhyIntfConfig::loopbackMode => handleLoopbackMode();
   handleTimestampMode : extern invasive void();
   ethPhyIntfConfig::timestampMode => handleTimestampMode();
}

EthPhyIntfStatusSm : Tac::Type(handler, intfId,
                               ethPhyIntfStatus) : Tac::Constrainer {
   tacFwkActivity = 0;
   handler : EthPhyIntfHandler::RawPtr;
   intfId : Arnet::IntfId;
   ethPhyIntfStatus : in Interface::EthPhyIntfStatus::PtrConst;
   // TBD
}

EthLagIntfConfigSm : Tac::Type(handler, intfId,
                               ethLagIntfConfig) : Tac::Constrainer {
   tacFwkActivity = 0;
   handler : EthLagIntfHandler::RawPtr;
   intfId : Arnet::IntfId;
   ethLagIntfConfig : in Interface::EthLagIntfConfig::PtrConst;
   // TBD
}

EthLagIntfStatusSm : Tac::Type(handler, intfId,
                               ethLagIntfStatus) : Tac::Constrainer {
   tacFwkActivity = 0;
   handler : EthLagIntfHandler::RawPtr;
   intfId : Arnet::IntfId;
   ethLagIntfStatus : in Interface::EthLagIntfStatus::PtrConst;
   // TBD
}

}

<<= CppBlock("EthIntfSm.tin");
