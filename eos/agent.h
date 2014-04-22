// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_AGENT_H
#define EOS_AGENT_H

#include <eos/base.h>

/**
 * @file
 * EOS Agent handler and agent loop management.
 */

namespace eos {

/**
 * The agent_handler class handles events in the agent's lifecycle.
 */
class EOS_SDK_PUBLIC agent_handler {
 public:
   agent_handler();
   virtual ~agent_handler();

   /**
    * Handler called after the agent has been internally initialized.
    *
    * Accessors and mutators (from _mgr classes) should not be called
    * before this event, and other handlers will not fire before this
    * event.
    */
   virtual void on_initialized();
};

class sdk;

/**
 * Hands over the main event loop to EOS.
 * Blocks until the event loop stops.
 */
void EOS_SDK_PUBLIC
agent_main_loop(sdk * sdk, const char * agent_name, int argc, char ** argv);

/// Stop this agent's execution (after the next pass through the event loop)
void EOS_SDK_PUBLIC
agent_exit();

/**
 * Given a name, returns a numeric ID uniquely identifying the agent.
 * This number is guaranteed to remain the same across agent restarts,
 * though not across reboots.
 */
uint32_t EOS_SDK_PUBLIC
agent_id(const char * agent_name);

}

#endif // EOS_AGENT_H
