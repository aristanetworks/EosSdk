// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_EXCEPTION_H
#define EOS_EXCEPTION_H

#include <string>

#include <eos/base.h>
#include <eos/eth.h>
#include <eos/intf.h>
#include <eos/policy_map.h>

#if __cplusplus <= 199711L
#define noexcept throw()
#endif

namespace eos {

/// Base exception type for all SDK-reported exceptions.
class EOS_SDK_PUBLIC error {
 public:
   virtual ~error() noexcept;
   explicit error(std::string const & msg) noexcept;
   std::string const & msg() const noexcept;
   const char * what() const noexcept;
   virtual void raise() const EOS_SDK_NORETURN = 0;  ///< Throws this exception.

 private:
   std::string msg_;
};

/**
 * Base exception for all cases where an attempt was made to configure
 * the system with completely invalid arguments -- for example, an
 * out-of-range VLAN ID (>4095).
 */
class EOS_SDK_PUBLIC invalid_argument_error : public error {
  public:
   virtual ~invalid_argument_error() noexcept;
   explicit invalid_argument_error(std::string const & argument_name) noexcept;
   explicit invalid_argument_error(std::string const & argument_name,
                                    std::string const & error_details) noexcept;
   virtual void raise() const;  ///< Throws this exception.
   std::string argument_name() const noexcept;

  private:
   std::string argument_name_;
};

/// The given argument was outside of the legal range of values for
/// that argument (e.g., VLAN IDs must be between 1 and 4094).
class EOS_SDK_PUBLIC invalid_range_error : public invalid_argument_error {
  public:
   virtual ~invalid_range_error() noexcept;
   explicit invalid_range_error(std::string const & argument_name,
                                uint32_t min_valid, uint32_t max_valid) noexcept;
   virtual void raise() const;  ///< Throws this exception.
   uint32_t min_valid() const noexcept;
   uint32_t max_valid() const noexcept;

  private:
   uint32_t min_valid_;
   uint32_t max_valid_;
};

/// Tried to access a non-existent interface.
class EOS_SDK_PUBLIC no_such_interface_error : public error {
 public:
   virtual ~no_such_interface_error() noexcept;
   explicit no_such_interface_error(intf_id_t intf) noexcept;
   explicit no_such_interface_error(std::string const & intfName) noexcept;
   virtual void raise() const;  ///< Throws this exception.
   intf_id_t intf() const noexcept;

 private:
   intf_id_t intf_;
};

/**
 * Base exception type for all cases where the configuration requested could
 * not be accepted because it's impossible or invalid.
 *
 * The configuration may be invalid because of other conflicting
 * configuration.  For instance if a VLAN ID is already used as
 * an internal VLAN on a routed port, trying to manually configure
 * this VLAN ID on a trunk port would fail until the requested VLAN
 * ID is no longer used as an internal VLAN on the routed port.
 */
class EOS_SDK_PUBLIC configuration_error : public error {
 public:
   virtual ~configuration_error() noexcept;
   explicit configuration_error(std::string const & msg) noexcept;
   virtual void raise() const;  ///< Throws this exception.
};

/// Tried to configure an interface as a routed port that cannot be a routed port.
class EOS_SDK_PUBLIC not_switchport_eligible_error : public error {
 public:
   virtual ~not_switchport_eligible_error() noexcept;
   explicit not_switchport_eligible_error(intf_id_t intf) noexcept;
   virtual void raise() const;  ///< Throws this exception.
   intf_id_t intf() const noexcept;

 private:
   intf_id_t intf_;
};

/// The given VLAN number was invalid (for example 0 or 4095).
class EOS_SDK_PUBLIC invalid_vlan_error : public error {
 public:
   virtual ~invalid_vlan_error() noexcept;
   explicit invalid_vlan_error(vlan_id_t vlan) noexcept;
   virtual void raise() const;  ///< Throws this exception.
   vlan_id_t vlan() const noexcept;

 private:
   vlan_id_t vlan_;
};

/// Tried to configure an internal VLAN on a trunk port.
class EOS_SDK_PUBLIC internal_vlan_error : public configuration_error {
 public:
   virtual ~internal_vlan_error() noexcept;
   explicit internal_vlan_error(vlan_id_t vlan) noexcept;
   virtual void raise() const;  ///< Throws this exception.
   vlan_id_t vlan() const noexcept;

 private:
   vlan_id_t vlan_;
};

/// The given address with mask overlaps with another configured address
class EOS_SDK_PUBLIC address_overlap_error : public configuration_error {
 public:
   virtual ~address_overlap_error() noexcept;
   explicit address_overlap_error(ip_addr_mask_t const & addr) noexcept;
   virtual void raise() const;  ///< Throws this exception.
   ip_addr_mask_t addr() const noexcept;

 private:
   ip_addr_mask_t addr_;
};

/// The given agent has not been configured
class EOS_SDK_PUBLIC unconfigured_agent_error : public configuration_error {
 public:
   virtual ~unconfigured_agent_error() noexcept;
   explicit unconfigured_agent_error(std::string const & agent_name) noexcept;
   virtual void raise() const;  ///< Throws this exception.
   std::string agent_name() const noexcept;

 private:
   std::string agent_name_;
};

/// Base class for "unsupported" errors
class EOS_SDK_PUBLIC unsupported_error : public error {
 public:
   virtual ~unsupported_error() noexcept;
   explicit unsupported_error(std::string const & msg) noexcept;
   virtual void raise() const;  ///< Throws this exception.

 private:
   std::string msg_;
};

/// The policy feature requested is unavailable in this SDK release
class EOS_SDK_PUBLIC unsupported_policy_feature_error : public unsupported_error {
 public:
   virtual ~unsupported_policy_feature_error() noexcept;
   explicit unsupported_policy_feature_error(policy_feature_t) noexcept;
   virtual void raise() const;  ///< Throws this exception.
   policy_feature_t policy_feature() const noexcept;

 private:
   policy_feature_t policy_feature_;
};

}

#include <eos/inline/exception.h>

#endif // EOS_EXCEPTION_H
