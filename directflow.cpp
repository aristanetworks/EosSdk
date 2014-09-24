// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/directflow.h"
#include "impl.h"

namespace eos {

//
// flow_handler
//

flow_handler::flow_handler(directflow_mgr * mgr) :
      base_handler<directflow_mgr, flow_handler>(mgr) {
   // TODO
}

void
flow_handler::watch_all_flows(bool should_watch) {
}

void flow_handler::watch_flow(std::string const &, bool) {
}

void
flow_handler::on_flow_status(const std::string & name, flow_status_t status) {
}

//
// directflow_mgr
//

class directflow_mgr_impl : public directflow_mgr {
 public:
   directflow_mgr_impl() {
   }

   flow_entry_iter_t flow_entry_iter() const {
      flow_entry_iter_t * nop = 0;
      return *nop;  // TODO: No op impl.
   }

   bool exists(std::string const & name) const {
      return false;
   }

   flow_entry_t flow_entry(std::string const & name) const {
      return flow_entry_t();
   }

   void flow_entry_set(flow_entry_t const & flow_entry) {
   }

   void flow_entry_del(std::string const & name) {
   }

   flow_counters_t flow_counters(std::string const & name) const {
      return flow_counters_t();
   }

   flow_status_t flow_status(std::string const & name) const {
      return FLOW_STATUS_UNKNOWN;
   }

   flow_rejected_reason_t flow_rejected_reason(std::string const & name) const {
      return FLOW_REJECTED_OTHER;
   }

};

DEFINE_STUB_MGR_CTOR(directflow_mgr)

}
