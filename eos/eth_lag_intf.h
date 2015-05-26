/**
 * @file
 * The eth_lag_intf module manages link aggregation groups (LAGs), also known as
 * Port Channels.
 *
 * LAGs bundle physical interfaces together into a single logical link to provide
 * combined bandwidth and other benefits. This module provides APIs to provision
 * LAG interfaces. APIs include LAG creation, deletion, retrieval,  member interface
 * adding to or removal from LAG interfaces. Two iterators are also provided to
 * allow iteration through all the LAG interfaces and also all the member interfaces
 * that are configured on the system.
 */


// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ETH_LAG_INTF_H
#define EOS_ETH_LAG_INTF_H

#include <string>

#include <eos/intf.h>
#include <eos/iterator.h>

#include <eos/types/eth_lag_intf.h>

namespace eos {

class eth_lag_intf_mgr;
class eth_lag_intf_iter_impl;
class eth_lag_intf_member_iter_impl;

/**
 * The handler for LAG interface events.
 */

class EOS_SDK_PUBLIC eth_lag_intf_handler : public base_handler<
   eth_lag_intf_mgr, eth_lag_intf_handler> {
 public:
   explicit eth_lag_intf_handler(eth_lag_intf_mgr *);
   virtual ~eth_lag_intf_handler();
   eth_lag_intf_mgr * get_eth_lag_intf_mgr() const;

   /**
    * Registers this class to receive change updates on all interfaces.
    *
    * Expects a boolean signifying whether notifications should be
    * enabled on all interfaces and propogated to this instance.
    */
   void watch_all_eth_lag_intfs(bool);

   /**
    * Registers this class to receive change updates on the given interface.
    *
    * Expects the ID of the corresponding LAG interface and a boolean
    * signifying whether notifications should be propagated to this
    * instance or not.
    */
   void watch_eth_lag_intf(intf_id_t, bool);

   /**
    * Handler called when a LAG ethernet interface is created.
    *
    * After on_eth_lag_intf_create is called, the given intf_id is
    * guaranteed to exist (ie eth_lag_intf_mgr::exists will return
    * true). At that point, the intf_id can be used will all methods
    * of the eth_lag_intf_mgr class.
    *
    * This also means that the intf_id can be used with all other
    * relevant *intf_mgr classes (ie intf_mgr and eth_intf_mgr).
    */
   virtual void on_eth_lag_intf_create(intf_id_t);
   
   /**
    * Handler called when a LAG ethernet interface is deleted.
    *
    * After on_eth_lag_intf_delete is called, the given intf_id is
    * guaranteed to not exist (ie eth_lag_intf_mgr::exists will return
    * false). At that point, the intf_id cannot be used will any
    * methods in the eth_lag_intf_mgr class, with the exception of
    * methods used to create new LAG interfaces.
    *
    * This also means that the intf_id can no longer be used with all
    * other relevant *intf_mgr classes (ie intf_mgr and eth_intf_mgr).
    */
   virtual void on_eth_lag_intf_delete(intf_id_t);
   
   /**
    * Handler called when a member interface is added to a watched LAG.
    */
   virtual void on_lag_member_set(intf_id_t lag, intf_id_t member);

   /**
    * Handler called when a member interface is removed from a watched LAG.
    */
   virtual void on_lag_member_del(intf_id_t lag, intf_id_t member);

   /**
    * Handler called when a LAG interface's speed changes
    */
   virtual void on_lag_intf_speed(intf_id_t lag, uint64_t speed);
};

/**
 * An LAG interface iterator for iterating through all LAG interfaces
 * created in the system.
 */
class EOS_SDK_PUBLIC eth_lag_intf_iter_t : public iter_base< intf_id_t,
                                                  eth_lag_intf_iter_impl> {
 private:
   friend class eth_lag_intf_iter_impl;
   explicit eth_lag_intf_iter_t(eth_lag_intf_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * An LAG member iterator for iterating through all interfaces configured as a
 * member of one LAG interface in the system.
 */
class EOS_SDK_PUBLIC eth_lag_intf_member_iter_t : public iter_base< intf_id_t,
                                                  eth_lag_intf_member_iter_impl> {
 private:
   friend class eth_lag_intf_member_iter_impl;
   explicit eth_lag_intf_member_iter_t(
                         eth_lag_intf_member_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * The manager for LAG interfaces. This is the main entry point for applications
 * to use EosSdk LAG APIs.
 */
class EOS_SDK_PUBLIC eth_lag_intf_mgr
   : public base_mgr<eth_lag_intf_handler, intf_id_t> {
 public:
   virtual ~eth_lag_intf_mgr();

   /**
    * Iterates through the LAG interfaces in system. An intf_id_t pointer is returned
    * for each LAG interface.
    */
   virtual eth_lag_intf_iter_t eth_lag_intf_iter() const = 0;

   /**
    * Returns whether the given ethernet LAG interface exists.
    *
    * If exists returns true, then this intf_id_t can be successfully
    * passed into every method of the eth_lag_intf_mgr. If not, then
    * methods of the eth_lag_intf_mgr can throw a no_such_interface_error
    * exception, or return empty data like intf_id_t().
    *
    * The exists method of all *intf_mgr classes that manage a given
    * interface (ie intf_mgr, eth_intf_mgr, and eth_lag_intf_mgr for
    * LAG interfaces) are all guaranteed to return the same result.
    */
   virtual bool exists(intf_id_t) const = 0;
   
   /**
    * Iterates over physical interfaces configured as a member of any
    * LAG interface in system. Note the interface may not be in a LAG
    * interface yet, but still shows up if its priority/mode/timeout
    * set. Yields an intf_id_t for each member.
    */
   virtual eth_lag_intf_member_iter_t eth_lag_intf_member_iter() const = 0;

   /**
    * Iterates over physical interfaces configured as members of a
    * given LAG interface. Yields an intf_id_t for each member.
    */
   virtual eth_lag_intf_member_iter_t eth_lag_intf_member_iter(
         intf_id_t eth_lag_intf_id) const = 0;

   /**
    * Creates a LAG interface, when given the LAG interface. No action will
    * be taken if the LAG exists already.
    */
   virtual void eth_lag_intf_is(intf_id_t eth_lag_intf_id) = 0;

   /**
    * Returns a LAG interface with the specified LAG interface. Will return
    * an empty eth_lag_intf_t if the LAG does not exist already.
    */
   virtual eth_lag_intf_t eth_lag_intf(intf_id_t eth_lag_intf_id) const = 0;

   /**
    * This API deletes a LAG interface. It is a no-op if the specified LAG 
    * interface doesn't exist.
    */
   virtual void eth_lag_intf_del(intf_id_t eth_lag_intf_id) = 0;

   /**
    * Returns the speed of a LAG interface in megabits. If the interface does not
    * exist, 0 is returned.
    */
   virtual uint64_t speed(intf_id_t eth_lag_intf_id) const = 0;

   /**
    * Sets the min links for a LAG interface. It's a no-op if the specified
    * LAG interface does not exist.
    */
   virtual void min_links_is(intf_id_t eth_lag_intf_id, uint32_t min_links) = 0;

   /**
    * Returns the minimum number of member interfaces required to be 
    * `OPER_STATUS_UP` before this LAG interface considered `OPER_STATUS_UP`.
    * If the LAG interface does not exist, 0 will be returned.
    */
   virtual uint32_t min_links(intf_id_t eth_lag_intf_id) const = 0;

   /**
    * Sets the fallback type for a LAG interface. It's a no-op if the LAG
    * interface does not exist. Throws "invalid_argument_error" exception if
    * invalid fallback type is passed in.
    */
   virtual void fallback_type_is(intf_id_t eth_lag_intf_id,
                                 eth_lag_intf_fallback_type_t fallback_type) = 0;

   /**
    * Returns the fallback mode for a LAG interface. ETH_LAG_INTF_FALLBACK_NULL is
    * returned if the LAG interface does not exist.
    */
   virtual eth_lag_intf_fallback_type_t fallback_type(
                                            intf_id_t eth_lag_intf_id) const = 0;
   /**
    * Sets the fallback timeout for a LAG interface. It's a no-op if the LAG
    * interface does not exist.
    */
   virtual void fallback_timeout_is(intf_id_t eth_lag_intf_id,
                                    uint16_t fallback_timeout) = 0;
   /**
    * Returns the LACP active mode timeout value in seconds. 0 is returned if
    * the LAG interface does not exist.
    */
   virtual uint16_t fallback_timeout(intf_id_t eth_lag_intf_id) const = 0;

   /**
    * Returns the default fallback timeout value in seconds.
    * */
   virtual uint16_t fallback_timeout_default(intf_id_t eth_lag_intf_id) const = 0;

   /**
    * Adds a physical interface to a LAG interface.
    *
    * This API may throw "Invalid_argument_error" exception if the interface's
    * mode is not compatible with the LAG interface mode or the LAG interface's 
    * type is INTF_TYPE_NULL.
    */
   virtual void membership_set(intf_id_t member_intf_id,
                               intf_id_t eth_lag_intf_id,
                               eth_lag_intf_member_lacp_mode_t mode) = 0;
   
   /** 
    * Removes an interface from a LAG interface.
    *
    * This API returns directly if the interface is invalid or not in a LAG.
    */
   virtual void membership_del(intf_id_t member_intf_id) = 0;
   
   
   /**
    * Returns the LAG interface ID to which the physical interface is configured
    * to belong. An empty intf_id_t is returned if the physical interface is not
    * configured or is not in a LAG.
    */
   virtual intf_id_t membership(intf_id_t member_intf_id) const = 0;

   /**
    * Returns the member interface's status details. Will return empty
    * eth_lag_intf_membership_t if the physical interface is not configured,
    * or it's not active in a LAG.
    */
   virtual eth_lag_intf_membership_t 
      membership_status(intf_id_t member_intf_id) const = 0;

   /**
    * Sets the port LACP priority.
    */
   virtual void member_priority_is(intf_id_t member_intf_id, uint16_t priority) = 0;

   /**
    * Gets the interface's configured LACP priority. 0 will be returned if the
    * member interface is not existing.
    */
   virtual uint16_t member_priority(intf_id_t member_intf_id) const = 0;

   /**
    * Sets the mode of this member in a LAG interface.
    */
   virtual void member_mode_is(intf_id_t member_intf_id,
                               eth_lag_intf_member_lacp_mode_t mode) = 0;

   /**
    * Returns the mode of this member in a LAG interface. If the member interface
    * is not existing, ETH_LAG_INTF_MEMBER_LACP_MODE_NULL is returned.
    */
   virtual eth_lag_intf_member_lacp_mode_t 
      member_mode(intf_id_t member_intf_id) const = 0;

   /**
    * Sets the LACP timeout for a member in a LAG.
    */
   virtual void member_timeout_is(intf_id_t member_intf_id,
                                  eth_lag_intf_member_lacp_timeout_t timeout) = 0;

   /**
    * Gets the configured LACP timeout for a member in a LAG. If the member interface
    * does not exist, ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_NULL will be returned.
    */
   virtual eth_lag_intf_member_lacp_timeout_t
      member_timeout(intf_id_t member_intf_id) const = 0;

   /**
    * Returns whether this interface is active in a LAG. False is returned if the
    * member interface does not exist.
    */
   virtual bool member_active(intf_id_t member_intf_id) const = 0;

   /**
    * Returns the time in seconds since reboot when this interface was last added 
    * or removed as a member from a  LAG. If this interface has never been a LAG 
    * member, this returns 0.
    */
   virtual double member_time(intf_id_t member_intf_id) const = 0;

   /**
    * Returns the reason this interface isn't active in LAG. Returns the empty
    * string if the interface is not configured to be in any LAG, or if the
    * interface is active in the LAg.
    */
   virtual std::string member_reason(intf_id_t member_intf_id) const = 0;


   /// @deprecated Please use the more succinctly named 'membership_status' instead.
   virtual eth_lag_intf_membership_t
      eth_lag_intf_membership_status(intf_id_t member_intf_id) const = 0;

   /// @deprecated Please use member_timeout_is() instead.
   virtual void eth_lag_intf_member_timeout_is(intf_id_t member_intf_id,
                                  eth_lag_intf_member_lacp_timeout_t timeout) = 0;

   /// @deprecated Please use member_priority_is() instead.
   virtual void
   eth_lag_intf_member_priority_is(intf_id_t member_intf_id, uint16_t priority) = 0;

   /// @deprecated Please use member_mode_is() instead.
   virtual void eth_lag_intf_member_mode_is(intf_id_t member_intf_id,
                                           eth_lag_intf_member_lacp_mode_t mode) = 0;

 protected:
   eth_lag_intf_mgr() EOS_SDK_PRIVATE;
   friend class eth_lag_intf_handler;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(eth_lag_intf_mgr);
};

} // end namespace eos

#include <eos/inline/eth_lag_intf.h>

#endif // EOS_ETH_LAG_INTF_H
