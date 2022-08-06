// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_INTF_IMPL_H
#define EOS_INLINE_TYPES_INTF_IMPL_H

namespace eos {







// Default constructor.
intf_counters_impl_t::intf_counters_impl_t() :
      out_ucast_pkts_(0), out_multicast_pkts_(0), out_broadcast_pkts_(0),
      in_ucast_pkts_(0), in_multicast_pkts_(0), in_broadcast_pkts_(0),
      out_octets_(0), in_octets_(0), out_discards_(0), out_errors_(0),
      in_discards_(0), in_errors_(0), sample_time_(0) {
}

intf_counters_impl_t::intf_counters_impl_t(uint64_t out_ucast_pkts,
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
      out_ucast_pkts_(out_ucast_pkts), out_multicast_pkts_(out_multicast_pkts),
      out_broadcast_pkts_(out_broadcast_pkts), in_ucast_pkts_(in_ucast_pkts),
      in_multicast_pkts_(in_multicast_pkts), in_broadcast_pkts_(in_broadcast_pkts),
      out_octets_(out_octets), in_octets_(in_octets), out_discards_(out_discards),
      out_errors_(out_errors), in_discards_(in_discards), in_errors_(in_errors),
      sample_time_(sample_time) {
}

uint64_t
intf_counters_impl_t::out_ucast_pkts() const {
   return out_ucast_pkts_;
}

uint64_t
intf_counters_impl_t::out_multicast_pkts() const {
   return out_multicast_pkts_;
}

uint64_t
intf_counters_impl_t::out_broadcast_pkts() const {
   return out_broadcast_pkts_;
}

uint64_t
intf_counters_impl_t::in_ucast_pkts() const {
   return in_ucast_pkts_;
}

uint64_t
intf_counters_impl_t::in_multicast_pkts() const {
   return in_multicast_pkts_;
}

uint64_t
intf_counters_impl_t::in_broadcast_pkts() const {
   return in_broadcast_pkts_;
}

uint64_t
intf_counters_impl_t::out_octets() const {
   return out_octets_;
}

uint64_t
intf_counters_impl_t::in_octets() const {
   return in_octets_;
}

uint64_t
intf_counters_impl_t::out_discards() const {
   return out_discards_;
}

uint64_t
intf_counters_impl_t::out_errors() const {
   return out_errors_;
}

uint64_t
intf_counters_impl_t::in_discards() const {
   return in_discards_;
}

uint64_t
intf_counters_impl_t::in_errors() const {
   return in_errors_;
}

seconds_t
intf_counters_impl_t::sample_time() const {
   return sample_time_;
}

bool
intf_counters_impl_t::operator==(intf_counters_impl_t const & other) const {
   return out_ucast_pkts_ == other.out_ucast_pkts_ &&
          out_multicast_pkts_ == other.out_multicast_pkts_ &&
          out_broadcast_pkts_ == other.out_broadcast_pkts_ &&
          in_ucast_pkts_ == other.in_ucast_pkts_ &&
          in_multicast_pkts_ == other.in_multicast_pkts_ &&
          in_broadcast_pkts_ == other.in_broadcast_pkts_ &&
          out_octets_ == other.out_octets_ &&
          in_octets_ == other.in_octets_ &&
          out_discards_ == other.out_discards_ &&
          out_errors_ == other.out_errors_ &&
          in_discards_ == other.in_discards_ &&
          in_errors_ == other.in_errors_ &&
          sample_time_ == other.sample_time_;
}

bool
intf_counters_impl_t::operator!=(intf_counters_impl_t const & other) const {
   return !operator==(other);
}

uint32_t
intf_counters_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
intf_counters_impl_t::mix_me(hash_mix & h) const {
   h.mix(out_ucast_pkts_); // uint64_t
   h.mix(out_multicast_pkts_); // uint64_t
   h.mix(out_broadcast_pkts_); // uint64_t
   h.mix(in_ucast_pkts_); // uint64_t
   h.mix(in_multicast_pkts_); // uint64_t
   h.mix(in_broadcast_pkts_); // uint64_t
   h.mix(out_octets_); // uint64_t
   h.mix(in_octets_); // uint64_t
   h.mix(out_discards_); // uint64_t
   h.mix(out_errors_); // uint64_t
   h.mix(in_discards_); // uint64_t
   h.mix(in_errors_); // uint64_t
   h.mix(sample_time_); // seconds_t
}

std::string
intf_counters_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "intf_counters_t(";
   ss << "out_ucast_pkts=" << out_ucast_pkts_;
   ss << ", out_multicast_pkts=" << out_multicast_pkts_;
   ss << ", out_broadcast_pkts=" << out_broadcast_pkts_;
   ss << ", in_ucast_pkts=" << in_ucast_pkts_;
   ss << ", in_multicast_pkts=" << in_multicast_pkts_;
   ss << ", in_broadcast_pkts=" << in_broadcast_pkts_;
   ss << ", out_octets=" << out_octets_;
   ss << ", in_octets=" << in_octets_;
   ss << ", out_discards=" << out_discards_;
   ss << ", out_errors=" << out_errors_;
   ss << ", in_discards=" << in_discards_;
   ss << ", in_errors=" << in_errors_;
   ss << ", sample_time=" << sample_time_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const intf_counters_impl_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
intf_traffic_rates_impl_t::intf_traffic_rates_impl_t() :
      out_pkts_rate_(0), in_pkts_rate_(0), out_bits_rate_(0), in_bits_rate_(0),
      sample_time_(0) {
}

intf_traffic_rates_impl_t::intf_traffic_rates_impl_t(double out_pkts_rate,
                                                            double in_pkts_rate,
                                                            double out_bits_rate,
                                                            double in_bits_rate,
                                                            seconds_t sample_time) :
      out_pkts_rate_(out_pkts_rate), in_pkts_rate_(in_pkts_rate),
      out_bits_rate_(out_bits_rate), in_bits_rate_(in_bits_rate),
      sample_time_(sample_time) {
}

double
intf_traffic_rates_impl_t::out_pkts_rate() const {
   return out_pkts_rate_;
}

double
intf_traffic_rates_impl_t::in_pkts_rate() const {
   return in_pkts_rate_;
}

double
intf_traffic_rates_impl_t::out_bits_rate() const {
   return out_bits_rate_;
}

double
intf_traffic_rates_impl_t::in_bits_rate() const {
   return in_bits_rate_;
}

seconds_t
intf_traffic_rates_impl_t::sample_time() const {
   return sample_time_;
}

bool
intf_traffic_rates_impl_t::operator==(intf_traffic_rates_impl_t const & other)
       const {
   return out_pkts_rate_ == other.out_pkts_rate_ &&
          in_pkts_rate_ == other.in_pkts_rate_ &&
          out_bits_rate_ == other.out_bits_rate_ &&
          in_bits_rate_ == other.in_bits_rate_ &&
          sample_time_ == other.sample_time_;
}

bool
intf_traffic_rates_impl_t::operator!=(intf_traffic_rates_impl_t const & other)
       const {
   return !operator==(other);
}

uint32_t
intf_traffic_rates_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
intf_traffic_rates_impl_t::mix_me(hash_mix & h) const {
   h.mix(out_pkts_rate_); // double
   h.mix(in_pkts_rate_); // double
   h.mix(out_bits_rate_); // double
   h.mix(in_bits_rate_); // double
   h.mix(sample_time_); // seconds_t
}

std::string
intf_traffic_rates_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "intf_traffic_rates_t(";
   ss << "out_pkts_rate=" << out_pkts_rate_;
   ss << ", in_pkts_rate=" << in_pkts_rate_;
   ss << ", out_bits_rate=" << out_bits_rate_;
   ss << ", in_bits_rate=" << in_bits_rate_;
   ss << ", sample_time=" << sample_time_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const intf_traffic_rates_impl_t& obj) {
   os << obj.to_string();
   return os;
}






}

#include <eos/inline/types/intf.h>

#endif // EOS_INLINE_TYPES_INTF_IMPL_H
