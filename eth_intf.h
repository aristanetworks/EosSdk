// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_ETH_INTF_H
#define EOS_ETH_INTF_H

#include <eos/eth.h>
#include <eos/intf.h>

namespace eos {

typedef enum eth_link_mode_e {
   LINK_MODE_UNKNOWN,
   LINK_MODE_AUTONEG,
   LINK_MODE_AUTO40GBPS_FULL,
   LINK_MODE_FORCED_10MBPS_HALF,
   LINK_MODE_FORCED_10MBPS_FULL,
   LINK_MODE_FORCED_100MBPS_HALF,
   LINK_MODE_FORCED_100MBPS_FULL,
   LINK_MODE_FORCED_1GBPS_HALF,
   LINK_MODE_FORCED_1GBPS_FULL,
   // There is no such thing as half duplex at speeds >= 10Gbps
   LINK_MODE_FORCED_10GBPS_FULL,
   LINK_MODE_FORCED_40GBPS_FULL,
   LINK_MODE_FORCED_100GBPS_FULL,
} eth_link_mode_t;

//= hidden
// Not needed at this point

// Loopback mode of the eth phy interface
typedef enum eth_loopback_mode_e {
   LOOPBACK_NONE,
   LOOPBACK_MAC,
   LOOPBACK_PHY,
} eth_loopback_mode_t;

// Add timestamp information in packets going out of this intf.
typedef enum eth_timestamp_mode_e {
   TIMESTAMP_MODE_DISABLED,
   TIMESTAMP_MODE_BEFORE_FCS,  // insert timestamp before FCS field
   TIMESTAMP_MODE_REPLACE_FCS, // replace FCS with timestamp field
} eth_timestamp_mode_t;

//= end_hidden

class eth_intf_handler {
 public:
   eth_intf_handler();
   ~eth_intf_handler();

   // Registers this class to receive updates on changes to the
   // interface. Expects a boolean signifying whether notifications
   // should be propagated to this instance or not.
   void watch_all_intfs( bool );
   // void watch_intf( intf_id_t, bool ); //= hide

   // Called after this handler instance has been internally initialized
   // and is ready to start receiving notifications.
   virtual void on_initialized();
   // Hanlder called when an ethernet interface is created
   virtual void on_create(intf_id_t);
   // Handler called when an ethernet interface is deleted
   virtual void on_delete(intf_id_t);
   // Handler called when the mac address of an interface changes
   virtual void on_eth_addr(intf_id_t, eth_addr_t);
   // Handler called when the link mode on an interface changes state
   virtual void on_link_mode(intf_id_t, eth_link_mode_t);
};

class eth_intf_mgr {
 public:
//= hidden
   // Reactor registration
   void add_handler(eth_intf_handler *); // handles all interfaces
   void remove_handler(eth_intf_handler *);
   void add_handler(intf_id_t, eth_intf_handler *); // handle given interface
   void remove_handler(intf_id_t, eth_intf_handler *);
//= end_hidden
   
   // Collection management
   void eth_intf_foreach(bool (*handler)(intf_id_t, void *), void *);
   void eth_intf_foreach(bool (*handler)(intf_id_t, void *), void *,
                         intf_id_t bookmark);
   bool exists(intf_id_t);

   // Attribute accessors
   // Read the operational ethernet address of the interface
   eth_addr_t eth_addr(intf_id_t);
   // Configure the ethernet address of the interface
   void eth_addr_is(intf_id_t, eth_addr_t);
   // Read the operational link mode of the interface
   eth_link_mode_t link_mode(intf_id_t);
   // Configure the link mode of the interface
   void link_mode_is(intf_id_t, eth_link_mode_t);

 //=> private:
   eth_intf_mgr();

 private:
   eth_intf_mgr(eth_intf_mgr const &);
};

eth_intf_mgr * get_eth_intf_mgr();

};

#endif // EOS_ETH_INTF_H
