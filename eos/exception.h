// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_EXCEPTION_H
#define EOS_EXCEPTION_H

#include <string>

#include <eos/base.h>
#include <eos/eth.h>
#include <eos/intf.h>

#if __cplusplus <= 199711L
#define noexcept throw()
#endif

namespace eos {

/// Base exception type for all SDK-reported exceptions.
class EOS_SDK_PUBLIC error {
 public:
   virtual ~error() noexcept;
   explicit error(std::string const & msg) noexcept;
   std::string msg() const noexcept;
   const char * what() const noexcept;
   virtual void raise() const EOS_SDK_NORETURN = 0;  ///< Throws this exception.

 private:
   std::string msg_;
};

/**
 * Base exception for all cases where an attempt was made to configure
 * the system with completely invalid parameters -- for example, an
 * out-of-range VLAN ID (>4095).
 */
class EOS_SDK_PUBLIC invalid_parameter_error : public error {
  public:
   virtual ~invalid_parameter_error() noexcept;
   explicit invalid_parameter_error(std::string const & parameter_name) noexcept;
   explicit invalid_parameter_error(std::string const & parameter_name,
                                    std::string const & error_details) noexcept;
   virtual void raise() const;  ///< Throws this exception.
   std::string parameter_name() const noexcept;

  private:
   std::string parameter_name_;
};

/// The given parameter was outside of the legal range of values for
/// that parameter (e.g., VLAN IDs must be between 1 and 4094).
class EOS_SDK_PUBLIC invalid_range_error : public invalid_parameter_error {
  public:
   virtual ~invalid_range_error() noexcept;
   explicit invalid_range_error(std::string const & parameter_name,
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

}

#include <eos/inline/exception.h>

#endif // EOS_EXCEPTION_H
