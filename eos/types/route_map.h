// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
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
   LINK_BANDWIDTH_UNIT_BIT,
   LINK_BANDWIDTH_UNIT_KILOBIT,
   LINK_BANDWIDTH_UNIT_MEGABIT,
   LINK_BANDWIDTH_UNIT_GIGABIT,
};
/** Appends a string representation of enum bandwidth_unit_t value to the ostream. */
std::ostream& operator<<(std::ostream& os, const bandwidth_unit_t & enum_val);

/** Extended community link bandwidth value. */
class EOS_SDK_PUBLIC link_bandwidth_t {
 public:
   link_bandwidth_t(float value, bandwidth_unit_t unit);
   explicit link_bandwidth_t(float value);
   link_bandwidth_t();

   /** Getter for 'value': The link bandwidth value. */
   float value() const;
   /** Setter for 'value'. */
   void value_is(float value);

   /** Getter for 'unit': The link bandwidth bitrate unit. */
   bandwidth_unit_t unit() const;
   /** Setter for 'unit'. */
   void unit_is(bandwidth_unit_t unit);

   bool operator==(link_bandwidth_t const & other) const;
   bool operator!=(link_bandwidth_t const & other) const;
   bool operator<(link_bandwidth_t const & other) const;
   /** The hash function for type link_bandwidth_t. */
   uint32_t hash() const;
   /** The hash mix function for type link_bandwidth_t. */
   void mix_me(hash_mix & h) const;
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

/** Route map extended community link bandwidth operation type. */
enum route_map_operation_type_t {
   OPERATION_TYPE_NONE,
   OPERATION_TYPE_SET,
   OPERATION_TYPE_DELETE,
};
/**
 * Appends a string representation of enum route_map_operation_type_t value to the
 * ostream.
 */
std::ostream& operator<<(std::ostream& os,
                         const route_map_operation_type_t & enum_val);

/** Route map link bandwidth operation attribute information. */
class EOS_SDK_PUBLIC route_map_link_bandwidth_t {
 public:
   /** Create route map link bandwidth. */
   route_map_link_bandwidth_t();

   /** Getter for 'operation': Operation type. */
   route_map_operation_type_t operation() const;

   /** Getter for 'asn': Peer AS number. */
   bgp_asn_t asn() const;

   /** Getter for 'bandwidth': Link bandwidth value. */
   link_bandwidth_t bandwidth() const;

   void route_map_operation_type_set_is(link_bandwidth_t bandwidth);
   void route_map_operation_type_delete_is(link_bandwidth_t bandwidth,
                                           bgp_asn_t asn);
   bool operator==(route_map_link_bandwidth_t const & other) const;
   bool operator!=(route_map_link_bandwidth_t const & other) const;
   bool operator<(route_map_link_bandwidth_t const & other) const;
   /** The hash function for type route_map_link_bandwidth_t. */
   uint32_t hash() const;
   /** The hash mix function for type route_map_link_bandwidth_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * route_map_link_bandwidth_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const route_map_link_bandwidth_t& obj);

 private:
   route_map_operation_type_t operation_;
   bgp_asn_t asn_;
   link_bandwidth_t bandwidth_;
};

/** Route map entry sequence. */
class EOS_SDK_PUBLIC route_map_entry_t {
 public:
   route_map_entry_t();
   explicit route_map_entry_t(bool permit);

   /** Getter for 'permit': Permit sequence entry when true, deny otherwise. */
   bool permit() const;
   /** Setter for 'permit'. */
   void permit_is(bool permit);

   /**
    * Getter for 'continue_sequence': Continue to a different map entry. Set to 0
    * for deletion.
    */
   route_map_sequence_number_t continue_sequence() const;
   /** Setter for 'continue_sequence'. */
   void continue_sequence_is(route_map_sequence_number_t continue_sequence);

   /**
    * Getter for 'link_bandwidth': BGP extended community link bandwidth attribute.
    */
   route_map_link_bandwidth_t link_bandwidth() const;
   /** Setter for 'link_bandwidth'. */
   void link_bandwidth_is(route_map_link_bandwidth_t const & link_bandwidth);

   /** Remove the link bandwidth configuration. */
   void link_bandwidth_del();
   bool operator==(route_map_entry_t const & other) const;
   bool operator!=(route_map_entry_t const & other) const;
   /** The hash function for type route_map_entry_t. */
   uint32_t hash() const;
   /** The hash mix function for type route_map_entry_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * route_map_entry_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const route_map_entry_t& obj);

 private:
   bool permit_;
   route_map_sequence_number_t continue_sequence_;
   route_map_link_bandwidth_t link_bandwidth_;
};

class EOS_SDK_PUBLIC route_map_t {
 public:

   /**
    * Getter for 'map_entry': A map of route map entries, keyed by sequence number.
    */
   std::map<route_map_sequence_number_t, route_map_entry_t> const & map_entry()
          const;
   /** Setter for 'map_entry'. */
   void map_entry_is(

         std::map<route_map_sequence_number_t, route_map_entry_t> const &
         map_entry);
   /** Inserts key/value pair to the map. */
   void map_entry_set(route_map_sequence_number_t const & key,
                      route_map_entry_t const & value);
   /** Deletes the key/value pair from the map. */
   void map_entry_del(route_map_sequence_number_t const & key);

   bool operator==(route_map_t const & other) const;
   bool operator!=(route_map_t const & other) const;
   /** The hash function for type route_map_t. */
   uint32_t hash() const;
   /** The hash mix function for type route_map_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of route_map_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const route_map_t& obj);

 private:
   std::map<route_map_sequence_number_t, route_map_entry_t> map_entry_;
};
}

#include <eos/inline/types/route_map.h>

#endif // EOS_TYPES_ROUTE_MAP_H
