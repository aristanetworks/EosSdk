// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOSSDK_EOSSDK_H
#define EOSSDK_EOSSDK_H

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <type_traits>

#include <EosSdk/EosFwdDecls.h>

namespace EosSdk {

typedef double Seconds;
typedef uint32_t U32;
typedef uint16_t U16;

class SDKInternal;
class SDK;
typedef void (*EosSdkInitFunc)(SDK*);

struct Via {};  // TBD
struct AclRule {};  // TBD
struct IPv4 {}; // TBD
struct IPv6 {}; // TBD
enum AclType { AclIPv4, AclIPv6, AclMAC };

class IntfId {
 public:
   explicit IntfId(const std::string& name) : name_(name) {
   }

   const std::string& name() const {
      return name_;
   }

   bool operator==(const IntfId& other) {
      return name_ == other.name_;
   }

   bool operator!=(const IntfId& other) {
      return name_ != other.name_;
   }
 private:
   std::string name_;
};

class EthAddr {
 public:
   explicit EthAddr(const std::string& addr);
   EthAddr(U16 word0, U16 word1, U16 word2)
      : word0(word0), word1(word1), word2(word2) {
   }

   bool operator==(const EthAddr& other) {
      return word2 == other.word2 && word1 == other.word1
         && word0 == other.word0;
   }

   bool operator!=(const EthAddr& other) {
      return !(*this == other);
   }

   static const EthAddr kZero;
   static const EthAddr kBroadcast;
   static const EthAddr kStp;
   static const EthAddr kPvst;
   static const EthAddr kSlowProto;
   static const EthAddr kLldp;
   static const EthAddr kIpMcastBase;
   static const EthAddr kVrrpIpv4Base;
   static const EthAddr kVrrpIpv6Base;
   static const EthAddr kPtp;
   static const EthAddr kPtpPeerDelay;
   static const EthAddr kIsisL1IS;
   static const EthAddr kIsisL2IS;
   static const EthAddr kIsisAllIS;
 private:
   U16 word0;
   U16 word1;
   U16 word2;
};

enum AdminDisabledReason {
   reasonUnknown,
   reasonEnabled,
   reasonAdmin,
   reasonErrDisabled,
   reasonInactive,
};

class IntfConfig {
 public:
   IntfId intfId() const {
      return intfId_;
   }
   std::string description() const;
   bool adminEnabled() const;
   AdminDisabledReason adminDisabledReason() const;

 private:
   friend class SDK;
   IntfConfig(SDK* const sdk, const IntfId& intfId) : sdk_(sdk), intfId_(intfId) {
   }
   SDK* const sdk_;
   IntfId intfId_;
};

enum OperStatus {
   intfOperUp,
   intfOperDown,
   intfOperTesting,
   intfOperUnknown,
   intfOperDormant,
   intfOperNotPresent,
   intfOperLowerLayerDown,
};

class IntfStatus {
 public:
   IntfId intfId() const {
      return intfId_;
   }
   OperStatus operStatus() const;

 private:
   friend class SDK;
   IntfStatus(SDK* const sdk, const IntfId& intfId) : sdk_(sdk), intfId_(intfId) {
   }
   SDK* const sdk_;
   IntfId intfId_;
};

enum EthLinkMode {
   linkModeUnknown,
   linkModeAutoneg,
   linkModeAuto40GbpsFull,
   linkModeForced10MbpsHalf,
   linkModeForced10MbpsFull,
   linkModeForced100MbpsHalf,
   linkModeForced100MbpsFull,
   linkModeForced1GbpsHalf,
   linkModeForced1GbpsFull,
   // There is no such thing as half duplex at speeds >= 10Gbps
   linkModeForced10GbpsFull,
   linkModeForced40GbpsFull,
   linkModeForced100GbpsFull,
};

// Loopback mode of the eth phy interface
enum LoopbackMode {
   loopbackNone,
   loopbackMac,
   loopbackPhy,
};

// Add timestamp information in packets going out of this intf.
enum EthTimestampMode {
   timestampModeDisabled,
   timestampModeBeforeFcs,  // insert timestamp before FCS field
   timestampModeReplaceFcs, // replace FCS with timestamp field
};

class EthPhyIntfConfig {
 public:
   IntfId intfId() const {
      return intfId_;
   }
   EthAddr addr() const;

   EthLinkMode linkModeLocal() const;
   LoopbackMode loopbackMode() const;
   EthTimestampMode timestampMode() const;

 private:
   friend class SDK;
   EthPhyIntfConfig(SDK* const sdk, const IntfId& intfId)
      : sdk_(sdk), intfId_(intfId) {
   }
   SDK* const sdk_;
   IntfId intfId_;
};

enum LinkStatus {
   linkUnknown,
   linkDown,
   linkUp,
};

enum EthDuplex {
   duplexUnknown,
   duplexHalf,
   duplexFull,
};

enum EthSpeed {
   speedUnknown,
   speed10Mbps,
   speed100Mbps,
   speed1Gbps,
   speed10Gbps,
   speed40Gbps,
   speed100Gbps,
};

enum XcvrPresence {
   xcvrPresenceUnknown,
   xcvrNotApplicable, // some ports don't have transceivers
   xcvrNotPresent,
   xcvrPresent,
};

enum LocalFaultStatus {
   localFaultUnknown,
   localFaultDetected,
   localFaultNotDetected,
};

enum TxFaultStatus {
   txFaultUnknown,
   txFaultDetected,
   txFaultNotDetected,
};

class EthPhyIntfStatus {
 public:
   IntfId intfId() const {
      return intfId_;
   }
   EthAddr addr() const;
   EthAddr burnedInAddr() const;
   LinkStatus linkStatus() const;

   bool macRxRemoteFault() const;
   U32 macRxRemoteFaultChanges() const;
   Seconds lastMacRxRemoteFaultChange() const;

   bool macRxLocalFault() const;
   U32 macRxLocalFaultChanges() const;
   Seconds lastMacRxLocalFaultChange() const;

   LocalFaultStatus localFaultStatus() const;
   Seconds localFaultStatusChangeTime() const;
   U32 localFaultStatusChanges() const;

   TxFaultStatus txFaultStatus() const;
   Seconds txFaultStatusChangeTime() const;
   U32 txFaultStatusChanges() const;

   EthTimestampMode timestampMode() const;

   EthDuplex duplex() const;
   EthSpeed speed() const;
   LoopbackMode loopbackMode() const;

   XcvrPresence xcvrPresence() const;
   std::string xcvrType() const;

 private:
   friend class SDK;
   EthPhyIntfStatus(SDK* const sdk, const IntfId& intfId)
      : sdk_(sdk), intfId_(intfId) {
   }
   SDK* const sdk_;
   IntfId intfId_;
};

class EthLagIntfStatus {
   // TBD
};

class IntfHandler {
 public:
   virtual void onDescription(const IntfId& intfId, const std::string& description) {
   }
   virtual void onAdminEnabled(const IntfId& intfId, bool adminEnabled) {
   }
   virtual void onAdminDisabledReason(const IntfId& intfId,
                                      AdminDisabledReason reason) {
   }

   virtual void onDeletion() {
   }
};

class EthPhyIntfHandler {
   // TBD
};

class Handlers {
 public:
   virtual IntfHandler* handleIntfCreation(const IntfStatus& status) {
      return 0;
   }
   virtual EthPhyIntfHandler*
   handleEthPhyIntfCreation(const EthPhyIntfStatus& status) {
      return 0;
   }
};

class FileDescriptorHandler {
 public:
   int fd() const {
      return fd_;
   }

   void interestReadableIs(bool b);
   void interestWritableIs(bool b);
   void interestExceptionIs(bool b);

   virtual void handleReadable() = 0;
   virtual void handleWriteable() = 0;
   virtual void handleException() = 0;

 private:
   FileDescriptorHandler(SDK* const sdk, int fd)
      : sdk_(sdk), fd_(fd) {
   }
   SDK* const sdk_;
   int fd_;
};

class TimerTask {
   virtual void run() {
   }
};

class SDK {
 public:
   // Access to basic interface config and status.
   IntfConfig intfConfig(const IntfId& intfId) {
      return IntfConfig(this, intfId);
   }
   IntfStatus intfStatus(const IntfId& intfId) {
      return IntfStatus(this, intfId);
   }
   // Access to the Ethernet interface config and status.
   EthPhyIntfConfig ethIntfConfig(const IntfId& intfId) {
      return EthPhyIntfConfig(this, intfId);
   }
   EthPhyIntfStatus ethIntfStatus(const IntfId& intfId) {
      return EthPhyIntfStatus(this, intfId);
   }

   void addRoute(const IPv4& ipAddress, Via &via) {};
   void addRoute(const IPv6& ipAddress, Via &via) {};
   void delRoute(const IPv4& ipAddress, Via &via) {};
   void delRoute(const IPv6& ipAddress, Via &via) {};

   // Create/delete ACLs
   void createAcl(const std::string& name, AclType aclType) {};
   void deleteAcl(const std::string& name, AclType aclType) {};
   // Add/remove rules from ACLs
   void aclAddRule(const std::string& name, AclType aclType,
                   int seqNo, AclRule rule) {};
   void aclDelRule(const std::string& name, AclType aclType,
                   int seqNo, AclRule rule) {};
   // Attach/detach ACLs from interfaces
   void attachAcl(const std::string& name, const IntfId& intfId) {};
   void detachAcl(const std::string& name, const IntfId& intfId) {};

   void commitAcl(const std::string& name, AclType aclType) {};

   void createTimer(TimerTask& task, Seconds deadline);
   void cancelTimer(TimerTask& task);

   void registerFileDescriptor(FileDescriptorHandler& fd) {
      fds_.insert(&fd);
   }
   void unregisterFileDescriptor(const FileDescriptorHandler& fd) {
      fds_.erase(const_cast<FileDescriptorHandler*>(&fd));
   }

   void registerHandlers(const std::string& name, Handlers* handlers);
   void unregisterHandlers(const std::string& name);

 private:
   friend class SDKInternal;
   friend class IntfConfig;
   friend class IntfStatus;
   friend class EthPhyIntfConfig;
   friend class EthPhyIntfStatus;
   friend class SdkSm;

   SDKInternal* const internal_;
   std::map<std::string, Handlers*> handlers_;

   struct FileDescriptorCmp {
      bool operator()(const FileDescriptorHandler* const a,
                      const FileDescriptorHandler* const b) const {
         return a->fd() < b->fd();
      }
   };
   std::set<FileDescriptorHandler*, FileDescriptorCmp> fds_;

   explicit SDK(SDKInternal* const internal) : internal_(internal) {
   }

   // Disable copy constructor and assignment operator.
   SDK(const SDK& sdk);
   SDK& operator=(const SDK& sdk);

};

}  // namespace EosSdk

#endif // EOSSDK_EOSSDK_H
