// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ETH_LAG_INTF_H
#define EOS_INLINE_TYPES_ETH_LAG_INTF_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const eth_lag_intf_fallback_type_t & enum_val) {
   if (enum_val==ETH_LAG_INTF_FALLBACK_NULL) {
      os << "ETH_LAG_INTF_FALLBACK_NULL";
   } else if (enum_val==ETH_LAG_INTF_FALLBACK_NONE) {
      os << "ETH_LAG_INTF_FALLBACK_NONE";
   } else if (enum_val==ETH_LAG_INTF_FALLBACK_STATIC) {
      os << "ETH_LAG_INTF_FALLBACK_STATIC";
   } else if (enum_val==ETH_LAG_INTF_FALLBACK_INDIVIDUAL) {
      os << "ETH_LAG_INTF_FALLBACK_INDIVIDUAL";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os,
           const eth_lag_intf_fallback_timeout_default_t & enum_val) {
   if (enum_val==ETH_LAG_INTF_FALLBACK_TIMEOUT_DEFAULT) {
      os << "ETH_LAG_INTF_FALLBACK_TIMEOUT_DEFAULT";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const eth_lag_intf_member_priority_t & enum_val) {
   if (enum_val==ETH_LAG_INTF_PORT_PRIORITY_DEFAULT) {
      os << "ETH_LAG_INTF_PORT_PRIORITY_DEFAULT";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const eth_lag_intf_member_lacp_mode_t & enum_val) {
   if (enum_val==ETH_LAG_INTF_MEMBER_LACP_MODE_NULL) {
      os << "ETH_LAG_INTF_MEMBER_LACP_MODE_NULL";
   } else if (enum_val==ETH_LAG_INTF_MEMBER_LACP_MODE_OFF) {
      os << "ETH_LAG_INTF_MEMBER_LACP_MODE_OFF";
   } else if (enum_val==ETH_LAG_INTF_MEMBER_LACP_MODE_PASSIVE) {
      os << "ETH_LAG_INTF_MEMBER_LACP_MODE_PASSIVE";
   } else if (enum_val==ETH_LAG_INTF_MEMBER_LACP_MODE_ACTIVE) {
      os << "ETH_LAG_INTF_MEMBER_LACP_MODE_ACTIVE";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const eth_lag_intf_member_lacp_timeout_t & enum_val) {
   if (enum_val==ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_NULL) {
      os << "ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_NULL";
   } else if (enum_val==ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_SHORT) {
      os << "ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_SHORT";
   } else if (enum_val==ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_LONG) {
      os << "ETH_LAG_INTF_MEMBER_LACP_TIMEOUT_LONG";
   } else {
      os << "Unknown value";
   }
   return os;
}


// Default constructor.
eth_lag_intf_membership_t::eth_lag_intf_membership_t() {
   pimpl = std::shared_ptr<eth_lag_intf_membership_impl_t>(
      new eth_lag_intf_membership_impl_t()
   );
}
eth_lag_intf_membership_t::eth_lag_intf_membership_t(
         intf_id_t eth_lag_intf_id, bool active, std::string const & reason,
         double member_time, eth_lag_intf_member_lacp_mode_t mode) {
   pimpl = std::shared_ptr<eth_lag_intf_membership_impl_t>(
      new eth_lag_intf_membership_impl_t(
         eth_lag_intf_id,
         active,
         reason,
         member_time,
         mode
      )
   );
}
eth_lag_intf_membership_t::eth_lag_intf_membership_t(
   const eth_lag_intf_membership_t& other)
{
   pimpl = std::make_unique<eth_lag_intf_membership_impl_t>(
      eth_lag_intf_membership_impl_t(*other.pimpl));
}
eth_lag_intf_membership_t&
eth_lag_intf_membership_t::operator=(
   eth_lag_intf_membership_t const & other)
{
   pimpl = std::shared_ptr<eth_lag_intf_membership_impl_t>(
      new eth_lag_intf_membership_impl_t(*other.pimpl));
   return *this;
}

intf_id_t
eth_lag_intf_membership_t::eth_lag_intf_id() const {
   return pimpl->eth_lag_intf_id();
}
void
eth_lag_intf_membership_t::eth_lag_intf_id_is(intf_id_t eth_lag_intf_id) {
   pimpl->eth_lag_intf_id_is(eth_lag_intf_id);
}
bool
eth_lag_intf_membership_t::active() const {
   return pimpl->active();
}
std::string
eth_lag_intf_membership_t::reason() const {
   return pimpl->reason();
}
void
eth_lag_intf_membership_t::reason_is(std::string const & reason) {
   pimpl->reason_is(reason);
}
double
eth_lag_intf_membership_t::member_time() const {
   return pimpl->member_time();
}
eth_lag_intf_member_lacp_mode_t
eth_lag_intf_membership_t::mode() const {
   return pimpl->mode();
}
bool
eth_lag_intf_membership_t::operator==(eth_lag_intf_membership_t const & other)
       const {
   return pimpl->operator==(*other.pimpl);
}
bool
eth_lag_intf_membership_t::operator!=(eth_lag_intf_membership_t const & other)
       const {
   return pimpl->operator!=(*other.pimpl);
}
bool
eth_lag_intf_membership_t::operator<(eth_lag_intf_membership_t const & other)
       const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
eth_lag_intf_membership_t::hash() const {
   return pimpl->hash();
}
void
eth_lag_intf_membership_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
eth_lag_intf_membership_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const eth_lag_intf_membership_t& obj) {
   return operator<<(os, *obj.pimpl);
}


// Default constructor.
eth_lag_intf_t::eth_lag_intf_t() {
   pimpl = std::shared_ptr<eth_lag_intf_impl_t>(
      new eth_lag_intf_impl_t()
   );
}
eth_lag_intf_t::eth_lag_intf_t(intf_id_t intf) {
   pimpl = std::shared_ptr<eth_lag_intf_impl_t>(
      new eth_lag_intf_impl_t(
         intf
      )
   );
}
eth_lag_intf_t::eth_lag_intf_t(intf_id_t intf, uint32_t min_links,
                                      uint64_t speed,
                                      eth_lag_intf_fallback_type_t fallback_type,
                                      uint16_t fallback_timeout) {
   pimpl = std::shared_ptr<eth_lag_intf_impl_t>(
      new eth_lag_intf_impl_t(
         intf,
         min_links,
         speed,
         fallback_type,
         fallback_timeout
      )
   );
}
eth_lag_intf_t::eth_lag_intf_t(
   const eth_lag_intf_t& other)
{
   pimpl = std::make_unique<eth_lag_intf_impl_t>(
      eth_lag_intf_impl_t(*other.pimpl));
}
eth_lag_intf_t&
eth_lag_intf_t::operator=(
   eth_lag_intf_t const & other)
{
   pimpl = std::shared_ptr<eth_lag_intf_impl_t>(
      new eth_lag_intf_impl_t(*other.pimpl));
   return *this;
}

intf_id_t
eth_lag_intf_t::intf() const {
   return pimpl->intf();
}
uint64_t
eth_lag_intf_t::speed() const {
   return pimpl->speed();
}
uint32_t
eth_lag_intf_t::min_links() const {
   return pimpl->min_links();
}
eth_lag_intf_fallback_type_t
eth_lag_intf_t::fallback_type() const {
   return pimpl->fallback_type();
}
uint16_t
eth_lag_intf_t::fallback_timeout() const {
   return pimpl->fallback_timeout();
}
uint16_t
eth_lag_intf_t::fallback_timeout_default() const {
   return pimpl->fallback_timeout_default();
}
bool
eth_lag_intf_t::operator==(eth_lag_intf_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
eth_lag_intf_t::operator!=(eth_lag_intf_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
eth_lag_intf_t::operator<(eth_lag_intf_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
eth_lag_intf_t::hash() const {
   return pimpl->hash();
}
void
eth_lag_intf_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
eth_lag_intf_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const eth_lag_intf_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_ETH_LAG_INTF_H
