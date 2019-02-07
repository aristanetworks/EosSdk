// Copyright (c) 2018 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

/**
 * @file
 * Nexthop Group tunnels are a tunneling abstraction in EOS.
 *
 * A nexthop group tunnel is comprised of a tunnel endpoint (IP prefix)
 * and a nexthop group name representing the underlying nexthop group that
 * forwards the traffic.
 *
 * The underlying nexthop group must be manually maintained by the
 * agent. If the underlying nexthop group is not configured, the tunnel
 * endpoint will be unreachable until the given nexthop group is configured.
 *
 * The following example creates a nexthop group tunnel which has an underlying
 * nexthop group "nhg1" that performs IP-in-IP encapsulation of traffic sent to
 * it. For a usage of a nexthop group, see the nexthop_group.h file.
 *
 * @code
 *   // Specify a tunnel endpoint and a nexthop group name
 *   eos::nexthop_group_tunnel_t nhg_tunnel(eos::ip_prefix_t("10.0.0.1/32"), "nhg1");
 *   nexthop_group_tunnel_mgr()->nexthop_group_tunnel_set(nhg_tunnel);
 *   // Configure the underlying nexthop group
 *   eos::nexthop_group_t nhg("nhg1", eos::NEXTHOP_GROUP_IP_IN_IP);
 *   eos::nexthop_group_entry_t nhe1(eos::ip_addr_t("172.12.1.1"));
 *   nhg.nexthop_set(0, nhe1);
 *   nexthop_group_mgr()->nexthop_set(nhg1);
 * @endcode
 */

#ifndef EOS_NEXTHOP_GROUP_TUNNEL_H
#define EOS_NEXTHOP_GROUP_TUNNEL_H

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/iterator.h>
#include <eos/types/nexthop_group_tunnel.h>

namespace eos {

class nexthop_group_tunnel_mgr;

/// The nexthop group tunnel handler
class EOS_SDK_PUBLIC nexthop_group_tunnel_handler :
   public base_handler<nexthop_group_tunnel_mgr,
                       nexthop_group_tunnel_handler> {
 public:
   explicit nexthop_group_tunnel_handler(nexthop_group_tunnel_mgr *);
   nexthop_group_tunnel_mgr * get_nexthop_group_tunnel_mgr() const;
};

class nexthop_group_tunnel_iter_impl;
/// An iterator over configured nexthop group tunnel
class EOS_SDK_PUBLIC nexthop_group_tunnel_iter_t :
   public iter_base<nexthop_group_tunnel_t,
                    nexthop_group_tunnel_iter_impl> {
 private:
   friend class nexthop_group_tunnel_iter_impl;
   explicit nexthop_group_tunnel_iter_t(
                     nexthop_group_tunnel_iter_impl * const) EOS_SDK_PRIVATE;
};

/// The nexthop group tunnel manager
class EOS_SDK_PUBLIC nexthop_group_tunnel_mgr :
   public base_mgr<nexthop_group_tunnel_handler, ip_prefix_t> {
 public:
    virtual ~nexthop_group_tunnel_mgr();

    /// Begin resync mode.
    virtual void resync_init() = 0;
    /// Complete resync mode, ready for regular updates.
    virtual void resync_complete() = 0;

    /// Returns an iterator over configured nexthop group tunnel.
    virtual nexthop_group_tunnel_iter_t nexthop_group_tunnel_iter() const = 0;

    /**
     * Retrieves an existing nexthop_group_tunnel_t by tunnel endpoint, if it exists.
     * Otherwise this returns an empty `nexthop_group_tunnel_t()`
     */
    virtual nexthop_group_tunnel_t nexthop_group_tunnel(
                                    ip_prefix_t const & tunnel_endpoint ) const = 0;

    /** Returns true if a nexthop group tunnel with the given tunnel endpoint has
     *  been configured.
     */
    virtual bool exists(ip_prefix_t const & tunnel_endpoint) const = 0;

    /// Creates or updates a nexthop group tunnel.
    virtual void nexthop_group_tunnel_set(nexthop_group_tunnel_t const &) = 0;

    /// Removes the nexthop group tunnel with the given tunnel endpoint if exists.
    virtual void nexthop_group_tunnel_del(
                           ip_prefix_t const & tunnel_endpoint) = 0;
 protected:
    nexthop_group_tunnel_mgr() EOS_SDK_PRIVATE;
    friend class nexthop_group_tunnel_handler;
 private:
    EOS_SDK_DISALLOW_COPY_CTOR(nexthop_group_tunnel_mgr);
};

} // end namespace eos

#include <eos/inline/nexthop_group_tunnel.h>

#endif // EOS_NEXTHOP_GROUP_TUNNEL_H
