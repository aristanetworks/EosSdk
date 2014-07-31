// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_DECAP_GROUP_H
#define EOS_DECAP_GROUP_H

#include <string>

#include <eos/base.h>
#include <eos/ip.h>
#include <eos/iterator.h>

#include <eos/types/decap_group.h>

namespace eos {

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
 * Create one of these via sdk object prior to starting the agent main loop. When
 * your eos::agent_handler::on_initialized virtual function is called, the manager
 * is valid for use.
 */
class EOS_SDK_PUBLIC decap_group_mgr {
 public:
   virtual ~decap_group_mgr();

   virtual void resync_init() = 0;
   virtual void resync_complete() = 0;

   /**
    * Iterates over all the decap groups currently configured.
    */
   virtual decap_group_iter_t decap_group_iter() const = 0;

   /**
    * Adds the specified decap group to the system configuration
    * Create a new or updates an existing decap group with the same name
    */
   virtual void decap_group_set(decap_group_t const &) = 0;
   /// Removes the named decap group from the configuration if it exists
   virtual void decap_group_del(std::string const & decap_group_name) = 0;
 protected:
   decap_group_mgr() EOS_SDK_PRIVATE;
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(decap_group_mgr);
};

}

#endif // EOS_DECAP_GROUP_H
