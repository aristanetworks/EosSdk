// Copyright (c) 2018 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_MACSEC_H
#define EOS_TYPES_MACSEC_H

#include <eos/exception.h>
#include <eos/hash_mix.h>
#include <eos/panic.h>
#include <eos/utility.h>
#include <sstream>

namespace eos {

typedef std::string macsec_profile_name_t;

/** Cipher suite used for MACsec. */
enum macsec_cipher_suite_t {
   CIPHER_NULL,
   GCM_AES_XPN_128 = 128,
   GCM_AES_XPN_256 = 256,
};
/**
 * Appends a string representation of enum macsec_cipher_suite_t value to the
 * ostream.
 */
std::ostream& operator<<(std::ostream& os, const macsec_cipher_suite_t & enum_val);

/** Which key an interface is using if a profile is configured. */
enum macsec_intf_key_status_t {
   MACSEC_NO_PROFILE,
   MACSEC_KEY_NONE,
   MACSEC_KEY_PRIMARY,
   MACSEC_KEY_FALLBACK,
};
/**
 * Appends a string representation of enum macsec_intf_key_status_t value to the
 * ostream.
 */
std::ostream& operator<<(std::ostream& os,
                         const macsec_intf_key_status_t & enum_val);

/** A connectivity association key. */
class EOS_SDK_PUBLIC macsec_key_t {
 public:
   macsec_key_t();

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
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of macsec_key_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const macsec_key_t& obj);

 private:
   std::string cak_;
   std::string ckn_;
   bool encoded_;
};

/** A MACsec profile which can be attached to an interface. */
class EOS_SDK_PUBLIC macsec_profile_t {
 public:
   macsec_profile_t();
   explicit macsec_profile_t(macsec_profile_name_t name);

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
    * protection.
    */
   bool bypass_lldp() const;
   /** Setter for 'bypass_lldp'. */
   void bypass_lldp_is(bool bypass_lldp);

   /**
    * Getter for 'allow_unprotected': if set, allow transmit/receive without MAC
    * security protection.
    */
   bool allow_unprotected() const;
   /** Setter for 'allow_unprotected'. */
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

   bool operator==(macsec_profile_t const & other) const;
   bool operator!=(macsec_profile_t const & other) const;
   bool operator<(macsec_profile_t const & other) const;
   /** The hash function for type macsec_profile_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * macsec_profile_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const macsec_profile_t& obj);

 private:
   macsec_profile_name_t name_;
   macsec_key_t primary_key_;
   macsec_key_t fallback_key_;
   uint8_t key_server_priority_;
   uint32_t rekey_period_;
   macsec_cipher_suite_t cipher_;
   bool dot1x_;
   bool include_sci_;
   bool bypass_lldp_;
   bool allow_unprotected_;
   bool replay_protection_;
   uint32_t replay_protection_window_;
   bool key_retirement_immediate_;
};

/** Information regarding the MACsec status of an interface. */
class EOS_SDK_PUBLIC macsec_intf_status_t {
 public:
   macsec_intf_status_t();

   macsec_intf_key_status_t status() const;
   void status_is(macsec_intf_key_status_t status);

   bool operator==(macsec_intf_status_t const & other) const;
   bool operator!=(macsec_intf_status_t const & other) const;
   bool operator<(macsec_intf_status_t const & other) const;
   /** The hash function for type macsec_intf_status_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * macsec_intf_status_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const macsec_intf_status_t& obj);

 private:
   macsec_intf_key_status_t status_;
};

/** MACsec interface counters class. */
class EOS_SDK_PUBLIC macsec_intf_counters_t {
 public:
   macsec_intf_counters_t();
   macsec_intf_counters_t(uint64_t out_pkts_encrypted,
                          uint64_t out_octets_encrypted,
                          uint64_t in_pkts_decrypted, uint64_t in_octets_decrypted,
                          uint64_t in_pkts_not_valid);

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
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * macsec_intf_counters_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const macsec_intf_counters_t& obj);

 private:
   uint64_t out_pkts_encrypted_;
   uint64_t out_octets_encrypted_;
   uint64_t in_pkts_decrypted_;
   uint64_t in_octets_decrypted_;
   uint64_t in_pkts_not_valid_;
};
}

#include <eos/inline/types/macsec.h>

#endif // EOS_TYPES_MACSEC_H
