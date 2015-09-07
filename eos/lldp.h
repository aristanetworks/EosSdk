// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_LLDP_H
#define EOS_LLDP_H

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <string>
#include <set>
#include <list>
#include <map>
#include "eos/intf.h"
#include "eos/eth.h"
#include <eos/types/lldp.h>

/**
 * @file
 * Module for LLDP (Link Layer Discovery Protocol).
 *
 * This module is in BETA. APIs that we expose here are subject to
 * change in future minor and patch releases. Feedback is greatly
 * appreciated.
 *
 * LLDP is a link layer protocol that sends "TLVs" across the link,
 * allowing devices to advertise their identities and properties over a network.
 * The protocol is uni-directional (no acks).
 *
 * This module provides access to information learned from neighbors
 * directly connected via Ethernet interfaces. It can also provide
 * proprietary information to those neighbors via "Organizationally defined TLVs".
 * The mandatory info exchanged over the link are the interface's name, the
 * chassis ID, the system name and the management port address (over
 * which more information can be gleaned via protocols such as SNMP).
 * The protocol has to be enabled per interface and per direction.
 * On EOS, LLDP is disabled by default, but once enabled (cli: "lldp run"), all
 * interfaces are enabled bi-directionally by default.
 *
 * The type of an LLDP TLV is composed of a 24 bit organization
 * (vendor/manufacturer) number assigned by IEEE (also called OUI:
 * organizationally unique identifier), and a subtype which is
 * managed by that organization. That's the lldp_tlv_type_t.
 * When you add the payload (of 0-507 octets) you get a TLV.
 *
 * When enabled, EOS transmits these TLVS on an interface (if they apply)
 * - Chassis ID & Port ID (mandatory)
 * - Port Description
 * - System Name
 * - System Description
 * - System Capabilities (bridge and router)
 * - Management Address
 * - Port Vlan ID (802.1; vlan ID of untagged frames: default/native vlan)
 * - Maximum Frame Size (802.3)
 * - Link Aggregation (802.3)
 * - MAC/Phy config/status info (802.3; speed auto-negotiation)
 */

namespace eos {

class lldp_mgr;

/// Handler class to notify of changes in LLDP.
/// In the handler context, "tlv" means received tlv.
class EOS_SDK_PUBLIC lldp_handler : public base_handler<lldp_mgr, lldp_handler> {
 public:
   explicit lldp_handler(lldp_mgr *);
   /// Returns the associated lldp_mgr
   lldp_mgr * get_lldp_mgr() const;

   /*** "life-cycle" callbacks ***/

   /// Called when a neighbor starts sending LLDP information. 
   /// `intf` refers to the local interface that this information was received on.
   virtual void on_lldp_intf_set(intf_id_t intf);
   /// Called when a neighbor's LLDP information ages out (or is disconnected).
   virtual void on_lldp_intf_del(intf_id_t intf);
   /// Called when the remote information has changed and all has been updated; 
   /// this can be used as an alternative to reacting to each single callback
   /// provided below.
   virtual void on_lldp_intf_change(intf_id_t intf);

   /*** Handlers called when information about the remote port changes ***/

   /* Callbacks for well-known TLVs, the 2 first ones are mandatory TLVs. */
   /// Called when the remote's "chassis ID" changed (mandatory TLV).
   virtual void on_lldp_chassis_id(intf_id_t intf, lldp_chassis_id_t name);
   /// Called when the remote's "interface ID" changed (mandatory TLV).
   virtual void on_lldp_intf_id(intf_id_t intf, lldp_intf_id_t name);
   /// Called when the remote's "system name" changed.
   virtual void on_lldp_system_name(intf_id_t intf, std::string const & name);
   /// Called when the remote's "system description" changed.
   virtual void on_lldp_system_description(intf_id_t intf, std::string const & desc);
   /// Called when the remote's "interface description" changed.
   virtual void on_lldp_intf_description(intf_id_t intf, std::string const & descr);
   /// Called when the remote's "default vlan" changed.
   virtual void on_lldp_default_vlan(intf_id_t intf, vlan_id_t vlan);
   /// Called when the remote's "management vlan" changed.
   virtual void on_lldp_management_vlan(intf_id_t intf, vlan_id_t vlan);
   /// Called when the remote's "maximum transmission unit" changed.
   virtual void on_lldp_max_frame_size(intf_id_t intf, uint32_t size);
   /// Called when the remote's "management address" changed.
   virtual void on_lldp_management_address(intf_id_t intf,
                                  std::list<lldp_management_address_t> const & info);
   /// Called when the remote's "link aggregation config/status" changed.
   virtual void on_lldp_lacp(intf_id_t intf, lldp_lacp_t const & info);
   /// Called when the remote's "phy negotiation config/status" changed.
   virtual void on_lldp_phy(intf_id_t intf, lldp_phy_t const & info);

   /* Called on changes in non standard TLVs (aka organizationally defined TLVs). */
   /// Called when a new TLV type is received, or its content has changed.
   virtual void on_lldp_tlv_set(intf_id_t intf, lldp_tlv_type_t type,
                                std::string const & data);
   /// Called when a TLV type previously received is now absent from advertisements.
   virtual void on_lldp_tlv_del(intf_id_t intf, lldp_tlv_type_t type);

   /*** Configuration change callbacks; when those happen, it means the lldp ***/
   /*** agent has processed the corresponding config you may have set earlier ***/
   /*** via the lldp_mgr apis (or a Cli user changed the config). ***/

   /// Called when a transmission timer value change became effective.
   virtual void on_lldp_tx_timer(uint32_t seconds);
   /// Called when a hold timer value change became effective.
   virtual void on_lldp_hold_time(uint32_t seconds);
   /// Called when an LLDP interface status change became effective.
   virtual void on_lldp_intf_enabled(intf_id_t intf, lldp_intf_enabled_t status);

};


/**
 * A manager for LLDP information.
 *
 * Create one of these via sdk.get_lldp_mgr() prior to starting the
 * agent main loop. When your eos::agent_handler::on_initialized
 * virtual function is called, the manager is valid for use.
 * In manager context, "tlv" means received tlv. What is sent it called tx_tlv.
 */
class EOS_SDK_PUBLIC lldp_mgr : public base_mgr<lldp_handler> {
 public:
   virtual ~lldp_mgr();

   // Configuration api so the agent can bootstrap itself: enable lldp if
   // agent needs it and not yet enabled -- off by default.
   virtual void enabled_is(bool) = 0; // start/stop the lldp agent
   virtual bool enabled() const = 0; // Check lldp agent is configured to run
   /// Enable LLDP on an interface -- on by default.
   /// LLDP is unidirectional, so enablement can be split by direction.
   virtual void intf_enabled_is(intf_id_t intf, lldp_intf_enabled_t enable) = 0;
   virtual lldp_intf_enabled_t intf_enabled(intf_id_t intf) const = 0;

   /*** LLDP global configuration (timers) ***/
   /// The LLDP transmit timer specifies how often TLVs are sent (aka
   /// "refreshed"), in seconds, default 30s, range 5-32768
   virtual void tx_timer_is(uint32_t seconds) = 0;
   virtual int  tx_timer() const = 0;
   /// The LLDP holding time determines how long the recipient of our TLVs
   /// should keep them un-refreshed, in seconds, default 120s, range 10-65535.
   /// This is sent to the neighbor as the "ttl" value (this holding time
   /// limit is imposed on our neighbor, has no effect locally).
   virtual  int hold_time() const = 0;
   virtual void hold_time_is(uint32_t seconds) = 0;

   /*** mandatory TLVs ***/
   /// Get the chassisID of the remote interface (< 255 octets)
   virtual lldp_chassis_id_t chassis_id (intf_id_t intf) const = 0;
   /// Get the port ID of the remote interface (< 255 octets)
   virtual lldp_intf_id_t intf_id(intf_id_t intf) const = 0;

   /*** optional TLVs ***/
   /// interface description: max string size 255, empty if not rx-ed
   virtual std::string intf_description(intf_id_t intf) const = 0;
   /// sysname: max string size 255, empty if not rx-ed
   virtual std::string system_name(intf_id_t intf) const = 0;
   /// sysdescr: max string size 255, empty if not rx-ed
   virtual std::string system_description(intf_id_t intf) const = 0;
   /// system capabilities bitmap, 'other' if not rx-ed
   virtual lldp_syscap_t system_capabilities(intf_id_t intf) const = 0;
   /// The default vlan ID (vlan-id for untagged packets); 0 if none or not rx-ed
   virtual vlan_id_t default_vlan(intf_id_t intf) const = 0;
   /// The vlan-id on which the managment interface is available; 0 if none
   virtual vlan_id_t management_vlan(intf_id_t intf) const = 0;
   /// The max frame size on the link; 0 if not rx-ed
   virtual uint32_t max_frame_size(intf_id_t intf) const = 0;
   /// Port-channel this interface is member of (and capability/status)
   /// !value returns false if this tlv was not received.
   virtual lldp_lacp_t lacp(intf_id_t intf)  const = 0;
   /// management info (address, snmp-ifindex, sysDescr-oid)
   /// !value returns false if this tlv was not received.
   /// The type of address (and its encoding) is described using IANA's
   /// AddressFamilyNumbers, which is available here:
   /// http://www.iana.org/assignments/ianaaddressfamilynumbers-mib/
   /// ianaaddressfamilynumbers-mib.
   /// In EOS's case, the address family is an IPV4 address.
   virtual std::list<lldp_management_address_t> management_address(
                                                           intf_id_t intf) const = 0;
   /// The mac phy config status info (auto-negotiation)
   /// !value returns false if this tlv was not received.
   virtual lldp_phy_t phy(intf_id_t intf) const = 0;

   /// Send a/multiple application defined TLV on a interface.
   /// Transmission will occur every tx_timer until revoked.
   virtual void tx_tlv_set(intf_id_t intf, lldp_tlv_type_t type,
                           std::string const & data) = 0;
   virtual void tx_tlv_del(intf_id_t intf, lldp_tlv_type_t type) = 0;
   // Lookup a TLV received from the remote port.
   // If the TLV can be empty (a boolean), use tlv_exists(type) first
   virtual std::string tlv(intf_id_t intf, lldp_tlv_type_t type) const = 0;
   virtual bool tlv_exists(intf_id_t intf, lldp_tlv_type_t type) const = 0;
   /// Get en-block (there is no iterator, cannot be many given mtu limit
   /// this includes all "organizationnally defined TLVs" (owned by this app or not)
   virtual std::map<lldp_tlv_type_t, std::string> tlvs(intf_id_t intf) const = 0;

 protected:
   lldp_mgr() EOS_SDK_PRIVATE;
   friend class lldp_handler;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(lldp_mgr);
};

} // end namespace eos

#if 0
Table of Content / Summary:
Config:                                         set/get/notify
 int                 tx_timer                   *   *   *
 int                 hold_time                  *   *   *
 lldp_intf_enabled_t intf_enabled (intf)        *   *   *
 std::string         tx_tlv[]    (intf, type)   *
Status:
                     intf[]        (intf)               *
                     intf_change   (intf)               *
 lldp_chassis_id_t   chassis_id    (intf)           *   *
 lldp_intf_id_t      intf_id       (intf)           *   *
 std::string    intf_description   (intf)           *   *
 std::string    system_name        (intf)           *   *
 std::string    system_description (intf)           *   *
 lldp_syscap_t  system_capabilities(intf)           *
 vlan_id_t      default_vlan       (intf)           *   *
 vlan_id_t      management_vlan    (intf)           *   *
 uint32_t       max_frame_size     (intf)           *   *
 lldp_lacp_t    lacp               (intf)           *   *
 std::list<lldp_management_address_t>
                management_address (intf)           *   *
 lldp_phy_t     phy                (intf)           *   *
 bool           tlv_exists         (intf, type)     *
 std::string    tlv                (intf, type)     *   *
 std::map<lldp_tlv_type_t, std::string>
                tlvs               (intf)           *
============
Type on left is extra arg in setter; [] is collection (has _set/_del).
Notification are called on_lldp_xxx.
intf stands for intf_id_t; type for lldp_tlv_type_t
#endif

#include <eos/inline/lldp.h>

#endif // EOS_LLDP_H
