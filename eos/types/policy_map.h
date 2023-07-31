// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_POLICY_MAP_H
#define EOS_TYPES_POLICY_MAP_H

#include <eos/acl.h>
#include <eos/exception.h>
#include <eos/hash_mix.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <unordered_set>

namespace eos {


typedef uint32_t policy_map_tag_t;

/**
 * The default match condition for the policy map.
 *
 * At present, the only supported condition is that any rule in the policy-map
 * matching will trigger the action (POLICY_MAP_CONDITION_ANY).
 */
enum policy_match_condition_t {
   POLICY_MAP_CONDITION_NULL,
   POLICY_MAP_CONDITION_ANY,
};
/**
 * Appends a string representation of enum policy_match_condition_t value to the
 * ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const policy_match_condition_t & enum_val);

/** A hardware feature a policy map can be used with. */
enum policy_feature_t {
   POLICY_FEATURE_NULL,
   POLICY_FEATURE_PBR,
   POLICY_FEATURE_QOS,
   POLICY_FEATURE_TAP_AGG,
   POLICY_FEATURE_TRAFFIC_POLICY,
};
/** Appends a string representation of enum policy_feature_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const policy_feature_t & enum_val);

/** The actions a PBR/QOS policy rule may apply to classified packets. */
enum policy_action_type_t {
   POLICY_ACTION_NULL,
   /** Perform no action. */
   POLICY_ACTION_NONE,
   /** Drop traffic for this policy. */
   POLICY_ACTION_DROP,
   /** Forward to one or more IP nexthops. */
   POLICY_ACTION_NEXTHOP,
   /** Forward to named group of nexthops/interfaces. */
   POLICY_ACTION_NEXTHOP_GROUP,
   /** Set DSCP bits. */
   POLICY_ACTION_DSCP,
   /** Set traffic class. */
   POLICY_ACTION_TRAFFIC_CLASS,
};
/**
 * Appends a string representation of enum policy_action_type_t value to the
 * ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const policy_action_type_t & enum_val);

/** The actions a traffic-policy rule may apply to classified packets. */
enum traffic_policy_action_type_t {
   /** Drop traffic for this policy. */
   TRAFFIC_POLICY_ACTION_DROP,
   /** Perform police action to limit traffic flow. */
   TRAFFIC_POLICY_ACTION_POLICE,
   /** Perform count action to count packets. */
   TRAFFIC_POLICY_ACTION_COUNT,
   /** Perform log action for logging. */
   TRAFFIC_POLICY_ACTION_LOG,
   /** Perform goto action for matching packet. */
   TRAFFIC_POLICY_ACTION_GOTO,
   /** Set DSCP bits. */
   TRAFFIC_POLICY_ACTION_DSCP,
   /** Set traffic class. */
   TRAFFIC_POLICY_ACTION_TRAFFIC_CLASS,
   /** Set vrf action. */
   TRAFFIC_POLICY_ACTION_SET_VRF,
   /** Set vrf secondary action. */
   TRAFFIC_POLICY_ACTION_SET_VRF_SECONDARY,
   /** Use vrf secondary action. */
   TRAFFIC_POLICY_ACTION_USE_VRF_SECONDARY,
   /** Mirror matching traffic to destinations. */
   TRAFFIC_POLICY_ACTION_MIRROR,
   /** Sample traffic and redirect to destinations. */
   TRAFFIC_POLICY_ACTION_SFLOW,
   /** Forward to one or more IP nexthops. */
   TRAFFIC_POLICY_ACTION_NEXTHOP,
   /** Forward to named group of nexthops/interfaces. */
   TRAFFIC_POLICY_ACTION_NEXTHOP_GROUP,
};
/**
 * Appends a string representation of enum traffic_policy_action_type_t value to
 * the ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(
         std::ostream& os, const traffic_policy_action_type_t & enum_val);

/** The direction in which a traffic-policy is applied. */
enum traffic_policy_direction_t {
   TRAFFIC_POLICY_DIRECTION_NULL,
   /** Ingress traffic-policy. */
   TRAFFIC_POLICY_DIRECTION_INPUT,
};
/**
 * Appends a string representation of enum traffic_policy_direction_t value to the
 * ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(
         std::ostream& os, const traffic_policy_direction_t & enum_val);

/** The policy map rule type. Valid types are IPV4 IPV6 and CLASSMAP. */
enum policy_map_rule_type_t {
   POLICY_RULE_TYPE_CLASSMAP,
   POLICY_RULE_TYPE_IPV4,
   POLICY_RULE_TYPE_IPV6,
};
/**
 * Appends a string representation of enum policy_map_rule_type_t value to the
 * ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const policy_map_rule_type_t & enum_val);

class policy_map_key_impl_t;
/** The key used to uniquely identify both class and policy maps. */
class EOS_SDK_PUBLIC policy_map_key_t {
 public:
   policy_map_key_t();
   policy_map_key_t(std::string const & name, policy_feature_t feature);
   policy_map_key_t(const policy_map_key_t& other);
   policy_map_key_t& operator=(
      policy_map_key_t const & other);


   std::string name() const;
   void name_is(std::string const & name);

   policy_feature_t feature() const;
   void feature_is(policy_feature_t feature);

   bool operator==(policy_map_key_t const & other) const;
   bool operator!=(policy_map_key_t const & other) const;
   bool operator<(policy_map_key_t const & other) const;
   /** The hash function for type policy_map_key_t. */
   uint32_t hash() const;
   /** The hash mix function for type policy_map_key_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * policy_map_key_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const policy_map_key_t& obj);

 private:
   std::shared_ptr<policy_map_key_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const policy_map_key_t& obj);

typedef policy_map_key_t class_map_key_t;

/** The rate unit type of police action. */
enum police_rate_unit_t {
   BPS,
   KBPS,
   MBPS,
   GBPS,
};
/**
 * Appends a string representation of enum police_rate_unit_t value to the ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const police_rate_unit_t & enum_val);

/** The burst unit type of police action. */
enum police_burst_unit_t {
   BYTES,
   KBYTES,
   MBYTES,
};
/**
 * Appends a string representation of enum police_burst_unit_t value to the
 * ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const police_burst_unit_t & enum_val);

class policy_map_action_impl_t;
/**
 * A single PBR/QOS action.
 * Each action defines a single type of action to be performed, presently
 * supporting: "set nexthop", "set nexthop group" and "drop".
 * It is illegal to set both nexthop and nexthop group or drop operations in a
 * single policy map rule.
 */
class EOS_SDK_PUBLIC policy_map_action_t {
 public:
   policy_map_action_t();
   /**
    * Constructs a PBR/QOS action of a particular type.
    *
    * After construction, set attributes appropriate for the action type using the
    * mutators below; only the action-specific attributes will be considered when
    * the policy is applied. If the action is POLICY_ACTION_DROP, no further
    * attributes require being set.
    */
   explicit policy_map_action_t(policy_action_type_t action_type);
   policy_map_action_t(const policy_map_action_t& other);
   policy_map_action_t& operator=(
      policy_map_action_t const & other);

   virtual ~policy_map_action_t();

   policy_action_type_t action_type() const;
   void action_type_is(policy_action_type_t action_type);

   /**
    * Getter for 'nexthop_group_name': the name of the nexthop group to be used
    * when the action is POLICY_ACTION_NEXTHOP_GROUP for PBR.
    * If the nexthop group does not yet exist when calling policy_map_is() on the
    * policy_map_mgr, that action will complete successfully but FIB entries for
    * the nextop group will not be programmed until the group is configured.
    */
   std::string nexthop_group_name() const;
   /** Setter for 'nexthop_group_name'. */
   void nexthop_group_name_is(std::string const & nexthop_group_name);

   std::unordered_set<ip_addr_t> const & nexthops() const;
   void nexthops_is(std::unordered_set<ip_addr_t> const & nexthops);
   /** Inserts one nexthop of 'value' to the set. */
   void nexthop_set(ip_addr_t const & value);
   /** Deletes one nexthop of 'value' from the set. */
   void nexthop_del(ip_addr_t const & value);

   /** Getter for 'vrf': the name of the VRF for nexthop action. */
   std::string vrf() const;
   /** Setter for 'vrf'. */
   void vrf_is(std::string const & vrf);

   /**
    * Getter for 'dscp': the DiffServ Code Point on matching IPv4/IPv6 packets.
    * This sets the 6-bit IPv4 DSCP or IPv6 traffic class field.
    *
    * @throw eos::invalid_argument_error if value outside range 0..63.
    */
   uint8_t dscp() const;
   /** Setter for 'dscp'. */
   void dscp_is(uint8_t dscp);

   /**
    * Getter for 'traffic_class': the internal EOS traffic class on matching
    * packets.
    * Setting this 3-bit value overrides any interface CoS/DSCP trust mapping.
    *
    * @throw eos::invalid_argument_error if value outside range 0..7.
    */
   uint8_t traffic_class() const;
   /** Setter for 'traffic_class'. */
   void traffic_class_is(uint8_t traffic_class);

   bool operator==(policy_map_action_t const & other) const;
   bool operator!=(policy_map_action_t const & other) const;
   bool operator<(policy_map_action_t const & other) const;
   /** The hash function for type policy_map_action_t. */
   uint32_t hash() const;
   /** The hash mix function for type policy_map_action_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * policy_map_action_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const policy_map_action_t& obj);

 private:
   std::shared_ptr<policy_map_action_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const policy_map_action_t& obj);

class traffic_policy_action_impl_t;
/**
 * A single traffic-policy action.
 * Each action defines a single type of action to be performed, presently
 * supporting: "set nexthop", "set nexthop group" and "drop".
 * It is illegal to set both nexthop and nexthop group or drop operations in a
 * single policy map rule.
 */
class EOS_SDK_PUBLIC traffic_policy_action_t {
 public:
   traffic_policy_action_t();
   /**
    * Constructs a traffic-policy action of a particular type.
    *
    * After construction, set attributes appropriate for the action type using the
    * mutators below; only the action-specific attributes will be considered when
    * the policy is applied. If the action is POLICY_ACTION_DROP, no further
    * attributes require being set.
    */
   explicit traffic_policy_action_t(traffic_policy_action_type_t action_type);
   traffic_policy_action_t(const traffic_policy_action_t& other);
   traffic_policy_action_t& operator=(
      traffic_policy_action_t const & other);

   virtual ~traffic_policy_action_t();

   traffic_policy_action_type_t action_type() const;
   void action_type_is(traffic_policy_action_type_t action_type);

   /** Getter for 'goto_class_name': the name of class for goto action. */
   std::string goto_class_name() const;
   /** Setter for 'goto_class_name'. */
   void goto_class_name_is(std::string const & goto_class_name);

   /** Getter for 'goto_next': the flag indicating if it is goto next action. */
   bool goto_next() const;
   /** Setter for 'goto_next'. */
   void goto_next_is(bool const & goto_next);

   /**
    * Getter for 'dscp': the DiffServ Code Point on matching IPv4/IPv6 packets.
    * This sets the 6-bit IPv4 DSCP or IPv6 traffic class field.
    *
    * @throw eos::invalid_argument_error if value outside range 0..63.
    */
   uint8_t dscp() const;
   /** Setter for 'dscp'. */
   void dscp_is(uint8_t dscp);

   /**
    * Getter for 'traffic_class': the internal EOS traffic class on matching
    * packets.
    * Setting this 3-bit value overrides any interface CoS/DSCP trust mapping.
    *
    * @throw eos::invalid_argument_error if value outside range 0..7.
    */
   uint8_t traffic_class() const;
   /** Setter for 'traffic_class'. */
   void traffic_class_is(uint8_t traffic_class);

   /** Getter for 'vrf': the name of the VRF for nexthop action. */
   std::string vrf() const;
   /** Setter for 'vrf'. */
   void vrf_is(std::string const & vrf);

   /** Getter for 'mirror_session': the name of mirror session for mirror action. */
   std::string mirror_session() const;
   /** Setter for 'mirror_session'. */
   void mirror_session_is(std::string const & mirror_session);

   /** Getter for 'police_rate': the police rate value for police action. */
   uint64_t police_rate() const;
   /** Setter for 'police_rate'. */
   void police_rate_is(uint64_t const & police_rate);

   /**
    * Getter for 'police_burst_size': the police burst size value for police
    * action.
    */
   uint64_t police_burst_size() const;
   /** Setter for 'police_burst_size'. */
   void police_burst_size_is(uint64_t const & police_burst_size);

   /** Getter for 'police_rate_unit': the police rate unit for police action. */
   police_rate_unit_t police_rate_unit() const;
   /** Setter for 'police_rate_unit'. */
   void police_rate_unit_is(police_rate_unit_t const & police_rate_unit);

   /** Getter for 'police_burst_unit': the police burst unit for police action. */
   police_burst_unit_t police_burst_unit() const;
   /** Setter for 'police_burst_unit'. */
   void police_burst_unit_is(police_burst_unit_t const & police_burst_unit);

   /**
    * Getter for 'nexthop_groups': the set of nexthop group names for traffic-
    * policy nexthop group action.
    */
   std::unordered_set<std::string> const & nexthop_groups() const;
   /** Setter for 'nexthop_groups'. */
   void nexthop_groups_is(std::unordered_set<std::string> const & nexthop_groups);
   /** Inserts one nexthop_group of 'value' to the set. */
   void nexthop_group_set(std::string const & value);
   /** Deletes one nexthop_group of 'value' from the set. */
   void nexthop_group_del(std::string const & value);

   std::unordered_set<ip_addr_t> const & nexthops() const;
   void nexthops_is(std::unordered_set<ip_addr_t> const & nexthops);
   /** Inserts one nexthop of 'value' to the set. */
   void nexthop_set(ip_addr_t const & value);
   /** Deletes one nexthop of 'value' from the set. */
   void nexthop_del(ip_addr_t const & value);

   bool operator==(traffic_policy_action_t const & other) const;
   bool operator!=(traffic_policy_action_t const & other) const;
   bool operator<(traffic_policy_action_t const & other) const;
   /** The hash function for type traffic_policy_action_t. */
   uint32_t hash() const;
   /** The hash mix function for type traffic_policy_action_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * traffic_policy_action_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const traffic_policy_action_t& obj);

 private:
   std::shared_ptr<traffic_policy_action_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const traffic_policy_action_t& obj);

class policy_map_rule_impl_t;
/**
 * A policy map rule, describing a traffic match and actions.
 *
 * A rule works by creating a filter to match only certain types of IP traffic. Any
 * traffic that passes this filter then has the corresponding `policy_map_action_t`
 * actions applied. For example, a rule can specify that any traffic on Vlan42
 * should have its traffic class set to 4 and should be forwarded out of
 * nexthop_group "foo".
 *
 * The match portion of a rule can take one of two forms: class maps or raw match
 * rules. Class maps let you combine various ACLs to decide whether to match or
 * ignore traffic. These objects are managed by the `class_map_mgr` in
 * `eos/class_map.h`. Alternatively, you can use a shorthand and specify just a
 * single `acl_rule_ip_t`, which will match traffic that passes that rule.
 * Actions can be set at once or added or removed one at a time.
 */
class EOS_SDK_PUBLIC policy_map_rule_t {
 public:
   policy_map_rule_t();
   explicit policy_map_rule_t(class_map_key_t const & class_map_key);
   policy_map_rule_t(const policy_map_rule_t& other);
   policy_map_rule_t& operator=(
      policy_map_rule_t const & other);


   /**
    * Getter for 'class_map_key': the class map key (name is CLASS_MAP_MPLS_ANY if
    * matching MPLS).
    */
   class_map_key_t class_map_key() const;
   /** Setter for 'class_map_key'. */
   void class_map_key_is(class_map_key_t const & class_map_key);

   /**
    * Getter for 'policy_map_rule_type': the rule type. Set the rule type to
    * POLICY_RULE_TYPE_CLASSMAP if the rule matches a class. If the rule has the
    * raw match statement set, the rule type should be set to POLICY_RULE_TYPE_IPV4
    * or POLICY_RULE_TYPE_IPV6.
    */
   policy_map_rule_type_t policy_map_rule_type() const;
   /** Setter for 'policy_map_rule_type'. */
   void policy_map_rule_type_is(policy_map_rule_type_t policy_map_rule_type);

   /** Getter for 'raw_rule': the raw match statement of PBR. */
   acl_rule_ip_t raw_rule() const;
   /** Setter for 'raw_rule'. */
   void raw_rule_is(acl_rule_ip_t raw_rule);

   /**
    * Getter for 'actions': the set of actions configured for this particular rule
    * of a PBR/QOS policy.
    */
   std::set<policy_map_action_t> const & actions() const;
   /** Setter for 'actions'. */
   void actions_is(std::set<policy_map_action_t> const & actions);
   /** Inserts one action of 'value' to the set. */
   void action_set(policy_map_action_t const & value);
   /** Deletes one action of 'value' from the set. */
   void action_del(policy_map_action_t const & value);

   void action_del(policy_action_type_t action_type);
   void raw_rule_is(acl_rule_ip_t acl_rule, policy_map_rule_type_t rule_type);
   bool operator==(policy_map_rule_t const & other) const;
   bool operator!=(policy_map_rule_t const & other) const;
   bool operator<(policy_map_rule_t const & other) const;
   /** The hash function for type policy_map_rule_t. */
   uint32_t hash() const;
   /** The hash mix function for type policy_map_rule_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * policy_map_rule_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const policy_map_rule_t& obj);

 private:
   std::shared_ptr<policy_map_rule_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const policy_map_rule_t& obj);

class policy_map_impl_t;
/**
 * A policy map instance.
 *
 * Once appropriately configured, policy maps are committed and applied to
 * interfaces using the policy_map_mgr.
 */
class EOS_SDK_PUBLIC policy_map_t {
 public:
   policy_map_t();
   explicit policy_map_t(policy_map_key_t const & key);
   policy_map_t(const policy_map_t& other);
   policy_map_t& operator=(
      policy_map_t const & other);


   policy_map_key_t key() const;
   void key_is(policy_map_key_t const & key);

   std::map<uint32_t, policy_map_rule_t> const & rules() const;

   void rules_is(std::map<uint32_t, policy_map_rule_t> const & rules);
   void rule_set(uint32_t key, policy_map_rule_t const & value);
   void rule_del(uint32_t key);
   bool operator==(policy_map_t const & other) const;
   bool operator!=(policy_map_t const & other) const;
   bool operator<(policy_map_t const & other) const;
   /** The hash function for type policy_map_t. */
   uint32_t hash() const;
   /** The hash mix function for type policy_map_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of policy_map_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const policy_map_t& obj);

 private:
   std::shared_ptr<policy_map_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const policy_map_t& obj);

class traffic_policy_rule_impl_t;
/**
 * A traffic policy rule, describing traffic match and actions.
 *
 * A rule works by creating a filter to match only certain types of traffic. Any
 * traffic that passes this filter then has the corresponding
 * `traffic_policy_action_t` actions applied. For example, a rule can specify that
 * any traffic on protocol tcp should have its traffic class set to 4.
 *
 * Actions can be set at once or added or removed one at a time.
 */
class EOS_SDK_PUBLIC traffic_policy_rule_t {
 public:
   traffic_policy_rule_t();
   traffic_policy_rule_t(std::string match_rule_name,
                         traffic_policy_rule_type_t traffic_policy_rule_type);
   traffic_policy_rule_t(const traffic_policy_rule_t& other);
   traffic_policy_rule_t& operator=(
      traffic_policy_rule_t const & other);


   std::string match_rule_name() const;

   /**
    * Getter for 'traffic_policy_rule_type': the rule type of traffic-policy. Set
    * the rule type to TRAFFIC_POLICY_RULE_TYPE_IPV4 or
    * TRAFFIC_POLICY_RULE_TYPE_IPV6.
    */
   traffic_policy_rule_type_t traffic_policy_rule_type() const;

   /** Getter for 'raw_rule': the match rule of a traffic policy. */
   tp_rule_filter_t raw_rule() const;

   /**
    * Getter for 'actions': the set of actions configured for this particular rule
    * of a traffic policy.
    */
   std::set<traffic_policy_action_t> const & actions() const;
   /** Setter for 'actions'. */
   void actions_is(std::set<traffic_policy_action_t> const & actions);
   /** Inserts one action of 'value' to the set. */
   void action_set(traffic_policy_action_t const & value);
   /** Deletes one action of 'value' from the set. */
   void action_del(traffic_policy_action_t const & value);

   void raw_rule_is(tp_rule_filter_t const & raw_rule);
   void action_del(traffic_policy_action_type_t action_type);
   bool operator==(traffic_policy_rule_t const & other) const;
   bool operator!=(traffic_policy_rule_t const & other) const;
   bool operator<(traffic_policy_rule_t const & other) const;
   /** The hash function for type traffic_policy_rule_t. */
   uint32_t hash() const;
   /** The hash mix function for type traffic_policy_rule_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * traffic_policy_rule_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const traffic_policy_rule_t& obj);

 private:
   std::shared_ptr<traffic_policy_rule_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const traffic_policy_rule_t& obj);

class traffic_policy_impl_t;
/**
 * A traffic policy instance.
 *
 * Once appropriately configured, traffic policies are committed and applied to
 * interfaces using the policy_map_mgr.
 */
class EOS_SDK_PUBLIC traffic_policy_t {
 public:
   explicit traffic_policy_t(std::string const & key);
   traffic_policy_t(const traffic_policy_t& other);
   traffic_policy_t& operator=(
      traffic_policy_t const & other);


   std::string key() const;

   std::map<uint32_t, traffic_policy_rule_t> const & rules() const;

   void rules_is(std::map<uint32_t, traffic_policy_rule_t> const & rules);
   void rule_set(uint32_t key, traffic_policy_rule_t const & value);
   void rule_del(uint32_t key);
   bool operator==(traffic_policy_t const & other) const;
   bool operator!=(traffic_policy_t const & other) const;
   bool operator<(traffic_policy_t const & other) const;
   /** The hash function for type traffic_policy_t. */
   uint32_t hash() const;
   /** The hash mix function for type traffic_policy_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * traffic_policy_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const traffic_policy_t& obj);

 private:
   std::shared_ptr<traffic_policy_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const traffic_policy_t& obj);

/** The policy feature requested is unavailable in this SDK release. */
class EOS_SDK_PUBLIC unsupported_policy_feature_error : public unsupported_error {
 public:
   explicit unsupported_policy_feature_error(policy_feature_t policy_feature)
          noexcept;
   virtual ~unsupported_policy_feature_error() noexcept;

   policy_feature_t policy_feature() const noexcept;

   virtual void raise() const;
   /** The hash function for type unsupported_policy_feature_error. */
   uint32_t hash() const;
   /** The hash mix function for type unsupported_policy_feature_error. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * unsupported_policy_feature_error to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const unsupported_policy_feature_error& obj);

 private:
   policy_feature_t policy_feature_;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os,
                         const unsupported_policy_feature_error& obj);

/** The policy map hardware status type. */
enum policy_map_status_t {
   POLICY_STATUS_NOT_FOUND,
   POLICY_STATUS_IN_PROGRESS,
   POLICY_STATUS_FAILED,
   POLICY_STATUS_SUCCESS,
};
/**
 * Appends a string representation of enum policy_map_status_t value to the
 * ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const policy_map_status_t & enum_val);

class policy_map_hw_status_key_impl_t;
/** policy map hardware interface key. */
class EOS_SDK_PUBLIC policy_map_hw_status_key_t {
 public:
   policy_map_hw_status_key_t();
   policy_map_hw_status_key_t(intf_id_t intf_id, acl_direction_t direction);
   policy_map_hw_status_key_t(const policy_map_hw_status_key_t& other);
   policy_map_hw_status_key_t& operator=(
      policy_map_hw_status_key_t const & other);


   /**
    * Getter for 'intf_id': Interface ID at with a policy map is applied.
    * If the feature type is POLICY_FEATURE_QOS,
    *  intf_id will be the default interface ID.
    */
   intf_id_t intf_id() const;
   /** Setter for 'intf_id'. */
   void intf_id_is(intf_id_t intf_id);

   /** Getter for 'direction': Direction in which a policy map is applied. */
   acl_direction_t direction() const;
   /** Setter for 'direction'. */
   void direction_is(acl_direction_t direction);

   bool operator==(policy_map_hw_status_key_t const & other) const;
   bool operator!=(policy_map_hw_status_key_t const & other) const;
   bool operator<(policy_map_hw_status_key_t const & other) const;
   /** The hash function for type policy_map_hw_status_key_t. */
   uint32_t hash() const;
   /** The hash mix function for type policy_map_hw_status_key_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * policy_map_hw_status_key_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const policy_map_hw_status_key_t& obj);

 private:
   std::shared_ptr<policy_map_hw_status_key_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const policy_map_hw_status_key_t& obj);

class policy_map_hw_statuses_impl_t;
/** policy map hardware statuses. */
class EOS_SDK_PUBLIC policy_map_hw_statuses_t {
 public:
   policy_map_hw_statuses_t();
   explicit policy_map_hw_statuses_t(
         
         std::map<policy_map_hw_status_key_t, policy_map_status_t> const &
         intf_statuses);
   policy_map_hw_statuses_t(const policy_map_hw_statuses_t& other);
   policy_map_hw_statuses_t& operator=(
      policy_map_hw_statuses_t const & other);


   /** Getter for 'intf_statuses': A map of interface key and policy map status. */
   std::map<policy_map_hw_status_key_t, policy_map_status_t> const & intf_statuses()
          const;
   /** Setter for 'intf_statuses'. */
   void intf_statuses_is(
         
         std::map<policy_map_hw_status_key_t, policy_map_status_t> const &
         intf_statuses);
   /** Inserts key/value pair to the map. */
   void intf_statuse_set(policy_map_hw_status_key_t const & key,
                         policy_map_status_t const & value);
   /** Deletes the key/value pair from the map. */
   void intf_statuse_del(policy_map_hw_status_key_t const & key);

   bool operator==(policy_map_hw_statuses_t const & other) const;
   bool operator!=(policy_map_hw_statuses_t const & other) const;
   bool operator<(policy_map_hw_statuses_t const & other) const;
   /** The hash function for type policy_map_hw_statuses_t. */
   uint32_t hash() const;
   /** The hash mix function for type policy_map_hw_statuses_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * policy_map_hw_statuses_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const policy_map_hw_statuses_t& obj);

 private:
   std::shared_ptr<policy_map_hw_statuses_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const policy_map_hw_statuses_t& obj);
}

#endif // EOS_TYPES_POLICY_MAP_H
