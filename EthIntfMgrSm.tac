// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

<<= TacModule("EthIntf::EthIntf");

eos : Tac::Namespace {

EthIntfStatusSm : Tac::Type(intfStatus) : Tac::Constrainer {
   tacFwkActivity = 0;

   intfStatus : in Interface::EthIntfStatus::PtrConst;

   intfId : : intfStatus::intfId;
   
   handleAddr : extern invasive void();
   intfStatus::addr => handleAddr();
}

EthIntfMgrSm : Tac::Type(ethIntfConfigDir, ethIntfStatusDir) : Tac::Constrainer {
   tacFwkActivity = 0;

   ethIntfConfigDir : Interface::EthIntfConfigDir::Ptr;

   ethIntfStatusDir : in Interface::EthIntfStatusDir::PtrConst;
   handleIntfStatus : extern invasive void(intfId : Arnet::IntfId);
   handleIntfStatus : extern invasive overloading void();
   ethIntfStatusDir::intfStatus[] => initially handleIntfStatus();
   ethIntfStatusDir::intfStatus[intfId] => handleIntfStatus(intfId);
   ethIntfStatusSm : EthIntfStatusSm[intfId];
}

}