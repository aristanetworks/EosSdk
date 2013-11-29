// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INTF_H
#define EOS_INTF_H

#include <stddef.h>
#include <eos/types.h>
#include <Arnet/IntfId.h> //= eos_internal
#include <Intf/Intf.h> //= eos_internal

namespace eos {

static const int INTF_NAME_MAX = 64;

typedef enum oper_status_e {
   INTF_OPER_NULL,
   INTF_OPER_UP,
   INTF_OPER_DOWN
} oper_status_t;


/* Unique identifier for an interface. */
class intf_id_t {
 public:
   // Default 'falsy' constructor' //= hide
   intf_id_t();
   // Constructor based on internal id representation
   explicit intf_id_t(uint32_t);
   // Constructor based on an interface name, i.e. 'Ethernet3/1', or 'Management1'
   explicit intf_id_t(char const *name);

   bool operator !() const;
   bool is_null0() const;

   size_t to_string(char * namebuf, size_t namebuf_size) const;
   // string to_string() const;  //= eos_internal

   bool operator==(intf_id_t const & other);
   bool operator!=(intf_id_t const & other);
   
//= hidden
   void validate();
   bool valid() const;

   Arnet::IntfId intfId_;
//= end_hidden
 //=> private:
   //=> uint32_t intfId_;

};


/* This class handles changes to base interface attributes. */
class intf_handler {
 public:
   intf_handler();
   ~intf_handler();

   // Registers this class to receive updates on changes to the
   // interface. Expects a boolean signifying whether notifications
   // should be propagated to this instance or not.
   void watch_all_intfs( bool );
   // void watch_intf( intf_id_t, bool ); //= hide

   // Called after this instance has been internally inialized and is
   // ready to start receiving notifications.
   virtual void on_initialized();
   // Handler called when a new interface is created.
   virtual void on_create(intf_id_t);
   // Handler called when an interface has been removed.
   virtual void on_delete(intf_id_t);
   // Handler called when the operational status of an interface changes.
   virtual void on_oper_status(intf_id_t, oper_status_t);
   // Handler called after an interface has been configured to be enabled.
   virtual void on_admin_enabled(intf_id_t, bool);

 private:
   bool watching_all_intfs_;
};

/* This class inspects and configures base interface attribtues */
class intf_mgr {
 public:
   /* Collection management */
   // Iterator that, for each interface, call the supplied handler callback with the
   // corresponding intf_id_t and arg. If callback returns false, we
   // stop iteration.
   void intf_foreach(bool (*handler)(intf_id_t, void *), void *);
   // Iterator that starts at the first element after the bookmark's position
   void intf_foreach(bool (*handler)(intf_id_t, void *), void *,
                          intf_id_t bookmark);
   // Returns true if the intf_id_t has a corresponding status.
   bool exists(intf_id_t);

   // Attribute accessors
//= hidden
   // NOT IMPLEMENTED:
   // Returns true if the given interface is configured to be enabled
   bool admin_enabled(intf_id_t);
   // Configure the enabled status of the interface
   void admin_enabled_is(intf_id_t, bool);
//= end_hidden
   // Configure the description of the given interface. Creates a
   // copy of the passed in string description.
   void description_is(intf_id_t, char const *);
   // Inspect the curren operational status of the given interface.
   oper_status_t oper_status(intf_id_t);

//= hidden
   // Trampoline methods for calling the associated methods
   // on all handlers
   void on_create(intf_id_t);
   void on_delete(intf_id_t);
   void on_oper_status(intf_id_t, Interface::IntfOperStatus);
   void on_admin_enabled(intf_id_t, bool);
//= end_hidden

 //=> private:
   intf_mgr();

 private:
   intf_mgr(intf_mgr const &);
};

intf_mgr * get_intf_mgr();

};

#endif // EOS_INTF_H
