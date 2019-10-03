// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_DIRECTFLOW_H
#define EOS_TYPES_DIRECTFLOW_H

#include <eos/eth.h>
#include <eos/exception.h>
#include <eos/hash_mix.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <set>
#include <sstream>

namespace eos {

typedef uint16_t flow_priority_t;

typedef uint16_t eth_type_t;

typedef uint8_t cos_t;

/** Defines the set of fields to match on flow. */
class EOS_SDK_PUBLIC flow_match_field_set_t {
 public:
   flow_match_field_set_t();

   void input_intfs_is(bool enabled);
   bool input_intfs() const;
   void eth_src_is(bool enabled);
   bool eth_src() const;
   void eth_dst_is(bool enabled);
   bool eth_dst() const;
   void eth_type_is(bool enabled);
   bool eth_type() const;
   void vlan_id_is(bool enabled);
   bool vlan_id() const;
   void cos_is(bool enabled);
   bool cos() const;
   void ip_src_is(bool enabled);
   bool ip_src() const;
   void ip_dst_is(bool enabled);
   bool ip_dst() const;
   bool operator==(flow_match_field_set_t const & other) const;
   bool operator!=(flow_match_field_set_t const & other) const;
   bool operator<(flow_match_field_set_t const & other) const;
   /** The hash function for type flow_match_field_set_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * flow_match_field_set_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const flow_match_field_set_t& obj);

 private:
   friend class flow_helper;
   uint32_t match_bitset_;
};

/** Match criteria for a flow. */
class EOS_SDK_PUBLIC flow_match_t {
 public:
   flow_match_t();

   /** Getter for 'match_field_set': the fields to match on. */
   flow_match_field_set_t match_field_set() const;
   /** Setter for 'match_field_set'. */
   void match_field_set_is(flow_match_field_set_t match_field_set);

   /** Getter for 'input_intfs': the input interfaces to match on. */
   std::set<intf_id_t> const & input_intfs() const;
   /** Setter for 'input_intfs'. */
   void input_intfs_is(std::set<intf_id_t> const & input_intfs);
   /** Inserts one input_intf of 'value' to the set. */
   void input_intf_set(intf_id_t const & value);
   /** Deletes one input_intf of 'value' from the set. */
   void input_intf_del(intf_id_t const & value);

   /** Getter for 'eth_src': the source Ethernet address to match on. */
   eth_addr_t eth_src() const;
   /** Setter for 'eth_src'. */
   void eth_src_is(eth_addr_t eth_src);

   void eth_src_is(eth_addr_t src, eth_addr_t mask);

   eth_addr_t eth_src_mask() const;
   void eth_src_mask_is(eth_addr_t eth_src_mask);

   /** Getter for 'eth_dst': the destination Ethernet address to match on. */
   eth_addr_t eth_dst() const;
   /** Setter for 'eth_dst'. */
   void eth_dst_is(eth_addr_t eth_dst);

   void eth_dst_is(eth_addr_t dst, eth_addr_t mask);

   eth_addr_t eth_dst_mask() const;
   void eth_dst_mask_is(eth_addr_t eth_dst_mask);

   /** Getter for 'eth_type': the Ethernet type to match on. */
   eth_type_t eth_type() const;
   /** Setter for 'eth_type'. */
   void eth_type_is(eth_type_t eth_type);

   /** Getter for 'vlan_id': the VLAN id to match. */
   vlan_id_t vlan_id() const;
   /** Setter for 'vlan_id'. */
   void vlan_id_is(vlan_id_t vlan_id);

   void vlan_id_is(vlan_id_t vlan_id, uint16_t mask);

   vlan_id_t vlan_id_mask() const;
   void vlan_id_mask_is(vlan_id_t vlan_id_mask);

   /**
    * Getter for 'cos': the class of service to match on, only used if vlan_id is
    * set to something other than 0.
    */
   cos_t cos() const;
   /** Setter for 'cos'. */
   void cos_is(cos_t cos);

   /** Getter for 'ip_src': the source IPv4 address to match on. */
   ip_addr_t ip_src() const;
   /** Setter for 'ip_src'. */
   void ip_src_is(ip_addr_t const & ip_src);

   void ip_src_is(ip_addr_t const & src, ip_addr_t const & mask);

   ip_addr_t ip_src_mask() const;
   void ip_src_mask_is(ip_addr_t const & ip_src_mask);

   /** Getter for 'ip_dst': the destination IPv4 address to match on. */
   ip_addr_t ip_dst() const;
   /** Setter for 'ip_dst'. */
   void ip_dst_is(ip_addr_t const & ip_dst);

   void ip_dst_is(ip_addr_t const & dst, ip_addr_t const & mask);

   ip_addr_t ip_dst_mask() const;
   void ip_dst_mask_is(ip_addr_t const & ip_dst_mask);

   bool operator==(flow_match_t const & other) const;
   bool operator!=(flow_match_t const & other) const;
   bool operator<(flow_match_t const & other) const;
   /** The hash function for type flow_match_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of flow_match_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const flow_match_t& obj);

 private:
   flow_match_field_set_t match_field_set_;
   std::set<intf_id_t> input_intfs_;
   eth_addr_t eth_src_;
   eth_addr_t eth_src_mask_;
   eth_addr_t eth_dst_;
   eth_addr_t eth_dst_mask_;
   eth_type_t eth_type_;
   vlan_id_t vlan_id_;
   vlan_id_t vlan_id_mask_;
   cos_t cos_;
   ip_addr_t ip_src_;
   ip_addr_t ip_src_mask_;
   ip_addr_t ip_dst_;
   ip_addr_t ip_dst_mask_;
};

/** Defines the set of enabled actions. */
class EOS_SDK_PUBLIC flow_action_set_t {
 public:
   flow_action_set_t();

   void set_output_intfs_is(bool enabled);
   bool set_output_intfs() const;

   void set_vlan_id_is(bool enabled);
   bool set_vlan_id() const;

   void set_cos_is(bool enabled);
   bool set_cos() const;

   void set_eth_src_is(bool enabled);
   bool set_eth_src() const;

   void set_eth_dst_is(bool enabled);
   bool set_eth_dst() const;

   void set_ip_src_is(bool enabled);
   bool set_ip_src() const;

   void set_ip_dst_is(bool enabled);
   bool set_ip_dst() const;

   bool operator==(flow_action_set_t const & other) const;
   bool operator!=(flow_action_set_t const & other) const;
   /** The hash function for type flow_action_set_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * flow_action_set_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const flow_action_set_t& obj);

 private:
   friend class flow_helper;
   uint32_t action_bitset_;
};

/** Defines the actions to take on a matching flow. */
class EOS_SDK_PUBLIC flow_action_t {
 public:
   flow_action_t();

   /** Getter for 'action_set': actions that are enabled. */
   flow_action_set_t action_set() const;
   /** Setter for 'action_set'. */
   void action_set_is(flow_action_set_t action_set);

   /**
    * Getter for 'output_intfs': 0 or more the output interfaces, passing in the
    * empty set will cause the packet to be dropped.
    */
   std::set<intf_id_t> const & output_intfs() const;
   /** Setter for 'output_intfs'. */
   void output_intfs_is(std::set<intf_id_t> const & output_intfs);
   /** Inserts one output_intf of 'value' to the set. */
   void output_intf_set(intf_id_t const & value);
   /** Deletes one output_intf of 'value' from the set. */
   void output_intf_del(intf_id_t const & value);

   vlan_id_t vlan_id() const;
   void vlan_id_is(vlan_id_t vlan_id);

   /** Getter for 'cos': the class of service. */
   cos_t cos() const;
   /** Setter for 'cos'. */
   void cos_is(cos_t cos);

   /** Getter for 'eth_src': the source Ethernet address. */
   eth_addr_t eth_src() const;
   /** Setter for 'eth_src'. */
   void eth_src_is(eth_addr_t eth_src);

   /** Getter for 'eth_dst': the destination Ethernet address. */
   eth_addr_t eth_dst() const;
   /** Setter for 'eth_dst'. */
   void eth_dst_is(eth_addr_t eth_dst);

   /** Getter for 'ip_src': the source IPv4 address. */
   ip_addr_t ip_src() const;
   /** Setter for 'ip_src'. */
   void ip_src_is(ip_addr_t const & ip_src);

   /** Getter for 'ip_dst': the destination IPv4 address. */
   ip_addr_t ip_dst() const;
   /** Setter for 'ip_dst'. */
   void ip_dst_is(ip_addr_t const & ip_dst);

   bool operator==(flow_action_t const & other) const;
   bool operator!=(flow_action_t const & other) const;
   /** The hash function for type flow_action_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of flow_action_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const flow_action_t& obj);

 private:
   flow_action_set_t action_set_;
   std::set<intf_id_t> output_intfs_;
   vlan_id_t vlan_id_;
   cos_t cos_;
   eth_addr_t eth_src_;
   eth_addr_t eth_dst_;
   ip_addr_t ip_src_;
   ip_addr_t ip_dst_;
};

/** Defines a flow entry. */
class EOS_SDK_PUBLIC flow_entry_t {
 public:
   flow_entry_t();
   flow_entry_t(std::string const & name, flow_match_t match, flow_action_t action,
                flow_priority_t priority);

   std::string name() const;

   flow_match_t match() const;

   flow_action_t action() const;

   flow_priority_t priority() const;

   bool operator==(flow_entry_t const & other) const;
   bool operator!=(flow_entry_t const & other) const;
   /** The hash function for type flow_entry_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of flow_entry_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const flow_entry_t& obj);

 private:
   std::string name_;
   flow_match_t match_;
   flow_action_t action_;
   flow_priority_t priority_;
};

/** Defines counters for a flow. */
class EOS_SDK_PUBLIC flow_counters_t {
 public:
   flow_counters_t();

   uint64_t bytes() const;

   uint64_t packets() const;

   bool operator==(flow_counters_t const & other) const;
   bool operator!=(flow_counters_t const & other) const;
   /** The hash function for type flow_counters_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * flow_counters_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const flow_counters_t& obj);

 private:
   friend class flow_helper;
   uint64_t bytes_;
   uint64_t packets_;
};

/** Flow entry status. */
enum flow_status_t {
   FLOW_STATUS_UNKNOWN,
   /** Flow created or modified in hardware. */
   FLOW_CREATED,
   /** Flow removed from hardware. */
   FLOW_DELETED,
   /** Flow not created. */
   FLOW_REJECTED,
   /** Flow requesting hardware resources. */
   FLOW_PENDING,
   /** Flow request submitted for tcam resource entry. */
   FLOW_HW_TABLE_PENDING,
   /** Flow request accepted. */
   FLOW_REQUEST_ACCEPTED,
};
/** Appends a string representation of enum flow_status_t value to the ostream. */
std::ostream& operator<<(std::ostream& os, const flow_status_t & enum_val);

/** Reason why a flow was not successfully created in hardware. */
enum flow_rejected_reason_t {
   /** Flow not created due to bad match criteria. */
   FLOW_REJECTED_BAD_MATCH,
   /** Flow not created due to bad action criteria. */
   FLOW_REJECTED_BAD_ACTION,
   /** Flow not created due to insufficient resources. */
   FLOW_REJECTED_HW_TABLE_FULL,
   /** Flow not created for some other reason. */
   FLOW_REJECTED_OTHER,
   /** Flow not created due to unsupported action set. */
   FLOW_REJECTED_ACTIONS_UNSUPPORTED,
   /** Flow not created due to unsupported timeouts set. */
   FLOW_REJECTED_TIMEOUT_NOT_SUPPORTED,
};
/**
 * Appends a string representation of enum flow_rejected_reason_t value to the
 * ostream.
 */
std::ostream& operator<<(std::ostream& os, const flow_rejected_reason_t & enum_val);
}

#include <eos/inline/types/directflow.h>

#endif // EOS_TYPES_DIRECTFLOW_H
