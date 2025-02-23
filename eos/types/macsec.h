// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_MACSEC_H
#define EOS_TYPES_MACSEC_H

#include <eos/exception.h>
#include <eos/hash_mix.h>
#include <eos/intf.h>
#include <eos/panic.h>
#include <eos/utility.h>
#include <forward_list>
#include <memory>
#include <sstream>

#ifdef SWIG
%ignore eos::macsec_key_t(eos::macsec_key_t &&) noexcept;
%ignore eos::macsec_key_t::operator=(eos::macsec_key_t &&) noexcept;
%ignore eos::macsec_profile_t(eos::macsec_profile_t &&) noexcept;
%ignore eos::macsec_profile_t::operator=(eos::macsec_profile_t &&) noexcept;
%ignore eos::macsec_intf_status_t(eos::macsec_intf_status_t &&) noexcept;
%ignore eos::macsec_intf_status_t::operator=(eos::macsec_intf_status_t &&) noexcept;
%ignore eos::macsec_intf_counters_t(eos::macsec_intf_counters_t &&) noexcept;
%ignore eos::macsec_intf_counters_t::operator=(eos::macsec_intf_counters_t &&)
   noexcept;
#endif

namespace eos {

typedef std::string macsec_profile_name_t;

/** Cipher suite used for MACsec. */
enum macsec_cipher_suite_t {
   CIPHER_NULL,
   GCM_AES_128 = 1,
   GCM_AES_256 = 2,
   GCM_AES_XPN_128 = 3,
   GCM_AES_XPN_256 = 4,
};
/**
 * Appends a string representation of enum macsec_cipher_suite_t value to the
 * ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const macsec_cipher_suite_t & enum_val);

/** Which key an interface is using if a profile is configured. */
enum macsec_intf_key_status_t {
   /** MacSec is not configured on the interface. */
   MACSEC_NO_PROFILE,
   /** None of the CAK/CKN could be selected as principal. */
   MACSEC_KEY_NONE,
   /** Configured primary CAK/CKN is selected as principal. */
   MACSEC_KEY_PRIMARY,
   /** Configured fallback CAK/CKN is selected as principal. */
   MACSEC_KEY_FALLBACK,
   /** Previously configured primary CAK/CKN is selected as principal. */
   MACSEC_KEY_PRIMARY_CACHED,
   /** Previously configured fallback CAK/CKN is selected as principal. */
   MACSEC_KEY_FALLBACK_CACHED,
};
/**
 * Appends a string representation of enum macsec_intf_key_status_t value to the
 * ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const macsec_intf_key_status_t & enum_val);

/** Traffic status on an interface. */
enum macsec_intf_traffic_status_t {
   /** Traffic through the interface is protected. */
   MACSEC_TRAFFIC_PROTECTED,
   /** Traffic through the interface is unprotected. */
   MACSEC_TRAFFIC_UNPROTECTED,
   /** Traffic through the interface is blocked. */
   MACSEC_TRAFFIC_BLOCKED,
};
/**
 * Appends a string representation of enum macsec_intf_traffic_status_t value to
 * the ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(
         std::ostream& os, const macsec_intf_traffic_status_t & enum_val);

/** Bypass level for a protocol. */
enum macsec_bypass_t {
   /** Allow transmit/receive of protocol with MACsec encryption only. */
   BYPASS_NULL,
   /** Allow transmit/receive of protocol packets when port is authorized. */
   BYPASS_AUTHORIZED,
   /**
    * Allow transmit/receive of protocol packets when port is authorized or
    * unauthorized.
    */
   BYPASS_UNAUTHORIZED,
};
/** Appends a string representation of enum macsec_bypass_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const macsec_bypass_t & enum_val);

/** Traffic policy on a profile. */
enum macsec_profile_traffic_policy_t {
   TRAFFIC_POLICY_NULL,
   /**
    * Allow transmit/receive of encrypted traffic using operational SAK and block
    * otherwise.
    */
   TRAFFIC_POLICY_ACTIVE_SAK,
   /** Allow transmit/receive of unprotected traffic. */
   TRAFFIC_POLICY_UNPROTECTED,
   /** Block transmit/receive of unprotected traffic. */
   TRAFFIC_POLICY_BLOCKED,
};
/**
 * Appends a string representation of enum macsec_profile_traffic_policy_t value to
 * the ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(
         std::ostream& os, const macsec_profile_traffic_policy_t & enum_val);

class macsec_key_impl_t;
/** A connectivity association key. */
class EOS_SDK_PUBLIC macsec_key_t {
 public:
   macsec_key_t();
   macsec_key_t(const macsec_key_t& other);
   macsec_key_t& operator=(
      macsec_key_t const & other);

   macsec_key_t(macsec_key_t && other) noexcept;
   macsec_key_t & operator=(macsec_key_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /** Getter for 'cak': connectivity association key (CAK). CAK is a hex string. */
   std::string cak() const;
   /** Setter for 'cak'. */
   void cak_is(std::string cak);

   /**
    * Getter for 'ckn': connectivity association key name (CKN). CKN is a hex
    * string.
    */
   std::string ckn() const;
   /** Setter for 'ckn'. */
   void ckn_is(std::string ckn);

   /** Getter for 'encoded': whether or not the CAK has been encoded. */
   bool encoded() const;
   /** Setter for 'encoded'. */
   void encoded_is(bool encoded);

   bool operator==(macsec_key_t const & other) const;
   bool operator!=(macsec_key_t const & other) const;
   bool operator<(macsec_key_t const & other) const;
   /** The hash function for type macsec_key_t. */
   uint32_t hash() const;
   /** The hash mix function for type macsec_key_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of macsec_key_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const macsec_key_t& obj);

 private:
   std::shared_ptr<macsec_key_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const macsec_key_t& obj);

class macsec_profile_impl_t;
/** A MACsec profile which can be attached to an interface. */
class EOS_SDK_PUBLIC macsec_profile_t {
 public:
   macsec_profile_t();
   explicit macsec_profile_t(macsec_profile_name_t name);
   macsec_profile_t(const macsec_profile_t& other);
   macsec_profile_t& operator=(
      macsec_profile_t const & other);

   macsec_profile_t(macsec_profile_t && other) noexcept;
   macsec_profile_t & operator=(macsec_profile_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   /** Getter for 'name': the name of the profile. */
   macsec_profile_name_t name() const;
   /** Setter for 'name'. */
   void name_is(macsec_profile_name_t name);

   /**
    * Getter for 'primary_key': the primary key, which is represented by a CKN and
    * an associated CAK.
    */
   macsec_key_t primary_key() const;
   /** Setter for 'primary_key'. */
   void primary_key_is(macsec_key_t primary_key);

   /**
    * Getter for 'fallback_key': the fallback, or default, key, which is used when
    * the primary is not successful.
    */
   macsec_key_t fallback_key() const;
   /** Setter for 'fallback_key'. */
   void fallback_key_is(macsec_key_t fallback_key);

   /**
    * Getter for 'key_server_priority': MACsec Key Agreement (MKA) protocol key
    * server priority. 255 is the highest priority.
    */
   uint8_t key_server_priority() const;
   /** Setter for 'key_server_priority'. */
   void key_server_priority_is(uint8_t key_server_priority);

   /** Getter for 'rekey_period': MKA session re-key period in seconds. */
   uint32_t rekey_period() const;
   /** Setter for 'rekey_period'. */
   void rekey_period_is(uint32_t rekey_period);

   /** Getter for 'mka_life_time': MKA session lifetime in seconds. */
   uint32_t mka_life_time() const;
   /** Setter for 'mka_life_time'. */
   void mka_life_time_is(uint32_t mka_life_time);

   /** Getter for 'cipher': which encryption standard to use. */
   macsec_cipher_suite_t cipher() const;
   /** Setter for 'cipher'. */
   void cipher_is(macsec_cipher_suite_t cipher);

   /**
    * Getter for 'dot1x': if set, derive MAC security keys from IEEE 802.1X based
    * port authentication. This will be disabled if a key is provided manually.
    */
   bool dot1x() const;
   /** Setter for 'dot1x'. */
   void dot1x_is(bool dot1x);

   /**
    * Getter for 'include_sci': if set, include secure channel identifier (SCI) in
    * data packets.
    */
   bool include_sci() const;
   /** Setter for 'include_sci'. */
   void include_sci_is(bool include_sci);

   /**
    * Getter for 'bypass_lldp': if set, transmit/receive LLDP frames without
    * protection : deprecated in favour of lldp_bypass_level.
    */
   bool bypass_lldp() const;
   /**
    * Setter for 'bypass_lldp': deprecated in favour of lldp_bypass_level_is.
    * Both `bypass_lldp` and `lldp_bypass_level` operate on the same internal
    * attribute.
    * A value of false corresponds to the macsec_bypass_t value BYPASS_NULL while a
    * value of true corresponds to BYPASS_AUTHORIZED.
    */
   void bypass_lldp_is(bool bypass_lldp);
   /**
    * Getter for 'lldp_bypass_level': If set, transmit/receive LLDP frames without
    * Macsec encryption when port is authorized/unauthorized.
    */
   macsec_bypass_t lldp_bypass_level() const;
   /** Setter for 'lldp_bypass_level'. */
   void lldp_bypass_level_is(macsec_bypass_t lldp_bypass_level);

   /** Getter for 'traffic_policy': traffic policy to be used by an interface. */
   macsec_profile_traffic_policy_t traffic_policy() const;
   /** Setter for 'traffic_policy'. */
   void traffic_policy_is(macsec_profile_traffic_policy_t traffic_policy);

   /** Getter for 'allow_unprotected': deprecated in favour of traffic_policy. */
   bool allow_unprotected() const;
   /** Setter for 'allow_unprotected': deprecated in favour of traffic_policy. */
   void allow_unprotected_is(bool allow_unprotected);
   /** Getter for 'replay_protection': if set, enable replay protection. */
   bool replay_protection() const;
   /** Setter for 'replay_protection'. */
   void replay_protection_is(bool replay_protection);

   /** Getter for 'replay_protection_window': replay protection window size. */
   uint32_t replay_protection_window() const;
   /** Setter for 'replay_protection_window'. */
   void replay_protection_window_is(uint32_t replay_protection_window);

   /** Getter for 'key_retirement_immediate': if set, enable key retirement. */
   bool key_retirement_immediate() const;
   /** Setter for 'key_retirement_immediate'. */
   void key_retirement_immediate_is(bool key_retirement_immediate);

   /** Getter for 'intfs': Interfaces with this profile configured. */
   std::forward_list<intf_id_t> const & intfs() const;

   bool operator==(macsec_profile_t const & other) const;
   bool operator!=(macsec_profile_t const & other) const;
   bool operator<(macsec_profile_t const & other) const;
   /** The hash function for type macsec_profile_t. */
   uint32_t hash() const;
   /** The hash mix function for type macsec_profile_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * macsec_profile_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const macsec_profile_t& obj);

 private:
   std::shared_ptr<macsec_profile_impl_t> pimpl;
   friend void addIntf(macsec_profile_t &profile, intf_id_t intfId);
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const macsec_profile_t& obj);

class macsec_intf_status_impl_t;
/** Information regarding the MACsec status of an interface. */
class EOS_SDK_PUBLIC macsec_intf_status_t {
 public:
   macsec_intf_status_t();
   macsec_intf_status_t(const macsec_intf_status_t& other);
   macsec_intf_status_t& operator=(
      macsec_intf_status_t const & other);

   macsec_intf_status_t(macsec_intf_status_t && other) noexcept;
   macsec_intf_status_t & operator=(macsec_intf_status_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   macsec_intf_key_status_t key_status() const;

   macsec_intf_traffic_status_t traffic_status() const;

   /** Deprecated: Setter for 'status'. */
   void status_is(macsec_intf_key_status_t status);
   /** Deprecated: Getter for 'status'. */
   macsec_intf_key_status_t status() const;
   bool operator==(macsec_intf_status_t const & other) const;
   bool operator!=(macsec_intf_status_t const & other) const;
   bool operator<(macsec_intf_status_t const & other) const;
   /** The hash function for type macsec_intf_status_t. */
   uint32_t hash() const;
   /** The hash mix function for type macsec_intf_status_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * macsec_intf_status_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const macsec_intf_status_t& obj);

 private:
   std::shared_ptr<macsec_intf_status_impl_t> pimpl;
   friend void status_is(macsec_intf_status_t &status,
      macsec_intf_key_status_t keyStatus,
      macsec_intf_traffic_status_t trafficStatus);
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const macsec_intf_status_t& obj);

class macsec_intf_counters_impl_t;
/** MACsec interface counters class. */
class EOS_SDK_PUBLIC macsec_intf_counters_t {
 public:
   macsec_intf_counters_t();
   macsec_intf_counters_t(uint64_t out_pkts_encrypted,
                          uint64_t out_octets_encrypted,
                          uint64_t in_pkts_decrypted, uint64_t in_octets_decrypted,
                          uint64_t in_pkts_not_valid);
   macsec_intf_counters_t(const macsec_intf_counters_t& other);
   macsec_intf_counters_t& operator=(
      macsec_intf_counters_t const & other);

   macsec_intf_counters_t(macsec_intf_counters_t && other) noexcept;
   macsec_intf_counters_t & operator=(macsec_intf_counters_t && other) noexcept;
   static void * operator new( std::size_t, void * ptr ) {
      return ptr;
   }
   static void * operator new( std::size_t );
   static void operator delete( void * ) noexcept;

   uint64_t out_pkts_encrypted() const;

   uint64_t out_octets_encrypted() const;

   uint64_t in_pkts_decrypted() const;

   uint64_t in_octets_decrypted() const;

   uint64_t in_pkts_not_valid() const;

   bool operator==(macsec_intf_counters_t const & other) const;
   bool operator!=(macsec_intf_counters_t const & other) const;
   bool operator<(macsec_intf_counters_t const & other) const;
   /** The hash function for type macsec_intf_counters_t. */
   uint32_t hash() const;
   /** The hash mix function for type macsec_intf_counters_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * macsec_intf_counters_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const macsec_intf_counters_t& obj);

 private:
   std::shared_ptr<macsec_intf_counters_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const macsec_intf_counters_t& obj);
}

#endif // EOS_TYPES_MACSEC_H
