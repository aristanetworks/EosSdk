// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

/**
 * @file
 * MAC address table management module.
 *
 * This module offers a MAC address table manager, used to define MAC addresses
 * in system configuration.
 *
 * This module also offers a handler that provides notifications when a MAC
 * address has been learned (or forgotten).
 *
 * Please refer to examples/SimpleMac.cpp for an example.
 */

#ifndef EOS_MAC_TABLE_H
#define EOS_MAC_TABLE_H

#include <eos/base.h>
#include <eos/eth.h>
#include <eos/intf.h>
#include <eos/iterator.h>

#include <eos/types/mac_table.h>

namespace eos {

class mac_table_mgr;

/**
 * Handler for the MAC table.
 * 
 * This handler provides notifications when MAC addresses are learned on or
 * removed from an interface.
 * Note: This handler currently only provides notifications for
 * unicast MAC addresses.
 */
class EOS_SDK_PUBLIC mac_table_handler :
      public base_handler<mac_table_mgr, mac_table_handler> {
 public:
    explicit mac_table_handler(mac_table_mgr *mgr);
    mac_table_mgr * get_mac_table_mgr() const;

    /**
     * Registers this class to receive change updates from the MAC table.
     *
     * Expects a boolean signifying whether notifications should be
     * propagated to this instance or not.
     */
    void watch_all_mac_entries(bool);

    /**
     * Registers this class to receive change updates on the given MAC entry.
     *
     * Expects the key of the corresponding MAC address and a boolean signifying
     * whether notifications should be propagated to this instance or not.
     */
    void watch_mac_entry(mac_key_t const & key, bool);
    /**
     * This handler is called when a unicast MAC entry is learned for the first
     * time, or when a unicast MAC entry has moved to a different interface.
     */
    virtual void on_mac_entry_set(mac_entry_t const & entry);
    /**
     * This handler is called when a unicast entry is removed from the MAC address
     * table.
     */
    virtual void on_mac_entry_del(mac_key_t const & key);
};

/**
 * MAC table iterators.
 * These provide iteration over the entries in the MAC address table.
 */

/// A MAC table iterator for unicast and multicast entries configured statically.
class mac_table_iter_impl;
/**
 * A MAC table iterator for unicast entries either learned dynamically or
 * configured explicitly.
 */
class mac_table_status_iter_impl;

class EOS_SDK_PUBLIC mac_table_iter_t : 
   public iter_base<mac_key_t, mac_table_iter_impl> {
 private:
    friend class mac_table_iter_impl;
    explicit mac_table_iter_t(
          mac_table_iter_impl * const) EOS_SDK_PRIVATE;
};

class EOS_SDK_PUBLIC mac_table_status_iter_t : 
   public iter_base<mac_key_t, mac_table_status_iter_impl> {
 private:
    friend class mac_table_status_iter_impl;
    explicit mac_table_status_iter_t(
          mac_table_status_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * Manager for the MAC address table.
 */
class EOS_SDK_PUBLIC mac_table_mgr : public base_mgr<mac_table_handler, mac_key_t> {
 public:
   virtual ~mac_table_mgr();

   // Accessors //
   /// Iterator for all configured MAC addresses.
   virtual mac_table_iter_t mac_table_iter() const = 0;
   /// Iterator for the MAC address table.
   virtual mac_table_status_iter_t mac_table_status_iter() const = 0;
   /**
    * Retrieves a mac_entry_t given the VLAN and MAC address key from the
    * collection of configured entries. 
    *
    * This entry contains the interface (or, for multicast entries, the interfaces)
    * that the given key was configured on. If the entry has not been configured, an
    * empty mac_entry_t() is returned.
    * @param mac_key_t The MAC address key object, consisting of a VLAN and
    * a MAC address, which are used to retrieve that unique MAC entry.
    */
   virtual mac_entry_t mac_entry(mac_key_t const & key) const = 0;
   /**
    * Returns a mac_entry_t given a VLAN and MAC address from the collection of
    * configured entries.
    *
    * @deprecated, please use mac_entry(mac_key_t const & key) method instead.
    */
   virtual mac_entry_t mac_entry(vlan_id_t vlan, eth_addr_t mac) const = 0;
   /**
    * Retrieves a mac_entry_t given the VLAN and MAC address key from the
    * collection of entries either learned dynamically or explicitly configured. 
    *
    * This entry contains the interface (or, for multicast entries, the interfaces)
    * that the given key has been learned on. If the entry has not been learned,
    * an empty mac_entry_t() is returned.
    * Note: At this time, a multicast MAC entry's status directly mirrors its
    * configuration and does not reflect whether or not the entry has been
    * programmed into hardware.
    * @param mac_key_t The MAC address key object, consisting of a VLAN and
    * a MAC address, which are used to retrieve that unique MAC entry.
    */
   virtual mac_entry_t mac_entry_status(mac_key_t const & key) const = 0;
   /// Returns the type of the programmed MAC entry.
   virtual mac_entry_type_t type(mac_key_t const & key) const = 0;
   /// Returns the number of times the MAC entry has moved.
   virtual uint32_t moves(mac_key_t const & key) const = 0;
   /// Returns the time at which the MAC entry last moved (since boot).
   virtual seconds_t last_move_time(mac_key_t const & key) const = 0;

   // Mutators //
   /**
    * Configure a MAC address statically as "learned" on a given interface (or set
    * of interfaces for multicast MAC entries).
    */
   virtual void mac_entry_set(mac_entry_t const & entry) = 0;
   /**
    * Remove a MAC entry with the given key from the collection of entries that 
    * were either learned dynamically or configured explicitly.
    */
   virtual void mac_entry_del(mac_key_t const & key) = 0;


 protected:
   mac_table_mgr() EOS_SDK_PRIVATE;
   friend class mac_table_handler;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(mac_table_mgr);
};


} // end namespace eos

#include <eos/inline/mac_table.h>

#endif // EOS_MAC_TABLE_H
