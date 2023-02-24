// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_ETH_LAG_INTF_IMPL_H
#define EOS_TYPES_ETH_LAG_INTF_IMPL_H

#include <eos/hash_mix.h>
#include <eos/intf.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

/**
 * This data structure is used to describe the operational status
 * of an interface configured in an LAG interface.
 */
class EOS_SDK_PUBLIC eth_lag_intf_membership_impl_t {
 public:
   eth_lag_intf_membership_impl_t();
   /** Constructor with paremeters. */
   eth_lag_intf_membership_impl_t(intf_id_t eth_lag_intf_id, bool active,
                                  std::string const & reason, double member_time,
                                  eth_lag_intf_member_lacp_mode_t mode);

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

   /** Getter for 'mode': the LACP mode this interface is configured. */
   eth_lag_intf_member_lacp_mode_t mode() const;

   bool operator==(eth_lag_intf_membership_impl_t const & other) const;
   bool operator!=(eth_lag_intf_membership_impl_t const & other) const;
   bool operator<(eth_lag_intf_membership_impl_t const & other) const;
   /** The hash function for type eth_lag_intf_membership_t. */
   uint32_t hash() const;
   /** The hash mix function for type eth_lag_intf_membership_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * eth_lag_intf_membership_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const eth_lag_intf_membership_impl_t& obj);

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
class EOS_SDK_PUBLIC eth_lag_intf_impl_t {
 public:
   eth_lag_intf_impl_t();
   /** Constructor with interface id. */
   explicit eth_lag_intf_impl_t(intf_id_t intf);
   /** Constructor with interface id. */
   eth_lag_intf_impl_t(intf_id_t intf, uint32_t min_links, uint64_t speed,
                       eth_lag_intf_fallback_type_t fallback_type,
                       uint16_t fallback_timeout);

   /** Getter for 'intf': the id of this LAG interface. */
   intf_id_t intf() const;

   /**
    * Getter for 'speed': the aggregated capacity (speed) of this LAG interface in
    * megabits.
    */
   uint64_t speed() const;

   /**
    * Getter for 'min_links': the min links required up before bringing up an LAG
    * interface.
    */
   uint32_t min_links() const;

   /** Getter for 'fallback_type': the fallback mode for this LAG interface. */
   eth_lag_intf_fallback_type_t fallback_type() const;

   /**
    * Getter for 'fallback_timeout': the LACP active mode timeout value in seconds.
    */
   uint16_t fallback_timeout() const;

   /** Returns the default fallback timeout value in seconds. */
   uint16_t fallback_timeout_default() const;

   bool operator==(eth_lag_intf_impl_t const & other) const;
   bool operator!=(eth_lag_intf_impl_t const & other) const;
   bool operator<(eth_lag_intf_impl_t const & other) const;
   /** The hash function for type eth_lag_intf_t. */
   uint32_t hash() const;
   /** The hash mix function for type eth_lag_intf_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of eth_lag_intf_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const eth_lag_intf_impl_t& obj);

 private:
   intf_id_t intf_;
   uint64_t speed_;
   uint32_t min_links_;
   eth_lag_intf_fallback_type_t fallback_type_;
   uint16_t fallback_timeout_;
};
}

#endif // EOS_TYPES_ETH_LAG_INTF_IMPL_H
