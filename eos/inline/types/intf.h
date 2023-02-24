// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_INTF_H
#define EOS_INLINE_TYPES_INTF_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const oper_status_t & enum_val) {
   if (enum_val==INTF_OPER_NULL) {
      os << "INTF_OPER_NULL";
   } else if (enum_val==INTF_OPER_UP) {
      os << "INTF_OPER_UP";
   } else if (enum_val==INTF_OPER_DOWN) {
      os << "INTF_OPER_DOWN";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const intf_type_t & enum_val) {
   if (enum_val==INTF_TYPE_NULL) {
      os << "INTF_TYPE_NULL";
   } else if (enum_val==INTF_TYPE_OTHER) {
      os << "INTF_TYPE_OTHER";
   } else if (enum_val==INTF_TYPE_ETH) {
      os << "INTF_TYPE_ETH";
   } else if (enum_val==INTF_TYPE_VLAN) {
      os << "INTF_TYPE_VLAN";
   } else if (enum_val==INTF_TYPE_MANAGEMENT) {
      os << "INTF_TYPE_MANAGEMENT";
   } else if (enum_val==INTF_TYPE_LOOPBACK) {
      os << "INTF_TYPE_LOOPBACK";
   } else if (enum_val==INTF_TYPE_LAG) {
      os << "INTF_TYPE_LAG";
   } else if (enum_val==INTF_TYPE_NULL0) {
      os << "INTF_TYPE_NULL0";
   } else if (enum_val==INTF_TYPE_CPU) {
      os << "INTF_TYPE_CPU";
   } else if (enum_val==INTF_TYPE_VXLAN) {
      os << "INTF_TYPE_VXLAN";
   } else {
      os << "Unknown value";
   }
   return os;
}


intf_id_t::intf_id_t(uint64_t id) {
   intfId_ = id;
}

bool
intf_id_t::operator==(intf_id_t const & other) const {
   return intfId_ == other.intfId_;
}

bool
intf_id_t::operator!=(intf_id_t const & other) const {
   return !operator==(other);
}

bool
intf_id_t::operator<(intf_id_t const & other) const {
   if(intfId_ != other.intfId_) {
      return intfId_ < other.intfId_;
   }
   return false;
}

uint32_t
intf_id_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
intf_id_t::mix_me(hash_mix & h) const {
   h.mix(intfId_); // uint64_t
}

std::ostream&
operator<<(std::ostream& os, const intf_id_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
intf_counters_t::intf_counters_t() {
   pimpl = std::shared_ptr<intf_counters_impl_t>(
      new intf_counters_impl_t()
   );
}
intf_counters_t::intf_counters_t(uint64_t out_ucast_pkts,
                                        uint64_t out_multicast_pkts,
                                        uint64_t out_broadcast_pkts,
                                        uint64_t in_ucast_pkts,
                                        uint64_t in_multicast_pkts,
                                        uint64_t in_broadcast_pkts,
                                        uint64_t out_octets, uint64_t in_octets,
                                        uint64_t out_discards, uint64_t out_errors,
                                        uint64_t in_discards, uint64_t in_errors,
                                        seconds_t sample_time) {
   pimpl = std::shared_ptr<intf_counters_impl_t>(
      new intf_counters_impl_t(
         out_ucast_pkts,
         out_multicast_pkts,
         out_broadcast_pkts,
         in_ucast_pkts,
         in_multicast_pkts,
         in_broadcast_pkts,
         out_octets,
         in_octets,
         out_discards,
         out_errors,
         in_discards,
         in_errors,
         sample_time
      )
   );
}
intf_counters_t::intf_counters_t(
   const intf_counters_t& other)
{
   pimpl = std::make_unique<intf_counters_impl_t>(
      intf_counters_impl_t(*other.pimpl));
}
intf_counters_t&
intf_counters_t::operator=(
   intf_counters_t const & other)
{
   pimpl = std::shared_ptr<intf_counters_impl_t>(
      new intf_counters_impl_t(*other.pimpl));
   return *this;
}

uint64_t
intf_counters_t::out_ucast_pkts() const {
   return pimpl->out_ucast_pkts();
}
uint64_t
intf_counters_t::out_multicast_pkts() const {
   return pimpl->out_multicast_pkts();
}
uint64_t
intf_counters_t::out_broadcast_pkts() const {
   return pimpl->out_broadcast_pkts();
}
uint64_t
intf_counters_t::in_ucast_pkts() const {
   return pimpl->in_ucast_pkts();
}
uint64_t
intf_counters_t::in_multicast_pkts() const {
   return pimpl->in_multicast_pkts();
}
uint64_t
intf_counters_t::in_broadcast_pkts() const {
   return pimpl->in_broadcast_pkts();
}
uint64_t
intf_counters_t::out_octets() const {
   return pimpl->out_octets();
}
uint64_t
intf_counters_t::in_octets() const {
   return pimpl->in_octets();
}
uint64_t
intf_counters_t::out_discards() const {
   return pimpl->out_discards();
}
uint64_t
intf_counters_t::out_errors() const {
   return pimpl->out_errors();
}
uint64_t
intf_counters_t::in_discards() const {
   return pimpl->in_discards();
}
uint64_t
intf_counters_t::in_errors() const {
   return pimpl->in_errors();
}
seconds_t
intf_counters_t::sample_time() const {
   return pimpl->sample_time();
}
bool
intf_counters_t::operator==(intf_counters_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
intf_counters_t::operator!=(intf_counters_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
intf_counters_t::hash() const {
   return pimpl->hash();
}
void
intf_counters_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
intf_counters_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const intf_counters_t& obj) {
   return operator<<(os, *obj.pimpl);
}


// Default constructor.
intf_traffic_rates_t::intf_traffic_rates_t() {
   pimpl = std::shared_ptr<intf_traffic_rates_impl_t>(
      new intf_traffic_rates_impl_t()
   );
}
intf_traffic_rates_t::intf_traffic_rates_t(double out_pkts_rate,
                                                  double in_pkts_rate,
                                                  double out_bits_rate,
                                                  double in_bits_rate,
                                                  seconds_t sample_time) {
   pimpl = std::shared_ptr<intf_traffic_rates_impl_t>(
      new intf_traffic_rates_impl_t(
         out_pkts_rate,
         in_pkts_rate,
         out_bits_rate,
         in_bits_rate,
         sample_time
      )
   );
}
intf_traffic_rates_t::intf_traffic_rates_t(
   const intf_traffic_rates_t& other)
{
   pimpl = std::make_unique<intf_traffic_rates_impl_t>(
      intf_traffic_rates_impl_t(*other.pimpl));
}
intf_traffic_rates_t&
intf_traffic_rates_t::operator=(
   intf_traffic_rates_t const & other)
{
   pimpl = std::shared_ptr<intf_traffic_rates_impl_t>(
      new intf_traffic_rates_impl_t(*other.pimpl));
   return *this;
}

double
intf_traffic_rates_t::out_pkts_rate() const {
   return pimpl->out_pkts_rate();
}
double
intf_traffic_rates_t::in_pkts_rate() const {
   return pimpl->in_pkts_rate();
}
double
intf_traffic_rates_t::out_bits_rate() const {
   return pimpl->out_bits_rate();
}
double
intf_traffic_rates_t::in_bits_rate() const {
   return pimpl->in_bits_rate();
}
seconds_t
intf_traffic_rates_t::sample_time() const {
   return pimpl->sample_time();
}
bool
intf_traffic_rates_t::operator==(intf_traffic_rates_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
intf_traffic_rates_t::operator!=(intf_traffic_rates_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
uint32_t
intf_traffic_rates_t::hash() const {
   return pimpl->hash();
}
void
intf_traffic_rates_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
intf_traffic_rates_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const intf_traffic_rates_t& obj) {
   return operator<<(os, *obj.pimpl);
}


no_such_interface_error::no_such_interface_error(intf_id_t intf) noexcept :
      error(std::string("No such interface: ") + intf.to_string()), intf_(intf) {

}

no_such_interface_error::no_such_interface_error(
         std::string const & intfName) noexcept :
      error(std::string("Bad interface name: ") + intfName), intf_() {

}


no_such_interface_error::~no_such_interface_error() noexcept {

}

intf_id_t
no_such_interface_error::intf() const noexcept {
   return intf_;
}

void
no_such_interface_error::raise() const {
   throw *this;
}

uint32_t
no_such_interface_error::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
no_such_interface_error::mix_me(hash_mix & h) const {
   h.mix(intf_); // intf_id_t
}

std::string
no_such_interface_error::to_string() const {
   std::ostringstream ss;
   ss << "no_such_interface_error(";
   ss << "intf=" << intf_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const no_such_interface_error& obj) {
   os << obj.to_string();
   return os;
}



not_switchport_eligible_error::not_switchport_eligible_error(intf_id_t intf)
       noexcept :
      
      error(std::string("Interface cannot be used as a switchport: ")
             + intf.to_string()),
      intf_(intf) {

}


not_switchport_eligible_error::~not_switchport_eligible_error() noexcept {

}

intf_id_t
not_switchport_eligible_error::intf() const noexcept {
   return intf_;
}

void
not_switchport_eligible_error::raise() const {
   throw *this;
}

uint32_t
not_switchport_eligible_error::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
not_switchport_eligible_error::mix_me(hash_mix & h) const {
   h.mix(intf_); // intf_id_t
}

std::string
not_switchport_eligible_error::to_string() const {
   std::ostringstream ss;
   ss << "not_switchport_eligible_error(";
   ss << "intf=" << intf_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const not_switchport_eligible_error& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_INTF_H
