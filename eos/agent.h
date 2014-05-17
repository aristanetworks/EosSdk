// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_AGENT_H
#define EOS_AGENT_H

#include <string>

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

   /**
    * Handler called when the agent has been enabled/disabled.
    *
    * The default implementation will synchronously call the
    * agent_mgr's agent_shutdown_complete method. If you override
    * on_agent_enabled, then you are also responsible for calling
    * agent_shutdown_complete.
    * 
    */
   virtual void on_agent_enabled(bool enabled);

   /**
    * Handler called when the configuration options of the agent
    * have changed.
    */
   virtual void on_agent_option(std::string const & name, std::string const & value);
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

    /**
     * Return whether the agent is enabled or not.
     *
     * When enabled is false, the agent is responsible for cleaning
     * itself up as necessary and then calling running_is(false).
     */
    virtual bool enabled() const = 0;

    /**
     * Get the configured value for the given agent option.
     *
     * If no value has been set for the option, the empty string is
     * returned.
     */
    virtual std::string agent_option(std::string const & name) const = 0;

    /**
     * Called when agent graceful shutdown has successfully completed.
     *
     * If the agent requires special handling to cleanup state when
     * the agent is disabled, then an agent_handler must be created
     * that overrides the on_agent_enabled method and appropriately
     * cleans up when the agent is disabled. Once the agent is
     * ready to be killed, it must call agent_shutdown_complete,
     * after which it will be killed by ProcMgr.
     * 
     * This method is called automatically by the default implementation
     * of on_agent_enabled when the agent is disabled. If no special
     * cleanup handling is required, then simply do not override
     * on_agent_enabled and the agent will be killed by ProcMgr as
     * soon as it is administratively disabled.
     */
    virtual void agent_shutdown_complete() = 0;

 protected:
    agent_mgr() EOS_SDK_PRIVATE;
    friend class agent_handler;
 private:
    EOS_SDK_DISALLOW_COPY_CTOR(agent_mgr);

};

}

#include <eos/inline/agent.h>

#endif // EOS_AGENT_H
