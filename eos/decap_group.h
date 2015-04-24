// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_DECAP_GROUP_H
#define EOS_DECAP_GROUP_H

#include <string>

#include <eos/base.h>
#include <eos/ip.h>
#include <eos/iterator.h>

#include <eos/types/decap_group.h>

/**
 * @file
 * Tunnel decapsulation group management.
 *
 * This module manages tunnel decapsulation for traffic arriving at
 * the switch (on any interface). This allows the switch to act as a
 * tunnel endpoint.
 *
 * By configuring a "decap group", the switch will decapsulate traffic
 * matching the specified outer (tunnel) header destination IP address
 * and IP protocol. Presently only GRE traffic (protocol 47) is
 * supported by decap groups. Traffic arriving at the switch matching
 * the group's parameters will be decapsulated and forwarded normally
 * based on the inner protocol headers.
 *
 * In this example, a decap group named "gre_tunnel1" is configured
 * for GRE traffic arriving at the switch with a tunnel destination
 * address of 172.12.0.1. That address may either be bound to a local
 * switch interface or announced by the switch in routing protocols.
 *
 * @code
 * // Configures a decapsulation group to unwrap received GRE traffic
 * eos::decap_group_t tunnel("gre_tunnel1",
 *                           eos::ip_addr_t("172.12.0.1"),
 *                           eos::PROTOCOL_TYPE_GRE);
 * mgr->decap_group_set(tunnel);
 * @endcode
 */
namespace eos {

class decap_group_iter_impl;

/// An iterator that yields a `decap_group_t` for each configured decap group.
class EOS_SDK_PUBLIC decap_group_iter_t : public iter_base<decap_group_t,
                                                           decap_group_iter_impl> {
 private:
   friend class decap_group_iter_impl;
   explicit decap_group_iter_t(decap_group_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * A manager of 'ip decap-group' configurations.
 *
 * Create one of these via sdk object prior to starting the agent main loop. When
 * your eos::agent_handler::on_initialized virtual function is called, the manager
 * is valid for use.
 */
class EOS_SDK_PUBLIC decap_group_mgr {
 public:
   virtual ~decap_group_mgr();

   /**
    * Enter resync mode.
    *
    * At this point the decap_group_mgr will start tracking which
    * groups you've added.
    */
   virtual void resync_init() = 0;

   /**
    * Exit resync mode.
    *
    * All decap groups in Sysdb that you haven't re-added during this
    * resync period will now be deleted.
    */
   virtual void resync_complete() = 0;


   /**
    * Iterates over all the decap groups currently configured.
    */
   virtual decap_group_iter_t decap_group_iter() const = 0;

   /**
    * Adds the specified decap group to the system configuration.
    *
    * Either creates or updates a decap group (keyed by the group name).
    */
   virtual void decap_group_set(decap_group_t const &) = 0;

   /**
    * Removes the named decap group from the configuration.
    *
    * If the specified group name does not exist, no action is taken.
    */
   virtual void decap_group_del(std::string const & decap_group_name) = 0;
 protected:
   decap_group_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(decap_group_mgr);
};

}

#endif // EOS_DECAP_GROUP_H
