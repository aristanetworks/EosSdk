// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_EXCEPTION_H
#define EOS_INLINE_EXCEPTION_H

namespace eos {

inline
error::error(std::string const & msg) noexcept : msg_(msg) {
}

inline
error::~error() noexcept {
}

inline std::string const &
error::msg() const noexcept {
   return msg_;
}

inline const char *
error::what() const noexcept {
   return msg_.c_str();
}

inline
invalid_argument_error::~invalid_argument_error() noexcept {
}

inline void
invalid_argument_error::raise() const {
   throw *this;
}

inline std::string
invalid_argument_error::argument_name() const noexcept {
   return argument_name_;
}

inline
invalid_range_error::~invalid_range_error() noexcept {
}

inline void
invalid_range_error::raise() const {
   throw *this;
}

inline uint32_t
invalid_range_error::min_valid() const noexcept {
   return min_valid_;
}

inline uint32_t
invalid_range_error::max_valid() const noexcept {
   return max_valid_;
}

inline
no_such_interface_error::~no_such_interface_error() noexcept {
}

inline void
no_such_interface_error::raise() const {
   throw *this;
}

inline intf_id_t
no_such_interface_error::intf() const noexcept {
   return intf_;
}

inline
configuration_error::configuration_error(std::string const & name) noexcept
   : error(name) {
}

inline
configuration_error::~configuration_error() noexcept {
}

inline void
configuration_error::raise() const {
   throw *this;
}

inline
not_switchport_eligible_error::~not_switchport_eligible_error() noexcept {
}

inline void
not_switchport_eligible_error::raise() const {
   throw *this;
}

inline intf_id_t
not_switchport_eligible_error::intf() const noexcept {
   return intf_;
}

inline
invalid_vlan_error::~invalid_vlan_error() noexcept {
}

inline void
invalid_vlan_error::raise() const {
   throw *this;
}

inline vlan_id_t
invalid_vlan_error::vlan() const noexcept {
   return vlan_;
}

inline
internal_vlan_error::~internal_vlan_error() noexcept {
}

inline void
internal_vlan_error::raise() const {
   throw *this;
}

inline vlan_id_t
internal_vlan_error::vlan() const noexcept {
   return vlan_;
}

inline address_overlap_error::~address_overlap_error() noexcept {
}

inline void address_overlap_error::raise() const {
   throw *this;
}

inline ip_addr_mask_t address_overlap_error::addr() const noexcept {
   return addr_;
}

inline unconfiged_agent_error::~unconfiged_agent_error() noexcept {
}

inline void unconfiged_agent_error::raise() const {
   throw *this;
}

inline std::string unconfiged_agent_error::agentName() const noexcept {
   return agentName_;
}

inline
unsupported_error::unsupported_error(std::string const & msg) noexcept : error(msg) {
}

inline
unsupported_error::~unsupported_error() noexcept {
}

inline void
unsupported_error::raise() const {
   throw *this;
}

inline
unsupported_policy_feature_error::~unsupported_policy_feature_error() noexcept {
}

inline void
unsupported_policy_feature_error::raise() const {
   throw *this;
}

inline policy_feature_t
unsupported_policy_feature_error::policy_feature() const noexcept {
   return policy_feature_;
}

}

#endif // EOS_INLINE_EXCEPTION_H
