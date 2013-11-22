// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

<<= TacModule("Intf::Intf");

eos : Tac::Namespace {

IntfConfigSm : Tac::Type(intfConfig) : Tac::Constrainer {
   tacFwkActivity = 0;
   
   intfConfig : in Interface::IntfConfig::PtrConst;
      
   intfId : : intfConfig::intfId;

   handleAdminEnabled : extern invasive void();
   intfConfig::adminEnabledStateLocal => handleAdminEnabled();
}

IntfStatusSm : Tac::Type(intfStatus) : Tac::Constrainer {
   tacFwkActivity = 0;

   intfStatus : in Interface::IntfStatus::PtrConst;

   intfId : : intfStatus::intfId;
      
   handleOperStatus : extern invasive void();
   intfStatus::operStatus => handleOperStatus();
}

IntfMgrSm : Tac::Type(allIntfConfigDir,
                      allIntfStatusDir) : Tac::Constrainer {
   tacFwkActivity = 0;
   
   allIntfConfigDir : in Interface::AllIntfConfigDir::PtrConst;
   handleIntfConfig : extern invasive void(intfId : Arnet::IntfId);
   handleIntfConfig : extern invasive overloading void();
   allIntfConfigDir::intfConfig[] => initially handleIntfConfig();
   allIntfConfigDir::intfConfig[intfId] => handleIntfConfig(intfId);
   intfConfigSm : IntfConfigSm[intfId];
   
   allIntfStatusDir : in Interface::AllIntfStatusDir::PtrConst;
   handleIntfStatus : extern invasive void(intfId : Arnet::IntfId);
   handleIntfStatus : extern invasive overloading void();
   allIntfStatusDir::intfStatus[] => initially handleIntfStatus();
   allIntfStatusDir::intfStatus[intfId] => handleIntfStatus(intfId);
   intfStatusSm : IntfStatusSm[intfId];
}

}
