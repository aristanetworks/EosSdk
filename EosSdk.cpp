// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <ostream>

#include "EosSdk.h"

#include <Arnet/EthAddr.h>
#include <Arnet/IntfId.h>
#include <EthIntf/EthIntf.h>
#include <Tac/ActivityLock.h>

#include "SDKInternal.h"
#include "EnumCast.h"

namespace EOS {

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
   Tac::ActivityLockAnchor lock;
   Handlers* prev = handlers_[name];
   if (prev) {
      // TODO: throw an exception?
      return;
   }
   handlers_[name] = handlers;
   internal_->registerHandlers(name, handlers);
};

void SDK::unregisterHandlers(const std::string& name) {
   Tac::ActivityLockAnchor lock;
   handlers_.erase(name);
   internal_->unregisterHandlers(name);
}

void SDK::registerFileDescriptor(FileDescriptorHandler& fd) {
   Tac::ActivityLockAnchor lock;
   fds_.insert(&fd);
   // TODO: use internal_ to insert this FD in the Activity loop.
}

void SDK::unregisterFileDescriptor(const FileDescriptorHandler& fd) {
   Tac::ActivityLockAnchor lock;
   fds_.erase(const_cast<FileDescriptorHandler*>(&fd));
   // TODO: use internal_ to remove this FD from the Activity loop.
}

// ------ //
// IntfId //
// ------ //

// We can't create an Arnet::IntfId from a U32, so this subclass helps us work
// around that by (ab)using the fact that there is a protected mutator available.
namespace {
   struct IntfIdHelper : public Arnet::IntfId {
      explicit IntfIdHelper(U32 intfId) {
         intfIdIs(intfId);
      }
   };
}

IntfId::IntfId(const std::string& name) : intfId_(Arnet::IntfId(name).intfId()) {
}

std::string IntfId::name() const {
   return IntfIdHelper(intfId_).stringValue().stdString();
}

std::string IntfId::shortName() const {
   return IntfIdHelper(intfId_).shortName().stdString();
}

std::ostream& operator<<(std::ostream& o, const IntfId& intfId) {
   return o << intfId.name();
}

// ---------- //
// IntfConfig //
// ---------- //

std::string IntfConfig::description() const {
   return convert(sdk_->internal_->ethIntfConfig(intfId_)->description());
}

void IntfConfig::descriptionIs(const std::string& description) {
   sdk_->internal_->ethIntfConfig(intfId_)->descriptionIs(description);
}

bool IntfConfig::adminEnabled() const {
   return sdk_->internal_->ethIntfConfig(intfId_)->adminEnabled();
}

void IntfConfig::adminEnabledIs(bool enabled) {
   return sdk_->internal_->ethIntfConfig(intfId_)->enabledIs(enabled);
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
   return enum_cast<OperStatus>(
         sdk_->internal_->ethIntfStatus(intfId_)->operStatus());
}

// ---------------- //
// EthPhyIntfConfig //
// ---------------- //

EthAddr EthPhyIntfConfig::addr() const {
   return convert(sdk_->internal_->ethPhyIntfConfig(intfId_)->addr());
}


EthLinkMode EthPhyIntfConfig::linkModeLocal() const {
   return enum_cast<EthLinkMode>(
         sdk_->internal_->ethPhyIntfConfig(intfId_)->linkModeLocal());
}

LoopbackMode EthPhyIntfConfig::loopbackMode() const {
   return enum_cast<LoopbackMode>(
         sdk_->internal_->ethPhyIntfConfig(intfId_)->loopbackMode());
}

EthTimestampMode EthPhyIntfConfig::timestampMode() const {
   return enum_cast<EthTimestampMode>(
         sdk_->internal_->ethPhyIntfConfig(intfId_)->timestampMode());
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
   return enum_cast<LinkStatus>(
        sdk_->internal_->ethPhyIntfStatus(intfId_)->linkStatus());
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
   return enum_cast<LocalFaultStatus>(
         sdk_->internal_->ethPhyIntfStatus(intfId_)->localFaultStatus());
}

Seconds EthPhyIntfStatus::localFaultStatusChangeTime() const {
   return sdk_->internal_->ethPhyIntfStatus(intfId_)->localFaultStatusChangeTime();
}

U32 EthPhyIntfStatus::localFaultStatusChanges() const {
   return sdk_->internal_->ethPhyIntfStatus(intfId_)->localFaultStatusChanges();
}


TxFaultStatus EthPhyIntfStatus::txFaultStatus() const {
   return enum_cast<TxFaultStatus>(
         sdk_->internal_->ethPhyIntfStatus(intfId_)->txFaultStatus());
}

Seconds EthPhyIntfStatus::txFaultStatusChangeTime() const {
   return sdk_->internal_->ethPhyIntfStatus(intfId_)->txFaultStatusChangeTime();
}

U32 EthPhyIntfStatus::txFaultStatusChanges() const {
   return sdk_->internal_->ethPhyIntfStatus(intfId_)->txFaultStatusChanges();
}


EthTimestampMode EthPhyIntfStatus::timestampMode() const {
   return enum_cast<EthTimestampMode>(
         sdk_->internal_->ethPhyIntfStatus(intfId_)->timestampMode());
}


EthDuplex EthPhyIntfStatus::duplex() const {
   return enum_cast<EthDuplex>(sdk_->internal_->ethPhyIntfStatus(intfId_)->duplex());
}

EthSpeed EthPhyIntfStatus::speed() const {
   return enum_cast<EthSpeed>(sdk_->internal_->ethPhyIntfStatus(intfId_)->speed());
}

LoopbackMode EthPhyIntfStatus::loopbackMode() const {
   return enum_cast<LoopbackMode>(
         sdk_->internal_->ethPhyIntfStatus(intfId_)->loopbackMode());
}


XcvrPresence EthPhyIntfStatus::xcvrPresence() const {
   return enum_cast<XcvrPresence>(
         sdk_->internal_->ethPhyIntfStatus(intfId_)->xcvrPresence());
}

std::string EthPhyIntfStatus::xcvrType() const {
   return convert(sdk_->internal_->ethPhyIntfStatus(intfId_)->xcvrType());
}


}  // namespace EOS
