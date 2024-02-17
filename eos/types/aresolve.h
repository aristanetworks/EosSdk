// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_ARESOLVE_H
#define EOS_TYPES_ARESOLVE_H

#include <eos/hash_mix.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <list>
#include <memory>
#include <sstream>

namespace eos {
/** Internal record helper class. */

class aresolve_internal;

/**
 * A base DNS response class.
 *
 * When receiving an aresolve_record_*, if valid() is false, the last_error()
 * method should be called to receive the EAI_* error (which can be converted to a
 * string with gai_strerror()). If there is no error, accessors in subclasses of
 * aresolve_record_base contain the latest update for the request.
 *
 * This class is not instantiated or received by user code.
 */
class EOS_SDK_PUBLIC aresolve_record_base {
 public:

   /** Getter for 'qname': the DNS query (request) name. */
   std::string qname() const;

   /** Getter for 'last_refresh': the last refresh time, seconds since boot. */
   seconds_t last_refresh() const;

   /**
    * Getter for 'valid': the flag indicating whether the request was successful.
    * If false, last_error() will return a non-zero value.
    */
   bool valid() const;

   /**
    * Getter for 'last_error': error code reporting the last error, or 0 if the
    * record was resolved. Values are EAI_* constants in netdb.h.
    */
   int last_error() const;

   /** The hash function for type aresolve_record_base. */
   uint32_t hash() const;
   /** The hash mix function for type aresolve_record_base. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * aresolve_record_base to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const aresolve_record_base& obj);

 protected:
   aresolve_record_base() EOS_SDK_INTERNAL;
   virtual ~aresolve_record_base() EOS_SDK_INTERNAL;

 private:
   std::string qname_;
   seconds_t last_refresh_;
   bool valid_;
   int last_error_;
   friend class aresolve_internal;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const aresolve_record_base& obj);

/**
 * A DNS response for a hostname query containing resolved IP addresses received by
 * the on_aresolve_host() receiver method.
 * A host response contains zero or more IPv4 or IPv6 addresses.
 */
class EOS_SDK_PUBLIC aresolve_record_host : public aresolve_record_base {
 public:

   aresolve_record_host() EOS_SDK_INTERNAL;
   virtual ~aresolve_record_host() EOS_SDK_INTERNAL;
   /** Getter for 'addr_v4': the resolved IPv4 addresses for the qname(). */
   std::list<ip_addr_t> const & addr_v4() const;

   /** Getter for 'addr_v6': the resolved IPv6 addresses for the qname(). */
   std::list<ip_addr_t> const & addr_v6() const;

   /** The hash function for type aresolve_record_host. */
   uint32_t hash() const;
   /** The hash mix function for type aresolve_record_host. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * aresolve_record_host to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const aresolve_record_host& obj);

 private:
   std::list<ip_addr_t> addr_v4_;
   std::list<ip_addr_t> addr_v6_;
   friend class aresolve_internal;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const aresolve_record_host& obj);
}

#endif // EOS_TYPES_ARESOLVE_H
