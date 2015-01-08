
// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_VRF_H
#define EOS_VRF_H

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/iterator.h>
#include <eos/types/vrf.h>

namespace eos {

class vrf_mgr;

/**
 *  The VRF handler.
 *
 *  This class provides handler APIs to react to a VRF's operational state change.
 *
 **/
class EOS_SDK_PUBLIC vrf_handler : public base_handler<vrf_mgr, vrf_handler> {
 public:
   explicit vrf_handler(vrf_mgr *mgr);
   vrf_mgr * get_vrf_mgr() const;

   /**
    * Called when a VRF's state changes. When a VRF:
    *
    *  - is created, its state is VRF_INITIALIZING.
    *  - becomes active, its state is VRF_ACTIVE.
    *  - is being deleted, its state is VRF_DELETING.
    *  - is deleted, its state is VRF_NULL.
    **/
   virtual void on_vrf_state(std::string vrf_name, vrf_state_t vrf_state);
};

class vrf_iter_impl;

class EOS_SDK_PUBLIC vrf_iter_t : public iter_base<vrf_t, vrf_iter_impl> {
 private:
   friend class vrf_iter_impl;
   explicit vrf_iter_t(vrf_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * The manager for VRF, this is the main entry point for applications
 * to use EosSdk VRF APIs.
 */
class EOS_SDK_PUBLIC vrf_mgr : public base_mgr<vrf_handler> {
 public:
   virtual ~vrf_mgr();

   /**
    * Iterates through all VRFs on the system, yielding a vrf_t for each VRF.
    */
   virtual vrf_iter_t vrf_iter() const = 0;

   /**
    * Returns the named VRF, or a default VRF object if it does not exist.
    */
   virtual vrf_t vrf(std::string const & vrf_name) const = 0;

   /**
    * Opens a socket inside a VRF specified by 'vrf_name'.
    *
    * @param domain A communication domain, same as in socket().
    * @param type The communication semantics, such as SOCK_STREAM, same as in
    * socket().
    * @param protocol The protocol to be used with the socket, same as in socket().
    * @param vrf_name The name of the vrf_name in which the socket will be created.
    * @return fd on success, -1 on error, and errno is set appropriately.
    */
   virtual int socket_at(int domain, int type, int protocol,
                         std::string const & vrf_name) = 0;

 protected:
   vrf_mgr() EOS_SDK_PRIVATE;
   friend class vrf_handler;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(vrf_mgr);
};

} // end namespace eos

#include <eos/inline/vrf.h>

#endif // EOS_VRF_H
