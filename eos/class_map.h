// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_CLASS_MAP_H
#define EOS_CLASS_MAP_H

#include <utility>

#include <eos/acl.h>
#include <eos/iterator.h>
#include <eos/policy.h>

/**
 * Class map manipulation.
 *
 * This module provides access to the management of class maps.
 * Classification or "class" maps, provide a way for the network
 * operator to classify packets arriving on an interface. Together
 * with the policy_map_mgr in policy.h, classified traffic can drive
 * policy features, such as PBR.
 */

namespace eos {

/**
 * A class map match rule uses an ACL to match classified traffic.
 *
 * Values of this type are returned from the class_map_rule_iter,
 * to program class maps, either supply one of these or the acl_key_t
 * directly to class_map_mgr's class_map_rule_set().
 */
class EOS_SDK_PUBLIC class_map_rule_t {
 public:
   class_map_rule_t();
   explicit class_map_rule_t(acl_key_t const & acl_key);

   /// The ACL name and type to use as a class map match rule.
   acl_key_t const & acl_key() const;

 private:
   acl_key_t acl_key_;
};

typedef std::pair<uint32_t, class_map_rule_t> class_map_rule_entry_t;

class class_map_iter_impl;

/// An iterator providing forwards only iteration over collections of class maps
class EOS_SDK_PUBLIC class_map_iter_t : public iter_base<policy_map_key_t,
                                                         class_map_iter_impl> {
 private:
   friend class class_map_iter_impl;
   explicit class_map_iter_t(class_map_iter_impl * const) EOS_SDK_PRIVATE;
};

class class_map_rule_iter_impl;

/// An iterator providing forwards iteration through the rules of a given class map
class EOS_SDK_PUBLIC class_map_rule_iter_t
   : public iter_base<class_map_rule_entry_t, class_map_rule_iter_impl> {
 private:
   friend class class_map_rule_iter_impl;
   explicit class_map_rule_iter_t(
         class_map_rule_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * EOS class map manager.
 *
 * This manager provides access to EOS traffic classifers, or "class
 * maps". Class maps are referred to by policy maps (policy.h) to classify
 * traffic that should be subject to the policy's actions.
 */
class EOS_SDK_PUBLIC class_map_mgr {
 public:
   virtual ~class_map_mgr();

   /**
    * Sets a class map match rule at a sequence number in the class map.
    * On the class map identified by the key, at the sequence number,
    * which cannot be 0, set a rule to match packets which are matched
    * by the provided ACL.
    */
   virtual void class_map_rule_set(policy_map_key_t const &,
                                   uint32_t seq,
                                   acl_key_t const &) = 0;

   /**
    * Sets a class map match rule on the class map.
    * Overwirtes any rule at the sequence number, which cannot be 0,
    * using the provided populated class map rule.
    */
   virtual void class_map_rule_set(policy_map_key_t const &,
                                   uint32_t seq,
                                   class_map_rule_t const &) = 0;

   /// Removes the numbered rule from the class map.
   virtual void class_map_rule_del(policy_map_key_t const &, uint32_t) = 0;

   /// Provides iteration over the configured class maps for a feature.
   virtual class_map_iter_t class_map_iter(policy_feature_t) const = 0;

   /// Provides iteration over the rules of the supplied class map.
   virtual class_map_rule_iter_t class_map_rule_iter(policy_map_key_t const &) const
      = 0;

   /// Deletes the class map specified.
   virtual void class_map_del(policy_map_key_t const &) = 0;

   /**
    * Commits all outstanding class map changes.
    *
    * There is no explicit notification of this configuration change,
    * but configuration changes made will be seen when iterating over
    * class maps after this function completes.
    */
   virtual void class_map_commit() = 0;

 protected:
   class_map_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(class_map_mgr);
};

} // end namespace eos

// The inline header relies on definitions above
#include <eos/inline/class_map.h>

#endif // EOS_CLASS_MAP_H
