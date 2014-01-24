// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_IP_ROUTE_H
#define EOS_INLINE_IP_ROUTE_H

namespace eos {

inline ip_route_key_t::ip_route_key_t() : prefix(), preference(1), metric(0) {
}

inline ip_route_key_t::ip_route_key_t(ip_prefix_t const & prefix)
   : prefix(prefix), preference(1), metric(0) {
}

inline ip_route_key_t::ip_route_key_t(ip_prefix_t const & prefix,
                               ip_route_preference_t preference)
   : prefix(prefix), preference(preference), metric(0) {
}

inline ip_route_t::ip_route_t() : key(), tag(0), persistent(false) {
}

inline ip_route_t::ip_route_t(ip_route_key_t const & route_key)
   : key(route_key), tag(0), persistent(false) {
}

inline ip_route_via_t::ip_route_via_t() : route_key(), hop(), intf() {
}

inline ip_route_via_t::ip_route_via_t(ip_route_key_t const & route_key)
   : route_key(route_key), hop(), intf() {
}

}

#endif // EOS_INLINE_IP_ROUTE_H
