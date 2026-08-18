// Copyright (c) 2026 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_AGENTS_H
#define EOS_AGENTS_H

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/iterator.h>
#include <string>

namespace eos {

class agents_mgr;

/**
 * Handler for cross-agent state-change notifications.
 * To watch ALL agents, call watch_all_agents(true).
 * To watch specific agents, call watch_agent(name, true).
 * These two modes are mutually exclusive (consistent with base_mgr).
 * watch_all overrides any agent-specific watches.
 */
class EOS_SDK_PUBLIC agents_handler
    : public base_handler<agents_mgr, agents_handler> {
  public:
   explicit agents_handler(agents_mgr* mgr);
   agents_mgr* get_agents_mgr() const;

   /// Register handler to receive changes for all agents. To unsub, pass 'false'.
   void watch_all_agents(bool);

   /**
    * Register this handler to receive changes for a specific agent.
    * Only effective when watch_all_agents is not active.
    */
   void watch_agent(std::string const& agent_name, bool);

   /**
    * Called when an agent's status key is created or changed.
    * @param agent_name The agent whose status changed.
    * @param key The status key that changed.
    * @param value The new value.
    */
   virtual void on_agent_status_set(std::string const& agent_name,
                                    std::string const& key,
                                    std::string const& value);

   /**
    * Called when an agent's status key is deleted.
    * @param agent_name The agent whose status key was removed.
    * @param key The status key that was deleted.
    */
   virtual void on_agent_status_del(std::string const& agent_name,
                                    std::string const& key);

   /// Called when an agent's enabled state changes.
   virtual void on_agent_enabled_set(std::string const& agent_name, bool enabled);
};

class agents_iter_impl;
/// Iterator over agent names.
class EOS_SDK_PUBLIC agents_iter_t
    : public iter_base<std::string, agents_iter_impl> {
  private:
   friend class agents_iter_impl;
   explicit agents_iter_t(agents_iter_impl* const) EOS_SDK_PRIVATE;
};

class agents_option_iter_impl;
/// Iterator over an agent's config option names.
class EOS_SDK_PUBLIC agents_option_iter_t
    : public iter_base<std::string, agents_option_iter_impl> {
  private:
   friend class agents_option_iter_impl;
   explicit agents_option_iter_t(agents_option_iter_impl* const) EOS_SDK_PRIVATE;
};

class agents_status_iter_impl;
/// Iterator over an agent's status keys.
class EOS_SDK_PUBLIC agents_status_iter_t
    : public iter_base<std::string, agents_status_iter_impl> {
  private:
   friend class agents_status_iter_impl;
   explicit agents_status_iter_t(agents_status_iter_impl* const) EOS_SDK_PRIVATE;
};

/**
 * Manager for reading other agents' config and status.
 * This manager provides read-only access to all agents' config options and status
 * keys. It doesn't provide write access to other agents' state. Agents
 * communicate by writing to their own status and watching others' status.
 *
 * Watch registration is done on the handler (watch_all_agents/watch_agent).
 */

class EOS_SDK_PUBLIC agents_mgr : public base_mgr<agents_handler, std::string> {
  public:
   virtual ~agents_mgr();

   /// Iterate over all agent names.
   virtual agents_iter_t agents_iter() const = 0;

   /// Check if agent with given name exists.
   virtual bool agent_exists(std::string const& agent_name) const = 0;

   /// Get status value or returns empty string if the agent or key does not exist.
   virtual std::string agent_status(std::string const& agent_name,
                                    std::string const& key) const = 0;

   /// Check whether a status key exists for an agent.
   virtual bool agent_status_exists(std::string const& agent_name,
                                    std::string const& key) const = 0;

   /// Iterate over status keys for a specific agent.
   virtual agents_status_iter_t agent_status_iter(
       std::string const& agent_name) const = 0;

   /// Get config option value or returns empty string if the agent or option does
   /// not exist.
   virtual std::string agent_option(std::string const& agent_name,
                                    std::string const& key) const = 0;

   /// Check whether a config option exists for an agent.
   virtual bool agent_option_exists(std::string const& agent_name,
                                    std::string const& key) const = 0;

   /// Iterate over config option names for a specific agent.
   virtual agents_option_iter_t agent_option_iter(
       std::string const& agent_name) const = 0;

  protected:
   agents_mgr() EOS_SDK_PRIVATE;
   friend class agents_handler;

  private:
   EOS_SDK_DISALLOW_COPY_CTOR(agents_mgr);
};

}  // namespace eos

#include <eos/inline/agents.h>

#endif  // EOS_AGENTS_H
