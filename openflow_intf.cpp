// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <EosSdk/openflow_intf.h>
#include <EosSdk/Mount.h>
#include <eos/types.h>
#include <Tac/Tracing.h>

DEFAULT_TRACE_HANDLE( "EosSdkOpenFlowIntf" );

namespace eos {

class OpenFlowIntfMgrImpl : public openflow_intf_mgr,
                            public MountHandler {
 public:
   OpenFlowIntfMgrImpl() {
      TRACE0( __PRETTY_FUNCTION__ );
   }

   virtual void doMounts( const Sysdb::MountGroup::Ptr & mg ) {
      TRACE0( __PRETTY_FUNCTION__ );
   }

   virtual void onMountsComplete( const Sysdb::EntityManager::Ptr & em ) {
      TRACE0( "OpenFlowIntfMgrImpl: all mounts completed" );
   }

};

OpenFlowIntfMgrImpl *
getOpenFlowIntfMgrImpl(openflow_intf_mgr *me) {
   OpenFlowIntfMgrImpl * impl = static_cast<OpenFlowIntfMgrImpl *>(me);
   assert( impl == get_openflow_intf_mgr() );
   return impl;
}

openflow_intf_mgr::openflow_intf_mgr() {
}

void
openflow_intf_mgr::openflow_intf_foreach(bool (*handler)(intf_id_t, void *),
                                         void *arg) {
   // OpenFlowIntfMgrImpl * impl = getOpenFlowIntfMgrImpl(this);
}

void
openflow_intf_mgr::openflow_intf_foreach(bool (*handler)(intf_id_t, void *),
                                         void *arg, intf_id_t bookmark) {
   /* Starting with the first element after bookmark's position, for
    * each interface, call the supplied handler callback with the
    * corresponding intf_id_t and arg. If callback returns false, we
    * stop iteration.  */

   // OpenFlowIntfMgrImpl * impl = getOpenFlowIntfMgrImpl(this);
}


uint32_t
openflow_intf_mgr::openflow_port_id(intf_id_t id) {
   // OpenFlowIntfMgrImpl * impl = getOpenFlowIntfMgrImpl(this);
   return 0;
}

intf_id_t
openflow_intf_mgr::intf_id(uint32_t openflow_port_id) {
   // OpenFlowIntfMgrImpl * impl = getOpenFlowIntfMgrImpl(this);
   return intf_id_t((uint32_t)0);
}

openflow_intf_handler::openflow_intf_handler() {
}

openflow_intf_handler::~openflow_intf_handler() {
}

void
openflow_intf_handler::watch_all_intfs( bool watch ) {
}

void
openflow_intf_handler::on_initialized(){
}

void
openflow_intf_handler::on_create(intf_id_t intf_id) {
}

void
openflow_intf_handler::on_delete(intf_id_t intf_id) {
}

void
openflow_intf_handler::on_openflow_port_id(intf_id_t intf_id,
                                           uint32_t openflow_port_id) {
}

openflow_intf_mgr * 
get_openflow_intf_mgr() {
   static OpenFlowIntfMgrImpl impl;
   return &impl;
}

}
