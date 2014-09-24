// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_DIRECTFLOW_H
#define EOS_DIRECTFLOW_H

#include <set>

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/iterator.h>
#include <eos/types/directflow.h>

namespace eos {


class directflow_mgr;

/**
 * Flow handler.
 *
 * A flow handler is notified when the status of configured flows changes.
 */
class EOS_SDK_PUBLIC flow_handler : public base_handler<directflow_mgr,
                                                        flow_handler> {
 public:
   explicit flow_handler(directflow_mgr *);
   directflow_mgr * get_directflow_mgr() const;

   /**
    * Registers this class to receive updates on changes to
    * flow state. Expects a boolean signifying whether notifications
    * should be proagated to this instance or not.
    */
   void watch_all_flows(bool);

  /**
    * Registers this class to receive updates on changes to flow state for the given
    * flow name. Expects the name of the flow to watch and a boolean signifying
    * whether notifications should be propagated to this instance or not.
    */
   void watch_flow(std::string const &, bool);

   /// Handler called when flow status changes
   virtual void on_flow_status(std::string const &, flow_status_t);
};


class flow_entry_iter_impl;

/// An iterator providing forwards iteration through the configured flows
class EOS_SDK_PUBLIC flow_entry_iter_t : public iter_base<flow_entry_t,
                                                          flow_entry_iter_impl> {
 private:
   friend class flow_entry_iter_impl;
   explicit flow_entry_iter_t(flow_entry_iter_impl * const) EOS_SDK_PRIVATE;
};


/**
 * DirectFlow configuration and status manager.
 */
class EOS_SDK_PUBLIC directflow_mgr : public base_mgr<flow_handler, std::string> {
 public:
   virtual ~directflow_mgr();

   /// Iterate across all configured flows
   virtual flow_entry_iter_t flow_entry_iter() const = 0;

   /// Tests for existence of a flow entry with the given name
   virtual bool exists(std::string const &) const = 0;

   /// Return the flow entry with the given name
   virtual flow_entry_t flow_entry(std::string const &) const = 0;

   // Flow management functions

   /// Insert or update a flow
   virtual void flow_entry_set(flow_entry_t const &) = 0;
   /// Delete a flow
   virtual void flow_entry_del(std::string const &) = 0;

   /// Return the status of the given flow
   virtual flow_status_t flow_status(std::string const & name) const = 0;
   /**
    * The reason a flow was not programmed. Only valid if the flow's
    * status is FLOW_REJECTED
    */
   virtual flow_rejected_reason_t flow_rejected_reason(std::string const & name)
      const = 0;
   /// Return the counters for a flow
   virtual flow_counters_t flow_counters(std::string const & name) const = 0;

 protected:
   directflow_mgr() EOS_SDK_PRIVATE;
   friend class flow_handler;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(directflow_mgr);
};

} // end namespace eos

#include <eos/inline/directflow.h>

#endif // EOS_DIRECTFLOW_H
