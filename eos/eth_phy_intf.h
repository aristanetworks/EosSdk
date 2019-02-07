// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ETH_PHY_INTF_H
#define EOS_ETH_PHY_INTF_H

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/eth.h>
#include <eos/intf.h>
#include <eos/iterator.h>
#include <eos/types/eth_phy_intf.h>

namespace eos {

class eth_phy_intf_mgr;

/**
 * A handler for Ethernet Physical Interface events.
 */
class EOS_SDK_PUBLIC eth_phy_intf_handler
   : public base_handler<eth_phy_intf_mgr, eth_phy_intf_handler> {
 public:
   explicit eth_phy_intf_handler(eth_phy_intf_mgr *);

   eth_phy_intf_mgr * get_eth_phy_intf_mgr() const;

   /**
    * Registers this class to receive interface change update notifications.
    *
    * Expects a boolean signifying whether notifications
    * should be propagated to this instance or not.
    */
   void watch_all_eth_phy_intfs(bool);

   /**
    * Registers this class to receive interface change update notifications for the
    * given interface.
    *
    * Expects the id of the corresponding interface and a boolean signifying whether
    * notifications should be propagated to this instance or not.
    */
   void watch_eth_phy_intf(intf_id_t, bool);

   /**
    * Handler called when a physical ethernet interface is created.
    *
    * After on_eth_phy_intf_create is called, the given intf_id is
    * guaranteed to exist (ie eth_phy_intf_mgr::exists will return
    * true). At that point, the intf_id can be used will all methods
    * of the eth_phy_intf_mgr class.
    *
    * This also means that the intf_id can be used with all other
    * relevant *intf_mgr classes (ie intf_mgr and eth_intf_mgr).
    */
   virtual void on_eth_phy_intf_create(intf_id_t);
   /**
    * Handler called when a physical ethernet interface is deleted.
    * 
    * After on_eth_phy_intf_delete is called, the given intf_id is
    * guaranteed to not exist (ie eth_phy_intf_mgr::exists will return
    * false). At that point, the intf_id cannot be used will any
    * methods in the eth_phy_intf_mgr class.
    *
    * This also means that the intf_id can no longer be used with all
    * other relevant *intf_mgr classes (ie intf_mgr and eth_intf_mgr).
    */
   virtual void on_eth_phy_intf_delete(intf_id_t);
   /**
    * Handler called when the presence of the underlying hardware for
    * the physical ethernet interface changes.
    *
    * When a physical interface goes from not-present to present, only
    * on_eth_phy_intf_hardware_present will get called even though
    * other attributes (like the link_speed) of the eth_phy_intf may
    * have changed. Similarly, when the physical interface hardware
    * goes from present to not-present, attributes of the eth_phy_intf
    * (like the link_speed) that are based on the underlying hardware
    * will go back to their default values even though their explicit
    * handlers are not called. It is up to the user to handle the new
    * values of those attributes within the
    * on_eth_phy_intf_hardware_present handler.
    */
   virtual void on_eth_phy_intf_hardware_present(intf_id_t, bool present);
   /// Handler called when the operational link speed changes
   virtual void on_eth_phy_intf_link_speed(intf_id_t, eth_link_speed_t);
   /// Handler called when a transceiver insertion or removal is detected
   virtual void on_eth_phy_intf_transceiver_present(intf_id_t, bool);
};


class eth_phy_intf_iter_impl;

/// Iterator over physical interfaces
class EOS_SDK_PUBLIC eth_phy_intf_iter_t : public iter_base<intf_id_t,
                                                            eth_phy_intf_iter_impl> {
 private:
   friend class eth_phy_intf_iter_impl;
   explicit eth_phy_intf_iter_t(eth_phy_intf_iter_impl * const) EOS_SDK_PRIVATE;
};


class EOS_SDK_PUBLIC eth_phy_intf_mgr : public base_mgr<eth_phy_intf_handler,
                                                        intf_id_t> {
 public:
   virtual ~eth_phy_intf_mgr();

   // Collection management
   virtual eth_phy_intf_iter_t eth_phy_intf_iter() const = 0;

   /**
    * Returns whether the given physical ethernet interface exists.
    *
    * If exists returns true, then this intf_id_t can be successfully
    * passed into every method of the eth_intf_mgr. If not, then
    * methods of the eth_intf_mgr can throw a no_such_interface_error
    * exception.
    *
    * The exists method of all *intf_mgr classes that manage a given
    * interface (ie intf_mgr, eth_intf_mgr, and eth_phy_intf_mgr for
    * physical interfaces) are all guaranteed to return the same
    * result.
    */
   virtual bool exists(intf_id_t) const = 0;

   /// Returns whether the underlying hardware for this interface is present
   virtual bool hardware_present(intf_id_t) const = 0;
   
   /**
    * Returns the "burned in" address of the interface.
    *
    * If the underlying hardware is not present, returns the default
    * eth_addr_t(). Once hardware_present is true, burned_in_eth_addr
    * is guaranteed to be available.
    */
   virtual eth_addr_t burned_in_eth_addr(intf_id_t) const = 0;

   /**
    * Returns the operational link speed.
    *
    * If the underlying hardware is not present, returns
    * LINK_SPEED_UNKNOWN.
    */
   virtual eth_link_speed_t link_speed(intf_id_t) const = 0;

   // Returns the presence of transceiver for the given interface
   virtual bool transceiver_present(intf_id_t) const = 0;

 protected:
   eth_phy_intf_mgr() EOS_SDK_PRIVATE;
   friend class eth_phy_intf_handler;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(eth_phy_intf_mgr);
};


/**
 * The Ethernet interface counter manager.
 * 
 * This class inspects ethernet interface counters and statistics.
 */
class EOS_SDK_PUBLIC eth_phy_intf_counter_mgr {
 public:
   virtual ~eth_phy_intf_counter_mgr();
   
   /// Get the current counters of the given ethernet interface.
   virtual eth_phy_intf_counters_t counters(intf_id_t) const = 0;
   
   /// Get the current bin counters of the given ethernet interface.
   virtual eth_phy_intf_bin_counters_t bin_counters(intf_id_t) const = 0;
   
 protected:
   eth_phy_intf_counter_mgr() EOS_SDK_PRIVATE;
   
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(eth_phy_intf_counter_mgr);
};


}

#include <eos/inline/eth_phy_intf.h>

#endif // EOS_ETH_PHY_INTF_H
