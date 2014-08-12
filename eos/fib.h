// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_FIB_H
#define EOS_FIB_H

#include <forward_list>
#include <eos/base.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/ip_route.h>
#include <eos/iterator.h>

#include <eos/types/fib.h>

namespace eos {

class fib_route_iter_impl;

class EOS_SDK_PUBLIC fib_route_iter_t {
   // Uncomment when Iterator is defined.
   // : public iter_base<fib_route_t, fib_route_iter_impl> {

 private:
   friend class fib_route_iter_impl;
   explicit fib_route_iter_t(fib_route_iter_impl * const) EOS_SDK_PRIVATE;
};

class fib_fec_iter_impl;

class EOS_SDK_PUBLIC fib_fec_iter_t {
   // Uncomment when Iterator is defined.
   //: public iter_base<fib_fec_t, fib_fec_iter_impl> {

 private:
   friend class fib_fec_iter_impl;
   explicit fib_fec_iter_t(fib_fec_iter_impl * const) EOS_SDK_PRIVATE;
};



/// The FIB Manager
class EOS_SDK_PUBLIC fib_mgr {
 public:
   virtual ~fib_mgr();

   // Iterators
   virtual fib_route_iter_t fib_route_iter() const = 0;
   virtual fib_fec_iter_t fib_fec_iter() const = 0;

   // FEC management
   virtual bool fib_fec_set(fib_fec_t const &) = 0;
   virtual void fib_fec_del(uint64_t const &) = 0;
   virtual bool fib_fec_exists(uint64_t const &) = 0;
   virtual fib_fec_t fib_fec(uint64_t const &) = 0;

   // Route Management
   virtual bool fib_route_set(fib_route_t const &) = 0;
   virtual void fib_route_del(ip_prefix_t const &) = 0;
   virtual bool fib_route_exists(ip_prefix_t const &) = 0;
   virtual fib_route_t fib_route(ip_prefix_t const &) = 0;

 protected:
   fib_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(fib_mgr);
};

} // end namespace eos

#endif // EOS_FIB_H

