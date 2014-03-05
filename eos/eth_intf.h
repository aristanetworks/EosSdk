// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ETH_INTF_H
#define EOS_ETH_INTF_H

#include <eos/base.h>
#include <eos/eth.h>
#include <eos/intf.h>
#include <eos/iterator.h>

namespace eos {

/**
 * Event handler for ethernet interface specific events.
 *
 * Handles events on ethernet interfaces. Includes physical interfaces
 * and LAGs (port-channels) among other interface types.
 */
class EOS_SDK_PUBLIC eth_intf_handler {
 public:
   eth_intf_handler();
   virtual ~eth_intf_handler();

   /**
    * Registers to receive updates on changes to the interface.
    *
    * @param bool Signifyies whether notifications should be
    * propagated to this handler instance or not.
    */
   void watch_all_eth_intfs(bool);

   /// Handler called when an ethernet interface is created
   virtual void on_eth_intf_create(intf_id_t);
   /// Handler called when an ethernet interface is deleted
   virtual void on_eth_intf_delete(intf_id_t);
   /// Handler called when the mac address of an interface changes
   virtual void on_eth_addr(intf_id_t, eth_addr_t);

 private:
   bool watching_all_intfs_;
};


class eth_intf_iter_impl;

/// Iterator type for ethernet interfaces
class EOS_SDK_PUBLIC eth_intf_iter_t : public iter_base<intf_id_t,
                                                        eth_intf_iter_impl> {
 private:
   friend class eth_intf_iter_impl;
   explicit eth_intf_iter_t(eth_intf_iter_impl * const) EOS_SDK_PRIVATE;
};


/// The ethernet interface manager
class EOS_SDK_PUBLIC eth_intf_mgr {
 public:
   // Collection management
   eth_intf_iter_t eth_intf_iter() const;
   typedef bool (*callback_func_eth_intf)(intf_id_t, void * context);
   void eth_intf_foreach(callback_func_eth_intf handler, void * context);
   void eth_intf_foreach(callback_func_eth_intf handler, void * context,
                         intf_id_t bookmark);
   bool exists(intf_id_t) const;

   // Attribute accessors
   /// Returns the operational ethernet address of the interface
   eth_addr_t eth_addr(intf_id_t) const;
   /// Returns the currently configured ethernet address
   eth_addr_t configured_eth_addr(intf_id_t) const;

   /**
    * Configures the ethernet address of the interface
    * @param intf_id_t The interface ID of the interface to change the address of
    * @param eth_addr_t The address to set
    */
   void eth_addr_is(intf_id_t, eth_addr_t);

 protected:
   eth_intf_mgr() EOS_SDK_PRIVATE;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(eth_intf_mgr);
};

/// Returns an ethernet interface manager instance
eth_intf_mgr * get_eth_intf_mgr() EOS_SDK_PUBLIC;

}

#endif // EOS_ETH_INTF_H
