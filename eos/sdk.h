// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_SDK_H
#define EOS_SDK_H

#include <eos/agent.h>
#include <eos/base.h>

namespace eos {

class acl_mgr;
class aresolve_mgr;
class class_map_mgr;
class decap_group_mgr;
class directflow_mgr;
class eth_intf_mgr;
class eth_phy_intf_mgr;
class event_loop;
class fib_mgr;
class intf_mgr;
class ip_route_mgr;
class mac_table_mgr;
class mlag_mgr;
class mount_mgr;
class mpls_route_mgr;
class neighbor_table_mgr;
class nexthop_group_mgr;
class policy_map_mgr;
class system_mgr;
class timeout_mgr;

/**
 * Manages the differents managers of the SDK. One manager of each type can be
 * linked to a SDK object.
 * As managers must be initialized at the beginning of the program, the init_*_mgr()
 * functions should be called for any managers you plan to use.
 * Since the get_*_mgr() functions also call their respective init_*_mgr() functions
 * if necessary, accessing the managers at the beginning of the code (before the
 * agent_loop is called) is enough to initialize them.
 */
class EOS_SDK_PUBLIC sdk {
 public:
    sdk();
    ~sdk();

    void init_acl_mgr();
    void init_agent_mgr();
    void init_aresolve_mgr();
    void init_class_map_mgr();
    void init_decap_group_mgr();
    void init_directflow_mgr();
    void init_eth_intf_mgr();
    void init_eth_phy_intf_mgr();
    void init_event_loop();
    void init_fib_mgr();
    void init_intf_mgr();
    void init_ip_route_mgr();
    void init_mac_table_mgr();
    void init_mlag_mgr();
    void init_mpls_route_mgr();
    void init_neighbor_table_mgr();
    void init_nexthop_group_mgr();
    void init_policy_map_mgr();
    void init_system_mgr();
    void init_timeout_mgr();

    void main_loop(const char * agent_name, int argc, char ** argv);

    acl_mgr * get_acl_mgr();
    agent_mgr * get_agent_mgr();
    aresolve_mgr * get_aresolve_mgr();
    class_map_mgr * get_class_map_mgr();
    decap_group_mgr * get_decap_group_mgr();
    directflow_mgr * get_directflow_mgr();
    eth_intf_mgr * get_eth_intf_mgr();
    eth_phy_intf_mgr * get_eth_phy_intf_mgr();
    event_loop * get_event_loop();
    fib_mgr * get_fib_mgr();
    intf_mgr * get_intf_mgr();
    ip_route_mgr * get_ip_route_mgr();
    mac_table_mgr * get_mac_table_mgr();
    mlag_mgr * get_mlag_mgr();
    // TODO: move back to private (BUG86400)
    mount_mgr * get_mount_mgr();
    mpls_route_mgr * get_mpls_route_mgr();
    neighbor_table_mgr * get_neighbor_table_mgr();
    nexthop_group_mgr * get_nexthop_group_mgr();
    policy_map_mgr * get_policy_map_mgr();
    system_mgr * get_system_mgr();
    timeout_mgr * get_timeout_mgr();

 private:
    void init_mount_mgr();

    EOS_SDK_DISALLOW_COPY_CTOR(sdk);
    acl_mgr * acl_mgr_;
    agent_mgr * agent_mgr_;
    aresolve_mgr * aresolve_mgr_;
    class_map_mgr * class_map_mgr_;
    decap_group_mgr * decap_group_mgr_;
    directflow_mgr * directflow_mgr_;
    eth_intf_mgr * eth_intf_mgr_;
    eth_phy_intf_mgr * eth_phy_intf_mgr_;
    event_loop * event_loop_;
    fib_mgr * fib_mgr_;
    intf_mgr * intf_mgr_;
    ip_route_mgr * ip_route_mgr_;
    mac_table_mgr * mac_table_mgr_;
    mlag_mgr * mlag_mgr_;
    mount_mgr * mount_mgr_;
    mpls_route_mgr * mpls_route_mgr_;
    neighbor_table_mgr * neighbor_table_mgr_;
    nexthop_group_mgr * nexthop_group_mgr_;
    policy_map_mgr * policy_map_mgr_;
    system_mgr * system_mgr_;
    timeout_mgr * timeout_mgr_;
};

}

#include <eos/inline/sdk.h>

#endif // EOS_SDK_H
