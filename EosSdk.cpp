// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "EosSdk.h"

#include <Tac/PtrInterface.h>
#include <Arnet/EthAddr.h>
#include <Arnet/IntfId.h>
#include <EthIntf/EthIntf.h>

namespace EosSdk {

namespace Internal {
void _referencesInc(const Tac::PtrInterface* entity) {
   U32 refCnt = entity->referencesInc(1);
   assert(refCnt > 1);  // We can't possibly be the only ones.
}

void _referencesDec(const Tac::PtrInterface* entity) {
   entity->referencesDec(1);
}
} // namespace Internal

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

static IntfId convert(Arnet::IntfId intf) {
   return IntfId(intf.stringValue().stdString());
}

static EthAddr convert(Arnet::EthAddr addr) {
   return EthAddr(addr.word0(), addr.word1(), addr.word2());
}

// ---------- //
// IntfConfig //
// ---------- //

IntfId IntfConfig::intfId() const {
   return convert(entity_->intfId());
}

std::string IntfConfig::description() const {
   return convert(entity_->description());
}

bool IntfConfig::adminEnabled() const {
   return entity_->adminEnabled();
}

std::string IntfConfig::adminDisabledReason() const {
   return convert(entity_->enabledStateReason());
}

// ---------- //
// IntfStatus //
// ---------- //

IntfId IntfStatus::intfId() const {
   return convert(entity_->intfId());
}

OperStatus IntfStatus::operStatus() const {
   return static_cast<OperStatus>(static_cast<int>(entity_->operStatus()));
}

// ---------------- //
// EthPhyIntfConfig //
// ---------------- //

IntfId EthPhyIntfConfig::intfId() const {
   return convert(entity_->intfId());
}

EthAddr EthPhyIntfConfig::addr() const {
   return convert(entity_->addr());
}


EthLinkMode EthPhyIntfConfig::linkModeLocal() const {
   return static_cast<EthLinkMode>(static_cast<int>(entity_->linkModeLocal()));
}

LoopbackMode EthPhyIntfConfig::loopbackMode() const {
   return static_cast<LoopbackMode>(static_cast<int>(entity_->loopbackMode()));
}

EthTimestampMode EthPhyIntfConfig::timestampMode() const {
   return static_cast<EthTimestampMode>(
         static_cast<int>(entity_->timestampMode()));
}

// ---------------- //
// EthPhyIntfStatus //
// ---------------- //

IntfId EthPhyIntfStatus::intfId() const {
   return convert(entity_->intfId());
}

EthAddr EthPhyIntfStatus::addr() const {
   return convert(entity_->addr());
}

EthAddr EthPhyIntfStatus::burnedInAddr() const {
   return convert(entity_->burnedInAddr());
}

LinkStatus EthPhyIntfStatus::linkStatus() const {
   return static_cast<LinkStatus>(static_cast<int>(entity_->linkStatus()));
}


bool EthPhyIntfStatus::macRxRemoteFault() const {
   return entity_->macRxRemoteFault();
}

U32 EthPhyIntfStatus::macRxRemoteFaultChanges() const {
   return entity_->macRxRemoteFaultChanges();
}

Seconds EthPhyIntfStatus::lastMacRxRemoteFaultChange() const {
   return entity_->lastMacRxRemoteFaultChange();
}


bool EthPhyIntfStatus::macRxLocalFault() const {
   return entity_->macRxLocalFault();
}

U32 EthPhyIntfStatus::macRxLocalFaultChanges() const {
   return entity_->macRxLocalFaultChanges();
}

Seconds EthPhyIntfStatus::lastMacRxLocalFaultChange() const {
   return entity_->lastMacRxLocalFaultChange();
}


LocalFaultStatus EthPhyIntfStatus::localFaultStatus() const {
   return static_cast<LocalFaultStatus>(
         static_cast<int>(entity_->localFaultStatus()));
}

Seconds EthPhyIntfStatus::localFaultStatusChangeTime() const {
   return entity_->localFaultStatusChangeTime();
}

U32 EthPhyIntfStatus::localFaultStatusChanges() const {
   return entity_->localFaultStatusChanges();
}


TxFaultStatus EthPhyIntfStatus::txFaultStatus() const {
   return static_cast<TxFaultStatus>(static_cast<int>(entity_->txFaultStatus()));
}

Seconds EthPhyIntfStatus::txFaultStatusChangeTime() const {
   return entity_->txFaultStatusChangeTime();
}

U32 EthPhyIntfStatus::txFaultStatusChanges() const {
   return entity_->txFaultStatusChanges();
}


EthTimestampMode EthPhyIntfStatus::timestampMode() const {
   return static_cast<EthTimestampMode>(
         static_cast<int>(entity_->timestampMode()));
}


EthDuplex EthPhyIntfStatus::duplex() const {
   return static_cast<EthDuplex>(static_cast<int>(entity_->duplex()));
}

EthSpeed EthPhyIntfStatus::speed() const {
   return static_cast<EthSpeed>(static_cast<int>(entity_->speed()));
}

LoopbackMode EthPhyIntfStatus::loopbackMode() const {
   return static_cast<LoopbackMode>(static_cast<int>(entity_->loopbackMode()));
}


XcvrPresence EthPhyIntfStatus::xcvrPresence() const {
   return static_cast<XcvrPresence>(static_cast<int>(entity_->xcvrPresence()));
}

std::string EthPhyIntfStatus::xcvrType() const {
   return convert(entity_->xcvrType());
}


}  // namespace EosSdk
