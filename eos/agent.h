// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_AGENT_H
#define EOS_AGENT_H

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>

/**
 * @file
 * EOS Agent handler and agent loop management.
 */

namespace eos {

class agent_mgr;

/**
 * The agent_handler class handles events in the agent's lifecycle.
 */
class EOS_SDK_PUBLIC agent_handler : public base_handler<agent_mgr, agent_handler> {
 public:
   explicit agent_handler(agent_mgr *);

   agent_mgr * get_agent_mgr() const;

   /**
    * Handler called after the agent has been internally initialized.
    *
    * Accessors and mutators (from _mgr classes) should not be called
    * before this event, and other handlers will not fire before this
    * event.
    */
   virtual void on_initialized();
};

class EOS_SDK_PUBLIC agent_mgr : public base_mgr<agent_handler> {
 public:
    virtual ~agent_mgr();

    /**
     * Hands over the main event loop to EOS.
     * Blocks until the event loop stops.
     */
    virtual void main_loop(const char * agent_name, int argc, char ** argv) = 0;

    /// Stop this agent's execution (after the next pass through the event loop)
    void exit();

    /**
     * Given a name, returns a numeric ID uniquely identifying the agent.
     * This number is guaranteed to remain the same across agent restarts,
     * though not across reboots.
     */
    static uint32_t id(const char * agent_name);

 protected:
    agent_mgr() EOS_SDK_PRIVATE;
    friend class agent_handler;
 private:
    EOS_SDK_DISALLOW_COPY_CTOR(agent_mgr);

};

}

#include <eos/inline/agent.h>

#endif // EOS_AGENT_H
