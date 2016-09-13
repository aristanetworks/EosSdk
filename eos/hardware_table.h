// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_HARDWARE_TABLE_H
#define EOS_HARDWARE_TABLE_H

#include <string>

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/iterator.h>
#include <eos/types/hardware_table.h>

/**
 * @file
 * Hardware table usage and capacity statistics
 *
 * This module exposes the usage statistics for the various hardware
 * tables used by the system. This is useful for agents that want to
 * track how many entries are used or available across the various
 * tables, either for monitoring purposes or so they can take specific
 * actions when a table is close to becoming full. Usage is exposed
 * per unique table, feature, and chip combination. Example tables
 * include 'TCAM', 'LEM', 'ECMP', and 'LPM' tables, while the features
 * look like "IPV4", "ACL", "MPLS", or even platform-specific features
 * like "V6Hosts".
 *
 * The usage statistics include the number of used, free, committed, 
 * maximum available entries, and the high watermark which records 
 * the maximum number of entries used by this feature so far and the 
 * time-stamp when the last high watermark value was hit. The capacity 
 * calculation is triggered every 10 seconds.
 *
 * For example, hardware table T has 1000 entries, and the allocation 
 * block size is 100. Table T is used by feature F1 and F2.
 * 200 entries have been allocated to Feature F1, 101 are in use.
 * 300 entries have been allocated to Feature F2, 299 are in use.
 * 500 entries are still in the shared pool of available entries.
 * Free entries are those that are committed but not used (200-101 
 * for feature F1) and the available entries in the shared pool (500).
 * --------------------------------------------------------------
 *   table_key   used     free  committed    max   high_watermark
 * --------------------------------------------------------------
 * (T, F1, --)    101   99+500        200   1000        (150, 10)
 * (T, F2, --)    299    1+500        300   1000        (299, 20)
 * --------------------------------------------------------------
 */

namespace eos {

class hardware_table_mgr;
class hardware_table_iter_impl;

/**
 * This class provides handler APIs to receive changes of hardware table.
 */
class EOS_SDK_PUBLIC hardware_table_handler : 
      public base_handler<hardware_table_mgr, hardware_table_handler> {
 public:
   explicit hardware_table_handler(hardware_table_mgr *mgr);

   hardware_table_mgr * get_hardware_table_mgr() const;

   /**
    * Register this handler to receive usage updates for all features
    * across all tables. To unsubscribe to events, pass 'false'.
    */
   void watch_all_hardware_tables(bool enable);
   
   /**
    * Register this handler to receive usage updates for a single
    * table/feature/chip combination. 
    *
    * If 'chip' is specified as "*" in the key, register this handler 
    * to receive all updates for the named feature/table combination. 
    * If this feature uses different numbers of entries per-chip, the 
    * handler will fire for updates on each chip. Otherwise this is 
    * equivalent to watching a unique hardware_table_key.
    *
    * If 'feature' is "*" in the key, register this handler to receive
    * all updates for the named chip/table combination.
    *
    * If 'chip' and 'feature' are both "*" in the key, register this
    * handler to receive all updates for the specified table.
    */
   void watch_hardware_table(hardware_table_key_t const & key, bool enable);

   /**
    * Handler called when a new table key is created or any of the 
    * fields in an existing usage entry changes. The capacity calculation 
    * is triggered every 10 seconds.
    *
    * For example, enabling multicast will allocate space in the TCAM, 
    * triggering this callback with the new ['TCAM', 'Multicast'] table key. 
    *
    * The handler can also be triggered because the feature is now using 
    * more entries (e.g. the 'IPv4' feature learned and added more routes 
    * to hardware), because the feature has been allocated more committed
    * entries (e.g. the 'ACL' feature now requires a second bank of
    * the TCAM), or because another feature that shares this table has
    * increased it's used or committed entries, causing this feature's
    * free entries to decrease.
    */
   virtual void on_hardware_table_entry_set(hardware_table_key_t const & key, 
                                            hardware_table_entry_t const & entry);

   /**
    * Handler called when a table key is deleted.
    */
   virtual void on_hardware_table_entry_del(hardware_table_key_t const & key);
};

/*
 * An iterator over the keys of hardware tables.
 */
class EOS_SDK_PUBLIC hardware_table_iter_t : 
            public iter_base<hardware_table_key_t, hardware_table_iter_impl> {
 private:
    friend class hardware_table_iter_impl;
    explicit hardware_table_iter_t(hardware_table_iter_impl * const) 
                                                      EOS_SDK_PRIVATE;
};

/**
 * A manager that exposes information about the hardware table's capacity 
 * and usage.
 *
 * Create one mgr by calling sdk.get_hardware_mgr() prior to starting the agent 
 * main loop. The manager can be used once the agent_handler::on_initialized 
 * function is called.
 */
class EOS_SDK_PUBLIC hardware_table_mgr : 
      public base_mgr<hardware_table_handler, hardware_table_key_t> {
 public:
   virtual ~hardware_table_mgr();

   /** 
    * Check whether the hardware table key exists. That is, check whether the 
    * specified table key exposes usage data.
    *
    * If exists returns true, this hardware_table_key_t can be successfully 
    * passed into every method of this hardware_table_mgr. If not, these methods 
    * will return default data such as 0 or hardware_table_usage_t(). 
    */
   virtual bool exists(hardware_table_key_t const & key) const  = 0;

   /**
    * Get an iterator over the existing tables. Yields a hardware_table_key_t 
    * for each table, feature, and chip combination that is being tracked by 
    * software.
    */
   virtual hardware_table_iter_t hardware_table_iter() const = 0;

   /**
    * Get the usage statistics for a given hardware_table_key. If the key does 
    * not exist, an empty hardware_table_usage_t is returned.
    */
   virtual hardware_table_usage_t usage(hardware_table_key_t const & key) const = 0;

   /**
    * Get the theoretical maximum number of entries available, assuming no other
    * features are using this table. If the key does not exist, 0 is returned.
    */
   virtual uint32_t max_entries(hardware_table_key_t const & key) const = 0;

   /* 
    * Get the high watermark statistics for a given hardware_table_key. If the key
    * does not exist, an empty hardware_table_high_watermark_t is returned.
    */
   virtual hardware_table_high_watermark_t 
      high_watermark(hardware_table_key_t const & key) const = 0;

 protected:
   hardware_table_mgr() EOS_SDK_PRIVATE;
   friend class hardware_table_handler;
   
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(hardware_table_mgr);
};

} // end namespace eos

#include <eos/inline/hardware_table.h>


#endif // EOS_HARDWARE_TABLE_H
