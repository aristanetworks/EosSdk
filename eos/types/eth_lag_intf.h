// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_ETH_LAG_INTF_H
#define EOS_TYPES_ETH_LAG_INTF_H

#include <eos/hash_mix.h>
#include <eos/intf.h>
#include <eos/utility.h>
#include <sstream>

namespace eos {

/** LAG interface fallback type. */
enum eth_lag_intf_fallback_type_t {
   /** Not a valid fallback type. */
   ETH_LAG_INTF_FALLBACK_NULL,
   /** No fallback if no LACPDUs seen. */
   ETH_LAG_INTF_FALLBACK_NONE,
   /** Fallback to static mode. */
   ETH_LAG_INTF_FALLBACK_STATIC,
   /** Fallback to individual mode. */
   ETH_LAG_INTF_FALLBACK_INDIVIDUAL,
};


/** How long to wait for LACP before fallback. */
enum eth_lag_intf_fallback_timeout_default_t {
   ETH_LAG_INTF_FALLBACK_TIMEOUT_DEFAULT = 90,
};


enum eth_lag_intf_member_priority_t {
   ETH_LAG_INTF_PORT_PRIORITY_DEFAULT = 0x8000,
};


/** LAG interface mebmer LACP mode. */
enum eth_lag_intf_member_lacp_mode_t {
   ETH_LAG_INTF_MEMBER_LACP_MODE_NULL,
   ETH_LAG_INTF_MEMBER_LACP_MODE_OFF,
   ETH_LAG_INTF_MEMBER_LACP_MODE_PASSIVE,
   ETH_LAG_INTF_MEMBER_LACP_MODE_ACTIVE,
};


/** LAG interface mebmer timeout values. */
enum eth_lag_intf_member_lacp_timeout_t {
   ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_NULL,
   ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_SHORT,
   ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_LONG,
};


/**
 * This data structure is used to describe the operational status
 * of an interface configured in an LAG interface.
 */
class EOS_SDK_PUBLIC eth_lag_intf_membership_t {
 public:
   eth_lag_intf_membership_t();

   /**
    * Getter for 'eth_lag_intf_id': the LAG interface id this interface is
    * configured to be in.
    */
   intf_id_t eth_lag_intf_id() const;
   /** Setter for 'eth_lag_intf_id'. */
   void eth_lag_intf_id_is(intf_id_t eth_lag_intf_id);

   /**
    * Getter for 'active': the attribute indicating whether this interface is
    * active in an LAG.
    */
   bool active() const;
   /** Setter for 'active'. */
   void active_is(bool active);

   /** Getter for 'reason': if populated, reason this interface isn't in LAG. */
   std::string reason() const;
   /** Setter for 'reason'. */
   void reason_is(std::string const & reason);

   /**
    * Getter for 'member_time': the time when this interface became member of an
    * LAG. If never a member, then the value is 0; if once was member, but now is
    * not, then this is the time the interface was removed from member.
    */
   double member_time() const;
   /** Setter for 'member_time'. */
   void member_time_is(double member_time);

   /** Getter for 'mode': the LACP mode this interface is configured. */
   eth_lag_intf_member_lacp_mode_t mode() const;
   /** Setter for 'mode'. */
   void mode_is(eth_lag_intf_member_lacp_mode_t mode);

   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * eth_lag_intf_membership_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, 
                                   const eth_lag_intf_membership_t& obj);

 private:
   intf_id_t eth_lag_intf_id_;
   bool active_;
   std::string reason_;
   double member_time_;
   eth_lag_intf_member_lacp_mode_t mode_;
};


/**
 * This data structure defines a LAG interface, which is also known
 * as a Link-Aggregation Group, or Port-Channel. LAGs bundle
 * physical interfaces together into a single logical link to
 * provide combined bandwidth and other benefits.
 */
class EOS_SDK_PUBLIC eth_lag_intf_t {
 public:
   eth_lag_intf_t();
   /** Constructor with interface id. */
   explicit eth_lag_intf_t(intf_id_t intf);

   /** Getter for 'intf': the id of this LAG interface. */
   intf_id_t intf() const;
   /** Setter for 'intf'. */
   void intf_is(intf_id_t intf);

   /**
    * Getter for 'speed': the aggregated capacity (speed) of this LAG interface in
    * megabits.
    */
   double speed() const;
   /** Setter for 'speed'. */
   void speed_is(double speed);

   /**
    * Getter for 'min_links': the min links required up before bringing up an LAG
    * interface.
    */
   uint32_t min_links() const;
   /** Setter for 'min_links'. */
   void min_links_is(uint32_t min_links);

   /** Getter for 'fallback_type': the fallback mode for this LAG interface. */
   eth_lag_intf_fallback_type_t fallback_type() const;
   /** Setter for 'fallback_type'. */
   void fallback_type_is(eth_lag_intf_fallback_type_t fallback_type);

   /**
    * Getter for 'fallback_timeout': the LACP active mode timeout value in seconds.
    */
   uint16_t fallback_timeout() const;
   /** Setter for 'fallback_timeout'. */
   void fallback_timeout_is(uint16_t fallback_timeout);

   /** Returns the default fallback timeout value in seconds. */
   uint16_t fallback_timeout_default() const;

   bool operator==(eth_lag_intf_t const & other) const;
   bool operator!=(eth_lag_intf_t const & other) const;
   /** The hash function for type eth_lag_intf_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of eth_lag_intf_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const eth_lag_intf_t& obj);

 private:
   intf_id_t intf_;
   double speed_;
   uint32_t min_links_;
   eth_lag_intf_fallback_type_t fallback_type_;
   uint16_t fallback_timeout_;
};

}

#include <eos/inline/types/eth_lag_intf.h>

#endif // EOS_TYPES_ETH_LAG_INTF_H
