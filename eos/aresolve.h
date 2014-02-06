// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ARESOLVE_H
#define EOS_ARESOLVE_H

#include <list>
#include <string>

#include <eos/ip.h>

// Aresolve allows asynchronous DNS resolution requests to be made.
//
// Aresolve resolves and automatically re-resolves DNS information for
// requests made via the aresolve_handler's watch_* methods.
//

namespace eos {

class aresolve_internal;  // Internal record helper class

// The base DNS response; not instantiated or received by user code.
// When receiving an aresolve_record_*, if valid() is false, the
// last_error() method should be called to receive the EAI_* error
// (which can be converted to a string with gai_strerror()). If there
// is no error, accessors in subclasses of aresolve_record_base
// contain the latest update for the request.
class EOS_SDK_PUBLIC aresolve_record_base {
 protected:
   aresolve_record_base() EOS_SDK_INTERNAL;
   virtual ~aresolve_record_base() EOS_SDK_INTERNAL;

 public:
   std::string const & qname() const;  // The DNS query (request) name
   seconds_t last_refresh() const;     // The last refresh time (seconds since boot)
   bool valid() const;                 // Was the request successful?
                                       // If not, last_error() will be non-zero
   int last_error() const;             // The last error reported (0 = success)
                                       // This value is one of EAI_* in netdb.h
 private:
   std::string qname_;
   seconds_t last_refresh_;
   bool valid_;
   int last_error_;

   friend class aresolve_internal;
};

// A host DNS response. Received by the on_aresolve_host() receiver method.
// A host response contains zero or more IPv4 or IPv6 addresses.
class EOS_SDK_PUBLIC aresolve_record_host : public aresolve_record_base {
 public:
   aresolve_record_host() EOS_SDK_INTERNAL;
   virtual ~aresolve_record_host();

   std::list<ip_addr_t> const & addr_v4() const;  // IPv4 addresses
   std::list<ip_addr_t> const & addr_v6() const;  // IPv6 addresses

 private:
   std::list<ip_addr_t> addr_v4_;
   std::list<ip_addr_t> addr_v6_;

   friend class aresolve_internal;
};

// The Aresolve handler receives callback notifications about objects
// that are being resolved via watch_* calls.
class EOS_SDK_PUBLIC aresolve_handler {
 public:
   aresolve_handler();
   virtual ~aresolve_handler();

   // Start watching IPv4 and IPv6 addresses for the provided host name.
   // When host resolution completes or an error occurs, on_aresolve_host is called.

   // After host resolution completes initially, watched hosts will be
   // refreshed automatically. When changes in the result happen, your
   // handler's on_aresolve_host(), method is called. In this way, you
   // need only watch hostnames you're interested in and implement
   // the on_aresolve_host() method to deal with the changes in results.
   void watch_host(std::string const &);
   // Stop watching address information for the host name (qname) provided.
   void unwatch_host(std::string const &);

   // Called by Aresolve when DNS resolution completes (either
   // successfully, or in error) for a given hostname. May be called
   // more than once for a given hostname, if DNS had a temporary
   // failure.
   virtual void on_aresolve_host(aresolve_record_host const &);

   // Aresolve implementation configuration.
   // Setting these values is a global change and applies to all aresolve_handler.
   // The short time defines the minimum period between DNS resolutions (default 1s)
   uint32_t aresolve_short_time() const;
   // The long time sets the period between re-resolution of queries (default 300s)
   uint32_t aresolve_long_time() const;

   void aresolve_short_time_is(uint32_t);
   void aresolve_long_time_is(uint32_t);
};

}

#include <eos/inline/aresolve.h>

#endif // EOS_ARESOLVE_H
