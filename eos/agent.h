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
 *
 * The agent_handler and agent_mgr provide a means to manage the agent
 * process lifecycle as managed by EOS' ProcMgr/Launcher
 * infrastructure, including any agent specific cleanup that must be
 * performed prior to ProcMgr terminating the agent when it is disabled.
 *
 * After ProcMgr tells Launcher to start the agent, if the agent is
 * configured to shutdown in EOS, the on_agent_enabled function of
 * agent_handler is called with false. In reaction to this call, if
 * your agent has resources (such as files or sockets) to close prior
 * to being terminated, you must override the implementation of
 * on_agent_enabled() to perform this cleanup. After cleanup, from
 * on_agent_enabled call the agent_mgr function
 * agent_shutdown_complete_is(true) to signal to ProcMgr that your
 * process is finished and can be terminated.
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
     * Return agent name that has been passed to main_loop().
     */
    virtual std::string agent_name() const = 0;

    /**
     * Return whether the agent is enabled or not.
     *
     * When enabled is false, as reported by the agent_handler's
     * on_agent_enabled() callback, the agent is responsible for
     * cleaning itself up as necessary and then calling
     * agent_shutdown_complete_is(false).
     */
    virtual bool enabled() const = 0;

    /**
     * Get the configured value for the given agent option.
     *
     * If no value has been set for the option, the empty string is
     * returned.
     */
    virtual std::string agent_option(std::string const & name) const = 0;

    /// Store custom agent status mapped to the given key
    virtual void status_set(std::string const & key,
                            std::string const & value) = 0;
    /// Delete the stored agent status with the given key
    virtual void status_del(std::string const & key) = 0;

    /**
     * Get the status value stored by the agent under the given key.
     *
     * If no value has been stored under the given key, the empty
     * string is returned.
     */
    virtual std::string status(std::string const & key) const = 0;

    /**
     * Called when agent graceful shutdown has successfully completed.
     *
     * If the agent requires special handling to cleanup state when
     * the agent is disabled, then an agent_handler must be created
     * that overrides the on_agent_enabled method and appropriately
     * cleans up when the agent is disabled. Once the agent is
     * ready to be killed, it must call agent_shutdown_complete_is(true),
     * after which it will be killed by ProcMgr.
     *
     * This method is called automatically by the default implementation
     * of on_agent_enabled when the agent is disabled. If no special
     * cleanup handling is required, then simply do not override
     * on_agent_enabled and the agent will be killed by ProcMgr as
     * soon as it is administratively disabled.
     */
    virtual void agent_shutdown_complete_is(bool) = 0;

 protected:
    agent_mgr() EOS_SDK_PRIVATE;
    friend class agent_handler;
 private:
    EOS_SDK_DISALLOW_COPY_CTOR(agent_mgr);

};

}

#include <eos/inline/agent.h>

#endif // EOS_AGENT_H
