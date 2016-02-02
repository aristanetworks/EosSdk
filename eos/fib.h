// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

/**
 * @file
 * System Forwarding Information Base (FIB) management
 *
 * The FIB represents the system forwarding tables. In this way, it is
 * generally the result of the programming of any routing agents in
 * the system including static and dynamic routing protocols.
 *
 * This module allows for direct manipulation of the FIB, as well as a
 * means of reacting to the contents of the table as well as perform
 * queries.
 */

#ifndef EOS_FIB_H
#define EOS_FIB_H

#include <forward_list>
#include <eos/types/sdk.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/ip_route.h>
#include <eos/iterator.h>

#include <eos/types/fib.h>

namespace eos {

class fib_route_iter_impl;

class EOS_SDK_PUBLIC fib_route_iter_t
    : public iter_base<fib_route_t, fib_route_iter_impl> {

 private:
   friend class fib_route_iter_impl;
   explicit fib_route_iter_t(fib_route_iter_impl * const) EOS_SDK_PRIVATE;
};

class fib_fec_iter_impl;

class EOS_SDK_PUBLIC fib_fec_iter_t
    : public iter_base<fib_fec_t, fib_fec_iter_impl> {

 private:
   friend class fib_fec_iter_impl;
   explicit fib_fec_iter_t(fib_fec_iter_impl * const) EOS_SDK_PRIVATE;
};

class fib_mgr;

/// This class receives changes route/fec collection
class EOS_SDK_PUBLIC fib_handler : public base_handler<fib_mgr, fib_handler> {
 public:
    // This constructor requires a NOTIFYING_READ or WRITE fib_mgr.
   explicit fib_handler(fib_mgr *);
   fib_mgr * get_fib_mgr() const;

   /// Handler called when a route gets added or updated.
   virtual void on_route_set(fib_route_t const&);
   /// Handler called when a route gets deleted.
   virtual void on_route_del(fib_route_key_t const&);

   /// Handler called when a FEC gets added or updated.
   virtual void on_fec_set(fib_fec_t const&);
   /// Handler called when a FEC gets deleted.
   virtual void on_fec_del(fib_fec_key_t const&);
};

/// The FIB Manager
class EOS_SDK_PUBLIC fib_mgr : public base_mgr<fib_handler> {
 public:
   virtual ~fib_mgr();

   // Iterators
   virtual fib_route_iter_t fib_route_iter() const = 0;
   virtual fib_fec_iter_t fib_fec_iter() const = 0;

   // FEC management
   virtual bool fib_fec_set(fib_fec_t const &) = 0;
   virtual void fib_fec_del(fib_fec_key_t const &) = 0;
   virtual bool fib_fec_exists(fib_fec_key_t const &) = 0;
   virtual fib_fec_t fib_fec(fib_fec_key_t const &) = 0;

   // Route Management
   virtual bool fib_route_set(fib_route_t const &) = 0;
   virtual void fib_route_del(fib_route_key_t const &) = 0;
   virtual bool fib_route_exists(fib_route_key_t const &) = 0;
   virtual fib_route_t fib_route(fib_route_key_t const &) = 0;

   // VRF Management
   virtual bool register_vrf(std::string const &, bool) = 0;

   /**
    * Returns the mode this manager is in.
    * This mode is set during the construction of the manager, i.e.:
    * `sdk.get_fib_mgr(MODE_TYPE_READ_NOTIFYING)`.
    * If MODE_TYPE_READ_ONLY, only the getters and
    * iterators of this manager will function.
    */
   virtual mgr_mode_type_t mode_type() = 0;

 protected:
   fib_mgr() EOS_SDK_PRIVATE;
   friend class fib_handler;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(fib_mgr);
};

#include <eos/inline/fib.h>

} // end namespace eos

#endif // EOS_FIB_H

