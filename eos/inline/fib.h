// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_FIB_H
#define INLINE_FIB_H

inline fib_route_t::fib_route_t()
   : prefix_(), preference_(1), metric_(0), route_type_(), fec_id_(0) {
}

inline fib_route_t::fib_route_t(ip_prefix_t const & prefix)
   : prefix_(prefix), preference_(1), metric_(0), route_type_(), fec_id_(0) {
}

inline bool
fib_route_t::operator==(fib_route_t const & other) const {
   return prefix_ == other.prefix_ &&
      preference_ == other.preference_ &&
      metric_ == other.metric_ &&
      route_type_ == other.route_type_ &&
      fec_id_ == other.fec_id_;
}

inline ip_prefix_t
fib_route_t::prefix() const {
   return prefix_;
}

inline void
fib_route_t::prefix_is(ip_prefix_t const & prefix) {
   prefix_ = prefix;
}

inline ip_route_preference_t
fib_route_t::preference() const {
   return preference_;
}

inline void
fib_route_t::preference_is(ip_route_preference_t preference) {
   preference_ = preference;
}

inline ip_route_metric_t
fib_route_t::metric() const {
   return metric_;
}

inline void
fib_route_t::metric_is(ip_route_metric_t metric) {
   metric_ = metric;
}

inline fib_route_type_t
fib_route_t::route_type() const {
   return route_type_;
}

inline void
fib_route_t::route_type_is(fib_route_type_t route_type) {
   route_type_ = route_type;
}

inline uint64_t
fib_route_t::fec_id() const {
   return fec_id_;
}

inline void
fib_route_t::fec_id_is(uint64_t const & fec_id) {
   fec_id_ = fec_id;
}

inline fib_via_t::fib_via_t() : hop_(), intf_() {
}

inline fib_via_t::fib_via_t(ip_addr_t const & hop, intf_id_t const & intf)
   : hop_(hop), intf_(intf) {
}

inline bool
fib_via_t::operator==(fib_via_t const & other) const {
   return hop_ == other.hop_ &&
      intf_ == other.intf_;
}

inline ip_addr_t
fib_via_t::hop() const {
   return hop_;
}

inline void
fib_via_t::hop_is(ip_addr_t const & hop) {
   hop_ = hop;
}

inline intf_id_t
fib_via_t::intf() const {
   return intf_;
}

inline void
fib_via_t::intf_is(intf_id_t const & intf) {
   intf_ = intf;
}

inline fib_fec_t::fib_fec_t() : fec_id_(0), fec_type_(), via_() {
}

inline fib_fec_t::fib_fec_t(uint64_t const & fec_id)
   :fec_id_(fec_id), fec_type_(), via_() {
}

inline uint64_t
fib_fec_t::fec_id() const {
   return fec_id_;
}

inline void
fib_fec_t::fec_id_is(uint64_t const & fec_id) {
   fec_id_ = fec_id;
}

inline fib_fec_type_t
fib_fec_t::fec_type() {
   return fec_type_;
}

inline void
fib_fec_t::fec_type_is(fib_fec_type_t fec_type) {
   fec_type_ = fec_type;
}

inline std::forward_list<fib_via_t>
fib_fec_t::via() const {
   return via_;
}

inline void
fib_fec_t::via_is(std::forward_list<fib_via_t> const & vias) {
   via_ = vias;
}

inline void
fib_fec_t::via_set(fib_via_t const & via) {
   via_.push_front(via);
}

inline void
fib_fec_t::via_del(fib_via_t const & via) {
   via_.remove(via);
}

#endif // INLINE_FIB_H

