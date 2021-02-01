// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_ROUTE_MAP_H
#define EOS_TYPES_ROUTE_MAP_H

#include <eos/bgp.h>
#include <eos/hash_mix.h>
#include <eos/utility.h>
#include <map>
#include <sstream>

namespace eos {

enum bandwidth_unit_t {
   BIT,
   KILOBIT,
   MEGABIT,
   GIGABIT,
};
/** Appends a string representation of enum bandwidth_unit_t value to the ostream. */
std::ostream& operator<<(std::ostream& os, const bandwidth_unit_t & enum_val);

class EOS_SDK_PUBLIC link_bandwidth_t {
 public:
   link_bandwidth_t();

   float value() const;
   void value_is(float value);

   bandwidth_unit_t unit() const;
   void unit_is(bandwidth_unit_t unit);

   bool operator==(link_bandwidth_t const & other) const;
   bool operator!=(link_bandwidth_t const & other) const;
   bool operator<(link_bandwidth_t const & other) const;
   /** The hash function for type link_bandwidth_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * link_bandwidth_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const link_bandwidth_t& obj);

 private:
   float value_;
   bandwidth_unit_t unit_;
};

typedef std::string route_map_name_t;

typedef uint32_t route_map_sequence_number_t;

enum route_map_link_bandwidth_action_t {
   ROUTE_MAP_LINK_BANDWIDTH_ACTION_NONE,
   ROUTE_MAP_LINK_BANDWIDTH_ACTION_SET,
   ROUTE_MAP_LINK_BANDWIDTH_ACTION_DELETE,
};
/**
 * Appends a string representation of enum route_map_link_bandwidth_action_t value
 * to the ostream.
 */
std::ostream& operator<<(std::ostream& os,
                         const route_map_link_bandwidth_action_t & enum_val);

class EOS_SDK_PUBLIC route_map_link_bandwidth_t {
 public:
   route_map_link_bandwidth_t();

   route_map_link_bandwidth_action_t action() const;

   bgp_asn_t asn() const;

   link_bandwidth_t bandwidth() const;

   bool operator==(route_map_link_bandwidth_t const & other) const;
   bool operator!=(route_map_link_bandwidth_t const & other) const;
   bool operator<(route_map_link_bandwidth_t const & other) const;
   /** The hash function for type route_map_link_bandwidth_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * route_map_link_bandwidth_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const route_map_link_bandwidth_t& obj);

 private:
   route_map_link_bandwidth_action_t action_;
   bgp_asn_t asn_;
   link_bandwidth_t bandwidth_;
};

class EOS_SDK_PUBLIC route_map_entry_t {
 public:
   route_map_entry_t();
   explicit route_map_entry_t(route_map_sequence_number_t sequence_number);
   explicit route_map_entry_t(route_map_sequence_number_t sequence_number,
                              bool permit);

   route_map_sequence_number_t sequence_number() const;
   void sequence_number_is(route_map_sequence_number_t sequence_number);

   bool permit() const;
   void permit_is(bool permit);

   route_map_link_bandwidth_t link_bandwidth() const;
   void link_bandwidth_is(route_map_link_bandwidth_t const & link_bandwidth);

   bool operator==(route_map_entry_t const & other) const;
   bool operator!=(route_map_entry_t const & other) const;
   bool operator<(route_map_entry_t const & other) const;
   /** The hash function for type route_map_entry_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * route_map_entry_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const route_map_entry_t& obj);

 private:
   route_map_sequence_number_t sequence_number_;
   bool permit_;
   route_map_link_bandwidth_t link_bandwidth_;
};

class EOS_SDK_PUBLIC route_map_t {
 public:

   route_map_name_t name() const;
   void name_is(route_map_name_t const & name);

   std::map<route_map_sequence_number_t, route_map_entry_t> const & map_entry()
          const;
   void map_entry_is(

         std::map<route_map_sequence_number_t, route_map_entry_t> const & map_entry)
         ;
   /** Inserts key/value pair to the map. */
   void map_entry_set(route_map_sequence_number_t const & key,
                      route_map_entry_t const & value);
   /** Deletes the key/value pair from the map. */
   void map_entry_del(route_map_sequence_number_t const & key);

   bool operator==(route_map_t const & other) const;
   bool operator!=(route_map_t const & other) const;
   bool operator<(route_map_t const & other) const;
   /** The hash function for type route_map_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of route_map_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const route_map_t& obj);

 private:
   route_map_name_t name_;
   std::map<route_map_sequence_number_t, route_map_entry_t> map_entry_;
};
}

#include <eos/inline/types/route_map.h>

#endif // EOS_TYPES_ROUTE_MAP_H
