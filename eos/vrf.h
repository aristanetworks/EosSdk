// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_VRF_H
#define EOS_VRF_H

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/iterator.h>
#include <eos/types/vrf.h>

/**
 * @file
 * VRF management
 *
 * This module manages Virtual Routing & Forwarding instances, known
 * commonly as VRFs. VRFs let you partition your switch's routing
 * tables so you can have unique IP domains.
 *
 * VRFs are keyed by a unique name across the system, and can be used
 * in other modules to configure routes and nexthops in different
 * domains.  If a route is not programmed in a specific VRF, it
 * belongs to the VRF named "default".
 */

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
    * Register to receive notifications when any VRF on the system changes state.
    */
   void watch_all_vrfs(bool);

   /**
    * Register to receive notifications when the specified VRF on the
    * system changes state.
    */
   void watch_vrf(std::string const & vrf_name, bool);
   
   /**
    * Called when a VRF's operational state changes.
    */
   virtual void on_vrf_state(std::string vrf_name, vrf_state_t vrf_state);
};


class vrf_iter_impl;
/// An iterator that yields a vrf_t for each VRF on the system.
class EOS_SDK_PUBLIC vrf_iter_t : public iter_base<std::string, vrf_iter_impl> {
 private:
   friend class vrf_iter_impl;
   explicit vrf_iter_t(vrf_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * The manager for VRF, this is the main entry point for applications
 * to use EosSdk VRF APIs.
 */
class EOS_SDK_PUBLIC vrf_mgr : public base_mgr<vrf_handler, std::string> {
 public:
   virtual ~vrf_mgr();

   /**
    * Iterates through all configured VRFs on the system, yielding a
    * vrf_t for each VRF.
    */
   virtual vrf_iter_t vrf_iter() const = 0;

   /**
    * Returns true if the VRF is currently configured.
    */
   virtual bool exists(std::string const & vrf_name) const = 0;

   /**
    * Returns the route distinguisher associated with this VRF. The
    * returned value is obtained from status that is the result of the
    * RD configuration under the 'vrf definition' submode and the RD
    * configuration under the 'router bgp vrf' submode. When
    * configuration for the VRF exists in both locations, the value
    * configured under 'router bgp' takes precedence and is returned.
    *
    * If no VRF matches the given name, this returns 0.
    */
   virtual uint64_t rd(std::string const & vrf_name) const = 0;

   /**
    * Returns the operational status of this VRF.
    *
    * If the given VRF name does not have a current status (e.g. a
    * newly configured VRF), or if it does not match any VRFs on the
    * system, this returns VRF_STATE_NULL.
    */
   virtual vrf_state_t state(std::string const & vrf_name) const = 0;

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

   /**
    * Returns a composite `vrf_t` for the named VRF, or a
    * default VRF object if it does not exist.
    *
    * @deprecated, please use the state(), exists(), and rd() methods
    * instead. 
    */
   virtual vrf_t vrf(std::string const & vrf_name) const = 0;

 protected:
   vrf_mgr() EOS_SDK_PRIVATE;
   friend class vrf_handler;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(vrf_mgr);
};

} // end namespace eos

#include <eos/inline/vrf.h>

#endif // EOS_VRF_H
