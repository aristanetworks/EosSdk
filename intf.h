// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INTF_H
#define EOS_INTF_H

#include <stddef.h>
#include <eos/types.h>
#include <Arnet/IntfId.h> //= eos_internal

namespace eos {

static const int INTF_NAME_MAX = 64;

typedef enum oper_status_e {
   INTF_OPER_NULL,
   INTF_OPER_UP,
   INTF_OPER_DOWN
} oper_status_t;


class intf_id_t {
 public:
   intf_id_t();
   explicit intf_id_t(uint32_t);
   explicit intf_id_t(char const *name);

   bool operator !() const;

   bool is_null0() const;

   size_t to_string(char * namebuf, size_t namebuf_size) const;
   // string to_string() const;  //= eos_internal

   // explicit operator==(intf_id_t const & other);
   // explicit operator!=(intf_id_t const & other);
//= hidden
   void validate();
   bool valid() const;

   Arnet::IntfId intfId_;
//= end_hidden
 //=> private:
   //=> uint32_t intfId_;

};


class intf_handler {
 public:
   virtual void on_initialized() {}
   virtual void on_create(intf_id_t) {}
   virtual void on_delete(intf_id_t) {}
   virtual void on_oper_status(intf_id_t, oper_status_t) {}
   virtual void on_admin_enabled(intf_id_t, bool) {}
};


class intf_mgr {
 public:
   // Reactor registration
   void add_handler(intf_handler *); // handles all interfaces
   void remove_handler(intf_handler *);
   void add_handler(intf_id_t, intf_handler *); // handle given interface
   void remove_handler(intf_id_t, intf_handler *);

   // Collection management
   void intf_foreach(bool (*handler)(intf_id_t, void *), void *);
   void intf_foreach(bool (*handler)(intf_id_t, void *), void *,
                          intf_id_t bookmark);
   bool exists(intf_id_t);

   // Attribute accessors
   bool admin_enabled(intf_id_t);
   void admin_enabled_is(intf_id_t, bool);
   void description_is(intf_id_t, char const *);
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
