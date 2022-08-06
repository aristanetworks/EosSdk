// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_CLASS_MAP_H
#define EOS_TYPES_CLASS_MAP_H

#include <eos/acl.h>
#include <eos/hash_mix.h>
#include <eos/policy_map.h>
#include <eos/utility.h>
#include <map>
#include <memory>
#include <sstream>

namespace eos {
/**
 * A special class map name which means "match all MPLS traffic."
 *
 * Use as follows when defining a class_map_key_t:
 *
 * @code
 *    eos::class_map_key_t key(eos::CLASS_MAP_MPLS_ANY,
 * eos::POLICY_FEATURE_PBR);
 *    eos::class_map_t cm(key);
 * @endcode
 *
 * Only one such rule can be set on any one policy map.
 */

static std::string const CLASS_MAP_MPLS_ANY = "__mpls_permit_any__";

typedef policy_map_key_t class_map_key_t;

class class_map_rule_impl_t;
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
   class_map_rule_t(const class_map_rule_t& other);
   class_map_rule_t& operator=(
      class_map_rule_t const & other);


   /**
    * Getter for 'acl_key': the ACL name and type to use as a class map match rule.
    */
   acl_key_t acl_key() const;

   bool operator==(class_map_rule_t const & other) const;
   bool operator!=(class_map_rule_t const & other) const;
   /** The hash function for type class_map_rule_t. */
   uint32_t hash() const;
   /** The hash mix function for type class_map_rule_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * class_map_rule_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const class_map_rule_t& obj);

 private:
   std::shared_ptr<class_map_rule_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const class_map_rule_t& obj);

class class_map_impl_t;
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
   class_map_t(const class_map_t& other);
   class_map_t& operator=(
      class_map_t const & other);


   /** Getter for 'key': the class map key. */
   class_map_key_t key() const;
   /** Setter for 'key'. */
   void key_is(class_map_key_t const & key);

   /** Getter for 'rules': the sequence of class map rules. */
   std::map<uint32_t, class_map_rule_t> const & rules() const;
   /** Setter for 'rules'. */
   void rules_is(std::map<uint32_t, class_map_rule_t> const & rules);
   /** Inserts key/value pair to the map. */
   void rule_set(uint32_t key, class_map_rule_t const & value);
   /** Deletes the key/value pair from the map. */
   void rule_del(uint32_t key);

   bool operator==(class_map_t const & other) const;
   bool operator!=(class_map_t const & other) const;
   /** The hash function for type class_map_t. */
   uint32_t hash() const;
   /** The hash mix function for type class_map_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of class_map_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const class_map_t& obj);

 private:
   std::shared_ptr<class_map_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const class_map_t& obj);
}

#endif // EOS_TYPES_CLASS_MAP_H
