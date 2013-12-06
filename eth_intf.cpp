// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <EosSdk/intf.h>
#include <EosSdk/eth.h>
#include <EosSdk/eth_intf.h>
#include <EosSdk/panic.h>
#include <EosSdk/Conversions.h>
#include <EosSdk/Mount.h>

#include <EthIntfMgrSm.h>

#include <Arnet/EthAddr.h>
#include <EthIntf/EthIntf.h>
#include <Lag/EthLagIntf.h>
#include <Sysdb/EntityManager.h>
#include <Tac/Tracing.h>

#include <list>

DEFAULT_TRACE_HANDLE( "EosSdkEthIntf" )

namespace eos {

class EthIntfMgrImpl : public eth_intf_mgr,
                       public MountHandler {
 public:
   EthIntfMgrImpl() {
      TRACE0( "intf_mgr_impl ctor: registering my mounts" );
   }

   void doMounts( const Sysdb::MountGroup::Ptr & mg ) {
      mg->doMount( Sysdb::Mount( "interface/config/eth/phy",
                                 "Interface::EthPhyIntfConfigDir", "w" ) );
      mg->doMount( Sysdb::Mount( "interface/config/eth/lag",
                                 "Interface::EthLagIntfConfigDir", "w" ) );
      mg->doMount( Sysdb::Mount( "interface/config/eth/intf",
                                 "Interface::EthIntfConfigDir", "w" ) );
      mg->doMount( Sysdb::Mount( "interface/status/eth/intf",
                                 "Interface::EthIntfStatusDir", "r" ) );
   }

   virtual void onMountsComplete( const Sysdb::EntityManager::Ptr & em ) {
      TRACE0( __FUNCTION__ );
      ethIntfConfigDir_ = em->getEntity<Interface::EthIntfConfigDir>(
            "interface/config/eth/intf" );
      ethIntfStatusDir_ = em->getEntity<Interface::EthIntfStatusDir>(
            "interface/status/eth/intf" );

      ethIntfMgrSm_ = EthIntfMgrSm::EthIntfMgrSmIs( ethIntfConfigDir_,
                                                    ethIntfStatusDir_ );
   }

   void handleInitialized() {
      for (auto handler_iterator = this->handlerList_.begin();
           handler_iterator!=this->handlerList_.end(); ++handler_iterator) {
         (*handler_iterator)->on_initialized();
      }
   }

   void add_handler(eth_intf_handler *handler) {
      // ordering: registration order (first to register is first to be notified).
      handlerList_.push_back( handler );
   }

   void remove_handler(eth_intf_handler *handler) {
      handlerList_.remove( handler );
   }

   void on_create(intf_id_t intf_id) {
      std::list<eth_intf_handler *>::const_iterator handler_iterator;
      for (handler_iterator = this->handlerList_.begin();
           handler_iterator!=this->handlerList_.end(); ++handler_iterator) {
         (*handler_iterator)->on_create(intf_id);
      }
   }

   void on_delete(intf_id_t intf_id) {
      std::list<eth_intf_handler *>::const_iterator handler_iterator;
      for (handler_iterator = this->handlerList_.begin();
           handler_iterator!=this->handlerList_.end(); ++handler_iterator) {
         (*handler_iterator)->on_delete(intf_id);
      }
   }

   void on_eth_addr(intf_id_t intf_id, eth_addr_t addr) {
      std::list<eth_intf_handler *>::const_iterator handler_iterator;
      for (handler_iterator = this->handlerList_.begin();
           handler_iterator!=this->handlerList_.end(); ++handler_iterator) {
         (*handler_iterator)->on_eth_addr(intf_id, addr);
      }
   }

   Interface::EthIntfConfigDir::Ptr ethIntfConfigDir_;
   Interface::EthIntfStatusDir::PtrConst ethIntfStatusDir_;
   EthIntfMgrSm::Ptr ethIntfMgrSm_;
   std::list<eth_intf_handler *> handlerList_;

};

EthIntfMgrImpl *
getEthIntfMgrImpl(eth_intf_mgr *me) {
   EthIntfMgrImpl * impl = static_cast<EthIntfMgrImpl *>(me);
   assert( impl == get_eth_intf_mgr() );
   return impl;
}

eth_intf_mgr::eth_intf_mgr() {
}

void
eth_intf_mgr::eth_intf_foreach(bool (*handler)(intf_id_t, void *), void *arg) {
   EthIntfMgrImpl * impl = getEthIntfMgrImpl(this);
   for( auto iter = impl->ethIntfStatusDir_->intfStatusIteratorConst();
        iter && (*handler)((eos::intf_id_t)iter.key().intfId(), arg);
        ++iter ) {}
}

void
eth_intf_mgr::eth_intf_foreach(bool (*handler)(intf_id_t, void *), void *arg,
                               intf_id_t bookmark) {
   EthIntfMgrImpl * impl = getEthIntfMgrImpl(this);
   for( auto iter = impl->ethIntfStatusDir_->intfStatusIteratorConst(
              convert(bookmark));
        iter && (*handler)((eos::intf_id_t)iter.key().intfId(), arg);
        ++iter ) {
   }
}

bool
eth_intf_mgr::exists(intf_id_t id) {
   /* returns true if intf_id_t has a corresponding status. */
   EthIntfMgrImpl * impl = getEthIntfMgrImpl(this);
   return !!impl->ethIntfStatusDir_->intfStatus(convert(id));
}

eth_addr_t
eth_intf_mgr::eth_addr(intf_id_t intf_id) {
   EthIntfMgrImpl * impl = getEthIntfMgrImpl(this);
   Interface::EthIntfStatus::PtrConst intfStatus = \
      impl->ethIntfStatusDir_->intfStatus(convert(intf_id));
   if( !intfStatus ) {
      panic( "Intf does not exist" );
   }
   return eth_addr_t(intfStatus->addr());
}

void
eth_intf_mgr::eth_addr_is(intf_id_t intf_id, eth_addr_t addr) {
   EthIntfMgrImpl * impl = getEthIntfMgrImpl(this);
   Interface::EthIntfConfig::Ptr intfConfig = \
      impl->ethIntfConfigDir_->intfConfig(convert(intf_id));
   if( !intfConfig ) {
      panic( "Intf does not exist" );
   }
   intfConfig->addrIs( addr.ethAddr_ );
}

eth_intf_mgr *
get_eth_intf_mgr() {
   static EthIntfMgrImpl impl;
   return &impl;
}

//
// eth_intf_handler implementations
//

eth_intf_handler::eth_intf_handler() : watching_all_intfs_(false) {}
eth_intf_handler::~eth_intf_handler() {
   TRACE0( __PRETTY_FUNCTION__ << " unregistering myself as a handler");
   if( watching_all_intfs_ ) {
      EthIntfMgrImpl * impl = (EthIntfMgrImpl *) get_eth_intf_mgr();
      impl->remove_handler(this);
   }
   // TODO: remove per-interface handlers
   // impl->remove_handler( (eos::intf_id_t)iter.key().intfId(), this );
}

void
eth_intf_handler::watch_all_intfs(bool interest) {
   TRACE0( __PRETTY_FUNCTION__ << " registering myself as new handler" );
   if( watching_all_intfs_ == interest ) return;
   EthIntfMgrImpl * impl = (EthIntfMgrImpl *) get_eth_intf_mgr();
   if(interest) {
      impl->add_handler(this);
   } else {
      impl->remove_handler(this);
   }
   watching_all_intfs_ = interest;
}

// Dummy implementations for virtual handler methods
void eth_intf_handler::on_initialized() {}
void eth_intf_handler::on_create(intf_id_t) {}
void eth_intf_handler::on_delete(intf_id_t) {}
void eth_intf_handler::on_eth_addr(intf_id_t, eth_addr_t) {}

//
// IntfStatusSm method implementations
//

void
EthIntfStatusSm::handleAddr() {
   TRACE8( __PRETTY_FUNCTION__ );
   EthIntfMgrImpl * impl = getEthIntfMgrImpl( eos::get_eth_intf_mgr() );

   intf_id_t intf_id = intf_id_t( (uint32_t)intfId().intfId() );
   impl->on_eth_addr( intf_id, intfStatus()->addr() );
}

//
// EthIntfMgrSm method implementations
//

void
EthIntfMgrSm::handleIntfStatus() {
   TRACE8( __PRETTY_FUNCTION__ );
   for( auto i = ethIntfStatusDir()->intfStatusIteratorConst(); i; ++i ) {
      ethIntfStatusSmIs( i.ptr() );
   }
}

void
EthIntfMgrSm::handleIntfStatus( Arnet::IntfId intfId ) {
   TRACE8( __PRETTY_FUNCTION__ );
   EthIntfMgrImpl * impl = getEthIntfMgrImpl( eos::get_eth_intf_mgr() );
   intf_id_t intf_id = intf_id_t( (uint32_t)intfId.intfId() );
   Interface::EthIntfStatus::PtrConst intfStatus = \
      ethIntfStatusDir()->intfStatus( intfId );
   if( intfStatus ) {
      ethIntfStatusSmIs( intfStatus );
      impl->on_create( intf_id );
   } else {
      ethIntfStatusSmDel( intfId );
      impl->on_delete( intf_id );
   }
}

} // end namespace eos
