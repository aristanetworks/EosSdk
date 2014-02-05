// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ETH_INTF_H
#define EOS_ETH_INTF_H

#include <eos/base.h>

#include <eos/eth.h>
#include <eos/intf.h>

namespace eos {

// Handles events on ethernet interfaces. Includes physical interfaces
// and lags (port-channels) among other interface types.
class EOS_SDK_PUBLIC eth_intf_handler {
 public:
   eth_intf_handler();
   virtual ~eth_intf_handler();

   // Registers this class to receive updates on changes to the
   // interface. Expects a boolean signifying whether notifications
   // should be propagated to this instance or not.
   void watch_all_eth_intfs(bool);

   // Handler called when an ethernet interface is created
   virtual void on_eth_intf_create(intf_id_t);
   // Handler called when an ethernet interface is deleted
   virtual void on_eth_intf_delete(intf_id_t);
   // Handler called when the mac address of an interface changes
   virtual void on_eth_addr(intf_id_t, eth_addr_t);

 private:
   bool watching_all_intfs_;
};


class EOS_SDK_PUBLIC eth_intf_mgr {
 public:
   // Collection management
   typedef bool (*callback_func_eth_intf)(intf_id_t, void * context);
   void eth_intf_foreach(callback_func_eth_intf handler, void * context);
   void eth_intf_foreach(callback_func_eth_intf handler, void * context,
                         intf_id_t bookmark);
   bool exists(intf_id_t) const;

   // Attribute accessors
   // Read the operational ethernet address of the interface
   eth_addr_t eth_addr(intf_id_t) const;
   // Read the currently configured ethernet address
   eth_addr_t configured_eth_addr(intf_id_t) const;

   // Configure the ethernet address of the interface
   void eth_addr_is(intf_id_t, eth_addr_t);

 protected:
   eth_intf_mgr() EOS_SDK_PRIVATE;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(eth_intf_mgr);
};

eth_intf_mgr * get_eth_intf_mgr() EOS_SDK_PUBLIC;

}

#endif // EOS_ETH_INTF_H
