// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_MPLS_ROUTE_H
#define EOS_INLINE_MPLS_ROUTE_H

namespace eos {

inline mpls_route_key_t::mpls_route_key_t() : top_label(0), metric(0) {
}

inline mpls_route_key_t::mpls_route_key_t(mpls_label_t const & _label,
                                          mpls_route_metric_t _metric)
   : top_label(_label), metric(_metric) {
}

inline bool
mpls_route_key_t::operator==(mpls_route_key_t const & other) const {
   return top_label == other.top_label && metric == other.metric;
}

inline bool
mpls_route_key_t::operator!=(mpls_route_key_t const & other) const {
   return !(*this == other);
}

inline mpls_route_t::mpls_route_t() : key(), persistent(false) {
}

inline mpls_route_t::mpls_route_t(mpls_route_key_t const & route_key)
   : key(route_key), persistent(false) {
}

inline bool
mpls_route_t::operator==(mpls_route_t const & other) const {
   return persistent == other.persistent && key == other.key;
}

inline bool
mpls_route_t::operator!=(mpls_route_t const & other) const {
   return !(*this == other);
}

inline mpls_route_via_t::mpls_route_via_t()
   : route_key(), hop(), intf(),
     pushswap_label(0),
     label_action(MPLS_ACTION_NULL),
     ttl_mode(MPLS_TTLMODE_NULL),
     payload_type(MPLS_PAYLOAD_TYPE_NULL) {
}

inline mpls_route_via_t::mpls_route_via_t(mpls_route_key_t const & key)
   : route_key(key), hop(), intf(),
     pushswap_label(0),
     label_action(MPLS_ACTION_NULL),
     ttl_mode(MPLS_TTLMODE_NULL),
     payload_type(MPLS_PAYLOAD_TYPE_NULL) {
}

}

#endif // EOS_INLINE_MPLS_ROUTE_H
