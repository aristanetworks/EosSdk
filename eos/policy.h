// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_POLICY_H
#define EOS_POLICY_H

#include <eos/acl.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/iterator.h>

namespace eos {

typedef uint32_t policy_map_tag_t;

/// A policy map rule sequence number, an int in the range LOW to HIGH, inclusive.
enum policy_map_rule_sequence_t {
   POLICY_MAP_RULE_SEQUENCE_LOW = 1,
   POLICY_MAP_RULE_SEQUENCE_HIGH = 255,
};

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
 * The class map match type for an individual class map match rule.
 */
enum class_map_match_type_t {
   CLASS_MAP_MATCH_NULL,
   CLASS_MAP_MATCH_ACL,            //< Matches all the permit rules in the ACL
   CLASS_MAP_MATCH_ACL_RULE_IPV4,  //< Matches a single IPv4 ACL rule
   CLASS_MAP_MATCH_ACL_RULE_IPV6,  //< Matches a single IPv6 ACL rule
   CLASS_MAP_MATCH_ACL_RULE_ETH,   //< Matches a single Ethernet ACL rule
};

/**
 * A hardware feature a policy map can be used with.
 */
enum policy_feature_t {
   POLICY_FEATURE_NULL,
   POLICY_FEATURE_QOS,      //< Quality of service
   POLICY_FEATURE_PBR,      //< Policy based routing (PBR)
   POLICY_FEATURE_TAP_AGG,  //< Tap aggregation
};

/**
 * The actions a policy map rule may apply to classified packets.
 */
enum policy_action_type_t {
   POLICY_ACTION_NULL,
   POLICY_ACTION_SHAPING,
   POLICY_ACTION_NONE,            //< Perform no action
   POLICY_ACTION_NEXTHOP,         //< Forward to a nexthop
   POLICY_ACTION_NEXTHOP_GROUP,   //< Forward to a group of nexthops/interfaces
   POLICY_ACTION_SET_DSCP,        //< Set DSCP bits
   POLICY_ACTION_SET_AGG_GROUP,
   POLICY_ACTION_SET_ID_TAG,
};

/// The key type used by both class and policy maps.
class EOS_SDK_PUBLIC policy_map_key_t {
 public:
   policy_map_key_t();
   policy_map_key_t(std::string const &, policy_feature_t);

   std::string const & name() const;
   policy_feature_t feature() const;

 private:
   std::string name_;
   policy_feature_t feature_;
};

class EOS_SDK_PUBLIC policy_map_t {
 public:
};

/**
 * The base class map match or "rule entry", not for instantiation.
 * A match defines a single match clause in a class map.
 * The rule is independent of its sequence number in the map.
 */
class EOS_SDK_PUBLIC class_map_match_base_t {
 public:
   /**
    * The match type of this class map match rule.
    * Either an ACL or an IPv4, IPv6 or Ethernet ACL rule.
    */
   class_map_match_type_t match_type() const;

 private:
   class_map_match_base_t() EOS_SDK_PRIVATE;

   class_map_match_type_t match_type_;
};

/// A class map match rule matching a named ACL.
class EOS_SDK_PUBLIC class_map_match_acl_t : public class_map_match_base_t {
 public:
   class_map_match_acl_t();
   explicit class_map_match_acl_t(acl_key_t const & acl_key);

   /// The ACL name and type to use as a class map match rule.
   acl_key_t const & acl_key() const;
 private:
   acl_key_t acl_key_;
};

/// A class map match rule matching an individual ACL rule of IPv4 or IPv6 type.
class EOS_SDK_PUBLIC class_map_match_acl_rule_ip_t : public class_map_match_base_t {
 public:
   class_map_match_acl_rule_ip_t();
   explicit class_map_match_acl_rule_ip_t(acl_rule_ip_t const &);

   /// An IPv4 or IPv6 ACL rule (rule type and addresses must equal match_type)
   acl_rule_ip_t const & rule() const;
 private:
   acl_rule_ip_t rule_;
};

/// A class map match rule matching an individual Ethernet ACL rule.
class EOS_SDK_PUBLIC class_map_match_acl_rule_eth_t : public class_map_match_base_t {
 public:
   class_map_match_acl_rule_eth_t();
   explicit class_map_match_acl_rule_eth_t(acl_rule_eth_t const &);

   /// An Ethernet ACL rule to match
   acl_rule_eth_t const & rule() const;
 private:
   acl_rule_eth_t rule_;
};

/// The base action type is not for instantiation; it holds only the action type.
class EOS_SDK_PUBLIC policy_map_action_base_t {
 public:
   policy_action_type_t action_type() const;

 private:
   policy_map_action_base_t() EOS_SDK_PRIVATE;

   policy_action_type_t action_type_;
};

/**
 * A policy map action specifying a list of IP address nexthops.
 *
 * Nexthop addresses can be repeated in the list to set unequal
 * cost multi-path load balancing.
 */
class EOS_SDK_PUBLIC policy_map_action_nexthop_t : public policy_map_action_base_t {
 public:
   policy_map_action_nexthop_t();
   explicit policy_map_action_nexthop_t(std::list<ip_addr_t const &>);

   std::list<ip_addr_t> nexthop() const;

 private:
   std::list<ip_addr_t> nexthop_;
};

/// A policy map action to use a nexthop-group name for forwarding.
class EOS_SDK_PUBLIC policy_map_action_nexthop_group_t :
      public policy_map_action_base_t {
 public:
   policy_map_action_nexthop_group_t();
   /**
    * Constructs a policy map action to send to a nexthop group.
    *
    * If the nexthop group does not yet exist when calling
    * policy_map_rule_set() on the policy_map_mgr, that action will
    * complete successfully but FIB entries for the nextop group will
    * not be programmed until such time as the group is configured.
    */
   explicit policy_map_action_nexthop_group_t(std::string const &);

   /// Returns the name of the nexthop group
   std::string const & nexthop_group() const;

 private:
   std::string nexthop_group_;
};

/**
 * Policy map handler.
 *
 * A policy map handler reacts to hardware feature updates for a
 * single hardware feature chosen upon construction.
 */
class EOS_SDK_PUBLIC policy_map_handler {
 public:
   /// Constructs a policy map handler for the supplied policy hardware feature.
   explicit policy_map_handler(policy_feature_t);
   virtual ~policy_map_handler();

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
 private:
   policy_feature_t feature_;
};

class policy_map_iter_impl;

/// An iterator providing forwards only iteration over collections of policy maps
class EOS_SDK_PUBLIC policy_map_iter_t : public iter_base<policy_map_t,
                                                          policy_map_iter_impl> {
 private:
   friend class policy_map_iter_impl;
   explicit policy_map_iter_t(policy_map_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * Policy map manager.
 *
 * The manager allows the (implicit) creation of policy maps, as well
 * as rule manipulation, iteration, policy commit and policy
 * application functions.
 */
class EOS_SDK_PUBLIC policy_map_mgr {
 protected:
   policy_map_mgr() EOS_SDK_PRIVATE;

 public:
   /**
    * Sets a policy map match rule at a sequence number in a policy map.
    *
    * On the policy map identified by the key, at the numbered
    * sequence number, which must be no less than 1 and goes up to
    * POLICY_MAP_RULE_SEQUENCE_HIGH, install a rule matching the
    * policy map match rule, applying the set of actions.
    * policy_map_commit() must be called after _rule_set() and before
    * policy_map_apply() is called to apply the policy map configured
    * by these functions to be applied to traffic.
    */
   void policy_map_rule_set(policy_map_key_t const &,
                            policy_map_rule_sequence_t,
                            class_map_match_base_t const & match,
                            std::list<policy_map_action_base_t const & actions>);

   /**
    * Removes the numbered rule from the policy map identified by the key.
    *
    * To actually remove the rule from the policy map in the switch
    * forwarding hardware, you must call policy_map_commit().
    */
   void policy_map_rule_del(policy_map_key_t const &,
                            policy_map_rule_sequence_t);

   /// Deletes the policy map identified by the argument.
   void policy_map_del(policy_map_key_t const &);

   /**
    * Provides iteration type over the configured policy maps for a feature.
    */
   policy_map_iter_t policy_map_iter(policy_feature_t) const;

   /**
    * Commits all outstanding policy map changes.
    *
    * Upon completion, the handler for the appropriate hardware tables
    * updated will have its on_policy_map_sync_complete or
    * on_policy_map_sync_failed functions called.
    */
   void policy_map_commit();

   /// Applies or unapplies the policy map to an interface in a direction
   void policy_map_apply(policy_map_key_t const &, intf_id_t, acl_direction_t,
                         bool apply);

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(policy_map_mgr);
};

/**
 * Creates a policy map manager.
 *
 * A policy map manager is used to setup policy maps using ACL names,
 * ACL rules to build class map match rules. From there, policy maps
 * with sequenced rules matching a class map match to a set of actions
 * are set using this manager. Finally, configured policy maps are
 * committed and applied to interfaces.
 */
policy_map_mgr * get_policy_map_mgr() EOS_SDK_PUBLIC;

} // end namespace eos

#endif // EOS_POLICY_H
