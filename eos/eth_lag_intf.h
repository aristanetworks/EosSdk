// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ETH_LAG_INTF_H
#define EOS_ETH_LAG_INTF_H

#include <string>

#include <eos/intf.h>
#include <eos/iterator.h>

namespace eos {

/// Eth Lag interface fallback type
enum eth_lag_intf_fallback_type_t {
   ETH_LAG_INTF_FALLBACK_NULL,
   ETH_LAG_INTF_FALLBACK_NONE,
   ETH_LAG_INTF_FALLBACK_STATIC,
   ETH_LAG_INTF_FALLBACK_INDIVIDUAL,
};

enum eth_lag_intf_fallback_timeout_default_t {
   ETH_LAG_INTF_FALLBACK_TIMEOUT_DEFAULT = 90,
};

enum eth_lag_intf_member_priority_t {
   ETH_LAG_INTF_PORT_PRIORITY_DEFAULT = 0x8000,
};

/// Lag member LACP mode
enum eth_lag_intf_member_lacp_mode_t {
   ETH_LAG_INTF_MEMBER_LACP_MODE_NULL,
   ETH_LAG_INTF_MEMBER_LACP_MODE_OFF,
   ETH_LAG_INTF_MEMBER_LACP_MODE_PASSIVE,
   ETH_LAG_INTF_MEMBER_LACP_MODE_ACTIVE,
};

/// Individual member (link) timeout values
enum eth_lag_intf_member_lacp_timeout_t {
   ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_NULL,
   ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_SHORT,
   ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_LONG,
};

/**
 * This data structure defines an Eth Lag interface, which is also known as LAG,
 * Link-Aggregation Group. LAGs bundle physical interfaces together into a single
 * logical link to provide combined bandwidth and other benefits.
 */
class EOS_SDK_PUBLIC eth_lag_intf_t {
 public:
   eth_lag_intf_t();
   eth_lag_intf_t(intf_id_t);

   bool operator==(eth_lag_intf_t const & other) const;
   bool operator!=(eth_lag_intf_t const & other) const;

   // Sets the eth Lag intf
   void eth_lag_intf_id_is(intf_id_t id);
   // Returns eth Lag intf id
   intf_id_t eth_lag_intf_id() const;
   /// Returns the aggregated capabity (speed) of this Eth Lag interface in megabits
   double speed() const;
   /// Sets the aggregated capabity (speed) of this Eth Lag interface in megabits
   void speed_is(double s);
   /// Returns the min links required up before bringing up an Eth Lag interface.
   uint32_t min_links() const;
   /// Configures the min links required up before bringing up an Eth Lag interface.
   void min_links_is(uint32_t min_links);
   /**
    * Returns the fallback mode currently configured, it will be one of following:
    * none, static LAG mode or individual ports.
    */
   eth_lag_intf_fallback_type_t fallback_type() const;
   /// Configures the fallback mode for this Eth Lag interface.
   void fallback_type_is(eth_lag_intf_fallback_type_t type);
   /// Returns the default LACP active mode timeout value, now it's 90
   uint16_t fallback_timeout_default() const;
   /// Configures the LACP active mode timeout value. 
   void fallback_timeout_is(uint16_t timeout);
   /// Returns the configured LACP active mode timeout value. 
   uint16_t fallback_timeout() const;

 private:
   intf_id_t intf_;
   double speed_;
   uint32_t min_links_;
   eth_lag_intf_fallback_type_t fallback_type_;
   uint16_t fallback_timeout_;
};

/**
 * This data structure is used to describe the operational status
 * of an intf configured in an Eth Lag interface.
 */
class EOS_SDK_PUBLIC eth_lag_intf_membership_t {
 public:
   eth_lag_intf_membership_t();

   /// The Eth Lag interface id this intf is configured to be in.
   intf_id_t eth_lag_intf_id;
   /// This attribute indicates whether this intf is active in a Lag
   bool active;
   /// If not empty, reason this intf isn't in LAG
   std::string reason;
   /**
    * The time when this intf became member of a LAG. If never a member,
    * then the value is 0; if once was member, but now isn't, then this
    * is the time the intf was removed from member.
    */
   double memberTime;
   /// This intf LACP mode
   eth_lag_intf_member_lacp_mode_t mode;
};

class eth_lag_intf_iter_impl;
class eth_lag_intf_member_iter_impl;


/**
 * An Eth Lag interface iterator iterating through all Eth Lag interfaces
 * created in the system.
 */
class EOS_SDK_PUBLIC eth_lag_intf_iter_t : public iter_base< intf_id_t,
                                                  eth_lag_intf_iter_impl> {
 private:
   friend class eth_lag_intf_iter_impl;
   explicit eth_lag_intf_iter_t(eth_lag_intf_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * A Lag member iterator iterating through all interfaces configured as a
 * member of one Lag interface in the system.
 */
class EOS_SDK_PUBLIC eth_lag_intf_member_iter_t : public iter_base< intf_id_t,
                                                  eth_lag_intf_member_iter_impl> {
 private:
   friend class eth_lag_intf_member_iter_impl;
   explicit eth_lag_intf_member_iter_t(
                         eth_lag_intf_member_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * The manager for Lag interface, this is the main entry point for applications
 * to use EosSdk Lag APIs.
 */
class EOS_SDK_PUBLIC eth_lag_intf_mgr {
 public:
   virtual ~eth_lag_intf_mgr();

   /**
    * Iterate the Lag interfaces in system, intf_id_t pointer is returned for
    * each Lag interface.
    */
   virtual eth_lag_intf_iter_t eth_lag_intf_iter() const = 0;
   /**
    * Iterate the physical interfaces configured as a member of an Eth Lag interface 
    * in system, note the interface may not be in a Lag interface yet, but still
    * shows up if its priority/mode/timeout set.
    * "intf_id_t *" is returned for each member intf.
    */
   virtual eth_lag_intf_member_iter_t eth_lag_intf_member_iter() const = 0;
   /**
    * This API creates an Eth Lag interface, when given the Lag id. It may throw
    * "invalid_argument_error" exception if the Lag exists already.
    */
   virtual eth_lag_intf_t eth_lag_intf_is(intf_id_t eth_lag_intf_id) = 0;
   /**
    * This API returns a Lag interface with the specified Lag id. May throw
    * "invalid_argument_error" exception if the Lag does not exist already.
    */
   virtual eth_lag_intf_t eth_lag_intf(intf_id_t eth_lag_intf_id) = 0;
   /**
    * This API deletes a Lag interface, it will simply return if the specified
    * Lag interface is not in existance.
    */
   virtual void eth_lag_intf_del( intf_id_t eth_lag_intf_id) = 0;
   /**
    * This API adds/removes one eth intf to/from a Lag interface.
    * To add an interface, the interface id and its LACP mode are needed.
    * To remove an interface from a Lag interface, the "intf" needs to be
    * provided, and eth_lag_intf_id needs to be the empty intf with
    * intf_type()==INTF_TYPE_NULL (created by intf_id_t()).
    *
    * When removing an interface from a Lag interface, this API may throw 
    * "no_such_interface_error" exception if the specified Lag interface does
    * not exist. It may also throw "invalid_argument_error" exception if the
    * specified "intf" is not in any Lag interface.
    *
    * When adding an interface to a Lag interface, this API may throw "Invalid_
    * argument_error" error if the interface's mode is not compatible with
    * the Lag interface mode.
    */
   virtual void membership_set(intf_id_t intf,
                               intf_id_t eth_lag_intf_id,
                               eth_lag_intf_member_lacp_mode_t mode) = 0;
   /**
    * This API returns the Lag interface id to which the physical intf is
    * configured to belong.
    * May throw "no_such_interface_error" if the "intf" does not exist.
    */
   virtual intf_id_t membership(intf_id_t intf) = 0;
   /**
    * This API returns the member intf operational status.
    * It may throw "no_such_interface_error" if the specified "intf" does not
    * exist.
    */
   virtual eth_lag_intf_membership_t
                         eth_lag_intf_membership_status(intf_id_t intf) = 0;

   /// This API sets the port LACP priority 
   virtual void eth_lag_intf_member_priority_is(intf_id_t intf,
                               uint16_t priority) = 0;
   /// This API sets the mode of this member in a Lag interface.
   virtual void eth_lag_intf_member_mode_is(intf_id_t intf,
                               eth_lag_intf_member_lacp_mode_t mode) = 0;
   /**
    * This API sets the LACP timeout for this member, the valid values are "short"
    * or "long".
    * It may throw "invalid_argument_error" exception, if the "timeout" value
    * is invalid.
    */
   virtual void eth_lag_intf_member_timeout_is(intf_id_t intf,
                               eth_lag_intf_member_lacp_timeout_t timeout) = 0;

 protected:
   eth_lag_intf_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(eth_lag_intf_mgr);
};

} // end namespace eos

#include <eos/inline/eth_lag_intf.h>

#endif // EOS_ETH_LAG_INTF_H
