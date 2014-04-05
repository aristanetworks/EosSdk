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

inline std::string
error::msg() const noexcept {
   return msg_;
}

inline const char *
error::what() const noexcept {
   return msg_.c_str();
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

}

#endif // EOS_INLINE_EXCEPTION_H
