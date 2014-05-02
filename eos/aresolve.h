// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ARESOLVE_H
#define EOS_ARESOLVE_H

#include <list>
#include <string>

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/ip.h>

/**
 * Aresolve allows asynchronous DNS resolution requests to be made.
 *
 * Aresolve resolves and automatically re-resolves DNS information for
 * requests made via the aresolve_handler's watch_* methods. Whenever
 * resolution information about the watched name changes, the
 * aresolve_handler's on_aresolve_host() function is called.
 */

namespace eos {

class aresolve_internal;  // Internal record helper class

/**
 * A base DNS response class.
 *
 * When receiving an aresolve_record_*, if valid() is false, the
 * last_error() method should be called to receive the EAI_* error
 * (which can be converted to a string with gai_strerror()). If there
 * is no error, accessors in subclasses of aresolve_record_base
 * contain the latest update for the request.
 *
 * Not instantiated or received by user code.
 */
class EOS_SDK_PUBLIC aresolve_record_base {
 protected:
   aresolve_record_base() EOS_SDK_INTERNAL;
   virtual ~aresolve_record_base() EOS_SDK_INTERNAL;

 public:
   /// Returns the DNS query (request) name
   std::string const & qname() const;
   /// Returns the last refresh time, seconds since boot
   seconds_t last_refresh() const;
   /// Was the request successful? If not, last_error() will return a non-zero value
   bool valid() const;
   /// Reports the last error (0 = success). Values from EAI_* constants in netdb.h
   int last_error() const;
 private:
   std::string qname_;
   seconds_t last_refresh_;
   bool valid_;
   int last_error_;

   friend class aresolve_internal;
};

/**
 * A DNS response for a hostname query containing resolved IP addresses
 * Received by the on_aresolve_host() receiver method.
 * A host response contains zero or more IPv4 or IPv6 addresses.
 */
class EOS_SDK_PUBLIC aresolve_record_host : public aresolve_record_base {
 public:
   aresolve_record_host() EOS_SDK_INTERNAL;
   virtual ~aresolve_record_host();

   /// Returns any resolved IPv4 addresses for the qname()
   std::list<ip_addr_t> const & addr_v4() const;
   /// Returns any resolved IPv6 addresses for the qname()
   std::list<ip_addr_t> const & addr_v6() const;
 private:
   std::list<ip_addr_t> addr_v4_;
   std::list<ip_addr_t> addr_v6_;

   friend class aresolve_internal;
};

class aresolve_mgr;

/**
 * The Aresolve handler.
 *
 * This handler receives callback notifications about objects that are
 * being resolved via watch_* calls.
 */
class EOS_SDK_PUBLIC aresolve_handler : public base_handler<aresolve_mgr,
                                                            aresolve_handler> {
 public:
   explicit aresolve_handler(aresolve_mgr *);
   aresolve_mgr * get_aresolve_mgr() const;

   /**
    * Starts or stops watching IPv4 and IPv6 addresses for the provided host name.
    *
    * When host resolution completes or an error occurs,
    * on_aresolve_host() is called.  After host resolution completes
    * initially, watched hosts will be refreshed automatically. When
    * changes in the result happen, your handler's on_aresolve_host(),
    * method is called. In this way, you need only watch hostnames
    * you're interested in and implement the on_aresolve_host() method
    * to deal with the changes in results.
    */
   void watch_host(std::string const &, bool);

   /**
    * Callback called by Aresolve when host resolution completes.
    *
    * Called by Aresolve when DNS resolution of a host previously
    * watched by watch_host() completes.
    *
    * Will be called upon successful updates or otherwise, when either
    * the valid or last update time member attributes change. May be
    * called more than once for a given hostname, if DNS had a
    * temporary failure.
    */
   virtual void on_aresolve_host(aresolve_record_host const &);
};

class EOS_SDK_PUBLIC aresolve_mgr : public base_mgr<aresolve_handler, std::string> {
 public:
   virtual ~aresolve_mgr();

   /**
    * Aresolve implementation configuration settings.
    *
    * The short time defines the minimum period between DNS
    * resolutions. (default: 1s)
    */
   virtual uint32_t aresolve_short_time() const = 0;

   /**
    * Returns the long timer, or seconds between repeated DNS queries.
    *
    * You will receive at most one notification per DNS query (watched
    * host) every aresolve_long_time() number of sceonds. (default: 300s)
    */
   virtual uint32_t aresolve_long_time() const = 0;

   /// Sets the Aresolve short timer to the value provided.
   virtual void aresolve_short_time_is(uint32_t) = 0;
   /// Sets the Aresolve long timer to the value provided.
   virtual void aresolve_long_time_is(uint32_t) = 0;

 protected:
   aresolve_mgr() EOS_SDK_PRIVATE;
   friend class aresolve_handler;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(aresolve_mgr);

};

}

#include <eos/inline/aresolve.h>

#endif // EOS_ARESOLVE_H
