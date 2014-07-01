// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_POLICY_H
#define EOS_POLICY_H

#include <map>
#include <utility>
#include <unordered_set>

#include <eos/acl.h>
#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/intf.h>
#include <eos/ip.h>
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
 * @code{.cpp}
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
 * @code{.cpp}
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

namespace eos {

typedef uint32_t policy_map_tag_t;

/**
 * The default match condition for the policy map.
 *
 * At present, the only supported condition is that any rule in the
 * policy-map matching will trigger the action (POLICY_MAP_CONDITION_ANY).
 */
enum policy_match_condition_t {
   POLICY_MAP_CONDITION_NULL,
   POLICY_MAP_CONDITION_ANY,
};

/**
 * A hardware feature a policy map can be used with.
 */
enum policy_feature_t {
   POLICY_FEATURE_NULL,
   POLICY_FEATURE_PBR,      ///< Policy based routing
   POLICY_FEATURE_QOS,      ///< Quality of service
   POLICY_FEATURE_TAP_AGG,  ///< TAP Aggregation steering (not yet supported)
};

/**
 * The actions a policy map rule may apply to classified packets.
 */
enum policy_action_type_t {
   POLICY_ACTION_NULL,
   POLICY_ACTION_NONE,            ///< Perform no action
   // PBR actions
   POLICY_ACTION_DROP,            ///< Drop traffic for this policy
   POLICY_ACTION_NEXTHOP,         ///< Forward to one or more IP nexthops
   POLICY_ACTION_NEXTHOP_GROUP,   ///< Forward to named group of nexthops/interfaces
   // QoS actions
   POLICY_ACTION_DSCP,            ///< Set DSCP bits
   POLICY_ACTION_TRAFFIC_CLASS,   ///< Set traffic class
};

/** The key used to uniquely identify both class and policy maps. */
class EOS_SDK_PUBLIC policy_map_key_t {
 public:
   policy_map_key_t();
   policy_map_key_t(std::string const & name, policy_feature_t const & feature);

   std::string name() const;
   void name_is(std::string const & name);

   policy_feature_t feature() const;
   void feature_is(policy_feature_t const & feature);

   bool operator==(policy_map_key_t const & other) const;
   bool operator!=(policy_map_key_t const & other) const;
   bool operator<(policy_map_key_t const & other) const;

 private:
   std::string name_;
   policy_feature_t feature_;
};

typedef policy_map_key_t class_map_key_t;

/**
 * A single policy map action.
 * Each action defines a single type of action to be performed,presently
 * supporting: "set nexthop", "set nexthop group" and "drop".
 * It is illegal to set both nexthop and nexthop group or dropoperations in a
 * single policy map rule.
 */
class EOS_SDK_PUBLIC policy_map_action_t {
 public:
   policy_map_action_t();
   /**
    * Constructs a policy map action of a particular type.
    *
    * After construction, set attributes appropriate for the action type
    * using the mutators below; only the action-specific attributes
    * will be considered when the policy is applied. If the action is
    * POLICY_ACTION_DROP, no further attributes require being set.
    */
   explicit policy_map_action_t(policy_action_type_t action_type);
   virtual ~policy_map_action_t();

   policy_action_type_t action_type() const;
   void action_type_is(policy_action_type_t action_type);

   // PBR applicable actions:

   /**
    * Manage the nexthop group to be used when the action is
    * POLICY_ACTION_NEXTHOP_GROUP
    *
    * If the nexthop group does not yet exist when calling
    * policy_map_is() on the policy_map_mgr, that action will
    * complete successfully but FIB entries for the nextop group will
    * not be programmed until the group is configured.
    */
   std::string nexthop_group_name() const;
   void nexthop_group_name_is(std::string const & nexthop_group_name);

   /// Manage the set of nexthop IP addresses
   std::unordered_set<ip_addr_t> const & nexthops() const;
   void nexthops_is(std::unordered_set<ip_addr_t> const & nexthops);
   void nexthop_set(ip_addr_t const & value);
   void nexthop_del(ip_addr_t const & value);

   // QoS applicable actions:
   /**
    * Sets the DiffServ Code Point on matching IPv4/IPv6 packets.
    * This sets the 6-bit IPv4 DSCP or IPv6 traffic class field.
    *
    * @raises eos::invalid_argument_error If value outside range 0..63
    */
   uint8_t dscp() const;
   void dscp_is(uint8_t dscp);

   /**
    * Sets the internal EOS traffic class on matching packets.
    * Setting this 3-bit value overrides any interface CoS/DSCP trust mapping.
    *
    * @raises eos::invalid_argument_error If value outside range 0..7
    */
   uint8_t traffic_class() const;
   void traffic_class_is(uint8_t traffic_class);

   bool operator==(policy_map_action_t const & other) const;
   bool operator!=(policy_map_action_t const & other) const;
   bool operator<(policy_map_action_t const & other) const;

 private:
   policy_action_type_t action_type_;
   std::string nexthop_group_name_;
   std::unordered_set<ip_addr_t> nexthops_;
   uint8_t dscp_;
   uint8_t traffic_class_;
};


/**
 * A policy map rule, describing a traffic match and actions.
 *
 * A rule can match IP traffic via a class map, or can choose to match
 * all MPLS traffic. To use a class map, use the explicit constructor
 * or create a default policy map rule and set the class map with
 * class_map_key_is().
 *
 * Actions can be set at once or added or removed one at a time.
 */
class EOS_SDK_PUBLIC policy_map_rule_t {
 public:
   policy_map_rule_t();
   explicit policy_map_rule_t(class_map_key_t const & class_map_key);

   /// Returns the class map key (name is "__mpls_permit_any__" if matching MPLS)
   class_map_key_t class_map_key() const;
   /// Sets IP traffic match mode to match traffic for the class map.
   void class_map_key_is(class_map_key_t const & class_map_key);

   /// Manages the set of actions configured for this particular rule
   std::unordered_set<policy_map_action_t> const & actions() const;
   void actions_is(std::unordered_set<policy_map_action_t> const & value);
   void action_set(policy_map_action_t const & value);
   void action_del(policy_map_action_t const & value);
   void action_del(policy_action_type_t action_type);

   bool operator==(policy_map_rule_t const & other) const;
   bool operator!=(policy_map_rule_t const & other) const;
   bool operator<(policy_map_rule_t const & other) const;

 private:
   class_map_key_t class_map_key_;
   std::unordered_set<policy_map_action_t> actions_;
};


/**
 * A policy map instance.
 *
 * Once appropriately configured, policy maps are committed and
 * applied to interfaces using the policy_map_mgr.
 */
class EOS_SDK_PUBLIC policy_map_t {
 public:
   policy_map_t();
   explicit policy_map_t(policy_map_key_t const & key);

   policy_map_key_t key() const;
   void key_is(policy_map_key_t const & key);

   std::map<uint32_t, policy_map_rule_t> const & rules() const;
   void rules_is(std::map<uint32_t, policy_map_rule_t> const & rules);
   void rule_set(uint32_t seq, policy_map_rule_t const & value);
   void rule_del(uint32_t seq);

   bool operator==(policy_map_t const & other) const;
   bool operator!=(policy_map_t const & other) const;

   /// Sets the config persistence for this policy map (defaults to false).
   /// TODO: Currently not implemented
   void persistent_is(bool);
   /// The persistence state for this policy map
   bool persistent() const;

 private:
   policy_map_key_t key_;
   std::map<uint32_t, policy_map_rule_t> rules_;
   bool persistent_;
};

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
    * @param watch Receives notifications if and only if true.
    */
   void watch_policy_map(policy_map_key_t const & key, bool interest);

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

   /// Applies or unapplies the policy map to an interface in a direction
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
