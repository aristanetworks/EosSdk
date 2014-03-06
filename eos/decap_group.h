// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_DECAP_GROUP_H
#define EOS_DECAP_GROUP_H

#include <string>

#include <eos/base.h>
#include <eos/ip.h>
#include <eos/iterator.h>

namespace eos {

/**
 * Inner (IP) protocol to match for a decap group.
 *
 * Only the GRE protocol is presently supported
 */
enum decap_protocol_type_t {
   PROTOCOL_TYPE_NULL,
   PROTOCOL_TYPE_GRE,
};

/**
 * An 'ip decap-group' configuration model.
 *
 * Note that once created, the group_name member cannot be changed
 */
class EOS_SDK_PUBLIC decap_group_t {
 public:
   decap_group_t();  // default constructor, sets NULL protocol type
   decap_group_t(std::string group_name, ip_addr_t const &, decap_protocol_type_t);

   bool operator==(decap_group_t const & other) const;
   bool operator!=(decap_group_t const & other) const;

   std::string group_name() const;
   ip_addr_t const & destination_addr() const;
   void destination_addr_is(ip_addr_t const &);
   decap_protocol_type_t protocol_type() const;
   void protocol_type_is(decap_protocol_type_t);

   bool persistent() const;
   void persistent_is(bool);
 private:
   // The decap-group name, must be supplied.  Note that the decap
   // group namespace is per-VRF, that is, the vrf_name scopes the
   // decap-group name
   std::string group_name_;

   ip_addr_t destination_addr_;  // Match destination IP on the outermost IP header
   decap_protocol_type_t protocol_type_;  // Match this outer IP protocol to decap

   bool persistent_; // If true, the decap group is stored in the startup-config
};

class decap_group_iter_impl;

class EOS_SDK_PUBLIC decap_group_iter_t : public iter_base<decap_group_t,
                                                           decap_group_iter_impl> {
 private:
   friend class decap_group_iter_impl;
   explicit decap_group_iter_t(decap_group_iter_impl * const) EOS_SDK_PRIVATE;
};

/**
 * A manager of 'ip decap-group' configurations.
 *
 * Create one of these via eos::get_decap_group_mgr() prior to
 * starting the agent main loop. When your eos::agent_handler::on_initialized
 * virtual function is called, the manager is valid for use.
 */
class EOS_SDK_PUBLIC decap_group_mgr {
 public:
   void resync_init();
   void resync_complete();

   /**
    * Iterates over all the decap groups currently configured.
    */
   decap_group_iter_t decap_group_iter() const;
   // The decap_group_foreach methods are deprecated and will be
   // removed in the future.
   typedef bool (*callback_func_decap_group)(decap_group_t const &, void * context);
   void decap_group_foreach(callback_func_decap_group handler, void * context);
   void decap_group_foreach(callback_func_decap_group handler, void * context,
                            decap_group_t const &bookmark);

   /**
    * Adds the specified decap group to the system configuration
    * Create a new or updates an existing decap group with the same name
    */
   void decap_group_set(decap_group_t const &);
   /// Removes the named decap group from the configuration if it exists
   void decap_group_del(std::string const & decap_group_name);
 protected:
   decap_group_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(decap_group_mgr);
};

decap_group_mgr * get_decap_group_mgr() EOS_SDK_PUBLIC;

}

#include <eos/inline/decap_group.h>

#endif // EOS_DECAP_GROUP_H
