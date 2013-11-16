// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "EosSdk.h"

#include <Tac/PtrInterface.h>
#include <Arnet/EthAddr.h>
#include <Arnet/IntfId.h>
#include <EthIntf/EthIntf.h>

#include "SDKInternal.h"

namespace EosSdk {

const EthAddr EthAddr::kZero = EthAddr(0x0000, 0x0000, 0x0000);
const EthAddr EthAddr::kBroadcast = EthAddr(0xffff, 0xffff, 0xffff);
const EthAddr EthAddr::kStp = EthAddr(0x0180, 0xc200, 0x0000);
const EthAddr EthAddr::kPvst = EthAddr(0x0100, 0x0ccc, 0xcccd);
const EthAddr EthAddr::kSlowProto = EthAddr(0x0180, 0xc200, 0x0002);
const EthAddr EthAddr::kLldp = EthAddr(0x0180, 0xc200, 0x000e);
const EthAddr EthAddr::kIpMcastBase = EthAddr(0x0100, 0x5e00, 0x0000);
const EthAddr EthAddr::kVrrpIpv4Base = EthAddr(0x0000, 0x5e00, 0x0100);
const EthAddr EthAddr::kVrrpIpv6Base = EthAddr(0x0000, 0x5e00, 0x0200);
const EthAddr EthAddr::kPtp = EthAddr(0x011b, 0x1900, 0x0000);
const EthAddr EthAddr::kPtpPeerDelay = EthAddr(0x0180, 0xc200, 0x000e);
const EthAddr EthAddr::kIsisL1IS = EthAddr(0x0180, 0xc200, 0x0014);
const EthAddr EthAddr::kIsisL2IS = EthAddr(0x0180, 0xc200, 0x0015);
const EthAddr EthAddr::kIsisAllIS = EthAddr(0x0900, 0x2b00, 0x0005);

static std::string convert(const Tac::String& s) {
   return s.stdString();
}

static EthAddr convert(Arnet::EthAddr addr) {
   return EthAddr(addr.word0(), addr.word1(), addr.word2());
}

// --- //
// SDK //
// --- //

void SDK::registerHandlers(const std::string& name, Handlers* handlers) {
   Handlers* prev = handlers_[name];
   if (prev) {
      // TODO: throw an exception?
      return;
   }
   handlers_[name] = handlers;
   internal_->registerHandlers(name, handlers);
};

void SDK::unregisterHandlers(const std::string& name) {
   handlers_.erase(name);
   internal_->unregisterHandlers(name);
}

// ---------- //
// IntfConfig //
// ---------- //

std::string IntfConfig::description() const {
   return convert(sdk_->internal_->ethIntfConfig(intfId_)->description());
}

bool IntfConfig::adminEnabled() const {
   return sdk_->internal_->ethIntfConfig(intfId_)->adminEnabled();
}

AdminDisabledReason IntfConfig::adminDisabledReason() const {
   Tac::String reason =
      sdk_->internal_->ethIntfConfig(intfId_)->enabledStateReason();
   return convertAdminDisabledReason(reason);
}

// ---------- //
// IntfStatus //
// ---------- //

OperStatus IntfStatus::operStatus() const {
   return static_cast<OperStatus>(
         static_cast<int>(sdk_->internal_->ethIntfStatus(intfId_)->operStatus()));
}

// ---------------- //
// EthPhyIntfConfig //
// ---------------- //

EthAddr EthPhyIntfConfig::addr() const {
   return convert(sdk_->internal_->ethPhyIntfConfig(intfId_)->addr());
}


EthLinkMode EthPhyIntfConfig::linkModeLocal() const {
   return static_cast<EthLinkMode>(static_cast<int>(
         sdk_->internal_->ethPhyIntfConfig(intfId_)->linkModeLocal()));
}

LoopbackMode EthPhyIntfConfig::loopbackMode() const {
   return static_cast<LoopbackMode>(static_cast<int>(
         sdk_->internal_->ethPhyIntfConfig(intfId_)->loopbackMode()));
}

EthTimestampMode EthPhyIntfConfig::timestampMode() const {
   return static_cast<EthTimestampMode>(static_cast<int>(
         sdk_->internal_->ethPhyIntfConfig(intfId_)->timestampMode()));
}

// ---------------- //
// EthPhyIntfStatus //
// ---------------- //

EthAddr EthPhyIntfStatus::addr() const {
   return convert(sdk_->internal_->ethPhyIntfStatus(intfId_)->addr());
}

EthAddr EthPhyIntfStatus::burnedInAddr() const {
   return convert(sdk_->internal_->ethPhyIntfStatus(intfId_)->burnedInAddr());
}

LinkStatus EthPhyIntfStatus::linkStatus() const {
   return static_cast<LinkStatus>(
        static_cast<int>(sdk_->internal_->ethPhyIntfStatus(intfId_)->linkStatus()));
}


bool EthPhyIntfStatus::macRxRemoteFault() const {
   return sdk_->internal_->ethPhyIntfStatus(intfId_)->macRxRemoteFault();
}

U32 EthPhyIntfStatus::macRxRemoteFaultChanges() const {
   return sdk_->internal_->ethPhyIntfStatus(intfId_)->macRxRemoteFaultChanges();
}

Seconds EthPhyIntfStatus::lastMacRxRemoteFaultChange() const {
   return sdk_->internal_->ethPhyIntfStatus(intfId_)->lastMacRxRemoteFaultChange();
}


bool EthPhyIntfStatus::macRxLocalFault() const {
   return sdk_->internal_->ethPhyIntfStatus(intfId_)->macRxLocalFault();
}

U32 EthPhyIntfStatus::macRxLocalFaultChanges() const {
   return sdk_->internal_->ethPhyIntfStatus(intfId_)->macRxLocalFaultChanges();
}

Seconds EthPhyIntfStatus::lastMacRxLocalFaultChange() const {
   return sdk_->internal_->ethPhyIntfStatus(intfId_)->lastMacRxLocalFaultChange();
}


LocalFaultStatus EthPhyIntfStatus::localFaultStatus() const {
   return static_cast<LocalFaultStatus>(static_cast<int>(
         sdk_->internal_->ethPhyIntfStatus(intfId_)->localFaultStatus()));
}

Seconds EthPhyIntfStatus::localFaultStatusChangeTime() const {
   return sdk_->internal_->ethPhyIntfStatus(intfId_)->localFaultStatusChangeTime();
}

U32 EthPhyIntfStatus::localFaultStatusChanges() const {
   return sdk_->internal_->ethPhyIntfStatus(intfId_)->localFaultStatusChanges();
}


TxFaultStatus EthPhyIntfStatus::txFaultStatus() const {
   return static_cast<TxFaultStatus>(static_cast<int>(
         sdk_->internal_->ethPhyIntfStatus(intfId_)->txFaultStatus()));
}

Seconds EthPhyIntfStatus::txFaultStatusChangeTime() const {
   return sdk_->internal_->ethPhyIntfStatus(intfId_)->txFaultStatusChangeTime();
}

U32 EthPhyIntfStatus::txFaultStatusChanges() const {
   return sdk_->internal_->ethPhyIntfStatus(intfId_)->txFaultStatusChanges();
}


EthTimestampMode EthPhyIntfStatus::timestampMode() const {
   return static_cast<EthTimestampMode>(static_cast<int>(
         sdk_->internal_->ethPhyIntfStatus(intfId_)->timestampMode()));
}


EthDuplex EthPhyIntfStatus::duplex() const {
   return static_cast<EthDuplex>(
         static_cast<int>(sdk_->internal_->ethPhyIntfStatus(intfId_)->duplex()));
}

EthSpeed EthPhyIntfStatus::speed() const {
   return static_cast<EthSpeed>(
         static_cast<int>(sdk_->internal_->ethPhyIntfStatus(intfId_)->speed()));
}

LoopbackMode EthPhyIntfStatus::loopbackMode() const {
   return static_cast<LoopbackMode>(static_cast<int>(
         sdk_->internal_->ethPhyIntfStatus(intfId_)->loopbackMode()));
}


XcvrPresence EthPhyIntfStatus::xcvrPresence() const {
   return static_cast<XcvrPresence>(static_cast<int>(
         sdk_->internal_->ethPhyIntfStatus(intfId_)->xcvrPresence()));
}

std::string EthPhyIntfStatus::xcvrType() const {
   return convert(sdk_->internal_->ethPhyIntfStatus(intfId_)->xcvrType());
}


}  // namespace EosSdk
