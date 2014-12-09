// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ACL_H
#define EOS_ACL_H

#include <utility>

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/eth.h>
#include <eos/ip.h>
#include <eos/intf.h>

#include <eos/types/acl.h>

namespace eos {

class acl_mgr;

/**
 * An ACL handler.
 *
 * Derive from this class to react to ACL hardware synchronization events.
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
    * Called upon hardware successfully committing all pending transactions.
    *
    * It may be called more than once for a single transaction, or
    * only once for a whole bunch of separate ACL updates. In fact, if
    * someone updates an ACL in the CLI, this function may get called,
    * i.e., it can get called once for zero transactions.
    */
   virtual void on_acl_sync();

   /**
    * Called upon a problem stopping ACL configuration from being committed.
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
 * fragments mode and enabling counters.
 *
 * When managing ACLs, you provide give an ACL key to modify, a
 * "sequence number" which starts at 1 and goes up to MAXINT, and for
 * set operations, the rule to set. Note: you must call commit() for
 * your changes here to get pushed into the hardware, and once you
 * have started setting rules, you must call acl_commit() prior to any
 * calls to acl_apply(), else the manager will panic(). Note that
 * extremely large numbers of ACLs or rules per ACL can result in
 * undefined behavior, including a switch reload.
 */
class EOS_SDK_PUBLIC acl_mgr : public base_mgr<acl_handler> {
 public:
   virtual ~acl_mgr();

   /// Iterates over all ACLs.
   virtual acl_iter_t acl_iter() const = 0;

   /// Iterates over the rules with an IP ACL.
   virtual acl_rule_ip_iter_t acl_rule_ip_iter(acl_key_t const &) const = 0;

   /// Iterates over the rules with an Ethernet ACL.
   virtual acl_rule_eth_iter_t acl_rule_eth_iter(acl_key_t const &) const = 0;

   /**
    * Configuration ACL existence test.
    *
    * @return true if an ACL with the same name and type (i.e., key)
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
    * Removes all rules and removes the ACL from all
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
