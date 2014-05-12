// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_INTF_H
#define EOS_INLINE_INTF_H

#include <eos/panic.h>

namespace eos {

inline intf_id_t::intf_id_t(uint64_t id) {
   intfId_ = id;
   if (intf_type() == INTF_TYPE_OTHER) {
      panic("Invalid interface id");
   }
}

inline bool
intf_id_t::operator==(intf_id_t const & other) const {
   return intfId_ == other.intfId_;
}

inline bool
intf_id_t::operator!=(intf_id_t const & other) const {
   return intfId_ != other.intfId_;
}

inline bool
intf_id_t::operator<(intf_id_t const & other) const {
   return intfId_ < other.intfId_;
}

inline intf_mgr * intf_handler::get_intf_mgr() const {
   return mgr_;
}

inline intf_counters_t::intf_counters_t() : out_ucast_pkts_(0),
                                            out_multicast_pkts_(0),
                                            out_broadcast_pkts_(0),
                                            in_ucast_pkts_(0),
                                            in_multicast_pkts_(0),
                                            in_broadcast_pkts_(0),
                                            out_octets_(0),
                                            in_octets_(0),
                                            out_discards_(0),
                                            out_errors_(0),
                                            in_discards_(0),
                                            in_errors_(0),
                                            sample_time_(0) {
}

inline intf_counters_t::intf_counters_t(uint64_t out_ucast_pkts,
                                        uint64_t out_multicast_pkts,
                                        uint64_t out_broadcast_pkts,
                                        uint64_t in_ucast_pkts,
                                        uint64_t in_multicast_pkts,
                                        uint64_t in_broadcast_pkts,
                                        uint64_t out_octets,
                                        uint64_t in_octets,
                                        uint64_t out_discards,
                                        uint64_t out_errors,
                                        uint64_t in_discards,
                                        uint64_t in_errors,
                                        seconds_t sample_time) :
      out_ucast_pkts_(out_ucast_pkts),
      out_multicast_pkts_(out_multicast_pkts),
      out_broadcast_pkts_(out_broadcast_pkts),
      in_ucast_pkts_(in_ucast_pkts),
      in_multicast_pkts_(in_multicast_pkts),
      in_broadcast_pkts_(in_broadcast_pkts),
      out_octets_(out_octets),
      in_octets_(in_octets),
      out_discards_(out_discards),
      out_errors_(out_errors),
      in_discards_(in_discards),
      in_errors_(in_errors),
      sample_time_(sample_time) {
}

inline uint64_t
intf_counters_t::out_ucast_pkts() const {
   return out_ucast_pkts_;
}

inline uint64_t
intf_counters_t::out_multicast_pkts() const {
   return out_multicast_pkts_;
}

inline uint64_t
intf_counters_t::out_broadcast_pkts() const {
   return out_broadcast_pkts_;
}

inline uint64_t
intf_counters_t::in_ucast_pkts() const {
   return in_ucast_pkts_;
}

inline uint64_t
intf_counters_t::in_multicast_pkts() const {
   return in_multicast_pkts_;
}

inline uint64_t
intf_counters_t::in_broadcast_pkts() const {
   return in_broadcast_pkts_;
}

inline uint64_t
intf_counters_t::out_octets() const {
   return out_octets_;
}

inline uint64_t
intf_counters_t::in_octets() const {
   return in_octets_;
}

inline uint64_t
intf_counters_t::in_discards() const {
   return in_discards_;
}

inline uint64_t
intf_counters_t::in_errors() const {
   return in_errors_;
}

inline uint64_t
intf_counters_t::out_discards() const {
   return out_discards_;
}

inline uint64_t
intf_counters_t::out_errors() const {
   return out_errors_;
}

inline seconds_t
intf_counters_t::sample_time() const {
   return sample_time_;
}

inline bool
intf_counters_t::operator==(intf_counters_t const & other) const {
   return ( ( out_ucast_pkts_ == other.out_ucast_pkts_ ) &&
            ( out_multicast_pkts_ == other.out_multicast_pkts_ ) &&
            ( out_broadcast_pkts_ == other.out_broadcast_pkts_ ) &&
            ( in_ucast_pkts_ == other.in_ucast_pkts_ ) &&
            ( in_multicast_pkts_ == other.in_multicast_pkts_ ) &&
            ( in_broadcast_pkts_ == other.in_broadcast_pkts_ ) &&
            ( out_octets_ == other.out_octets_ ) &&
            ( in_octets_ == other.in_octets_ ) &&
            ( out_discards_ == other.out_discards_ ) &&
            ( out_errors_ == other.out_errors_ ) &&
            ( in_discards_ == other.in_discards_ ) &&
            ( in_errors_ == other.in_errors_ ) &&
            ( sample_time_ == other.sample_time_ ) );            
}

inline bool
intf_counters_t::operator!=(intf_counters_t const & other) const {
   return !(*this == other);
}

inline intf_traffic_rates_t::intf_traffic_rates_t() : out_pkts_rate_(0),
                                                      in_pkts_rate_(0),
                                                      out_bits_rate_(0),
                                                      in_bits_rate_(0),
                                                      sample_time_(0) {
}

inline intf_traffic_rates_t::intf_traffic_rates_t(double out_pkts_rate,
                                                  double in_pkts_rate,
                                                  double out_bits_rate,
                                                  double in_bits_rate,
                                                  seconds_t sample_time) :
      out_pkts_rate_(out_pkts_rate),
      in_pkts_rate_(in_pkts_rate),
      out_bits_rate_(out_bits_rate),
      in_bits_rate_(in_bits_rate),
      sample_time_(sample_time) {
}

inline double
intf_traffic_rates_t::out_pkts_rate() const {
   return out_pkts_rate_;
}

inline double
intf_traffic_rates_t::in_pkts_rate() const {
   return in_pkts_rate_;
}

inline double
intf_traffic_rates_t::out_bits_rate() const {
   return out_bits_rate_;
}

inline double
intf_traffic_rates_t::in_bits_rate() const {
   return in_bits_rate_;
}

inline seconds_t
intf_traffic_rates_t::sample_time() const {
   return sample_time_;
}

inline bool
intf_traffic_rates_t::operator==(intf_traffic_rates_t const & other) const {
   return ( ( out_pkts_rate_ == other.out_pkts_rate_ ) &&
            ( in_pkts_rate_ == other.in_pkts_rate_ ) &&
            ( out_bits_rate_ == other.out_bits_rate_ ) &&
            ( in_bits_rate_ == other.in_bits_rate_ ) &&
            ( sample_time_ == other.sample_time_ ) );            
}

inline bool
intf_traffic_rates_t::operator!=(intf_traffic_rates_t const & other) const {
   return !(*this == other);
}

}

#endif // EOS_INLINE_INTF_H
