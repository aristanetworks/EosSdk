// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOSSDK_EOSSDK_H
#define EOSSDK_EOSSDK_H

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <list>
#include <set>
#include <string>
#include <type_traits>

#include <EosSdk/EosFwdDecls.h>

namespace EosSdk {

typedef double Seconds;
typedef uint32_t U32;
typedef uint16_t U16;

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

namespace Internal {
void _referencesInc(const Tac::PtrInterface* entity);
void _referencesDec(const Tac::PtrInterface* entity);
}

// TODO: Hide all constructors and befriend a factory helper class not exposed
// by the SDK.
template <typename T>
class TacEntity {
 public:
   typedef T TacType;
   explicit TacEntity(const T* entity) : entity_(entity) {
      assert(entity);
      Internal::_referencesInc(reinterpret_cast<const Tac::PtrInterface*>(entity_));
   }
   ~TacEntity() {
      Internal::_referencesDec(reinterpret_cast<const Tac::PtrInterface*>(entity_));
   }
 protected:
   const T* entity_;  // TODO: Remove this and replace with a per-class handler.
};

enum AdminDisabledReason {
   reasonUnknown,
   reasonEnabled,
   reasonAdmin,
   reasonErrDisabled,
   reasonInactive,
};

class IntfConfig : public TacEntity< ::Interface::IntfConfig> {
 public:
   explicit IntfConfig(const TacType* config) : TacEntity(config) {
   }

   IntfId intfId() const;
   std::string description() const;
   bool adminEnabled() const;
   AdminDisabledReason adminDisabledReason() const;
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

class IntfStatus : public TacEntity< ::Interface::IntfStatus> {
 public:
   explicit IntfStatus(const TacType* status) : TacEntity(status) {
   }

   IntfId intfId() const;
   OperStatus operStatus() const;
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

class EthPhyIntfConfig : public TacEntity< ::Interface::EthPhyIntfConfig> {
 public:
   explicit EthPhyIntfConfig(const TacType* config) : TacEntity(config) {
   }

   IntfId intfId() const;
   EthAddr addr() const;

   EthLinkMode linkModeLocal() const;
   LoopbackMode loopbackMode() const;
   EthTimestampMode timestampMode() const;
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

class EthPhyIntfStatus : public TacEntity< ::Interface::EthPhyIntfStatus> {
 public:
   explicit EthPhyIntfStatus(const TacType* status): TacEntity(status) {
   }

   IntfId intfId() const;
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
};

class EthLagIntfStatus {
   // TBD
};

class IntfHandler {
 public:
   virtual void onOperStatus(OperStatus status) {
   }
   virtual void onMtu(U32 mtu) {
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

class FileDescriptor {
 public:
   FileDescriptor(int fd) : fd_(fd) {
   }
   int fd() const {
      return fd_;
   }

   void interestReadableIs(bool b);
   void interestWritableIs(bool b);
   void interestExceptionIs(bool b);

   virtual void handleReadable() = 0;
   virtual void handleWriteable() = 0;
   virtual void handleException() = 0;

 protected:
   int fd_;
};

class TimerTask {
   virtual void run() {
   }
};

class SDK {
 public:
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

   void registerFileDescriptor(FileDescriptor& fd) {
      fds_.insert(&fd);
   }
   void unregisterFileDescriptor(const FileDescriptor& fd) {
      fds_.erase(const_cast<FileDescriptor*>(&fd));
   }

   void registerHandlers(Handlers& handlers) {
      std::list<Handlers*>::const_iterator i = std::find(handlers_.begin(),
            handlers_.end(), &handlers);
      if (i == handlers_.end()) {
         handlers_.push_back(&handlers);
      }
   };

   void unregisterHandlers(const Handlers& handlers) {
      std::list<Handlers*>::iterator i = std::find(handlers_.begin(),
            handlers_.end(), const_cast<Handlers*>(&handlers));
      if (i != handlers_.end()) {
         handlers_.erase(i);
      }
   }

 private:
   std::list<Handlers*> handlers_;

   struct FileDescriptorCmp {
      bool operator()(const FileDescriptor* const a,
                      const FileDescriptor* const b) const {
         return a->fd() < b->fd();
      }
   };
   std::set<FileDescriptor*, FileDescriptorCmp> fds_;
};

}  // namespace EosSdk

#endif // EOSSDK_EOSSDK_H
