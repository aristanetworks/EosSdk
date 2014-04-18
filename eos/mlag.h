// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_MLAG_H
#define EOS_MLAG_H

#include <eos/base.h>
#include <eos/base_mgr.h>
#include <eos/ip.h>

namespace eos {

enum mlag_state_t {
   MLAG_STATE_UNKNOWN,
   MLAG_STATE_DISABLED,
   MLAG_STATE_INACTIVE,
   MLAG_STATE_PRIMARY,
   MLAG_STATE_SECONDARY,
};

class mlag_mgr;

class EOS_SDK_PUBLIC mlag_handler {
 public:
   mlag_handler(mlag_mgr *mgr);
   virtual ~mlag_handler();

   virtual void on_mlag_state(mlag_state_t);
   
 protected:
   mlag_mgr *mlag_mgr_;
};

class EOS_SDK_PUBLIC mlag_mgr : protected base_mgr<mlag_handler> {
 public:
   virtual ~mlag_mgr();
   
   /// Returns whether or not MLAG is configured on this system
   virtual bool enabled() const = 0;
   /// Configures whether MLAG is enabled
   virtual void enabled_is(bool) = 0;
   
   /// Returns the configured IP address of our MLAG peer
   virtual ip_addr_t peer_address() const = 0;

   /// Returns the current operational state of our MLAG relationship
   virtual mlag_state_t state() const = 0;

 protected:
   mlag_mgr() EOS_SDK_PRIVATE;
   friend class mlag_handler;
   
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(mlag_mgr);
};

}

#endif // EOS_MLAG_H
