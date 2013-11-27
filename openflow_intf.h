// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_OPENFLOW_INTF_H
#define EOS_OPENFLOW_INTF_H

#include <eos/intf.h>

namespace eos {

class openflow_intf_handler {
 public:
   openflow_intf_handler();
   ~openflow_intf_handler();

   // Registers this class to receive updates on changes
   // to openflow interfaces. Expects a boolean signifying
   // whether notifications should be propagated to this
   // instance or not.
   void watch_all_intfs( bool );

   // Called after this instance has been internally initialized
   // and is ready to start receiving notifications.
   virtual void on_initialized();
   // Handler called when an interface with openflow attributes
   // is created
   virtual void on_create(intf_id_t);
   // Handler called when an interface with openflow attributes
   // is deleted
   virtual void on_delete(intf_id_t);
   // Handler called when the openflow port id changes.
   virtual void on_openflow_port_id(intf_id_t intf_id, uint32_t);
};

class openflow_intf_mgr {
 public:

   // Collection management
   void openflow_intf_foreach(bool (*handler)(intf_id_t, void *), void *);
   void openflow_intf_foreach(bool (*handler)(intf_id_t, void *), void *,
                              intf_id_t bookmark);
   
   // Attribute accessors
   uint32_t openflow_port_id(intf_id_t);
   intf_id_t intf_id(uint32_t);
   
 //=> private:
   openflow_intf_mgr();

 private:
   openflow_intf_mgr(openflow_intf_mgr const &);
};

openflow_intf_mgr * get_openflow_intf_mgr();

}

#endif // EOS_OPENFLOW_INTF_H
