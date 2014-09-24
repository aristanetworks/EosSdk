// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_IP_H
#define EOS_IP_H

#include <netinet/in.h>

#include <functional>
#include <eos/base.h>
#include <eos/types/ip.h>


/**
 * @file
 * IP address and prefix types.
 *
 * This module provides definitions of a variety of IP address types
 * used throughout the SDK, including an IPv4 or IPv6 address, an IP
 * prefix (a network address with a prefix length), and an IP address
 * and mask. IPv4 and IPv6 are supported by each of these types, so
 * there are no separate classes for each address family. For example,
 * the eos::ip_addr_t IP address type has an af() accessor to inspect
 * the address family.
 *
 * Utility functions are provided to parse or validate string format
 * IP addresses and CIDR-style IP prefixes.
 *
 * Some examples of the manipulations available are as follows, see
 * the function descriptions for more information.
 *
 * @code
 * // Constructs an IPv4 address from a string. Must be a valid IP.
 * eos::ip_addr_t v4("1.2.3.4");
 *
 * // Constructs an IPv6 address from a string.
 * eos::ip_addr_t v6("dead:beef::1");
 *
 * // Parses and validates an IP address
 * eos::ip_addr_t address;   // the IPv4/IPv6 address type
 * eos::ip_prefix_t prefix;  // the IPv4/IPv6 prefix type
 * bool valid;
 *
 * // valid == true, and address is changed to contain the
 * // representation of 1.1.1.1 with its af() == eos::AF_IPV4
 * valid = eos::parse_ip_addr("1.1.1.1", &address);
 * // valid == false, address is unchanged
 * valid = eos::parse_ip_addr("not_an_ip", &address);
 *
 * // Parses and validates an IP prefix
 *
 * // The IP address must be the prefix network address, else the
 * // prefix is invalid. Like parse_ip_address, prefix is updated to
 * // contain the representation of the parsed prefix if and only if
 * // valid == true.
 * valid = eos::parse_ip_prefix("192.0.2.0/24", &prefix); // valid == true
 * valid = eos::parse_ip_prefix("192.0.2.1/24", &prefix); // valid == false
 * valid = eos::parse_ip_prefix("192.0.2.1/32", &prefix); // valid == true
 * valid = eos::parse_ip_prefix("::1/128", &prefix); // valid == true
 *
 * // Construct an IP address and mask for 192.0.2.200/24 (e.g., used to
 * // plumb a network interface in ip_intf.h)
 * eos::ip_addr_t intf_addr("192.0.2.200");
 * eos::ip_addr_mask_t intf_addr_mask(intf_addr, 24);
 * @endcode
 */

namespace eos {
// Forward declarations used by std::hash specializations below
class ip_addr_t;

}

// Declaration of hash specialization for ip_addr_t
namespace std {

template <>
struct EOS_SDK_PUBLIC hash<eos::ip_addr_t> {
   size_t operator() (eos::ip_addr_t const &) const;
};

}

#endif // EOS_IP_H
