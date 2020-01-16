// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_POLICY_H
#define EOS_POLICY_H

#include <functional>

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/iterator.h>

/**
 * @file
 * Policy map manipulation.
 *
 * This module permits the manipulation of policy maps used in the
 * creation of service policies that can be applied to one or more
 * types of hardware features, beginning with Policy Based Routing
 * (PBR).
 *
 * Policy maps for PBR (policy based routing) can match rules of
 * either an IPv4 access list (including both source, destination
 * addresses and all normal ACL flags) or any MPLS traffic.
 *
 * Policy maps are constructed by key (consisting of a name and a
 * feature, only eos::POLICY_FEATURE_PBR is presently supported), and
 * the above rules are configured using the policy_map_mgr. For example,
 * to source route traffic matching the existing ACL "netblock-fe" for
 * a PBR policy named "src-routing-fe", use this code in a handler with
 * access to the policy_map_mgr object as policy_map_mgr() in scope.
 *
 * @code
 *   eos::policy_map_key_t pm_key("src-routing-fe", eos::POLICY_FEATURE_PBR);
 *   eos::acl_key_t acl_key("netblock-fe", eos::ACL_TYPE_IPV4);
 *   eos::class_map_t cm(pm_key);
 *   eos::class_map_rule_t cm_rule(acl_key);
 *   eos::policy_map_t pm(pm_key);
 *   eos::policy_map_rule_t pm_rule(pm_key);
 *   eos::policy_map_action_t action(eos::POLICY_ACTION_NEXTHOP_GROUP);
 *   action.nexthop_group_name_is("nhg-fe");
 *   pm_rule.action_set(action);
 *   cm.rule_set(1, cm_rule);
 *   pm.rule_set(1, pm_rule);
 *   policy_map_mgr()->policy_map_is(pm);
 *   // Apply to Ethernet3/1 (PBR policies are always applied ACL_IN (inbound).
 *   policy_map_mgr()->policy_map_apply(pm_key, eos::intf_id_t("Ethernet3/1"),
 *                                      eos::ACL_IN, true);
 * @endcode
 *
 * To instead program that same policy matching MPLS traffic instead
 * of an IPv4 ACL, use the following pattern, noting that we
 * explicitly supply a new class map key referring to the special
 * eos::CLASS_MAP_MPLS_ANY name and skip binding the ACL to the class
 * map entirely:
 *
 * @code
 *   eos::policy_map_key_t pm_key("src-routing-fe", eos::POLICY_FEATURE_PBR);
 *   eos::class_map_key_t cm_key(eos::CLASS_MAP_MPLS_ANY, eos::POLICY_FEATURE_PBR);
 *   eos::class_map_t cm(cm_key);
 *   eos::policy_map_rule_t pm_rule(cm_key);
 *   eos::policy_map_action_t action(eos::POLICY_ACTION_NEXTHOP_GROUP);
 *   action.nexthop_group_name_is("nhg-fe");
 *   pm_rule.action_set(action);
 *   cm.rule_set(1, cm_rule);
 *   pm.rule_set(1, pm_rule);
 *   policy_map_mgr()->policy_map_is(pm);
 *   // Finally, apply the policy as before
 * @endcode
 *
 * A valid policy map may have either:
 *
 * 1. One or more rules matching class maps matching one or more IPv4 ACLs.
 * 2. A single policy map rule matching eos::CLASS_MAP_MPLS_ANY class,
 *    which itself may have only a single action
 *
 * Using both "IP ACL" and "MPLS any" modes in the same policy map is not
 * supported, and a eos::configuration_error will be thrown by the policy
 * map when attempting to set both rules, or attempting to set more than
 * one eos::CLASS_MAP_MPLS_ANY class map match rule per policy map.
 */

// Provide the hash functor for the policy_map_action_t type.
// This allows users to use policy_map_action_t's without explicitly
// supplying the functor to the STL collection template.
// This specialization must be placed here, prior to instantiation.

namespace eos {
// Forward declarations used by std::hash specializations below
class policy_map_action_t;
class policy_map_key_t;
}

namespace std {

template <>
struct EOS_SDK_PUBLIC hash<eos::policy_map_action_t> {
   size_t operator() (eos::policy_map_action_t const &) const;
};

template <>
struct EOS_SDK_PUBLIC hash<eos::policy_map_key_t> {
   size_t operator() (eos::policy_map_key_t const &) const;
};

} // end namespace std

#include <eos/types/policy_map.h>

namespace eos {

class policy_map_iter_impl;

/// An iterator providing forwards only iteration over collections of policy maps
class EOS_SDK_PUBLIC policy_map_iter_t : public iter_base<policy_map_key_t,
                                                          policy_map_iter_impl> {
 private:
   friend class policy_map_iter_impl;
   explicit policy_map_iter_t(policy_map_iter_impl * const) EOS_SDK_PRIVATE;
};


// Forward declaration for policy_map_handler
class policy_map_mgr;

/**
 * Event handler for policy feature specific events.
 *
 * Callbacks about failures to program policy features into hardware
 * are reported via this handler.
 */
class EOS_SDK_PUBLIC policy_map_handler : public base_handler<policy_map_mgr,
                                                              policy_map_handler> {
 public:
   /// Constructs a policy map handler for the supplied policy hardware feature
   explicit policy_map_handler(policy_map_mgr *);

   /// Returns a pointer to the policy map manager for use in a derived handler
   policy_map_mgr * get_policy_map_mgr() const;

   /**
    * Registers to receive updates on changes to this policy feature.
    *
    * @param key The policy feature to receive notifications for
    * @param interest Receives notifications if and only if true.
    */
   void watch_policy_map(policy_map_key_t const & key, bool interest);
   /**
    * Registers to receive updates on changes to this policy feature.
    *
    * @param key The policy feature to receive notifications for
    * @param agent_name The agent which configures the policy being watched
    * @param interest Receives notifications if and only if true.
    */
   void watch_policy_map(policy_map_key_t const & key,
                         std::string const & agent_name, bool interest);

   /**
    * Callback fired upon successful policy map application.
    *
    * @param policy_map_key_t The key identifying the updated policy map.
    */
   virtual void on_policy_map_sync(policy_map_key_t const &);

   /**
    * Callback fired when policy map commit or apply operations failed.
    *
    * @param policy_map_key_t The policy map which failed to update.
    * @param message An error message which may be the empty string.
    */
   virtual void on_policy_map_sync_fail(policy_map_key_t const &,
                                        std::string const & message);

   /**
    * Callback fired when policy map configuration changes.
    *
    * @param name Policy map name.
    */
   virtual void on_policy_map_config_set(policy_map_key_t const &);

 protected:
   policy_map_mgr * policy_map_mgr_;
   policy_feature_t feature_;
};


/**
 * EOS policy map manager.
 *
 * The policy manager provides access to policy-map management, as
 * well as policy map application to interfaces.
 */
class EOS_SDK_PUBLIC policy_map_mgr : public base_mgr<policy_map_handler,
                                                      policy_map_key_t> {
 public:
   virtual ~policy_map_mgr();

   /**
    * Resync
    */
   virtual void resync_init() = 0;
   /// Completes any underway resync operation.
   virtual void resync_complete() = 0;

   /// Returns true if and only if the provided policy map key is configured
   virtual bool exists(policy_map_key_t const & key) const = 0;

   virtual policy_map_t policy_map(policy_map_key_t const & key) const = 0;
   virtual void policy_map_is(policy_map_t const & policy_map) = 0;
   virtual void policy_map_del(policy_map_key_t const & key) = 0;

   /**
    * Provides iteration over the configured policy maps for a feature.
    */
   virtual policy_map_iter_t policy_map_iter(policy_feature_t) const = 0;

   /**
    * Applies or unapplies a policy map on the given interface and direction.
    * @param policy_map_key_t Name and type of the policy map to [un]apply
    * @param intf_id_t The interface ID of the interface to [un]apply
    *  the policy map.
    * @param acl_direction_t The direction in which to [un]apply the policy map
    * @param bool Whether to apply or unapply the policy map. If true,
    *  policy map is applied on the given interface and direction. If false,
    *  policy map is removed from the given interface and direction.
    */
   virtual void policy_map_apply(policy_map_key_t const &, intf_id_t,
                                 acl_direction_t, bool apply) = 0;

 protected:
   policy_map_mgr() EOS_SDK_PRIVATE;
   friend class policy_map_handler;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(policy_map_mgr);
};

} // end namespace eos

// The inline header relies on definitions above
#include <eos/inline/policy_map.h>

#endif // EOS_POLICY_H
