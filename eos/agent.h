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
 * Most agents will inherit from agent_handler to react to the
 * on_initialized() callback. This callback is important because it
 * alerts you that all Sysdb state for other managers and handlers has
 * been synchronized. It is at this point that callbacks to your
 * agent's other handler methods will commence, and that your agent
 * may call a mgr's methods.
 *
 * @warning Note that the features documented below are only available
 * in certain releases, or in conjunction with another extension
 * providing EOS SDK state.
 *
 * In order to gracefully shutdown, agents can override the
 * on_agent_enabled() method provided by the agent_handler in order to
 * cleanup existing resources, such as files or sockets. When a
 * shutdown event is triggered, your agent will not be terminated
 * until it has set the agent_mgr's agent_shutdown_complete_is(true)
 * method. This method will not always be called before your agent
 * exits. During supervisor switchover or reload events (or, if your
 * agent is sent a kill signal), the agent will exit abruptly and this
 * method will not be called.
 *
 * This module also provides a way to handle configuration changes and
 * publish a status. If this agent is configured via the daemon CLI, a
 * custom data store is created for this agent in Sysdb. This data
 * store contains two string-string maps, one for configuration and
 * one for status.
 *
 * Configuration options will be externally set, either via the CLI,
 * eAPI, or programatically in some other manner. Your agent can read
 * configuration options via the agent_mgr's agent_option() method,
 * and should react to options via the agent_handler's
 * on_agent_option() method. Note that you should manually handle
 * existing configuration options when initialized. These options will be
 * reflected in the running configuration so they will persist across
 * supervisor switchovers, and, if written to the startup config, will
 * persist after a reboot.
 *
 * Status data is meant for external consumption; your agent should
 * publish key-value status objects to reflect current status, errors,
 * or other important data that should be monitored. Status can be
 * monitored via the "show daemon [agent_name]" CLI command, or
 * retrieved via an off-box script using an eAPI request with that
 * same command. To publish status, use the agent_mgr's status_set()
 * methods, or unset a status via status_del().
 *
 * To see an example of these methods in use, view
 * examples/CustomStateAgent.cpp.
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
    * Handler called when the configuration options of the agent have
    * changed. If the option was deleted, this will be called with
    * value set as the empty string.
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
     *
     * During supervisor switchover or reload events (or, if your
     * agent is sent a kill signal), the agent will exit abruptly and this
     * method will not be called.
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
