// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_ETH_LAG_INTF_H
#define EOS_TYPES_ETH_LAG_INTF_H

#include <eos/hash_mix.h>
#include <eos/intf.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

#ifdef SWIG
%ignore eos::eth_lag_intf_membership_t(eos::eth_lag_intf_membership_t &&) noexcept;
%ignore eos::eth_lag_intf_membership_t::operator=(eos::eth_lag_intf_membership_t &&)
   noexcept;
%ignore eos::eth_lag_intf_membership_t::reason_is(std::string &&);
%ignore eos::eth_lag_intf_t(eos::eth_lag_intf_t &&) noexcept;
%ignore eos::eth_lag_intf_t::operator=(eos::eth_lag_intf_t &&) noexcept;
#endif

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
/**
 * Appends a string representation of enum eth_lag_intf_fallback_type_t value to
 * the ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(
         std::ostream& os, const eth_lag_intf_fallback_type_t & enum_val);

/** How long to wait for LACP before fallback. */
enum eth_lag_intf_fallback_timeout_default_t {
   ETH_LAG_INTF_FALLBACK_TIMEOUT_DEFAULT = 90,
};
/**
 * Appends a string representation of enum eth_lag_intf_fallback_timeout_default_t
 * value to the ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(
         std::ostream& os,
         const eth_lag_intf_fallback_timeout_default_t & enum_val);

enum eth_lag_intf_member_priority_t {
   ETH_LAG_INTF_PORT_PRIORITY_DEFAULT = 0x8000,
};
/**
 * Appends a string representation of enum eth_lag_intf_member_priority_t value to
 * the ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(
         std::ostream& os, const eth_lag_intf_member_priority_t & enum_val);

/** LAG interface mebmer LACP mode. */
enum eth_lag_intf_member_lacp_mode_t {
   ETH_LAG_INTF_MEMBER_LACP_MODE_NULL,
   ETH_LAG_INTF_MEMBER_LACP_MODE_OFF,
   ETH_LAG_INTF_MEMBER_LACP_MODE_PASSIVE,
   ETH_LAG_INTF_MEMBER_LACP_MODE_ACTIVE,
};
/**
 * Appends a string representation of enum eth_lag_intf_member_lacp_mode_t value to
 * the ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(
         std::ostream& os, const eth_lag_intf_member_lacp_mode_t & enum_val);

/** LAG interface mebmer timeout values. */
enum eth_lag_intf_member_lacp_timeout_t {
   ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_NULL,
   ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_SHORT,
   ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_LONG,
};
/**
 * Appends a string representation of enum eth_lag_intf_member_lacp_timeout_t value
 * to the ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(
         std::ostream& os, const eth_lag_intf_member_lacp_timeout_t & enum_val);

class eth_lag_intf_membership_impl_t;
/**
 * This data structure is used to describe the operational status
 * of an interface configured in an LAG interface.
 */
class EOS_SDK_PUBLIC eth_lag_intf_membership_t {
 public:
   eth_lag_intf_membership_t();
   /** Constructor with paremeters. */
   eth_lag_intf_membership_t(intf_id_t eth_lag_intf_id, bool active,
                             std::string const & reason, double member_time,
                             eth_lag_intf_member_lacp_mode_t mode);
   eth_lag_intf_membership_t(const eth_lag_intf_membership_t& other);
   eth_lag_intf_membership_t& operator=(
      eth_lag_intf_membership_t const & other);

   eth_lag_intf_membership_t(eth_lag_intf_membership_t && other) noexcept;
   eth_lag_intf_membership_t & operator=(eth_lag_intf_membership_t && other)
      noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

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
   /** Moving Setter for 'reason'. */
   void reason_is(std::string && reason);

   /**
    * Getter for 'member_time': the time when this interface became member of an
    * LAG. If never a member, then the value is 0; if once was member, but now is
    * not, then this is the time the interface was removed from member.
    */
   double member_time() const;

   /** Getter for 'mode': the LACP mode this interface is configured. */
   eth_lag_intf_member_lacp_mode_t mode() const;

   bool operator==(eth_lag_intf_membership_t const & other) const;
   bool operator!=(eth_lag_intf_membership_t const & other) const;
   bool operator<(eth_lag_intf_membership_t const & other) const;
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
                                   const eth_lag_intf_membership_t& obj);

 private:
   std::shared_ptr<eth_lag_intf_membership_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const eth_lag_intf_membership_t& obj);

class eth_lag_intf_impl_t;
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
   /** Constructor with interface id. */
   eth_lag_intf_t(intf_id_t intf, uint32_t min_links, uint64_t speed,
                  eth_lag_intf_fallback_type_t fallback_type,
                  uint16_t fallback_timeout, uint64_t min_speed);
   eth_lag_intf_t(const eth_lag_intf_t& other);
   eth_lag_intf_t& operator=(
      eth_lag_intf_t const & other);

   eth_lag_intf_t(eth_lag_intf_t && other) noexcept;
   eth_lag_intf_t & operator=(eth_lag_intf_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

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

   /**
    * Getter for 'min_speed': minimal speed required to keep the LAG interface up.
    */
   uint64_t min_speed() const;

   /** Returns the default fallback timeout value in seconds. */
   uint16_t fallback_timeout_default() const;

   bool operator==(eth_lag_intf_t const & other) const;
   bool operator!=(eth_lag_intf_t const & other) const;
   bool operator<(eth_lag_intf_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os, const eth_lag_intf_t& obj);

 private:
   std::shared_ptr<eth_lag_intf_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const eth_lag_intf_t& obj);
}

#endif // EOS_TYPES_ETH_LAG_INTF_H
