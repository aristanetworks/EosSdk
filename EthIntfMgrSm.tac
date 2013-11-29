// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

<<= TacModule("EthIntf::EthIntf");

eos : Tac::Namespace {

EthIntfMgrSm : Tac::Type(ethPhyIntfConfigDir, ethPhyIntfStatusDir,
                         ethIntfConfigDir, ethIntfStatusDir) : Tac::Constrainer {
   tacFwkActivity = 0;

   ethPhyIntfConfigDir : Interface::EthPhyIntfConfigDir::Ptr;
   ethPhyIntfStatusDir : in Interface::EthPhyIntfStatusDir::PtrConst;
   ethIntfConfigDir : Interface::EthIntfConfigDir::Ptr;
   ethIntfStatusDir : in Interface::EthIntfStatusDir::PtrConst;
   
}

}