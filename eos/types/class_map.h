// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_CLASS_MAP_H
#define EOS_TYPES_CLASS_MAP_H

#include <eos/acl.h>
#include <eos/policy_map.h>
#include <eos/utility.h>
#include <map>
#include <sstream>

namespace eos {
/**
 * A special class map name which means "match all MPLS traffic."
 *
 * Use as follows when defining a class_map_key_t:
 *
 * @code{.cpp}
 *    eos::class_map_key_t key(eos::CLASS_MAP_MPLS_ANY,
 * eos::POLICY_FEATURE_PBR);
 *    eos::class_map_t cm(key);
 * @endcode
 *
 * Only one such rule can be set on any one policy map.
 */

static std::string const CLASS_MAP_MPLS_ANY = "__mpls_permit_any__";

typedef policy_map_key_t class_map_key_t;

/**
 * A class map match rule uses an ACL to match classified traffic.
 * Values of this type are returned from the class_map_rule_iter, to program class
 * maps, either supply one of these or the acl_key_t directly to class_map_mgr's
 * class_map_rule_set().
 */
class EOS_SDK_PUBLIC class_map_rule_t {
 public:
   class_map_rule_t();
   explicit class_map_rule_t(acl_key_t const & acl_key);

   /**
    * Getter for 'acl_key': the ACL name and type to use as a class map match rule.
    */
   acl_key_t acl_key() const;

   bool operator==(class_map_rule_t const & other) const;
   bool operator!=(class_map_rule_t const & other) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * class_map_rule_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, 
                                   const class_map_rule_t& obj);

 private:
   acl_key_t acl_key_;
};

/**
 * A class map classifies traffic to apply policy features to.
 *
 * A class map can match IP or MPLS traffic. To match IP traffic, specify a class
 * map matching one or more IPv4 ACLs (for PBR).
 */
class EOS_SDK_PUBLIC class_map_t {
 public:
   class_map_t();
   explicit class_map_t(class_map_key_t const & key);

   /** Getter for 'key': the class map key. */
   class_map_key_t key() const;
   /** Setter for 'key'. */
   void key_is(class_map_key_t const & key);

   /** Getter for 'rules': the sequence of class map rules. */
   std::map<uint32_t, class_map_rule_t> const & rules() const;
   /** Setter for 'rules'. */
   void rules_is(std::map<uint32_t, class_map_rule_t> const & rules);
   /** inserts key/value pair to the map. */
   void rule_set(uint32_t key, class_map_rule_t const & value);
   /** deletes the key/value pair from the map. */
   void rule_del(uint32_t key);

   /**
    * Getter for 'persistent': the persistence state for this class map.
    *
    * When true, the class map will be stored in the running and startup
    * configuration.
    */
   bool persistent() const;
   /** Setter for 'persistent'. */
   void persistent_is(bool persistent);

   bool operator==(class_map_t const & other) const;
   bool operator!=(class_map_t const & other) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of class_map_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const class_map_t& obj);

 private:
   class_map_key_t key_;
   std::map<uint32_t, class_map_rule_t> rules_;
   bool persistent_;
};
}

#include <eos/inline/types/class_map.h>

#endif // EOS_TYPES_CLASS_MAP_H
