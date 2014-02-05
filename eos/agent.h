// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_AGENT_H
#define EOS_AGENT_H

#include <eos/base.h>

namespace eos {

/* This class handles events in the agent's lifecycle. */
class EOS_SDK_PUBLIC agent_handler {
 public:
   agent_handler();
   virtual ~agent_handler();

   // Called after the agent has been internally
   // initialized. Accessors and mutators (from _mgr classes) should
   // not be called before this event, and other handlers will not
   // fire before this event.
   virtual void on_initialized();
};

// Handover the main event loop to EOS
void EOS_SDK_PUBLIC
agent_main_loop(const char * agent_name, int argc, char ** argv);

}

#endif // EOS_AGENT_H
