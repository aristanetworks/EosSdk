// Copyright (c) 2018 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_BFD_H
#define EOS_TYPES_BFD_H

#include <eos/hash_mix.h>
#include <eos/utility.h>
#include <sstream>

namespace eos {

/** BFD session status. */
enum bfd_session_status_t {
   BFD_SESSION_STATUS_NULL,
   BFD_SESSION_STATUS_DOWN,
   BFD_SESSION_STATUS_INIT,
   BFD_SESSION_STATUS_UP,
   BFD_SESSION_STATUS_ADMIN_DOWN,
};
/**
 * Appends a string representation of enum bfd_session_status_t value to the
 * ostream.
 */
std::ostream& operator<<(std::ostream& os, const bfd_session_status_t & enum_val);

/** BFD session type. */
enum bfd_session_type_t {
   BFD_SESSION_TYPE_NULL,
   BFD_SESSION_TYPE_NORMAL,
   BFD_SESSION_TYPE_MICRO,
   BFD_SESSION_TYPE_VXLANTUNNEL,
   BFD_SESSION_TYPE_LAGRFC7130,
   BFD_SESSION_TYPE_MICRORFC7130,
   BFD_SESSION_TYPE_MULTIHOP,
   BFD_SESSION_TYPE_SBFD_INITIATOR,
   BFD_SESSION_TYPE_SBFD_REFLECTOR,
};
/**
 * Appends a string representation of enum bfd_session_type_t value to the ostream.
 */
std::ostream& operator<<(std::ostream& os, const bfd_session_type_t & enum_val);

/**
 * BFD session key class.
 * Used to identify a BFD session on a switch.
 */
class EOS_SDK_PUBLIC bfd_session_key_t {
 public:
   bfd_session_key_t();
   bfd_session_key_t(ip_addr_t ip_addr, std::string vrf, bfd_session_type_t type,
                     intf_id_t intf);

   /** Getter for 'ip_addr': IP address of the peer. */
   ip_addr_t ip_addr() const;

   /** Getter for 'vrf': vrf associated with the BFD session. */
   std::string vrf() const;

   /** Getter for 'type': type associated with the BFD session. */
   bfd_session_type_t type() const;

   /** Getter for 'intf': local interface associated with the BFD session. */
   intf_id_t intf() const;

   bool operator==(bfd_session_key_t const & other) const;
   bool operator!=(bfd_session_key_t const & other) const;
   bool operator<(bfd_session_key_t const & other) const;
   /** The hash function for type bfd_session_key_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * bfd_session_key_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const bfd_session_key_t& obj);

 private:
   ip_addr_t ip_addr_;
   std::string vrf_;
   bfd_session_type_t type_;
   intf_id_t intf_;
};

/**
 * BFD interval configuration class.
 * Used to specify BFD timer interval.
 */
class EOS_SDK_PUBLIC bfd_interval_t {
 public:
   bfd_interval_t();
   bfd_interval_t(uint16_t tx, uint16_t rx, uint8_t mult);

   /** Getter for 'tx': desired minimum tx interval. */
   uint16_t tx() const;

   /** Getter for 'rx': required minimum rx interval. */
   uint16_t rx() const;

   /** Getter for 'mult': detection multiplier. */
   uint8_t mult() const;

   bool operator==(bfd_interval_t const & other) const;
   bool operator!=(bfd_interval_t const & other) const;
   /** The hash function for type bfd_interval_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of bfd_interval_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const bfd_interval_t& obj);

 private:
   uint16_t tx_;
   uint16_t rx_;
   uint8_t mult_;
};

/** This data structure is used to describe a BFD session. */
class EOS_SDK_PUBLIC bfd_session_t {
 public:
   bfd_session_t();
   bfd_session_t(bfd_session_key_t peer, bfd_session_status_t status);

   /** Getter for 'peer': the peer for this BFD session. */
   bfd_session_key_t peer() const;

   /** Getter for 'status': the status of the BFD session. */
   bfd_session_status_t status() const;

   bool operator==(bfd_session_t const & other) const;
   bool operator!=(bfd_session_t const & other) const;
   bool operator<(bfd_session_t const & other) const;
   /** The hash function for type bfd_session_t. */
   uint32_t hash() const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of bfd_session_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const bfd_session_t& obj);

 private:
   bfd_session_key_t peer_;
   bfd_session_status_t status_;
};
}

#include <eos/inline/types/bfd.h>

#endif // EOS_TYPES_BFD_H
