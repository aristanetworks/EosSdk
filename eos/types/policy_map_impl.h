// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_POLICY_MAP_IMPL_H
#define EOS_TYPES_POLICY_MAP_IMPL_H

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

/** The key used to uniquely identify both class and policy maps. */
class EOS_SDK_PUBLIC policy_map_key_impl_t {
 public:
   policy_map_key_impl_t();
   policy_map_key_impl_t(std::string const & name, policy_feature_t feature);

   std::string name() const;
   void name_is(std::string const & name);

   policy_feature_t feature() const;
   void feature_is(policy_feature_t feature);

   bool operator==(policy_map_key_impl_t const & other) const;
   bool operator!=(policy_map_key_impl_t const & other) const;
   bool operator<(policy_map_key_impl_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os,
                                   const policy_map_key_impl_t& obj);

 private:
   std::string name_;
   policy_feature_t feature_;
};

/**
 * A single policy map action.
 * Each action defines a single type of action to be performed, presently
 * supporting: "set nexthop", "set nexthop group" and "drop".
 * It is illegal to set both nexthop and nexthop group or drop operations in a
 * single policy map rule.
 */
class EOS_SDK_PUBLIC policy_map_action_impl_t {
 public:
   policy_map_action_impl_t();
   /**
    * Constructs a policy map action of a particular type.
    *
    * After construction, set attributes appropriate for the action type using the
    * mutators below; only the action-specific attributes will be considered when
    * the policy is applied. If the action is POLICY_ACTION_DROP, no further
    * attributes require being set.
    */
   explicit policy_map_action_impl_t(policy_action_type_t action_type);
   virtual ~policy_map_action_impl_t();

   policy_action_type_t action_type() const;
   void action_type_is(policy_action_type_t action_type);

   /**
    * Getter for 'nexthop_group_name': the name of the nexthop group to be used
    * when the action is POLICY_ACTION_NEXTHOP_GROUP.
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

   bool operator==(policy_map_action_impl_t const & other) const;
   bool operator!=(policy_map_action_impl_t const & other) const;
   bool operator<(policy_map_action_impl_t const & other) const;
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
                                   const policy_map_action_impl_t& obj);

 private:
   policy_action_type_t action_type_;
   std::string nexthop_group_name_;
   std::unordered_set<ip_addr_t> nexthops_;
   std::string vrf_;
   uint8_t dscp_;
   uint8_t traffic_class_;
};

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
class EOS_SDK_PUBLIC policy_map_rule_impl_t {
 public:
   policy_map_rule_impl_t();
   explicit policy_map_rule_impl_t(class_map_key_t const & class_map_key);

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

   /** Getter for 'raw_rule': the raw match statement. */
   acl_rule_ip_t raw_rule() const;
   /** Setter for 'raw_rule'. */
   void raw_rule_is(acl_rule_ip_t raw_rule);

   /**
    * Getter for 'actions': the set of actions configured for this particular rule.
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
   bool operator==(policy_map_rule_impl_t const & other) const;
   bool operator!=(policy_map_rule_impl_t const & other) const;
   bool operator<(policy_map_rule_impl_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os,
                                   const policy_map_rule_impl_t& obj);

 private:
   class_map_key_t class_map_key_;
   policy_map_rule_type_t policy_map_rule_type_;
   acl_rule_ip_t raw_rule_;
   std::set<policy_map_action_t> actions_;
};

/**
 * A policy map instance.
 *
 * Once appropriately configured, policy maps are committed and applied to
 * interfaces using the policy_map_mgr.
 */
class EOS_SDK_PUBLIC policy_map_impl_t {
 public:
   policy_map_impl_t();
   explicit policy_map_impl_t(policy_map_key_t const & key);

   policy_map_key_t key() const;
   void key_is(policy_map_key_t const & key);

   std::map<uint32_t, policy_map_rule_t> const & rules() const;

   void rules_is(std::map<uint32_t, policy_map_rule_t> const & rules);
   void rule_set(uint32_t key, policy_map_rule_t const & value);
   void rule_del(uint32_t key);
   bool operator==(policy_map_impl_t const & other) const;
   bool operator!=(policy_map_impl_t const & other) const;
   bool operator<(policy_map_impl_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os, const policy_map_impl_t& obj);

 private:
   policy_map_key_t key_;
   std::map<uint32_t, policy_map_rule_t> rules_;
};


/** policy map hardware interface key. */
class EOS_SDK_PUBLIC policy_map_hw_status_key_impl_t {
 public:
   policy_map_hw_status_key_impl_t();
   policy_map_hw_status_key_impl_t(intf_id_t intf_id, acl_direction_t direction);

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

   bool operator==(policy_map_hw_status_key_impl_t const & other) const;
   bool operator!=(policy_map_hw_status_key_impl_t const & other) const;
   bool operator<(policy_map_hw_status_key_impl_t const & other) const;
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
                                   const policy_map_hw_status_key_impl_t& obj);

 private:
   intf_id_t intf_id_;
   acl_direction_t direction_;
};

/** policy map hardware statuses. */
class EOS_SDK_PUBLIC policy_map_hw_statuses_impl_t {
 public:
   policy_map_hw_statuses_impl_t();
   explicit policy_map_hw_statuses_impl_t(
         
         std::map<policy_map_hw_status_key_t, policy_map_status_t> const &
         intf_statuses);

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

   bool operator==(policy_map_hw_statuses_impl_t const & other) const;
   bool operator!=(policy_map_hw_statuses_impl_t const & other) const;
   bool operator<(policy_map_hw_statuses_impl_t const & other) const;
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
                                   const policy_map_hw_statuses_impl_t& obj);

 private:
   std::map<policy_map_hw_status_key_t, policy_map_status_t> intf_statuses_;
};
}

#endif // EOS_TYPES_POLICY_MAP_IMPL_H
