
// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_VRF_H
#define EOS_VRF_H

#include <eos/iterator.h>
#include <eos/types/vrf.h>

namespace eos {

class vrf_iter_impl;

/**
 * A VRF iterator iterating through all active VRFs created in the system.
 */
class EOS_SDK_PUBLIC vrf_iter_t : public iter_base<vrf_t, vrf_iter_impl> {
 private:
   friend class vrf_iter_impl;
   explicit vrf_iter_t(vrf_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * The manager for VRF, this is the main entry point for applications
 * to use EosSdk VRF APIs.
 */
class EOS_SDK_PUBLIC vrf_mgr {
 public:
   virtual ~vrf_mgr();

   /**
    * Iterates VRFs in system, vrf_t is returned for each VRF.
    */
   virtual vrf_iter_t vrf_iter() const = 0;

   /**
    * Checks if a VRF specified by 'vrf_name' exists.
    */
   virtual bool exists(std::string const & vrf_name) const = 0;

   /**
    * Opens a socket inside a VRF specified by 'vrf_name'.
    * Params:
    *    domain: a communication domain, same as in socket().
    *    type: the communication semantics, such as SOCK_STREAM, same as in socket().
    *    protocol: the protocol to be used with the socket, same as in socket().
    *    vrf_name: the name of the vrf_name in which the socket will be created.
    * Return:
    * fd on success, -1 on error, and errno is set appropriately.
    */
   virtual int socket_at(int domain, int type, int protocol,
                         std::string const & vrf_name) = 0;

 protected:
   vrf_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(vrf_mgr);
};

} // end namespace eos

#endif // EOS_VRF_H
