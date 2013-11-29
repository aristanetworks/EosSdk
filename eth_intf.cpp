// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <EosSdk/eth.h>
#include <EosSdk/eth_intf.h>
#include <EosSdk/intf.h>
#include <EosSdk/Mount.h>

#include <EthIntfMgrSm.h>

#include <Arnet/EthAddr.h>
#include <EthIntf/EthIntf.h>
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
      mg->doMount( Sysdb::Mount( "interface/status/eth/phy",
                                 "Interface::EthPhyIntfStatusDir", "r" ) );
      mg->doMount( Sysdb::Mount( "interface/config/eth/intf",
                                 "Interface::EthIntfConfigDir", "w" ) );
      mg->doMount( Sysdb::Mount( "interface/status/eth/intf",
                                 "Interface::EthIntfStatusDir", "r" ) );
   }

   virtual void onMountsComplete( const Sysdb::EntityManager::Ptr & em ) {
      TRACE0( __FUNCTION__ );
      ethPhyIntfConfigDir_ = em->getEntity<Interface::EthPhyIntfConfigDir>( 
            "interface/config/eth/phy" );
      ethPhyIntfStatusDir_ = em->getEntity<Interface::EthPhyIntfStatusDir>( 
            "interface/status/eth/phy" );
      ethIntfConfigDir_ = em->getEntity<Interface::EthIntfConfigDir>( 
            "interface/config/eth/intf" );
      ethIntfStatusDir_ = em->getEntity<Interface::EthIntfStatusDir>( 
            "interface/status/eth/intf" );

      ethIntfMgrSm_ = EthIntfMgrSm::EthIntfMgrSmIs( ethPhyIntfConfigDir_,
                                                    ethPhyIntfStatusDir_,
                                                    ethIntfConfigDir_,
                                                    ethIntfStatusDir_ );

      for (auto handler_iterator = this->handlerList_.begin();
           handler_iterator!=this->handlerList_.end(); ++handler_iterator) {
         (*handler_iterator)->on_initialized();
      }
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

   void on_link_mode(intf_id_t intf_id, eth_link_mode_t link_mode) {
      std::list<eth_intf_handler *>::const_iterator handler_iterator;
      for (handler_iterator = this->handlerList_.begin();
           handler_iterator!=this->handlerList_.end(); ++handler_iterator) {
         (*handler_iterator)->on_link_mode(intf_id, link_mode);
      }
   }

   Interface::EthPhyIntfConfigDir::Ptr ethPhyIntfConfigDir_;
   Interface::EthPhyIntfStatusDir::PtrConst ethPhyIntfStatusDir_;
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

eth_intf_mgr * 
get_eth_intf_mgr() {
   static EthIntfMgrImpl impl;
   return &impl;
}

} // end namespace eos
