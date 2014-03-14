// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_DIRECTFLOW_H
#define EOS_DIRECTFLOW_H

#include <set>

#include <eos/base.h>
#include <eos/eth.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/iterator.h>

namespace eos {

typedef uint16_t flow_priority_t;
typedef uint16_t eth_type_t;
typedef uint8_t cos_t;

/// Defines the set of fields to match on
class EOS_SDK_PUBLIC flow_match_field_set_t {
 public:
   flow_match_field_set_t();

   bool operator==(flow_match_field_set_t const & other) const;
   bool operator!=(flow_match_field_set_t const & other) const;

   void input_intfs_is(bool);
   bool input_intfs() const;

   void eth_src_is(bool);
   bool eth_src() const;

   void eth_dst_is(bool);
   bool eth_dst() const;

   void eth_type_is(bool);
   bool eth_type() const;

   void vlan_id_is(bool);
   bool vlan_id() const;

   void cos_is(bool);
   bool cos() const;

   void ip_src_is(bool);
   bool ip_src() const;

   void ip_dst_is(bool);
   bool ip_dst() const;

 private:
   friend class directflow_mgr;
   uint32_t match_bitset_;
};

/// Match criteria for a flow
class EOS_SDK_PUBLIC flow_match_t {
 public:
   flow_match_t();

   bool operator==(flow_match_t const & other) const;
   bool operator!=(flow_match_t const & other) const;

   /// Specify which fields to match on
   void match_field_set_is(const flow_match_field_set_t &);
   flow_match_field_set_t match_field_set() const;

   /// Match on input interface.
   void input_intfs_is(const std::set<intf_id_t> &);
   std::set<intf_id_t> input_intfs() const;
   // input_intf_set and input_intf_del are a workaround
   // until there is proper support for std::set in python.
   // consider these deprecated
   void input_intf_set(intf_id_t);
   void input_intf_del(intf_id_t);

   /// Match on source Eth address
   void eth_src_is(eth_addr_t src, eth_addr_t mask);
   eth_addr_t eth_src() const;
   eth_addr_t eth_src_mask() const;
   /// Match on destination Eth address
   void eth_dst_is(eth_addr_t dst, eth_addr_t mask);
   eth_addr_t eth_dst() const;
   eth_addr_t eth_dst_mask() const;
   /// Match on Eth type
   void eth_type_is(eth_type_t);
   eth_type_t eth_type() const;

   /**
    * Match on VLAN id
    * 0 means match configured native VLAN
    */
   void vlan_id_is(vlan_id_t, uint16_t mask);
   vlan_id_t vlan_id() const;
   uint16_t vlan_id_mask() const;
   /**
    * Match on class of service
    * Only used if vlan_id is set to something other than 0
    */
   void cos_is(cos_t);
   cos_t cos() const;

   /// Match on source IPv4 address
   void ip_src_is(const ip_addr_t & src, const ip_addr_t & mask);
   ip_addr_t ip_src() const;
   ip_addr_t ip_src_mask() const;
   /// Match on destination IPv4 address
   void ip_dst_is(const ip_addr_t & dst, const ip_addr_t & mask);
   ip_addr_t ip_dst() const;
   ip_addr_t ip_dst_mask() const;

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

/// Defines the set of enabled actions
class EOS_SDK_PUBLIC flow_action_set_t {
 public:
   flow_action_set_t();

   bool operator==(flow_action_set_t const & other) const;
   bool operator!=(flow_action_set_t const & other) const;

   bool set_output_intfs() const;
   void set_output_intfs_is(bool);

   bool set_vlan_id() const;
   void set_vlan_id_is(bool);

   bool set_cos() const;
   void set_cos_is(bool);

   bool set_eth_src() const;
   void set_eth_src_is(bool);

   bool set_eth_dst() const;
   void set_eth_dst_is(bool);

   bool set_ip_src() const;
   void set_ip_src_is(bool);

   bool set_ip_dst() const;
   void set_ip_dst_is(bool);

 private:
   friend class directflow_mgr;
   uint32_t action_bitset_;
};

/// Defines the actions to take on a matching flow
class EOS_SDK_PUBLIC flow_action_t {
 public:
   flow_action_t();

   bool operator==(flow_action_t const & other) const;
   bool operator!=(flow_action_t const & other) const;

   /// Specify which actions are enabled
   void action_set_is(const flow_action_set_t &);
   flow_action_set_t action_set() const;

   /**
    * Specify 0 or more output interfaces
    * Passing in the empty set will cause the packet to be dropped.
    */
   void output_intfs_is(const std::set<intf_id_t> &);
   std::set<intf_id_t> output_intfs() const;
   // output_intf_set and output_intf_del are a workaround
   // until there is proper support for std::set in python.
   // consider these deprecated
   void output_intf_set(intf_id_t);
   void output_intf_del(intf_id_t);

   /**
    * Specify the VLAN id
    * 0 means use configured native VLAN
    */
   void vlan_id_is(vlan_id_t);
   vlan_id_t vlan_id() const;
   /// Specify the cos
   void cos_is(cos_t);
   cos_t cos() const;

   /// Rewrite the destination eth address
   void eth_src_is(eth_addr_t);
   eth_addr_t eth_src() const;
   /// Rewrite the source eth address
   void eth_dst_is(eth_addr_t);
   eth_addr_t eth_dst() const;

   /// Rewrite the source IP address
   void ip_src_is(const ip_addr_t &);
   ip_addr_t ip_src() const;
   /// Rewrite the destination IP address
   void ip_dst_is(const ip_addr_t &);
   ip_addr_t ip_dst() const;

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

/// A flow entry
class EOS_SDK_PUBLIC flow_entry_t {
 public:
   flow_entry_t();
   flow_entry_t(const std::string & name, flow_match_t,
                flow_action_t, flow_priority_t);

   bool operator==(flow_entry_t const & other) const;
   bool operator!=(flow_entry_t const & other) const;

   std::string name() const;
   flow_match_t match() const;
   flow_action_t action() const;
   flow_priority_t priority() const;

 private:
   std::string name_;
   flow_match_t match_;
   flow_action_t action_;
   flow_priority_t priority_;
};


/// Counters for a flow entry
class EOS_SDK_PUBLIC flow_counters_t {
 public:
   flow_counters_t();

   bool operator==(flow_counters_t const & other) const;
   bool operator!=(flow_counters_t const & other) const;

   uint64_t bytes() const;
   uint64_t packets() const;

 private:
   friend class directflow_mgr;
   uint64_t bytes_;
   uint64_t packets_;
};

/**
 * Flow entry status
 */
enum flow_status_t {
   FLOW_STATUS_UNKNOWN,
   FLOW_CREATED,                ///< Flow created or modified in hardware
   FLOW_DELETED,                ///< Flow removed from hardware
   FLOW_REJECTED,               ///< Flow not created
};

/**
 * Reason why a flow was not successfully created
 * in hardware
 */
enum flow_rejected_reason_t {
   FLOW_REJECTED_BAD_MATCH,     ///< Flow not created due to bad match criteria
   FLOW_REJECTED_BAD_ACTION,    ///< Flow not created due to bad action criteria
   FLOW_REJECTED_HW_TABLE_FULL, ///< Flow not created due to insufficient resources
   FLOW_REJECTED_OTHER,         ///< Flow not created for some other reason
};

/**
 * Flow handler.
 *
 * A flow handler is notified when the status of configured flows changes.
 */
class EOS_SDK_PUBLIC flow_handler {
 public:
   flow_handler();
   virtual ~flow_handler();

   /**
    * Registers this class to receive updates on changes to
    * flow state. Expects a boolean signifying whether notifications
    * should be proagated to this instance or not.
    */
   void watch_all_flows(bool);

   /// Handler called when flow status changes
   virtual void on_flow_status(const std::string & name, flow_status_t);

 private:
   bool watching_all_flows_;
};


class flow_entry_iter_impl;

/// An iterator providing forwards iteration through the configured flows
class EOS_SDK_PUBLIC flow_entry_iter_t : public iter_base<flow_entry_t,
                                                          flow_entry_iter_impl> {
 private:
   friend class flow_entry_iter_impl;
   explicit flow_entry_iter_t(flow_entry_iter_impl * const) EOS_SDK_PRIVATE;
};


/**
 * DirectFlow configuration and status manager.
 */
class EOS_SDK_PUBLIC directflow_mgr {
 public:
   /// Iterate across all configured flows
   flow_entry_iter_t flow_entry_iter() const;

   /// Tests for existence of a flow entry with the given name
   bool exists(std::string const &) const;

   // Flow management functions

   /// Insert or update a flow
   void flow_entry_set(flow_entry_t const &);
   /// Delete a flow
   void flow_entry_del(std::string const &);

   /// Return the status of the given flow
   flow_status_t flow_status(std::string const & name) const;
   /**
    * The reason a flow was not programmed. Only valid if the flow's
    * status is FLOW_REJECTED
    */
   flow_rejected_reason_t flow_rejected_reason(std::string const & name) const;
   /// Return the counters for a flow
   flow_counters_t flow_counters(std::string const & name) const;

 protected:
   directflow_mgr() EOS_SDK_PRIVATE;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(directflow_mgr);
};

directflow_mgr * get_directflow_mgr() EOS_SDK_PUBLIC;

} // end namespace eos

#include <eos/inline/directflow.h>

#endif // EOS_DIRECTFLOW_H
