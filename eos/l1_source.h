// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_L1_SOURCE_H
#define EOS_L1_SOURCE_H

#include <eos/base.h>
#include <eos/iterator.h>

#include <eos/types/intf.h>
#include <eos/types/l1_source.h>

/**
 * @file
 * L1 source management module.
 * 
 * On platforms with a crosspoint, interfaces can configure their source using a
 * config.
 * 
 * This module provides APIs to set and delete source configs, watch for
 * config changes, get source configs and source statuses, and iterate through
 * source configs and source statuses.
 */

namespace eos {

class l1_source_mgr;

class EOS_SDK_PUBLIC l1_source_handler : public base_handler<l1_source_mgr,
                                                             l1_source_handler> {
   public:
      explicit l1_source_handler(l1_source_mgr *);
      l1_source_mgr * get_l1_source_mgr() const;

      /** 
       * Register to receive notification when l1 source config for any interface
       * changes.
       */
      void watch_all_l1_source(bool);

      /**
       * Register to receive notification when l1 source config of an interface
       * changes.
       */
      void watch_l1_source(intf_id_t, bool);

      /**
       * Called when l1 source of an interface is set.
       */
      virtual void on_l1_source_set(intf_id_t);

      /**
       * Called when l1 source of an interface is removed.
       */
      virtual void on_l1_source_del(intf_id_t);
};

class l1_source_iter_impl;

/// An iterator that yields a intf_id_t for each l1 source config/status.
class EOS_SDK_PUBLIC l1_source_iter_t : public iter_base<intf_id_t,
                                                         l1_source_iter_impl> {
  private:
      friend class l1_source_iter_impl;
      explicit l1_source_iter_t(l1_source_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * The l1 source manager.
 * This class inspects and configures l1 source for an interface.
 */
class EOS_SDK_PUBLIC l1_source_mgr : public base_mgr<l1_source_handler, intf_id_t> {
   public:
      virtual ~l1_source_mgr();
      
      /**
       * Configures l1 source of an interface.
       */
      virtual void l1_source_is(intf_id_t, l1_source_t source) = 0;
      
      /**
       * Remove the l1 source of an interface.
       */
      virtual void l1_source_del(intf_id_t) = 0;
      
      /**
       * Returns whether a l1 source config exists for the interface.
       */
      virtual bool exists(intf_id_t) const = 0;

      /**
       * Returns the source config for an interface.
       * If no source config is set, returns the default source config.
       */
      virtual l1_source_t l1_source_config(intf_id_t) = 0;

      /**
       * Returns the source status for an interface.
       * If no source status exists, returns the default source status.
       */
      virtual l1_source_t l1_source_status(intf_id_t) = 0;

      /**
       * Iterator for l1 source configuration.
       */
      virtual l1_source_iter_t l1_source_config_iter() const = 0;

      /**
       * Iterator for l1 source status.
       */
      virtual l1_source_iter_t l1_source_status_iter() const = 0;

      /**
       * Configures the description of an application interface.
       */
      virtual void app_description_is(intf_id_t, std::string) = 0;
      
      /**
       * Remove the description of an application interface.
       */
      virtual void app_description_del(intf_id_t) = 0;

   protected:
      l1_source_mgr() EOS_SDK_PRIVATE;
      friend class l1_source_handler;

   private:
      EOS_SDK_DISALLOW_COPY_CTOR(l1_source_mgr);
};

}

#include <eos/inline/l1_source.h>

#endif // EOS_L1_SOURCE_H
