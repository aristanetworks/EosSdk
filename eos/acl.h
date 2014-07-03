// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ACL_H
#define EOS_ACL_H

#include <list>
#include <utility>

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/eth.h>
#include <eos/ip.h>
#include <eos/intf.h>

namespace eos {

class acl_internal;

/// The ACL type, of which valid types are either IPv4, IPv6, or Ethernet.
enum acl_type_t {
   ACL_TYPE_NULL,
   ACL_TYPE_IPV4,
   ACL_TYPE_IPV6,
   ACL_TYPE_ETH,
   ACL_TYPE_MPLS,
};

/**
 * The direction in which an ACL is applied.
 * To apply in both directions, use both operations in order.
 */
enum acl_direction_t {
   ACL_DIRECTION_NULL,
   ACL_IN,
   ACL_OUT,
};

/// The type of range operator for TTL and port specifications below.
enum acl_range_operator_t {
   ACL_RANGE_NULL,
   ACL_RANGE_ANY,
   ACL_RANGE_EQ,
   ACL_RANGE_GT,
   ACL_RANGE_LT,
   ACL_RANGE_NEQ,
   ACL_RANGE_BETWEEN,
};

/// The action to take for an individual ACL rule
enum acl_action_t {
   ACL_ACTION_NULL,
   ACL_PERMIT,
   ACL_DENY,
};

/// TCP flags used in IP rules to specify which TCP flags to match
enum acl_tcp_flag_t {
   ACL_TCP_NULL = 0,
   ACL_TCP_FIN = 1,
   ACL_TCP_SYN = 2,
   ACL_TCP_RST = 4,
   ACL_TCP_PSH = 8,
   ACL_TCP_ACK = 16,
   ACL_TCP_URG = 32,
};

/**
 * A TTL specifier, used in an IP ACL rule to define TTLs to match.
 *
 * Create an instance of the classes below, such as a
 * acl_ttl_spec_gt_t to specify matching TTLs greater than the value
 * passed.
 */
class EOS_SDK_PUBLIC acl_ttl_spec_t {
 public:
   acl_ttl_spec_t();  // Default TTL spec; matches any TTL

   acl_range_operator_t oper() const;
   uint8_t ttl() const;

   void oper_is(acl_range_operator_t a);
   void ttl_is(uint8_t u);

 protected:
   acl_range_operator_t oper_;  // BETWEEN is not supported.
   uint8_t ttl_;
   friend class acl_internal;
};

/// Matches an exact TTL
class EOS_SDK_PUBLIC acl_ttl_spec_eq_t : public acl_ttl_spec_t {
 public:
   explicit acl_ttl_spec_eq_t(uint8_t ttl);
   friend class acl_internal;
};

/// Matches all TTLs except this
class EOS_SDK_PUBLIC acl_ttl_spec_neq_t : public acl_ttl_spec_t {
 public:
   explicit acl_ttl_spec_neq_t(uint8_t ttl);
   friend class acl_internal;
};

/// Matches TTLs greater than this
class EOS_SDK_PUBLIC acl_ttl_spec_gt_t : public acl_ttl_spec_t {
 public:
   explicit acl_ttl_spec_gt_t(uint8_t ttl);
   friend class acl_internal;
};

/// Matches TTLs less than this
class EOS_SDK_PUBLIC acl_ttl_spec_lt_t : public acl_ttl_spec_t {
 public:
   explicit acl_ttl_spec_lt_t(uint8_t ttl);
   friend class acl_internal;
};

/// Matches any TTL value
class EOS_SDK_PUBLIC acl_ttl_spec_any_t : public acl_ttl_spec_t {
 public:
   explicit acl_ttl_spec_any_t();
   friend class acl_internal;
};

/**
 * A UDP or TCP port specifier.
 *
 * Pick one of either:
 * - acl_port_spec_eq_t : Matches 1-10 port numbers
 * - acl_port_spec_neq_t : Doesn't match these 1-10 ports
 * - acl_port_spec_lt_t : Matches ports less than the value
 * - acl_port_spec_gt_t : Matches ports greater than the value
 * - acl_port_spec_between_t : Matches ports between the two values
 */
class EOS_SDK_PUBLIC acl_port_spec_t {
 public:
   acl_port_spec_t();  // Default port spec; matches any port
   acl_range_operator_t oper() const;
   std::list<uint16_t> const & ports() const;

   void oper_is(acl_range_operator_t a);
   void ports_is(std::list<uint16_t> const & l);
 protected:
   acl_range_operator_t oper_;
   std::list<uint16_t> ports_;

   friend class acl_internal;
};

/// Matches one or more ports exactly
class EOS_SDK_PUBLIC acl_port_spec_eq_t : public acl_port_spec_t {
 public:
   explicit acl_port_spec_eq_t(uint16_t port);
   explicit acl_port_spec_eq_t(std::list<uint16_t> const & ports);
   friend class acl_internal;
};

/// Matches every port except these one or more ports
class EOS_SDK_PUBLIC acl_port_spec_neq_t : public acl_port_spec_t {
 public:
   explicit acl_port_spec_neq_t(uint16_t port);
   explicit acl_port_spec_neq_t(std::list<uint16_t> const & ports);

   friend class acl_internal;
};

/// Matches ports between low and high
class EOS_SDK_PUBLIC acl_port_spec_between_t : public acl_port_spec_t {
 public:
   acl_port_spec_between_t(uint16_t low, uint16_t high);
   friend class acl_internal;
};

/// Matches ports greater than this
class EOS_SDK_PUBLIC acl_port_spec_gt_t : public acl_port_spec_t {
 public:
   explicit acl_port_spec_gt_t(uint16_t port);
   friend class acl_internal;
};

/// Matches ports less than this
class EOS_SDK_PUBLIC acl_port_spec_lt_t : public acl_port_spec_t {
 public:
   explicit acl_port_spec_lt_t(uint16_t port);
   friend class acl_internal;
};

/// Matches any port number
class EOS_SDK_PUBLIC acl_port_spec_any_t : public acl_port_spec_t {
 public:
   explicit acl_port_spec_any_t();
   friend class acl_internal;
};

/// An ACL key is the combination of its name and ACL type (IPv4, IPv6 or ETH)
class EOS_SDK_PUBLIC acl_key_t {
 public:
   acl_key_t();
   acl_key_t(std::string const & acl_name, acl_type_t acl_type);

   std::string const acl_name() const;
   acl_type_t acl_type() const;

   bool operator() (acl_key_t const &, acl_key_t const &) const;
   bool operator==(acl_key_t const &) const;

  private:
   std::string acl_name_;
   acl_type_t acl_type_;
};

// Classes that represent access lists (ACLs)
// Access lists are sequences of rules specifying per-packet rules
// filters apply to either IPv4, IPv6 or ETH (layer 2) traffic and are
// attached to traffic arriving (in) or leaving (out) on zero or more
// interfaces.

// To use ACL rules in these libraries, construct the appropriate
// concrete type of rule you desire, either a:
//  * acl_rule_ip_t  or a
//  * acl_rule_eth_t

// Base parameters common to all filter types are defined on the parent
// acl_base_filter_t, such as 'log' to enable logging of packets matching
// the rule, and the action applied to packets matching the rule.

/**
 * Base ACL rule class containing common fields.
 *
 * Instead of this, instantiate one of the concrete rule classes.
 */
class EOS_SDK_PUBLIC acl_rule_base_t {
 public:
  bool log() const;
  bool tracked() const;
  acl_action_t action() const;

  void log_is(bool l);
  void tracked_is(bool t);
  void action_is(acl_action_t a);

 private:
   acl_action_t action_;
   bool log_;
   bool tracked_;

 protected:
   acl_rule_base_t() EOS_SDK_PRIVATE;
};

/// An individual ACL rule for IPv4 or IPv6 ACLs
class EOS_SDK_PUBLIC acl_rule_ip_t : public acl_rule_base_t {
 public:
   acl_rule_ip_t();
   vlan_id_t inner_vlan() const;
   vlan_id_t vlan() const;
   vlan_id_t vlan_mask() const;
   vlan_id_t inner_vlan_mask() const;
   ip_addr_mask_t source_addr() const;
   ip_addr_mask_t destination_addr() const;
   acl_port_spec_t source_port() const;
   acl_port_spec_t destination_port() const;
   acl_ttl_spec_t ttl() const;
   uint8_t ip_protocol() const;
   uint16_t tcp_flags() const;
   bool established() const;
   uint16_t icmp_type() const;
   uint16_t icmp_code() const;
   uint8_t priority_value() const;
   uint8_t priority_mask() const;
   bool match_fragments() const;
   bool match_ip_priority() const;

   void vlan_is(vlan_id_t v);
   void vlan_mask_is(vlan_id_t v);
   void inner_vlan_is(vlan_id_t v);
   void inner_vlan_mask_is(vlan_id_t v);
   void ip_protocol_is(uint8_t ip);
   void ttl_is(acl_ttl_spec_t t);
   void source_addr_is(ip_addr_mask_t const & ip);
   void destination_addr_is(ip_addr_mask_t const & ip);
   void source_port_is(acl_port_spec_t const & a);
   void destination_port_is(acl_port_spec_t const & a);
   void tcp_flags_is(uint16_t n);
   void established_is(bool b);
   void icmp_type_is(uint16_t n);
   void icmp_code_is(uint16_t n);
   void priority_value_is(uint8_t n);
   void priority_mask_is(uint8_t n);
   void match_fragments_is(bool b);
   void match_ip_priority_is(bool b);
 private:
   vlan_id_t vlan_;
   vlan_id_t vlan_mask_;
   vlan_id_t inner_vlan_;
   vlan_id_t inner_vlan_mask_;

   uint8_t ip_protocol_;

   acl_ttl_spec_t ttl_;

   ip_addr_mask_t source_addr_;
   ip_addr_mask_t destination_addr_;

   acl_port_spec_t source_port_;
   acl_port_spec_t destination_port_;

   // Bitmask of TCP flags to match, if set
   uint16_t tcp_flags_;
   // Match "established" connections
   bool established_;

   // Match a specific ICMP type and code
   // The default value 0xFFFF matches all types or codes
   uint16_t icmp_type_;
   uint16_t icmp_code_;

   uint8_t priority_value_;// 0..63, DSCP match to value (IPv4);traffic class (IPv6)
   uint8_t priority_mask_; // supported for IPv6 only
   bool match_fragments_;  // match IP fragments?
   // Match DSCP (IPv4) or TE (IPv6) data provided in priority_{value,mask}
   bool match_ip_priority_;
};

/// An Ethernet ACL, which can be applied to Ethernet, Vlan, and MLAG interfaces.
class EOS_SDK_PUBLIC acl_rule_eth_t : public acl_rule_base_t {
 public:
   acl_rule_eth_t();

   vlan_id_t vlan() const;
   vlan_id_t vlan_mask() const;
   vlan_id_t inner_vlan() const;
   vlan_id_t inner_vlan_mask() const;
   eth_addr_t source_addr() const;
   eth_addr_t source_mask() const;
   eth_addr_t destination_addr() const;
   eth_addr_t destination_mask() const;

   void vlan_is(vlan_id_t v);
   void vlan_mask_is(vlan_id_t v);
   void inner_vlan_is(vlan_id_t v);
   void inner_vlan_mask_is(vlan_id_t v);
   void source_addr_is(eth_addr_t const & e);
   void source_mask_is(eth_addr_t const & e);
   void destination_addr_is(eth_addr_t const & e);
   void destination_mask_is(eth_addr_t const & e);

 private:
   vlan_id_t vlan_;
   vlan_id_t vlan_mask_;
   vlan_id_t inner_vlan_;
   vlan_id_t inner_vlan_mask_;

   eth_addr_t source_addr_;
   eth_addr_t source_mask_;
   eth_addr_t destination_addr_;
   eth_addr_t destination_mask_;
};

class acl_mgr;

/**
 * An ACL handler.
 *
 * Derive from this class to react to ACL hardware synchronisation events.
 */
class EOS_SDK_PUBLIC acl_handler : public base_handler<acl_mgr, acl_handler> {
 public:
   explicit acl_handler(acl_mgr *);
   acl_mgr * get_acl_mgr() const;

   /**
    * Watches updates to synchronization status for all ACLs.
    * This defaults to false at handler construction time.
    *
    * @param bool If true, receive ACL sync status notifications, else do not.
    */
   void watch_all_acls(bool);

   /**
    * Called upon hardware succesfully committing all pending transactions.
    *
    * It may be called more than once for a single transaction, or
    * only once for a whole bunch of separate ACL updates. In fact, if
    * someone updates an ACL in the CLI, this function may get called,
    * i.e., it can get called once for zero transactions.
    */
   virtual void on_acl_sync();

   /**
    * Called upon a problem stopping ACL configuration from being commited.
    *
    * This indicates that the ACL config (as stored in Sysdb) cannot
    * be loaded into hardware, ever. It must be changed in some way to
    * get Sysdb and the hardware back in sync. The most common
    * problem, of course, is too many ACLs or ACL entries. It is up to
    * you to find some things to delete, commit those deletions, and
    * then see if things fit once again (on_acl_sync() will get called
    * if they do, or on_acl_sync_fail() will get called again if they
    * don't). Note you may be notified more than once of the same
    * problem, and you may be notified of problems that have nothing
    * to do with you, such as an operator at the CLI doing something
    * unsupported.
    */
   virtual void on_acl_sync_fail(std::string const & linecard,
                                 std::string const & message);
};

class acl_iter_impl;

/// An ACL iterator.
class EOS_SDK_PUBLIC acl_iter_t : public iter_base<acl_key_t, acl_iter_impl> {
 private:
   friend class acl_iter_impl;
   explicit acl_iter_t(acl_iter_impl * const) EOS_SDK_PRIVATE;
};

/// A rule in an IP ACL.
typedef std::pair<uint32_t, acl_rule_ip_t> acl_rule_ip_entry_t;

class acl_rule_ip_iter_impl;

/// An IP ACL rule iterator.
class EOS_SDK_PUBLIC acl_rule_ip_iter_t : public iter_base<acl_rule_ip_entry_t,
                                                           acl_rule_ip_iter_impl> {
 private:
   friend class acl_rule_ip_iter_impl;
   explicit acl_rule_ip_iter_t(acl_rule_ip_iter_impl * const) EOS_SDK_PRIVATE;
};

/// A rule in an Ethernet ACL.
typedef std::pair<uint32_t, acl_rule_eth_t> acl_rule_eth_entry_t;

class acl_rule_eth_iter_impl;

/// An Ethernet ACL rule iterator.
class EOS_SDK_PUBLIC acl_rule_eth_iter_t : public iter_base<acl_rule_eth_entry_t,
                                                            acl_rule_eth_iter_impl> {
 private:
   friend class acl_rule_eth_iter_impl;
   explicit acl_rule_eth_iter_t(acl_rule_eth_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * The ACL manager.
 *
 * This manager provides access to current ACL configuration,
 * creation, modification and deletion of ACLs, and functions to
 * commit changes, apply ACLs to interfaces as well as manage
 * fragements mode and enabling counters.
 *
 * When managing ACLs, you provide give an ACL key to modify, a
 * "sequence number" which starts at 1 and goes up to MAXINT, and for
 * set operations, the rule to set. Note: you must call commit() for
 * your changes here to get pushed into the hardware, and once you
 * have started setting rules, you must call acl_commit() prior to any
 * calls to acl_apply(), else the manager will panic(). Note that
 * extremely large numbers of ACLs or rules per ACL can result in
 * undefined behaviour, including a switch reload.
 */
class EOS_SDK_PUBLIC acl_mgr : public base_mgr<acl_handler> {
 public:
   virtual ~acl_mgr();

   typedef bool (*acl_cb)(acl_key_t const &, void * context);
   typedef bool (*acl_rule_ip_cb)(uint32_t seq,
                                  acl_rule_ip_t const &,
                                  void * context);
   typedef bool (*acl_rule_eth_cb)(uint32_t seq,
                                   acl_rule_eth_t const &,
                                   void * context);

   /// Iterates over all ACLs.
   virtual acl_iter_t acl_iter() const = 0;

   /**
    * Iterates over all ACLs from the beginning.
    *
    * @deprecated Use acl_iter() instead.
    * @param[in] handler An ACL callback handler.
    * @param[out] context A pointer to state to pass to the handler when called.
    */
   virtual void acl_foreach(acl_cb handler, void * context) EOS_SDK_DEPRECATED = 0;
   virtual void acl_foreach(acl_cb handler, void * context, acl_key_t bookmark)
      EOS_SDK_DEPRECATED = 0;

   /// Iterates over the rules with an IP ACL.
   virtual acl_rule_ip_iter_t acl_rule_ip_iter(acl_key_t const &) const = 0;

   /**
    * Iterates over the rules with an IP ACL.
    * Provide a callback function matching the acl_rule_cb_* definitions above.
    * @deprecated Use acl_rule_ip_iter() instead.
    */
   virtual void acl_rule_ip_foreach(acl_key_t const &, acl_rule_ip_cb,
                                    void * context) EOS_SDK_DEPRECATED = 0;

   /// Iterates over the rules with an Ethernet ACL.
   virtual acl_rule_eth_iter_t acl_rule_eth_iter(acl_key_t const &) const = 0;

   /**
    * Iterates over the rules with an Ethernet ACL.
    * Provide a callback function matching the acl_rule_cb_* definitions above.
    * @deprecated Use acl_rule_eth_iter() instead.
    */
   virtual void acl_rule_eth_foreach(acl_key_t const &, acl_rule_eth_cb,
                                     void * context) EOS_SDK_DEPRECATED = 0;

   /**
    * Configuration ACL existance test.
    *
    * @returns true if an ACL with the same name and type (i.e., key)
    * exists in the configuration, else false.
    */
   virtual bool acl_exists(acl_key_t const &) const = 0;

   /**
    * Adds an IP ACL rule to an ACL.
    *
    * If the ACL key doesn't exist, it will be created.
    * If the ACL type is not the same as the rule type, panic() is called.
    *
    * @param acl_key_t The ACL key to modify (name and ACL type)
    * @param uint32_t ACL sequence number
    * @param acl_rule_ip_t ACL rule to set at sequence number
    */
   virtual void acl_rule_set(acl_key_t const &, uint32_t,
                             acl_rule_ip_t const &) = 0;

   /**
    * Adds an Ethernet (MAC) ACL rule to an ACL.
    *
    * If the ACL doesn't exist, it will be created before the rule is
    * added to it: there is no explicit "create ACL" operation. If the
    * ACL type is not the same as the rule type (i.e., Ethernet),
    * panic() is called.
    *
    * @param acl_key_t The ACL key to modify (name and ACL type)
    * @param uint32_t ACL sequence number (in the range 1..MAXINT)
    * @param acl_rule_eth_t ACL rule to set at sequence number
    */
   virtual void acl_rule_set(acl_key_t const &, uint32_t,
                             acl_rule_eth_t const &) = 0;

   /**
    * Removes a rule from an ACL.
    *
    * If the ACL key doesn't exist, that is a no op.
    * If there is no rule at the sequence number, that is also a no op.

    * @param acl_key_t The ACL key to modify (name and ACL type)
    * @param uint32_t ACL sequence number to remove
    */
   virtual void acl_rule_del(acl_key_t const &, uint32_t) = 0;

   /**
    * Commits all rule changes and application changes made above to all ACLs.
    *
    * Pushes ACLs into Sysdb's active configuration. This commit
    * cannot fail, but it can lead to a state where not all ACLs can
    * be loaded into hardware. You will be notified via on_acl_sync()
    * when this commit and all other outstanding operations such as
    * interface applications are loaded into hardware, or
    * on_acl_sync_fail() if the newly committed configuration can't be
    * loaded. If there are no changes pending and you call this
    * function, you will get one of those callbacks depending on
    * whether the current state in Sysdb can be loaded into hardware
    * or not.
    */
   virtual void acl_commit() = 0;

   /**
    * Deletes the ACL.
    *
    * Removes all rules and unapplies from all
    * interfaces. Any pending changes to the ACL are discarded.  Is
    * effective immediately (no commit or commit notification).
    */
   virtual void acl_del(acl_key_t const &) = 0;

   /**
    * Requests that an ACL be (un)applied on the given interface and direction.
    *
    * ACL is loaded into hardware asynchronously. Like commit(), this
    * function results in a call to your handler when we have applied,
    * or failed to apply, this ACL configuration. That is, you do not
    * get a handler callback per call; you get a handler callback when
    * everything is loaded into hardware, or when we notice problems.
    *
    * API call ordering note: any acl_rule_set() or acl_rule_del()
    * calls be followed by an acl_commit() prior to calling this
    * function else a panic() will occur.
    */
   virtual void acl_apply(acl_key_t const &, intf_id_t, acl_direction_t, bool) = 0;

   /// Immediately enable or disable counters for the ACL
   virtual void acl_counters_enabled_set(acl_key_t const &, bool) = 0;

   /// Immediately enable or disable fragments matching on the ACL
   virtual void acl_fragments_enabled_set(acl_key_t const &, bool) = 0;

 protected:
   acl_mgr() EOS_SDK_PRIVATE;
   friend class acl_handler;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(acl_mgr);
};

}  // namespace eos

#include <eos/inline/acl.h>

#endif // EOS_ACL_H
