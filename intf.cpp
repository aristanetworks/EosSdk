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

intf_id_t::intf_id_t() : intfId_("") {
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

// Arnet::IntfId's default constructor sets emptyIntfId as the intfId
// when passed the empty string, as we do in our default
// constructor. See Arnet/IntfId.tin IntfId::handleInitialized()
bool
intf_id_t::operator !() const {
   return intfId_.intfId() == Arnet::IntfId::emptyIntfId();
}

bool
intf_id_t::is_null0() const {
   static uint32_t null0_intf_id = Arnet::IntfId("Null0").intfId();
   return intfId_.intfId() == null0_intf_id;
}

bool
intf_id_t::operator==(intf_id_t const & other) {
   return (intfId_ == other.intfId_);
}

bool
intf_id_t::operator!=(intf_id_t const & other) {
   return (intfId_ != other.intfId_);
}

void
intf_id_t::validate() {
   // Ask IntfIdTrie if intfId_ looks valid.
   // If not, call panic().
}

size_t
intf_id_t::to_string(char *namebuf, size_t namebuf_size) const {
   Tac::String name = intfId_.stringValue();
   char const * ptr = name.charPtr();
   strncpy( namebuf, ptr, namebuf_size );
   namebuf[namebuf_size - 1] = 0;
   return namebuf_size;
}


class IntfMgrImpl : public intf_mgr,
                    public MountHandler {
 public:
   IntfMgrImpl() {
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
      TRACE0( "IntfMgrImpl: all mounts completed" );
      allIntfStatusDir_ = em->getEntity<Interface::AllIntfStatusDir>( 
            "interface/status/all" );
      allIntfConfigDir_ = em->getEntity<Interface::AllIntfConfigDir>( 
            "interface/config/all" );

      intfMgrSm_ = IntfMgrSm::IntfMgrSmIs( allIntfConfigDir_,
                                           allIntfStatusDir_ );
   }

   void handleInitialized() {
      for (auto handler_iterator = this->handlerList_.begin();
           handler_iterator!=this->handlerList_.end(); ++handler_iterator) {
         (*handler_iterator)->on_initialized();
      }
   }

   void add_handler(intf_handler *handler) {
      TRACE0( __PRETTY_FUNCTION__ );
      // ordering: registration order (first to register is first to be notified).
      handlerList_.push_back( handler );
   }

   void remove_handler(intf_handler *handler) {
      TRACE0( __PRETTY_FUNCTION__ );
      handlerList_.remove( handler );   
   }

   void add_handler(intf_id_t, intf_handler *handler) {
      assert( false && "Not yet implemented" );
   }

   void remove_handler(intf_id_t, intf_handler *) {
      assert( false && "Not yet implemented" );
   }
   
   void on_create(intf_id_t intf_id) {
      std::list<intf_handler *>::const_iterator handler_iterator;
      for (handler_iterator = this->handlerList_.begin();
           handler_iterator!=this->handlerList_.end(); ++handler_iterator) {
         (*handler_iterator)->on_create( intf_id );
      }
   }
   
   void on_delete(intf_id_t intf_id) {
      std::list<intf_handler *>::const_iterator handler_iterator;
      for (handler_iterator = this->handlerList_.begin();
           handler_iterator!=this->handlerList_.end(); ++handler_iterator) {
         (*handler_iterator)->on_delete( intf_id );
      }
   }
   void on_oper_status(intf_id_t intf_id, Interface::IntfOperStatus oper_status) {
      oper_status_t status = convert( oper_status );
      std::list<intf_handler *>::const_iterator handler_iterator;
      for (handler_iterator = this->handlerList_.begin();
           handler_iterator!=this->handlerList_.end(); ++handler_iterator) {
         (*handler_iterator)->on_oper_status( intf_id, status );
      }
   }
      
   void on_admin_enabled(intf_id_t intf_id, bool enabled) {
      std::list<intf_handler *>::const_iterator handler_iterator;
      for (handler_iterator = this->handlerList_.begin();
           handler_iterator!=this->handlerList_.end(); ++handler_iterator) {
         (*handler_iterator)->on_admin_enabled( intf_id, enabled );
      }
   }

   Interface::AllIntfStatusDir::Ptr allIntfStatusDir_;
   Interface::AllIntfConfigDir::Ptr allIntfConfigDir_;
   IntfMgrSm::Ptr intfMgrSm_;
   std::list<intf_handler *> handlerList_;
};

IntfMgrImpl *
getIntfMgrImpl(intf_mgr *me) {
   IntfMgrImpl * impl = static_cast<IntfMgrImpl *>(me);
   assert( impl == get_intf_mgr() );
   return impl;
}

intf_mgr::intf_mgr() {
}

void
intf_mgr::intf_foreach(bool (*handler)(intf_id_t, void *), void *arg) {
   IntfMgrImpl * impl = getIntfMgrImpl(this);
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

   IntfMgrImpl * impl = getIntfMgrImpl(this);
   for( auto iter = impl->allIntfStatusDir_->intfStatusIterator( bookmark.intfId_ );
        iter && (*handler)((eos::intf_id_t)iter.key().intfId(), arg);
        ++iter ) {}
}

bool
intf_mgr::exists(intf_id_t id) {
   /* returns true if intf_id_t has a corresponding status. */
   IntfMgrImpl * impl = getIntfMgrImpl(this);
   return !!impl->allIntfStatusDir_->intfStatus( id.intfId_ );
}

void
intf_mgr::description_is(intf_id_t id, char const * descr) {
   IntfMgrImpl * impl = getIntfMgrImpl(this);
   Interface::IntfConfig::Ptr intfConfig = 
      impl->allIntfConfigDir_->intfConfig( id.intfId_ );
   intfConfig->descriptionIs( descr );
}

oper_status_t
intf_mgr::oper_status(intf_id_t id) {
   IntfMgrImpl * impl = getIntfMgrImpl(this);
   Interface::IntfStatus::Ptr intfStatus = 
      impl->allIntfStatusDir_->intfStatus( id.intfId_ );
   if( !intfStatus ) {
      panic( "No matching interface" );
   }
   return convert( intfStatus->operStatus() );
}

intf_mgr * 
get_intf_mgr() {
   static IntfMgrImpl impl;
   return &impl;
}


// 
// intf_handler implementation
//

intf_handler::intf_handler() : watching_all_intfs_(false) {}

// The intf_handler destructor automatically unregisters itself as a
// handler for all interfaces via the intf_mgr
intf_handler::~intf_handler() {
   TRACE0( __PRETTY_FUNCTION__ << " unregistering myself as a handler");
   if( watching_all_intfs_ ) {
      IntfMgrImpl * impl = (IntfMgrImpl *) get_intf_mgr();
      impl->remove_handler(this);
   }
   // TODO: remove per-interface handlers
   // impl->remove_handler( (eos::intf_id_t)iter.key().intfId(), this );
}

void
intf_handler::watch_all_intfs(bool interest) {
   TRACE0( __PRETTY_FUNCTION__ << " registering myself as new handler" );
   if( watching_all_intfs_ == interest ) return;
   IntfMgrImpl * impl = (IntfMgrImpl *) get_intf_mgr();
   if(interest) {
      impl->add_handler(this);
   } else {
      impl->remove_handler(this);
   }
   watching_all_intfs_ = interest;
}

// Not implemented:
// void
// intf_handler::watch_intf(intf_id_t i, bool interest) {
//    TRACE0( __PRETTY_FUNCTION__ << " registering myself as a " <<
//            "interface-specific handler" );
//    IntfMgrImpl * impl = (IntfMgrImpl *) get_intf_mgr();
//    if(interest) {
//       impl->add_handler(i, this);
//    } else {
//       impl->remove_handler(i, this);
//    }
// }

// Dummy implementations for virtual handler methods.
void intf_handler::on_initialized() {}
void intf_handler::on_create(intf_id_t) {}
void intf_handler::on_delete(intf_id_t) {}
void intf_handler::on_oper_status(intf_id_t, oper_status_t) {}
void intf_handler::on_admin_enabled(intf_id_t, bool) {}


//
// IntfConfigSm method implementations
//

void
IntfConfigSm::handleAdminEnabled() {
   TRACE8( __PRETTY_FUNCTION__ << " adminEnabled is "
           << intfConfig()->adminEnabled() );
   IntfMgrImpl * impl = getIntfMgrImpl( eos::get_intf_mgr() );
   intf_id_t intf_id = intf_id_t( (uint32_t)intfId().intfId() );
   impl->on_admin_enabled( intf_id, intfConfig()->adminEnabled() );
}

//
// IntfStatusSm method implementations
//

void
IntfStatusSm::handleOperStatus() {
   TRACE8( __PRETTY_FUNCTION__ );
   IntfMgrImpl * impl = getIntfMgrImpl( eos::get_intf_mgr() );

   intf_id_t intf_id = intf_id_t( (uint32_t)intfId().intfId() );
   impl->on_oper_status( intf_id, intfStatus()->operStatus() );
}

//
// IntfMgrSm method implementations
//

void
IntfMgrSm::handleIntfConfig() {
   TRACE8( __PRETTY_FUNCTION__ );
   for( auto i = allIntfConfigDir()->intfConfigIteratorConst(); i; ++i ) {
      intfConfigSmIs( i.ptr() );
   }
}

void
IntfMgrSm::handleIntfConfig( Arnet::IntfId intfId ) {
   TRACE8( __PRETTY_FUNCTION__ );
   Interface::IntfConfig::PtrConst intfConfig = \
      allIntfConfigDir()->intfConfig( intfId );
   if( intfConfig ) {
      intfConfigSmIs( intfConfig );
   } else {
      intfConfigSmDel( intfId );
   }
}

void
IntfMgrSm::handleIntfStatus() {
   TRACE8( __PRETTY_FUNCTION__ );
   for( auto i = allIntfStatusDir()->intfStatusIteratorConst(); i; ++i ) {
      intfStatusSmIs( i.ptr() );
   }
}

void
IntfMgrSm::handleIntfStatus( Arnet::IntfId intfId ) {
   TRACE8( __PRETTY_FUNCTION__ );
   IntfMgrImpl * impl = getIntfMgrImpl( eos::get_intf_mgr() );
   intf_id_t intf_id = intf_id_t( (uint32_t)intfId.intfId() );
   Interface::IntfStatus::PtrConst intfStatus = \
      allIntfStatusDir()->intfStatus( intfId );
   if( intfStatus ) {
      intfStatusSmIs( intfStatus );
      impl->on_create( intf_id );
   } else {
      intfStatusSmDel( intfId );
      impl->on_delete( intf_id );
   }
}

};
