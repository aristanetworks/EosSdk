// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ACL_H
#define EOS_ACL_H

#include <list>

#include <eos/eth.h>
#include <eos/ip.h>
#include <eos/intf.h>
#include <eos/base.h>

namespace eos {

class acl_internal;

// The ACL type, of which valid types are either an IPv4, IPv6, or
// Ethernet (MAC) access list.
enum acl_type_t {
   ACL_TYPE_NULL,
   ACL_TYPE_IPV4,
   ACL_TYPE_IPV6,
   ACL_TYPE_ETH,
};

// The direction in which an ACL is applied to an interface (both
// directions is two operations).
enum acl_direction_t {
   ACL_DIRECTION_NULL,
   ACL_IN,
   ACL_OUT,
};

// The type of range operator for TTL and port specifications below.
enum acl_range_operator_t {
   ACL_RANGE_NULL,
   ACL_RANGE_ANY,
   ACL_RANGE_EQ,
   ACL_RANGE_GT,
   ACL_RANGE_LT,
   ACL_RANGE_NEQ,
   ACL_RANGE_BETWEEN,
};

// The action for an individual ACL rule.
enum acl_action_t {
   ACL_ACTION_NULL,
   ACL_PERMIT,
   ACL_DENY,
};

// TCP flags used in acl_rule_ip_t to specify which TCP flags the
// filter rule should match on.
enum acl_tcp_flag_t {
   ACL_TCP_NULL = 0,
   ACL_TCP_FIN = 1,
   ACL_TCP_SYN = 2,
   ACL_TCP_RST = 4,
   ACL_TCP_PSH = 8,
   ACL_TCP_ACK = 16,
   ACL_TCP_URG = 32,
};

// A TTL specifier, used in an IP ACL rule to define a range of
// IP TTL values that the filter rule must match.

// Normally, one creates an instance of the classes below,
// such as a acl_ttl_spec_gt_t to specify matching TTLs
// greater than the value passed.

class EOS_SDK_PUBLIC acl_ttl_spec_t {
 public:
   acl_ttl_spec_t();  // Default TTL spec; matches any TTL

   acl_range_operator_t oper() const;
   uint8_t ttl() const;

 protected:
   acl_range_operator_t oper_;  // BETWEEN is not supported.
   uint8_t ttl_;
   friend class acl_internal;
};

// Matches an exact TTL
class EOS_SDK_PUBLIC acl_ttl_spec_eq_t : public acl_ttl_spec_t {
 public:
   explicit acl_ttl_spec_eq_t(uint8_t ttl);
   friend class acl_internal;
};

// Matches all TTLs except this one
class EOS_SDK_PUBLIC acl_ttl_spec_neq_t : public acl_ttl_spec_t {
 public:
   explicit acl_ttl_spec_neq_t(uint8_t ttl);
   friend class acl_internal;
};

// Matches TTLs greater than this
class EOS_SDK_PUBLIC acl_ttl_spec_gt_t : public acl_ttl_spec_t {
 public:
   explicit acl_ttl_spec_gt_t(uint8_t ttl);
   friend class acl_internal;
};

// Matches TTLs less than this
class EOS_SDK_PUBLIC acl_ttl_spec_lt_t : public acl_ttl_spec_t {
 public:
   explicit acl_ttl_spec_lt_t(uint8_t ttl);
   friend class acl_internal;
};

// Matches any TTL value
class EOS_SDK_PUBLIC acl_ttl_spec_any_t : public acl_ttl_spec_t {
 public:
   explicit acl_ttl_spec_any_t();
   friend class acl_internal;
};

// Defines a UDP/TCP port specifier.
// Pick one of either:
// - acl_port_spec_eq_t : Matches 1-10 port numbers
// - acl_port_spec_neq_t : Doesn't match these 1-10 ports
// - acl_port_spec_lt_t : Matches ports less than the value
// - acl_port_spec_gt_t : Matches ports greater than the value
// - acl_port_spec_between_t : Matches ports between the two values

class EOS_SDK_PUBLIC acl_port_spec_t {
 public:
   acl_port_spec_t();  // Default port spec; matches any port
   acl_range_operator_t oper() const;

 protected:
   acl_range_operator_t oper_;
   std::list<uint16_t> ports_;

   friend class acl_internal;
};

// Matches one or more ports exactly
class EOS_SDK_PUBLIC acl_port_spec_eq_t : public acl_port_spec_t {
 public:
   explicit acl_port_spec_eq_t(uint16_t port);
   explicit acl_port_spec_eq_t(std::list<uint16_t> ports);
   friend class acl_internal;
};

// Matches every port except these one or more ports
class EOS_SDK_PUBLIC acl_port_spec_neq_t : public acl_port_spec_t {
 public:
   explicit acl_port_spec_neq_t(uint16_t port);
   explicit acl_port_spec_neq_t(std::list<uint16_t> ports);

   friend class acl_internal;
};

// Matches ports between low and high
class EOS_SDK_PUBLIC acl_port_spec_between_t : public acl_port_spec_t {
 public:
   acl_port_spec_between_t(uint16_t low, uint16_t high);
   friend class acl_internal;
};

// Matches ports greater than this
class EOS_SDK_PUBLIC acl_port_spec_gt_t : public acl_port_spec_t {
 public:
   explicit acl_port_spec_gt_t(uint16_t port);
   friend class acl_internal;
};

// Matches ports less than this
class EOS_SDK_PUBLIC acl_port_spec_lt_t : public acl_port_spec_t {
 public:
   explicit acl_port_spec_lt_t(uint16_t port);
   friend class acl_internal;
};

// Matches any port number
class EOS_SDK_PUBLIC acl_port_spec_any_t : public acl_port_spec_t {
 public:
   explicit acl_port_spec_any_t();
   friend class acl_internal;
};

// An ACL key is the combination of its name and ACL type (IPv4, IPv6 or ETH)
class EOS_SDK_PUBLIC acl_key_t {
 public:
   acl_key_t();
   acl_key_t(std::string const & acl_name, acl_type_t acl_type);

   std::string const acl_name() const;
   acl_type_t acl_type() const;

   bool operator() (acl_key_t const &, acl_key_t const &) const;

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

// Abstract ACL rule class. Instead of this, instantiate one of the
// concrete rule classes.

class EOS_SDK_PUBLIC acl_rule_base_t {
 public:
   acl_action_t action;
   bool log;
   bool tracked;

 protected:
   acl_rule_base_t() EOS_SDK_PRIVATE;
};

// An individual ACL rule for IPv4 or IPv6 ACLs
class EOS_SDK_PUBLIC acl_rule_ip_t : public acl_rule_base_t {
 public:
   acl_rule_ip_t();

   uint16_t vlan;
   uint16_t vlan_mask;
   uint16_t inner_vlan;
   uint16_t inner_vlan_mask;

   uint8_t ip_protocol;

   acl_ttl_spec_t ttl;

   ip_addr_mask_t source_addr;
   ip_addr_mask_t destination_addr;

   acl_port_spec_t source_port;
   acl_port_spec_t destination_port;

   // Bitmask of TCP flags to match, if set
   int tcp_flags;
   // Match "established" connections
   bool established;

   // Match a specific ICMP type and code
   // The default value 0xFFFF matches all types or codes
   uint16_t icmp_type;
   uint16_t icmp_code;

   uint8_t priority_value; // 0..63, DSCP match to value (IPv4); traffic class (IPv6)
   uint8_t priority_mask;  // supported for IPv6 only
   bool match_fragments;   // match IP fragments?
   // Match DSCP (IPv4) or TE (IPv6) data provided in priority_{value,mask}
   bool match_ip_priority;
};

// An Ethernet ACL, which can be applied to Ethernet, Vlan, and MLAG interfaces.
class EOS_SDK_PUBLIC acl_rule_eth_t : public acl_rule_base_t {
 public:
   acl_rule_eth_t();

   uint16_t vlan;
   uint16_t vlan_mask;
   uint16_t inner_vlan;
   uint16_t inner_vlan_mask;

   eth_addr_t source_addr;
   eth_addr_t source_mask;
   eth_addr_t destination_addr;
   eth_addr_t destination_mask;
};

// An ACL handler is the class users should derive from if they wish
// to react to ACL hardware synchronisation events.
class EOS_SDK_PUBLIC acl_handler {
 public:
   acl_handler();
   virtual ~acl_handler();

   // Call this method to receive notifications (on_acl_* function
   // calls) for all ACLs configured on the system. Setting this to
   // false will stop your acl_handler subclass receiving
   // notifications. Defaults to false.
   void watch_all_acls(bool interest);

   // Called when all pending transactions have been successfully
   // committed into hardware.  It may be called more than once for a
   // single transaction, or only once for a whole bunch of separate
   // ACL updates. In fact, if someone updates an ACL in the CLI, this
   // function may get called, i.e., it can get called once for zero
   // transactions.
   virtual void on_acl_sync();

   // Called when we notice a problem keeping the ACL configuration
   // from being committed into hardware. It indicates that the ACL
   // config (as stored in Sysdb) cannot be loaded into hardware,
   // ever. It must be changed in some way to get Sysdb and the
   // hardware back in sync. The most common problem, of course, is
   // too many ACLs or ACL entries. It is up to you to find some
   // things to delete, commit those deletions, and then see if things
   // fit once again (on_acl_sync() will get called if they do, or
   // on_acl_sync_fail() will get called again if they don't). Note
   // you may be notified more than once of the same problem, and you
   // may be notified of problems that have nothing to do with you,
   // such as an operator at the CLI doing something unsupported.
   virtual void on_acl_sync_fail(std::string const & linecard,
                                 std::string const & message);

  private:
   bool watching_all_acls_;
};

// The ACL manager provides access to current ACL configuration,
// creation, modification and deletion of ACLs, and functions to
// commit changes, apply ACLs to interfaces as well as manage
// fragements mode and enabling counters.
class EOS_SDK_PUBLIC acl_mgr {
 public:
   typedef bool (*acl_cb)(acl_key_t const &, void * context);
   typedef bool (*acl_rule_ip_cb)(int seq,
                                  acl_rule_ip_t const &,
                                  void * context);
   typedef bool (*acl_rule_eth_cb)(int seq,
                                   acl_rule_eth_t const &,
                                   void * context);

   void acl_foreach(acl_cb handler, void * context);
   void acl_foreach(acl_cb handler, void * context, acl_key_t bookmark);

   // Iterates over the rules within an ACL. Provide a callback function matching
   // the acl_rule_cb_* function definitions above.
   void acl_rule_eth_foreach(acl_key_t const &, acl_rule_eth_cb, void * context);
   void acl_rule_ip_foreach(acl_key_t const &, acl_rule_ip_cb, void * context);

   // ACL management
   //
   // Returns true if an ACL with the same name and type (i.e., key)
   // exists in the configuration.
   bool acl_exists(acl_key_t const &) const;

   // Add and remove ACL rules of a particular type. If the ACL
   // doesn't exist, it will be created before the rule is added to
   // it. There's no explicit ACL add operation.
   //
   // You give an ACL key to modify, a "sequence number" which starts
   // at 1 and goes up to MAXINT, and for set operations, the rule to
   // set. Note: you must call commit() for your changes here to get
   // pushed into the hardware, and once you have started setting
   // rules, you must call acl_commit() prior to any calls to
   // acl_apply(), else the manager will panic(). Note that extremely
   // large numbers of ACLs or rules per ACL can result in undefined
   // behaviour, including a switch reload.
   void acl_rule_set(acl_key_t const &, int, acl_rule_ip_t const &);
   void acl_rule_set(acl_key_t const &, int, acl_rule_eth_t const &);
   // Removes the rule for sequence number from the ACL
   void acl_rule_delete(acl_key_t const &, int);

   // Commits all rule changes and application changes made above, to
   // all ACLs, pushing them into Sysdb's active configuration. This
   // commit cannot fail, but it can lead to a state where not all
   // ACLs can be loaded into hardware. You will be notified via
   // on_acl_sync() when this commit and all other outstanding
   // operations (applications of any ACL to an interface) are loaded
   // into hardware, or on_acl_sync_fail() if the newly committed
   // configuration can't be loaded.  If there are no changes pending
   // and you call this function, you will get one of those callbacks
   // depending on whether the current state in Sysdb can be loaded
   // into hardware or not.
   void acl_commit();

   // Deletes the ACL.  Removes all rules and unapplies from all
   // interfaces. Any pending changes to the ACL are discarded.  Is
   // effective immediately (no commit or commit notification).
   void acl_delete(acl_key_t const &);

   // Request that an ACL be (un)applied on the given interface. ACL
   // is loaded into hardware asynchronously. Like commit(), this
   // function results in a call to your handler when we have applied,
   // or failed to apply, this ACL configuration. That is, you do not
   // get a handler callback per call; you get a handler callback when
   // everything is loaded into hardware, or when we notice problems.
   //
   // API call ordering note: any acl_rule_set() or acl_rule_delete()
   // calls be followed by an acl_commit() prior to calling this
   // function else a panic() will occur.
   void acl_apply(acl_key_t const &, intf_id_t, acl_direction_t, bool);

   // Immediately enable or disable counters for the ACL.
   void acl_counters_enabled_set(acl_key_t const &, bool);

   // Immediately enable or disable fragments matching on the ACL
   void acl_fragments_enabled_set(acl_key_t const &, bool);

 protected:
   acl_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(acl_mgr);
};

acl_mgr * get_acl_mgr() EOS_SDK_PUBLIC;

}  // namespace eos

#include <eos/inline/acl.h>

#endif // EOS_ACL_H
