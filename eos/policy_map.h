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
 * Policy map manipulation.
 *
 * This module permits the manipulation of policy maps used in the
 * creation of service policies that can be applied to one or more
 * types of hardware features, beginning with Policy Based Routing
 * (PBR).
 *
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
   POLICY_FEATURE_PBR,      ///< Policy based routing (PBR)
   POLICY_FEATURE_QOS,      ///< Quality of service (not yet supported)
   POLICY_FEATURE_TAP_AGG,  ///< TAP Aggregation steering (not yet supported)
};

/**
 * The actions a policy map rule may apply to classified packets.
 */
enum policy_action_type_t {
   POLICY_ACTION_NULL,
   POLICY_ACTION_NONE,            ///< Perform no action
   POLICY_ACTION_DROP,            ///< Drop traffic for this policy
   POLICY_ACTION_NEXTHOP,         ///< Forward to one or more IP nexthops
   POLICY_ACTION_NEXTHOP_GROUP,   ///< Forward to named group of nexthops/interfaces
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
   std::unordered_set<ip_addr_t> & nexthops();
   std::unordered_set<ip_addr_t> const & nexthops() const;
   void nexthops_is(std::unordered_set<ip_addr_t> const & nexthops);
   void nexthop_set(ip_addr_t const & value);
   void nexthop_del(ip_addr_t const & value);

   bool operator==(policy_map_action_t const & other) const;
   bool operator!=(policy_map_action_t const & other) const;
   bool operator<(policy_map_action_t const & other) const;

 private:
   policy_action_type_t action_type_;
   std::string nexthop_group_name_;
   std::unordered_set<ip_addr_t> nexthops_;
};



/** An individual policy map rule, describing a class map match and actions */
class EOS_SDK_PUBLIC policy_map_rule_t {
 public:
   policy_map_rule_t();
   explicit policy_map_rule_t(class_map_key_t const & class_map_key);

   class_map_key_t class_map_key() const;
   void class_map_key_is(class_map_key_t const & class_map_key);

   /// Manage the set of actions configured for this particular rule
   std::unordered_set<policy_map_action_t> & actions();
   std::unordered_set<policy_map_action_t> const & actions() const;
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


/** A policy map instance */
class EOS_SDK_PUBLIC policy_map_t {
 public:
   policy_map_t();
   explicit policy_map_t(policy_map_key_t const & key);

   policy_map_key_t key() const;
   void key_is(policy_map_key_t const & key);

   std::map<uint32_t, policy_map_rule_t> & rules();
   std::map<uint32_t, policy_map_rule_t> const & rules() const;
   void rules_is(std::map<uint32_t, policy_map_rule_t> const & rules);
   void rule_set(uint32_t seq, policy_map_rule_t const & value);
   void rule_del(uint32_t seq);

   bool operator==(policy_map_t const & other) const;
   bool operator!=(policy_map_t const & other) const;

 private:
   policy_map_key_t key_;
   std::map<uint32_t, policy_map_rule_t> rules_;
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
