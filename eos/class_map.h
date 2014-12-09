// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_CLASS_MAP_H
#define EOS_CLASS_MAP_H

#include <map>
#include <utility>

#include <eos/acl.h>
#include <eos/iterator.h>
#include <eos/policy_map.h>

#include <eos/types/class_map.h>

/**
 * @file
 * Class map manipulation.
 *
 * This module provides access to the management of class maps.
 * Classification or "class" maps, provide a way for the network
 * operator to classify packets arriving on an interface. Together
 * with the policy_map_mgr in policy_map.h, classified traffic can drive
 * policy features, such as PBR.
 */

namespace eos {

class class_map_iter_impl;

/// An iterator providing forwards only iteration over collections of class maps
class EOS_SDK_PUBLIC class_map_iter_t : public iter_base<class_map_key_t,
                                                         class_map_iter_impl> {
 private:
   friend class class_map_iter_impl;
   explicit class_map_iter_t(class_map_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * EOS class map manager.
 *
 * This manager provides access to EOS traffic classifiers, or "class
 * maps". Class maps are referred to by policy maps (policy_map.h) to classify
 * traffic that should be subject to the policy's actions.
 */
class EOS_SDK_PUBLIC class_map_mgr {
 public:
   virtual ~class_map_mgr();

   /**
    * Resync mediates class map configuration into a known good state.
    *
    * To start a resync, call resync_init() and then use the functions
    * in the module to manipulate class maps like normal, setting them
    * with class_map_is(). After all entries have been set, call
    * resync_complete(), which will delete existing class_maps that
    * were not added or modified during resync.
    *
    * During resync, this manager will act like it is referencing a
    * temporary table that starts off empty. Thus, methods like exist,
    * del, and getters will act only on that temporary table,
    * regardless of the real values in Sysdb. The one exception is
    * iteration; they will traverse the table stored in Sysdb,
    * regardless of whether or not the manager is in resync mode.
    */
   virtual void resync_init() = 0;
   /// Completes any underway resync operation.
   virtual void resync_complete() = 0;

   /// Returns true if and only if the provided key exists in the system config
   virtual bool exists(class_map_key_t const & key) const = 0;

   /**
    * Returns the class map for the provided class map key.
    * If there is no class map for the key, returns a default class_map_t
    */
   virtual class_map_t class_map(class_map_key_t const & key) const = 0;

   /// Sets a class map and commits its configuration
   virtual void class_map_is(class_map_t const & class_map) = 0;

   /// Provides iteration over the configured class maps for a feature
   virtual class_map_iter_t class_map_iter(policy_feature_t) const = 0;

   /// Deletes the class map specified
   virtual void class_map_del(class_map_key_t const & key) = 0;

 protected:
   class_map_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(class_map_mgr);
};

} // end namespace eos

#endif // EOS_CLASS_MAP_H
