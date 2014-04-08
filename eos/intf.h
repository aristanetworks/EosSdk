// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INTF_H
#define EOS_INTF_H

#include <string>
#include <stddef.h>

#include <eos/base.h>
#include <eos/iterator.h>

/**
 * Base interface types.
 *
 * A base interface contains non-media or interface type specific information.
 * Also included in this module is the interface ID type intf_id_t, used
 * to uniquely identify any interface in the system of any type, as well as
 * common enumerates.
 */

namespace eos {

/// The operational status of an interface
enum oper_status_t {
   INTF_OPER_NULL,
   INTF_OPER_UP,
   INTF_OPER_DOWN,
};

/// The interface's type
enum intf_type_t {
   INTF_TYPE_NULL,
   INTF_TYPE_OTHER,
   INTF_TYPE_ETH,
   INTF_TYPE_VLAN,
   INTF_TYPE_MANAGEMENT,
   INTF_TYPE_LOOPBACK,
   INTF_TYPE_LAG,
   INTF_TYPE_NULL0,
};

/// Unique identifier for an interface.
class EOS_SDK_PUBLIC intf_id_t {
 public:
   /// Default constructor
   intf_id_t();
   // Copy constructor and assignment operator implicitly declared.

   /// Constructor based on an interface name, i.e. 'Ethernet3/1', or 'Management1'
   explicit intf_id_t(char const * name);
   /// Constructor based on an interface name, i.e. 'Ethernet3/1', or 'Management1'
   explicit intf_id_t(std::string const & name);

   /// Returns true if the interface is Null0
   bool is_null0() const;
   /// Returns the interface's type
   intf_type_t intf_type() const;

   /// Returns the interface name as a string, e.g., 'Ethernet3/1'
   std::string to_string() const;

   // Only the "default interface" provided by the default constructor
   // evaluates to false.
   bool operator!() const;
   bool operator==(intf_id_t const & other) const;
   bool operator!=(intf_id_t const & other) const;
   bool operator<(intf_id_t const & other) const;

 private:
   friend struct IntfIdHelper;
   uint64_t intfId_;
 public:  // Not part of the public API.
   /// Constructor based on internal id representation
   explicit intf_id_t(uint64_t) EOS_SDK_INTERNAL;
};


/// This class receives changes to base interface attributes.
class EOS_SDK_PUBLIC intf_handler {
 public:
   intf_handler();
   virtual ~intf_handler();

   /**
    * Registers this class to receive change updates on the interface.
    *
    * Expects a boolean signifying whether notifications should be
    * propagated to this instance or not.
    */
   void watch_all_intfs(bool);

  /**
    * Registers this class to receive change updates on the given interface.
    *
    * Expects the id of the corresponding interface and a boolean signifying whether
    * notifications should be propagated to this instance or not.
    */
   void watch_intf(intf_id_t, bool);

   /// Handler called when a new interface is created.
   virtual void on_intf_create(intf_id_t);
   /// Handler called when an interface has been removed.
   virtual void on_intf_delete(intf_id_t);
   /// Handler called when the operational status of an interface changes.
   virtual void on_oper_status(intf_id_t, oper_status_t);
   /// Handler called after an interface has been configured to be enabled.
   virtual void on_admin_enabled(intf_id_t, bool);
};


class intf_iter_impl;

/// An interface iterator
class EOS_SDK_PUBLIC intf_iter_t : public iter_base<intf_id_t,
                                                    intf_iter_impl> {
 private:
   friend class intf_iter_impl;
   explicit intf_iter_t(intf_iter_impl * const) EOS_SDK_PRIVATE;
};


/**
 * The interface manager.
 * This class inspects and configures base interface attribtues.
 */
class EOS_SDK_PUBLIC intf_mgr {
 public:
   /// Iterates over all interfaces currently available in the system.
   intf_iter_t intf_iter() const;
   /* Collection management */
   typedef bool (*callback_func_intf)(intf_id_t, void * context);
   /**
    * An iterator that for each interface, calls the handler with an interface ID.
    * Also passed is a pointer to a context managed by the application.
    * If callback returns false, we stop iteration.
    * @deprecated Use intf_iter() instead.
    */
   void intf_foreach(callback_func_intf handler, void *context)
      EOS_SDK_DEPRECATED;
   /// Iterator that starts at the first element after the bookmark's position
   /// @deprecated Use intf_iter() instead.
   void intf_foreach(callback_func_intf handler, void *context,
                          intf_id_t bookmark)
      EOS_SDK_DEPRECATED;
   /// Returns true if the intf_id_t has a corresponding status.
   bool exists(intf_id_t) const;

   // Attribute accessors
   /// Returns true if the given interface is configured to be enabled
   bool admin_enabled(intf_id_t) const;
   /// Configures the enabled status of the interface
   void admin_enabled_is(intf_id_t, bool);
   /**
    * Configure the description of the given interface.
    * Creates a copy of the passed in string description.
    */
   void description_is(intf_id_t, char const *);
   /// Inspects the curren operational status of the given interface.
   oper_status_t oper_status(intf_id_t) const;

 protected:
   intf_mgr() EOS_SDK_PRIVATE;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(intf_mgr);
};

/// Returns the base interface manager.
intf_mgr * get_intf_mgr() EOS_SDK_PUBLIC;

}

#include <eos/inline/intf.h>

#endif // EOS_INTF_H
