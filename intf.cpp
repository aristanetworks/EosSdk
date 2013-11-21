// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <Tac/Tracing.h>
#include <Arnet/IntfId.h>
#include <Intf/Intf.h>
#include <EosSdk/intf.h>
#include <EosSdk/Mount.h>
#include <EosSdk/panic.h>
#include <IntfMgrSm.h>
#include <Sysdb/EntityManager.h>
#include <list>


DEFAULT_TRACE_HANDLE( "EosSdkIntf" )

namespace eos {

static oper_status_t convert( Interface::IntfOperStatus operStatus ) {
   oper_status_t ret;
   switch( operStatus ) {
    case Interface::intfOperUp_:
      ret = INTF_OPER_UP;
      break;
    case Interface::intfOperDown_:
    case Interface::intfOperDormant_:
    case Interface::intfOperNotPresent_:
    case Interface::intfOperLowerLayerDown_:
      ret = INTF_OPER_DOWN;
      break;
    default:
      ret = INTF_OPER_NULL;
      break;
   }
   return ret;
}

intf_id_t::intf_id_t(uint32_t id) {
   assert( sizeof(id) == sizeof(intfId_) );
   memcpy( &intfId_, &id, sizeof(intfId_) );
   validate();
}

intf_id_t::intf_id_t(char const * intfname) :
      intfId_(intfname) {
   validate();
}

void
intf_id_t::validate() {
   // Ask IntfIdTrie if intfId_ looks valid.
   // If not, call panic().
}

void
intf_id_t::to_string(char *namebuf, size_t namebuf_size) {
   Tac::String name = intfId_.stringValue();
   char const * ptr = name.charPtr();
   strncpy( namebuf, ptr, namebuf_size );
   namebuf[namebuf_size - 1] = 0;
}

class intf_mgr_impl : public intf_mgr,
                      public mount_handler {
 public:
   intf_mgr_impl() {
      TRACE0( __PRETTY_FUNCTION__ );
   }

   virtual void doMounts( const Sysdb::MountGroup::Ptr & mg ) {
      TRACE0( __PRETTY_FUNCTION__ );
      mg->doMount( Sysdb::Mount( "interface/config/eth/intf",
                                 "Interface::EthIntfConfigDir", "w" ) );
      mg->doMount( Sysdb::Mount( "interface/status/eth/intf",
                                 "Interface::EthIntfStatusDir", "r" ) );
      mg->doMount( Sysdb::Mount( "interface/config/eth/phy",
                                 "Interface::EthPhyIntfConfigDir", "w" ) );
      mg->doMount( Sysdb::Mount( "interface/status/eth/phy",
                                 "Interface::EthPhyIntfStatusDir", "r" ) );
      mg->doMount( Sysdb::Mount( "interface/config/eth/lag",
                                 "Interface::EthLagIntfConfigDir", "w" ) );
      mg->doMount( Sysdb::Mount( "interface/status/eth/lag",
                                 "Interface::EthLagIntfStatusDir", "r" ) );
      mg->doMount( Sysdb::Mount( "interface/config/all",
                                 "Interface::AllIntfConfigDir", "r" ) );
      mg->doMount( Sysdb::Mount( "interface/status/all",
                                 "Interface::AllIntfStatusDir", "r" ) );
   }

   virtual void onMountsComplete( const Sysdb::EntityManager::Ptr & em ) {
      TRACE0( "intf_mgr_impl: all mounts completed" );
      allIntfStatusDir_ = em->getEntity<Interface::AllIntfStatusDir>( 
            "interface/status/all" );
      allIntfConfigDir_ = em->getEntity<Interface::AllIntfConfigDir>( 
            "interface/config/all" );

      intfMgrSm_ = IntfMgrSm::IntfMgrSmIs( allIntfConfigDir_,
                                           allIntfStatusDir_ );

      for (auto handler_iterator = this->handlerList_.begin();
           handler_iterator!=this->handlerList_.end(); ++handler_iterator) {
         (*handler_iterator)->on_initialized();
   }

   }
   Interface::AllIntfStatusDir::Ptr allIntfStatusDir_;
   Interface::AllIntfConfigDir::Ptr allIntfConfigDir_;
   IntfMgrSm::Ptr intfMgrSm_;
   std::list<intf_handler *> handlerList_;
};

intf_mgr_impl *
get_intf_mgr_impl(intf_mgr *me) {
   intf_mgr_impl * impl = static_cast<intf_mgr_impl *>(me);
   assert( impl == get_intf_mgr() );
   return impl;
}

intf_mgr::intf_mgr() {
}

void intf_mgr::add_handler(intf_handler *handler) {
   intf_mgr_impl * impl = get_intf_mgr_impl(this);
   impl->handlerList_.push_back( handler );
}

void intf_mgr::remove_handler(intf_handler *handler) {
   intf_mgr_impl * impl = get_intf_mgr_impl(this);
   impl->handlerList_.remove( handler );   
}

void intf_mgr::add_handler(intf_id_t, intf_handler *handler) {
   assert( false && "Not yet implemented" );
}

void intf_mgr::remove_handler(intf_id_t, intf_handler *) {
   assert( false && "Not yet implemented" );
}

void
intf_mgr::intf_foreach(bool (*handler)(intf_id_t, void *), void *arg) {
   intf_mgr_impl * impl = get_intf_mgr_impl(this);
   for( auto iter = impl->allIntfStatusDir_->intfStatusIterator();
        iter && (*handler)((eos::intf_id_t)iter.key().intfId(), arg);
        ++iter ) {}
}

void
intf_mgr::intf_foreach(bool (*handler)(intf_id_t, void *), void *arg,
                       intf_id_t bookmark) {
   /* Starting with the first element after bookmark's position, for
    * each interface, call the supplied handler callback with the
    * corresponding intf_id_t and arg. If callback returns false, we
    * stop iteration.  */

   intf_mgr_impl * impl = get_intf_mgr_impl(this);
   for( auto iter = impl->allIntfStatusDir_->intfStatusIterator( bookmark.intfId_ );
        iter && (*handler)((eos::intf_id_t)iter.key().intfId(), arg);
        ++iter ) {}
}

bool
intf_mgr::exists(intf_id_t id) {
   /* returns true if intf_id_t has a corresponding status. */
   intf_mgr_impl * impl = get_intf_mgr_impl(this);
   return !!impl->allIntfStatusDir_->intfStatus( id.intfId_ );
}

void
intf_mgr::description_is(intf_id_t id, char const * descr) {
   intf_mgr_impl * impl = get_intf_mgr_impl(this);
   Interface::IntfConfig::Ptr intfConfig = 
      impl->allIntfConfigDir_->intfConfig( id.intfId_ );
   intfConfig->descriptionIs( descr );
}

oper_status_t
intf_mgr::oper_status(intf_id_t id) {
   intf_mgr_impl * impl = get_intf_mgr_impl(this);
   Interface::IntfStatus::Ptr intfStatus = 
      impl->allIntfStatusDir_->intfStatus( id.intfId_ );
   if( !intfStatus ) {
      panic( "No matching interface" );
   }
   return convert( intfStatus->operStatus() );
}

void
intf_mgr::on_create(intf_id_t intf_id) {
   intf_mgr_impl * impl = get_intf_mgr_impl(this);

   std::list<intf_handler *>::const_iterator handler_iterator;
   for (handler_iterator = impl->handlerList_.begin();
        handler_iterator!=impl->handlerList_.end(); ++handler_iterator) {
      (*handler_iterator)->on_create( intf_id );
   }
}

void
intf_mgr::on_delete(intf_id_t intf_id) {
   intf_mgr_impl * impl = get_intf_mgr_impl(this);

   std::list<intf_handler *>::const_iterator handler_iterator;
   for (handler_iterator = impl->handlerList_.begin();
        handler_iterator!=impl->handlerList_.end(); ++handler_iterator) {
      (*handler_iterator)->on_delete( intf_id );
   }
}

void
intf_mgr::on_oper_status(intf_id_t intf_id, Interface::IntfOperStatus oper_status) {
   intf_mgr_impl * impl = get_intf_mgr_impl(this);
   oper_status_t status = convert( oper_status );
   std::list<intf_handler *>::const_iterator handler_iterator;
   for (handler_iterator = impl->handlerList_.begin();
        handler_iterator!=impl->handlerList_.end(); ++handler_iterator) {
      (*handler_iterator)->on_oper_status( intf_id, status );
   }
}

void
intf_mgr::on_admin_enabled(intf_id_t intf_id, bool enabled) {
   intf_mgr_impl * impl = get_intf_mgr_impl(this);

   std::list<intf_handler *>::const_iterator handler_iterator;
   for (handler_iterator = impl->handlerList_.begin();
        handler_iterator!=impl->handlerList_.end(); ++handler_iterator) {
      (*handler_iterator)->on_admin_enabled( intf_id, enabled );
   }
}


intf_mgr * 
get_intf_mgr() {
   static intf_mgr_impl impl;
   return &impl;
}


};
